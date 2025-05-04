#include "audioManager.hpp"

//Load music (BGM)
Mix_Music* Audio::loadMusic(const char* path){
	Mix_Music *gMusic = Mix_LoadMUS(path);
	if (gMusic == nullptr){
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
					   "Could not load music! SDL_mixer Error: %s", Mix_GetError());
	}
	return gMusic;
}

//Play music (BGM)
void Audio::play(Mix_Music *gMusic){
	if (gMusic == nullptr) return;

	if (Mix_PlayingMusic() == 0){
		Mix_PlayMusic(gMusic, -1);
	}
	else if (Mix_PausedMusic() == 1){
		Mix_ResumeMusic();
	}
}

//Load sound effect
Mix_Chunk* Audio::loadSound(const char* path){
	Mix_Chunk* gChunk = Mix_LoadWAV(path);
	if (gChunk == nullptr){
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
					   SDL_LOG_PRIORITY_ERROR,
					   "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
	}
}

//Play SFX
void Audio::playSfx(Mix_Chunk* gChunk){
	if (gChunk != nullptr){
		Mix_PlayChannel(-1, gChunk, 0);
	}
}

//Free sound
void Audio::quitSound(const char *path, Mix_Chunk *& gChunk){
	if (gChunk != nullptr){
		Mix_FreeChunk(gChunk);
		gChunk = nullptr;
		SDL_Log("[DEBUG] Unloaded successfully: %s", path);
	} else {
		SDL_Log("[DEBUG] %s is nullptr already!", path);
	}
}