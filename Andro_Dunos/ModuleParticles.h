#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__	// @CarlesHoms @Andres

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 1000		// Make dymanic array for final game?
#define DEFAULT_VALUE -1

enum weapon_types	// To mark the weapon Type currently using
{
	TYPE_1 = 1,
	TYPE_2,
	TYPE_3,
	TYPE_4
};

enum shot_type
{
	BLUE_SHOT,
	GREEN_SINGLE_SHOT,
	ORANGE_SHOT,
	YELLOW_SHOT
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
	float fPositionHorizontal, fPositionVertical;
	int arrayId = DEFAULT_VALUE;	// Id needed to delete the full particle array, default for non arrays
	int shotType = DEFAULT_VALUE;	// Id for blue and orange power particles
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

	void SetParticleArray(Particle* particleArray, int arraySize, int startX, int startY, int particleSizeX, int particleSizeY, int movX, int movY, float speedX, float speedY, int particleLife, float animSpeed = 0.0f, bool animLoop = false);
	void AddParticle(const Particle& particle, int x, int y, int shotType = DEFAULT_VALUE, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void AddParticleArray(Particle* particleArray, int arraySize, int x, int y, int movX, int movY, int shotType = DEFAULT_VALUE, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void ArrayListNext();
	void OnCollision(Collider* c1, Collider* c2) override;

private:
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	// Particle current used values
	int shortLife = 1000;
	int mediumLife = 2000;
	int	longLife = 3000;

	int arrayIdList = 0;

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
	Particle redRocketLeftDown;
	Particle redRocketLeftUp;
	Particle redRocketUpDiagonal;
	Particle redRocketDownDiagonal;

	// Type 3 particles
	Particle straightGreen;			

	// First diagonals				// Size: 2, 4. Move: 2, 2.
	Particle upRightGreen1[8];		// Starts at 57, 49
	Particle downRightGreen1[8];	// Starts at
	Particle upLeftGreen1[8];		// Starts at
	Particle downLeftGreen1[8];		// Starts at

	// Second diagonals cut in half
	Particle upRightGreen2[4];		
	Particle downRightGreen2[4];
	Particle upLeftGreen2[4];
	Particle downLeftGreen2[4];

	// Second diagonals full		// Size: 4, 12. Move: 4, 4. Array size: 8.
	Particle upRightGreen3[8];		// Starts at
	Particle downRightGreen3[8];	// Starts at 114, 42
	Particle upLeftGreen3[8];		// Starts at
	Particle downLeftGreen3[8];		// Starts at

	// Third diagonals cut in half
	Particle upRightGreen4[2];		
	Particle downRightGreen4[2];
	Particle upLeftGreen4[2];
	Particle downLeftGreen4[2];

	// Third diagonals full
	Particle upRightGreen5[4];
	Particle downRightGreen5[4];
	Particle upLeftGreen5[4];
	Particle downLeftGreen5[4];

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

	//@Andres
	Particle explosion;  //ring 
	Particle explosion1; //big fire
	Particle explosion2; //small fire

	//enemy laser
	Particle enemyBlueShot;



};

#endif // __MODULEPARTICLES_H__