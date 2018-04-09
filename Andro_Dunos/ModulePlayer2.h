#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__	//@CarlesHoms

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

	// Ship and propeller sizes in pixels
	int shipHeight;
	int shipWidth;
	int propellerWidth;
	int propellerHeight;

	iPoint position;
	float movVertical;	// Counter for the vertical movement of the ship
	int maxVertical;	// Limit of the counter
};

#endif