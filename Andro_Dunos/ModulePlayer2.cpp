#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"

ModulePlayer2::ModulePlayer2()	//@CarlesHoms
{
	position.x = 0;							// Starting point of the ship (using p2Point)
	position.y = SCREEN_HEIGHT / 2 + 10;

	movVertical = 0;
	maxVertical = 14;

	/*
	Sprites positioning

	154, 66; superup
	154, 87; up
	154, 108; idle
	154, 131; down
	154, 153; superdown
	27, 17; size

	42, 62; superup first flame
	60, 62; superup second flame
	73, 62; superup third flame

	42, 91; up first flame
	60, 91; up second flame
	73, 91; up third flame

	42, 108; idle first flame
	60, 108; idle second flame
	73, 108; idle third flame

	42, 134; down first flame
	60, 134; down second flame
	73, 134; down third flame

	42, 155; superdown first flame
	60, 155; superdown second flame
	73, 155; superdown third flame

	12, 17; size
	*/

	// All ship and booster animations
	superUpwards.PushBack({ 154, 66, 27, 17 });
	superUpwards.speed = 0.1f;

	superUpwardsBooster.PushBack({ 43, 63, 12, 17 });
	superUpwardsBooster.PushBack({ 0, 0, 12, 17 });
	superUpwardsBooster.PushBack({ 62, 63, 12, 17 });
	superUpwardsBooster.PushBack({ 0, 0, 12, 17 });
	superUpwardsBooster.PushBack({ 74, 63, 12, 17 });
	superUpwardsBooster.PushBack({ 0, 0, 12, 17 });
	superUpwardsBooster.PushBack({ 62, 63, 12, 17 });
	superUpwardsBooster.PushBack({ 0, 0, 12, 17 });
	superUpwardsBooster.speed = 1.2f;

	upwards.PushBack({ 154, 87, 27, 17 });
	upwards.speed = 0.1f;

	upwardsBooster.PushBack({ 43, 87, 12, 17 });
	upwardsBooster.PushBack({ 0, 0, 12, 17 });
	upwardsBooster.PushBack({ 62, 87, 12, 17 });
	upwardsBooster.PushBack({ 0, 0, 12, 17 });
	upwardsBooster.PushBack({ 74, 87, 12, 17 });
	upwardsBooster.PushBack({ 0, 0, 12, 17 });
	upwardsBooster.PushBack({ 62, 87, 12, 17 });
	upwardsBooster.PushBack({ 0, 0, 12, 17 });
	upwardsBooster.speed = 1.2f;

	idle.PushBack({ 154, 108, 27, 17 });
	idle.speed = 0.1f;

	idleBooster.PushBack({ 43, 108, 12, 17 });
	idleBooster.PushBack({ 0, 0, 12, 17 });
	idleBooster.PushBack({ 62, 108, 12, 17 });
	idleBooster.PushBack({ 0, 0, 12, 17 });
	idleBooster.PushBack({ 74, 108, 12, 17 });
	idleBooster.PushBack({ 0, 0, 12, 17 });
	idleBooster.PushBack({ 62, 108, 12, 17 });
	idleBooster.PushBack({ 0, 0, 12, 17 });
	idleBooster.speed = 1.2f;

	downwards.PushBack({ 154, 131, 27, 17 });
	downwards.speed = 0.1f;

	downwardsBooster.PushBack({ 43, 131, 12, 17 });
	downwardsBooster.PushBack({ 0, 0, 12, 17 });
	downwardsBooster.PushBack({ 62, 131, 12, 17 });
	downwardsBooster.PushBack({ 0, 0, 12, 17 });
	downwardsBooster.PushBack({ 74, 131, 12, 17 });
	downwardsBooster.PushBack({ 0, 0, 12, 17 });
	downwardsBooster.PushBack({ 62, 131, 12, 17 });
	downwardsBooster.PushBack({ 0, 0, 12, 17 });
	downwardsBooster.speed = 1.2f;

	superDownwards.PushBack({ 154, 153, 27, 17 });
	superDownwards.speed = 0.1f;

	superDownwardsBooster.PushBack({ 43, 153, 12, 17 });
	superDownwardsBooster.PushBack({ 0, 0, 12, 17 });
	superDownwardsBooster.PushBack({ 62, 153, 12, 17 });
	superDownwardsBooster.PushBack({ 0, 0, 12, 17 });
	superDownwardsBooster.PushBack({ 74, 153, 12, 17 });
	superDownwardsBooster.PushBack({ 0, 0, 12, 17 });
	superDownwardsBooster.PushBack({ 62, 153, 12, 17 });
	superDownwardsBooster.PushBack({ 0, 0, 12, 17 });
	superDownwardsBooster.speed = 1.2f;
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
update_status ModulePlayer2::Update()	// Ship and booster used based on movVertical value, which changes on pressing W and S keys or neither
{
	Animation* current_animation = &idle;
	Animation* propeller_animation = &idleBooster;

	int speed = 2;

	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
		position.y += speed;

		if (movVertical > -maxVertical)
		{
			--movVertical;		// Decrease vertical counter.
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_W] == 1)
	{
		position.y -= speed;

		if (movVertical < maxVertical)
		{
			++movVertical;		// Increase vertical counter.
		}
	}

	else if (App->input->keyboard[SDL_SCANCODE_W] == 0 && App->input->keyboard[SDL_SCANCODE_S] == 0)
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

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		position.x -= speed;
	}

	else if (App->input->keyboard[SDL_SCANCODE_D] == 1)
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

	App->render->Blit(graphics, position.x - 12, position.y - r.h, &p);
	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}

bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player 2");
	App->textures->Unload(graphics);

	App->player2->Disable();

	return true;
}