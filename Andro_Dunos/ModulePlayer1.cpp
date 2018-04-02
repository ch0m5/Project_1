/*#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer1.h"

ModulePlayer1::ModulePlayer1()
{
	position.x = 100;
	position.y = 220;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	upwards.PushBack({ 78, 131, 60, 88 });
	upwards.PushBack({ 162, 128, 64, 92 });
	upwards.PushBack({ 259, 128, 63, 90 });
	upwards.PushBack({ 352, 128, 54, 91 });
	upwards.PushBack({ 432, 131, 50, 89 });
	upwards.speed = 0.1f;

	// TODO 4: Make ryu walk backwards with the correct animations (NOT DONE)
	downwards.PushBack({ 432, 131, 50, 89 });
	downwards.PushBack({ 352, 128, 54, 91 });
	downwards.PushBack({ 259, 128, 63, 90 });
	downwards.PushBack({ 162, 128, 64, 92 });
	downwards.PushBack({ 78, 131, 60, 88 });
	downwards.speed = 0.1f;

}

ModulePlayer1::~ModulePlayer1()
{}

// Load assets
bool ModulePlayer1::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer1::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}

	else if (App->input->keyboard[SDL_SCANCODE_UP] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	else if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);

	return UPDATE_CONTINUE;
}*/