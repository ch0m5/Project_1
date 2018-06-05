#include <math.h>
#include "p2Point.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleShieldsP2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleTextures.h"
#include "ModuleMixer.h"

ModuleShieldsP2::ModuleShieldsP2()
{
	/* SOUNDS FX NEEDED
	Power_Up_Picked
	Power_Up_UNIT_SHIELDS_EQUIPPED
	Power_Up_UNIT_SHIELDS_EQUIPPING
	*/

	//Blitting needs fixing, except for front
	//Front
	frontRed.PushBack({ 510 + shieldWidth * 0, 288, shieldWidth, shieldHeight });
	frontRed.PushBack({ 510 + shieldWidth * 1, 288, shieldWidth, shieldHeight });
	frontRed.PushBack({ 510 + shieldWidth * 2, 288, shieldWidth, shieldHeight });
	frontRed.PushBack({ 510 + shieldWidth * 3, 288, shieldWidth, shieldHeight });
	frontRed.PushBack({ 510 + shieldWidth * 4, 288, shieldWidth, shieldHeight });
	frontRed.PushBack({ 510 + shieldWidth * 5, 288, shieldWidth, shieldHeight });
	frontRed.loop = true;
	frontRed.speed = 0.2f;

	frontGreen.PushBack({ 510 + shieldWidth * 0, 304, shieldWidth, shieldHeight });
	frontGreen.PushBack({ 510 + shieldWidth * 1, 304, shieldWidth, shieldHeight });
	frontGreen.PushBack({ 510 + shieldWidth * 2, 304, shieldWidth, shieldHeight });
	frontGreen.PushBack({ 510 + shieldWidth * 3, 304, shieldWidth, shieldHeight });
	frontGreen.PushBack({ 510 + shieldWidth * 4, 304, shieldWidth, shieldHeight });
	frontGreen.PushBack({ 510 + shieldWidth * 5, 304, shieldWidth, shieldHeight });
	frontGreen.loop = true;
	frontGreen.speed = 0.2f;

	frontYellow.PushBack({ 510 + shieldWidth * 0, 272, shieldWidth, shieldHeight });
	frontYellow.PushBack({ 510 + shieldWidth * 1, 272, shieldWidth, shieldHeight });
	frontYellow.PushBack({ 510 + shieldWidth * 2, 272, shieldWidth, shieldHeight });
	frontYellow.PushBack({ 510 + shieldWidth * 3, 272, shieldWidth, shieldHeight });
	frontYellow.PushBack({ 510 + shieldWidth * 4, 272, shieldWidth, shieldHeight });
	frontYellow.PushBack({ 510 + shieldWidth * 5, 272, shieldWidth, shieldHeight });
	frontYellow.loop = true;
	frontYellow.speed = 0.2f;

	//Back
	backRed.PushBack({ 512 + shieldWidth * 0, 336, shieldWidth, shieldHeight });
	backRed.PushBack({ 512 + shieldWidth * 1, 336, shieldWidth, shieldHeight });
	backRed.PushBack({ 512 + shieldWidth * 2, 336, shieldWidth, shieldHeight });
	backRed.PushBack({ 512 + shieldWidth * 3, 336, shieldWidth, shieldHeight });
	backRed.PushBack({ 512 + shieldWidth * 4, 336, shieldWidth, shieldHeight });
	backRed.PushBack({ 512 + shieldWidth * 5, 336, shieldWidth - 1, shieldHeight });
	backRed.loop = true;
	backRed.speed = 0.2f;

	backGreen.PushBack({ 512 + shieldWidth * 0, 320, shieldWidth, shieldHeight });
	backGreen.PushBack({ 512 + shieldWidth * 1, 320, shieldWidth, shieldHeight });
	backGreen.PushBack({ 512 + shieldWidth * 2, 320, shieldWidth, shieldHeight });
	backGreen.PushBack({ 512 + shieldWidth * 3, 320, shieldWidth, shieldHeight });
	backGreen.PushBack({ 512 + shieldWidth * 4, 320, shieldWidth, shieldHeight });
	backGreen.PushBack({ 512 + shieldWidth * 5, 320, shieldWidth - 1, shieldHeight });
	backGreen.loop = true;
	backGreen.speed = 0.2f;

	backYellow.PushBack({ 512 + shieldWidth * 0, 352, shieldWidth, shieldHeight });
	backYellow.PushBack({ 512 + shieldWidth * 1, 352, shieldWidth, shieldHeight });
	backYellow.PushBack({ 512 + shieldWidth * 2, 352, shieldWidth, shieldHeight });
	backYellow.PushBack({ 512 + shieldWidth * 3, 352, shieldWidth, shieldHeight });
	backYellow.PushBack({ 512 + shieldWidth * 4, 352, shieldWidth, shieldHeight });
	backYellow.PushBack({ 512 + shieldWidth * 5, 352, shieldWidth - 1, shieldHeight });
	backYellow.loop = true;
	backYellow.speed = 0.2f;

	//Top
	topRed.PushBack({ 623, 273 + shieldHeight * 0, shieldWidth, shieldHeight });
	topRed.PushBack({ 623, 273 + shieldHeight * 1, shieldWidth, shieldHeight });
	topRed.PushBack({ 623, 273 + shieldHeight * 2, shieldWidth, shieldHeight });
	topRed.PushBack({ 623, 273 + shieldHeight * 3, shieldWidth, shieldHeight });
	topRed.PushBack({ 623, 273 + shieldHeight * 4, shieldWidth, shieldHeight });
	topRed.PushBack({ 623, 273 + shieldHeight * 5, shieldWidth, shieldHeight });
	topRed.loop = true;
	topRed.speed = 0.3f;

	topGreen.PushBack({ 639, 273 + shieldHeight * 0, shieldWidth, shieldHeight });
	topGreen.PushBack({ 639, 273 + shieldHeight * 1, shieldWidth, shieldHeight });
	topGreen.PushBack({ 639, 273 + shieldHeight * 2, shieldWidth, shieldHeight });
	topGreen.PushBack({ 639, 273 + shieldHeight * 3, shieldWidth, shieldHeight });
	topGreen.PushBack({ 639, 273 + shieldHeight * 4, shieldWidth, shieldHeight });
	topGreen.PushBack({ 639, 273 + shieldHeight * 5, shieldWidth, shieldHeight });
	topGreen.loop = true;
	topGreen.speed = 0.3f;

	topYellow.PushBack({ 607, 273 + shieldHeight * 0, shieldWidth, shieldHeight });
	topYellow.PushBack({ 607, 273 + shieldHeight * 1, shieldWidth, shieldHeight });
	topYellow.PushBack({ 607, 273 + shieldHeight * 2, shieldWidth, shieldHeight });
	topYellow.PushBack({ 607, 273 + shieldHeight * 3, shieldWidth, shieldHeight });
	topYellow.PushBack({ 607, 273 + shieldHeight * 4, shieldWidth, shieldHeight });
	topYellow.PushBack({ 607, 273 + shieldHeight * 5, shieldWidth, shieldHeight });
	topYellow.loop = true;
	topYellow.speed = 0.3f;

	//Bottom
	bottomRed.PushBack({ 671, 271 + shieldHeight * 0, shieldWidth, shieldHeight });
	bottomRed.PushBack({ 671, 271 + shieldHeight * 1, shieldWidth, shieldHeight });
	bottomRed.PushBack({ 671, 271 + shieldHeight * 2, shieldWidth, shieldHeight });
	bottomRed.PushBack({ 671, 271 + shieldHeight * 3, shieldWidth, shieldHeight });
	bottomRed.PushBack({ 671, 271 + shieldHeight * 4, shieldWidth, shieldHeight });
	bottomRed.PushBack({ 671, 271 + shieldHeight * 5, shieldWidth, shieldHeight });
	bottomRed.loop = true;
	bottomRed.speed = 0.3f;

	bottomGreen.PushBack({ 655, 271 + shieldHeight * 0, shieldWidth, shieldHeight });
	bottomGreen.PushBack({ 655, 271 + shieldHeight * 1, shieldWidth, shieldHeight });
	bottomGreen.PushBack({ 655, 271 + shieldHeight * 2, shieldWidth, shieldHeight });
	bottomGreen.PushBack({ 655, 271 + shieldHeight * 3, shieldWidth, shieldHeight });
	bottomGreen.PushBack({ 655, 271 + shieldHeight * 4, shieldWidth, shieldHeight });
	bottomGreen.PushBack({ 655, 271 + shieldHeight * 5, shieldWidth, shieldHeight });
	bottomGreen.loop = true;
	bottomGreen.speed = 0.3f;

	bottomYellow.PushBack({ 687, 271 + shieldHeight * 0, shieldWidth, shieldHeight });
	bottomYellow.PushBack({ 687, 271 + shieldHeight * 1, shieldWidth, shieldHeight });
	bottomYellow.PushBack({ 687, 271 + shieldHeight * 2, shieldWidth, shieldHeight });
	bottomYellow.PushBack({ 687, 271 + shieldHeight * 3, shieldWidth, shieldHeight });
	bottomYellow.PushBack({ 687, 271 + shieldHeight * 4, shieldWidth, shieldHeight });
	bottomYellow.PushBack({ 687, 271 + shieldHeight * 5, shieldWidth, shieldHeight });
	bottomYellow.loop = true;
	bottomYellow.speed = 0.3f;
}

