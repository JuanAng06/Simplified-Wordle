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
	
	//Debug
	void logErrorAndExit(const char* msg, const char* error);

	//Initialize SDL
	SDL_Window* init();

	//Draw frame
	void prepareScene(SDL_Texture* texture);

	//Show frame
	void presentScene();

	//Taking out some materials
    SDL_Texture *loadTexture(const char* filename);

	//Ah ha! Here they are!
	void renderTexture(SDL_Texture *texture, int x, int y);

	//Quit
	void quit();

	//Blit image
	SDL_Texture *optimizeTexture(const char* filename);

	////////////////////////// BACKGROUND ////////////////////

	//render scrollingBackground
	void render(const ScrollingBackground& bgr);

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

		//Getter để lấy texture
		SDL_Texture* getTexture() const { return texture; }

		//Access to render (Graphics)
		friend void Graphics::render(const ScrollingBackground& bgr);
};

#endif