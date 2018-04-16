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

	// Player rectangle pointer
	SDL_Rect* shipRect;

	// Ship and propeller sizes in pixels
	int shipHeight;
	int shipWidth;
	int propellerWidth;
	int propellerHeight;

	fPoint position;	// Float movement
	float movVertical;	// Counter for the vertical movement of the ship
	int maxVertical;	// Limit of the counter

	//Music 
	Mix_Chunk *type1Shot = nullptr;		// All use the same channel (3)
	Mix_Chunk *type2Shot = nullptr;
	Mix_Chunk *type3Shot = nullptr;
	Mix_Chunk *type4Shot = nullptr;
	Mix_Chunk *typeSwap = nullptr;
	Mix_Chunk *powerUp = nullptr;
	Mix_Chunk *playerDeathExplosion = nullptr;

	//Collider
	Collider* playerHitbox;
	
	//Lasers
	int laserFrontOffset;		// Offset for front bullets
	int laserBackOffset;		// Offset for back bullets	// Distance from ship position to bullet creation
	int laserVerticalOffset;	// Offset for all bullets

	//Types and levels
	int type;					// Flag/counter for type equipped
	int bluePower;				// Flag/counter for blue power level
	int orangePower;			// Flag/counter for orange power level
	int yellowPower;			// Flag/counter for yellow power level
	int greenPower;				// Flag/counter for green power level

	//Debug Purpose Variables
	bool godMode = false;
};

#endif