ModuleShieldsP2::~ModuleShieldsP2() {}

bool ModuleShieldsP2::Start()
{
	bool ret = true;

	LOG("Loading shield sprites");
	graphics = App->textures->Load("Assets/Sprites/Players_Ships/Laser_particles.png");

	if (graphics == nullptr)
	{
		LOG("Loading shield sprites FAILED!");
		ret = false;
	}

	//----channel 7
	shieldsEquipping = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Power_Up_UNIT_SHIELDS_EQUIPPING.wav");
	shieldsEquipped = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Power_Up_UNIT_SHIELDS_EQUIPPED.wav");
	shieldsTypeChange = App->mixer->LoadFX("Assets/Audio/Sounds_FX/HighScore_Name_Entry_Letter_SELECT_or_Shield_Type_Change.wav");

	Mix_VolumeChunk(shieldsEquipping, FXVol);
	Mix_VolumeChunk(shieldsEquipped, FXVol);
	Mix_VolumeChunk(shieldsTypeChange, FXVol);

	// starting rotation angle
	angle = 0.5f;

	//Type 2 starting position as a standard
	shield1Pos.x = App->player2->position.x + 5;
	shield1Pos.y = App->player2->position.y - 8;
	shield2Pos.x = App->player2->position.x + 5;
	shield2Pos.y = App->player2->position.y + 10;

	// ---- Declares colliders for shield parts individually
	shield1Collider = App->collision->AddCollider({ (int)shield1Pos.x, (int)shield1Pos.y, shieldWidth, shieldHeight }, COLLIDER_PLAYER_SHIELD, this);
	shield2Collider = App->collision->AddCollider({ (int)shield2Pos.x, (int)shield2Pos.y, shieldWidth, shieldHeight }, COLLIDER_PLAYER_SHIELD, this);

	shield1Collider->SetPos(shield1Pos.x + App->render->camera.x, shield1Pos.y + App->render->camera.y);
	shield2Collider->SetPos(shield2Pos.x + App->render->camera.x, shield2Pos.y + App->render->camera.y);

	return ret;
}

