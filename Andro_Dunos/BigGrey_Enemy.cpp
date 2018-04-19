#include "Application.h"
#include "BigGrey_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"


BigGrey_Enemy::BigGrey_Enemy(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 20;
	hitboxHeight = 20;

	fly.PushBack({ 0, 55, hitboxWidth, hitboxHeight });
	fly.PushBack({ 21, 55, hitboxWidth, hitboxHeight });
	fly.PushBack({ 43, 55, hitboxWidth, hitboxHeight });
	fly.PushBack({ 64, 55, hitboxWidth, hitboxHeight });
	fly.PushBack({ 85, 55, hitboxWidth, hitboxHeight });
	fly.PushBack({ 106, 55, hitboxWidth, hitboxHeight });
	fly.PushBack({ 0, 76, hitboxWidth, hitboxHeight });
	fly.PushBack({ 21, 76, hitboxWidth, hitboxHeight });
	fly.PushBack({ 43, 76, hitboxWidth, hitboxHeight });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	BigGrey_posx = x;
	BigGrey_posy = y;

	BigGrey_Path.PushBack({ -0.25, -0.5 }, 50);
	BigGrey_Path.PushBack({ -0.25, 0.75 }, 50);
}

void BigGrey_Enemy::Move()
{

	position.x = BigGrey_posx + BigGrey_Path.GetCurrentPosition().x;
	position.y = BigGrey_posy + BigGrey_Path.GetCurrentPosition().y;

}