#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleMixer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleHiScore.h"
#include "ModuleStage1.h"
#include "ModuleStage2.h"
#include "ModuleFont.h"
#include "ModuleUserInterface.h"
#include "ModuleShieldsP1.h"

ModulePlayer1::ModulePlayer1()	// @CarlesHoms @Andres
{
	graphics = nullptr;

	// Animation ship crash
	destroyed = false;

	// Animation pointers
	shipAnimation = nullptr;
	propellerAnimation = nullptr;
	crashAnimation = nullptr;

	// Ship and propeller sizes in pixels
	shipWidth = 27;
	shipHeight = 17;
	propellerWidth = 12;
	propellerHeight = 17;

	maxVertical = 14;	// Limit of the counter

	//Debug Purpose Variables
	godMode = false;

	//Music 
	type1Shot = nullptr;		// All use the same channel: 1
	type2Shot = nullptr;
	type3Shot = nullptr;
	type4Shot = nullptr;

	type1Weapon = nullptr;
	type2Weapon = nullptr;
	type3Weapon = nullptr;
	type4Weapon = nullptr;

	typeSwap = nullptr;		// Channel 0
	powerUp = nullptr;
	playerDeathExplosion = nullptr;

	//Lasers
	laserHorizontalOffset = 18;	// Horizontal Offset for bullets
	laserVerticalOffset = 12;	// Vertical Offset for bullets

	/*
	Sprites positioning

	94, 66; superup
	94, 87; up		
	94, 108; idle
	94, 131; down
	94, 153; superdown
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

	// Ship "animation" (works as an array of states which you switch from based on the movVertical counter)
	shipVerticalMovement.PushBack({ 94, 66, shipWidth, shipHeight });
	shipVerticalMovement.PushBack({ 94, 87, shipWidth, shipHeight });
	shipVerticalMovement.PushBack({ 94, 108, shipWidth, shipHeight });
	shipVerticalMovement.PushBack({ 94, 131, shipWidth, shipHeight });
	shipVerticalMovement.PushBack({ 94, 153, shipWidth, shipHeight });

	shipChargedSuperUp.PushBack({ 257, 66, shipWidth + 5, shipHeight + 6 });
	shipChargedSuperUp.PushBack({ 222, 65, shipWidth + 5, shipHeight + 6 });
	shipChargedSuperUp.speed = 0.8f;

	shipChargedUp.PushBack({ 257, 89, shipWidth + 5, shipHeight + 6 });
	shipChargedUp.PushBack({ 222, 88, shipWidth + 5, shipHeight + 6 });
	shipChargedUp.speed = 0.8f;

	shipCharged.PushBack({ 257, 113, shipWidth + 5, shipHeight + 6 });
	shipCharged.PushBack({ 222, 112, shipWidth + 5, shipHeight + 6 });
	shipCharged.speed = 0.8f;

	shipChargedDown.PushBack({ 257, 138, shipWidth + 5, shipHeight + 6 });
	shipChargedDown.PushBack({ 222, 137, shipWidth + 5, shipHeight + 6 });
	shipChargedDown.speed = 0.8f;

	shipChargedSuperDown.PushBack({ 257, 164, shipWidth + 5, shipHeight + 6 });
	shipChargedSuperDown.PushBack({ 222, 163, shipWidth + 5, shipHeight + 6 });
	shipChargedSuperDown.speed = 0.8f;

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
	crash.PushBack({ 42, 224, 27, 17 });
	crash.PushBack({ 79, 224, 28, 18 });
	crash.PushBack({ 117, 224, 30, 21 });
	crash.PushBack({ 157, 224, 31, 25 });

	crash.PushBack({ 42, 251, 32, 27 });
	crash.PushBack({ 79, 251, 32, 31 });
	crash.PushBack({ 117, 251, 32, 32 });

	//same for player 2 from know on
	crash.PushBack({ 157, 251, 30, 30 });

	crash.PushBack({ 42, 284, 27, 17 });
	crash.PushBack({ 79, 284, 24, 15 });
	crash.PushBack({ 117, 284, 19, 11 });
	crash.PushBack({ 157, 284, 15, 9 });

	crash.PushBack({ 42, 304, 17, 13 });
	crash.PushBack({ 79, 304, 15, 15 });
	crash.PushBack({ 117, 304, 30, 21 });
	crash.PushBack({ 157, 304, 2, 1 });
	crash.PushBack({ 0, 0, 0, 0 }); //MUST FIX THIS AFTER PROTOTYPE Right now prints an epty frame at the end for when player dies
	crash.speed = 0.3f;
	crash.loop = false;
}

ModulePlayer1::~ModulePlayer1()
{}

// Load assets
bool ModulePlayer1::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	destroyed = false;
	App->UI->p1Dead = false;
	lives = 3;
	graphics = App->textures->Load("Assets/Sprites/Players_Ships/ships_all.png"); // arcade version

	//Music and sounds FX
	type1Shot = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type-1_(Main_Ships).wav");
	type2Shot = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type-2_(Main_Ships).wav");
	type3Shot = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type-3_(Main_Ships).wav");
	type4Shot = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type-4_(Main_Ships).wav");
	
	type1Weapon = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Special_Attack_Type-1_(Main_Ships).wav");
	type2Weapon = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Special_Attack_Type-2_(Main_Ships).wav");
	type3Weapon = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Special_Attack_Type-3_(Main_Ships).wav");
	type4Weapon = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Special_Attack_Type-4_(Main_Ships).wav");

	typeSwap = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Laser_Shot_Type_CHANGE.wav");
	typeCharging = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Charging_Special_Attack.wav");
	typeCharged = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Charged_Special_Attack_Loop.wav");
	powerUp = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Power_Up_Picked.wav");
	playerDeathExplosion = App->mixer->LoadFX("Assets/Audio/Sounds_FX/Player_Death_Explosion.wav");

	//Types and levels
	type = TYPE_1;			// Flag/counter for type equipped
	bluePower = LEVEL_1;	// Flag/counter for blue power level
	orangePower = LEVEL_0;	// Flag/counter for orange power level
	yellowPower = LEVEL_0;	// Flag/counter for yellow power level
	greenPower = LEVEL_0;	// Flag/counter for green power level

	currentBlue = 0;	// Every shot increases the counter by 2, player will not shot if it gets higher than 4. Each collide substracts 1.
	currentOrange = 0;	// Every time it fires increases the counter by x (changes on level), player will not shot if it reaches MAX.  Each collide substracts 1.
	currentYellow = 0;	// When reaching level yellow one, the max becomes 5 and the counter increases by 1 for each misile fired. Each collide substracts 1.

	checkBluePowerParticleLimit();

	fireWeapon = NONE;				// Integer that marks which weapon is being fired at the moment (with an enum)
	weaponLaserInterval = 0;	// Marks time between fired lasers in a single weapon shot
	weaponStage = 0;			// Marks stage of currently firing weapon
	weaponLoop = 0;				// Marks the number of loops of the weapon, if any

	blueShotTimer = 0;
	weaponChargeTimer = 0;
	weaponChargingStage = NOT_CHARGING;

	// Starting point of the ship (using p2Point)
	position.x = 0;
	position.y = (int)(SCREEN_HEIGHT / 2 - 10);

	movVertical = 0;	// Counter for the vertical movement of the ship

	//Invincibility stuff
	invStartTime = 0;
	isInvincible = 0;

	Mix_VolumeChunk(type1Shot, FXVol);
	Mix_VolumeChunk(type2Shot, FXVol);
	Mix_VolumeChunk(type3Shot, FXVol);
	Mix_VolumeChunk(type4Shot, FXVol);

	Mix_VolumeChunk(type1Weapon, FXVol);
	Mix_VolumeChunk(type2Weapon, FXVol);
	Mix_VolumeChunk(type3Weapon, FXVol);
	Mix_VolumeChunk(type4Weapon, FXVol);

	Mix_VolumeChunk(typeCharging, FXVol);
	Mix_VolumeChunk(typeCharged, FXVol);
	Mix_VolumeChunk(typeSwap, FXVol);
	Mix_VolumeChunk(powerUp, FXVol);
	Mix_VolumeChunk(playerDeathExplosion, FXVol);
	
	// Place player hitbox
	playerHitbox = App->collision->AddCollider({ (int)position.x, (int)position.y, shipWidth, shipHeight}, COLLIDER_PLAYER, this);
	
	return ret;
}

// Update: draw background
update_status ModulePlayer1::Update()	// Moves the ship and changes it's printed sprite depending on a counter.
{
	if (destroyed == false)
	{
		// How it works: A counter (movVertical) changes values by pressing UP, DOWN or neither and then one of the SDL_Rects inside
		// the frames array of ship animation (shipVerticalMovement) is blited depending on the value of the counter.
		shipAnimation = &shipVerticalMovement;
		propellerAnimation = &idleBooster;
		shipRect = shipAnimation->frames[SHIP_IDLE];

		int speed = 2;

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE &&
			App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE ||
			App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
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
		else if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT && destroyed == false)
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

		else if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT && destroyed == false)
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

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && position.x > 0 && destroyed == false)
		{
			position.x -= speed;
		}

		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && position.x < SCREEN_WIDTH - shipWidth && destroyed == false)
		{
			position.x += speed;
		}

		// Depending on the vertical counter and the weapon charge, we decide the animation
		if (weaponChargingStage == CHARGED || weaponChargingStage == CHARGED_LOOP)
		{
			if (movVertical >= maxVertical)
			{
				shipAnimation = &shipChargedSuperUp;
				propellerAnimation = &superUpwardsBooster;
			}

			else if (movVertical > (maxVertical / 2) && movVertical < maxVertical)
			{
				shipAnimation = &shipChargedUp;
				propellerAnimation = &upwardsBooster;
			}

			else if (movVertical <= (maxVertical / 2) && movVertical >= -(maxVertical / 2))
			{
				shipAnimation = &shipCharged;
				propellerAnimation = &idleBooster;
			}

			else if (movVertical < -(maxVertical / 2) && movVertical > -maxVertical)
			{
				shipAnimation = &shipChargedDown;
				propellerAnimation = &downwardsBooster;
			}

			else if (movVertical <= -maxVertical)
			{
				shipAnimation = &shipChargedSuperDown;
				propellerAnimation = &superDownwardsBooster;
			}
		}

		else
		{
			if (movVertical >= maxVertical)
			{
				shipRect = shipAnimation->frames[SHIP_FULL_UP];
				propellerAnimation = &superUpwardsBooster;
			}

			else if (movVertical > (maxVertical / 2) && movVertical < maxVertical)
			{
				shipRect = shipAnimation->frames[SHIP_UP];
				propellerAnimation = &upwardsBooster;
			}

			else if (movVertical <= (maxVertical / 2) && movVertical >= -(maxVertical / 2))
			{
				shipRect = shipAnimation->frames[SHIP_IDLE];
				propellerAnimation = &idleBooster;
			}

			else if (movVertical < -(maxVertical / 2) && movVertical > -maxVertical)
			{
				shipRect = shipAnimation->frames[SHIP_DOWN];
				propellerAnimation = &downwardsBooster;
			}

			else if (movVertical <= -maxVertical)
			{
				shipRect = shipAnimation->frames[SHIP_FULL_DOWN];
				propellerAnimation = &superDownwardsBooster;
			}
		}

		// (TEMPORAL) level up and down
		if (App->input->debugMode == true)
		{
			if (App->input->keyboard[SDL_SCANCODE_6] == KEY_DOWN && bluePower < LEVEL_7)	// Level up blue
			{
				if (bluePower == LEVEL_1)
					weaponChargeTimer = SDL_GetTicks();

				bluePower++;
				checkBluePowerParticleLimit();
				Mix_PlayChannel(6, powerUp, 0);
			}

			if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN && orangePower < LEVEL_5)	// Level up orange
			{
				orangePower++;
				Mix_PlayChannel(6, powerUp, 0);
			}

			if (App->input->keyboard[SDL_SCANCODE_8] == KEY_DOWN && yellowPower < LEVEL_8)	// Level up yellow
			{
				yellowPower++;
				Mix_PlayChannel(6, powerUp, 0);
			}

			if (App->input->keyboard[SDL_SCANCODE_9] == KEY_DOWN && yellowPower < LEVEL_8)	// Level up green
			{
				if (greenPower <= LEVEL_0)
					App->shieldsP1->Enable();

				greenPower++;
				App->shieldsP1->life += 5;
				Mix_PlayChannel(6, powerUp, 0);
			}

			if (App->input->keyboard[SDL_SCANCODE_0] == KEY_DOWN)	// Level all down
			{
				if (bluePower > LEVEL_1)
					bluePower--;

				checkBluePowerParticleLimit();

				if (orangePower > LEVEL_0)
					orangePower--;

				if (yellowPower > LEVEL_0)
					yellowPower--;

				if (greenPower > LEVEL_0)
				{
					greenPower--;
					App->shieldsP1->life -= 5;
				}

				if (greenPower == LEVEL_0)
				{
					App->shieldsP1->Disable();
					App->shieldsP1->life = 0;
				}
			}
		}

		//Change weapon
		if (App->input->keyboard[SDL_SCANCODE_O] == KEY_DOWN)	// Swap type
		{
			if (type >= TYPE_4)
			{
				type = TYPE_1;
			}

			else { type++; }

			checkBluePowerParticleLimit();	// Changes the new particle limit

			switch (type)	// Shield position and particle maximum variation
			{
			case TYPE_1:

				//Change shield position
				break;

			case TYPE_2:

				//Change shield position
				break;

			case TYPE_3:

				//Change shield position
				break;

			case TYPE_4:

				//Change shield position
				break;
			}

			Mix_PlayChannel(0, typeSwap, 0);
		}

		// Fire lasers
		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
		{
			if (bluePower > LEVEL_1)
				weaponChargeTimer = SDL_GetTicks();

			if (currentBlue < maxBlueShots && blueShotTimer < SDL_GetTicks() - 100 && fireWeapon == NONE)
			{
				blueShotTimer = SDL_GetTicks();
				/*
				if (currentBlue < 0)
				currentBlue == 0;
				*/
				switch (type)
				{
				case TYPE_1:
					switch (bluePower)
					{
					case LEVEL_1:
						currentBlue += 2;
						App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset - 6, position.y + laserVerticalOffset - 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset - 6, position.y + laserVerticalOffset, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_2:
						currentBlue += 3;
						App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset - 6, position.y + laserVerticalOffset - 8, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset - 6, position.y + laserVerticalOffset + 4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_3:
						currentBlue += 3;
						App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset - 5, position.y + laserVerticalOffset - 12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset - 5, position.y + laserVerticalOffset + 8, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_4:
						currentBlue += 3;
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 14, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset + 8, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_5:
						currentBlue += 4;
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 14, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 7, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 1, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset + 8, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_6:
						currentBlue += 4;
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 20, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 0, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset + 12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_7:
						currentBlue += 4;
						App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 24, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 0, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset + 14, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;
					}

					Mix_PlayChannel(1, type1Shot, 0);
					break;

				case TYPE_2:
					switch (bluePower)
					{
					case LEVEL_1:
						currentBlue += 2;
						App->particles->AddParticle(App->particles->yellowSmallLeft, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_2:
						currentBlue += 3;
						App->particles->AddParticle(App->particles->yellowSmallLeft, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 5, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallLeft, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 1, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_3:
						currentBlue += 4;
						App->particles->AddParticle(App->particles->yellowSmallUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 5, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset + 1, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 0, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_4:
						currentBlue += 5;
						App->particles->AddParticle(App->particles->yellowSmallUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 5, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowBigLeft, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 1, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 0, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_5:
						currentBlue += 5;
						App->particles->AddParticle(App->particles->yellowBigUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 5, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowBigLeft, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset + 1, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowBigDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 0, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_6:
						currentBlue += 6;
						App->particles->AddParticle(App->particles->yellowBigUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 10, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 5, position.y + laserVerticalOffset - 2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowBigLeft, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset + 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowBigDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 0, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_7:
						currentBlue += 6;
						App->particles->AddParticle(App->particles->yellowBigUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 10, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowBigRight, position.x + laserHorizontalOffset - 5, position.y + laserVerticalOffset - 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowBigLeft, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset + 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->yellowBigDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 0, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;
					}

					Mix_PlayChannel(1, type2Shot, 0);
					break;

				case TYPE_3:
					switch (bluePower)
					{
					case LEVEL_1:
						currentBlue += 1;
						App->particles->AddParticle(App->particles->straightGreen, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 1, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_2:
						currentBlue += 2;
						App->particles->AddParticleArray(App->particles->upRightGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 2, -2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downRightGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 2, 2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_3:
						currentBlue += 4;
						App->particles->AddParticleArray(App->particles->upRightGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 2, -2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downRightGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 2, 2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, -2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, 2, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_4:
						currentBlue += 4;
						App->particles->AddParticleArray(App->particles->upRightGreen2, 4, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 4, -4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downRightGreen2, 4, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 4, 4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen2, 4, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -4, -4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen2, 4, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -4, 4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_5:
						currentBlue += 4;
						App->particles->AddParticleArray(App->particles->upRightGreen3, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 4, -4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downRightGreen3, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 4, 4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen3, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -4, -4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen3, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -4, 4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_6:
						currentBlue += 4;
						App->particles->AddParticleArray(App->particles->upRightGreen4, 2, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, 12, -10, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downRightGreen4, 2, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, 10, 12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen4, 2, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, -10, -12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen4, 2, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, -12, 10, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_7:
						currentBlue += 4;
						App->particles->AddParticleArray(App->particles->upRightGreen5, 4, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, 12, -10, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downRightGreen5, 4, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, 10, 12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen5, 4, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, -10, -12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen5, 4, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, -12, 10, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;
					}

					Mix_PlayChannel(1, type3Shot, 0);
					break;

				case TYPE_4:
					switch (bluePower)
					{
					case LEVEL_1:
						currentBlue += 2;
						App->particles->AddParticle(App->particles->arrowUp1, position.x + 5, position.y + 7, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowDown1, position.x + 5, position.y + 9, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_2:
						currentBlue += 3;
						App->particles->AddParticle(App->particles->arrowUp1, position.x + 5, position.y + 7, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowStraight1, position.x + 20, position.y + 8, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowDown1, position.x + 5, position.y + 9, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_3:
						currentBlue += 3;
						App->particles->AddParticle(App->particles->arrowUp2, position.x + 5, position.y + 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowStraight2, position.x + 20, position.y + 8, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowDown2, position.x + 5, position.y + 10, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_4:
						currentBlue += 4;
						App->particles->AddParticle(App->particles->arrowSuperUp2, position.x + 0, position.y + 1, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowUp2, position.x + 12, position.y + 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowDown2, position.x + 12, position.y + 8, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowSuperDown2, position.x + 0, position.y + 12, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_5:
						currentBlue += 4;
						App->particles->AddParticle(App->particles->arrowSuperUp2, position.x + 0, position.y + 1, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowUp3, position.x + 12, position.y + 4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowDown3, position.x + 12, position.y + 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowSuperDown2, position.x + 0, position.y + 14, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_6:
						currentBlue += 5;
						App->particles->AddParticle(App->particles->arrowSuperUp2, position.x + 0, position.y + 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowUp3, position.x + 12, position.y + 4, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowStraight3, position.x + 24, position.y + 7, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowDown3, position.x + 12, position.y + 8, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowSuperDown2, position.x + 0, position.y + 15, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_7:
						currentBlue += 5;
						App->particles->AddParticle(App->particles->arrowSuperUp3, position.x + 0, position.y - 6, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowUp3, position.x + 12, position.y + 0, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowStraight3, position.x + 24, position.y + 3, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowDown3, position.x + 12, position.y + 5, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->arrowSuperDown3, position.x + 0, position.y + 13, PLAYER_1_BLUE_SHOT, COLLIDER_PLAYER_SHOT);
						break;
					}

					Mix_PlayChannel(1, type4Shot, 0);
					break;
				}
			}
		}

		/*Preparation for keyholding*/
		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_REPEAT)
		{
			if (currentOrange <= 0)
			{
				switch (type)
				{
				case TYPE_1:
					switch (orangePower)
					{
					case LEVEL_0:
						break;

					case LEVEL_1:
						currentOrange = 1;
						App->particles->AddParticle(App->particles->missileDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_2:
						currentOrange = 2;
						App->particles->AddParticle(App->particles->missileUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->missileDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_3:
						currentOrange = 2;
						App->particles->AddParticle(App->particles->missileUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->missileDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_4:
						currentOrange = 4;
						App->particles->AddParticle(App->particles->missileSuperUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->missileUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->missileDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->missileSuperDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_5:
						currentOrange = 4;
						App->particles->AddParticle(App->particles->missileSuperUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->missileUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->missileDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->missileSuperDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;
					}

					break;

				case TYPE_2:
					switch (orangePower)
					{
					case LEVEL_0:
						break;

					case LEVEL_1:
						currentOrange = 1;
						App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_2:
						currentOrange = 2;
						App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_3:
						currentOrange = 2;
						App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_4:
						currentOrange = 6;
						App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketLeftDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketLeftUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketDownDiagonal, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketUpDiagonal, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_5:
						currentOrange = 6;
						App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketLeftDown, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketLeftUp, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketDownDiagonal, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->redRocketUpDiagonal, position.x + 5, position.y + laserVerticalOffset, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;
					}

					break;

				case TYPE_3:
					switch (orangePower)
					{
					case LEVEL_0:
						break;

					case LEVEL_1:
						currentOrange = 1;
						App->particles->AddParticle(App->particles->bombRightDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_2:
						currentOrange = 2;
						App->particles->AddParticle(App->particles->bombRightDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bombRightUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_3:
						currentOrange = 2;
						App->particles->AddParticle(App->particles->bombRightDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bombRightUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_4:
						currentOrange = 4;
						App->particles->AddParticle(App->particles->bombRightDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bombRightUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bombLeftDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bombLeftUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_5:
						currentOrange = 4;
						App->particles->AddParticle(App->particles->bombRightDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bombRightUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bombLeftDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->bombLeftUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;
					}

					break;

				case TYPE_4:
					switch (orangePower)
					{
					case LEVEL_0:
						break;

					case LEVEL_1:
						currentOrange = 2;
						App->particles->AddParticle(App->particles->laserUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 20, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_2:
						currentOrange = 4;
						App->particles->AddParticle(App->particles->laserUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 20, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, -2, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, 2, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_3:
						currentOrange = 4;
						App->particles->AddParticle(App->particles->laserUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 20, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, -2, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, 2, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_4:
						currentOrange = 4;
						App->particles->AddParticle(App->particles->laserUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 20, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, -2, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, 2, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;

					case LEVEL_5:
						currentOrange = 4;
						App->particles->AddParticle(App->particles->laserUp, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 20, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticle(App->particles->laserDown, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 4, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->upLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, -2, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						App->particles->AddParticleArray(App->particles->downLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, 2, PLAYER_1_ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
						break;
					}

					break;
				}
			}

			if (yellowPower != LEVEL_0 && currentYellow < 5)
				currentYellow++;

			// Charging weapon sounds
			if (bluePower > LEVEL_1 && weaponChargeTimer < SDL_GetTicks() - 1300 && weaponChargingStage == NOT_CHARGING)
			{
				Mix_PlayChannel(1, typeCharging, 0);
				weaponChargingStage = CHARGING;
			}

			else if (bluePower > LEVEL_1 && weaponChargeTimer < SDL_GetTicks() - 2200 && weaponChargingStage == CHARGING)
			{
				weaponChargingStage = CHARGED;
			}

			else if (bluePower > LEVEL_1 && weaponChargeTimer < SDL_GetTicks() - 4400 && weaponChargingStage == CHARGED)
			{
				Mix_PlayChannel(1, typeCharged, -1);
				weaponChargingStage = CHARGED_LOOP;
			}
		}

		// Weapon shot
		if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_UP && bluePower > LEVEL_1)
		{
			weaponChargingStage = NOT_CHARGING;

			if (weaponChargeTimer < SDL_GetTicks() - 2200)
			{
				switch (type)
				{
				case TYPE_1:
					fireWeapon = TYPE_1;
					weaponLaserInterval = SDL_GetTicks();
					break;

				case TYPE_2:
					fireWeapon = TYPE_2;
					weaponLaserInterval = SDL_GetTicks();
					break;

				case TYPE_3:
					fireWeapon = TYPE_3;
					weaponLaserInterval = SDL_GetTicks();
					break;

				case TYPE_4:
					fireWeapon = TYPE_4;
					weaponLaserInterval = SDL_GetTicks();
					break;
				}

				bluePower--;
				checkBluePowerParticleLimit();
			}

			else if (weaponChargeTimer < SDL_GetTicks() - 1300)
				Mix_HaltChannel(1);
		}

		switch (fireWeapon)
		{
		case NONE:
			break;

		case TYPE_1:
			if (weaponLaserInterval < SDL_GetTicks() && weaponStage == 0)
			{
				App->particles->AddParticle(App->particles->weaponBlueVerticalUp, position.x + laserHorizontalOffset, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueVerticalDown, position.x + laserHorizontalOffset, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 10, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 10, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);


				Mix_PlayChannel(1, type1Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 150 && weaponStage == 1)
			{
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 30, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 30, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 300 && weaponStage == 3)
			{
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 50, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 50, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 225 && weaponStage == 2)
			{
				App->particles->AddParticle(App->particles->weaponBlueVerticalUp, position.x + laserHorizontalOffset, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueVerticalDown, position.x + laserHorizontalOffset, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 10, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 10, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(-1, type1Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 375 && weaponStage == 4)
			{
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 30, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 30, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 525 && weaponStage == 6)
			{
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 50, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 50, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 450 && weaponStage == 5)
			{
				App->particles->AddParticle(App->particles->weaponBlueVerticalUp, position.x + laserHorizontalOffset, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueVerticalDown, position.x + laserHorizontalOffset, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 10, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 10, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(-1, type1Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 600 && weaponStage == 7)
			{
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 30, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 30, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 750 && weaponStage == 8)
			{
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y - 50, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponBlueHorizontal, position.x, position.y + 50, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
				fireWeapon = NONE;
				weaponStage = 0;
			}
			break;

		case TYPE_2:
			if (weaponLaserInterval < SDL_GetTicks() && weaponStage == 0)
			{
				App->particles->AddParticle(App->particles->Weapon2RightUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2RightDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftSuperUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftStraight, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftSuperDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(1, type2Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 120 && weaponStage == 1)
			{
				App->particles->AddParticle(App->particles->Weapon2RightUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2RightDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftSuperUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftStraight, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftSuperDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(-1, type2Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 240 && weaponStage == 2)
			{
				App->particles->AddParticle(App->particles->Weapon2RightUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2RightDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftSuperUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftStraight, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->Weapon2LeftSuperDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 10, PLAYER_1_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(-1, type2Weapon, 0);
				weaponStage = 0;
				fireWeapon = NONE;
			}
			break;

		case TYPE_3:
			if (weaponLaserInterval < SDL_GetTicks() && weaponStage == 0)
			{


				Mix_PlayChannel(1, type3Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 300 && weaponStage == 1)
			{

				weaponStage++;
				fireWeapon = NONE;
				weaponStage = 0;
			}
			break;

		case TYPE_4:
			if (weaponLaserInterval < SDL_GetTicks() && weaponStage == 0)
			{
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(1, type4Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 30 && weaponStage == 1)
			{
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 40, position.y - 10, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 40, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 40, position.y + 10, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 60 && weaponStage == 2)
			{
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 80, position.y - 20, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 80, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 80, position.y + 20, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(1, type4Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 90 && weaponStage == 3)
			{
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 120, position.y - 30, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 120, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 120, position.y + 30, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 120 && weaponStage == 4)
			{
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 160, position.y - 40, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 160, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 160, position.y + 40, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(1, type4Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 150 && weaponStage == 5)
			{
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 200, position.y - 50, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 200, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 200, position.y + 50, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 180 && weaponStage == 6)
			{
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 240, position.y - 60, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 240, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 240, position.y + 60, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				Mix_PlayChannel(1, type4Weapon, 0);
				weaponStage++;
			}

			else if (weaponLaserInterval < SDL_GetTicks() - 210 && weaponStage == 7)
			{
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 280, position.y - 70, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 280, position.y, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);
				App->particles->AddParticle(App->particles->weaponYellowBlast, position.x + laserHorizontalOffset + 280, position.y + 70, PLAYER_1_CONSTANT_WEAPON_SHOT, COLLIDER_PLAYER_SHOT);

				if (weaponLoop < 1)
				{
					weaponLaserInterval = SDL_GetTicks() + 200;		// + delay
					weaponStage = 0;
					weaponLoop++;
				}

				else
				{
					weaponStage = 0;
					weaponLoop = 0;
					fireWeapon = NONE;
				}
			}

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


			if (godMode == true )
			{
				playerHitbox->to_delete = true;
				playerHitbox = App->collision->AddCollider({ App->render->camera.x / SCREEN_SIZE + (int)position.x, App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight }, COLLIDER_PLAYER_INV, this);
			}
			else if (godMode == false)
			{
				godMode = false;
				playerHitbox->to_delete = true;
				playerHitbox = App->collision->AddCollider({ App->render->camera.x / SCREEN_SIZE + (int)position.x, App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight }, COLLIDER_PLAYER, this);
			}

		}

		if (invStartTime !=0 && SDL_GetTicks() - invStartTime > 3999 && SDL_GetTicks() - invStartTime < 4020 && godMode== false)
		{
			playerHitbox->to_delete = true;
			playerHitbox = App->collision->AddCollider({ App->render->camera.x / SCREEN_SIZE + (int)position.x, App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight }, COLLIDER_PLAYER, this);
			isInvincible = false;
		}

		/*if ( isInvincible==true && SDL_GetTicks() - invStartTime == 4000)
		{
			playerHitbox = App->collision->AddCollider({ App->render->camera.x / SCREEN_SIZE + (int)position.x, App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight }, COLLIDER_PLAYER, this);
			isInvincible = false;
			playerHitbox->to_delete = true;
		}
		else if (isInvincible == true && SDL_GetTicks() - invStartTime < 4000)
		{
			playerHitbox = App->collision->AddCollider({ App->render->camera.x / SCREEN_SIZE + (int)position.x, App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight }, COLLIDER_PLAYER_INV, this);
			isInvincible = false;
			playerHitbox->to_delete = true;
		}*/
		// Update collider position to player position
			playerHitbox->SetPos(App->render->camera.x / SCREEN_SIZE + position.x, App->render->camera.y / SCREEN_SIZE + position.y);

		

		if (destroyed == true)
		{
			SDL_Rect crashrect = crashAnimation->GetCurrentFrame();
			App->render->Blit(graphics, position.x, position.y, &crashrect, 1.0f, false);

			// VALUES THAT NEED TO RESTART WHEN PLAYER DIES, SHOULD HAPPEN ONLY ONCE
			/*
			if (bluePower > LEVEL_1)
			bluePower--;

			if (orangePower > LEVEL_0)
			orangePower--;

			if (yellowPower > LEVEL_0)
			yellowPower--;

			if (greenPower > LEVEL_0)
			greenPower--;

			checkBluePowerParticleLimit();

			fireWeapon = NONE;				// Integer that marks which weapon is being fired at the moment (with an enum)
			weaponLaserInterval = 0;	// Marks time between fired lasers in a single weapon shot
			weaponStage = 0;			// Marks stage of currently firing weapon
			weaponLoop = 0;				// Marks the number of loops of the weapon, if any

			blueShotTimer = 0;
			weaponChargeTimer = 0;
			weaponChargingStage = NOT_CHARGING;

			movVertical = 0;	// Counter for the vertical movement of the ship
			*/
		}

		// Draw everything --------------------------------------
		if (destroyed == false)
		{
			SDL_Rect propellerRect = propellerAnimation->GetCurrentFrame();
			App->render->Blit(graphics, position.x - propellerWidth, position.y, &propellerRect, 1.0f, false);

			if (weaponChargingStage == CHARGED || weaponChargingStage == CHARGED_LOOP)
			{
				shipRect = shipAnimation->GetCurrentFrame();
				App->render->Blit(graphics, position.x - 2, position.y - 3, &shipRect, 1.0f, false);
			}
				
			else
				App->render->Blit(graphics, position.x, position.y, &shipRect, 1.0f, false);
		}

		//When the explosion animation ends, execute this code (RESPAWN)
		if (crash.Finished() == true && destroyed == true)
		{
			//Reset player pos
			position.x = 0;							// Starting point of the ship (using p2Point)
			position.y = (int)(SCREEN_HEIGHT / 2 - 10);
			crash.Reset();
			crash.ResetLoops();
			/*crashAnimation->;*/

			if (godMode == false)
			{
				playerHitbox = App->collision->AddCollider({ App->render->camera.x / SCREEN_SIZE + (int)position.x, App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight }, COLLIDER_PLAYER_INV, this);
				//playerHitbox->SetPos(App->render->camera.x / SCREEN_SIZE + position.x, App->render->camera.y / SCREEN_SIZE + position.y);
				playerHitbox->to_delete = false;
			}

			if (lives < 1)
			{
				App->UI->p1Dead = true;
				if (playerHitbox != nullptr)
				{
					playerHitbox->to_delete = true;
				}
				this->Disable();
				if (App->UI->p2Dead == true && App->UI->CurrentStage == App->UI->Stage1)
				{
					App->fade->FadeToBlack(App->stage1, App->scene_HiScore);    // HARDCODED: Needs "current stage" functionality
				}
				else if (App->UI->p2Dead == true && App->UI->CurrentStage == App->UI->Stage2)
				{
					App->fade->FadeToBlack(App->stage2, App->scene_HiScore);    // HARDCODED: Needs "current stage" functionality
				}
			}

			destroyed = false;
		}

	return UPDATE_CONTINUE;
}

bool ModulePlayer1::CleanUp()
{
	LOG("Unloading player 1");
	App->textures->Unload(graphics);
	graphics = nullptr;

	App->player1->Disable();

	App->mixer->UnloadFx(type1Shot);
	App->mixer->UnloadFx(type2Shot);
	App->mixer->UnloadFx(type3Shot);
	App->mixer->UnloadFx(type4Shot);

	App->mixer->UnloadFx(type1Weapon);
	App->mixer->UnloadFx(type2Weapon);
	App->mixer->UnloadFx(type3Weapon);
	App->mixer->UnloadFx(type4Weapon);

	App->mixer->UnloadFx(typeCharging);
	App->mixer->UnloadFx(typeCharged);
	App->mixer->UnloadFx(typeSwap);
	App->mixer->UnloadFx(powerUp);
	App->mixer->UnloadFx(playerDeathExplosion);

	//Reset player pos
	position.x = 0;							// Starting point of the ship (using p2Point)
	position.y = (int)(SCREEN_HEIGHT / 2 - 10);
	shipAnimation = nullptr;
	propellerAnimation = nullptr;
	crashAnimation = nullptr;
	crash.Reset();

	return true;
}

void ModulePlayer1::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type != COLLIDER_POWERUP)
	{
		Mix_PlayChannel(3, playerDeathExplosion, 0);
		blueShotTimer = SDL_GetTicks();
		invStartTime = SDL_GetTicks();
		isInvincible = true;
		crashAnimation = &crash;
		destroyed = true;
		playerHitbox->to_delete = true;
		
		lives -= 1;
	}
}

void ModulePlayer1::checkBluePowerParticleLimit()
{
	switch (type)
	{
	case TYPE_1:
		switch (bluePower)
		{
		case LEVEL_1:
			maxBlueShots = 6;
			break;
		case LEVEL_2:
			maxBlueShots = 9;
			break;
		case LEVEL_3:
			maxBlueShots = 9;
			break;
		case LEVEL_4:
			maxBlueShots = 9;
			break;
		case LEVEL_5:
			maxBlueShots = 12;
			break;
		case LEVEL_6:
			maxBlueShots = 12;
			break;
		case LEVEL_7:
			maxBlueShots = 12;
			break;
		}
		break;

	case TYPE_2:
		switch (bluePower)
		{
		case LEVEL_1:
			maxBlueShots = 6;
			break;
		case LEVEL_2:
			maxBlueShots = 9;
			break;
		case LEVEL_3:
			maxBlueShots = 12;
			break;
		case LEVEL_4:
			maxBlueShots = 12;
			break;
		case LEVEL_5:
			maxBlueShots = 15;
			break;
		case LEVEL_6:
			maxBlueShots = 15;
			break;
		case LEVEL_7:
			maxBlueShots = 18;
			break;
		}
		break;

	case TYPE_3:
		switch (bluePower)
		{
		case LEVEL_1:
			maxBlueShots = 3;
			break;
		case LEVEL_2:
			maxBlueShots = 6;
			break;
		case LEVEL_3:
			maxBlueShots = 12;
			break;
		case LEVEL_4:
			maxBlueShots = 12;
			break;
		case LEVEL_5:
			maxBlueShots = 12;
			break;
		case LEVEL_6:
			maxBlueShots = 12;
			break;
		case LEVEL_7:
			maxBlueShots = 12;
			break;
		}
		break;

	case TYPE_4:
		switch (bluePower)
		{
		case LEVEL_1:
			maxBlueShots = 6;
			break;
		case LEVEL_2:
			maxBlueShots = 9;
			break;
		case LEVEL_3:
			maxBlueShots = 9;
			break;
		case LEVEL_4:
			maxBlueShots = 12;
			break;
		case LEVEL_5:
			maxBlueShots = 12;
			break;
		case LEVEL_6:
			maxBlueShots = 15;
			break;
		case LEVEL_7:
			maxBlueShots = 15;
			break;
		}
		break;
	}
}