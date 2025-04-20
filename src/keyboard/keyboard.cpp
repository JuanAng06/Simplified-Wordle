#include "keyboard.hpp"

#include "../defs.hpp"

#include <iostream>

//Constructor
Keyboard::Keyboard(Graphics* gfx, int x, int y, int s)
: keyboardS(gfx), startX(x), startY(y), size(s) {
    font = keyboardS->loadFont(KEYBOARD_FONT, KEYBOARD_TEXT_SIZE);
    if (!font) std::cerr << "Error, font not loaded!" << TTF_GetError() << std::endl;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 10; j++){
            keyChar[i][j] = -1;
        }
    }
}

//Render the keyboard
void Keyboard::renderKeyboard(SDL_Color textColor){

    for (size_t row = 0; row < keyboardRows.size(); row++){
        std::string &currentKeyRow = keyboardRows[row];
        int posY = startY + ROW_SPACING * row;

        for (size_t i = 0; i < currentKeyRow.length(); i++){
            int posX = startX + PADDING * i - 10;
            if (row == 1) posX += PADDING / 2;
            if (row == 2) posX += PADDING * 3 / 2;

            // !!!TEST ZONE !!!

            SDL_Texture *keyTexture = nullptr;
            switch (keyChar[row][i]){
                case 0:
                    keyTexture = grayKey;
                    break;
                
                case 1:
                    keyTexture = yellowKey;
                    break;

                case 2:
                    keyTexture = greenKey;
                    break;
            }

            // !!! TEST ZONE !!!
            if (keyTexture){
                keyboardS->renderTexture(keyTexture, posX, posY);
            }
            //~~~~~~~~~~~~~~~~~~~~~~~

            keyboardS->renderTexture(keyLayout, 0, MID_HEIGHT);
        }
    }
}

// !!! TEST ZONE !!!: Update keyboard state (2, 1, 0, -1)
void Keyboard::updateKeyboardState(const std::vector<std::vector<int>>& keyState, int currentRow, const std::string& previousGuess){
    std::string guessUpper = previousGuess;
    for (char &c : guessUpper) c = toupper(c);

    for (size_t i = 0; i < guessUpper.size(); i++){
        char guessedChar = guessUpper[i];
        int newState = keyState[currentRow][i];

        for (size_t row = 0; row < keyboardRows.size(); row++){
            const std::string& currentKBRow = keyboardRows[row];

            for (size_t col = 0; col < currentKBRow.size(); col++){
                if (currentKBRow[col] == guessedChar && keyChar[row][col] < newState){
                    keyChar[row][col] = newState;
                }
            }
        }
    }

    //debug
    std::cout << "Key state: " << std:: endl;
    for (size_t i = 0; i < 3; i++){
        for (size_t j = 0; j < 10; j++){
            std::cout << keyChar[i][j] << " ";
        }
        std::cout << std::endl;
    }

}

//Clean up
Keyboard::~Keyboard(){
    if (grayKey) SDL_DestroyTexture(grayKey);
    if (yellowKey) SDL_DestroyTexture(yellowKey);
    if (greenKey) SDL_DestroyTexture(greenKey);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~ Destroyed keyboard successfully! ~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

//~~~ TEST ZONE ~~~
void Keyboard::reset(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 10; j++){
            keyChar[i][j] = -1;
        }
    }
}