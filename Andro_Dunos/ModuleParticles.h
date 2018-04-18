#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__	// @CarlesHoms @Andres

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 500

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
	float fPositionHorizontal, fPositionVertical;	// carles edit
	fPoint speed;
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
	void AddParticleArray(const Particle* particleArray, int arraySize, int x, int y, int horizontalOffset, int verticalOffset, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void AddParticleArray2(const Particle& particle, int arraySize, int x, int y, int horizontalOffset, int verticalOffset, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void OnCollision(Collider* c1, Collider* c2) override;

private:
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

	SDL_Texture* explosionPtr = nullptr;
	SDL_Texture* shipExplosion = nullptr;
	SDL_Texture* enemyExplosion = nullptr;

public:
		// Particle current used values
	int shortLife = 1000;
	int mediumLife = 2000;
	int	longLife = 3000;

		// Type 1 particles
	Particle smallBlue;
	Particle mediumBlue;			// Needs paths
	Particle bigBlue;				

	// Orange Power
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

	// Orange Power
	Particle redRocketDown;
	Particle redRocketUp;
	Particle redRocketRightDown;
	Particle redRocketRightUp;

		// Type 3 particles
	Particle straightGreen;					// First diagonals
	//Particle upRightGreen1;				// Starts at  57, 53, Up, Right	// TESTING HERE
	Particle upRightGreen1[8];				// Starts at  57, 53, Up, Right	// TESTING HERE
	Particle* downRightGreen1 = nullptr;	// Starts at  57, 53, Up
	Particle* upLeftGreen1 = nullptr;		// Starts at  57, 53, Up
	Particle* downLeftGreen1 = nullptr;		// Starts at  57, 53, Up
	int greenSize1 = 8;						// Size: 2, 4. Move: 2, 2.

	// Second diagonals cut in half
	Particle* upRightGreen2 = nullptr;
	Particle* downRightGreen2 = nullptr;
	Particle* upLeftGreen2 = nullptr;
	Particle* downLeftGreen2 = nullptr;
	int greenSize2 = 0;

	// Second diagonals full
	Particle* upRightGreen3 = nullptr;		
	Particle* downRightGreen3 = nullptr;
	Particle* upLeftGreen3 = nullptr;
	Particle* downLeftGreen3 = nullptr;
	int greenSize3 = 0;						// Size: 4, 12. Move: 4, 4.

	// Third diagonals cut in half
	Particle* upRightGreen4 = nullptr;
	Particle* downRightGreen4 = nullptr;
	Particle* upLeftGreen4 = nullptr;
	Particle* downLeftGreen4 = nullptr;
	int greenSize4 = 0;						
	
	// Third diagonals full
	Particle* upRightGreen5 = nullptr;		
	Particle* downRightGreen5 = nullptr;
	Particle* upLeftGreen5 = nullptr;
	Particle* downLeftGreen5 = nullptr;
	int greenSize5 = 0;						// Size 4, 12, starts in 80, 68 in spritesheet, goes up by 4 pixels each time

	// Orange Power
	Particle bombRightDown;
	Particle bombRightUp;
	Particle bombLeftDown;
	Particle bombLeftUp;

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

	// Orange Power
	Particle laserUp;
	Particle laserDown;
	//Particle* downRightGreen = nullptr;	// Reusing particles (keep commented)
	//Particle* upRightGreen = nullptr;

		// Homing particles

	//Particle SeekingMissile1;
	//Particle SeekingMissile2;		// Needs paths
	//Particle SeekingMissile3;

		// Shield particles

	//Particle redShield;
	//Particle greenShield;		// Needs paths
	//Particle yellowShield;

	Particle explosion;
	//@XaviMarin
	//Particle shipExplo;
	Particle EnemyExplo;

	
};

#endif // __MODULEPARTICLES_H__