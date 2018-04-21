#include "Application.h"
#include "BigGrey_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"

BigGrey_Enemy::BigGrey_Enemy(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 31;
	hitboxHeight = 27;

	fly.PushBack({ 515, 2, hitboxWidth, hitboxHeight });
	fly.PushBack({ 546, 2, hitboxWidth, hitboxHeight });
	
	fly.speed = 0.1f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	BigGrey_posx = x;
	BigGrey_posy = y;

	/*BigGrey_Path.PushBack({ -0.25, -0.5 }, 50);
	BigGrey_Path.PushBack({ -0.25, 0.5 }, 50);*/
}

void BigGrey_Enemy::Move()
{
	
	position.x += 0.1;
	position.y = App->player1->position.y;
	/*
	if (App->player1->position.y > position.y) {
		position.y -= 0.1;
	}
	if (App->player1->position.y < position.y) {
		position.y += 0.1;
	}*/
}

void BigGrey_Enemy::OnCollision(Collider* collider)
{
	

	if (dead == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x + 10, position.y);
		App->particles->AddParticle(App->particles->explosion1, position.x, position.y);
		App->particles->AddParticle(App->particles->explosion2, position.x + 30, position.y);
		if (collider->type == COLLIDER_PLAYER_SHOT)
		{
			App->UI->player1Score += score;
		}
		else if (collider->type == COLLIDER_PLAYER_2_SHOT)
		{
			App->UI->player2Score += score;
		}
	}
	dead = true;
}


void BigGrey_Enemy::Fire()	//@XaviMarin
{
	if (currentShot > maxShots)
	{
		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y, -1, COLLIDER_ENEMY_SHOT);
		currentShot = 0;
	}
	else
	{
		currentShot++;
	}
}