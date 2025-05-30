#ifndef GRID_HPP
#define GRID_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>

#include "../init/graphics.hpp"

#include "../defs.hpp"

class Grid{
    private:
        char grid[ROWS][COLS];
        int curentRow = 0, currentCol = 0;
        std::string currentWord = "";
        TTF_Font* gridFont;
        Graphics* gridChar;

        //Grid state
        std::vector<std::vector<int>> gridState;

        // Render cell color
        SDL_Texture* gray_cell = nullptr;
        SDL_Texture* yellow_cell = nullptr;
        SDL_Texture* green_cell = nullptr;

    public:
        Grid(); //Default constructor
        Grid(Graphics* gridChar, TTF_Font* font);
        void render();
        void setLetter(int row, int col, char letter);

        void updateGridState(const std::vector<std::vector<int>>& newState){
            gridState = newState;
        }
        void renderGridState(Graphics& graphics);

        void reset();

        ~Grid(); //Destructor

};

#endif