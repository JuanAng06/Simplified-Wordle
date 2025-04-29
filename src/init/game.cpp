/*TO DO:
	Destructor for all files
	Refractor code
*/

#include "game.hpp"
#include "graphics.hpp"
#include "music_and_background/audioManager.hpp"
#include "../keyboard/keyboard.hpp"
#include "../logic_game/handleInput.hpp"
#include "../logic_game/grid.hpp"
#include "../logic_game/wordProcessor.hpp"
#include "../logic_game/popup.hpp"

#include <iostream>

void Start::play() {

	WordProcessor wordProcessorTest;

	wordProcessorTest.loadDictionary(DICTIONARY);

	//////////////////////// Initialization ///////////////////////

	//class Graphics
	// Graphics graphics;
	graphics.init();

	//~~~ TEST ZONE
	loadMenuTexture();

	//class Audio
	// Audio audio;

	//class Keyboard
	Keyboard keyboard(&graphics);
	SDL_Color textColor = {255, 255, 255, 255};

	///////////////////////// UI initialization ///////////////////////////////////

	//Load scrolling background
	ScrollingBackground background;
	background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

	//Background music
	Mix_Music *bgm = audio.loadMusic(BGM);
	audio.play(bgm);

	//main UI
	SDL_Texture* guess_board = graphics.loadTexture(GUESS_GRID_IMG);
	SDL_Texture* gradient = graphics.loadTexture(GRADIENT_IMG);
	SDL_Texture* keyboard_layout = graphics.loadTexture(KEYBOARD_IMG);

	//Input handler
	HandleInput inputHandler;

	//Grid initialization
	TTF_Font* gridFont = graphics.loadFont(KEYBOARD_FONT, 30);
	Grid grid(&graphics, gridFont);
	std::string currentWord = "";
	int currentCol = 0;
	int currentRow = 0;

	//Pop Up Message
	Result result(&graphics);

	//Back & Give Up button - TEST ZONE
	loadMainTexture();
	Button backToMenuBtn(&graphics, 30, 30, 60, 60, backToMenuButton, backToMenuButton_hover);
	Button giveUpBtn(&graphics, SCREEN_WIDTH - 180, 30, 150, 60, giveUpButton, giveUpButton_hover);

	///////////////////////// Game loop ////////////////////////////
	bool keepRunning = true;

	bool onMenu = true;

	SDL_Event event;

	//Game loop
	while (keepRunning) {

		//Set a secret word
		wordProcessorTest.setSecretWord();
		std::string secretWord = wordProcessorTest.getSecretWord();
		std::cout << "Secret Word: " << secretWord << std::endl;

		std::string currentWord = "";
		int currentCol = 0;
		int currentRow = 0;

		bool gameRunning = true;

		bool showOnce = true;
		bool didShowWhenInvalid = false;

		while (gameRunning) {

			if (onMenu && !isOnMainMenu()) exitGame(gameRunning, keepRunning);
			else onMenu = false;

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					exitGame(gameRunning, keepRunning);
				}

				inputHandler.handleEvent(event, currentWord, currentCol, COLS, grid, currentRow);

				//Process the check prucedure
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && currentRow < ROWS) {
					if (currentWord.length() == 5) {

						//debug (DO NOT REMOVE - It crashed somehow)
						std::cout << std::string(20, '~') << std::endl;
						std::cout << "ENTER was pressed" << std::endl;

						//Update the guess stat (Use previousGuess to check)
						wordProcessorTest.updatePreviousGuess(inputHandler);

						//Check and update grid state
						wordProcessorTest.checkGuess(currentWord, currentRow);
						const std::vector<std::vector<int>>& gridState = wordProcessorTest.getGridState();
						keyboard.updateKeyboardState(gridState, currentRow, wordProcessorTest.getPreviousGuess());

						//debug
						grid.updateGridState(gridState);

						std::cout << "Current row: " << currentRow + 1 << "/ 6" << std::endl;

						std::cout << std::endl << "Previous grid state: " << std::endl;
						for (int i : gridState[currentRow]) {
							std::cout << i << " ";
						}
						std::cout << std::endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

						//Check if the game over
						bool guessedCorrectly = true;
						for (int status : gridState[currentRow]) {
							if (status != 2) {
								guessedCorrectly = false;
								break;
							}
						}

						if (guessedCorrectly || currentRow == ROWS - 1) {
							if (guessedCorrectly) std::cout << " ~~~~~~~~~~~~ User found the word ~~~~~~~~~~~~~" << std::endl;
							else std::cout << " ~~~~~~~~~~~ User failed to find a word ~~~~~~~~~~~~~" << std::endl;

							if (result.retry(guessedCorrectly, secretWord))
								resetGame(keyboard, grid, wordProcessorTest, gameRunning); //New word

							else {
								resetGame(keyboard, grid, wordProcessorTest, gameRunning);
								gameRunning = false;
								onMenu = true;
							} //Back to main menu
						}

						else {
							continueGame(currentWord, currentCol, currentRow); //Continue the game
						}
					}
					else {
						didShowWhenInvalid = true;
					}
				}
				if (backToMenuBtn.isClicked(event)) {
					audio.playSfx(clickSound);
					onMenu = true;
					resetGame(keyboard, grid, wordProcessorTest, gameRunning);
					std::cout << "Going back to main menu..." << std::endl;
				}

				//~~~ TEST ZONE ~~~
				if (giveUpBtn.isClicked(event)) {
					audio.playSfx(clickSound);
					std::cout << " ~~~~~~~~~~~ User failed to find a word ~~~~~~~~~~~~~" << std::endl;
					if (result.retry(false, secretWord))
						resetGame(keyboard, grid, wordProcessorTest, gameRunning); //New word

					else {
						resetGame(keyboard, grid, wordProcessorTest, gameRunning);
						gameRunning = false;
						onMenu = true;
					} //Back to main menu
				}
			}

			//scrolling background
			background.scroll(1);
			graphics.render(background);

			//Render UI
			graphics.renderTexture(gradient, 0, 0);
			graphics.renderTexture(guess_board, 0, 40);
			graphics.renderTexture(keyboard_layout, 0, MID_HEIGHT);
			keyboard.renderKeyboard(textColor);
			backToMenuBtn.renderButton();
			giveUpBtn.renderButton();

			//Render grid state
			grid.renderGridState(graphics);

			//Render the letters
			grid.render();

			//Render the pop up message
			if (showOnce) result.renderMessage("Guess your first word!", showOnce, POPUP_X, POPUP_Y);
			if(didShowWhenInvalid) result.renderMessage("Too short!", didShowWhenInvalid, POPUP_X + 75, POPUP_Y);

			//Show to the screen
			graphics.presentScene();
			SDL_Delay(16); // ~60FPS

		}
	}
	/////////////////////////// quit /////////////////////////////

	if (bgm != nullptr) Mix_FreeMusic(bgm);
	SDL_DestroyTexture( background.getTexture() );
	graphics.quit();
}

