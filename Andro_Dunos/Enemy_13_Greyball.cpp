#include "Application.h"
#include "Enemy_13_Greyball.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"


Enemy_13_Greyball::Enemy_13_Greyball(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 18;
	hitboxHeight = 22;

	fly.PushBack({ 21, 22, hitboxWidth, hitboxHeight });
	fly.PushBack({ 54, 22, hitboxWidth, hitboxHeight });
	fly.PushBack({ 87, 22, hitboxWidth, hitboxHeight });
	fly.PushBack({ 21, 53, hitboxWidth, hitboxHeight });
	fly.PushBack({ 54, 54, hitboxWidth, hitboxHeight });
	fly.PushBack({ 87, 55, hitboxWidth, hitboxHeight });
	fly.PushBack({ 6, 89, hitboxWidth, hitboxHeight });
	fly.PushBack({ 39, 89, hitboxWidth, hitboxHeight });
	fly.PushBack({ 72, 88, hitboxWidth, hitboxHeight });
	fly.PushBack({ 105, 88, hitboxWidth, hitboxHeight });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_13_Greyball::Move()
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
	
	position.y = int(float(original_y) + (15.0f * sinf(2*PI*wave + 0)));
	position.x -= 1;
}

void Enemy_13_Greyball::Fire()
{
	if (position.y == App->player1->position.y)
	{
		App->particles->AddParticle(App->particles->yellowSmallLeft, position.x, position.y, COLLIDER_ENEMY_SHOT);
	}
}

