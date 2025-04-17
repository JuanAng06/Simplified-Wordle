#include "popup.hpp"

//Constructor
PopUp::PopUp(Graphics* result): popup(result) {}

//Destructor
PopUp::~PopUp() {
	if (result_win) SDL_DestroyTexture(result_win);
	if (result_lose) SDL_DestroyTexture(result_lose);
	if (retry_button) SDL_DestroyTexture(retry_button);
	if (exit_button) SDL_DestroyTexture(exit_button);
}

//Is it a retry button?
bool PopUp::isRetryButton(int x, int y) {
	return (RETRY_X_START <= x && x <= RETRY_X_END && RETRY_Y_START <= y && y <= RETRY_Y_END);
}

//Is it an exit button?
bool PopUp::isExitButton(int x, int y) {
	return (EXIT_X_START <= x && x <= EXIT_X_END && EXIT_Y_START <= y && y <= EXIT_Y_END);
}

//Show result screen
bool PopUp::retry(bool playerWon) {
	while (true) {
		if (playerWon) popup->renderTexture(result_win, 0, 0);
		else popup->renderTexture(result_lose, 0, 0);

		SDL_PollEvent(&event);

		SDL_GetMouseState(&mouseX, &mouseY);

		if (event.type == SDL_QUIT) {
			return true;
		}

		//Exit button
		if (isExitButton(mouseX,mouseY)) {
			popup->renderTexture(exit_button, EXIT_X_START, EXIT_Y_START);
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) return false; //Quit the game
		}

		//Retry button
		if (isRetryButton(mouseX,mouseY)) {
			popup->renderTexture(retry_button, RETRY_X_START, RETRY_Y_START);
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) return true; //New game
		}

		popup->presentScene();

	}
}