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
	Mix_Music *loadMusic(const char* path); //Load music
	void play(Mix_Music *gMusic); //Play BGM
	Mix_Chunk* loadSound(const char* path); //Load SFX
	void playSfx(Mix_Chunk* gChunk); //Play SFX
	
	void quitSound(const char *path, Mix_Chunk *& gChunk); //Quit sound
};

#endif