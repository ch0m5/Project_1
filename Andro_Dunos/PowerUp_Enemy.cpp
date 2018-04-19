#include "Application.h"
#include "PowerUp_Enemy.h"
#include "ModuleCollision.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"


PowerUp_Enemy::PowerUp_Enemy(int x, int y) : Enemy(x, y)
{
	hitboxWidth = 18;
	hitboxHeight = 26;

	fly.PushBack({ 229, 2, hitboxWidth, hitboxHeight });
	fly.PushBack({ 255, 2, hitboxWidth, hitboxHeight });
	
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	PowerUp_posx = x;
	PowerUp_posy = y;

	PowerUp_Path.PushBack({ 0.25, 0 }, 50);
	
}

void PowerUp_Enemy::Move()
{

	position.x = PowerUp_posx + PowerUp_Path.GetCurrentPosition().x;
	position.y = PowerUp_posy + PowerUp_Path.GetCurrentPosition().y;

}
