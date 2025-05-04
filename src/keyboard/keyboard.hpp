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
		SDL_Texture* grayKey = nullptr;
		SDL_Texture* yellowKey = nullptr;
		SDL_Texture* greenKey = nullptr;
		SDL_Texture* keyLayout = nullptr;

	public:
		Keyboard(); //Default constructor
        Keyboard(Graphics* gfx); // Constructor
		void renderKeyboard(SDL_Color textColor);
		~Keyboard(); // Destructor

		void updateKeyboardState(const std::vector<std::vector<int>>& keyState, int currentRow, const std::string& previousGuess);
		
		void reset();
};

#endif