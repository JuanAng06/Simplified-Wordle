#include "game.hpp"
#include "graphics.hpp"
#include "music_and_background/audioManager.hpp"
#include "../keyboard/keyboard.hpp"
#include "../logic_game/handleInput.hpp"
#include "../logic_game/grid.hpp"
#include "../logic_game/wordProcessor.hpp"
#include "../logic_game/popup.hpp"

#include <iostream>

void Start::initGameObjects()
{
	// Init graphics
	graphics.init();
	loadMenuTexture();
	loadMainTexture();

	// Pointer init
	keyboard = new Keyboard(&graphics);

	// background music
	bgm = audio.loadMusic(BGM);
	audio.play(bgm);

	// Grid intialization
	gridFont = graphics.loadFont(KEYBOARD_FONT, 30);
	grid = new Grid(&graphics, gridFont);

	// Popup init
	result = new Result(&graphics);

	// Input init
	inputHandler = new HandleInput(&audio);

	// Scrolling background
	background.setTexture(graphics.loadTexture(BACKGROUND_IMG));

	// Button intialization
	backToMenuBtn = Button(&graphics, 30, 30, 60, 60, backToMenuButton, backToMenuButton_hover);
	giveUpBtn = Button(&graphics, SCREEN_WIDTH - 180, 30, 150, 60, giveUpButton, giveUpButton_hover);
}

///// RUN GAME LOOP ////
void Start::runGameLoop()
{
	while (gameRunning)
	{
		if (onMenu && !gonnaPlay())
			exitGame();
		else
			onMenu = false;

		// Process guess procedure
		processGuess();

		// Render frame
		renderFrame();
	}
}

////// Play the game //////
void Start::play()
{
	wordProcessorTest.loadDictionary(DICTIONARY);

	initGameObjects();

	// Game loop
	while (keepRunning)
	{
		// Set a secret word
		wordProcessorTest.setSecretWord();
		secretWord = wordProcessorTest.getSecretWord();
		std::cout << "Secret Word: " << secretWord << std::endl;

		// Reset round
		newGame();
		runGameLoop();
	}

	cleanUp();
}

////// Process the guess ////// <- MAIN LOGIC HERE !!!!
void Start::processGuess()
{
	guessedCorrectly = false;
	gameOver = false;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exitGame();

		// Handle input
		inputHandler->handleEvent(event, currentWord, currentCol, currentRow, COLS, grid);

		// Process the check prucedure
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN && currentRow < ROWS)
		{
			if (currentWord.length() == 5)
			{

				// Update the guess stat (Use previousGuess to check)
				wordProcessorTest.updatePreviousGuess(inputHandler);

				// Check and update grid state
				wordProcessorTest.checkGuess(currentWord, currentRow);
				const auto &gridState = wordProcessorTest.getGridState();
				keyboard->updateKeyboardState(gridState, currentRow, wordProcessorTest.getPreviousGuess());
				grid->updateGridState(gridState);

				// Check if the game is over
				guessedCorrectly = correctGuess(gridState[currentRow]);
				if (guessedCorrectly || currentRow == ROWS - 1)
					gameOver = true;

				continueGame(); // Continue the game
			}
			else
				didShowWhenInvalid = true; // If the word is not long enough
		}
		// If player click the "Back" button
		if (backToMenuBtn.isClicked(event))
		{
			audio.playSfx(clickSound);
			onMenu = true;
			resetGame();
			std::cout << "Going back to main menu..." << std::endl;
		}

		if (giveUpBtn.isClicked(event) || gameOver) // If player give up
		{
			if (giveUpBtn.isClicked(event))
				audio.playSfx(clickSound);
			processResult();
		}
	}
}

void Start::resetGame()
{
	keyboard->reset();
	grid->reset();
	wordProcessorTest.reset();
	gameRunning = false;
}

void Start::exitGame()
{
	gameRunning = false;
	keepRunning = false;
}

void Start::continueGame()
{
	currentWord = "";
	currentCol = 0;
	currentRow++;
}

void Start::loadMenuTexture()
{
	menuScreen = graphics.loadTexture(MAIN_MENU_SCREEN);
	menu_ExitButton = graphics.loadTexture(MENU_EXIT_BUTTON);
	menu_TutorialButton = graphics.loadTexture(MENU_TUTORIAL_BUTTON);
	menu_PlayButton = graphics.loadTexture(MENU_PLAY_BUTTON);
	menu_tutorialScreen = graphics.loadTexture(MENU_TUTORIAL_SCREEN);
	tutorial_okayButton = graphics.loadTexture(TUTORIAL_OKAY_BUTTON);
}

