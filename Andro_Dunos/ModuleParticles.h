#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;

struct Particle
{
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
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

	void AddParticle(const Particle& particle, int x, int y, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:

	// Type 1 particles
	Particle smallBlue;
	/*Particle mediumBlue;
	Particle bigBlue;

	// Type 2 particles
	Particle YellowBigRight;
	Particle YellowBigLeft;
	Particle yellowUpLeft;
	Particle yellowSmallRight;
	Particle yellowSmallLeft;

	// Type 3 particles
	Particle straightGreen;
	Particle upRightGreen;
	Particle downRightGreen;

	// Type 4 particles
	Particle arrow1;
	Particle arrow2;
	Particle arrow3;
	Particle arrow4;
	Particle arrow5;*/

	// Homing particles


	// Shield particles


};

#endif // __MODULEPARTICLES_H__