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

	// Animation ship crash
	Animation crash;
	bool destroyed;

	// Animation pointers
	Animation* shipAnimation = nullptr;
	Animation* propellerAnimation = nullptr;
	Animation* crashAnimation = nullptr;

	// Player rectangle pointer
	SDL_Rect* shipRect;

	// Ship and propeller sizes in pixels
	int shipWidth;
	int shipHeight;
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
	int laserHorizontalOffset = 18;	// Horizontal Offset for bullets
	int laserVerticalOffset = 12;	// Vertical Offset for bullets

	//Types and levels
	int type;					// Flag/counter for type equipped
	int bluePower;				// Flag/counter for blue power level
	int orangePower;			// Flag/counter for orange power level
	int yellowPower;			// Flag/counter for yellow power level
	int greenPower;				// Flag/counter for green power level

	//int blueShotTimer;	// After the last shot taken, if enough time passes without no shots, the "currentBlue" counter restarts.
	//int timeBetweenShotsTimer;	// time between each shot, could be a get ticks
	//int weaponChargeTimer

	int currentBlue;	// Every shot increases the counter by 2, player will not shot if it gets higher than 4. Each collide substracts 1.
	int currentOrange;	// Every time it fires increases the counter by x (changes on level), player will not shot until it reaches 0.  Each collide substracts 1.
	int currentYellow;	// When reaching level yellow one, the max becomes 5 and the counter increases by 1 for each misile fired. Each collide substracts 1.
	int currentMultipleShots;
	int currentArrayShots;

	int maxShots;	// TEMPORAL SHOT LIMITATION
	int maxArrayShots;

	// COUTNER THAT UPDATES DEPENDING ON THE TYPE OF SHOTS WITH NUMBER OF SHOTS MAX = 3?

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
	bool godMode;
};

#endif