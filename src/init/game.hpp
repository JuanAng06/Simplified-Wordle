#ifndef GAME_HPP
#define GAME_HPP

#include "graphics.hpp"
#include "../defs.hpp"

#include "../keyboard/keyboard.hpp"
#include "../logic_game/handleInput.hpp"
#include "../logic_game/grid.hpp"
#include "../logic_game/wordProcessor.hpp"
#include "../logic_game/popup.hpp"

#include "../utils/utils.hpp"

#include <vector>

class Start{
    public:
        void play();

        void loadMenuTexture();
        bool isTutorialConfirmButton(int x, int y);
        bool isTutorialButton(int x, int y);
        bool isExitButton(int x, int y);
        bool isPlayButton(int x, int y);
        bool isOnMainMenu();

        //Main UI button
        void loadMainTexture();

        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        void resetGame(Keyboard &keyboard, Grid& grid, WordProcessor &wordProcessor, bool &gameRunning);
        void exitGame(bool &gameRunning, bool &keepRunning);
        void continueGame(std::string& currentWord, int& currentCol, int& currentRow);

        //NO
        void cleanup();

    private:

    //~~~ TEST ZONE
        Graphics graphics;
        SDL_Event event;
        int mouseX, mouseY;

        SDL_Texture* menuScreen = nullptr;
        SDL_Texture* menu_ExitButton = nullptr;
        SDL_Texture* menu_TutorialButton = nullptr;
        SDL_Texture* menu_PlayButton = nullptr;
        SDL_Texture* menu_tutorialScreen = nullptr;
        SDL_Texture* tutorial_okayButton = nullptr;

        //Back button + give up button
        SDL_Texture* backToMenuButton = nullptr;
        SDL_Texture* backToMenuButton_hover = nullptr;
        SDL_Texture* giveUpButton = nullptr;
        SDL_Texture* giveUpButton_hover = nullptr;

    //~~~~~~~~~~~~~

    //Audio
	Audio audio;
    Mix_Chunk* clickSound = nullptr;
};
#endif