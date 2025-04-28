#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "init/game.hpp"

int main(int argc, char* argv[])
{
    Start game;
    game.play();
    return 0;
}
