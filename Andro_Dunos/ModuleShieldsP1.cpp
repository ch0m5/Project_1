#include <math.h>
#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleShieldsP1.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleMixer.h"

ModuleShieldsP1::ModuleShieldsP1()
{
	/* SOUNDS FX NEEDED
	Power_Up_Picked
	Power_Up_UNIT_SHIELDS_EQUIPPED
	Power_Up_UNIT_SHIELDS_EQUIPPING
	*/

	//Blitting needs fixing, except for front
	//Front
	frontRed.PushBack({ 69, 241, shieldWidth, shieldHeight });
	frontRed.PushBack({ 69, 241, shieldWidth, shieldHeight });
	frontRed.loop = true;
	frontRed.speed = 0.2f;

	frontGreen.PushBack({69, 263, shieldWidth, shieldHeight});
	frontGreen.PushBack({ 69, 263, shieldWidth, shieldHeight });
	frontGreen.loop = true;
	frontGreen.speed = 0.2f;

	frontYellow.PushBack({69, 219, shieldWidth, shieldHeight});
	frontYellow.PushBack({ 69, 219, shieldWidth, shieldHeight });
	frontYellow.loop = true;
	frontYellow.speed = 0.2f;

	//Back
	backRed.PushBack({ 69, 241, shieldWidth, shieldHeight });
	backRed.PushBack({ 69, 241, shieldWidth, shieldHeight });
	backRed.loop = true;
	backRed.speed = 0.2f;

	backGreen.PushBack({ 69, 263, shieldWidth, shieldHeight });
	backGreen.PushBack({ 69, 263, shieldWidth, shieldHeight });
	backGreen.loop = true;
	backGreen.speed = 0.2f;

	backYellow.PushBack({ 69, 219, shieldWidth, shieldHeight });
	backYellow.PushBack({ 69, 219, shieldWidth, shieldHeight });
	backYellow.loop = true;
	backYellow.speed = 0.2f;

	//Top
	topRed.PushBack({ 69, 241, shieldWidth, shieldHeight });
	topRed.PushBack({ 69, 241, shieldWidth, shieldHeight });
	topRed.loop = true;
	topRed.speed = 0.2f;

	topGreen.PushBack({ 69, 263, shieldWidth, shieldHeight });
	topGreen.PushBack({ 69, 263, shieldWidth, shieldHeight });
	topGreen.loop = true;
	topGreen.speed = 0.2f;

	topYellow.PushBack({ 69, 219, shieldWidth, shieldHeight });
	topYellow.PushBack({ 69, 219, shieldWidth, shieldHeight });
	topYellow.loop = true;
	topYellow.speed = 0.2f;

	//Bottom
	bottomRed.PushBack({ 69, 241, shieldWidth, shieldHeight });
	bottomRed.PushBack({ 69, 241, shieldWidth, shieldHeight });
	bottomRed.loop = true;
	bottomRed.speed = 0.2f;

	bottomGreen.PushBack({ 69, 263, shieldWidth, shieldHeight });
	bottomGreen.PushBack({ 69, 263, shieldWidth, shieldHeight });
	bottomGreen.loop = true;
	bottomGreen.speed = 0.2f;

	bottomYellow.PushBack({ 69, 219, shieldWidth, shieldHeight });
	bottomYellow.PushBack({ 69, 219, shieldWidth, shieldHeight });
	bottomYellow.loop = true;
	bottomYellow.speed = 0.2f;
}

ModuleShieldsP1::~ModuleShieldsP1() {}

