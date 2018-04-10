#ifndef __ModulePlayer1_H__
#define __ModulePlayer1_H__	//@CarlesHoms

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer1 : public Module
{
public:
	ModulePlayer1();
	~ModulePlayer1();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override;

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

	//Music 
	Mix_Chunk *shot = nullptr;

	//Collider
	struct Collider* playerHitbox;
};

#endif