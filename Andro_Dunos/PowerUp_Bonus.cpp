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

	PowerUpBonus_Path.PushBack({ -0.25, 0 }, 70,&blueMode); //bluemode
	PowerUpBonus_Path.PushBack({ -0.25, 0 }, 10, &blueClose);//close blue
	PowerUpBonus_Path.PushBack({ 0.25, -1 }, 10, &redOpen);//open red
	PowerUpBonus_Path.PushBack({ 0.25, -1 }, 70, &redMode);//redmode
	PowerUpBonus_Path.PushBack({ 0.25, 0 }, 10, &redShine);//red shine
	PowerUpBonus_Path.PushBack({ 0.25, 1 }, 70, &redClose);//red close
	PowerUpBonus_Path.PushBack({ -0.25, 0 }, 70, &blueOpen);//blue open
	PowerUpBonus_Path.PushBack({ -0.25, 0 }, 70, &blueMode); //bluemode
	

	blue = true;
}

void PowerUp_Bonus::Move()
{
	//LO QUE HAY Q HACER (asi lo haria yo) paso1
	//implementar un contador que suba y cuando llegue a un valor que blue=false y red sea igual a true (1)
	// y lo mismo que despues llegue a otro valor y y cambie blue a tru y red a false
	// (varibale q hay q crear ejemplo i)
	/*i++;
	if (i==2000)
		blue=false
		red=true
	if else (i ==4000)
		blue=true
		red=false

	else if (i>4000)
		i=0*/

	position.x = PowerUpBonus_posx + PowerUpBonus_Path.GetCurrentPosition(&animation).x;
	position.y = PowerUpBonus_posy + PowerUpBonus_Path.GetCurrentPosition(&animation).y;

}

void PowerUp_Bonus::OnCollision(Collider* collider)
{	
	if (dead == false)
	{
		//paso 2
		/*luego aqui depende de si el jugador choca cuando blue es tru o cuando red es true, pues se le suma a bluepower o a orange power*/
		if (collider->type == COLLIDER_PLAYER)
		{
			Mix_PlayChannel(6, App->player1->powerUp, 0);
			App->player1->bluePower++;
			App->UI->player1Score += score;
		}
		if (collider->type == COLLIDER_PLAYER_2)
		{
			Mix_PlayChannel(6, App->player2->powerUp, 0);
			App->player2->bluePower++;
			App->UI->player2Score += score;
		}
	}
	dead = true;
}
	

