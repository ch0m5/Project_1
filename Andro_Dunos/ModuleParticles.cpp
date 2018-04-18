#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

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
	/*graphics = App->textures->Load("Assets/Sprites/Players_Ships/laser_types.png");*/
	//explosionPtr = App->textures->Load("Assets/Sprites/Players_Ships/ship-explosion.png");
	shipExplosion = App->textures->Load("Assets/Sprites/Players_Ships/ship-explosion.png");
	enemyExplosion = App->textures->Load("Assets/Sprites/Common_level_elements/explosion_2.png");

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

	// Player Type 1 (blue)
	smallBlue.anim.PushBack({ 24, 39, 11, 4 });
	smallBlue.anim.loop = false;
	smallBlue.speed.x = 7.0f;
	smallBlue.life = shortLife;
	smallBlue.anim.speed = 0.3f;

	/*mediumBlue.anim.PushBack({ 24, 39, 11, 4 });
	mediumBlue.anim.loop = false;
	mediumBlue.speed.x = 7.0f;
	mediumBlue.life = 1200;
	mediumBlue.anim.speed = 0.3f;

	bigBlue.anim.PushBack({ 24, 39, 11, 4 });
	bigBlue.anim.loop = false;
	bigBlue.speed.x = 7.0f;
	bigBlue.life = 1200;
	bigBlue.anim.speed = 0.3f;*/
	
	//Player Type 2 (yellow)
	/*YellowBigRight.anim.PushBack({ 6, 69, 10, 3 });
	YellowBigRight.anim.loop = false;
	YellowBigRight.speed.x = 7.0f;
	YellowBigRight.life = 1200;
	YellowBigRight.anim.speed = 0.3f;

	YellowBigLeft.anim.PushBack({ 6, 69, 10, 3 });
	YellowBigLeft.anim.loop = false;
	YellowBigLeft.speed.x = 7.0f;
	YellowBigLeft.life = 1200;
	YellowBigLeft.anim.speed = 0.3f;

	yellowDown.anim.PushBack({ 6, 69, 10, 3 });
	yellowDown.anim.loop = false;
	yellowDown.speed.x = 7.0f;
	yellowDown.life = 1200;
	yellowDown.anim.speed = 0.3f;

	yellowUp.anim.PushBack({ 6, 69, 10, 3 });
	yellowUp.anim.loop = false;
	yellowUp.speed.x = 7.0f;
	yellowUp.life = 1200;
	yellowUp.anim.speed = 0.3f;*/

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

	/*upRightGreen.anim.PushBack({ 42, 87, 32 ,3 });
	upRightGreen.anim.loop = false;
	upRightGreen.speed.x = 7.0f;
	upRightGreen.life = 1200;
	upRightGreen.anim.speed = 0.3f;

	downRightGreen.anim.PushBack({ 42, 87, 32 ,3 });
	downRightGreen.anim.loop = false;
	downRightGreen.speed.x = 7.0f;
	downRightGreen.life = 1200;
	downRightGreen.anim.speed = 0.3f;*/

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
	arrowSuperUp2.anim.loop = false;
	arrowSuperUp2.speed.x = 7.0f;
	arrowSuperUp2.speed.y = -1.5f;
	arrowSuperUp2.life = shortLife;
	arrowSuperUp2.anim.speed = 0.5f;

	arrowUp2.anim.PushBack({ 41, 8, 13, 8 });
	arrowUp2.anim.PushBack({ 41, 22, 13, 8 });
	arrowUp2.anim.PushBack({ 41, 38, 13, 8 });
	arrowUp2.anim.loop = false;
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
	arrowDown2.anim.loop = false;
	arrowDown2.speed.x = 7.0f;
	arrowDown2.speed.y = 1.0f;
	arrowDown2.life = shortLife;
	arrowDown2.anim.speed = 0.5f;

	arrowSuperDown2.anim.PushBack({ 41, 8, 13, 8 });
	arrowSuperDown2.anim.PushBack({ 41, 22, 13, 8 });
	arrowSuperDown2.anim.PushBack({ 41, 38, 13, 8 });
	arrowSuperDown2.anim.loop = false;
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
	/*explosion.anim.PushBack({ 33, 66, 6, 6 });
	explosion.anim.PushBack({ 45, 64, 10, 8 });
	explosion.anim.PushBack({ 59, 56, 16, 16 });
	explosion.anim.PushBack({ 81, 58, 14, 14 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.2f;*/

	// @XaviMarin
	// Explosion ship 
	/*shipExplo.anim.PushBack({ 50, 35, 27, 17 });
	shipExplo.anim.PushBack({ 87, 34, 28, 18 });
	shipExplo.anim.PushBack({ 125, 31, 30, 21 });
	shipExplo.anim.PushBack({ 165, 27, 31, 25 });
	shipExplo.anim.PushBack({ 50, 63, 32, 27 });
	shipExplo.anim.PushBack({ 92, 59, 32, 31 });
	shipExplo.anim.PushBack({ 134, 57, 32, 32 });
	shipExplo.anim.PushBack({ 92, 105, 30, 30 });
	shipExplo.anim.PushBack({ 132, 110, 24, 15 });
	shipExplo.anim.PushBack({ 168, 114, 19, 11 });
	shipExplo.anim.PushBack({ 199, 116, 15, 9 });
	shipExplo.anim.loop = false;
	shipExplo.anim.speed = 0.2f;*/

	// Enemy explosion
	EnemyExplo.anim.PushBack({ 4, 25, 8, 8 });
	EnemyExplo.anim.PushBack({ 14, 19, 13, 15 });
	EnemyExplo.anim.PushBack({ 30, 8, 25, 25 });
	EnemyExplo.anim.PushBack({ 60, 7, 27, 26 });
	EnemyExplo.anim.PushBack({ 90, 4, 30, 29 });
	EnemyExplo.anim.PushBack({ 4, 40, 29, 28 });
	EnemyExplo.anim.PushBack({ 37, 40, 29, 28 });
	EnemyExplo.anim.PushBack({ 70, 41, 28, 27 });
	EnemyExplo.anim.PushBack({ 100, 43, 29, 27 });
	EnemyExplo.anim.PushBack({ 4, 75, 29, 27 });
	EnemyExplo.anim.PushBack({ 37, 77, 28, 26 });
	EnemyExplo.anim.PushBack({ 70, 78, 26, 24 });
	EnemyExplo.anim.PushBack({ 99, 80, 21, 21 });
	EnemyExplo.anim.PushBack({ 10, 108, 17, 17 });
	EnemyExplo.anim.PushBack({ 37, 116, 6, 6 });
	EnemyExplo.anim.loop = false;
	EnemyExplo.anim.speed = 0.4f;


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	//App->textures->Unload(shipExplosion);
	App->textures->Unload(enemyExplosion);

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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = p->fPositionHorizontal = x + App->render->camera.x / SCREEN_SIZE;
			p->position.y = p->fPositionVertical = y + App->render->camera.y / SCREEN_SIZE;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::AddParticleArray(const Particle* colliderArray, int arraySize, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	uint i;

	for (i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			bool enoughSpace = true;

			for (int j = i; j < arraySize; j++)
			{
				if (j >= MAX_ACTIVE_PARTICLES || active[j] != nullptr)
				{
					enoughSpace = false;
					break;
				}
			}

			if (enoughSpace == true)
			{
				Particle* p = new Particle[arraySize];

				for (int j = i; j < arraySize; j++)
				{
					if (j >= MAX_ACTIVE_PARTICLES)
						j = 0;

					(p + j)->born = SDL_GetTicks() + delay;
					(p + j)->position.x = (p + j)->fPositionHorizontal = x;
					(p + j)->position.y = (p + j)->fPositionVertical = y;
					if (collider_type != COLLIDER_NONE)
						(p + j)->collider = App->collision->AddCollider((p + j)->anim.GetCurrentFrame(), collider_type, this);
					active[i] = (p + j);

					j++;
				}

				break;
			}
		}
	}
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
			}
			else if (c1->type == COLLIDER_PLAYER_SHOT && c2->type == COLLIDER_ENEMY) 
			{
				AddParticle(EnemyExplo, active[i]->position.x, active[i]->position.y);
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
	life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;
	
	fPositionHorizontal += speed.x;
	fPositionVertical += speed.y;

	position.x = (int)fPositionHorizontal;
	position.y = (int)fPositionVertical;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}