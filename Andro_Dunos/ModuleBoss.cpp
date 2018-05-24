#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleBoss.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Boss.h"
#include "ModuleMixer.h"

//Enemy types includes



#define SPAWN_MARGIN 50

ModuleBoss::ModuleBoss()
{
	for (uint i = 0; i < MAX_BOSS; ++i)
		Boss[i] = nullptr;
}

// Destructor
ModuleBoss::~ModuleBoss()
{

}

bool ModuleBoss::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Assets/Sprites/Enemies_and_projectiles/boss.png");

	explosion1 = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Enemy_Small_EXPLOSION.wav");
	explosion2 = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Enemy_Medium_EXPLOSION.wav");
	enemyHit = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Enemy_WHITE_SPRITE_Hit.wav");

	Mix_VolumeChunk(explosion1, FXVol);
	Mix_VolumeChunk(explosion2, FXVol);
	Mix_VolumeChunk(enemyHit, FXVol);

	return true;
}

update_status ModuleBoss::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_BOSS; ++i)
	{
		if (queue[i].type != BOSS_TYPES::YES_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnBoss(queue[i]);
				queue[i].type = BOSS_TYPES::YES_TYPE;
				//	LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleBoss::Update()
{
	for (uint i = 0; i < MAX_BOSS; ++i)
		if (Boss[i] != nullptr) Boss[i]->Move();

	for (uint i = 0; i < MAX_BOSS; ++i)
		if (Boss[i] != nullptr) Boss[i]->Draw(sprites);

	for (uint i = 0; i < MAX_BOSS; ++i)
		if (Boss[i] != nullptr) Boss[i]->Fire();

	return UPDATE_CONTINUE;
}

update_status ModuleBoss::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_BOSS; ++i)
	{
		if (Boss[i] != nullptr)
		{
			if (Boss[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				//	LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete Boss[i];
				Boss[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting

bool ModuleBoss::CleanUp()
{
	LOG("Freeing enemy texture");
	App->textures->Unload(sprites);
	sprites = nullptr;

	LOG("Feeing fx");
	App->mixer->UnloadFx(explosion1);
	App->mixer->UnloadFx(explosion2);
	App->mixer->UnloadFx(enemyHit);

	explosion1 = nullptr;
	explosion2 = nullptr;
	enemyHit = nullptr;

	LOG("Freeing all enemies");

	for (uint i = 0; i < MAX_BOSS; ++i)
	{
		if (Boss[i] != nullptr)
		{
			delete Boss[i];
			Boss[i] = nullptr;
		}

		queue[i].type = YES_TYPE;
		queue[i].x = 0;
		queue[i].y = 0;

	}

	return true;
}

bool ModuleBoss::AddBoss(BOSS_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_BOSS; ++i)
	{
		if (queue[i].type == BOSS_TYPES::YES_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleBoss::SpawnBoss(const BossInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; Boss[i] != nullptr && i < MAX_BOSS; ++i);

	if (i != MAX_BOSS)
	{
		//switch (info.type)
		//{
		///*case ENEMY_TYPES::GREYBALL_UP_DOWN:
		//	enemies[i] = new Enemy_13_Greyball(info.x, info.y);
		//	break;*/
		

		//}
	}
}

void ModuleBoss::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_BOSS; ++i)
	{
		if (Boss[i] != nullptr && Boss[i]->GetCollider() == c1)
		{
			if (Boss[i]->life > 1)	// When an enemy is hit, if it has more than 1 HP, one is substracted and the hit blit animation (should) plays
			{
				Boss[i]->life--;
				Mix_PlayChannel(-1, enemyHit, 0);
				break;
			}

			else	// if enemy has only 1 HP left, execute it's OnCollision function and destroy it
			{
				Boss[i]->OnCollision(c2);
				delete Boss[i];
				Boss[i] = nullptr;
				break;
			}
		}
	}
}
