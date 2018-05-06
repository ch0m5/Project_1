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
#include "NewPath.h"

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
	// Particle life values
	shortLife = 1000;
	mediumLife = 2000;
	longLife = 3000;

	// List of Ids needed to delete the full particle array
	arrayIdList = 0;

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
	//smallBlue.particlePath.PushBack({ -1, 0 }, 125);

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

	/* Missile sprites
	/	39, 158, 13, 9
	/	39, 173, 13, 9

	-	39, 142, 13, 9
	-	38, 127, 13, 9

	\	39, 113, 13, 9
	\	39, 98, 13, 9
	*/

	missileSuperUp.anim.PushBack({ 39, 158, 13, 9 });
	missileSuperUp.anim.PushBack({ 39, 173, 13, 9 });
	missileSuperUp.anim.loop = true;
	missileSuperUp.speed.x = 1.0f;
	missileSuperUp.speed.y = -5.0f;
	missileSuperUp.life = mediumLife;
	missileSuperUp.anim.speed = 0.1f;

	missileUp.anim.PushBack({ 39, 158, 13, 9 });
	missileUp.anim.PushBack({ 39, 173, 13, 9 });
	missileUp.anim.loop = true;
	missileUp.speed.x = 6.0f;
	missileUp.speed.y = -5.0f;
	missileUp.life = mediumLife;
	missileUp.anim.speed = 0.1f;

	missileDown.anim.PushBack({ 39, 113, 13, 9 });
	missileDown.anim.PushBack({ 39, 98, 13, 9 });
	missileDown.anim.loop = true;
	missileDown.speed.x = 6.0f;
	missileDown.speed.y = 5.0f;
	missileDown.life = mediumLife;
	missileDown.anim.speed = 0.1f;

	missileSuperDown.anim.PushBack({ 39, 113, 13, 9 });
	missileSuperDown.anim.PushBack({ 39, 98, 13, 9 });
	missileSuperDown.anim.loop = true;
	missileSuperDown.speed.x = 1.0f;
	missileSuperDown.speed.y = 5.0f;
	missileSuperDown.life = mediumLife;
	missileSuperDown.anim.speed = 0.1f;

	// Weapon
	blueWeapon.anim.PushBack({ 127, 123, 41, 18 });
	blueWeapon.anim.PushBack({ 174, 123, 63, 18 });
	blueWeapon.anim.loop = false;
	blueWeapon.speed.x = 7.0f;
	blueWeapon.speed.y = 0.0f;
	blueWeapon.life = mediumLife;
	blueWeapon.anim.speed = 0.3f;

	//Player Type 2 (yellow)
	yellowBigRight.anim.PushBack({ 3, 8, 15, 5 });
	yellowBigRight.anim.loop = false;
	yellowBigRight.speed.x = 7.0f;
	yellowBigRight.life = shortLife;
	yellowBigRight.anim.speed = 0.3f;
	
	yellowBigLeft.anim.PushBack({ 3, 23, 15, 5 });
	yellowBigLeft.anim.loop = false;
	yellowBigLeft.speed.x = -7.0f;
	yellowBigLeft.life = shortLife;
	yellowBigLeft.anim.speed = 0.3f;
	
	yellowSmallDown.anim.PushBack({ 24, 79, 8, 6 });
	yellowSmallDown.anim.loop = false;
	yellowSmallDown.speed.x = -5.0f;
	yellowSmallDown.speed.y = 2.0f;
	yellowSmallDown.life = shortLife;
	yellowSmallDown.anim.speed = 0.3f;
	
	yellowSmallUp.anim.PushBack({ 24, 68, 8, 6 });
	yellowSmallUp.anim.loop = false;
	yellowSmallUp.speed.x = -5.0f;
	yellowSmallUp.speed.y = -2.0f;
	yellowSmallUp.life = shortLife;
	yellowSmallUp.anim.speed = 0.3f;

	yellowBigDown.anim.PushBack({ 5, 37, 11, 8 });
	yellowBigDown.anim.loop = false;
	yellowBigDown.speed.x = -5.0f;
	yellowBigDown.speed.y = 2.0f;
	yellowBigDown.life = shortLife;
	yellowBigDown.anim.speed = 0.3f;

	yellowBigUp.anim.PushBack({ 5, 50, 11, 8 });
	yellowBigUp.anim.loop = false;
	yellowBigUp.speed.x = -5.0f;
	yellowBigUp.speed.y = -2.0f;
	yellowBigUp.life = shortLife;
	yellowBigUp.anim.speed = 0.3f;

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
	
	redRocketDown.anim.PushBack({ 2, 99, 16, 9 });
	redRocketDown.anim.PushBack({ 1, 113, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 129, 16, 9 });
	redRocketDown.anim.PushBack({ 4, 142, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 158, 16, 9 });
	redRocketDown.anim.PushBack({ 2, 173, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 188, 16, 9 });
	redRocketDown.anim.PushBack({ 4, 202, 16, 9 });
	redRocketDown.anim.loop = true;
	redRocketDown.speed.x = 0.0f;
	redRocketDown.speed.y = 2.0f;
	redRocketDown.life = mediumLife;
	redRocketDown.anim.speed = 0.7f;

	redRocketUp.anim.PushBack({ 2, 99, 16, 9 });
	redRocketUp.anim.PushBack({ 1, 113, 16, 9 });
	redRocketUp.anim.PushBack({ 3, 129, 16, 9 });
	redRocketUp.anim.PushBack({ 4, 142, 16, 9 });
	redRocketUp.anim.PushBack({ 3, 158, 16, 9 });
	redRocketUp.anim.PushBack({ 2, 173, 16, 9 });
	redRocketUp.anim.PushBack({ 3, 188, 16, 9 });
	redRocketUp.anim.PushBack({ 4, 202, 16, 9 });
	redRocketUp.anim.loop = true;
	redRocketUp.speed.x = 0.0f;
	redRocketUp.speed.y = -2.0f;
	redRocketUp.life = mediumLife;
	redRocketUp.anim.speed = 0.7f;

	redRocketLeftDown.anim.PushBack({ 22, 99, 16, 9 });
	redRocketLeftDown.anim.PushBack({ 21, 113, 16, 9 });
	redRocketLeftDown.anim.PushBack({ 23, 129, 16, 9 });
	redRocketLeftDown.anim.PushBack({ 24, 142, 16, 9 });
	redRocketLeftDown.anim.PushBack({ 23, 158, 16, 9 });
	redRocketLeftDown.anim.PushBack({ 22, 173, 16, 9 });
	redRocketLeftDown.anim.PushBack({ 23, 188, 16, 9 });
	redRocketLeftDown.anim.PushBack({ 24, 202, 16, 9 });
	redRocketLeftDown.anim.loop = true;
	redRocketLeftDown.speed.x = 0.0f;
	redRocketLeftDown.speed.y = 2.0f;
	redRocketLeftDown.life = mediumLife;
	redRocketLeftDown.anim.speed = 0.7f;

	redRocketLeftUp.anim.PushBack({ 22, 99, 16, 9 });
	redRocketLeftUp.anim.PushBack({ 21, 113, 16, 9 });
	redRocketLeftUp.anim.PushBack({ 23, 129, 16, 9 });
	redRocketLeftUp.anim.PushBack({ 24, 142, 16, 9 });
	redRocketLeftUp.anim.PushBack({ 23, 158, 16, 9 });
	redRocketLeftUp.anim.PushBack({ 22, 173, 16, 9 });
	redRocketLeftUp.anim.PushBack({ 23, 188, 16, 9 });
	redRocketLeftUp.anim.PushBack({ 24, 202, 16, 9 });
	redRocketLeftUp.anim.loop = true;
	redRocketLeftUp.speed.x = 0.0f;
	redRocketLeftUp.speed.y = -2.0f;
	redRocketLeftUp.life = mediumLife;
	redRocketLeftUp.anim.speed = 0.7f;

	redRocketDownDiagonal.anim.PushBack({ 2, 99, 16, 9 });
	redRocketDownDiagonal.anim.PushBack({ 1, 113, 16, 9 });
	redRocketDownDiagonal.anim.PushBack({ 3, 129, 16, 9 });
	redRocketDownDiagonal.anim.PushBack({ 4, 142, 16, 9 });
	redRocketDownDiagonal.anim.PushBack({ 3, 158, 16, 9 });
	redRocketDownDiagonal.anim.PushBack({ 2, 173, 16, 9 });
	redRocketDownDiagonal.anim.PushBack({ 3, 188, 16, 9 });
	redRocketDownDiagonal.anim.PushBack({ 4, 202, 16, 9 });
	redRocketDownDiagonal.anim.loop = true;
	redRocketDownDiagonal.speed.x = 2.0f;
	redRocketDownDiagonal.speed.y = 2.0f;
	redRocketDownDiagonal.life = mediumLife;
	redRocketDownDiagonal.anim.speed = 0.7f;

	redRocketUpDiagonal.anim.PushBack({ 2, 99, 16, 9 });
	redRocketUpDiagonal.anim.PushBack({ 1, 113, 16, 9 });
	redRocketUpDiagonal.anim.PushBack({ 3, 129, 16, 9 });
	redRocketUpDiagonal.anim.PushBack({ 4, 142, 16, 9 });
	redRocketUpDiagonal.anim.PushBack({ 3, 158, 16, 9 });
	redRocketUpDiagonal.anim.PushBack({ 2, 173, 16, 9 });
	redRocketUpDiagonal.anim.PushBack({ 3, 188, 16, 9 });
	redRocketUpDiagonal.anim.PushBack({ 4, 202, 16, 9 });
	redRocketUpDiagonal.anim.loop = true;
	redRocketUpDiagonal.speed.x = 2.0f;
	redRocketUpDiagonal.speed.y = -2.0f;
	redRocketUpDiagonal.life = mediumLife;
	redRocketUpDiagonal.anim.speed = 0.7f;

	Weapon2RightUp.anim.PushBack({ 149, 151, 28, 28 });
	Weapon2RightUp.anim.PushBack({ 181, 182, 28, 28 });
	Weapon2RightUp.anim.PushBack({ 180, 151, 28, 28 });
	Weapon2RightUp.anim.PushBack({ 146, 182, 28, 28 });
	Weapon2RightUp.anim.loop = true;
	Weapon2RightUp.speed.x = 10.0f;
	Weapon2RightUp.speed.y = -4.0f;
	Weapon2RightUp.life = shortLife;
	Weapon2RightUp.anim.speed = 0.7f;

	Weapon2RightDown.anim.PushBack({ 149, 151, 28, 28 });
	Weapon2RightDown.anim.PushBack({ 181, 182, 28, 28 });
	Weapon2RightDown.anim.PushBack({ 180, 151, 28, 28 });
	Weapon2RightDown.anim.PushBack({ 146, 182, 28, 28 });
	Weapon2RightDown.anim.loop = true;
	Weapon2RightDown.speed.x = 10.0f;
	Weapon2RightDown.speed.y = 4.0f;
	Weapon2RightDown.life = shortLife;
	Weapon2RightDown.anim.speed = 0.7f;

	Weapon2LeftSuperUp.anim.PushBack({ 149, 151, 28, 28 });
	Weapon2LeftSuperUp.anim.PushBack({ 181, 182, 28, 28 });
	Weapon2LeftSuperUp.anim.PushBack({ 180, 151, 28, 28 });
	Weapon2LeftSuperUp.anim.PushBack({ 146, 182, 28, 28 });
	Weapon2LeftSuperUp.anim.loop = true;
	Weapon2LeftSuperUp.speed.x = -10.0f;
	Weapon2LeftSuperUp.speed.y = -7.0f;
	Weapon2LeftSuperUp.life = shortLife;
	Weapon2LeftSuperUp.anim.speed = 0.7f;

	Weapon2LeftUp.anim.PushBack({ 149, 151, 28, 28 });
	Weapon2LeftUp.anim.PushBack({ 181, 182, 28, 28 });
	Weapon2LeftUp.anim.PushBack({ 180, 151, 28, 28 });
	Weapon2LeftUp.anim.PushBack({ 146, 182, 28, 28 });
	Weapon2LeftUp.anim.loop = true;
	Weapon2LeftUp.speed.x = -10.0f;
	Weapon2LeftUp.speed.y = -4.0f;
	Weapon2LeftUp.life = shortLife;
	Weapon2LeftUp.anim.speed = 0.7f;

	Weapon2LeftStraight.anim.PushBack({ 149, 151, 28, 28 });
	Weapon2LeftStraight.anim.PushBack({ 181, 182, 28, 28 });
	Weapon2LeftStraight.anim.PushBack({ 180, 151, 28, 28 });
	Weapon2LeftStraight.anim.PushBack({ 146, 182, 28, 28 });
	Weapon2LeftStraight.anim.loop = true;
	Weapon2LeftStraight.speed.x = -10.0f;
	Weapon2LeftStraight.speed.y = 0.0f;
	Weapon2LeftStraight.life = shortLife;
	Weapon2LeftStraight.anim.speed = 0.7f;

	Weapon2LeftDown.anim.PushBack({ 149, 151, 28, 28 });
	Weapon2LeftDown.anim.PushBack({ 181, 182, 28, 28 });
	Weapon2LeftDown.anim.PushBack({ 180, 151, 28, 28 });
	Weapon2LeftDown.anim.PushBack({ 146, 182, 28, 28 });
	Weapon2LeftDown.anim.loop = true;
	Weapon2LeftDown.speed.x = -10.0f;
	Weapon2LeftDown.speed.y = 4.0f;
	Weapon2LeftDown.life = shortLife;
	Weapon2LeftDown.anim.speed = 0.7f;

	Weapon2LeftSuperDown.anim.PushBack({ 149, 151, 28, 28 });
	Weapon2LeftSuperDown.anim.PushBack({ 181, 182, 28, 28 });
	Weapon2LeftSuperDown.anim.PushBack({ 180, 151, 28, 28 });
	Weapon2LeftSuperDown.anim.PushBack({ 146, 182, 28, 28 });
	Weapon2LeftSuperDown.anim.loop = true;
	Weapon2LeftSuperDown.speed.x = -10.0f;
	Weapon2LeftSuperDown.speed.y = 7.0f;
	Weapon2LeftSuperDown.life = shortLife;
	Weapon2LeftSuperDown.anim.speed = 0.7f;

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
	SetParticleArray(downRightGreen3, 8, 114, 46, 4, 12, 4, 4, 4.0f, 4.0f, shortLife);
	SetParticleArray(upLeftGreen3, 8, 108, 34, 4, 12, -4, -4, -4.0f, -4.0f, shortLife);
	SetParticleArray(downLeftGreen3, 8, 108, 46, 4, 12, -4, 4, -4.0f, 4.0f, shortLife);
	
	SetParticleArray(upRightGreen4, 2, 215, 40, 12, 18, 12, -10, 4.0f, -4.0f, shortLife);
	SetParticleArray(downRightGreen4, 2, 216, 59, 18, 12, 10, 12, 4.0f, 4.0f, shortLife);
	SetParticleArray(upLeftGreen4, 2, 196, 47, 18, 12, -10, -12, -4.0f, -4.0f, shortLife);
	SetParticleArray(downLeftGreen4, 2, 203, 60, 12, 18, -12, 10, -4.0f, 4.0f, shortLife);

	SetParticleArray(upRightGreen5, 4, 215, 40, 12, 18, 12, -10, 4.0f, -4.0f, shortLife);
	SetParticleArray(downRightGreen5, 4, 216, 59, 18, 12, 10, 12, 4.0f, 4.0f, shortLife);
	SetParticleArray(upLeftGreen5, 4, 196, 47, 18, 12, -10, -12, -4.0f, -4.0f, shortLife);
	SetParticleArray(downLeftGreen5, 4, 203, 60, 12, 18, -12, 10, -4.0f, 4.0f, shortLife);

	bombRightDown.anim.PushBack({ 121, 113, 8, 9 });
	bombRightDown.anim.loop = false;
	bombRightDown.speed.x = 3.0f;
	bombRightDown.speed.y = 6.0f;
	bombRightDown.life = shortLife;
	bombRightDown.anim.speed = 0.5f;

	bombRightUp.anim.PushBack({ 121, 98, 8, 9 });
	bombRightUp.anim.loop = false;
	bombRightUp.speed.x = 3.0f;
	bombRightUp.speed.y = -6.0f;
	bombRightUp.life = shortLife;
	bombRightUp.anim.speed = 0.5f;

	bombLeftDown.anim.PushBack({ 121, 113, 8, 9 });
	bombLeftDown.anim.loop = false;
	bombLeftDown.speed.x = -3.0f;
	bombLeftDown.speed.y = 6.0f;
	bombLeftDown.life = shortLife;
	bombLeftDown.anim.speed = 0.5f;

	bombLeftUp.anim.PushBack({ 121, 98, 8, 9 });
	bombLeftUp.anim.loop = false;
	bombLeftUp.speed.x = -3.0f;
	bombLeftUp.speed.y = -6.0f;
	bombLeftUp.life = shortLife;
	bombLeftUp.anim.speed = 0.5f;

	//Player Type 4 (white)
	arrowUp1.anim.PushBack({ 41, 9, 13, 6 });
	arrowUp1.anim.PushBack({ 41, 23, 13, 6 });
	arrowUp1.anim.loop = false;
	arrowUp1.speed.x = 7.0f;
	arrowUp1.speed.y = -0.6f;
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
	arrowDown1.speed.y = 0.6f;
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
	arrowSuperUp3.anim.PushBack({ 41, 48, 13, 14 });
	arrowSuperUp3.anim.PushBack({ 41, 64, 13, 14 });
	arrowSuperUp3.anim.loop = false;
	arrowSuperUp3.speed.x = 7.0f;
	arrowSuperUp3.speed.y = -1.5;
	arrowSuperUp3.life = shortLife;
	arrowSuperUp3.anim.speed = 0.5f;

	arrowUp3.anim.PushBack({ 41, 5, 13, 14 });
	arrowUp3.anim.PushBack({ 41, 19, 13, 14 });
	arrowUp3.anim.PushBack({ 41, 35, 13, 14 });
	arrowUp3.anim.PushBack({ 41, 48, 13, 14 });
	arrowUp3.anim.PushBack({ 41, 64, 13, 14 });
	arrowUp3.anim.loop = false;
	arrowUp3.speed.x = 7.0f;
	arrowUp3.speed.y = -1.0f;
	arrowUp3.life = shortLife;
	arrowUp3.anim.speed = 0.5f;

	arrowStraight3.anim.PushBack({ 41, 5, 13, 14 });
	arrowStraight3.anim.PushBack({ 41, 19, 13, 14 });
	arrowStraight3.anim.PushBack({ 41, 35, 13, 14 });
	arrowStraight3.anim.PushBack({ 41, 48, 13, 14 });
	arrowStraight3.anim.PushBack({ 41, 64, 13, 14 });
	arrowStraight3.anim.loop = false;
	arrowStraight3.speed.x = 7.0f;
	arrowStraight3.life = shortLife;
	arrowStraight3.anim.speed = 0.5f;

	arrowDown3.anim.PushBack({ 41, 5, 13, 14 });
	arrowDown3.anim.PushBack({ 41, 19, 13, 14 });
	arrowDown3.anim.PushBack({ 41, 35, 13, 14 });
	arrowDown3.anim.PushBack({ 41, 48, 13, 14 });
	arrowDown3.anim.PushBack({ 41, 64, 13, 14 });
	arrowDown3.anim.loop = false;
	arrowDown3.speed.x = 7.0f;
	arrowDown3.speed.y = 1.0f;
	arrowDown3.life = shortLife;
	arrowDown3.anim.speed = 0.5f;

	arrowSuperDown3.anim.PushBack({ 41, 5, 13, 14 });
	arrowSuperDown3.anim.PushBack({ 41, 19, 13, 14 });
	arrowSuperDown3.anim.PushBack({ 41, 35, 13, 14 });
	arrowSuperDown3.anim.PushBack({ 41, 48, 13, 14 });
	arrowSuperDown3.anim.PushBack({ 41, 64, 13, 14 });
	arrowSuperDown3.anim.loop = false;
	arrowSuperDown3.speed.x = 7.0f;
	arrowSuperDown3.speed.y = 1.5f;
	arrowSuperDown3.life = shortLife;
	arrowSuperDown3.anim.speed = 0.5f;

	// Orange Power
	laserUp.anim.PushBack({ 63, 11, 3, 16 });
	laserUp.anim.loop = false;
	laserUp.speed.x = 0.0f;
	laserUp.speed.y = -4.0f;
	laserUp.life = shortLife;
	laserUp.anim.speed = 0.5f;

	laserDown.anim.PushBack({ 63, 11, 3, 16 });
	laserDown.anim.loop = false;
	laserDown.speed.x = 0.0f;
	laserDown.speed.y = 4.0f;
	laserDown.life = shortLife;
	laserDown.anim.speed = 0.5f;
	//Particle* downRightGreen = nullptr;	// Reusing particles (keep commented)
	//Particle* upRightGreen = nullptr;

	//Enemy laser
	enemyBlueShot.anim.PushBack({ 238, 161, 6, 6 });
	enemyBlueShot.anim.PushBack({ 238, 169, 8, 6 });
	enemyBlueShot.anim.PushBack({ 246, 161, 6, 6 });
	enemyBlueShot.anim.PushBack({ 239, 177, 6, 8 });
	enemyBlueShot.anim.loop = true;
	enemyBlueShot.anim.speed = 0.6f;
	enemyBlueShot.speed.x = -3.0f;
	enemyBlueShot.life = longLife;


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
	explosion.anim.speed = 1.5f;
	explosion.anim.Finished();

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
	explosion1.anim.speed = 1.5f;
	explosion1.anim.Finished();

	explosion2.anim.PushBack({ 509, 137, 6, 6 });
	explosion2.anim.PushBack({ 521, 135, 10, 8 });
	explosion2.anim.PushBack({ 535, 127, 16, 16 });
	explosion2.anim.PushBack({ 557, 129, 14, 14 });
	explosion2.anim.loop = false;
	explosion2.anim.speed = 1.5f;
	explosion2.anim.Finished();




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
			if (p->arrayId > -1)	//ATTEMPT OF ELIMIATING ARRAYS
			{
				if (p->shotType == PLAYER_1_ARRAY_SHOT)
				{
					App->player1->currentArrayShots -= 1;
				}

				else if (p->shotType == PLAYER_1_ORANGE_SHOT)
				{
					App->player1->currentOrange -= 1;
				}

				else if (p->shotType == PLAYER_2_ARRAY_SHOT)
				{
					App->player2->currentArrayShots -= 1;
				}

				else if (p->shotType == PLAYER_2_ORANGE_SHOT)
				{
					App->player2->currentOrange -= 1;
				}

				int arrayIdMarker = p->arrayId;

				for (uint j = 0; j < MAX_ACTIVE_PARTICLES; j++)
				{
					if (active[j] != nullptr && active[j]->arrayId == arrayIdMarker)
					{
						delete active[j];
						active[j] = nullptr;
					}
				}

				continue;
			}

			if (p->shotType == PLAYER_1_BLUE_SHOT)
			{
				App->player1->currentBlue -= 1;
			}

			else if (p->shotType == PLAYER_1_GREEN_SINGLE_SHOT)
			{
				App->player1->currentBlue -= 2;
			}

			else if (p->shotType == PLAYER_1_ORANGE_SHOT)
			{
				App->player1->currentOrange -= 1;
			}

			else if (p->shotType == PLAYER_1_MULTIPLE_SHOT)
			{
				App->player1->currentMultipleShots -= 1;
			}

			else if (p->shotType == PLAYER_2_BLUE_SHOT)
			{
				App->player2->currentBlue -= 1;
			}

			else if (p->shotType == PLAYER_2_GREEN_SINGLE_SHOT)
			{
				App->player2->currentBlue -= 2;
			}

			else if (p->shotType == PLAYER_2_ORANGE_SHOT)
			{
				App->player2->currentOrange -= 1;
			}

			else if (p->shotType == PLAYER_2_MULTIPLE_SHOT)
			{
				App->player2->currentMultipleShots -= 1;
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
			p->position.x = (int)p->fPositionHorizontal;
			p->position.y = (int)p->fPositionVertical;
			p->shotType = shotType;
			if (collider_type == COLLIDER_PLAYER_SHOT || collider_type == COLLIDER_PLAYER_2_SHOT)
			{
				p->fPositionHorizontal = x + App->render->camera.x / SCREEN_SIZE;
				p->fPositionVertical = y + App->render->camera.y / SCREEN_SIZE;
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			}

			else if (collider_type != COLLIDER_NONE)
			{
				p->fPositionHorizontal = x;
				p->fPositionVertical = y;
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			}
				
			else
			{
				p->fPositionHorizontal = x;
				p->fPositionVertical = y;
			}

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
				p->arraySize = arraySize;
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

				if (active[i]->arrayId > -1)
				{
					if (active[i]->shotType == PLAYER_1_ARRAY_SHOT)
					{
						App->player1->currentArrayShots -= 1;
					}

					else if (active[i]->shotType == PLAYER_1_ORANGE_SHOT)
					{
						App->player1->currentOrange -= 1;
					}

					else if (active[i]->shotType == PLAYER_2_ARRAY_SHOT)
					{
						App->player2->currentArrayShots -= 1;
					}

					else if (active[i]->shotType == PLAYER_2_ORANGE_SHOT)
					{
						App->player2->currentOrange -= 1;
					}

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
				
				if (active[i]->shotType == PLAYER_1_BLUE_SHOT)
				{
					App->player1->currentBlue -= 1;
				}

				else if (active[i]->shotType == PLAYER_1_GREEN_SINGLE_SHOT)
				{
					App->player1->currentBlue -= 2;
				}

				else if (active[i]->shotType == PLAYER_1_ORANGE_SHOT)
				{
					App->player1->currentOrange -= 1;
				}

				else if (active[i]->shotType == PLAYER_1_MULTIPLE_SHOT)
				{
					App->player1->currentMultipleShots -= 1;
				}

				else if (active[i]->shotType == PLAYER_2_BLUE_SHOT)
				{
					App->player2->currentBlue -= 1;
				}

				else if (active[i]->shotType == PLAYER_2_GREEN_SINGLE_SHOT)
				{
					App->player2->currentBlue -= 2;
				}

				else if (active[i]->shotType == PLAYER_2_ORANGE_SHOT)
				{
					App->player2->currentOrange -= 1;
				}

				else if (active[i]->shotType == PLAYER_2_MULTIPLE_SHOT)
				{
					App->player2->currentMultipleShots -= 1;
				}
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
	arrayId(p.arrayId),
	shotType(p.shotType),
	arraySize(p.arraySize),	// carles edit
	particlePath(p.particlePath)	// carles edit
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
	
	else if (anim.Finished())	// carles edit (else was above the if, i didn't like it)
		ret = false;
	
	if (position.x > App->render->camera.x / SCREEN_SIZE + SCREEN_WIDTH)	// carles edit, bullets outside the screen will die
		ret = false;
	
	if (App->stage1->moveMapRight == true)
	{
		fPositionHorizontal += speed.x + App->stage1->ySpeedMultiplier * 0.86f;
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