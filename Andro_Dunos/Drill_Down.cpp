#include "Application.h"
#include "Drill_Down.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"


Drill_Down::Drill_Down(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 15;
	hitboxHeight = 32;

	life = 10;

	fly.PushBack({ 4, 298, hitboxWidth, hitboxHeight });
	fly.PushBack({ 20,298, hitboxWidth, hitboxHeight });
	fly.PushBack({ 36, 298, hitboxWidth, hitboxHeight });
	fly.PushBack({ 52, 298, hitboxWidth, hitboxHeight });

	fly.speed = 0.6f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	posx = x;
	posy = y;

	original_y = y;

	Path.PushBack({ 0, 0 }, 350);
	Path.PushBack({ 0, 0.25 }, 50);
	Path.PushBack({ 0, 0.75 }, 400);

}

void Drill_Down::Move()
{
	position.x = posx + Path.GetCurrentPosition().x;
	position.y = posy + Path.GetCurrentPosition().y;
}

//void Drill_Down::Fire()
//{
//	if (position.y == App->player1->position.y)
//	{
//		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y,-1, COLLIDER_ENEMY_SHOT);
//	}
//}

void Drill_Down::OnCollision(Collider* collider)
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