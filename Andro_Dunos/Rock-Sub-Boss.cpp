#include "Application.h"
#include "Rock-Sub-Boss.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"


Rock_Sub_Boss::Rock_Sub_Boss(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 63;
	hitboxHeight = 67;

	life = 100;

	fly.PushBack({ 246, 393, hitboxWidth, hitboxHeight });
	

	fly.speed = 0.6f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	posx = x-50;
	posy = y;

	original_y = y;

	Path.PushBack({ 0.25, -0.5 }, 300);
	Path.PushBack({ 0, -0 }, 100);
	Path.PushBack({ 0.5, 0.5 }, 100);

	Path.PushBack({ 0.5, 1.25 }, 100);
	Path.PushBack({ 0.5, -0.5 }, 100);
	Path.PushBack({ 0.25, 0.5 }, 100);

	Path.PushBack({ 0.5, 1.25 }, 100);
	Path.PushBack({ 0.5, -0.5 }, 100);
	Path.PushBack({ 0.5, 0.5 }, 100);

	Path.PushBack({ 0.5, 1.25 }, 100);
	Path.PushBack({ 0.5, -0.5 }, 100);
	Path.PushBack({ 0.25, 0.5 }, 100);

	Path.PushBack({ 0.5, 1 }, 100);
	Path.PushBack({ 0.5, -0.5 }, 100);
	 
	

	Path.PushBack({ -1, -0.5 }, 600);
	

	
	

}

void Rock_Sub_Boss::Move()
{
	position.x = posx + Path.GetCurrentPosition().x;
	position.y = posy + Path.GetCurrentPosition().y;
	
}

void  Rock_Sub_Boss::Fire()
{
	if (currentShot > maxShots)
	{
		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y, -1, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y - 15, -1, COLLIDER_ENEMY_SHOT);

		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y + 15, -1, COLLIDER_ENEMY_SHOT);
		currentShot = 0;
	}
	else
	{
		currentShot++;
	}
}

void Rock_Sub_Boss::OnCollision(Collider* collider)
{


	if (dead == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->particles->AddParticle(App->particles->explosion1, position.x, position.y);
		App->particles->AddParticle(App->particles->explosion2, position.x, position.y);
		Mix_PlayChannel(5, App->enemies->explosion1, 0);
		Mix_PlayChannel(4, App->enemies->explosion2, 0);
		App->enemies->AddEnemy(ENEMY_TYPES::SUBBOSS2, this->position.x, this->position.y); // must deliver a powerup particle
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