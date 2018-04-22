#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleMixer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleHiScore.h"
#include "ModuleStage1.h"
#include "ModuleStage2.h"


ModulePlayer2::ModulePlayer2()	// @CarlesHoms @Andres
{
	shipAnimation = nullptr;
	shipWidth = 27;
	shipHeight = 17;

	propellerAnimation = nullptr;
	propellerWidth = 12;
	propellerHeight = 17;

	crashAnimation = nullptr;

	// Starting point of the ship (using p2Point)
	position.x = 0;
	position.y = SCREEN_HEIGHT / 2 - 10;

	movVertical = 0;	// Counter for the vertical movement of the ship
	maxVertical = 14;	// Limit of the counter

	laserFrontOffset = 20;		// Offset for front bullets
	laserBackOffset = 18;		// Offset for back bullets		// Distance from ship position to bullet creation
	laserVerticalOffset = 11;	// Offset for all bullets

	type = TYPE_1;				// Flag/counter for type equipped
	bluePower = LEVEL_1;		// Flag/counter for blue power level
	orangePower = LEVEL_0;		// Flag/counter for orange power level
	yellowPower = LEVEL_0;		// Flag/counter for yellow power level
	greenPower = LEVEL_0;		// Flag/counter for green power level

	/*
	Sprites positioning

	154, 66; superup
	154, 87; up
	154, 108; idle
	154, 131; down
	154, 153; superdown
	27, 17; size

	42, 63; superup first flame
	59, 63; superup second flame
	73, 63; superup third flame
	
	43, 86; up first flame
	60, 86; up second flame
	74, 86; up third flame

	43, 109; idle first flame
	62, 109; idle second flame
	74, 109; idle third flame

	43, 133; down first flame
	60, 133; down second flame
	74, 133; down third flame

	43, 153; superdown first flame
	60, 153; superdown second flame
	74, 153; superdown third flame

	12, 17; size
	*/

	/*GoingUp
	goingDown.PushBack({ 94, 66, 27, 17 });
	goingDown.PushBack({ 94, 87, 27, 17 });
	goingDown.PushBack({ 94, 108, 27, 17 });
	goingDown.PushBack({ 94, 131, 27, 17 });
	goingDown.PushBack({ 94, 153, 27, 17 });

	goingDown.PushBack({ 94, 153, 27, 17 });
	goingDown.PushBack({ 94, 131, 27, 17 });
	goingDown.PushBack({ 94, 108, 27, 17 });
	goingDown.PushBack({ 94, 87, 27, 17 });
	goingDown.PushBack({ 94, 66, 27, 17 });
	*/

	// Ship "animation" (works as an array of states which you switch from based on the movVertical counter)
	shipVerticalMovement.PushBack({ 154, 66, shipWidth, shipHeight });
	shipVerticalMovement.PushBack({ 154, 87, shipWidth, shipHeight });
	shipVerticalMovement.PushBack({ 154, 108, shipWidth, shipHeight });
	shipVerticalMovement.PushBack({ 154, 131, shipWidth, shipHeight });
	shipVerticalMovement.PushBack({ 154, 153, shipWidth, shipHeight });

	// Booster animations
	superUpwardsBooster.PushBack({ 42, 63, propellerWidth, propellerHeight });
	superUpwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	superUpwardsBooster.PushBack({ 59, 63, propellerWidth, propellerHeight });
	superUpwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	superUpwardsBooster.PushBack({ 73, 63, propellerWidth, propellerHeight });
	superUpwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	superUpwardsBooster.speed = 1.4f;

	upwardsBooster.PushBack({ 43, 86, propellerWidth, propellerHeight });
	upwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	upwardsBooster.PushBack({ 60, 86, propellerWidth, propellerHeight });
	upwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	upwardsBooster.PushBack({ 74, 86, propellerWidth, propellerHeight });
	upwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	upwardsBooster.speed = 1.4f;

	idleBooster.PushBack({ 43, 109, propellerWidth, propellerHeight });
	idleBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	idleBooster.PushBack({ 62, 109, propellerWidth, propellerHeight });
	idleBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	idleBooster.PushBack({ 74, 109, propellerWidth, propellerHeight });
	idleBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	idleBooster.speed = 1.4f;

	downwardsBooster.PushBack({ 43, 133, propellerWidth, propellerHeight });
	downwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	downwardsBooster.PushBack({ 60, 133, propellerWidth, propellerHeight });
	downwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	downwardsBooster.PushBack({ 74, 133, propellerWidth, propellerHeight });
	downwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	downwardsBooster.speed = 1.4f;

	superDownwardsBooster.PushBack({ 43, 153, propellerWidth, propellerHeight });
	superDownwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	superDownwardsBooster.PushBack({ 60, 153, propellerWidth, propellerHeight });
	superDownwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	superDownwardsBooster.PushBack({ 74, 153, propellerWidth, propellerHeight });
	superDownwardsBooster.PushBack({ 0, 0, propellerWidth, propellerHeight });
	superDownwardsBooster.speed = 1.4f;

	// Animation
	crash.PushBack({ 42, 333, 27, 17 });
	crash.PushBack({ 79, 333, 28, 18 });
	crash.PushBack({ 117, 333, 30, 21 });
	crash.PushBack({ 157, 333, 31, 25 });

	crash.PushBack({ 42, 361, 32, 27 });
	crash.PushBack({ 79, 361, 32, 31 });
	crash.PushBack({ 117, 361, 32, 32 });

	//same for player 1 from know on
	crash.PushBack({ 157, 251, 30, 30 });

	crash.PushBack({ 42, 284, 27, 17 });
	crash.PushBack({ 79, 284, 24, 15 });
	crash.PushBack({ 117, 284, 19, 11 });
	crash.PushBack({ 157, 284, 15, 9 });

	crash.PushBack({ 42, 304, 17, 13 });
	crash.PushBack({ 79, 304, 15, 15 });
	crash.PushBack({ 117, 304, 30, 21 });
	crash.PushBack({ 157, 304, 2, 1 });
	crash.speed = 0.3f;
	crash.loop = false;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	destroyed = false;
	graphics = App->textures->Load("Assets/Sprites/Players_Ships/ships_all.png"); // arcade version

	//Music
	type1Shot = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type-1_(Main_Ships).wav");
	type2Shot = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type-2_(Main_Ships).wav");
	type3Shot = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type-3_(Main_Ships).wav");
	type4Shot = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type-4_(Main_Ships).wav");
	typeSwap = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type_CHANGE.wav");
	powerUp = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Power_Up_Picked.wav");
	playerDeathExplosion = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Player_Death_Explosion.wav");

	Mix_VolumeChunk(type1Shot, FXVol);
	Mix_VolumeChunk(type2Shot, FXVol);
	Mix_VolumeChunk(type3Shot, FXVol);
	Mix_VolumeChunk(type4Shot, FXVol);
	Mix_VolumeChunk(typeSwap, FXVol);
	Mix_VolumeChunk(powerUp, FXVol);
	Mix_VolumeChunk(playerDeathExplosion, FXVol);

	// Place player hitbox
	playerHitbox = App->collision->AddCollider({ App->render->camera.x / SCREEN_SIZE + (int)position.x,App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight, }, COLLIDER_PLAYER, this);

	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()	// Moves the ship and changes it's printed sprite depending on a counter.
{
	// How it works: A counter (movVertical) changes values by pressing UP, DOWN or neither and then one of the SDL_Rects inside
	// the frames array of ship animation (shipVerticalMovement) is blited depending on the value of the counter.

	shipAnimation = &shipVerticalMovement;
	propellerAnimation = &idleBooster;
	shipRect = &shipAnimation->frames[SHIP_IDLE];

	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE ||
		App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
		App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (movVertical > 0)
		{
			--movVertical;		// Decrease vertical counter.
		}

		if (movVertical < 0)
		{
			++movVertical;		// Increase vertical counter.
		}
	}

	//Player Movement
	else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT  && destroyed == false)
	{
		if (position.y < SCREEN_HEIGHT - shipHeight)
		{
			position.y += speed;
		}

		if (movVertical > -maxVertical)
		{
			--movVertical;		// Decrease vertical counter. Animation Purpose.
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT  && destroyed == false)
	{
		if (position.y > 0)
		{
			position.y -= speed;
		}

		if (movVertical < maxVertical)
		{
			++movVertical;		// Increase vertical counter. Animation Purpose.
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && position.x > 0 && destroyed == false)
	{
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && position.x < SCREEN_WIDTH - shipWidth  && destroyed == false)
	{
		position.x += speed;
	}

	// Depending on the vertical counter, we decide the animation

	if (movVertical >= maxVertical)
	{
		shipRect = &shipAnimation->frames[SHIP_FULL_UP];
		propellerAnimation = &superUpwardsBooster;
	}

	else if (movVertical > (maxVertical / 2) && movVertical < maxVertical)
	{
		shipRect = &shipAnimation->frames[SHIP_UP];
		propellerAnimation = &upwardsBooster;
	}

	else if (movVertical <= (maxVertical / 2) && movVertical >= -(maxVertical / 2))
	{
		shipRect = &shipAnimation->frames[SHIP_IDLE];
		propellerAnimation = &idleBooster;
	}

	else if (movVertical < -(maxVertical / 2) && movVertical > -maxVertical)
	{
		shipRect = &shipAnimation->frames[SHIP_DOWN];
		propellerAnimation = &downwardsBooster;
	}

	else if (movVertical <= -maxVertical)
	{
		shipRect = &shipAnimation->frames[SHIP_FULL_DOWN];
		propellerAnimation = &superDownwardsBooster;
	}

	// (TEMPORAL) level up and down
	if (App->input->keyboard[SDL_SCANCODE_6] == KEY_DOWN && bluePower < LEVEL_7)	// Level up blue
	{
		bluePower++;
		Mix_PlayChannel(3, powerUp, 0);
	}

	if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN && orangePower < LEVEL_5)	// Level up orange
	{
		orangePower++;
		Mix_PlayChannel(3, powerUp, 0);
	}

	if (App->input->keyboard[SDL_SCANCODE_8] == KEY_DOWN && yellowPower < LEVEL_8)	// Level up yellow
	{
		yellowPower++;
		Mix_PlayChannel(3, powerUp, 0);
	}

	if (App->input->keyboard[SDL_SCANCODE_9] == KEY_DOWN && yellowPower < LEVEL_8)	// Level up green
	{
		greenPower++;
		Mix_PlayChannel(3, powerUp, 0);
	}

	if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN)	// Level all down
	{
		if (bluePower > LEVEL_1)
			bluePower--;

		if (orangePower > LEVEL_0)
			orangePower--;

		if (yellowPower > LEVEL_0)
			yellowPower--;

		if (greenPower > LEVEL_0)
			greenPower--;
	}

	//Change weapon
	if (App->input->keyboard[SDL_SCANCODE_B] == KEY_DOWN)	// Swap type
	{
		if (type >= TYPE_4)
		{
			type = TYPE_1;
		}

		else
			type++;

		switch (type)	// Shield position variation
		{
		case TYPE_1:

			break;

		case TYPE_2:

			break;

		case TYPE_3:

			break;

		case TYPE_4:

			break;
		}

		Mix_PlayChannel(3, typeSwap, 0);
	}

	// Fire lasers
	if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_DOWN)
	{
		switch (type)
		{
		case TYPE_1:
			switch (bluePower)
			{
			case LEVEL_1:
				App->particles->AddParticle(App->particles->smallBlue, position.x + laserFrontOffset, position.y + laserVerticalOffset - 3, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->smallBlue, position.x + laserFrontOffset, position.y + laserVerticalOffset + 3, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_2:
				App->particles->AddParticle(App->particles->smallBlue, position.x + laserFrontOffset, position.y + laserVerticalOffset - 5, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->smallBlue, position.x + laserFrontOffset, position.y + laserVerticalOffset + 0, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->smallBlue, position.x + laserFrontOffset, position.y + laserVerticalOffset + 5, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;

			case LEVEL_6:

				break;

			case LEVEL_7:

				break;
			}

			switch (orangePower)
			{
			case LEVEL_0:
				break;

			case LEVEL_1:

				break;

			case LEVEL_2:

				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;
			}

			switch (yellowPower)
			{
			case LEVEL_0:
				break;

			case LEVEL_1:

				break;

			case LEVEL_2:

				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;

			case LEVEL_6:

				break;

			case LEVEL_7:

				break;

			case LEVEL_8:

				break;
			}

			Mix_PlayChannel(3, type1Shot, 0);
			break;

		case TYPE_2:
			switch (bluePower)
			{
			case LEVEL_1:
				App->particles->AddParticle(App->particles->yellowSmallLeft, position.x + laserFrontOffset, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->yellowSmallRight, position.x - 10, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_2:

				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;

			case LEVEL_6:

				break;

			case LEVEL_7:

				break;
			}

			switch (orangePower)
			{
			case LEVEL_0:
				break;

			case LEVEL_1:
				App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_2:
				App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_3:
				App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_4:
				App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketLeftDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketLeftUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketDownDiagonal, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketUpDiagonal, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				break;

			case LEVEL_5:
				App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketLeftDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketLeftUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketDownDiagonal, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->redRocketUpDiagonal, position.x + 5, position.y + laserVerticalOffset, PLAYER_2_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
				break;
			}

			switch (yellowPower)
			{
			case LEVEL_0:
				break;

			case LEVEL_1:

				break;

			case LEVEL_2:

				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;

			case LEVEL_6:

				break;

			case LEVEL_7:

				break;

			case LEVEL_8:

				break;
			}

			Mix_PlayChannel(3, type2Shot, 0);
			break;

		case TYPE_3:
			switch (bluePower)
			{
			case LEVEL_1:
				App->particles->AddParticle(App->particles->straightGreen, position.x + laserFrontOffset, position.y + laserVerticalOffset - 1, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_2:

				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;

			case LEVEL_6:

				break;

			case LEVEL_7:

				break;
			}

			switch (orangePower)
			{
			case LEVEL_0:
				break;

			case LEVEL_1:
				App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_2:
				App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->bombRightUp, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_3:
				App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->bombRightUp, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_4:
				App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->bombRightUp, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->bombLeftDown, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->bombLeftUp, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_5:
				App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->bombRightUp, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->bombLeftDown, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->bombLeftUp, position.x + 7, position.y + laserVerticalOffset, COLLIDER_PLAYER_2_SHOT);
				break;
			}

			switch (yellowPower)
			{
			case LEVEL_0:
				break;

			case LEVEL_1:

				break;

			case LEVEL_2:

				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;

			case LEVEL_6:

				break;

			case LEVEL_7:

				break;

			case LEVEL_8:

				break;
			}

			Mix_PlayChannel(3, type3Shot, 0);
			break;

		case TYPE_4:
			switch (bluePower)
			{
			case LEVEL_1:
				App->particles->AddParticle(App->particles->arrowUp1, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowDown1, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_2:
				App->particles->AddParticle(App->particles->arrowUp1, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowStraight1, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowDown1, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_3:
				App->particles->AddParticle(App->particles->arrowUp2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowStraight2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowDown2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_4:
				App->particles->AddParticle(App->particles->arrowSuperUp2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowUp2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowDown2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowSuperDown2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_5:
				App->particles->AddParticle(App->particles->arrowSuperUp2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowUp3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowDown3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowSuperDown2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_6:
				App->particles->AddParticle(App->particles->arrowSuperUp2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowUp3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowStraight3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowDown3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowSuperDown2, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				break;

			case LEVEL_7:
				App->particles->AddParticle(App->particles->arrowSuperUp3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowUp3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowStraight3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowDown3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				App->particles->AddParticle(App->particles->arrowSuperDown3, position.x + 14, position.y + 8, COLLIDER_PLAYER_2_SHOT);
				break;
			}

			switch (orangePower)
			{
			case LEVEL_0:
				break;

			case LEVEL_1:

				break;

			case LEVEL_2:

				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;
			}

			switch (yellowPower)
			{
			case LEVEL_0:
				break;

			case LEVEL_1:

				break;

			case LEVEL_2:

				break;

			case LEVEL_3:

				break;

			case LEVEL_4:

				break;

			case LEVEL_5:

				break;

			case LEVEL_6:

				break;

			case LEVEL_7:

				break;

			case LEVEL_8:

				break;
			}

			Mix_PlayChannel(3, type4Shot, 0);
			break;
		}
	}

	//GodMode Function
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN && App->input->debugMode == true)
	{
		if (App->input->debugMode == false)
		{
			godMode = false;
		}
		if (App->input->keyboard[SDL_SCANCODE_F2] != KEY_REPEAT && App->input->debugMode == true)
		{
			godMode = !godMode;
		}
		
			if (godMode == true)
			{
				playerHitbox->to_delete = true;
				playerHitbox = nullptr;
			}
		
			else if (godMode == false)
			{
			godMode = false;
			playerHitbox = App->collision->AddCollider({ App->render->camera.x / SCREEN_SIZE + (int)position.x, App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight }, COLLIDER_PLAYER, this);
			}
	}

	// Update collider position to player position
	if (godMode == false)
	{
		playerHitbox->SetPos(App->render->camera.x / SCREEN_SIZE + position.x, App->render->camera.y / SCREEN_SIZE + position.y);
	}

	// Draw everything --------------------------------------
	if (destroyed == false)
	{
		SDL_Rect propellerRect = propellerAnimation->GetCurrentFrame();

		App->render->Blit(graphics, position.x - propellerWidth, position.y, &propellerRect, 1.0f, false);
		App->render->Blit(graphics, position.x, position.y, shipRect, 1.0f, false);
	}
	if (destroyed == true)
	{
		SDL_Rect crashrect = crashAnimation->GetCurrentFrame();
		App->render->Blit(graphics, position.x, position.y, &crashrect, 1.0f, false);


	}
	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player 2");
	App->textures->Unload(graphics);

	App->player2->Disable();

	App->mixer->UnloadFx(type1Shot);
	App->mixer->UnloadFx(type2Shot);
	App->mixer->UnloadFx(type3Shot);
	App->mixer->UnloadFx(type4Shot);
	App->mixer->UnloadFx(typeSwap);
	App->mixer->UnloadFx(powerUp);
	App->mixer->UnloadFx(playerDeathExplosion);

	//Reset player pos
	position.x = 0;							// Starting point of the ship (using p2Point)
	position.y = SCREEN_HEIGHT / 2 - 10;

	shipAnimation = nullptr;
	propellerAnimation = nullptr;
	crashAnimation = nullptr;
	crash.Reset();

	return true;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	Mix_PlayChannel(3, playerDeathExplosion, 0);

	if ((c1->type == COLLIDER_WALL ||
		c2->type == COLLIDER_WALL ||
		c1->type == COLLIDER_ENEMY_SHOT || //Cambio @andres
		c2->type == COLLIDER_ENEMY_SHOT || //Cambio @andres
		c1->type == COLLIDER_ENEMY ||		//Cambio @andres
		c2->type == COLLIDER_ENEMY))		//Cambio @andres
	{
		crashAnimation = &crash;
		destroyed = true;
		playerHitbox->to_delete = true;
		App->fade->FadeToBlack(App->stage1, App->scene_HiScore);	// HARDCODED: Needs "current stage" functionality
	}
}