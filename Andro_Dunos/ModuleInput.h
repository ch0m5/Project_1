#ifndef __ModuleInput_H__
#define __ModuleInput_H__	//@CarlesHoms

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL.h"

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
};

#endif // __ModuleInput_H__