update_status ModuleShieldsP2::Update()
{
	App->player2->greenPower = checkShieldsLife(life);

	switch (App->player2->type)
	{
	case TYPE_1:
		switch (App->player2->greenPower)
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
		switch (App->player2->greenPower)
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

		shield1Pos.x = App->player2->position.x + 5;
		shield1Pos.y = App->player2->position.y - 15;
		shield2Pos.x = App->player2->position.x + 5;
		shield2Pos.y = App->player2->position.y + 17;
		break;

		// ---- Stays in front of ship
	case TYPE_3:
		switch (App->player2->greenPower)
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

		shield1Pos.x = App->player2->position.x + 29;
		shield1Pos.y = App->player2->position.y - 5;
		shield2Pos.x = App->player2->position.x + 29;
		shield2Pos.y = App->player2->position.y + 13;
		break;

		// ---- Stays behind ship
	case TYPE_4:
		switch (App->player2->greenPower)
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

		shield1Pos.x = App->player2->position.x - shieldHeight;
		shield1Pos.y = App->player2->position.y - 5;
		shield2Pos.x = App->player2->position.x - shieldHeight;
		shield2Pos.y = App->player2->position.y + 13;
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

void ModuleShieldsP2::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_PLAYER_SHIELD)
	{
		if (life > 1)
			life--;

		else
		{
			life--;
			App->player2->greenPower = LEVEL_0;

			if (shield1Collider != nullptr)
				shield1Collider->to_delete = true;
			if (shield2Collider != nullptr)
				shield2Collider->to_delete = true;

			Disable();
		}
	}
}

bool ModuleShieldsP2::CleanUp()
{
	// Remove all memory leaks
	LOG("Unloading shield");
	App->textures->Unload(graphics);

	if (shield1Collider != nullptr)
		shield1Collider->to_delete = true;
	if (shield2Collider != nullptr)
		shield2Collider->to_delete = true;

	App->mixer->UnloadFx(shieldsEquipping);
	App->mixer->UnloadFx(shieldsEquipped);
	App->mixer->UnloadFx(shieldsTypeChange);

	//Get rid of colliders
	shield1Collider = nullptr;
	shield2Collider = nullptr;

	return true;
}

