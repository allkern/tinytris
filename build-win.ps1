$ELFIO_DIR = "elfio"
$IMGUI_DIR = "imgui"
$SDL2_DIR = "sdl2\x86_64-w64-mingw32"
$TETRIS_DIR = "."

md -Force -Path bin > $null

c++ -I"`"$($TETRIS_DIR)`"" `
    -I"`"$($SDL2_DIR)\include`"" `
    -I"`"$($SDL2_DIR)\include\SDL2`"" `
    -I"`"$($IMGUI_DIR)`"" `
    -I"`"$($IMGUI_DIR)\backends`"" `
    "build-win32\*.o" `
    "main.cpp" `
    -o "bin\tetris.exe" `
    -L"`"$($SDL2_DIR)\lib`"" `
    -m64 -std=c++2a -lSDL2main -lSDL2 `
    -g -O3 -Wall -pedantic -Wno-format-security