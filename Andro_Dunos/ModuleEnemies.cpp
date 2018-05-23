#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "ModuleMixer.h"

//Enemy types includes
#include "Enemy_13_Greyball.h"
#include "RedLineShip_Enemy.h"
#include "BigGrey_Enemy.h"
#include "PowerUp_Enemy.h"
#include "GreyYellow_Enemy.h"
#include "PowerUp_Bonus.h"
#include "Enemy_GreyBall_S.h"
#include "Greyball_K.h"
#include "GreyYellow_Enemy_Up.h"
#include "GreyYellow_Enemy_Down.h"
#include "Shuriken_Enemy.h"
#include "silver_round.h"
#include "silver_round_down.h"
#include "Down_WhiteOrangeTurret.h"
#include "Down_WhiteOrangeTurret.h"
#include "Drill_Down.h"
#include "Drill_Up.h"
#include "Greyball_Circle.h"
#include "GreyYellow_Enemy_Right_Up.h"
#include "GreyYellow_Enemy_Right_Down.h"


#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Assets/Sprites/Enemies_and_projectiles/table_enemy_goodone.png");

	explosion1 = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Enemy_Small_EXPLOSION.wav");
	explosion2 = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Enemy_Medium_EXPLOSION.wav");
	enemyHit = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Enemy_WHITE_SPRITE_Hit.wav");

	Mix_VolumeChunk(explosion1, FXVol);
	Mix_VolumeChunk(explosion2, FXVol);
	Mix_VolumeChunk(enemyHit, FXVol);
	
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
			//	LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Fire();

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
			//	LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting

bool ModuleEnemies::CleanUp()
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

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
 		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		
		queue[i].type = NO_TYPE;
		queue[i].x = 0;
		queue[i].y = 0;

	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
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

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::GREYBALL_UP_DOWN:
			enemies[i] = new Enemy_13_Greyball(info.x, info.y);
			break;
		case ENEMY_TYPES::REDLINE_SHIP:
			enemies[i] = new RedLineShip_Enemy(info.x, info.y);
			break;
		case ENEMY_TYPES::POWERUP_ENEMY:
			enemies[i] = new PowerUp_Enemy(info.x, info.y);
			break;
		case ENEMY_TYPES::BIGGREY_ENEMY:
			enemies[i] = new BigGrey_Enemy(info.x, info.y);
			break;
		case ENEMY_TYPES::GREY_YELLOW_SHIP:
			enemies[i] = new GreyYellow_Enemy(info.x, info.y);
			break;
		case ENEMY_TYPES::POWERUP_BONUS:
			enemies[i] = new PowerUp_Bonus(info.x, info.y);
			break;
		case ENEMY_TYPES::GREYBALL_S:
			enemies[i] = new Enemy_Greyball_S(info.x, info.y);
			break;
		case ENEMY_TYPES::GREYBALL_K:
			enemies[i] = new Enemy_Greyball_K(info.x, info.y);
			break;
		case ENEMY_TYPES::YELLOWSHIP_UP:
			enemies[i] = new GreyYellow_Enemy_Up(info.x, info.y);
			break;
		case ENEMY_TYPES::YELLOWSHIP_DOWN:
			enemies[i] = new GreyYellow_Enemy_Down(info.x, info.y);
			break;
		case ENEMY_TYPES::SHURIKEN_ENEMY:
			enemies[i] = new Shuriken_Enemy(info.x, info.y);
			break;
		case ENEMY_TYPES::SILVER_ROUND:
			enemies[i] = new Silver_Round(info.x, info.y);
			break;
		case ENEMY_TYPES::SILVER_ROUND_DOWN:
			enemies[i] = new Silver_Round_Down(info.x, info.y);
			break;
		case ENEMY_TYPES::DOWN_WHITEORANGETURRET:
			enemies[i] = new Down_WhiteOrangeTurret(info.x, info.y);
			break;
		case ENEMY_TYPES::DRILL_DOWN:
			enemies[i] = new Drill_Down(info.x, info.y);
			break;
		case ENEMY_TYPES::DRILL_UP:
			enemies[i] = new Drill_Up(info.x, info.y);
			break;
		case ENEMY_TYPES::GREYBALL_CIRCLE:
			enemies[i] = new Greyball_Circle(info.x, info.y);
			break;
		case ENEMY_TYPES::YELLOWSHIP_RIGHT_UP:
			enemies[i] = new GreyYellow_Enemy_Right_Up(info.x, info.y);
			break;
		case ENEMY_TYPES::YELLOWSHIP_RIGHT_DOWN:
			enemies[i] = new GreyYellow_Enemy_Right_Down(info.x, info.y);
			break;
		
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (enemies[i]->life > 1)	// When an enemy is hit, if it has more than 1 HP, one is substracted and the hit blit animation (should) plays
			{
				enemies[i]->life--;
				Mix_PlayChannel(-1, enemyHit, 0);
				break;
			}
			
			else	// if enemy has only 1 HP left, execute it's OnCollision function and destroy it
			{
				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}

