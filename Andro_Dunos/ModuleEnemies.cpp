#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"

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
	sprites = App->textures->Load("Assets/Sprites/Enemies_and_projectiles/table_enemy.png");

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
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2);
			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}

