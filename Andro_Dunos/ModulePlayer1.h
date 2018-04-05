#ifndef __ModulePlayer1_H__
#define __ModulePlayer1_H__	//@CarlesHoms

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer1 : public Module
{
public:
	ModulePlayer1();
	~ModulePlayer1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;

	// Ship and booster animations
	Animation shipVerticalMovement;
	Animation superUpwardsBooster;
	Animation upwardsBooster;
	Animation idleBooster;
	Animation downwardsBooster;
	Animation superDownwardsBooster;

	// Animation pointers
	Animation* shipAnimation = nullptr;
	Animation* propellerAnimation = nullptr;

	iPoint position;
	float movVertical;	// Counter for the vertical movement of the ship
	int maxVertical;	// Limit of the counter
};

#endif