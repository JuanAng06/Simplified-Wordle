#include "utils.hpp"

#include <iostream>

bool isValidChar (char c){
    return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

//Ask: Why error if not pass graphics and texture?
Button::Button(Graphics* g, int x, int y, int w, int h, SDL_Texture* normalTex, SDL_Texture* hoverTex)
: graphics(g), normalTex(normalTex), hoverTex(hoverTex) {
    rect = {x, y, w, h};
}

bool Button::isClicked(SDL_Event& event){
    if (!graphics) return false; //Safety first
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT){
        int mx = event.button.x;
        int my = event.button.y;
        SDL_Point pos = {mx, my};
        return SDL_PointInRect(&pos, &rect);
    }
    return false;
}

bool Button::isHovered(){
    if (!graphics) return false; //Safety first
    int mx, my;
    SDL_GetMouseState(&mx, &my);
    SDL_Point pos = {mx , my};
    return SDL_PointInRect(&pos, &rect);
}

void Button::renderButton(){
    if (!graphics) return; //Safety first

    SDL_Texture* toRender = normalTex;
    if (hoverTex && isHovered()){
        toRender = hoverTex;
    }

    if (toRender){
        graphics->renderTexture(toRender, rect.x, rect.y);
    }
}

//Destructor
// Button::~Button(){
//     if (normalTex) SDL_DestroyTexture(normalTex) ;
//     if (hoverTex) SDL_DestroyTexture(hoverTex);
//     hoverTex = normalTex = nullptr;
//     if (normalTex || hoverTex) std::cout << "[DEBUG] Failed to destroy Button!" << std::endl;
//     else std::cout << "[DEBUG] Destroyed Button successfully!" << std::endl;
// }