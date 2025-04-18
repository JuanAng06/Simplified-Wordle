#ifndef POPUP_HPP
#define POPUP_HPP

#include "../defs.hpp"
#include "../init/graphics.hpp"

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

        SDL_Texture* result_win = popup->loadTexture(WIN_SCREEN);
        SDL_Texture* result_lose = popup->loadTexture(LOSE_SCREEN);
        SDL_Texture* retry_button = popup->loadTexture(RETRY_BUTTON);
        SDL_Texture* exit_button = popup->loadTexture(EXIT_BUTTON);

        //Using mouse event
        SDL_Event event;
        int mouseX, mouseY;

        //Render message ~~~ TEST ZONE ~~~
        SDL_Texture* renderMsg;
        Uint32 startPopUpTime = SDL_GetTicks(); //TEST
        Uint32 popUpDuration = 2000;
        bool isVisible = false;
        std::string lastMessage = "";

    public:
        Result(Graphics* result);
        ~Result();

        //Show the result
        bool retry(bool didPlayerWin, std::string& secretWord);
        bool isRetryButton(int x, int y);
        bool isExitButton(int x, int y);
        void showSecretWord(std::string &secretWord);

        //~~~ TEST ZONE ~~~
        void renderMessage(const char* message, bool &showOnce, int x, int y);
};

#endif