void Start::resetGame(Keyboard &keyboard, Grid& grid, WordProcessor &wordProcessor, bool &gameRunning) {
	keyboard.reset();
	grid.reset();
	wordProcessor.reset();
	gameRunning = false;
}

void Start::exitGame(bool &gameRunning, bool &keepRunning) {
	gameRunning = false;
	keepRunning = false;
}

void Start::continueGame(std::string& currentWord, int& currentCol, int& currentRow) {
	currentWord = "";
	currentCol = 0;
	currentRow++;
}

void Start::loadMenuTexture() {
	menuScreen = graphics.loadTexture(MAIN_MENU_SCREEN);
	menu_ExitButton = graphics.loadTexture(MENU_EXIT_BUTTON);
	menu_TutorialButton = graphics.loadTexture(MENU_TUTORIAL_BUTTON);
	menu_PlayButton = graphics.loadTexture(MENU_PLAY_BUTTON);
	menu_tutorialScreen = graphics.loadTexture(MENU_TUTORIAL_SCREEN);
	tutorial_okayButton = graphics.loadTexture(TUTORIAL_OKAY_BUTTON);
}

bool Start::isOnMainMenu() {
	Button exitBtn(&graphics, 314, 586, 395, 115, nullptr, menu_ExitButton);
	Button playBtn(&graphics, 314, 326, 395, 115, nullptr, menu_PlayButton);
	Button tutorialBtn(&graphics, 314, 456, 395, 115, nullptr, menu_TutorialButton);
	Button tutorialOkayBtn(&graphics, 379, 598, 272, 60, nullptr, tutorial_okayButton);

	bool isOnTutorialScreen = false;

	while(true) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) return false;

		graphics.renderTexture(menuScreen, 0, 0);

		if (!isOnTutorialScreen) {
			if (exitBtn.isClicked(event)) {
				audio.playSfx(clickSound);
				return false;
			}

			if (playBtn.isClicked(event)) {
				audio.playSfx(clickSound);
				return true;
			}

			if (tutorialBtn.isClicked(event)) {
				audio.playSfx(clickSound);
				isOnTutorialScreen = true;
			}

			exitBtn.renderButton();
			playBtn.renderButton();
			tutorialBtn.renderButton();
		}
		else {
			graphics.renderTexture(menu_tutorialScreen, 112, 84);
			tutorialOkayBtn.renderButton();

			if (tutorialOkayBtn.isClicked(event)) {
				audio.playSfx(clickSound);
				isOnTutorialScreen = false;
			}
		}

		graphics.presentScene();
		SDL_Delay(16);

	}
}

void Start::loadMainTexture() {
	backToMenuButton = graphics.loadTexture(BACK_BUTTON);
	backToMenuButton_hover = graphics.loadTexture(BACK_BUTTON_HOVER);

	giveUpButton = graphics.loadTexture(GIVEUP_BUTTON);
	giveUpButton_hover = graphics.loadTexture(GIVEUP_BUTTON_HOVER);

	clickSound = audio.loadSound(CLICK_BUTTON);
}