#include "Application.h"
#include "Down_WhiteOrangeTurret.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"
#include "ModuleEnemies.h"
#include "ModuleMixer.h"

#include "SDL\include\SDL_timer.h"
#include <math.h>


Down_WhiteOrangeTurret::Down_WhiteOrangeTurret(int x, int y) : Enemy(x, y) // @XaviMarin
{
	hitboxWidth = 14;
	hitboxHeight = 14;

	fly.PushBack({ 0, 101, hitboxWidth, hitboxHeight });
	fly.PushBack({ 32, 101, hitboxWidth, hitboxHeight });
	fly.PushBack({ 65, 101, hitboxWidth, hitboxHeight });
	fly.PushBack({ 97, 101, hitboxWidth, hitboxHeight });

	fly.speed = 0.6f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	Down_WhiteOrangeTurret_posx = x;
	Down_WhiteOrangeTurret_posy = y;

	original_y = y;


	Down_WhiteOrangeTurret_Path.PushBack({ -0.5, 1 }, 70);


}

float Down_WhiteOrangeTurret::resultingAngle()
{
	float result = atan2(App->player1->position.y - position.y, position.x - App->player1->position.x) * 180 / PI;
}

void Down_WhiteOrangeTurret::Move()
{
	position.x = ShurikenEnemy_posx + ShurikenEnemy_Path.GetCurrentPosition().x;
	position.y = ShurikenEnemy_posy + ShurikenEnemy_Path.GetCurrentPosition().y;
}


void Down_WhiteOrangeTurret::OnCollision(Collider* collider)
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