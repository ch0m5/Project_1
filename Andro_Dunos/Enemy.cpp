#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleUserInterface.h"
Enemy::Enemy(int x, int y) : position(x, y)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	//App->particles->AddParticle(App->particles->shipExplo, (int)position.x, (int)position.y); // Well done!! Only must put the player position in the parameters
	App->particles->AddParticle(App->particles->EnemyExplo, position.x, position.y);
	if (collider->type == COLLIDER_PLAYER_SHOT)			//ADDED CHANGES HERE
	{
		App->UI->player1Score += 100;
	}
	if (collider->type == COLLIDER_PLAYER_2_SHOT)
	{
		App->UI->player2Score += 100;
	}
}