#include "Application.h"
#include "Boss.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"
#include "ModuleUserInterface.h"

Boss::Boss(int x, int y) : position(x, y)
{

}

Boss::~Boss()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Boss::GetCollider() const
{
	return collider;
}

void Boss::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Boss::OnCollision(Collider* collider) {}