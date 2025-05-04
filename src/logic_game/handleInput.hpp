#ifndef HANDLE_INPUT_HPP
#define HANDLE_INPUT_HPP

#include <string>
#include <SDL2/SDL.h>

#include "grid.hpp"

#include "../init/music_and_background/audioManager.hpp"
#include "../defs.hpp"

class HandleInput{
    public:
        void handleEvent(SDL_Event& event, std::string& currentWord, int& currentCol, int& currentRow, int maxCols, Grid*grid);
        std::string getPreviousWord() const {
            return previousWord;
        }

        //Key press sound effect
        void playKeySound();

        //Constructor
        HandleInput(); //Default
        HandleInput(Audio* audio);

        //Destructor
        ~HandleInput();

    private:
        std::string previousWord = "";

        Audio* sound = nullptr;
        Mix_Chunk* enterKey_sfx = nullptr;

        //Keyboard sound
        Mix_Chunk* keySound_1 = nullptr;
        Mix_Chunk* keySound_2 = nullptr;
        Mix_Chunk* keySound_3 = nullptr;
        Mix_Chunk* keySound_4 = nullptr;
        Mix_Chunk* keySound_5 = nullptr;
};

#endif