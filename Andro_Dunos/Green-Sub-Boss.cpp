#include "Application.h"
#include "Green-Sub-Boss.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"


Green_Sub_Boss::Green_Sub_Boss(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 43;
	hitboxHeight = 44;

	life = 115;

	fly.PushBack({ 256, 330, hitboxWidth, hitboxHeight });


	fly.speed = 0.6f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	posx = x;
	posy = y;

	original_y = y;

	Path.PushBack({ 0, 0 }, 300);
	Path.PushBack({ 0.5, 0.5 }, 200);
	Path.PushBack({ 0.5, -0.5 }, 200);
	Path.PushBack({ 0.25, 0 }, 100);
	Path.PushBack({ 0.5, 0.5 }, 200);
	Path.PushBack({ 0.5, -0.5 }, 200);
	Path.PushBack({ 0.25, 0 }, 100);
	Path.PushBack({ 0.5, 0.5 }, 200);
	Path.PushBack({ 0.5, -0.5 }, 200);
	Path.PushBack({ 0.5, 0.5 }, 200);
	Path.PushBack({ 0.5, -0.5 }, 200);
	Path.PushBack({ 0.25, 0 }, 100);
	Path.PushBack({ 0.5, 0.5 }, 200);
	Path.PushBack({ 0.5, -0.5 }, 200);


	Path.PushBack({ -1, -0.5 }, 600);





}

void Green_Sub_Boss::Move()
{
	position.x = posx + Path.GetCurrentPosition().x;
	position.y = posy + Path.GetCurrentPosition().y;

}

//void Drill_Up::Fire()
//{
//	if (position.y == App->player1->position.y)
//	{
//		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y,-1, COLLIDER_ENEMY_SHOT);
//	}
//}

void Green_Sub_Boss::OnCollision(Collider* collider)
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