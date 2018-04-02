#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;

	Animation superUpwards;
	Animation superUpwardsBooster;
	Animation upwards;
	Animation upwardsBooster;
	Animation idle;
	Animation idleBooster;
	Animation downwards;
	Animation downwardsBooster;
	Animation superDownwards;
	Animation superDownwardsBooster;
	iPoint position;
	int movVertical;	// Counter for the vertical movement of the ship
	int maxVertical;	// Maximum value
};

#endif