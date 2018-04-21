#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePlayer1.h"
#include "ModuleParticles.h"
#include "ModuleMixer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleHiScore.h"
#include "ModuleStage1.h"
#include "ModuleStage2.h"
#include "ModuleFont.h"

ModulePlayer1::ModulePlayer1()	// @CarlesHoms @Andres
{
	graphics = nullptr;

	font_score = -1;
	score = 0;

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

	movVertical = 0;	// Counter for the vertical movement of the ship
	maxVertical = 14;	// Limit of the counter

	//Music 
	type1Shot = nullptr;		// All use the same channel (3)
	type2Shot = nullptr;
	type3Shot = nullptr;
	type4Shot = nullptr;
	typeSwap = nullptr;
	powerUp = nullptr;
	playerDeathExplosion = nullptr;

	//Collider
	playerHitbox;

	//Lasers
	laserHorizontalOffset = 18;	// Horizontal Offset for bullets
	laserVerticalOffset = 12;	// Vertical Offset for bullets
	
	//Types and levels
	type = TYPE_1;			// Flag/counter for type equipped
	bluePower = LEVEL_1;	// Flag/counter for blue power level
	orangePower = LEVEL_0;	// Flag/counter for orange power level
	yellowPower = LEVEL_0;	// Flag/counter for yellow power level
	greenPower = LEVEL_0;	// Flag/counter for green power level
								//Counter to limitate how many lasers, boms, etc can the player have on screen, based on needed particles to be destroyed to make more shots.
	maxBlue = 4;
	maxOrange = 0;
	maxYellow = 0;
	//int blueShotTimer;	// After the last shot taken, if enough time passes without no shots, the "currentBlue" counter restarts.
	//int timeBetweenShotsTimer;	// time between each shot, could be a get ticks

	currentBlue = 0;	// Every shot increases the counter by 2, player will not shot if it gets higher than 4. Each collide substracts 1.
	currentOrange = 0;	// Every time it fires increases the counter by x (changes on level), player will not shot if it reaches MAX.  Each collide substracts 1.
	currentYellow = 0;	// When reaching level yellow one, the max becomes 3 and the counter increases by 1 for each misile fired. Each collide substracts 1.

	// Starting point of the ship (using p2Point)
	position.x = 0;
	position.y = SCREEN_HEIGHT / 2 - 10;

	//Debug Purpose Variables
	godMode = false;

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
	
	// UI must change
	score = 0;
	
	// Place player hitbox
	playerHitbox = App->collision->AddCollider({ (int)position.x, (int)position.y, shipWidth, shipHeight}, COLLIDER_PLAYER, this);
	
	return ret;
}

