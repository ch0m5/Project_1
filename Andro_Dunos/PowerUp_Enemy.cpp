#include "Application.h"
#include "Globals.h"
#include "PowerUp_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"

/*
enum EnemyPattern {
	leftMov, stop1, downLeftMov, stop2, upLeftMov, stop3, rightMov, stop4
};
*/

PowerUp_Enemy::PowerUp_Enemy(int x, int y) : Enemy(x, y)	//@XaviMarin
{
	hitboxWidth = 18;
	hitboxHeight = 26;
	int i = 0;
	for (; i < 3; ++i) {
		// left movement -------------------------------------
		left.PushBack({ 229, 2, hitboxWidth, hitboxHeight });
		left.PushBack({ 255, 2, hitboxWidth, hitboxHeight });
		left.speed = 0.1f;

		// stop 1 --------------------------------------------
		stop1.PushBack({ 281, 3, hitboxWidth, hitboxHeight });
		stop1.speed = 0.1f;

		// left down movement --------------------------------
		leftdown.PushBack({ 307, 3, hitboxWidth, hitboxHeight });
		leftdown.PushBack({ 333, 2, hitboxWidth, hitboxHeight });
		leftdown.speed = 0.1f;

		// stop 2 --------------------------------------------
		stop2.PushBack({ 359, 2, hitboxWidth, hitboxHeight });
		stop2.PushBack({ 385, 3, hitboxWidth, hitboxHeight });
		stop2.PushBack({ 411, 3, hitboxWidth, hitboxHeight });
		stop2.speed = 0.1f;

		// left up movement ----------------------------------
		leftup.PushBack({ 437, 3, hitboxWidth, hitboxHeight });
		leftup.PushBack({ 462, 2, hitboxWidth, hitboxHeight });
		leftup.speed = 0.1f;

		// stop 3 --------------------------------------------
		stop3.PushBack({ 489, 7, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 229, 37, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 255, 37, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 281, 37, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 307, 37, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 333, 34, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 359, 34, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 385, 30, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 411, 30, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 437, 29, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 463, 29, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 489, 29, hitboxWidth, hitboxHeight });
		stop3.PushBack({ 229, 56, hitboxWidth, hitboxHeight });
		stop3.speed = 0.1f;

		// right movement ------------------------------------
		right.PushBack({ 255, 56, hitboxWidth, hitboxHeight });
		right.PushBack({ 281, 56, hitboxWidth, hitboxHeight });
		right.speed = 0.1f;

		// stop4 ---------------------------------------------
		stop4.PushBack({ 307, 57, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 333, 61, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 359, 64, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 385, 64, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 412, 64, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 438, 64, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 463, 64, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 489, 62, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 229, 88, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 255, 84, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 281, 84, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 307, 83, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 333, 83, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 359, 83, hitboxWidth, hitboxHeight });
		stop4.PushBack({ 385, 83, hitboxWidth, hitboxHeight });
		stop4.speed = 0.1f;


		PowerUpEnemy_Path.PushBack({ 0, 0 }, 220, &left);
		PowerUpEnemy_Path.PushBack({ 0, 0 }, 0, &stop1);
		PowerUpEnemy_Path.PushBack({ -0.25, 0.25 }, 60, &leftdown);
		PowerUpEnemy_Path.PushBack({ 0, 0 }, 0, &stop2);
		PowerUpEnemy_Path.PushBack({ -0.25, -0.25 }, 60, &leftup);
		PowerUpEnemy_Path.PushBack({ 0, 0 }, 0, &stop3);
		PowerUpEnemy_Path.PushBack({ 1, 0 }, 250, &right);
		PowerUpEnemy_Path.PushBack({ 0, 0 }, 0, &stop4);

	}
	i = 4;

	//PowerUpEnemy_Path.loop = false;
	//PowerUpEnemy_Path.Reset();
	PowerUpEnemy_Path.PushBack({ 1.5, 0 }, 100, &right);
	
	
	//animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	PowerUpEnemy_posx = x;
	PowerUpEnemy_posy = y;

}

void PowerUp_Enemy::Move()
{
	//position = originalPos + PowerUpEnemy_Path.GetCurrentPosition(&animation);
	
	position.x = PowerUpEnemy_posx + PowerUpEnemy_Path.GetCurrentPosition(&animation).x;
	position.y = PowerUpEnemy_posy + PowerUpEnemy_Path.GetCurrentPosition(&animation).y;

}

void PowerUp_Enemy::OnCollision(Collider* collider)
{
	

	if (dead == false)
	{
		App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BONUS, this->position.x, this->position.y); // must deliver a powerup particle
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
