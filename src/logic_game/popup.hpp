#ifndef POPUP_HPP
#define POPUP_HPP

#include "../defs.hpp"
#include "../init/graphics.hpp"

#include <SDL2/SDL.h>
#include <string>

class PopUp{
    private:
        Graphics *popup;
        SDL_Texture* result_win = popup->loadTexture(WIN_SCREEN);
        SDL_Texture* result_lose = popup->loadTexture(LOSE_SCREEN);
        SDL_Texture* retry_button = popup->loadTexture(RETRY_BUTTON);
        SDL_Texture* exit_button = popup->loadTexture(EXIT_BUTTON);

        //Using mouse event
        SDL_Event event;
        int mouseX, mouseY;

    public:
        PopUp(Graphics* result);
        ~PopUp();
        bool retry(bool playerWon);
        bool isRetryButton(int x, int y);
        bool isExitButton(int x, int y);

        //~~~ TEST ZONE ~~~
        void showSecretWord(std::string &secretWord);
};

#endif