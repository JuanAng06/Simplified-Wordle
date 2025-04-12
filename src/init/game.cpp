//UPDATED: Checked word - ON THE GRID

/*TO DO:
		Update the keyboard each time a word is submitted
		End when the word is found (game over)
		Retry button
		Difficulty?
*/

#include "game.hpp"
#include "graphics.hpp"
#include "music_and_background/audioManager.hpp"
#include "../keyboard/keyboard.hpp"
#include "../logic_game/handleInput.hpp"
#include "../logic_game/grid.hpp"
#include "../logic_game/wordProcessor.hpp"

#include <iostream>

void Start::play() {

	//!!! TEST ZONE !!!
	WordProcessor wordProcessorTest;

    wordProcessorTest.loadDictionary(DICTIONARY);
    wordProcessorTest.setSecretWord();

    std::cout << "Secret Word: " << wordProcessorTest.getSecretWord() << std::endl;

	//////////////////////// Initialization ///////////////////////

	//class Graphics
	Graphics graphics;
	graphics.init();
	
	//class Audio
	Audio bgMusic;

	//class Keyboard
	Keyboard keyboard(&graphics);
	SDL_Color textColor = {255, 255, 255, 255};

	///////////////////////// UI ///////////////////////////////////

	//Load scrolling background
	ScrollingBackground background;
	background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

    //Background music
    Mix_Music *bgm = bgMusic.loadMusic(BGM);
    bgMusic.play(bgm);

	//main UI
	SDL_Texture* guess_board = graphics.loadTexture(GUESS_GRID_IMG);
	SDL_Texture* gradient = graphics.loadTexture(GRADIENT_IMG);
	SDL_Texture* keyboard_layout = graphics.loadTexture(KEYBOARD_IMG);

	//Handle key drawing
	SDL_Texture* keyGreen = graphics.loadTexture(KEY_GREEN_IMG);
	SDL_Texture* keyYellow = graphics.loadTexture(KEY_YELLOW_IMG);
	SDL_Texture* keyGray = graphics.loadTexture(KEY_GRAY_IMG);

	//Input handler
	HandleInput inputHandler;

	//Grid initialization
	TTF_Font* gridFont = graphics.loadFont(KEYBOARD_FONT, 30);
	Grid grid(&graphics, gridFont);
	std::string currentWord = "";
	int currentCol = 0;
	int currentRow = 0;

	///////////////////////// Game loop ////////////////////////////
	bool gameRunning = true;

	SDL_Event event;

	//Game loop
	while (gameRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameRunning = false;
			}

			inputHandler.handleEvent(event, currentWord, currentCol, COLS, grid, currentRow);

			//Process the check prucedure
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && currentWord.length() == 5 && currentRow < ROWS){

				//debug
				std::cout << std::string(20, '~') << std::endl;
				std::cout << "ENTER was pressed" << std:: endl;

				//Update the guess stat (Use previousGuess to check)
				wordProcessorTest.updatePreviousGuess(inputHandler);

				//Check and update grid stat
				wordProcessorTest.checkGuess(currentWord, currentRow);
				const std::vector<std::vector<int>>& gridState = wordProcessorTest.getGridState();
				keyboard.updateKeyboardState(gridState, currentRow, wordProcessorTest.getPreviousGuess()); //TEST

				//debug
				std::cout << "Grid size: " << gridState.size() << std::endl;
				grid.updateGridState(gridState);

				std::cout << "Current row: " << currentRow + 1 << std::endl;

				std::cout << std::endl << "Previous grid state: " << std::endl;
				for (int i : gridState[currentRow]){
					std::cout << i << " ";
				}
				std::cout << std::endl;
				
				//end of debug

				//Check if the game over?
				bool guessedCorrectly = true;
				for (int status : gridState[currentRow]){
					if (status != 2){
						guessedCorrectly = false;
						break;
					}
				}

				if (guessedCorrectly){
					std::cout << " ~~~~~~~~~~~~ User found the word ~~~~~~~~~~~~~" << std::endl;
					gameRunning = false;
				}

				else if (currentRow == ROWS){
					std::cout << " ~~~~~~~~~~~ User failed to find a word ~~~~~~~~~~~~~" << std::endl;
					gameRunning = false;
				}

				else {
				//Continue the game
				currentWord = "";
				currentCol = 0;
				currentRow++;
			}
			}
		}

		//scrolling background
		background.scroll(1);
		graphics.render(background);

		//load UI
		graphics.renderTexture(gradient, 0, 0);
		graphics.renderTexture(guess_board, 0, 40);
		graphics.renderTexture(keyboard_layout, 0, MID_HEIGHT);
		keyboard.renderKeyboard(textColor);
		
		//Print grid state
		grid.renderGridState(graphics);

		//Render the letters
		grid.render();

		//Show to the screen
		graphics.presentScene();
        SDL_Delay(16);

	}
	/////////////////////////// quit /////////////////////////////

    if (bgm != nullptr) Mix_FreeMusic(bgm);
	SDL_DestroyTexture( background.getTexture() );
	graphics.quit();
}