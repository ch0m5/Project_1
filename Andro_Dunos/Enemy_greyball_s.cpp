//#include "Application.h"
//#include "Enemy_13_Greyball.h"
//#include "ModuleCollision.h"
//#include "ModuleRender.h"
//#include "ModulePlayer1.h"
//#include "ModuleParticles.h"
//#include "ModuleUserInterface.h"
//
//
//Enemy_13_Greyball::Enemy_13_Greyball(int x, int y) : Enemy(x, y)
//{
//	hitboxWidth = 18;
//	hitboxHeight = 19;
//
//	fly.PushBack({ 0, 3, hitboxWidth, hitboxHeight });
//	fly.PushBack({ 19, 3, hitboxWidth, hitboxHeight });
//	fly.PushBack({ 39, 3, hitboxWidth, hitboxHeight });
//	fly.PushBack({ 59, 1, hitboxWidth, hitboxHeight });
//	fly.PushBack({ 79, 0, hitboxWidth, hitboxHeight });
//	fly.PushBack({ 101, 0, hitboxWidth, hitboxHeight });
//
//	fly.PushBack({ 0, 22, hitboxWidth, hitboxHeight });
//	fly.PushBack({ 22, 23, hitboxWidth, hitboxHeight });
//	fly.PushBack({ 44, 24, hitboxWidth, hitboxHeight });
//	fly.PushBack({ 67, 26, hitboxWidth, hitboxHeight });
//	fly.speed = 0.2f;
//
//	animation = &fly;
//
//	collider = App->collision->AddCollider({ 0, 0, hitboxWidth, hitboxHeight }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
//
//	original_y = y;
//}
//
//void Enemy_13_Greyball::Move()
//{
//	if (going_up)
//	{
//		if (wave > 1.0f)
//			going_up = false;
//		else
//			wave += 0.01f;
//	}
//	else
//	{
//		if (wave < -1.0f)
//			going_up = true;
//		else
//			wave -= 0.01f;
//	}
//
//	position.y = int(float(original_y) + (25.0f * sinf(2 * PI*wave + 0)));
//	position.x -= 1;
//}
//
//void Enemy_13_Greyball::Fire()
//{
//	if (position.y == App->player1->position.y)
//	{
//		App->particles->AddParticle(App->particles->enemyBlueShot, position.x, position.y, -1, COLLIDER_ENEMY_SHOT);
//	}
//}
//
//void Enemy_13_Greyball::OnCollision(Collider* collider)
//{
//
//
//	if (dead == false)
//	{
//		App->particles->AddParticle(App->particles->explosion, position.x - 50, position.y);
//		App->particles->AddParticle(App->particles->explosion1, position.x, position.y);
//		App->particles->AddParticle(App->particles->explosion2, position.x + 30, position.y);
//		if (collider->type == COLLIDER_PLAYER_SHOT)
//		{
//			App->UI->player1Score += score;
//		}
//		if (collider->type == COLLIDER_PLAYER_2_SHOT)
//		{
//			App->UI->player2Score += score;
//		}
//	}
//	dead = true;
//}