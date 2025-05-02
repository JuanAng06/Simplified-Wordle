#include "popup.hpp"

#include <iostream>

//Default
Result::Result(){}

//Constructor
Result::Result(Graphics* result): popup(result), result_font(result_font), popup_font(popup_font) {
	result_font = popup->loadFont(KEYBOARD_FONT, REVEAL_SECRETWORD_TEXTSIZE);
	popup_font = popup->loadFont(KEYBOARD_FONT, POPUP_TEXTSIZE);
	if (!result_font) std::cerr << "Result font not loaded! " << TTF_GetError << std::endl;
	if (!popup_font) std::cerr << "Popup font not loaded! " << TTF_GetError << std::endl;
}

//Destructor
Result::~Result() {

	popup->destroyTexture(WIN_SCREEN, result_win);
	popup->destroyTexture(LOSE_SCREEN, result_lose);
	popup->destroyTexture(RETRY_BUTTON, retry_button);
	popup->destroyTexture(EXIT_BUTTON, exit_button);

	if (renderSecretWord) SDL_DestroyTexture(renderSecretWord);
	renderSecretWord = nullptr;

	if (result_win || result_lose || retry_button || exit_button || renderSecretWord)
		std::cout << "[DEBUG] Failed to destroy Result." << std::endl;
	else std::cout << "[DEBUG] Destroyed Result successfully!" << std::endl;
}

//Is it a retry button?
bool Result::isRetryButton(int x, int y) {
	return (RETRY_X_START <= x && x <= RETRY_X_END && RETRY_Y_START <= y && y <= RETRY_Y_END);
}

//Is it an exit button?
bool Result::isExitButton(int x, int y) {
	return (EXIT_X_START <= x && x <= EXIT_X_END && EXIT_Y_START <= y && y <= EXIT_Y_END);
}

//Show result screen
bool Result::retry(bool didPlayerWin, std::string& secretWord) {
	while (true) {
		if (didPlayerWin) popup->renderTexture(result_win, 0, 0);
		else popup->renderTexture(result_lose, 0, 0);

		showSecretWord(secretWord);

		SDL_PollEvent(&event);

		SDL_GetMouseState(&mouseX, &mouseY);

		if (event.type == SDL_QUIT) {
			return false;
		}

		//Exit button
		if (isExitButton(mouseX,mouseY)) {
			popup->renderTexture(exit_button, EXIT_X_START, EXIT_Y_START);
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
				sound->playSfx(clickButton);
				return false; //Quit the game
			}
		}

		//Retry button
		if (isRetryButton(mouseX,mouseY)) {
			popup->renderTexture(retry_button, RETRY_X_START, RETRY_Y_START);
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
				sound->playSfx(clickButton);
				return true; //New game
			}
		}

		popup->presentScene();

	}
}

//Reveal the secret word
void Result::showSecretWord(std::string &secretWord){

	if (lastSecretWord != secretWord){
		lastSecretWord == secretWord;
		std::string upperWord = secretWord;
		for (char &c : upperWord){
			c = toupper(c);
		}

		if (renderSecretWord){
			SDL_DestroyTexture(renderSecretWord);
		}

		const char* text = upperWord.c_str();
		renderSecretWord = popup->renderText(text, result_font, color);
	}
	
	popup->renderTexture(renderSecretWord, REVEAL_SECRETWORD_X, REVEAL_SECRETWORD_Y);
}

//Render the message (i.e: "Guess your first word!") ~~~ TEST ZONE ~~~
void Result::renderMessage(const char* message, bool &showOnce, int x, int y){
	Uint32 currentTime = SDL_GetTicks();

	std::string currentText = std::string(message);

	if (!isVisible || currentText != lastMessage) {
		startPopUpTime = currentTime;
		isVisible = true;
		lastMessage = currentText;
	}

	if (currentTime - startPopUpTime > popUpDuration){
		isVisible = false;
		showOnce = false;
		return;
	}

	renderMsg = popup->renderText(message, popup_font, color);

	popup->renderTexture(popupBox, POPUP_CENTER_X, POPUP_CENTER_Y);
	popup->renderTexture(renderMsg, x, y);

	SDL_DestroyTexture(renderMsg);

}