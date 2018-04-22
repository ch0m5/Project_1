#include "Application.h"
#include "PowerUp_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "PowerUp_Bonus.h"
#include "PowerUp_Enemy.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"
#include "ModuleUserInterface.h"
#include "ModuleFont.h"
PowerUp_Bonus::PowerUp_Bonus(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 16;
	hitboxHeight = 16;

	//blue---------------------------------------

	blueMode.PushBack({ 516, 53, hitboxWidth, hitboxHeight });

	blueClose.PushBack({589,53, hitboxWidth, hitboxHeight });
	blueClose.PushBack({ 607,53, hitboxWidth, hitboxHeight });
	blueClose.PushBack({ 551,71, hitboxWidth, hitboxHeight }); //repeat
	blueClose.Finished();
	blueClose.loop = false;

	blueOpen.PushBack({ 607,53, hitboxWidth, hitboxHeight });
	blueOpen.PushBack({ 589,53, hitboxWidth, hitboxHeight });
	blueOpen.Finished();
	blueOpen.loop = false;

	//red-----------------------------------------
	
	redMode.PushBack({ 516,35, hitboxWidth, hitboxHeight });

	redShine.PushBack({ 535,35, hitboxWidth, hitboxHeight });
	redShine.PushBack({ 553,35, hitboxWidth, hitboxHeight });
	redShine.PushBack({ 571,35, hitboxWidth, hitboxHeight });
	blueClose.Finished();
	blueClose.speed = 0.2f;
	blueClose.loop = false;

	redClose.PushBack({ 607,35, hitboxWidth, hitboxHeight });
	redClose.PushBack({ 589,35, hitboxWidth, hitboxHeight });
	redClose.PushBack({ 551,71, hitboxWidth, hitboxHeight }); //closed anim
	redClose.Finished();
	redClose.speed = 0.2f;
	redClose.loop = false;

	redOpen.PushBack({ 589,35, hitboxWidth, hitboxHeight });
	redOpen.PushBack({ 607,35, hitboxWidth, hitboxHeight });
	redOpen.Finished();
	redOpen.speed = 0.2f;
	redOpen.loop = false;



	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_POWERUP, (Module*)App->enemies);

	PowerUpBonus_posx = x;
	
	PowerUpBonus_posy = y;

	PowerUpBonus_Path.PushBack({ +0.25, 0 }, 5000, &blueMode); //bluemode
	PowerUpBonus_Path.PushBack({ -0.25, 0 }, 30, &blueClose);//close blue
	//PowerUpBonus_Path.PushBack({ 0.25, -1 }, 30, &redOpen);//open red
	PowerUpBonus_Path.PushBack({ 0.25, 0 }, 10, &redShine);//red shine
	PowerUpBonus_Path.PushBack({ 0.25, -1 }, 170, &redMode);//redmode
	PowerUpBonus_Path.PushBack({ 0.25, 1 }, 70, &redClose);//red close
	PowerUpBonus_Path.PushBack({ -0.25, 0 }, 180, &blueOpen);//blue open
	PowerUpBonus_Path.PushBack({ -0.25, 0 }, 70, &blueMode); //bluemode
	

	//PowerUpBonus_Path.PushBack({ -0.25, 0 }, 70, &blueMode); //bluemode
	//PowerUpBonus_Path.PushBack({ -0.25, 0 }, 10, &blueClose);//close blue
	

	blue = true;
}

void PowerUp_Bonus::Move()
{

	if (move_init == true)
	{
		start_time = SDL_GetTicks();
		move_init = false;
	}
	uint timePassed = SDL_GetTicks() - start_time;
	//The power up attribute must change every 5 seconds
	if (timePassed > 0 && timePassed < 5000)
	{
		blue = true;
		orange = false;
	}
	else if (timePassed > 5000 && timePassed < 10000)
	{
		blue = false;
		orange = true;
	}
	else if (timePassed > 10000)
	{
		start_time = SDL_GetTicks();
	}

	if (App->input->debugMode==true)
	{
		if (blue == true)
		{
			App->fonts->BlitText(100, 20, App->UI->debug_font, "blue");
		}
		if (orange == true)
		{
			App->fonts->BlitText(100, 20, App->UI->debug_font, "orange");
		}
	}

	position.x = PowerUpBonus_posx + PowerUpBonus_Path.GetCurrentPosition(&animation).x;
	position.y = PowerUpBonus_posy + PowerUpBonus_Path.GetCurrentPosition(&animation).y;

}

void PowerUp_Bonus::OnCollision(Collider* collider)
{	
	if (dead == false)
	{
		if (collider->type == COLLIDER_PLAYER)
		{
			Mix_PlayChannel(2, App->player1->powerUp, 0);
			App->UI->player1Score += score;
			if (blue==true)
			{
				App->player1->bluePower++;
			}
			else if (orange==true)
			{
				App->player1->orangePower++;
			}
		}
		if (collider->type == COLLIDER_PLAYER_2)
		{
			Mix_PlayChannel(2, App->player2->powerUp, 0);
			App->UI->player2Score += score;
			if (blue == true)
			{
				App->player2->bluePower++;
			}
			else if (orange == true)
			{
				App->player2->orangePower++;
			}
		}
	}
	dead = true;
	start_time = 0;
}
	

