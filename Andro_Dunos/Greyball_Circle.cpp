#include "Application.h"
#include "Greyball_Circle.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"


Greyball_Circle::Greyball_Circle(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 18;
	hitboxHeight = 19;

	life = 1;

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
	fly.speed = 0.6f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	GreyS_posx = x;
	GreyS_posy = y;

	original_y = y;

	S_Path.PushBack({ -0.5, 0 }, 250);
	S_Path.PushBack({ 0.75, 0.5 }, 220);
	S_Path.PushBack({ 0, 0.5 }, 150);
	
}

void Greyball_Circle::Move()
{
	position.x = GreyS_posx + S_Path.GetCurrentPosition().x;
	position.y = GreyS_posy + S_Path.GetCurrentPosition().y;
}

//void Greyball_Circle::Fire()
//{
//	if (position.y == App->player1->position.y)
//	{
//		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y,-1, COLLIDER_ENEMY_SHOT);
//	}
//}

void Greyball_Circle::OnCollision(Collider* collider)
{


	if (dead == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->particles->AddParticle(App->particles->explosion1, position.x, position.y);
		App->particles->AddParticle(App->particles->explosion2, position.x, position.y);
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