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

	int font_score = -1;
	char score_text[10];
	uint score = 0;

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

	//Counter to limitate how many lasers, boms, etc can the player have on screen, based on needed particles to be destroyed to make more shots.
	int maxBlue = 4;
	int maxOrange = 0;
	int maxYellow = 0;
	//int blueShotTimer;	// After the last shot taken, if enough time passes without no shots, the "currentBlue" counter restarts.
	//int timeBetweenShotsTimer;	// time between each shot, could be a get ticks

	int currentBlue = 0;	// Every shot increases the counter by 2, player will not shot if it gets higher than 4. Each collide substracts 1.
	int currentOrange = 0;	// Every time it fires increases the counter by x (changes on level), player will not shot if it reaches MAX.  Each collide substracts 1.
	int currentYellow = 0;	// When reaching level yellow one, the max becomes 3 and the counter increases by 1 for each misile fired. Each collide substracts 1.

	// For max: MaxBlueLasers = 3, MaxOrange = 1, MaxYellow = 3
	// Lower Conditions:
	// Blue = 2 collides
	// Orange lvl 1,2 = 1 collide; level 2,5 = 2 collides
	// Yellow = 1 collide
	// ! By colliding it also means if they die by life time end

	// Blue: time (200/300 miliseconds) or collision
	// Orange: collision (2nd, bombs, just have really short life)
	// Yellow: collision

	//Debug Purpose Variables
	bool godMode = false;
};

#endif