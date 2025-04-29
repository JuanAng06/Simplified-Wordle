#include "grid.hpp"

#include <iostream>

//Constructor
Grid::Grid(Graphics* gridChar ,TTF_Font* font) : gridFont(font), gridChar(gridChar){
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            grid[i][j] = ' '; //empty cell
        }
    }
}

//Initialize the grid + character + Render word
void Grid::render(){
    SDL_Color textColor = {255, 255, 255, 255};
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            if (grid[i][j] != ' '){

                //Get the letter
                std::string renderLetter(1, grid[i][j]);

                //Render the letter on grid [i][j]
                SDL_Texture* letter = gridChar->renderText(renderLetter.c_str(), gridFont, textColor);
                gridChar->renderTexture(letter, FIRST_CELL_X + j * (GRID_PADDING - 1), FIRST_CELL_Y + i * (GRID_PADDING - 1));
                SDL_DestroyTexture(letter);
            }
        }
    }
}

//Save the letter to grid[ROWS][COLS] (See grid.hpp)
void Grid::setLetter(int row, int col, char letter){
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS){
        letter = toupper(letter);
        grid[row][col] = letter;
    }
}

// Update the cells
void Grid::renderGridState(Graphics& graphics){
    for (int row = 0; row < gridState.size(); row++){
        for (int col = 0; col < gridState[row].size(); col++){
            int state = gridState[row][col];

            SDL_Texture* texture = nullptr;

            switch (state){
                case 0: //Wrong letter
                    texture = gray_cell;
                    break;

                case 1: //Misplaced letter
                    texture = yellow_cell;
                    break;

                case 2: //Correct letter
                    texture = green_cell;
                    break;
            }

            if (texture){
                graphics.renderTexture(texture, FIRST_CHECK_CELL_X + col * CHECK_CELL_PADDING, FIRST_CHECK_CELL_Y + row * CHECK_CELL_PADDING);
            }
        }
    }
}

void Grid::reset(){

    //Reset character grid
    for (size_t i = 0; i < ROWS; i++){
        for (size_t j = 0; j < COLS; j++){
            grid[i][j] = ' ';
        }
    }

    //Reset some states
    curentRow = 0; currentCol = 0; currentWord = "";

    //Reset gridState
    gridState.assign(ROWS, std::vector<int>(COLS, -1));
}

//Destructor - TEST ZONE
Grid::~Grid(){
    if (gray_cell) SDL_DestroyTexture(gray_cell);
    if (yellow_cell) SDL_DestroyTexture(yellow_cell);
    if (green_cell) SDL_DestroyTexture(green_cell);

    gray_cell = yellow_cell = green_cell = nullptr;
    if (gray_cell || yellow_cell || green_cell) std::cout << "[DEBUG] Failed to destroy Grid" << std::endl;
    else std::cout << "[DEBUG] Destroyted Grid successfully!" << std::endl;
}