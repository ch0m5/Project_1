#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL\include\SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

enum update_status	// To flag if the modules' status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum ship_status	// To mark the position in the array of SDL_rects related the the ship vertical status
{
	SHIP_FULL_UP,
	SHIP_UP,
	SHIP_IDLE,
	SHIP_DOWN,
	SHIP_FULL_DOWN
};

// Useful typedefs ---------
typedef unsigned int uint;

// Configuration -----------
#define SCREEN_SIZE 3		// Multiplies the screen size and resolution
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 224
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define REN_VSYNC 1
#define VERSION " (v0.2.0)"		// Adds to the window name "Andro Dunos", used to mark the current working version

#endif // __GLOBALS_H__
