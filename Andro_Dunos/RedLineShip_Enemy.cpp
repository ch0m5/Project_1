#include "Application.h"
#include "RedLineShip_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"


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

	RedLineShip_posx = x;
	RedLineShip_posy = y;

	RedLineShip_Path.PushBack({ -0.75,-1 }, 50);
	RedLineShip_Path.PushBack({ -0.75,1 }, 50);
}

void RedLineShip_Enemy::Move()
{
	
	position.x = RedLineShip_posx + RedLineShip_Path.GetCurrentPosition().x;
	position.y = RedLineShip_posy + RedLineShip_Path.GetCurrentPosition().y;

}


void RedLineShip_Enemy::OnCollision(Collider* collider)
{
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	//App->particles->AddParticle(App->particles->shipExplo, (int)position.x, (int)position.y); // Well done!! Only must put the player position in the parameters

	if (dead == false)
	{
		App->particles->AddParticle(App->particles->EnemyExplo, position.x, position.y);
		if (collider->type == COLLIDER_PLAYER_SHOT)
		{
			App->UI->player1Score += score;
		}
		if (collider->type == COLLIDER_PLAYER_2_SHOT)
		{
			App->UI->player2Score += score;
		}
	}
	dead = true;
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