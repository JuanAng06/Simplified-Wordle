#include "handleInput.hpp"
#include "../utils/utils.hpp"

#include <iostream>

//Handle input event
void HandleInput::handleEvent(SDL_Event& event, std::string& currentWord, int& currentCol, int maxCols, Grid&grid, int& currentRow){
    if (event.type == SDL_TEXTINPUT && currentCol < maxCols && isValidChar(event.text.text[0])){
        currentWord += event.text.text[0];
        grid.setLetter(currentRow,currentCol, event.text.text[0]);
        currentCol++;

        std::cout << "A key was pressed : " << std::endl;
        std::cout << "currentWord: " << currentWord << std::endl 
                << "previousWord: " << previousWord << std::endl
                << "currentCol: " << currentCol << std::endl 
                << "currentRow: " << currentRow << std::endl;

    } 
    
    //Case : Backspace
     else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && currentCol > 0){
        currentWord.pop_back();
        currentCol--;
        grid.setLetter(currentRow, currentCol, ' ');

        std::cout << "BACKSPACE" << std::endl;
        std::cout << "currentWord: " << currentWord << std::endl 
                << "currentCol: " << currentCol << std::endl 
                << "currentRow: " << currentRow << std::endl;
    }

    //Case: Enter
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && currentWord.size() == 5){
        if (currentRow < ROWS - 1){
            previousWord = currentWord;
            currentCol = 0;
        }

        std::cout << "ENTER" << std::endl;
        std::cout << "currentWord: " << currentWord << std::endl 
                << "previousWord: " << previousWord << std::endl
                << "currentCol: " << currentCol << std::endl 
                << "currentRow: " << currentRow << std::endl;
    }
}