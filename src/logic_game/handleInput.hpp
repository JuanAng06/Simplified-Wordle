#ifndef HANDLE_INPUT_HPP
#define HANDLE_INPUT_HPP

#include <string>
#include <SDL2/SDL.h>

#include "grid.hpp"

//~~~TEST ZONE ~~~
#include "../init/music_and_background/audioManager.hpp"
#include "../defs.hpp"

class HandleInput{
    public:
        void handleEvent(SDL_Event& event, std::string& currentWord, int& currentCol, int maxCols, Grid&grid, int& currentRow);
        std::string getPreviousWord() const {
            return previousWord;
        }

        //Key press sound effect
        void playKeySound();

    private:
        std::string previousWord = "";

        //~~~ TEST ZONE ~~~
        Audio* sound;
        Mix_Chunk* enterKey_sfx = sound->loadSound(ENTER_KEY);

        //Keyboard input
        Mix_Chunk* keySound_1 = sound->loadSound(KEY_SOUND_1);
        Mix_Chunk* keySound_2 = sound->loadSound(KEY_SOUND_2);
        Mix_Chunk* keySound_3 = sound->loadSound(KEY_SOUND_3);
        Mix_Chunk* keySound_4 = sound->loadSound(KEY_SOUND_4);
        Mix_Chunk* keySound_5 = sound->loadSound(KEY_SOUND_5);
};

#endif