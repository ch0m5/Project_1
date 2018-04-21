#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleStage1.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()	// @Andres @CarlesHoms
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Sprites/Players_Ships/Laser_particles.png");

	/* Laser Sprites

	Type 1:
	21, 6, 16, 10	big
	24, 39, 11, 4	small	// Lasers grow, collider should change while travelling
	22, 51, 15, 6	medium

	Type 2:
	3, 8, 15, 5		big right
	3, 23, 15, 5	big left
	5, 45, 11, 8	down
	5, 50, 11, 8	up
	6, 69, 10, 3	right
	6, 84, 10, 3	left

	Type 3:
	42, 87, 32, 3   --	small
	66, 27, 3, 16	|	small
	57, 35, 16, 18	/	small
	57, 60, 16, 18	\	small

	76, 2, 16, 22	/1	medium
	76, 32, 16, 22	\1	medium
	76, 65, 16, 22	/2	medium
	76, 95, 16, 22	\2	medium

	94, 0, 31, 31	/1	big
	94, 32, 31, 31	\1	big
	94, 64, 31, 31	/2	big
	94, 96, 31, 31	\2	big

	Type 4:
	41, 11, 13, 2	1
	41, 23, 13, 6	2
	41, 38, 13, 8	3	// Lasers grow, collider should change while travelling
	41, 49, 13, 12	4
	41, 64, 13, 14	5

	*/

	/* Laser Sprites

	Type 1:
	21, 6, 16, 10	big
	24, 39, 11, 4	small	// Lasers grow, collider should change while travelling
	22, 51, 15, 6	medium

	Type 2:
	3, 8, 15, 5		big right
	3, 23, 15, 5	big left
	5, 45, 11, 8	down
	5, 50, 11, 8	up
	6, 69, 10, 3	right
	6, 84, 10, 3	left

	Type 3:
	42, 87, 32, 3   --	small
	66, 27, 3, 16	|	small
	57, 35, 16, 18	/	small
	57, 60, 16, 18	\	small

	76, 2, 16, 22	/1	medium
	76, 32, 16, 22	\1	medium
	76, 65, 16, 22	/2	medium
	76, 95, 16, 22	\2	medium

	94, 0, 31, 31	/1	big
	94, 32, 31, 31	\1	big
	94, 64, 31, 31	/2	big
	94, 96, 31, 31	\2	big

	Type 4:
	41, 11, 13, 2	1
	41, 23, 13, 6	2
	41, 38, 13, 8	3	// Lasers grow, collider should change while travelling (HAHAHAHAHA, making the collider grow...)
	41, 49, 13, 12	4
	41, 64, 13, 14	5

	*/

	// Player Type 1 (blue)
	smallBlue.anim.PushBack({ 24, 39, 11, 4 });
	smallBlue.anim.loop = false;
	smallBlue.speed.x = 7.0f;
	smallBlue.life = shortLife;
	smallBlue.anim.speed = 0.3f;

	mediumBlue.anim.PushBack({ 22, 51, 15, 6 });
	mediumBlue.anim.loop = false;
	mediumBlue.speed.x = 7.0f;
	mediumBlue.life = shortLife;
	mediumBlue.anim.speed = 0.3f;

	bigBlue.anim.PushBack({ 21, 6, 16, 10 });
	bigBlue.anim.loop = false;
	bigBlue.speed.x = 7.0f;
	bigBlue.life = shortLife;
	bigBlue.anim.speed = 0.3f;

	//Player Type 2 (yellow)
	YellowBigRight.anim.PushBack({ 3, 8, 15, 5 });
	YellowBigRight.anim.loop = false;
	YellowBigRight.speed.x = 7.0f;
	YellowBigRight.life = shortLife;
	YellowBigRight.anim.speed = 0.3f;

	YellowBigLeft.anim.PushBack({ 3, 23, 15, 5 });
	YellowBigLeft.anim.loop = false;
	YellowBigLeft.speed.x = -7.0f;
	YellowBigLeft.life = shortLife;
	YellowBigLeft.anim.speed = 0.3f;

	yellowDown.anim.PushBack({ 5, 37, 11, 8 });
	yellowDown.anim.loop = false;
	yellowDown.speed.x = -7.0f;
	yellowDown.speed.y = 2.0f;
	yellowDown.life = shortLife;
	yellowDown.anim.speed = 0.3f;

	yellowUp.anim.PushBack({ 5, 50, 10, 8 });
	yellowUp.anim.loop = false;
	yellowUp.speed.x = 7.0f;
	yellowUp.speed.x = -2.0f;
	yellowUp.life = shortLife;
	yellowUp.anim.speed = 0.3f;

	yellowSmallRight.anim.PushBack({ 6, 69, 10, 3 });
	yellowSmallRight.anim.loop = false;
	yellowSmallRight.speed.x = 7.0f;
	yellowSmallRight.life = shortLife;
	yellowSmallRight.anim.speed = 0.3f;

	yellowSmallLeft.anim.PushBack({ 6, 84, 10, 3 });
	yellowSmallLeft.anim.loop = false;
	yellowSmallLeft.speed.x = -7.0f;
	yellowSmallLeft.life = shortLife;
	yellowSmallLeft.anim.speed = 0.3f;
	// red rocket fix sprite
	redRocketDown.anim.PushBack({ 0, 99, 16, 9 });	// RedRockets sprites need to be fixed
	redRocketDown.anim.PushBack({ 0, 113, 16, 9 });
	redRocketDown.anim.PushBack({ 2, 129, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 142, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 158, 16, 9 });
	redRocketDown.anim.PushBack({ 2, 173, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 188, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 202, 16, 9 });
	redRocketDown.anim.loop = true;
	redRocketDown.speed.x = 1.0f;	// Should be camera horizontal speed
	redRocketDown.speed.y = 2.0f;
	redRocketDown.life = shortLife;
	redRocketDown.anim.speed = 0.3f;

	redRocketUp.anim.PushBack({ 0, 99, 16, 9 });
	redRocketUp.anim.PushBack({ 0, 113, 16, 9 });
	redRocketUp.anim.PushBack({ 2, 129, 16, 9 });
	redRocketUp.anim.PushBack({ 3, 142, 16, 9 });
	redRocketUp.anim.PushBack({ 3, 158, 16, 9 });
	redRocketUp.anim.PushBack({ 2, 173, 16, 9 });
	redRocketUp.anim.PushBack({ 3, 188, 16, 9 });
	redRocketUp.anim.PushBack({ 3, 202, 16, 9 });
	redRocketUp.anim.loop = true;
	redRocketUp.speed.x = 1.0f;	// Should be camera horizontal speed
	redRocketUp.speed.y = -2.0f;
	redRocketUp.life = shortLife;
	redRocketUp.anim.speed = 0.3f;

	redRocketRightDown.anim.PushBack({ 0, 99, 16, 9 });
	redRocketRightDown.anim.PushBack({ 0, 113, 16, 9 });
	redRocketRightDown.anim.PushBack({ 2, 129, 16, 9 });
	redRocketRightDown.anim.PushBack({ 3, 142, 16, 9 });
	redRocketRightDown.anim.PushBack({ 3, 158, 16, 9 });
	redRocketRightDown.anim.PushBack({ 2, 173, 16, 9 });
	redRocketRightDown.anim.PushBack({ 3, 188, 16, 9 });
	redRocketRightDown.anim.PushBack({ 3, 202, 16, 9 });
	redRocketRightDown.anim.loop = true;
	redRocketRightDown.speed.x = 2.0f;
	redRocketRightDown.speed.y = 2.0f;
	redRocketRightDown.life = shortLife;
	redRocketRightDown.anim.speed = 0.3f;

	redRocketRightUp.anim.PushBack({ 0, 99, 16, 9 });
	redRocketRightUp.anim.PushBack({ 0, 113, 16, 9 });
	redRocketRightUp.anim.PushBack({ 2, 129, 16, 9 });
	redRocketRightUp.anim.PushBack({ 3, 142, 16, 9 });
	redRocketRightUp.anim.PushBack({ 3, 158, 16, 9 });
	redRocketRightUp.anim.PushBack({ 2, 173, 16, 9 });
	redRocketRightUp.anim.PushBack({ 3, 188, 16, 9 });
	redRocketRightUp.anim.PushBack({ 3, 202, 16, 9 });
	redRocketRightUp.anim.loop = true;
	redRocketRightUp.speed.x = 2.0f;
	redRocketRightUp.speed.y = -2.0f;
	redRocketRightUp.life = shortLife;
	redRocketRightUp.anim.speed = 0.3f;

	//Player Type 3 (green)
	straightGreen.anim.PushBack({ 42, 87, 32, 3 });
	straightGreen.anim.loop = false;
	straightGreen.speed.x = 7.0f;
	straightGreen.life = shortLife;
	straightGreen.anim.speed = 0.3f;

	// Parameter list: (Particle* particleArray, int arraySize, int startX, int startY, int particleSizeX, int particleSizeY, int movX, int movY, float speedX, float speedY, int life, int animSpeed = 0.0f, bool animLoop = false)
	SetParticleArray(upRightGreen1, 8, 57, 49, 2, 4, 2, -2, 4.0f, -4.0f, shortLife);
	SetParticleArray(downRightGreen1, 8, 57, 60, 2, 4, 2, 2, 4.0f, 4.0f, shortLife);
	SetParticleArray(upLeftGreen1, 8, 71, 74, 2, 4, -2, -2, -4.0f, -4.0f, shortLife);
	SetParticleArray(downLeftGreen1, 8, 71, 35, 2, 4, -2, 2, -4.0f, 4.0f, shortLife);

	SetParticleArray(upRightGreen2, 4, 114, 34, 4, 12, 4, -4, 4.0f, -4.0f, shortLife);
	SetParticleArray(downRightGreen2, 4, 114, 46, 4, 12, 4, 4, 4.0f, 4.0f, shortLife);
	SetParticleArray(upLeftGreen2, 4, 108, 34, 4, 12, -4, -4, -4.0f, -4.0f, shortLife);
	SetParticleArray(downLeftGreen2, 4, 108, 46, 4, 12, -4, 4, -4.0f, 4.0f, shortLife);

	SetParticleArray(upRightGreen3, 8, 114, 34, 4, 12, 4, -4, 4.0f, -4.0f, shortLife);
	SetParticleArray(downRightGreen3, 8, 114, 46, 4, 12, 4, 4, 4.0f, 4.0f, shortLife);	// DO NOT DELETE
	SetParticleArray(upLeftGreen3, 8, 108, 34, 4, 12, -4, -4, -4.0f, -4.0f, shortLife);
	SetParticleArray(downLeftGreen3, 8, 108, 46, 4, 12, -4, 4, -4.0f, 4.0f, shortLife);
	
	SetParticleArray(upRightGreen4, 4, 215, 50, 16, 8, 8, -7, 4.0f, -4.0f, shortLife);
	SetParticleArray(downRightGreen4, 4, 215, 60, 16, 8, 8, 7, 4.0f, 4.0f, shortLife);
	SetParticleArray(upLeftGreen4,4, 199, 50, 16, 8, -8, -7, -4.0f, -4.0f, shortLife);
	SetParticleArray(downLeftGreen4, 4, 199, 60, 16, 8, -8, 7, -4.0f, 4.0f, shortLife);

	SetParticleArray(upRightGreen5, 8, 215, 50, 16, 8, 8, -7, 4.0f, -4.0f, shortLife);
	SetParticleArray(downRightGreen5, 8, 215, 60, 16, 8, 8, 7, 4.0f, 4.0f, shortLife);
	SetParticleArray(upLeftGreen5, 8, 199, 50, 16, 8, -8, -7, -4.0f, -4.0f, shortLife);
	SetParticleArray(downLeftGreen5, 8, 199, 60, 16, 8, -8, 7, -4.0f, 4.0f, shortLife);

	bombRightDown.anim.PushBack({ 121, 113, 8, 9 });
	bombRightDown.anim.loop = false;
	bombRightDown.speed.x = 3.0f;
	bombRightDown.speed.y = 1.0f;
	bombRightDown.life = shortLife;
	bombRightDown.anim.speed = 0.5f;

	bombRightUp.anim.PushBack({ 121, 98, 8, 9 });
	bombRightUp.anim.loop = false;
	bombRightUp.speed.x = 3.0f;
	bombRightUp.speed.y = -1.0f;
	bombRightUp.life = shortLife;
	bombRightUp.anim.speed = 0.5f;

	bombLeftDown.anim.PushBack({ 121, 113, 8, 9 });
	bombLeftDown.anim.loop = false;
	bombLeftDown.speed.x = -2.0f;
	bombLeftDown.speed.y = 1.0f;
	bombLeftDown.life = shortLife;
	bombLeftDown.anim.speed = 0.5f;

	bombLeftUp.anim.PushBack({ 121, 98, 8, 9 });
	bombLeftUp.anim.loop = false;
	bombLeftUp.speed.x = -2.0f;
	bombLeftUp.speed.y = -1.0f;
	bombLeftUp.life = shortLife;
	bombLeftUp.anim.speed = 0.5f;

	//Player Type 4 (white)
	arrowUp1.anim.PushBack({ 41, 9, 13, 6 });
	arrowUp1.anim.PushBack({ 41, 23, 13, 6 });
	arrowUp1.anim.loop = false;
	arrowUp1.speed.x = 7.0f;
	arrowUp1.speed.y = -1.0f;
	arrowUp1.life = shortLife;
	arrowUp1.anim.speed = 0.5f;

	arrowStraight1.anim.PushBack({ 41, 9, 13, 6 });
	arrowStraight1.anim.PushBack({ 41, 23, 13, 6 });
	arrowStraight1.anim.loop = false;
	arrowStraight1.speed.x = 7.0f;
	arrowStraight1.life = shortLife;
	arrowStraight1.anim.speed = 0.5f;

	arrowDown1.anim.PushBack({ 41, 9, 13, 6 });
	arrowDown1.anim.PushBack({ 41, 23, 13, 6 });
	arrowDown1.anim.loop = false;
	arrowDown1.speed.x = 7.0f;
	arrowDown1.speed.y = 1.0f;
	arrowDown1.life = shortLife;
	arrowDown1.anim.speed = 0.5f;

	//------------------------------------------------

	arrowSuperUp2.anim.PushBack({ 41, 8, 13, 8 });
	arrowSuperUp2.anim.PushBack({ 41, 22, 13, 8 });
	arrowSuperUp2.anim.PushBack({ 41, 38, 13, 8 });
	arrowSuperUp2.anim.loop = false;
	arrowSuperUp2.speed.x = 7.0f;
	arrowSuperUp2.speed.y = -1.5f;
	arrowSuperUp2.life = shortLife;
	arrowSuperUp2.anim.speed = 0.5f;

	arrowUp2.anim.PushBack({ 41, 8, 13, 8 });
	arrowUp2.anim.PushBack({ 41, 22, 13, 8 });
	arrowUp2.anim.PushBack({ 41, 38, 13, 8 });
	arrowUp2.anim.loop = false;
	arrowUp2.speed.x = 7.0f;
	arrowUp2.speed.y = -1.0f;
	arrowUp2.life = shortLife;
	arrowUp2.anim.speed = 0.5f;

	arrowStraight2.anim.PushBack({ 41, 8, 13, 8 });
	arrowStraight2.anim.PushBack({ 41, 22, 13, 8 });
	arrowStraight2.anim.PushBack({ 41, 38, 13, 8 });
	arrowStraight2.anim.loop = false;
	arrowStraight2.speed.x = 7.0f;
	arrowStraight2.life = shortLife;
	arrowStraight2.anim.speed = 0.5f;

	arrowDown2.anim.PushBack({ 41, 8, 13, 8 });
	arrowDown2.anim.PushBack({ 41, 22, 13, 8 });
	arrowDown2.anim.PushBack({ 41, 38, 13, 8 });
	arrowDown2.anim.loop = false;
	arrowDown2.speed.x = 7.0f;
	arrowDown2.speed.y = 1.0f;
	arrowDown2.life = shortLife;
	arrowDown2.anim.speed = 0.5f;

	arrowSuperDown2.anim.PushBack({ 41, 8, 13, 8 });
	arrowSuperDown2.anim.PushBack({ 41, 22, 13, 8 });
	arrowSuperDown2.anim.PushBack({ 41, 38, 13, 8 });
	arrowSuperDown2.anim.loop = false;
	arrowSuperDown2.speed.x = 7.0f;
	arrowSuperDown2.speed.y = 1.5f;
	arrowSuperDown2.life = shortLife;
	arrowSuperDown2.anim.speed = 0.5f;

	//--------------------------------------------------

	arrowSuperUp3.anim.PushBack({ 41, 5, 13, 14 });
	arrowSuperUp3.anim.PushBack({ 41, 19, 13, 14 });
	arrowSuperUp3.anim.PushBack({ 41, 35, 13, 14 });
	arrowSuperUp3.anim.PushBack({ 41, 49, 13, 14 });
	arrowSuperUp3.anim.PushBack({ 41, 48, 13, 14 });
	arrowSuperUp3.anim.loop = false;
	arrowSuperUp3.speed.x = 7.0f;
	arrowSuperUp3.speed.y = -1.5;
	arrowSuperUp3.life = shortLife;
	arrowSuperUp3.anim.speed = 0.2f;

	arrowUp3.anim.PushBack({ 41, 5, 13, 14 });
	arrowUp3.anim.PushBack({ 41, 19, 13, 14 });
	arrowUp3.anim.PushBack({ 41, 35, 13, 14 });
	arrowUp3.anim.PushBack({ 41, 49, 13, 14 });
	arrowUp3.anim.PushBack({ 41, 48, 13, 14 });
	arrowUp3.anim.loop = false;
	arrowUp3.speed.x = 7.0f;
	arrowUp3.speed.y = -1.0f;
	arrowUp3.life = shortLife;
	arrowUp3.anim.speed = 0.2f;

	arrowStraight3.anim.PushBack({ 41, 5, 13, 14 });
	arrowStraight3.anim.PushBack({ 41, 19, 13, 14 });
	arrowStraight3.anim.PushBack({ 41, 35, 13, 14 });
	arrowStraight3.anim.PushBack({ 41, 49, 13, 14 });
	arrowStraight3.anim.PushBack({ 41, 48, 13, 14 });
	arrowStraight3.anim.loop = false;
	arrowStraight3.speed.x = 7.0f;
	arrowStraight3.life = shortLife;
	arrowStraight3.anim.speed = 0.2f;

	arrowDown3.anim.PushBack({ 41, 5, 13, 14 });
	arrowDown3.anim.PushBack({ 41, 19, 13, 14 });
	arrowDown3.anim.PushBack({ 41, 35, 13, 14 });
	arrowDown3.anim.PushBack({ 41, 49, 13, 14 });
	arrowDown3.anim.PushBack({ 41, 48, 13, 14 });
	arrowDown3.anim.loop = false;
	arrowDown3.speed.x = 7.0f;
	arrowDown3.speed.y = 1.0f;
	arrowDown3.life = shortLife;
	arrowDown3.anim.speed = 0.2f;

	arrowSuperDown3.anim.PushBack({ 41, 5, 13, 14 });
	arrowSuperDown3.anim.PushBack({ 41, 19, 13, 14 });
	arrowSuperDown3.anim.PushBack({ 41, 35, 13, 14 });
	arrowSuperDown3.anim.PushBack({ 41, 49, 13, 14 });
	arrowSuperDown3.anim.PushBack({ 41, 48, 13, 14 });
	arrowSuperDown3.anim.loop = false;
	arrowSuperDown3.speed.x = 7.0f;
	arrowSuperDown3.speed.y = 1.5f;
	arrowSuperDown3.life = shortLife;
	arrowSuperDown3.anim.speed = 0.2f;

	// Explosion particle // @Andres
	explosion.anim.PushBack({ 505, 34, 4, 4 });
	explosion.anim.PushBack({ 512, 26, 12, 12 });
	explosion.anim.PushBack({ 528, 6, 32, 32 });
	explosion.anim.PushBack({ 563, 7, 30, 30 });
	explosion.anim.PushBack({ 597, 8, 30, 30 });
	explosion.anim.PushBack({ 518, 46, 30, 30 });
	explosion.anim.PushBack({ 552, 47, 30, 30 });
	explosion.anim.PushBack({ 587, 45, 32, 32 });
	explosion.anim.PushBack({ 524, 82, 32, 32 });
	explosion.anim.PushBack({ 571, 82, 32, 32 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.6f;

	explosion1.anim.PushBack({ 632, 24, 8, 8 });
	explosion1.anim.PushBack({ 642, 18, 13, 14 });
	explosion1.anim.PushBack({ 658, 7, 25, 25 });
	explosion1.anim.PushBack({ 688, 6, 27, 26 });
	explosion1.anim.PushBack({ 718, 3, 30, 29 });
	explosion1.anim.PushBack({ 632, 39, 29, 28 });
	explosion1.anim.PushBack({ 665, 39, 29, 28 });
	explosion1.anim.PushBack({ 698, 40, 28, 27 });
	explosion1.anim.PushBack({ 728, 42, 29, 27 });
	explosion1.anim.PushBack({ 632, 74, 29, 27 });
	explosion1.anim.PushBack({ 665, 76, 28, 26 });
	explosion1.anim.PushBack({ 698, 77, 26, 24 });
	explosion1.anim.PushBack({ 727, 79, 21, 21 });
	explosion1.anim.PushBack({ 638, 107, 17, 17 });
	explosion1.anim.PushBack({ 665, 115, 6, 6 });
	explosion1.anim.loop = false;
	explosion1.anim.speed = 0.6f;

	explosion2.anim.PushBack({ 509, 137, 6, 6 });
	explosion2.anim.PushBack({ 521, 135, 10, 8 });
	explosion2.anim.PushBack({ 535, 127, 16, 16 });
	explosion2.anim.PushBack({ 557, 129, 14, 14 });
	explosion2.anim.loop = false;
	explosion2.anim.speed = 0.6f;




	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			// carles edit
			if (p->shotType == BLUE_SHOT)
			{
				App->player1->currentBlue -= 1;
			}

			if (p->shotType == GREEN_SINGLE_SHOT)
			{
				App->player1->currentBlue -= 2;
			}

			if (p->shotType == ORANGE_SHOT)
			{
				App->player1->currentOrange -= 1;
			}

			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			//App->render->Blit(shipExplosion, p->position.x, p->position.y, &(p->anim.GetCurrentFrame())); // need to put the player position
			//App->render->Blit(enemyExplosion, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Parameter list: (Particle* particleArray, int arraySize, int particleSizeX, int particleSizeY, int startX, int startY, int movX, int movY, float speedX, float speedY, int life, int animSpeed, bool animLoop)
void ModuleParticles::SetParticleArray(Particle* particleArray, int arraySize, int startX, int startY, int particleSizeX, int particleSizeY, int movX, int movY, float speedX, float speedY, int particleLife, float animSpeed, bool animLoop) // Carles edit
{
	for (int i = 0; i < arraySize; i++)	// Carles edit
	{
		particleArray[i].anim.PushBack({ startX + movX * i, startY + movY * i, particleSizeX, particleSizeY });
		particleArray[i].anim.loop = animLoop;
		particleArray[i].speed.x = speedX;
		particleArray[i].speed.y = speedY;
		particleArray[i].life = particleLife;
		particleArray[i].anim.speed = animSpeed;
	}
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, int shotType, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->fPositionHorizontal = x + App->render->camera.x / SCREEN_SIZE;
			p->fPositionVertical = y + App->render->camera.y / SCREEN_SIZE;
			p->position.x = (int)p->fPositionHorizontal;
			p->position.y = (int)p->fPositionVertical;
			p->shotType = shotType;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::AddParticleArray(Particle* particleArray, int arraySize, int x, int y, int movX, int movY, int shotType, COLLIDER_TYPE collider_type, Uint32 delay)	// Carles edit
{
	uint i = 0;

	for (int j = 0; j < arraySize; j++)
	{
		for (i; i < MAX_ACTIVE_PARTICLES; ++i)	// Carles edit
		{
			if (active[i] == nullptr)
			{
				Particle* p = new Particle(particleArray[j]);	// maybe fails in here
				p->born = SDL_GetTicks() + delay;
				p->fPositionHorizontal = x + App->render->camera.x / SCREEN_SIZE + movX * j;
				p->fPositionVertical = y + App->render->camera.y / SCREEN_SIZE + movY * j;
				p->position.x = (int)p->fPositionHorizontal;
				p->position.y = (int)p->fPositionVertical;
				p->arrayId = arrayIdList;
				p->shotType = shotType;
				if (collider_type != COLLIDER_NONE)
					p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				active[i] = p;
				break;
			}
		}
	}

	ArrayListNext();
}

void ModuleParticles::ArrayListNext()
{
	if (arrayIdList < MAX_ACTIVE_PARTICLES)
		arrayIdList++;

	else { arrayIdList = 0; }
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (c2->type == COLLIDER_WALL || c2->type == COLLIDER_ENEMY)
			{
				//AddParticle(shipExplo, active[i]->position.x, active[i]->position.y);
				
				// carles edit (NEEDS PLAYER 2 IMPLEMETATION)
				if (active[i]->shotType == BLUE_SHOT)
				{
					App->player1->currentBlue -= 1;
				}

				if (active[i]->shotType == ORANGE_SHOT)
				{
					App->player1->currentOrange -= 1;;
				}

				if (active[i]->shotType == GREEN_SINGLE_SHOT)
				{
					App->player1->currentBlue -= 2;
				}

				// Carles Code <- THIS TRIGGERS THE CORRECT CONDITION
				if (active[i]->arrayId > -1)
				{
					int arrayIdMarker = active[i]->arrayId;

					//AddParticle(EnemyExplo, active[i]->position.x, active[i]->position.y); explosion needs to be here somewhere?

					for (uint j = 0; j < MAX_ACTIVE_PARTICLES; j++)
					{
						if (active[j] != nullptr && active[j]->arrayId == arrayIdMarker)
						{
							delete active[j];
							active[j] = nullptr;
						}
					}

					break;
				}
				// End Carles code
			}
			
			else if (c1->type == COLLIDER_PLAYER_SHOT && c2->type == COLLIDER_ENEMY)
			{

			}
			else if (c1->type == COLLIDER_ENEMY_SHOT || c2->type == COLLIDER_ENEMY_SHOT)
			{

			}

			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim),
	position(p.position),
	fPositionHorizontal(p.fPositionHorizontal),
	fPositionVertical(p.fPositionVertical),
	speed(p.speed),
	fx(p.fx),
	born(p.born),
	life(p.life),
	arrayId(p.arrayId)	// Carles edit
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;		// EXCEPTION THROWN CONSTANT BUGG HERE
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if (((int)SDL_GetTicks() - (int)born) > (int)life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;
	
	if (App->stage1->moveMapRight == true)
	{
		fPositionHorizontal += speed.x + App->stage1->ySpeedMultiplier * 0.82f;
	}

	else { fPositionHorizontal += speed.x; }

	if (App->stage1->moveMapDown == true)
		fPositionVertical += speed.y + App->stage1->ySpeedMultiplier * 0.82f;

	else if (App->stage1->moveMapUp == true)
		fPositionVertical += speed.y - App->stage1->ySpeedMultiplier * 0.82f;

	else { fPositionVertical += speed.y; }

	position.x = (int)fPositionHorizontal;
	position.y = (int)fPositionVertical;
	
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}