// Update: draw background
update_status ModulePlayer1::Update()	// Moves the ship and changes it's printed sprite depending on a counter.
{
	// How it works: A counter (movVertical) changes values by pressing UP, DOWN or neither and then one of the SDL_Rects inside
	// the frames array of ship animation (shipVerticalMovement) is blited depending on the value of the counter.

	shipAnimation = &shipVerticalMovement;
	propellerAnimation = &idleBooster;
	shipRect = &shipAnimation->frames[SHIP_IDLE];

	// Bliting Text
	//App->fonts->BlitText(50, 10, font_score, "we are going to do the best game ric has ever seen dude!!");

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

	if (App->input->debugMode == true)
	{
		if (App->input->keyboard[SDL_SCANCODE_6] == KEY_DOWN && bluePower < LEVEL_7)	// Level up blue
		{
			bluePower++;
			Mix_PlayChannel(3, powerUp, 0);
		}

		if (App->input->keyboard[SDL_SCANCODE_7] == KEY_DOWN && orangePower < LEVEL_5)	// Level up orange
		{
			orangePower++;	// Red rockets have 6 particles, IT'S A TRAP
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

		switch (orangePower)
		{
		case LEVEL_0:
			maxOrange = 0;
			break;

		case LEVEL_1:
			maxOrange = 1;
			break;

		case LEVEL_2:
			maxOrange = 2;
			break;

		case LEVEL_4:
			maxOrange = 4;
			break;

		default:
			break;
		}

		if (yellowPower > 0)
		{
			maxYellow = 5;
		}

		else { maxYellow = 0; }
	}

	//Change weapon
	if  (App->input->keyboard[SDL_SCANCODE_O] == KEY_DOWN)	// Swap type
	{
		if (type >= TYPE_4)
		{
			type = TYPE_1;
		}

		else { type++; }

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
	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN)
	{
		if (currentBlue <= maxBlue)
		{
			// Restart shot timer here

			switch (type)
			{
			case TYPE_1:
				currentBlue += 2;

				switch (bluePower)
				{
				case LEVEL_1:
					App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_2:
					App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 7, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 3, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_3:
					App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 0, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->smallBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_4:
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 0, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_5:
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 0, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_6:
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 0, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->mediumBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_7:
					App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 0, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bigBlue, position.x + laserHorizontalOffset, position.y + laserVerticalOffset + 5, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;
				}

				Mix_PlayChannel(3, type1Shot, 0);
				break;

			case TYPE_2:
				currentBlue += 2;

				switch (bluePower)
				{
				case LEVEL_1:
					App->particles->AddParticle(App->particles->yellowSmallLeft, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;
					
				case LEVEL_2:
					App->particles->AddParticle(App->particles->yellowSmallLeft, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallLeft, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_3:
					App->particles->AddParticle(App->particles->yellowSmallUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;
					
				case LEVEL_4:
					App->particles->AddParticle(App->particles->yellowSmallUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowBigLeft, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_5:
					App->particles->AddParticle(App->particles->yellowBigUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowBigLeft, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowBigDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_6:
					App->particles->AddParticle(App->particles->yellowSmallUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowBigLeft, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_7:
					App->particles->AddParticle(App->particles->yellowSmallUp, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowBigRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowBigLeft, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserHorizontalOffset - 10, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->yellowSmallDown, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;
				}

				Mix_PlayChannel(3, type2Shot, 0);
				break;

			case TYPE_3:
				switch (bluePower)
				{
				case LEVEL_1:
					currentBlue += 2;
					App->particles->AddParticle(App->particles->straightGreen, position.x + laserHorizontalOffset, position.y + laserVerticalOffset - 1, GREEN_SINGLE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_2:
					App->particles->AddParticleArray(App->particles->upRightGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 2, -2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downRightGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 2, 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_3:
					App->particles->AddParticleArray(App->particles->upRightGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 2, -2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downRightGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 2, 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->upLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, -2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downLeftGreen1, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -2, 2, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_4:
					App->particles->AddParticleArray(App->particles->upRightGreen2, 4, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 4, -4, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downRightGreen2, 4, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 4, 4, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->upLeftGreen2, 4, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -4, -4, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downLeftGreen2, 4, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -4, 4, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_5:
					App->particles->AddParticleArray(App->particles->upRightGreen3, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 4, -4, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downRightGreen3, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, 4, 4, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->upLeftGreen3, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -4, -4, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downLeftGreen3, 8, position.x + laserHorizontalOffset - 4, position.y + laserVerticalOffset - 4, -4, 4, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_6:
					App->particles->AddParticleArray(App->particles->upRightGreen4, 2, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, 12, -10, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downRightGreen4, 2, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, 10, 12, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->upLeftGreen4, 2, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, -10, -12, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downLeftGreen4, 2, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, -12, 10, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_7:
					App->particles->AddParticleArray(App->particles->upRightGreen5, 4, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, 12, -10, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downRightGreen5, 4, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, 10, 12, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->upLeftGreen5, 4, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, -10, -12, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticleArray(App->particles->downLeftGreen5, 4, position.x + laserHorizontalOffset - 14, position.y + laserVerticalOffset - 10, -12, 10, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;
				}

				Mix_PlayChannel(3, type3Shot, 0);
				break;

			case TYPE_4:
				currentBlue += 2;

				switch (bluePower)
				{
				case LEVEL_1:
					App->particles->AddParticle(App->particles->arrowUp1, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowDown1, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_2:
					App->particles->AddParticle(App->particles->arrowUp1, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowStraight1, position.x + 26, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowDown1, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_3:
					App->particles->AddParticle(App->particles->arrowUp2, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowStraight2, position.x + 26, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowDown2, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_4:
					App->particles->AddParticle(App->particles->arrowSuperUp2, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowUp2, position.x + 26, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowDown2, position.x + 26, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowSuperDown2, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_5:
					App->particles->AddParticle(App->particles->arrowSuperUp2, position.x + 26, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowUp3, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowDown3, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowSuperDown2, position.x + 26, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_6:
					App->particles->AddParticle(App->particles->arrowSuperUp2, position.x, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowUp3, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowStraight3, position.x + 26, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowDown3, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowSuperDown2, position.x, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_7:
					App->particles->AddParticle(App->particles->arrowSuperUp3, position.x, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowUp3, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowStraight3, position.x + 26, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowDown3, position.x + 13, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->arrowSuperDown3, position.x, position.y + 8, BLUE_SHOT, COLLIDER_PLAYER_SHOT);
					break;
				}

				Mix_PlayChannel(3, type4Shot, 0);
				break;
			}
		}
	}

	/*Preparation for keyholding*/
	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_REPEAT)
	{
		if (currentOrange == 0)
		{
			currentOrange = maxOrange;

			switch (type)
			{
			case TYPE_1:
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

				break;

			case TYPE_2:
				switch (orangePower)
				{
				case LEVEL_0:
					break;

				case LEVEL_1:
					App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_2:
					App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_3:
					App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_4:
					currentOrange = maxOrange + 2;
					App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketLeftDown, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketLeftUp, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketDownDiagonal, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketUpDiagonal, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_5:
					currentOrange = maxOrange + 2;
					App->particles->AddParticle(App->particles->redRocketDown, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketUp, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketLeftDown, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketLeftUp, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketDownDiagonal, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->redRocketUpDiagonal, position.x + 5, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;
				}

				break;

			case TYPE_3:
				switch (orangePower)
				{
				case LEVEL_0:
					break;

				case LEVEL_1:
					App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_2:
					App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bombRightUp, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_3:
					App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bombRightUp, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_4:
					App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bombRightUp, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bombLeftDown, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bombLeftUp, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;

				case LEVEL_5:
					App->particles->AddParticle(App->particles->bombRightDown, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bombRightUp, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bombLeftDown, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					App->particles->AddParticle(App->particles->bombLeftUp, position.x + 7, position.y + laserVerticalOffset, ORANGE_SHOT, COLLIDER_PLAYER_SHOT);
					break;
				}

				break;

			case TYPE_4:
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

				break;
			}
		}

		if (currentYellow < maxYellow)
		{
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

			currentYellow++;
		}
	}
	
	//GodMode Function
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN && App->input->debugMode==true)
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
				playerHitbox = App->collision->AddCollider({ App->render->camera.x /SCREEN_SIZE + (int)position.x, App->render->camera.y / SCREEN_SIZE + (int)position.y, shipWidth, shipHeight}, COLLIDER_PLAYER, this);
			}
		
	}

	// Update collider position to player position
	if (godMode == false)
	{
		playerHitbox->SetPos(App->render->camera.x /SCREEN_SIZE + position.x, App->render->camera.y / SCREEN_SIZE + position.y);
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

bool ModulePlayer1::CleanUp()
{
	LOG("Unloading player 1");
	App->textures->Unload(graphics);

	App->player1->Disable();

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

void ModulePlayer1::OnCollision(Collider* c1, Collider* c2)
{
	Mix_PlayChannel(3, playerDeathExplosion, 0);

	if ((c1->type == COLLIDER_WALL ||
		c2->type == COLLIDER_WALL ||
		c1->type == COLLIDER_ENEMY_SHOT ||  //Cambio @andres
		c2->type == COLLIDER_ENEMY_SHOT ||  //Cambio @andres
		c1->type == COLLIDER_ENEMY ||		//Cambio @andres
		c2->type == COLLIDER_ENEMY))		//Cambio @andres
	{
		crashAnimation = &crash;
		destroyed = true;
		playerHitbox->to_delete = true;
		App->fade->FadeToBlack(App->stage1, App->scene_HiScore);	// HARDCODED: Needs "current stage" functionality
	}
	/*if ((c1->type == COLLIDER_POWERUP ||c2->type == COLLIDER_POWERUP ))
	{
		bluePower++;
	}*/
}