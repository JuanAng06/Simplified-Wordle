#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include "graphics.hpp"

//////////////////////////////////////// Handle bug ////////////////////////////////////////
void Graphics::logErrorAndExit(const char* msg, const char* error)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
	SDL_Quit();
}

/////////////////////////////////////// Init SDL + Window ////////////////////////////////////////
SDL_Window* Graphics::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		logErrorAndExit("SDL_Init could not initialize! Error: %s", SDL_GetError());

	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) == -1)
		SDL_Log("SDL_mixer could not initialize! Error: %s", Mix_GetError());
	
	if (TTF_Init() == -1) {
		std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}
	
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	//full screen
	//window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

	if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
		logErrorAndExit( "SDL_image error: ", IMG_GetError());

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//renderer = SDL_CreateSodtwareRenderer(SDL_GetWindowSurface(window));

	if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

/////////////////////////////////////// Prepare + Display ///////////////////////////////////////
//Render
void Graphics::prepareScene(SDL_Texture* background)
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, background, NULL, NULL);
}

//Display
void Graphics::presentScene()
{
	SDL_RenderPresent(renderer);
}

/////////////////////////////////////// Load texture ///////////////////////////////////////
SDL_Texture* Graphics::loadTexture(const char* filename)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL) {
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
	}

	return texture;
}

////////////////////////////////////// Render at (x,y) ////////////////////////////////////////
void Graphics::renderTexture(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}


/////////////////////////////////////// Quit SDL + Destroy window ///////////////////////////////////////
void Graphics::quit()
{
	IMG_Quit();
	Mix_Quit();
	TTF_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Quit SDL successfully" << std::endl;
}

/////////////////////////////////////// SCROLLING BACKGROUND /////////////////////////////
void ScrollingBackground::setTexture(SDL_Texture* _texture){
	texture = _texture;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void ScrollingBackground::scroll(int distance){
	scrollingOffset -= distance;
	if ( scrollingOffset < 0 ){
		scrollingOffset = width;
	}
}

void Graphics::render(const ScrollingBackground& bgr){
	renderTexture(bgr.texture, bgr.scrollingOffset, 0); 
    renderTexture(bgr.texture, bgr.scrollingOffset - bgr.width, 0); 
}

//////////////////////////////// TEXT RENDER //////////////////////////

//Load font
TTF_Font* Graphics::loadFont (const char* path, int size){
	TTF_Font* gFont = TTF_OpenFont ( path, size );
	if (gFont == nullptr){
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
					   "Load font %s", TTF_GetError());
	}
	return gFont;
}

//Render text
SDL_Texture* Graphics::renderText(const char* text, TTF_Font* font, SDL_Color textColor){
	SDL_Surface* textSurface = TTF_RenderText_Solid ( font, text, textColor );
	if ( textSurface == nullptr){
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
					   "Create texture from surface %s", SDL_GetError());
					   return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
	if ( texture == nullptr ){
			SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
						   "Create texture from text %s", SDL_GetError());
	}
	SDL_FreeSurface( textSurface );
	return texture;
}

////////////////// DESTROY TEXTURES /////////////////////////////
void Graphics::destroyTexture(const char* path, SDL_Texture *& texture){
	if (texture != nullptr){
		SDL_DestroyTexture(texture);
		texture = nullptr;
		SDL_Log("Successfully destroyed texture: %s", path);
	} else {
		SDL_Log("Texture %s is nullptr already!", path);
	}
}