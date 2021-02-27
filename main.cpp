#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include "header/Game.h"

int main(int argc, char* argv[])
{
    Game * game = new Game();


    delete game;

    return 0;
}