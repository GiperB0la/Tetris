#include "include/Tetris.hpp"
#include <windows.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    TetrisGame game;
    game.run();

    return 0;
}