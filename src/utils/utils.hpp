#ifndef UTILS_HPP
#define UTILS_HPP

#include "../defs.hpp"
#include <string>

#include <SDL2/SDL.h>
#include "../init/graphics.hpp"

bool isValidChar (char letter);

class Button{
    private:
        SDL_Rect rect;
        SDL_Texture* normalTex = nullptr;
        SDL_Texture* hoverTex = nullptr;
        Graphics* graphics = nullptr;
        int mouseX, mouseY;
    public:
        Button(); //Default
        Button(Graphics* g, int x, int y, int w, int h, SDL_Texture* normalTex = nullptr, SDL_Texture* hoverTex = nullptr);
        // ~Button();

        bool isClicked(SDL_Event& event);
        bool isHovered();
        void renderButton();
        
};

#endif