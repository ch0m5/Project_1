#include "Application.h"
#include "BigGrey_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"


BigGrey_Enemy::BigGrey_Enemy(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 31;
	hitboxHeight = 27;

	fly.PushBack({ 515, 2, hitboxWidth, hitboxHeight });
	fly.PushBack({ 546, 2, hitboxWidth, hitboxHeight });
	
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	BigGrey_posx = x;
	BigGrey_posy = y;

	BigGrey_Path.PushBack({ -0.25, -0.5 }, 50);
	BigGrey_Path.PushBack({ -0.25, 0.5 }, 50);
}

void BigGrey_Enemy::Move()
{

	position.x = BigGrey_posx + BigGrey_Path.GetCurrentPosition().x;
	position.y = BigGrey_posy + BigGrey_Path.GetCurrentPosition().y;

}