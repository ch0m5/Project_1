#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__	// @CarlesHoms @Andres

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

enum weapon_types	// To mark the weapon Type currently using
{
	TYPE_1 = 1,
	TYPE_2,
	TYPE_3,
	TYPE_4
};

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void OnCollision(Collider* c1, Collider* c2) override;

private:
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

	SDL_Texture* explosionPtr = nullptr;

public:
		// Type 1 particles
	Particle smallBlue;
	Particle mediumBlue;			// Needs paths
	Particle bigBlue;				

	//Particle missileHorizontal;
	//Particle missileUp;			// Needs paths
	//Particle missileDown;

		// Type 2 particles
	Particle YellowBigRight;
	Particle YellowBigLeft;
	Particle yellowDown;
	Particle yellowUp;
	Particle yellowSmallRight;
	Particle yellowSmallLeft;

	//Particle redRocket;

		// Type 3 particles
	Particle straightGreen;
	Particle upRightGreen;		// Diagonal: needs modified collider
	Particle downRightGreen;	// Diagonal: needs modified collider

	//Particle nigger and split lasers

	//Particle bomb;

		// Type 4 particles
	Particle arrowUp1;
	Particle arrowStraight1;	// Animation stops at 2nd frame
	Particle arrowDown1;

	Particle arrowSuperUp2;
	Particle arrowUp2;
	Particle arrowStraight2;	// Animation stops at 3rd frame
	Particle arrowDown2;
	Particle arrowSuperDown2;

	Particle arrowSuperUp3;
	Particle arrowUp3;
	Particle arrowStraight3;	// Animation stops at 5th frame
	Particle arrowDown3;
	Particle arrowSuperDown3;

	Particle laserUp;
	Particle laserDown;
	//Particle downRightGreen;	// Reusing particles (keep commented)
	//Particle upRightGreen;

		// Homing particles

	//Particle SeekingMissile1;
	//Particle SeekingMissile2;		// Needs paths
	//Particle SeekingMissile3;

		// Shield particles

	//Particle redShield;
	//Particle greenShield;		// Needs paths
	//Particle yellowShield;

	Particle explosion;
};

#endif // __MODULEPARTICLES_H__