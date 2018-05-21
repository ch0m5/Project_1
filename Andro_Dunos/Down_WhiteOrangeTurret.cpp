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
	hitboxWidth = 15;
	hitboxHeight = 15;

	pos1.PushBack({ 292, 688, hitboxWidth, hitboxHeight });
	pos2.PushBack({ 315, 688, hitboxWidth, hitboxHeight });
	pos3.PushBack({ 336, 688, hitboxWidth, hitboxHeight });
	pos4.PushBack({ 227, 706, hitboxWidth, hitboxHeight });
	pos5.PushBack({ 250, 704, hitboxWidth, hitboxHeight });
	pos6.PushBack({ 272, 704, hitboxWidth, hitboxHeight });
	pos7.PushBack({ 292, 704, hitboxWidth, hitboxHeight });
	pos8.PushBack({ 316, 704, hitboxWidth, hitboxHeight });
	pos9.PushBack({ 336, 704, hitboxWidth, hitboxHeight });

	//fly.speed = 0.6f;


	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	Down_WhiteOrangeTurret_posx = x;
	Down_WhiteOrangeTurret_posy = y;

	//original_y = y;

}

float Down_WhiteOrangeTurret::resultingAngle()
{
	float result = (atan2(App->player1->position.y - position.y, position.x - App->player1->position.x) * 180) / PI;
	return result;
}

void Down_WhiteOrangeTurret::Move()
{
	time = SDL_GetTicks();

	if (time > restart + 2000) {
		ready = true;
		restart = time;

		if (App->player1->position.x - position.x < 100 && position.x - App->player1->position.x > -100) {
			ready = false;
		}
	}

	if (App->player1->position.x - position.x <= -100 && App->player1->position.x - position.x <= 100) {

		if (resultingAngle() >= 10 && resultingAngle() < 20) {
			animation = &pos2;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}

		else if (resultingAngle() >= 20 && resultingAngle() < 40) {
			animation = &pos3;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}

		else if (resultingAngle() >= 40 && resultingAngle() < 80) {
			animation = &pos4;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}

		else if (resultingAngle() >= 80 && resultingAngle() < 100) {
			animation = &pos5;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}

		else if (resultingAngle() >= 100 && resultingAngle() < 120) {
			animation = &pos6;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}

		else if (resultingAngle() >= 120 && resultingAngle() < 150) {
			animation = &pos7;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}

		else if (resultingAngle() >= 150 && resultingAngle() < 170) {
			animation = &pos8;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}

		else if (resultingAngle() >= 170 && resultingAngle() <= 180) {
			animation = &pos9;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}

	}
	else {
			if (resultingAngle() >= -181 && resultingAngle() < 10) {
			animation = &pos1;
			if (ready == true) {
				//App->particles->AddParticle()
				//ready = false;
			}
		}
	}
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