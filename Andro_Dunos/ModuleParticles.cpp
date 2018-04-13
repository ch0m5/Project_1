#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
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
	//explosionPtr = App->textures->Load("Assets/Sprites/Common_level_elements.png");
	
	/* Laser Sprites

	Type 1:
	21, 6, 16, 10	big
	24, 39, 11, 4	small
	22, 51, 15, 6	medium

	Type 2:
	3, 8, 15, 5		right
	3, 23, 15, 5	left
	5, 37, 11, 8	down left
	5, 50, 11, 8	up left
	6, 69, 10, 3	small right
	6, 84, 10, 3	small left

	Type 3:
	63, 11, 3, 16	|
	57, 35, 16, 18	/
	57, 60, 16, 18	\
	42, 87, 32 ,3   --

	76, y

	94, y

	Type 4:
	41, 5, 13, 14	1
	41, 19, 13, 14	2
	41, 35, 13, 14	3
	41, 48, 13, 14	4
	41, 64, 13, 14	5

	*/

	// Player blue laser
	smallBlue.anim.PushBack({ 24, 39, 11, 4 });
	smallBlue.anim.loop = false;
	smallBlue.speed.x = 7.0f;
	smallBlue.life = 1200;
	smallBlue.anim.speed = 0.3f;

	//Player Type 2 laser yellow @Andres
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

	//Player Type 3 laser green
	straightGreen.anim.PushBack({ 42, 87, 32 ,3 });
	straightGreen.anim.loop = false;
	straightGreen.speed.x = 7.0f;
	straightGreen.life = 1200;
	straightGreen.anim.speed = 0.3f;

	//Player Laser Type 4 white
	arrow1.anim.PushBack({ 41, 5, 13, 14 });
	arrow1.anim.PushBack({ 41, 19, 13, 14 });
	arrow1.anim.PushBack({ 41, 35, 13, 14 });
	arrow1.anim.loop = false;
	arrow1.speed.x = 7.0f;
	arrow1.speed.y = 1.0f;
	arrow1.life = 1200;
	arrow1.anim.speed = 0.5f;

	arrow2.anim.PushBack({ 41, 5, 13, 14 });
	arrow2.anim.PushBack({ 41, 19, 13, 14 });
	arrow2.anim.PushBack({ 41, 35, 13, 14 });
	arrow2.anim.loop = false;
	arrow2.speed.x = 7.0f;
	arrow2.speed.y = -1.0f;
	arrow2.life = 1200;
	arrow2.anim.speed = 0.5f;

		//---------------------------
	// Explosion particle // @Andres
	/*explosion.anim.PushBack({ 33, 66, 6, 6 });
	explosion.anim.PushBack({ 45, 64, 10, 8 });
	explosion.anim.PushBack({ 59, 56, 16, 16 });
	explosion.anim.PushBack({ 81, 58, 14, 14 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.2f;*/

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
			if (c2->type == COLLIDER_WALL)
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