bool Start::gonnaPlay()
{
	Button exitBtn(&graphics, 314, 586, 395, 115, nullptr, menu_ExitButton);
	Button playBtn(&graphics, 314, 326, 395, 115, nullptr, menu_PlayButton);
	Button tutorialBtn(&graphics, 314, 456, 395, 115, nullptr, menu_TutorialButton);
	Button tutorialOkayBtn(&graphics, 379, 598, 272, 60, nullptr, tutorial_okayButton);

	bool isOnTutorialScreen = false;

	while (true)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			return false;

		graphics.renderTexture(menuScreen, 0, 0);

		bool exitClick = exitBtn.isClicked(event);
		bool playClick = playBtn.isClicked(event);
		bool tutClick = tutorialBtn.isClicked(event);
		bool okClick = tutorialOkayBtn.isClicked(event);

		if (((exitClick || playClick || tutClick) && !isOnTutorialScreen) || (okClick && isOnTutorialScreen))
			audio.playSfx(clickSound);

		if (!isOnTutorialScreen)
		{

			if (exitClick)
				return false; // Quit the gane
			if (playClick)
				return true; // Play the game
			if (tutClick)
				isOnTutorialScreen = true; //Show the tutorial screen

			exitBtn.renderButton();
			playBtn.renderButton();
			tutorialBtn.renderButton();
		}
		else
		{ // Show tutorial
			graphics.renderTexture(menu_tutorialScreen, 112, 84);
			tutorialOkayBtn.renderButton();

			if (okClick)
				isOnTutorialScreen = false;
		}

		graphics.presentScene();
		SDL_Delay(16);
	}
}

void Start::loadMainTexture()
{
	backToMenuButton = graphics.loadTexture(BACK_BUTTON);
	backToMenuButton_hover = graphics.loadTexture(BACK_BUTTON_HOVER);
	giveUpButton = graphics.loadTexture(GIVEUP_BUTTON);
	giveUpButton_hover = graphics.loadTexture(GIVEUP_BUTTON_HOVER);
	clickSound = audio.loadSound(CLICK_BUTTON);
	guess_board = graphics.loadTexture(GUESS_GRID_IMG);
	gradient = graphics.loadTexture(GRADIENT_IMG);
	keyboard_layout = graphics.loadTexture(KEYBOARD_IMG);
}

void Start::renderFrame()
{

	// scrolling background
	background.scroll(1);
	graphics.render(background);

	// Render UI
	graphics.renderTexture(gradient, 0, 0);
	graphics.renderTexture(guess_board, 0, 40);
	graphics.renderTexture(keyboard_layout, 0, MID_HEIGHT);
	keyboard->renderKeyboard(textColor);
	backToMenuBtn.renderButton();
	giveUpBtn.renderButton();

	// Render grid state
	grid->renderGridState(graphics);

	// Render the letters
	grid->render();

	// Render the pop up message
	if (showOnce)
		result->renderMessage("Guess your first word!", showOnce, POPUP_X, POPUP_Y);
	if (didShowWhenInvalid)
		result->renderMessage("Too short!", didShowWhenInvalid, POPUP_X + 75, POPUP_Y);

	// Show to the screen
	graphics.presentScene();
	SDL_Delay(16); // ~60FPS
}

bool Start::correctGuess(const std::vector<int> &currentState)
{
	for (int status : currentState)
	{
		if (status != 2)
			return false;
	}
	return true;
}

void Start::newGame()
{
	currentWord.clear();
	currentCol = 0;
	currentRow = 0;

	gameRunning = true;
	showOnce = true;
	didShowWhenInvalid = false;
}

void Start::cleanUp()
{
	if (bgm != nullptr)
		Mix_FreeMusic(bgm);
	SDL_DestroyTexture(background.getTexture());
	delete keyboard;
	keyboard = nullptr;
	delete grid;
	grid = nullptr;
	delete result;
	result = nullptr;
	delete inputHandler;
	inputHandler = nullptr;
	graphics.quit();
}

void Start::processResult()
{
	// Debug
	if (guessedCorrectly)
		std::cout << " ~~~~~~~~~~~~ User found the word ~~~~~~~~~~~~~" << std::endl;
	else
		std::cout << " ~~~~~~~~~~~ User failed to find a word ~~~~~~~~~~~~~" << std::endl;

	if (result->retry(guessedCorrectly, secretWord))
		resetGame(); // New word

	else
	{ // Back to main menu
		resetGame();
		gameRunning = false;
		onMenu = true;
	}
}