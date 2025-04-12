#ifndef _RESIZE__H
#define _RESIZE__H

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int MID_WIDTH = SCREEN_WIDTH / 2;
const int MID_HEIGHT = SCREEN_HEIGHT / 2;
const int MID_BOTTOM = SCREEN_HEIGHT - SCREEN_HEIGHT / 2;

const int WORD_LENGTH = 5;

//UI thingy
#define WINDOW_TITLE "Simplified Wordle"
#define BACKGROUND_IMG "assets//background//background_2.jpg"
#define BGM "assets//music//background_music.MP3"
#define GUESS_GRID_IMG "assets//ui//guess_grid.png"
#define GRADIENT_IMG "assets//ui//gradient.png"
#define KEYBOARD_IMG "assets//ui//keyboard_layout.png"

#define KEY_GREEN_IMG "assets//ui//KeyColor//key_green.png"
#define KEY_YELLOW_IMG "assets//ui//KeyColor//key_yellow.png"
#define KEY_GRAY_IMG "assets//ui//KeyColor//key_gray.png"

#define WORD_LIST_TXT "wordlist.txt"

//keyboard render
#define KEYBOARD_FONT "assets//font//Gilroy-ExtraBold.ttf"
const int START_KEYBOARD_X = 201;
const int START_KEYBOARD_Y = MID_WIDTH - 24;
const int KEYBOARD_TEXT_SIZE = 32;
const int ROW_SPACING = 67;
const int PADDING = 66;

//Grid manager
static const int ROWS = 6;
static const int COLS = 5;

const int FIRST_CELL_X = MID_WIDTH - PADDING * 2; 
const int FIRST_CELL_Y = 50;
const int GRID_PADDING = 63;

const int CELL_SIZE = 64;
#define WRONG_CELL "assets//ui//CellColor//grid_gray.png"
#define MISPLACE_CELL "assets//ui//CellColor//grid_yellow.png"
#define CORRECT_CELL "assets//ui//CellColor//grid_green.png"

//print gridstate
const int FIRST_CHECK_CELL_X = MID_WIDTH - PADDING * 2 - 30;
const int FIRST_CHECK_CELL_Y = 41;

//Const filepath to get the word
#define DICTIONARY "src/wordlist.txt"

#endif
