#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "../init/graphics.hpp"

class Keyboard{
	private:
		Graphics* keyboardS;
        TTF_Font* font;
		int startX, startY;
		int size;
		
		std::vector<std::string> keyboardRows = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};

		// !!! TEST ZONE !!!
		int keyChar [3][10];
		SDL_Texture* grayKey = keyboardS->loadTexture(KEY_GRAY_IMG);
		SDL_Texture* yellowKey = keyboardS->loadTexture(KEY_YELLOW_IMG);
		SDL_Texture* greenKey = keyboardS->loadTexture(KEY_GREEN_IMG);

		// ~~~~~~~~~~~~~~~~~~~~~
	public:
        Keyboard(Graphics* gfx, int startX_ = START_KEYBOARD_X, int startY_ = START_KEYBOARD_Y, int s = 0); // Constructor
		void renderKeyboard(SDL_Color textColor); //Render keyboard
		~Keyboard(); // Destructor

		// !!! TEST ZONE !!!: Update Keyboard State (2, 1, 0, -1)
		void updateKeyboardState(const std::vector<std::vector<int>>& keyState, int currentRow, const std::string& previousGuess);

		// ~~~~~~~~~~~~~~~~~~
};

#endif