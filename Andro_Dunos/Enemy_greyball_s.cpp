#include "Application.h"
#include "Enemy_GreyBall_S.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"


Enemy_Greyball_S::Enemy_Greyball_S(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 18;
	hitboxHeight = 19;

	fly.PushBack({ 0, 3, hitboxWidth, hitboxHeight });
	fly.PushBack({ 19, 3, hitboxWidth, hitboxHeight });
	fly.PushBack({ 39, 3, hitboxWidth, hitboxHeight });
	fly.PushBack({ 59, 1, hitboxWidth, hitboxHeight });
	fly.PushBack({ 79, 0, hitboxWidth, hitboxHeight });
	fly.PushBack({ 101, 0, hitboxWidth, hitboxHeight });

	fly.PushBack({ 0, 22, hitboxWidth, hitboxHeight });
	fly.PushBack({ 22, 23, hitboxWidth, hitboxHeight });
	fly.PushBack({ 44, 24, hitboxWidth, hitboxHeight });
	fly.PushBack({ 67, 26, hitboxWidth, hitboxHeight });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	GreyS_posx = x;
	GreyS_posy = y;

	original_y = y;

	S_Path.PushBack({ -0.5, 1 }, 70);
	S_Path.PushBack({ -0.5, 0 }, 20);
	S_Path.PushBack({ -0.5, -1 }, 70);
	S_Path.PushBack({ -0.5, 0 }, 20);
	S_Path.PushBack({ -0.5, 1 }, 70);
	S_Path.PushBack({ -0.5, 0 }, 20);
	S_Path.PushBack({ -0.5, -1 }, 70);
	
}

void Enemy_Greyball_S::Move()
{
	position.x = GreyS_posx + S_Path.GetCurrentPosition().x;
	position.y = GreyS_posy + S_Path.GetCurrentPosition().y;
}

//void Enemy_Greyball_S::Fire()
//{
//	if (position.y == App->player1->position.y)
//	{
//		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y,-1, COLLIDER_ENEMY_SHOT);
//	}
//}

void Enemy_Greyball_S::OnCollision(Collider* collider)
{
	
	
	if (dead==false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x-50, position.y);
		App->particles->AddParticle(App->particles->explosion1, position.x, position.y);
		App->particles->AddParticle(App->particles->explosion2, position.x + 30, position.y);
		Mix_PlayChannel(5, App->enemies->explosion1, 0);
		Mix_PlayChannel(4, App->enemies->explosion2, 0);
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