bool ModuleShieldsP1::Start()
{
	bool ret = true;
	
	LOG("Loading shield sprites");
	graphics = App->textures->Load("Assets/Sprites/Players_Ships/Laser_particles.png");

	if (graphics == nullptr)
	{
		LOG("Loading shield sprites FAILED!");
		ret = false;
	}
	
	// starting rotation angle
	angle = 0.5f;

	//Type 2 starting position as a standard
	shield1Pos.x = App->player1->position.x + 5;
	shield1Pos.y = App->player1->position.y - 8;
	shield2Pos.x = App->player1->position.x + 5;
	shield2Pos.y = App->player1->position.y + 10;

	// ---- Declares colliders for shield parts individually ----------- COLLIDER_PLAYER_SHIELD
	shield1Collider = App->collision->AddCollider({ (int)shield1Pos.x, (int)shield1Pos.y, shieldWidth, shieldHeight }, COLLIDER_PLAYER_SHIELD, this);
	shield2Collider = App->collision->AddCollider({ (int)shield2Pos.x, (int)shield2Pos.y, shieldWidth, shieldHeight }, COLLIDER_PLAYER_SHIELD, this);

	shield1Collider->SetPos(shield1Pos.x + App->render->camera.x, shield1Pos.y + App->render->camera.y);
	shield2Collider->SetPos(shield2Pos.x + App->render->camera.x, shield2Pos.y + App->render->camera.y);

	return ret;
}

update_status ModuleShieldsP1::Update()
{
	App->player1->greenPower = checkShieldsLife(life);

	switch (App->player1->type)
	{
	case TYPE_1:
		switch (App->player1->greenPower)
		{
		case LEVEL_1:
			shield1Animation = &topRed;
			shield2Animation = &bottomRed;
			spinTheShields(shield1Animation, shield2Animation, LEVEL_1);
			break;

		case LEVEL_2:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			spinTheShields(shield1Animation, shield2Animation, LEVEL_2);
			break;

		case LEVEL_3:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			spinTheShields(shield1Animation, shield2Animation, LEVEL_3);
			break;

		case LEVEL_4:
			shield1Animation = &topYellow;
			shield2Animation = &bottomYellow;
			spinTheShields(shield1Animation, shield2Animation, LEVEL_4);
			break;

		case LEVEL_5:
			shield1Animation = &topYellow;
			shield2Animation = &bottomYellow;
			spinTheShields(shield1Animation, shield2Animation, LEVEL_5);
			break;

		case LEVEL_6:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			spinTheShields(shield1Animation, shield2Animation, LEVEL_6);
			break;

		case LEVEL_7:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			spinTheShields(shield1Animation, shield2Animation, LEVEL_7);
			break;

		case LEVEL_8:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			spinTheShields(shield1Animation, shield2Animation, LEVEL_8);
			break;
		}
		break;

		// ---- Stays on both top and bottom
	case TYPE_2:
		switch (App->player1->greenPower)
		{
		case LEVEL_1:
			shield1Animation = &topRed;
			shield2Animation = &bottomRed;
			break;

		case LEVEL_2:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			break;

		case LEVEL_3:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			break;

		case LEVEL_4:
			shield1Animation = &topYellow;
			shield2Animation = &bottomYellow;
			break;

		case LEVEL_5:
			shield1Animation = &topYellow;
			shield2Animation = &bottomYellow;
			break;

		case LEVEL_6:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			break;

		case LEVEL_7:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			break;

		case LEVEL_8:
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
			break;
		}
		
		shield1Pos.x = App->player1->position.x + 5;
		shield1Pos.y = App->player1->position.y - 12;
		shield2Pos.x = App->player1->position.x + 5;
		shield2Pos.y = App->player1->position.y + 14;
		break;

		// ---- Stays in front of ship
	case TYPE_3:
		switch (App->player1->greenPower)
		{
		case LEVEL_1:
			shield1Animation = shield2Animation = &frontRed;
			break;

		case LEVEL_2:
			shield1Animation = shield2Animation = &frontGreen;
			break;

		case LEVEL_3:
			shield1Animation = shield2Animation = &frontGreen;
			break;

		case LEVEL_4:
			shield1Animation = shield2Animation = &frontYellow;
			break;

		case LEVEL_5:
			shield1Animation = shield2Animation = &frontYellow;
			break;

		case LEVEL_6:
			shield1Animation = shield2Animation = &frontGreen;
			break;

		case LEVEL_7:
			shield1Animation = shield2Animation = &frontGreen;
			break;

		case LEVEL_8:
			shield1Animation = shield2Animation = &frontGreen;
			break;
		}

		shield1Pos.x = App->player1->position.x + 29;
		shield1Pos.y = App->player1->position.y - 8;
		shield2Pos.x = App->player1->position.x + 29;
		shield2Pos.y = App->player1->position.y + 10;
		break;

		// ---- Stays behind ship
	case TYPE_4:
		switch (App->player1->greenPower)
		{
		case LEVEL_1:
			shield1Animation = shield2Animation = &backRed;
			break;

		case LEVEL_2:
			shield1Animation = shield2Animation = &backGreen;
			break;

		case LEVEL_3:
			shield1Animation = shield2Animation = &backGreen;
			break;

		case LEVEL_4:
			shield1Animation = shield2Animation = &backYellow;
			break;

		case LEVEL_5:
			shield1Animation = shield2Animation = &backYellow;
			break;

		case LEVEL_6:
			shield1Animation = shield2Animation = &backGreen;
			break;

		case LEVEL_7:
			shield1Animation = shield2Animation = &backGreen;
			break;

		case LEVEL_8:
			shield1Animation = shield2Animation = &backGreen;
			break;
		}

		shield1Pos.x = App->player1->position.x - shieldHeight;
		shield1Pos.y = App->player1->position.y - 8;
		shield2Pos.x = App->player1->position.x - shieldHeight;
		shield2Pos.y = App->player1->position.y + 10;
		break;
	}

	// ---- Updates colliders
	shield1Collider->SetPos(shield1Pos.x + App->render->camera.x, shield1Pos.y + App->render->camera.y);
	shield2Collider->SetPos(shield2Pos.x + App->render->camera.x, shield2Pos.y + App->render->camera.y);

	// ----------> shield1Rect = base_anim.GetCurrentFrame();

	// ---- Draw Everything
	SDL_Rect shield1Rect = shield1Animation->GetCurrentFrame();
	SDL_Rect shield2Rect = shield2Animation->GetCurrentFrame();

	App->render->Blit(graphics, shield1Pos.x + App->render->camera.x, shield1Pos.y + App->render->camera.y, &shield1Rect);	//false before
	App->render->Blit(graphics, shield2Pos.x + App->render->camera.x, shield2Pos.y + App->render->camera.y, &shield2Rect);

	return update_status::UPDATE_CONTINUE;
}

