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

ModulePlayer1::ModulePlayer1()	//@CarlesHoms
{
	shipAnimation = nullptr;
	shipWidth = 27;
	shipHeight = 17;

	propellerAnimation = nullptr;
	propellerWidth = 12;
	propellerHeight = 17;

	position.x = 0;							// Starting point of the ship (using p2Point)
	position.y = SCREEN_HEIGHT / 2 - 10;

	movVertical = 0;	// Counter for the vertical movement of the ship
	maxVertical = 14;	// Limit of the counter
							
	laserFrontOffset = 20;	// Offset for front bullets
	laserBackOffset = 18;	// Offset for back bullets		// Distance from ship position to bullet creation
	laserVerticalOffset = 11;	// Offset for all bullets

	type = TYPE_1;		//laser type

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
}

ModulePlayer1::~ModulePlayer1()
{}

// Load assets
bool ModulePlayer1::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Players_Ships/ships.png"); // arcade version

    //Music
	shot = App->mixer->LoadFX("Music/Laser_Shot_Type-1_(Main_Ships).wav");
	Mix_VolumeChunk(shot, FXVol);
	
	// Place player hitbox
	playerHitbox = App->collision->AddCollider({ position.x, position.y, shipWidth, shipHeight }, COLLIDER_PLAYER, this);
	
	return ret;
}

// Update: draw background
update_status ModulePlayer1::Update()	// Moves the ship and changes it's printed sprite depending on a counter.
{
	// How it works: A counter (movVertical) changes values by pressing UP, DOWN or neither and then one of the SDL_Rects inside
	// the frames array of ship animation (shipVerticalMovement) is blited depending on the value of the counter.

	shipAnimation = &shipVerticalMovement;
	propellerAnimation = &idleBooster;
	SDL_Rect shipRect = shipAnimation->frames[SHIP_IDLE];
	
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

	else if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y < App->render->camera.y + App->render->camera.w)
		{
			position.y += speed;
		}

		if (movVertical > -maxVertical)
		{
			--movVertical;		// Decrease vertical counter.
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y > App->render->camera.y)
		{
			position.y -= speed;
		}

		if (movVertical < maxVertical)
		{
			++movVertical;		// Increase vertical counter.
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT /*&& position.x < App->render->camera.x*/)
	{
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && position.x > App->render->camera.x - App->render->camera.w)
	{
		position.x += speed;
	}
	/*
	if (position.x >= App->render->camera.x)
	{
		position.x += speed;
	}
	*/
	// Depending on the vertical counter, we decide the animation
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

	else if (movVertical < -(maxVertical/2) && movVertical > -maxVertical)
	{
		shipRect = shipAnimation->frames[SHIP_DOWN];
		propellerAnimation = &downwardsBooster;
	}

	else if (movVertical <= -maxVertical)
	{
		shipRect = shipAnimation->frames[SHIP_FULL_DOWN];
		propellerAnimation = &superDownwardsBooster;
	}

	//Change weapon @Andres
	if  (App->input->keyboard[SDL_SCANCODE_O] == KEY_DOWN)
	{
		if (type >= TYPE_4)
		{
			type = TYPE_1;
		}
		else
			type++;
	}

	// Fire lasers @Andres
	if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN && type == TYPE_1)
	{
		App->particles->AddParticle(App->particles->smallBlue, position.x + laserFrontOffset, position.y + laserVerticalOffset -5, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->smallBlue, position.x + laserFrontOffset, position.y + laserVerticalOffset, COLLIDER_PLAYER_SHOT);

		Mix_PlayChannel(3, shot, 0);
	}

	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN &&  type == TYPE_2)
	{
		App->particles->AddParticle(App->particles->yellowSmallRight, position.x + laserFrontOffset, position.y + laserVerticalOffset, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->yellowSmallLeft, position.x + laserBackOffset, position.y + laserVerticalOffset, COLLIDER_PLAYER_SHOT);

		Mix_PlayChannel(3, shot, 0);
	}
	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN &&  type == TYPE_3)
	{
		App->particles->AddParticle(App->particles->straightGreen, position.x + laserFrontOffset, position.y + laserVerticalOffset - 1, COLLIDER_PLAYER_SHOT);

		Mix_PlayChannel(3, shot, 0);
	}
	else if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN &&  type == TYPE_4)
	{
		App->particles->AddParticle(App->particles->arrow1, position.x + 14, position.y + 5, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->arrow2, position.x + 14, position.y + 5, COLLIDER_PLAYER_SHOT);

		Mix_PlayChannel(3, shot, 0);
	}

	//GodMode Function
	if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN)
	{
		if (App->input->keyboard[SDL_SCANCODE_F2] != KEY_REPEAT)
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
			playerHitbox = App->collision->AddCollider({ position.x, position.y, shipWidth, shipHeight }, COLLIDER_PLAYER, this);
		}
	}

	// Update collider position to player position
	if (godMode == false)
	{
		playerHitbox->SetPos(position.x, position.y);
	}

	// Draw everything --------------------------------------
	SDL_Rect propellerRect = propellerAnimation->GetCurrentFrame();

	App->render->Blit(graphics, position.x-propellerWidth, position.y, &propellerRect);
	App->render->Blit(graphics, position.x, position.y, &shipRect);

	return UPDATE_CONTINUE;
}

bool ModulePlayer1::CleanUp()
{
	LOG("Unloading player 1");
	App->textures->Unload(graphics);

	App->player1->Disable();

	//Reset player pos
	position.x = 0;							// Starting point of the ship (using p2Point)
	position.y = SCREEN_HEIGHT / 2 - 10;

	return true;
}

void ModulePlayer1::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == COLLIDER_WALL || c2->type == COLLIDER_WALL)
	{
		App->player1->Disable();
		App->fade->FadeToBlack(App->stage1, App->scene_HiScore);
	}
}