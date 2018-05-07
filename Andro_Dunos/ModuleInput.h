#ifndef __ModuleInput_H__
#define __ModuleInput_H__	//@CarlesHoms

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	const Uint8* keys = nullptr;
	KEY_STATE keyboard[MAX_KEYS];
	SDL_Event e;
	//Game Controllers, currently implementing for player 1
	SDL_GameController* gamepadP1 = nullptr;
	bool gamepadP1con = false;
	int gamepadP1LAxisX = 0;
	int gamepadP1LAxisY = 0;
	bool gamepadP1APressed = false;
	bool gamepadP1XPressed = false;
	bool gamepadP1StartPressed = false;

	//GAme Controller for Player 2
	SDL_GameController* gamepadP2 = nullptr;
	bool gamepadP2con = false;
	int gamepadP2LAxisX = 0;
	int gamepadP2LAxisY = 0;
	bool gamepadP2APressed = false;
	bool gamepadP2XPressed = false;
	bool gamepadP2StartPressed = false;

	//debug mode function
	bool debugMode = false;
	bool coliderView = false;

	//second player on off
	bool secondPlayerState;
};

#endif // __ModuleInput_H__