void ModuleShieldsP1::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER_SHIELD)
	{
		if (life > 1)
			life--;

		else
		{
			if (shield1Collider != nullptr)
				shield1Collider->to_delete = true;
			if (shield2Collider != nullptr)
				shield2Collider->to_delete = true;

			Disable();	// Could create problems, maybe a direct deletion is needed
		}
	}
}

bool ModuleShieldsP1::CleanUp()
{
	// Remove all memory leaks
	LOG("Unloading shield");
	App->textures->Unload(graphics);

	//Get rid of colliders;
	shield1Collider = nullptr;
	shield2Collider = nullptr;

	return true;
}

void ModuleShieldsP1::spinTheShields(Animation* shield1Animation, Animation* shield2Animation, int greenLevel)
{
	// start at PI/2 radians (90 degrees) and moves by substraction (- instead of +), to 0, 3/4PI and PI

	//x = cx + r * cos(a);
	//y = cy + r * sin(a);
	//radians = 2PI

	//Where r is the radius, cx, cy the origin, and a the angle.

	shield1Pos.x = (int)(App->player1->position.x + 5 + RADIUS * cosf(angle));
	shield1Pos.y = (int)(App->player1->position.y + 0 - RADIUS * sinf(angle));

	shield2Pos.x = (int)(App->player1->position.x + 5 + RADIUS * cosf(angle + 3.0f));
	shield2Pos.y = (int)(App->player1->position.y + 0 - RADIUS * sinf(angle + 3.0f));

	angle -= 0.1f;

	if (angle == 0)
		angle = 2.0f;

	if (greenLevel == LEVEL_1)
	{
		if (angle <= 0.2f)
			shield1Animation = shield2Animation = &frontRed;

		else if (angle <= 0.4f)
			shield1Animation = shield2Animation = &frontRed;	//&topRightRed;

		else if (angle <= 0.7f)
			shield1Animation = shield2Animation = &topRed;

		else if (angle <= 0.9f)
			shield1Animation = shield2Animation = &topRed;	//&topLeftRed;

		else if (angle <= 1.2f)
			shield1Animation = shield2Animation = &backRed;

		else if (angle <= 1.4f)
			shield1Animation = shield2Animation = &backRed;	//&bottomLeftRed;

		else if (angle <= 1.7f)
			shield1Animation = shield2Animation = &bottomRed;

		else if (angle <= 1.9f)
			shield1Animation = shield2Animation = &bottomRed;	//&bottomRightRed;

		else if (angle <= 2.0f)
			shield1Animation = shield2Animation = &frontRed;
	}

	else if (greenLevel == LEVEL_2 ||
		greenLevel == LEVEL_3 ||
		greenLevel == LEVEL_6 ||
		greenLevel == LEVEL_7 ||
		greenLevel == LEVEL_8)
	{
		if (angle <= 0.2f)
			shield1Animation = shield2Animation = &frontGreen;

		else if (angle <= 0.4f)
			shield1Animation = shield2Animation = &frontGreen;	//&topRightGreen;

		else if (angle <= 0.7f)
			shield1Animation = shield2Animation = &topGreen;

		else if (angle <= 0.9f)
			shield1Animation = shield2Animation = &topGreen;	//&topLeftGreen;

		else if (angle <= 1.2f)
			shield1Animation = shield2Animation = &backGreen;

		else if (angle <= 1.4f)
			shield1Animation = shield2Animation = &backGreen;	//&bottomLeftGreen;

		else if (angle <= 1.7f)
			shield1Animation = shield2Animation = &bottomGreen;

		else if (angle <= 1.9f)
			shield1Animation = shield2Animation = &bottomGreen;	//&bottomRightGreen;

		else if (angle <= 2.0f)
			shield1Animation = shield2Animation = &frontGreen;
	}

	else if (greenLevel == LEVEL_4 ||
		greenLevel == LEVEL_5)

	{
		if (angle <= 0.2f)
			shield1Animation = shield2Animation = &frontYellow;

		else if (angle <= 0.4f)
			shield1Animation = shield2Animation = &frontYellow;	//&topRightYellow;

		else if (angle <= 0.7f)
			shield1Animation = shield2Animation = &topYellow;

		else if (angle <= 0.9f)
			shield1Animation = shield2Animation = &topYellow;	//&topLeftYellow;

		else if (angle <= 1.2f)
			shield1Animation = shield2Animation = &backYellow;

		else if (angle <= 1.4f)
			shield1Animation = shield2Animation = &backYellow;	//&bottomLeftYellow;

		else if (angle <= 1.7f)
			shield1Animation = shield2Animation = &bottomYellow;

		else if (angle <= 1.9f)
			shield1Animation = shield2Animation = &bottomYellow;	//&bottomRightYellow;

		else if (angle <= 2.0f)
			shield1Animation = shield2Animation = &frontYellow;
	}
}

int ModuleShieldsP1::checkShieldsLife(int life)
{
	if (life <= 5)
		return LEVEL_1;

	else if (life <= 10)
		return LEVEL_2;

	else if (life <= 15)
		return LEVEL_3;

	else if (life <= 20)
		return LEVEL_4;

	else if (life <= 25)
		return LEVEL_5;

	else if (life <= 30)
		return LEVEL_6;

	else if (life <= 35)
		return LEVEL_7;

	else if (life <= 40)
		return LEVEL_8;
}