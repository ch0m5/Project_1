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
	
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	BigGrey_posx = x;
	BigGrey_posy = y;

	BigGrey_Path.PushBack({ -0.25, -0.5 }, 50);
	BigGrey_Path.PushBack({ -0.25, 0.5 }, 50);
}

void BigGrey_Enemy::Move()
{
	position.x = BigGrey_posx + BigGrey_Path.GetCurrentPosition().x;
	position.y = BigGrey_posy + BigGrey_Path.GetCurrentPosition().y;
}

void BigGrey_Enemy::OnCollision(Collider* collider)
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
		else if (collider->type == COLLIDER_PLAYER_2_SHOT)
		{
			App->UI->player2Score += score;
		}
	}
	dead = true;
}