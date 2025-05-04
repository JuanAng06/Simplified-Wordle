#ifndef POPUP_HPP
#define POPUP_HPP

#include "../defs.hpp"
#include "../init/graphics.hpp"
#include "../init/music_and_background/audioManager.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Result{
    private:
        Graphics *popup;
        TTF_Font* result_font;
        TTF_Font* popup_font;
        SDL_Color color = {255,255,255,255}; //White
        SDL_Texture* renderSecretWord = nullptr;

        std::string lastSecretWord = "";

        SDL_Texture* result_win = nullptr;
        SDL_Texture* result_lose = nullptr;
        SDL_Texture* retry_button = nullptr;
        SDL_Texture* exit_button = nullptr;

        //Popup message
        SDL_Texture* popupBox = nullptr;

        //Using mouse event
        SDL_Event event;
        int mouseX, mouseY;

        //Render message
        SDL_Texture* renderMsg = nullptr;
        Uint32 startPopUpTime = SDL_GetTicks();
        Uint32 popUpDuration = 2000;
        bool isVisible = false;
        std::string lastMessage = "";

        //Audio
        Audio* sound;
        Mix_Chunk* clickButton = sound->loadSound(CLICK_BUTTON);

    public:
        Result();
        Result(Graphics* result);
        ~Result();

        //Show the result
        bool retry(bool didPlayerWin, std::string& secretWord);
        bool isRetryButton(int x, int y);
        bool isExitButton(int x, int y);
        void showSecretWord(std::string &secretWord);

        //Render message
        void renderMessage(const char* message, bool &showOnce, int x, int y);
};

#endif