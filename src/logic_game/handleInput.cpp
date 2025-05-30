#include "handleInput.hpp"
#include "../utils/utils.hpp"

#include <iostream>

HandleInput::HandleInput(){} //Default constructor

//Constructor
HandleInput::HandleInput(Audio* audio){

    sound = audio;

    enterKey_sfx = sound->loadSound(ENTER_KEY);

    //Keyboard input
    keySound_1 = sound->loadSound(KEY_SOUND_1);
    keySound_2 = sound->loadSound(KEY_SOUND_2);
    keySound_3 = sound->loadSound(KEY_SOUND_3);
    keySound_4 = sound->loadSound(KEY_SOUND_4);
    keySound_5 = sound->loadSound(KEY_SOUND_5);
}

//Handle input event
void HandleInput::handleEvent(SDL_Event& event, std::string& currentWord, int& currentCol, int& currentRow, int maxCols, Grid*grid){

    if (event.type == SDL_KEYDOWN){
        playKeySound();
    }

    if (event.type == SDL_TEXTINPUT && currentCol < maxCols && isValidChar(event.text.text[0])){
        currentWord += event.text.text[0];
        grid->setLetter(currentRow,currentCol, event.text.text[0]);
        currentCol++;
    }
    
    //Case : Backspace
     else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && currentCol > 0){
        currentWord.pop_back();
        currentCol--;
        grid->setLetter(currentRow, currentCol, ' ');

        std::cout << "BACKSPACE was pressed." << std::endl; //Debug
    }

    //Case: Enter
    else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && currentWord.size() == 5){

        sound->playSfx(enterKey_sfx);

        if (currentRow < ROWS - 1){
            previousWord = currentWord;
            currentCol = 0;
        }

        std::cout << "ENTER was pressed." << std::endl; //Debug
    }

    //Debug
    if(isValidChar(event.text.text[0])){
        std::cout << "currentWord: " << currentWord << std::endl 
        << "previousWord: " << previousWord << std::endl
        << "Current pos: (" << currentCol << ", " << currentRow << ")" << std::endl
        << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    }
}

//Random sfx each key was pressed
void HandleInput::playKeySound(){
    std::vector<Mix_Chunk*> playSound = {keySound_1, keySound_2, keySound_3, keySound_4, keySound_5};
    int index = rand() % playSound.size();
    sound->playSfx(playSound[index]);
}

//Destructor
HandleInput::~HandleInput(){

    sound->quitSound(ENTER_KEY, enterKey_sfx);
    sound->quitSound(KEY_SOUND_1, keySound_1);
    sound->quitSound(KEY_SOUND_2, keySound_2);
    sound->quitSound(KEY_SOUND_3, keySound_3);
    sound->quitSound(KEY_SOUND_4, keySound_4);
    sound->quitSound(KEY_SOUND_5, keySound_5);
    
    if (enterKey_sfx || keySound_1 || keySound_2 || keySound_3 || keySound_4 || keySound_5)
        std::cout << "[DEBUG] Failed to destroy HandleInput!" << std::endl;
    else std::cout << "[DEBUG] Destroyed HandleInput successfully!" << std::endl;
}