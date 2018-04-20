#include "Application.h"
#include "RedLineShip_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "GreyYellow_Enemy.h"


GreyYellow_Enemy::GreyYellow_Enemy(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 29;
	hitboxHeight = 17;

	fly.PushBack({ 319, 121, hitboxWidth, hitboxHeight });
	fly.PushBack({ 289, 120, hitboxWidth, hitboxHeight });
	fly.PushBack({ 259, 119, hitboxWidth, hitboxHeight });
	fly.PushBack({ 289, 120, hitboxWidth, hitboxHeight });
	fly.PushBack({ 319, 121, hitboxWidth, hitboxHeight });
	fly.PushBack({ 259, 149, hitboxWidth, hitboxHeight });
	fly.PushBack({ 289, 148, hitboxWidth, hitboxHeight });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	GreyYellow_Ship_posx = x;
	GreyYellow_Ship_posy = y;

	GreyYellow_Ship_Path.PushBack({ -0.75, -0.15f }, 50);
	GreyYellow_Ship_Path.PushBack({ -0.75, 0.15f }, 50);
	
}

void GreyYellow_Enemy::Move()
{

	position.x = GreyYellow_Ship_posx + GreyYellow_Ship_Path.GetCurrentPosition().x;
	position.y = GreyYellow_Ship_posy + GreyYellow_Ship_Path.GetCurrentPosition().y;

}


void GreyYellow_Enemy::OnCollision(Collider* collider)
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