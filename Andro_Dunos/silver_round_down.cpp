#include "Application.h"
#include "silver_round_down.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"


Silver_Round_Down::Silver_Round_Down(int x, int y) : Enemy(x, y) //must use the position of the spritesheet: table_enemy_goodone.png where there are all the enemies
{
	hitboxWidth = 20;
	hitboxHeight = 20;

	life = 2;

	left.PushBack({ 0, 224, hitboxWidth, hitboxHeight });
	left.speed = 0.1f;

	leftUp.PushBack({ 20, 224, hitboxWidth, hitboxHeight });
	leftUp.speed = 0.1f;

	leftUP2.PushBack({ 40, 224, hitboxWidth, hitboxHeight });
	leftUP2.speed = 0.1f;

	down.PushBack({ 60, 244, hitboxWidth, hitboxHeight });
	down.speed = 0.1f;

	upRight.PushBack({ 80, 224, hitboxWidth, hitboxHeight });
	upRight.speed = 0.1f;

	upRight2.PushBack({ 100, 224, hitboxWidth, hitboxHeight });
	upRight2.speed = 0.1f;

	right.PushBack({ 0, 244, hitboxWidth, hitboxHeight });
	right.speed = 0.1f;



	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	Silver_posx = x;
	Silver_posy = y;

	original_y = y;

	Silver_Path.PushBack({ -0.25, 0 }, 350, &left);

	Silver_Path.PushBack({ -0.25, 0.5 }, 50, &down);

	Silver_Path.PushBack({ 1, 0 }, 200, &right);

	Silver_Path.PushBack({ -0.25, 0.5 }, 50, &down);

	Silver_Path.PushBack({ -0.25, 0 }, 200, &left);

}

void Silver_Round_Down::Move()
{
	position.x = Silver_posx + Silver_Path.GetCurrentPosition(&animation).x;
	position.y = Silver_posy + Silver_Path.GetCurrentPosition(&animation).y;
}


void Silver_Round_Down::OnCollision(Collider* collider)
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