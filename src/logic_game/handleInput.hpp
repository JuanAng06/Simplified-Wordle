#ifndef HANDLE_INPUT_HPP
#define HANDLE_INPUT_HPP

#include <string>
#include <SDL2/SDL.h>

#include "grid.hpp"

class HandleInput{
    public:
        void handleEvent(SDL_Event& event, std::string& currentWord, int& currentCol, int maxCols, Grid&grid, int& currentRow);
        std::string getPreviousWord() const {
            return previousWord;
        }

    private:
        std::string previousWord = "";
};

#endif