void ModuleShieldsP2::spinTheShields(Animation* shield1Animation, Animation* shield2Animation, int greenLevel)
{
	// start at PI/2 radians (90 degrees) and moves by substraction (- instead of +), to 0, 3/4PI and PI

	//x = cx + r * cos(a);
	//y = cy + r * sin(a);
	//radians = 2PI

	//Where r is the radius, cx, cy the origin, and a the angle.

	shield1Pos.x = (int)(App->player2->position.x + 5 + RADIUS * cosf(angle));
	shield1Pos.y = (int)(App->player2->position.y + 0 - RADIUS * sinf(angle));

	shield2Pos.x = (int)(App->player2->position.x + 5 + RADIUS * cosf(angle + 3.0f));	// before was 3
	shield2Pos.y = (int)(App->player2->position.y + 0 - RADIUS * sinf(angle + 3.0f));

	angle -= 0.1f;

	if (angle == 0.0f)
		angle = 2.0f;

	if (greenLevel == LEVEL_1)
	{
		if (angle <= 0.2f)
		{
			shield1Animation = &frontRed;
			shield2Animation = &backRed;
		}

		else if (angle <= 0.4f)
		{
			shield1Animation = &frontRed;	//&topRightRed;
			shield2Animation = &backRed;
		}

		else if (angle <= 0.7f)
		{
			shield1Animation = &topRed;
			shield2Animation = &bottomRed;
		}

		else if (angle <= 0.9f)
		{
			shield1Animation = &topRed;		//&topLeftRed;
			shield2Animation = &bottomRed;
		}

		else if (angle <= 1.2f)
		{
			shield1Animation = &backRed;
			shield2Animation = &frontRed;
		}

		else if (angle <= 1.4f)
		{
			shield1Animation = &backRed;	//&bottomLeftRed
			shield2Animation = &frontRed;
		}

		else if (angle <= 1.7f)
		{
			shield1Animation = &bottomRed;
			shield2Animation = &topRed;
		}

		else if (angle <= 1.9f)
		{
			shield1Animation = &bottomRed;	//&bottomRightRed;
			shield2Animation = &topRed;
		}

		else if (angle <= 2.0f)
		{
			shield1Animation = &frontRed;
			shield2Animation = &backRed;
		}
	}

	else if (greenLevel == LEVEL_2 ||
		greenLevel == LEVEL_3 ||
		greenLevel == LEVEL_6 ||
		greenLevel == LEVEL_7 ||
		greenLevel == LEVEL_8)
	{
		if (angle <= 0.2f)
		{
			shield1Animation = &frontGreen;
			shield2Animation = &backGreen;
		}

		else if (angle <= 0.4f)
		{
			shield1Animation = &frontGreen;	//&topRightRed;
			shield2Animation = &backGreen;
		}

		else if (angle <= 0.7f)
		{
			shield1Animation = &topGreen;
			shield2Animation = &bottomGreen;
		}

		else if (angle <= 0.9f)
		{
			shield1Animation = &topGreen;	//&topLeftRed;
			shield2Animation = &bottomGreen;
		}

		else if (angle <= 1.2f)
		{
			shield1Animation = &backGreen;
			shield2Animation = &frontGreen;
		}

		else if (angle <= 1.4f)
		{
			shield1Animation = &backGreen;	//&bottomLeftRed
			shield2Animation = &frontGreen;
		}

		else if (angle <= 1.7f)
		{
			shield1Animation = &bottomGreen;
			shield2Animation = &topGreen;
		}

		else if (angle <= 1.9f)
		{
			shield1Animation = &bottomGreen;	//&bottomRightRed;
			shield2Animation = &topGreen;
		}

		else if (angle <= 2.0f)
		{
			shield1Animation = &frontGreen;
			shield2Animation = &backGreen;
		}
	}

	else if (greenLevel == LEVEL_4 ||
		greenLevel == LEVEL_5)

	{
		if (angle <= 0.2f)
		{
			shield1Animation = &frontYellow;
			shield2Animation = &backYellow;
		}

		else if (angle <= 0.4f)
		{
			shield1Animation = &frontYellow;	//&topRightRed;
			shield2Animation = &backYellow;
		}

		else if (angle <= 0.7f)
		{
			shield1Animation = &topYellow;
			shield2Animation = &bottomYellow;
		}

		else if (angle <= 0.9f)
		{
			shield1Animation = &topYellow;		//&topLeftRed;
			shield2Animation = &bottomYellow;
		}

		else if (angle <= 1.2f)
		{
			shield1Animation = &backYellow;
			shield2Animation = &frontYellow;
		}

		else if (angle <= 1.4f)
		{
			shield1Animation = &backYellow;	//&bottomLeftRed
			shield2Animation = &frontYellow;
		}

		else if (angle <= 1.7f)
		{
			shield1Animation = &bottomYellow;
			shield2Animation = &topYellow;
		}

		else if (angle <= 1.9f)
		{
			shield1Animation = &bottomYellow;	//&bottomRightRed;
			shield2Animation = &topYellow;
		}

		else if (angle <= 2.0f)
		{
			shield1Animation = &frontYellow;
			shield2Animation = &backYellow;
		}
	}
}

int ModuleShieldsP2::checkShieldsLife(int life)
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