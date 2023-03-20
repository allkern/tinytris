git clone https://github.com/ocornut/imgui
git clone https://github.com/libsdl-org/SDL.git -b SDL2 sdl2

$IMGUI_DIR = "..\imgui"
$SDL2_DIR = "..\sdl2\x86_64-w64-mingw32"

md -Force -Path build-win32 > $null

cd build-win32

Write-Output "Building ImGui..."

c++ -I"`"$($IMGUI_DIR)`"" `
    -I"`"$($IMGUI_DIR)\backends`"" `
    -I"`"$($SDL2_DIR)\include\SDL2`"" `
    "`"$($IMGUI_DIR)\backends\imgui_impl_sdl2.cpp`"" `
    "`"$($IMGUI_DIR)\backends\imgui_impl_sdlrenderer.cpp`"" `
    "`"$($IMGUI_DIR)\*.cpp`"" `
    -c -m64

cd ..