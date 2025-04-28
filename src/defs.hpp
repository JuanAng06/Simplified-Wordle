#ifndef _DEFS__H
#define _DEFS__H

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
#define KEY_LETTER_LAYOUT "assets//ui//key_letter_layout.png"
const int START_KEYBOARD_X = 195;
const int START_KEYBOARD_Y = MID_WIDTH - 30;
const int KEYBOARD_TEXT_SIZE = 32;
const int ROW_SPACING = 66;
const int PADDING = 66;

//Grid manager
static const int ROWS = 6;
static const int COLS = 5;

const int FIRST_CELL_X = MID_WIDTH - PADDING * 2 - 1; 
const int FIRST_CELL_Y = 52;
const int GRID_PADDING = 63;

const int CELL_SIZE = 64;
#define WRONG_CELL "assets//ui//CellColor//grid_gray.png"
#define MISPLACE_CELL "assets//ui//CellColor//grid_yellow.png"
#define CORRECT_CELL "assets//ui//CellColor//grid_green.png"

//print gridstate
const int FIRST_CHECK_CELL_X = 359;
const int FIRST_CHECK_CELL_Y = 44;
const int CHECK_CELL_PADDING = 62;

//Const filepath to get the word
#define DICTIONARY "src/wordlist.txt"

//Show result
#define RESULT "assets//ui//result//result.jpg"
#define WIN_SCREEN "assets//ui//result//win_screen.png"
#define LOSE_SCREEN "assets//ui//result//lose_screen.png"
#define RETRY_BUTTON "assets//ui//result//retry_button.png"
#define EXIT_BUTTON "assets//ui//result//exit_button.png"

//Retry button
const int RETRY_X_START = 148, RETRY_X_END = 148 + 365;
const int RETRY_Y_START = 520, RETRY_Y_END = 520 + 120;

//Exit button
const int EXIT_X_START = 547, EXIT_X_END = 547 + 365;
const int EXIT_Y_START = 520, EXIT_Y_END = 520 + 120;

//Show the secret word
const int REVEAL_SECRETWORD_X = 400, REVEAL_SECRETWORD_Y = 300;
const int REVEAL_SECRETWORD_TEXTSIZE = 80;

//Show temp pop up
#define POP_UP_ANNOUCNER "assets//ui//popup_announcer.png"
const int POPUP_X = MID_WIDTH - 150 , POPUP_Y = MID_HEIGHT - 50;
const int POPUP_TEXTSIZE = 30;
const int POPUP_CENTER_X = MID_WIDTH - 250, POPUP_CENTER_Y = MID_HEIGHT - 125;

//Sound effect - TEST ZONE
#define ENTER_KEY "assets//sfx//enterKey.MP3"
#define CLICK_BUTTON "assets//sfx//buttonClick.MP3"

//KeySound
#define KEY_SOUND_1 "assets//sfx//keyboard_sound//keysound_1.MP3"
#define KEY_SOUND_2 "assets//sfx//keyboard_sound//keysound_2.MP3"
#define KEY_SOUND_3 "assets//sfx//keyboard_sound//keysound_3.MP3"
#define KEY_SOUND_4 "assets//sfx//keyboard_sound//keysound_4.MP3"
#define KEY_SOUND_5 "assets//sfx//keyboard_sound//keysound_5.MP3"

//Main menu UI
#define MAIN_MENU_SCREEN "assets//ui//mainMenu//main_menu_screen.png"
#define MENU_EXIT_BUTTON "assets//ui//mainMenu//exit_button.png"
#define MENU_TUTORIAL_BUTTON "assets//ui//mainMenu//tutorial_button.png"
#define MENU_PLAY_BUTTON "assets//ui//mainMenu//play_button.png"
#define MENU_TUTORIAL_SCREEN "assets//ui//mainMenu//tutorial_screen.png"
#define TUTORIAL_OKAY_BUTTON "assets//ui//mainMenu//tutorial_okay_button.png"

//Back button + give up button
#define BACK_BUTTON "assets//ui//back_button.png"
#define BACK_BUTTON_HOVER "assets//ui//back_button_hover.png"
#define GIVEUP_BUTTON "assets//ui//giveup_button.png"
#define GIVEUP_BUTTON_HOVER "assets//ui//giveup_button_hover.png"


#endif
