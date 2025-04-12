#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "../../defs.hpp"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

class Audio{

    private:
    Mix_Music* bgm;
    Mix_Chunk* sfx;

    public:
    //Load music
	Mix_Music *loadMusic(const char* path);

	//Play BGM
	void play(Mix_Music *gMusic);

	//Load SFX
	Mix_Chunk* loadSound(const char* path);

	//Play SFX
	void playSfx(Mix_Chunk* gChunk);
};

#endif