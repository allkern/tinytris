.ONESHELL:

VERSION_TAG := $(shell git describe --always --tags --abbrev=0)
COMMIT_HASH := $(shell git rev-parse --short HEAD)
OS_INFO := $(shell uname -rmo)

OBJECTS := $(wildcard build-linux/*.o)
SOURCES := main.cpp

SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)

IMGUI_DIR := "imgui"

bin/tetris main.cpp:
	mkdir -p bin

	c++ -g $(OBJECTS) $(SOURCES) -o bin/tetris \
		-I"." \
		-I$(IMGUI_DIR) \
		-I$(IMGUI_DIR)/backends \
		-DOS_INFO="$(OS_INFO)" \
		-DREP_VERSION="$(VERSION_TAG)" \
		-DREP_COMMIT_HASH="$(COMMIT_HASH)" \
		-lSDL2 -g -Wno-format-security -std=c++2a \
		$(SDL_CFLAGS) $(SDL_LDFLAGS)

build-sdl2:
	git clone https://github.com/libsdl-org/SDL.git -b SDL2 sdl2-linux
	cd sdl2-linux
	mkdir build
	cd build
	../configure
	make
	sudo make install

IMGUI_SRC := $(addprefix ../, $(wildcard imgui/*.cpp))

deps:
	git clone https://github.com/serge1/elfio
	git clone https://github.com/ocornut/imgui
	mkdir -p build-linux
	cd build-linux
	c++ -I../$(IMGUI_DIR) \
	    -I../$(IMGUI_DIR)/backends \
	    -c ../$(IMGUI_DIR)/backends/imgui_impl_sdl2.cpp \
	       ../$(IMGUI_DIR)/backends/imgui_impl_sdlrenderer.cpp \
	       $(IMGUI_SRC) \
		$(SDL_CFLAGS) $(SDL_LDFLAGS)

clean:
	rm -rf "build-linux"
	rm -rf "bin"
