#include "Application.h"
#include "PowerUp_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "PowerUp_Bonus.h"
#include "PowerUp_Enemy.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"


PowerUp_Bonus::PowerUp_Bonus(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 16;
	hitboxHeight = 16;

	fly.PushBack({ 516, 53, hitboxWidth, hitboxHeight });
	fly.PushBack({ 516, 53, hitboxWidth, hitboxHeight });

	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->enemies);

	PowerUpBonus_posx = x;
	
	PowerUpBonus_posy = y;

	PowerUpBonus_Path.PushBack({ 0.25, 0 }, 50);


}

void PowerUp_Bonus::Move()
{

	position.x = PowerUpBonus_posx + PowerUpBonus_Path.GetCurrentPosition().x;
	position.y = PowerUpBonus_posy + PowerUpBonus_Path.GetCurrentPosition().y;

}

void PowerUp_Bonus::OnCollision(Collider* collider)
{	
	if (dead == false)
	{
	
		if (collider->type == COLLIDER_PLAYER)
		{
			Mix_PlayChannel(3, App->player1->powerUp, 0);
			App->player1->bluePower++;
			App->UI->player1Score += score;
		}
		if (collider->type == COLLIDER_PLAYER)
		{
			App->UI->player2Score += score;
		}
	}
	dead = true;
}
	

