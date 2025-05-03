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
		int startX = START_KEYBOARD_X, startY = START_KEYBOARD_Y;
		int size;
		
		std::vector<std::string> keyboardRows = {"QWERTYUIOP", "ASDFGHJKL", "ZXCVBNM"};

		//Load keyboard
		int keyChar [3][10];
		SDL_Texture* grayKey = keyboardS->loadTexture(KEY_GRAY_IMG);
		SDL_Texture* yellowKey = keyboardS->loadTexture(KEY_YELLOW_IMG);
		SDL_Texture* greenKey = keyboardS->loadTexture(KEY_GREEN_IMG);
		SDL_Texture* keyLayout = keyboardS->loadTexture(KEY_LETTER_LAYOUT);

	public:
		Keyboard();
        Keyboard(Graphics* gfx); // Constructor
		void renderKeyboard(SDL_Color textColor);
		~Keyboard(); // Destructor

		void updateKeyboardState(const std::vector<std::vector<int>>& keyState, int currentRow, const std::string& previousGuess);
		
		void reset();
};

#endif