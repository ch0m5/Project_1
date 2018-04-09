#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"

ModulePlayer2::ModulePlayer2()	//@CarlesHoms
{
	shipAnimation = nullptr;
	shipWidth = 27;
	shipHeight = 17;

	propellerAnimation = nullptr;
	propellerWidth = 12;
	propellerHeight = 17;

	position.x = 0;							// Starting point of the ship (using p2Point)
	position.y = SCREEN_HEIGHT / 2 + 10;

	movVertical = 0;	// Counter for the vertical movement of the ship
	maxVertical = 14;	// Limit of the counter

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
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Players_Ships/ships.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer2::Update()	// Moves the ship and changes it's printed sprite depending on a counter.
{
	// How it works: A counter (movVertical) changes values by pressing UP, DOWN or neither and then one of the SDL_Rects inside
	// the frames array of ship animation (shipVerticalMovement) is blited depending on the value of the counter.

	shipAnimation = &shipVerticalMovement;
	propellerAnimation = &idleBooster;
	SDL_Rect shipRect = shipAnimation->frames[SHIP_IDLE];

	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y < SCREEN_HEIGHT)
		{
			position.y += speed;
		}

		if (movVertical > -maxVertical)
		{
			--movVertical;		// Decrease vertical counter.
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y > shipHeight)
		{
			position.y -= speed;
		}

		if (movVertical < maxVertical)
		{
			++movVertical;		// Increase vertical counter.
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
		App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
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

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && position.x > 0)
	{
		position.x -= speed;
	}

	else if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && position.x < SCREEN_WIDTH - shipWidth)
	{
		position.x += speed;
	}

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

	// Draw everything --------------------------------------
	SDL_Rect propellerRect = propellerAnimation->GetCurrentFrame();

	App->render->Blit(graphics, position.x - 12, position.y - shipRect.h, &propellerRect);
	App->render->Blit(graphics, position.x, position.y - shipRect.h, &shipRect);

	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player 2");
	App->textures->Unload(graphics);

	App->player2->Disable();

	return true;
}