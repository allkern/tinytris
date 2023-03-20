
#ifdef __cplusplus
#pragma once
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#else
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#endif

#if (!defined(_TETRIS_H)) || defined(__cplusplus)
#define _TETRIS_H

#define TETROMINO_I 0
#define TETROMINO_J 1
#define TETROMINO_L 2
#define TETROMINO_O 3
#define TETROMINO_S 4
#define TETROMINO_T 5
#define TETROMINO_Z 6

static const uint8_t i_piece_srs[4 * 4 * 4] = {
    0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0
};

static const uint8_t j_piece_srs[4 * 4 * 4] = {
    0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 2, 2, 0
};

static const uint8_t l_piece_srs[4 * 4 * 4] = {
    0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 3, 3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 3, 3,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 3, 0, 0,
    0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 3, 0, 0, 0, 3, 0
};

static const uint8_t o_piece_srs[4 * 4 * 4] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 4, 4
};

static const uint8_t s_piece_srs[4 * 4 * 4] = {
    0, 0, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 5, 0, 0, 0, 5,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 5, 5, 0,
    0, 0, 0, 0, 0, 5, 0, 0, 0, 5, 5, 0, 0, 0, 5, 0
};

static const uint8_t t_piece_srs[4 * 4 * 4] = {
    0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 6, 6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 6, 6, 0, 0, 6, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 6, 0,
    0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 6, 0, 0, 0, 6, 0
};

static const uint8_t z_piece_srs[4 * 4 * 4] = {
    0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 7, 7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 7, 7, 0, 0, 7, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 0, 7, 7,
    0, 0, 0, 0, 0, 0, 7, 0, 0, 7, 7, 0, 0, 7, 0, 0
};

const uint8_t* pieces[7] = {
    i_piece_srs,
    j_piece_srs,
    l_piece_srs,
    o_piece_srs,
    s_piece_srs,
    t_piece_srs,
    z_piece_srs
};

static const unsigned tetromino_sizes[7] = {
    4, 3, 3, 2, 3, 3, 3
};

struct tetromino_t {
    // We only use the 4 LSBs of each byte
    uint8_t buf[4 * 4];

    unsigned x, y;
    unsigned size, rot, type;
};

tetromino_t* tetromino_create() {
    return new tetromino_t;
}

void tetromino_init(tetromino_t* ttr, int type) {
    std::memcpy(ttr->buf, pieces[type], 4 * 4);

    ttr->x = 0;
    ttr->y = 0;
    ttr->size = tetromino_sizes[type];
    ttr->rot = 0;
    ttr->type = type;
}

void tetromino_rotate(tetromino_t* ttr, bool cw) {
    ttr->rot = (ttr->rot + (cw ? 1 : (-1))) & 3;

    std::memcpy(ttr->buf, &pieces[ttr->type][ttr->rot * (4 * 4)], 4 * 4);
}

#define TRIS_PF_WIDTH  12
#define TRIS_PF_HEIGHT 21

struct tetris_t {
    // 40x10 + edges
    uint8_t playfield[TRIS_PF_WIDTH * TRIS_PF_HEIGHT];

    uint8_t next;
    tetromino_t* current;
};

tetris_t* tris_create() {
    return new tetris_t;
}

unsigned get_random_tetromino() {
    srand(time(NULL));

    return rand() % 7;
}

void tris_spawn_tetromino(tetris_t* tris) {
    tetromino_init(tris->current, tris->next);

    tris->current->x = (TRIS_PF_WIDTH / 2) - (4 - tris->current->size);
    tris->current->y = 0;

    tris->next = get_random_tetromino();
}

void tris_init(tetris_t* tris) {
    std::memset(tris->playfield, 0, (TRIS_PF_WIDTH * sizeof(uint8_t)) * (TRIS_PF_HEIGHT * sizeof(uint8_t)));

    tris->next = get_random_tetromino();
    tris->current = tetromino_create();
    
    tris_spawn_tetromino(tris);

    // Fill edges in
    for (int y = 0; y < TRIS_PF_HEIGHT - 1; y++) {
        tris->playfield[0 + (y * TRIS_PF_WIDTH)] = 8;
        tris->playfield[(TRIS_PF_WIDTH - 1) + (y * TRIS_PF_WIDTH)] = 8;
    }

    for (int x = 0; x < TRIS_PF_WIDTH; x++) {
        tris->playfield[x + ((TRIS_PF_HEIGHT - 1) * TRIS_PF_WIDTH)] = 8;
    }
}

#define TRIS_CHECK_COLLISION_DOWN(t)  tris_check_collision(t,  0, 1)
#define TRIS_CHECK_COLLISION_LEFT(t)  tris_check_collision(t, -1, 0)
#define TRIS_CHECK_COLLISION_RIGHT(t) tris_check_collision(t,  1, 0)
#define DOWN  0
#define LEFT  1
#define RIGHT 2

bool tris_check_collision(tetris_t* tris, int offx, int offy) {
    int tx = tris->current->x;
    int ty = tris->current->y;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            uint8_t ttb = tris->current->buf[x + (y * 4)];
            
            if (ttb && tris->playfield[(tx + x + offx) + ((ty + y + offy) * TRIS_PF_WIDTH)]) {
                return true;
            }
        }
    }

    return false;
}

bool tris_move_tetromino(tetris_t* tris, int direction) {
    switch (direction) {
        case DOWN: {
            if (!TRIS_CHECK_COLLISION_DOWN(tris)) {
                tris->current->y++;

                return true;
            } else {
                return false;
            }
        } break;

        case LEFT: {
            if (!TRIS_CHECK_COLLISION_LEFT(tris)) {
                tris->current->x--;

                return true;
            } else {
                return false;
            }
        }
        
        case RIGHT: {
            if (!TRIS_CHECK_COLLISION_RIGHT(tris)) {
                tris->current->x++;

                return true;
            } else {
                return false;
            }
        }
    }

    return false;
}

void tris_collapse_down(tetris_t* tris, int line) {
    for (int y = line; y > 0; y--) {
        for (int x = 1; x < TRIS_PF_WIDTH - 1; x++) {
            tris->playfield[x + (y * TRIS_PF_WIDTH)] = 0;
        }

        for (int x = 1; x < TRIS_PF_WIDTH - 1; x++) {
            tris->playfield[x + (y * TRIS_PF_WIDTH)] = tris->playfield[x + ((y - 1) * TRIS_PF_WIDTH)];
        }
    }
}

bool tris_tick(tetris_t* tris) {
    if (!tris_move_tetromino(tris, DOWN)) {
        int tx = tris->current->x;
        int ty = tris->current->y;

        // Copy tetromino to playfield
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                uint8_t ttb = tris->current->buf[x + (y * 4)];
                
                if (ttb) {
                    tris->playfield[(tx + x) + ((ty + y) * TRIS_PF_WIDTH)] = ttb;
                }
            }
        }

        // Check for lines
        for (int y = 0; y < TRIS_PF_HEIGHT - 1; y++) {
            int blocks = 0;

            for (int x = 1; x < TRIS_PF_WIDTH - 1; x++) {
                if (tris->playfield[x + (y * TRIS_PF_WIDTH)]) {
                    blocks++;
                }
            }

            if (blocks == (TRIS_PF_WIDTH - 2)) {
                tris_collapse_down(tris, y);
            }
        } 

        // Spawn a new tetromino
        tris_spawn_tetromino(tris);

        return true;
    }

    return false;
}

#endif