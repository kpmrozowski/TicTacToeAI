#pragma once
// These are game options, use on your own risc xD

#define SCREEN_WIDTH 930
#define SCREEN_HEIGHT 1030

#define SPLASH_STATE_SHOW_TIME 0.1

#define SPLASH_SCENE_BACKGROUND_FILEPATH "Resources/res/Splash Background.png"
#define MAIN_MENU_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"
#define GAME_BACKGROUND_FILEPATH "Resources/res/Game Background.png"
#define PAUSE_BACKGROUND_FILEPATH "Resources/res/Main Menu Background.png"

#define MAIN_MENU_TITLE_FILEPATH "Resources/res/Game Title.png"

#define MAIN_MENU_PLAY_BUTTON_X "Resources/res/Play Button X.png"
#define MAIN_MENU_PLAY_BUTTON_O "Resources/res/Play Button O.png"
#define RESUME_BUTTON "Resources/res/Resume Button.png"
#define HOME_BUTTON "Resources/res/Home Button.png"
#define RETRY_BUTTON "Resources/res/Retry Button.png"

#define MAIN_MENU_PLAY_BUTTON_OUTER "Resources/res/Play Button Outer.png"

#define PAUSE_BUTTON "Resources/res/Pause Button.png"

#define X_PIECE_FILEPATH "Resources/res/X.png"
#define O_PIECE_FILEPATH "Resources/res/O.png"
#define XY_BUTTONS_OFFSET 20
#define X_WINNING_PIECE_FILEPATH "Resources/res/X Win.png"
#define O_WINNING_PIECE_FILEPATH "Resources/res/O Win.png"

#define GRID_SPRITE_FILEPATH "Resources/res/Grid.png"

//	Some predefined states for the grid in which are different pices:
#define X_PIECE 8
#define O_PIECE 0
#define EMPTY_PIECE -1	//	Tracking the empty pice

#define STATE_PLAYING 98
#define STATE_PAUSED 97
#define STATE_WON 96
#define STATE_LOSE 95
#define STATE_PLACING_PIECE 94
#define STATE_AI_PLAYING 93
#define STATE_DRAW 92

#define TIME_BEFORE_SHOWING_GAME_OVER 2