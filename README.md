# wolfenstein-clone
Simple wolfenstein clone to get back into the C language !

## Prerequisites
The [GCC Compiler](https://gcc.gnu.org/)
The [SDL2 Library](https://www.libsdl.org)
`sudo apt install libsdl2-dev`

## Running the project:
`mkdir -p /out && gcc main.c -o ./out/main -I/usr/local/include/SDL2 -L/usr/local/lib -lSDL2 -lm && ./out/main`