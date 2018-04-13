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
	graphics = App->textures->Load("Assets/Sprites/Players_Ships/laser_types.png");
	explosionPtr = App->textures->Load("Assets/Sprites/Common_level_elements.png");

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
	smallBlue.life = 1200;
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
	yellowSmallRight.life = 1200;
	yellowSmallRight.anim.speed = 0.3f;

	yellowSmallLeft.anim.PushBack({ 6, 84, 10, 3 });
	yellowSmallLeft.anim.loop = false;
	yellowSmallLeft.speed.x = -7.0f;
	yellowSmallLeft.life = 1200;
	yellowSmallLeft.anim.speed = 0.3f;

	//Player Type 3 (green)
	straightGreen.anim.PushBack({ 42, 87, 32, 3 });
	straightGreen.anim.loop = false;
	straightGreen.speed.x = 7.0f;
	straightGreen.life = 1200;
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

	//Player Type 4 (white)
	arrowUp1.anim.PushBack({ 41, 9, 13, 6 });
	arrowUp1.anim.PushBack({ 41, 23, 13, 6 });
	arrowUp1.anim.loop = false;
	arrowUp1.speed.x = 7.0f;
	arrowUp1.speed.y = -1.0f;
	arrowUp1.life = 1200;
	arrowUp1.anim.speed = 0.5f;

	arrowDown1.anim.PushBack({ 41, 9, 13, 6 });
	arrowDown1.anim.PushBack({ 41, 23, 13, 6 });
	arrowDown1.anim.loop = false;
	arrowDown1.speed.x = 7.0f;
	arrowDown1.speed.y = 1.0f;
	arrowDown1.life = 1200;
	arrowDown1.anim.speed = 0.5f;

	// Explosion particle // @Andres
	explosion.anim.PushBack({ 33, 66, 6, 6 });
	explosion.anim.PushBack({ 45, 64, 10, 8 });
	explosion.anim.PushBack({ 59, 56, 16, 16 });
	explosion.anim.PushBack({ 81, 58, 14, 14 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.2f;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	App->textures->Unload(explosionPtr);

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
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
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
			if (c2->type == COLLIDER_WALL) // Should be collider enemy
			{
				AddParticle(explosion, active[i]->position.x, active[i]->position.y);
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
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
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

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}