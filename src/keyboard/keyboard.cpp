#include "keyboard.hpp"

#include "../defs.hpp"

#include <iostream>

//Default constructor
Keyboard::Keyboard(){}

//Constructor
Keyboard::Keyboard(Graphics* gfx, int x, int y)
: keyboardS(gfx), startX(x), startY(y) {
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

            if (keyTexture){
                keyboardS->renderTexture(keyTexture, posX, posY);
            }

            keyboardS->renderTexture(keyLayout, 0, MID_HEIGHT);
        }
    }
}

//Update keyboard state (2, 1, 0, -1)
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
}

//Destructor
Keyboard::~Keyboard(){
    keyboardS->destroyTexture(KEY_GRAY_IMG, grayKey);
    keyboardS->destroyTexture(KEY_YELLOW_IMG, yellowKey);
    keyboardS->destroyTexture(KEY_GREEN_IMG, greenKey);

    if (grayKey || yellowKey || greenKey) std::cout << "[DEBUG] Failed to destroy Keyboard" << std::endl;
    else std::cout << "[DEBUG] Destroyed keyboard successfully!" << std::endl;
}

//Reset keyboard
void Keyboard::reset(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 10; j++){
            keyChar[i][j] = -1;
        }
    }
}