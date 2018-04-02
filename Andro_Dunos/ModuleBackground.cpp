#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleBackground::ModuleBackground()
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	ship.x = 8;
	ship.y = 38;
	ship.w = 520;
	ship.h = 185;

	girl.PushBack({ 623, 16, 32, 56 });
	girl.PushBack({ 623, 80, 32, 56 });
	girl.PushBack({ 623, 144, 32, 56 });
	girl.PushBack({ 623, 80, 32, 56 });
	girl.speed = 0.08f;

	// flag animation
	flag.PushBack({848, 208, 40, 40});
	flag.PushBack({848, 256, 40, 40});
	flag.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("ken_stage.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	if (boatUp == true)
	{
		shipPos += 0.1;
	}

	else if (boatUp == false)
	{
		shipPos -= 0.1;
	}

	if (shipPos >= 5)
		boatUp = false;

	else if (shipPos <= -5)
		boatUp = true;

	// Draw everything --------------------------------------
	App->render->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->render->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation

	// TODO 2: Draw the ship from the sprite sheet with some parallax effect

	App->render->Blit(graphics, 0, shipPos+15, &ship, 0.75f); // ship

	// TODO 3: Animate the girl on the ship (see the sprite sheet)
	App->render->Blit(graphics, 191, shipPos+105, &(girl.GetCurrentFrame()), 0.75f);
	
	App->render->Blit(graphics, 0, 170, &ground);

	return UPDATE_CONTINUE;
}