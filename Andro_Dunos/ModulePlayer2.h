#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__	//@CarlesHoms

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

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
	Collider* playerHitbox;

	//Lasers
	int type;					// Flag/counter for type equipped
	int laserFrontOffset;		// Offset for front bullets
	int laserBackOffset;		// Offset for back bullets	// Distance from ship position to bullet creation
	int laserVerticalOffset;	// Offset for all bullets

	//Debug Purpose Variables
	bool godMode = false;
};

#endif