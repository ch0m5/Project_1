#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"

ModulePlayer1::ModulePlayer1()	//@CarlesHoms
{
	position.x = 0;							// Starting point of the ship (using p2Point)
	position.y = SCREEN_HEIGHT / 2 - 10;

	movVertical = 0;
	maxVertical = 14;

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

	// All ship and booster animations
	superUpwards.PushBack({ 94, 66, 27, 17 });
	superUpwards.speed = 1.2f;

	superUpwardsBooster.PushBack({ 42, 63, 12, 17 });
	superUpwardsBooster.PushBack({ 0, 0, 12, 17 });
	superUpwardsBooster.PushBack({ 59, 63, 12, 17 });
	superUpwardsBooster.PushBack({ 0, 0, 12, 17 });
	superUpwardsBooster.PushBack({ 73, 63, 12, 17 });
	superUpwardsBooster.PushBack({ 0, 0, 12, 17 });
	superUpwardsBooster.PushBack({ 59, 63, 12, 17 });
	superUpwardsBooster.PushBack({ 0, 0, 12, 17 });
	superUpwardsBooster.speed = 1.2f;

	upwards.PushBack({ 94, 87, 27, 17 });
	upwards.speed = 1.2f;

	upwardsBooster.PushBack({ 43, 86, 12, 17 });
	upwardsBooster.PushBack({ 0, 0, 12, 17 });
	upwardsBooster.PushBack({ 60, 86, 12, 17 });
	upwardsBooster.PushBack({ 0, 0, 12, 17 });
	upwardsBooster.PushBack({ 74, 86, 12, 17 });
	upwardsBooster.PushBack({ 0, 0, 12, 17 });
	upwardsBooster.PushBack({ 60, 86, 12, 17 });
	upwardsBooster.PushBack({ 0, 0, 12, 17 });
	upwardsBooster.speed = 1.2f;

	idle.PushBack({ 94, 108, 27, 17 });
	idle.speed = 1.2f;

	idleBooster.PushBack({ 43, 109, 12, 17 });
	idleBooster.PushBack({ 0, 0, 12, 17 });
	idleBooster.PushBack({ 62, 109, 12, 17 });
	idleBooster.PushBack({ 0, 0, 12, 17 });
	idleBooster.PushBack({ 74, 109, 12, 17 });
	idleBooster.PushBack({ 0, 0, 12, 17 });
	idleBooster.PushBack({ 62, 109, 12, 17 });
	idleBooster.PushBack({ 0, 0, 12, 17 });
	idleBooster.speed = 1.2f;

	downwards.PushBack({ 94, 131, 27, 17 });
	downwards.speed = 1.2f;

	downwardsBooster.PushBack({ 43, 133, 12, 17 });
	downwardsBooster.PushBack({ 0, 0, 12, 17 });
	downwardsBooster.PushBack({ 60, 133, 12, 17 });
	downwardsBooster.PushBack({ 0, 0, 12, 17 });
	downwardsBooster.PushBack({ 74, 133, 12, 17 });
	downwardsBooster.PushBack({ 0, 0, 12, 17 });
	downwardsBooster.PushBack({ 60, 133, 12, 17 });
	downwardsBooster.PushBack({ 0, 0, 12, 17 });
	downwardsBooster.speed = 1.2f;

	superDownwards.PushBack({ 94, 153, 27, 17 });
	superDownwards.speed = 1.2f;

	superDownwardsBooster.PushBack({ 43, 153, 12, 17 });
	superDownwardsBooster.PushBack({ 0, 0, 12, 17 });
	superDownwardsBooster.PushBack({ 60, 153, 12, 17 });
	superDownwardsBooster.PushBack({ 0, 0, 12, 17 });
	superDownwardsBooster.PushBack({ 74, 153, 12, 17 });
	superDownwardsBooster.PushBack({ 0, 0, 12, 17 });
	superDownwardsBooster.PushBack({ 60, 153, 12, 17 });
	superDownwardsBooster.PushBack({ 0, 0, 12, 17 });
	superDownwardsBooster.speed = 1.2f;
}

ModulePlayer1::~ModulePlayer1()
{}

// Load assets
bool ModulePlayer1::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Sprites/Players_Ships/ships.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer1::Update()	// Ship and booster animation used based on movVertical value, which changes on pressing UP and DOWN keys or neither
{
	Animation* current_animation = &idle;
	Animation* propeller_animation = &idleBooster;
	
	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
	{
		position.y += speed;

		if (movVertical > -maxVertical)
		{
			--movVertical;		// Decrease vertical counter.
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_UP] == 1)
	{
		position.y -= speed;

		if (movVertical < maxVertical)
		{
			++movVertical;		// Increase vertical counter.
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_DOWN] == 0 && App->input->keyboard[SDL_SCANCODE_UP] == 0)
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

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1)
	{
		position.x -= speed;
	}

	else if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1)
	{
		position.x += speed;
	}
	
	// Depending on the vertical counter, we decide the animation
	if (movVertical >= maxVertical)
	{
		current_animation = &superUpwards;
		propeller_animation = &superUpwardsBooster;
	}

	else if (movVertical > 7 && movVertical < maxVertical)
	{
		current_animation = &upwards;
		propeller_animation = &upwardsBooster;
	}

	else if (movVertical <= 7 && movVertical >= -7)
	{
		current_animation = &idle;
		propeller_animation = &idleBooster;
	}

	else if (movVertical < -7 && movVertical > -maxVertical)
	{
		current_animation = &downwards;
		propeller_animation = &downwardsBooster;
	}

	else if (movVertical <= -maxVertical)
	{
		current_animation = &superDownwards;
		propeller_animation = &superDownwardsBooster;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	SDL_Rect p = propeller_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x-12, position.y - r.h, &p);
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}

bool ModulePlayer1::CleanUp()
{
	LOG("Unloading player 1");
	App->textures->Unload(graphics);

	App->player1->Disable();

	return true;
}