#include "tetris.h"
#include "SDL.h"

#include <vector>
#include <iostream>

#define TRIS_DISPLAY_WIDTH (TRIS_PF_WIDTH * 2)
#define TRIS_DISPLAY_HEIGHT TRIS_PF_HEIGHT
#define TRIS_DISPLAY_SCALE 24

#undef main

void draw_ghost_tetromino(tetris_t* tris, uint32_t* buf) {
    // Save current tetromino
    tetromino_t* copy = tetromino_create();

    *copy = *tris->current;

    // Move to bottom
    while (tris_move_tetromino(tris, DOWN));

    int tx = tris->current->x;
    int ty = tris->current->y;

    // Draw ghost tetromino
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            uint8_t tb = tris->current->buf[x + (y * 4)];

            if (tb) {
                buf[(x + tx) + ((y + ty) * TRIS_DISPLAY_WIDTH)] = 0x555555ff;
            }
        }
    }

    delete tris->current;

    // Restore current tetromino
    tris->current = copy;
}

int main(int argc, const char* argv[]) {
    SDL_Window* window = SDL_CreateWindow(
        "Tinytris",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        TRIS_DISPLAY_WIDTH * TRIS_DISPLAY_SCALE, TRIS_DISPLAY_HEIGHT * TRIS_DISPLAY_SCALE,
        SDL_WINDOW_OPENGL
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_Texture* texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING,
        TRIS_DISPLAY_WIDTH, TRIS_DISPLAY_HEIGHT
    );

    static const uint32_t colors[10] = {
        0x000000ff, 0x0000ffff, 0x00ff00ff, 0x00ffffff,
        0xff0000ff, 0xff00ffff, 0xffff00ff, 0xffffffff,
        0xaaaaaaff, 0x555555ff
    };

    std::vector <uint32_t> buf;

    buf.resize(TRIS_DISPLAY_WIDTH * TRIS_DISPLAY_HEIGHT);

    bool open = true;

    tetris_t* tris = tris_create();

    tris_init(tris);

    int frames = 60; 

    while (open) {
        // Draw playfield
        for (int y = 0; y < TRIS_PF_HEIGHT; y++) {
            for (int x = 0; x < TRIS_PF_WIDTH; x++) {
                uint8_t pf = tris->playfield[x + (y * TRIS_PF_WIDTH)];

                buf[x + (y * TRIS_DISPLAY_WIDTH)] = colors[pf];
            }
        }

        draw_ghost_tetromino(tris, buf.data());

        int tx = tris->current->x;
        int ty = tris->current->y;

        // Draw current tetromino
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                uint8_t tb = tris->current->buf[x + (y * 4)];

                if (tb) {
                    buf[(x + tx) + ((y + ty) * TRIS_DISPLAY_WIDTH)] = colors[tb];
                }
            }
        }

        SDL_UpdateTexture(texture, NULL, buf.data(), TRIS_DISPLAY_WIDTH * sizeof(uint32_t));
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        if (!frames--) {
            tris_tick(tris);

            frames = 60;
        }

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    open = false;
                } break;

                case SDL_KEYDOWN: {
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT: {
                            tris_move_tetromino(tris, LEFT);
                        } break;

                        case SDLK_RIGHT: {
                            tris_move_tetromino(tris, RIGHT);
                        } break;

                        case SDLK_DOWN: {
                            tris_tick(tris);
                        } break;

                        case SDLK_UP: {
                            // Check if rotation is possible
                            tetromino_t* copy = tetromino_create();

                            *copy = *tris->current;

                            tetromino_rotate(tris->current, true);

                            if (TRIS_CHECK_COLLISION_DOWN(tris)) {
                                delete tris->current;

                                tris->current = copy;
                            } else {
                                delete copy;
                            }
                        } break;

                        case SDLK_SPACE: {
                            while (!tris_tick(tris));
                        } break;
                    }
                } break;
            }
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}