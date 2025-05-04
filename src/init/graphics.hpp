#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

#include "../defs.hpp"

class ScrollingBackground;

class Graphics {
	private:
	SDL_Renderer *renderer;
	SDL_Window *window;

	//text
	const char* path;
	int size;

	public:

	void logErrorAndExit(const char* msg, const char* error); //Debug
	SDL_Window* init(); //Initialize SDL
	void prepareScene(SDL_Texture* texture); //Draw frame
	void presentScene(); //Show frame
    SDL_Texture *loadTexture(const char* filename); //Load texture
	void renderTexture(SDL_Texture *texture, int x, int y); //Render texture at (x,y)
	void quit(); //Quit SDL + Destroy window

	void render(const ScrollingBackground& bgr); //render scrollingBackground

	////////////////////////// TEXT ////////////////////////
	TTF_Font* loadFont (const char* path, int size);
	SDL_Texture* renderText (const char* text, TTF_Font* font, SDL_Color textColor);

	//////////////// DESTROY ////////////////////
	void destroyTexture(const char* path, SDL_Texture *& texture);

};

class ScrollingBackground {
	private:
		SDL_Texture* texture;
		int scrollingOffset = 0;
		int width, height;
	
	public:
		void setTexture(SDL_Texture* _texture);
		void scroll(int distance);

		//Getter
		SDL_Texture* getTexture() const { return texture; }

		//Access to render (Graphics)
		friend void Graphics::render(const ScrollingBackground& bgr);
};

#endif