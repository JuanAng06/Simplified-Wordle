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
        bool isOnMainMenu();
        void resetGame(Keyboard &keyboard, Grid& grid, WordProcessor &wordProcessor, bool &gameRunning);
        void exitGame();
        void continueGame();

        //Process main logic
        void newGame();
        bool correctGuess(const std::vector<int> &gridState);
        void runGameLoop(HandleInput &inputHandler, Grid& grid, Keyboard& keyboard, Result& result, ScrollingBackground& background, std::string& secretWord);
        void processResult(bool& guessedCorrectly, int& currentRow, std::string& secretWord,
                            Keyboard& keyboard, Grid& grid, WordProcessor& wordProcessorTest, Result& result, bool& gameRunning, bool &onMenu);

        //Render frame
        void renderFrame(ScrollingBackground &background, Grid& grid, Keyboard& keyboard, Result& result, const SDL_Color& textCol, Button& backToMenuBtn, Button& giveUpBtn,
                        bool& showOnce, bool& didShowWhenInvalid);
        void renderFrame(); //Add later

        void cleanUp(); //Quit

    private:
        Graphics graphics;

        WordProcessor wordProcessorTest;

        SDL_Event event;
        int mouseX, mouseY;

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
	    Audio audio;
        Mix_Chunk* clickSound = nullptr;
        Mix_Music* bgm = nullptr;

        ///////////////////////// UI initialization ///////////////////////////////////
        SDL_Texture* guess_board = nullptr;
        SDL_Texture* gradient = nullptr;
        SDL_Texture* keyboard_layout = nullptr;

        //Grid initialization
        TTF_Font *gridFont = nullptr;

        //Sth
        std::string currentWord = "";
        int currentCol = 0;
        int currentRow = 0;

        bool keepRunning = true;
        bool gameRunning = true;
        
        bool showOnce = true;
        bool didShowWhenInvalid = false;
        bool onMenu = true;

        

        //Button Initialization - TEST
        Button backToMenuBtn;
        Button giveUpBtn;

        //Text color
        SDL_Color textColor = {255, 255, 255, 255}; //WHITE
};
#endif