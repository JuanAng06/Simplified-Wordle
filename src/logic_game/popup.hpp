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
        SDL_Texture* renderSecretWord;

        std::string lastSecretWord = "";

        SDL_Texture* result_win = popup->loadTexture(WIN_SCREEN);
        SDL_Texture* result_lose = popup->loadTexture(LOSE_SCREEN);
        SDL_Texture* retry_button = popup->loadTexture(RETRY_BUTTON);
        SDL_Texture* exit_button = popup->loadTexture(EXIT_BUTTON);

        //Popup message
        SDL_Texture* popupBox = popup->loadTexture(POP_UP_ANNOUCNER);

        //Using mouse event
        SDL_Event event;
        int mouseX, mouseY;

        //Render message
        SDL_Texture* renderMsg;
        Uint32 startPopUpTime = SDL_GetTicks();
        Uint32 popUpDuration = 2000;
        bool isVisible = false;
        std::string lastMessage = "";

        //Audio
        Audio* sound;
        Mix_Chunk* clickButton = sound->loadSound(CLICK_BUTTON);

    public:
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