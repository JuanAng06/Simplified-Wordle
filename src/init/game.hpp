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

        //Load assets
        void initGameObjects();
        void loadMenuTexture();
        void loadMainTexture();

        //Main function
        bool gonnaPlay();
        void resetGame();
        void exitGame();
        void continueGame();

        //Process main logic
        void newGame();
        bool correctGuess(const std::vector<int> &gridState);
        void runGameLoop();
        void processResult();

        //Render frame
        void renderFrame();

        //Quit
        void cleanUp();

    private:
        Graphics graphics;
        Audio audio;
        HandleInput* inputHandler;
        Keyboard* keyboard;
        Grid* grid;
        Result* result;
        ScrollingBackground background;
        WordProcessor wordProcessorTest;
        std::string secretWord = "";

        SDL_Event event;

        //Main menu
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

        //Audio
        Mix_Chunk* clickSound = nullptr;
        Mix_Music* bgm = nullptr;

        ///////////////////////// UI initialization ///////////////////////////////////
        SDL_Texture* guess_board = nullptr;
        SDL_Texture* gradient = nullptr;
        SDL_Texture* keyboard_layout = nullptr;

        //Grid initialization
        TTF_Font *gridFont = nullptr;

        //Uses for processing word
        std::string currentWord = "";
        int currentCol = 0;
        int currentRow = 0;

        bool keepRunning = true;
        bool gameRunning = true;
        
        bool showOnce = true;
        bool didShowWhenInvalid = false;
        bool onMenu = true;

        bool guessedCorrectly = false;

        //Button Initialization
        Button backToMenuBtn;
        Button giveUpBtn;

        //Text color
        SDL_Color textColor = {255, 255, 255, 255}; //WHITE
};
#endif