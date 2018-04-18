#include "Application.h"
#include "RedLineShip_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"


RedLineShip_Enemy::RedLineShip_Enemy(int x, int y) : Enemy(x, y)
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

	original_y = y;
}

void RedLineShip_Enemy::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.01f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.01f;
	}

	position.y = int(float(original_y) + (15.0f * sinf(2 * PI*wave + 0)));
	position.x -= 1;
}

/*
void Enemy_13_Greyball::Fire()
{
	if (position.y == App->player1->position.y)
	{
		App->particles->AddParticle(App->particles->yellowSmallLeft, position.x, position.y, COLLIDER_ENEMY_SHOT);
	}
}
*/