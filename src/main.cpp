#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "init/game.hpp"

#include "logic_game/wordProcessor.hpp"

using namespace std;

//Wait to quit
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        //SDL_Delay(100);
    }
}

int main(int argc, char* argv[])
{
    //TEST ZONE !!!!

    std::cout << "~~~~~ THIS IS A TEST ZONE !!!! ~~~~" << std::endl;

    // end of "TEST ZONE !!!!"
    Start start;
    start.play();
    return 0;
}
