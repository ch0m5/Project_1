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

	//ANDRO DUNOS RECTS
	// Background1Rect  // i dont know why this  isnt working 
	background1Rect.x = 0;
	background1Rect.y = 0; // i think the problem is here but i couldnt find it
	background1Rect.w = 1654; //1654
	background1Rect.h = 85;

	//map1Rect	
	map1Rect.x = 0;
	map1Rect.y = 60; // 60
	map1Rect.w = 9305;
	map1Rect.h = 505;

	// bluePlanetRect
	bluePlanetRect.x = 0;
	bluePlanetRect.y = 0;
	bluePlanetRect.w = 165;
	bluePlanetRect.h = 152;
}

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	map1Text = App->textures->Load("Sprites/Backgrounds/1_FullMap.png");
	background1Text = App->textures->Load("Sprites/Backgrounds/1_Background1.png");
	bluePlanetText = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/Moon.png");
	return ret;
}

// Update: draw background
update_status ModuleBackground::Update()
{
	if (shipPos >= 5)
		boatUp = false;

	else if (shipPos <= -5)
		boatUp = true;

	// Draw everything -------------------------------------- Andro Dunos
	App->render->Blit(background1Text, movementxBack, 118, &background1Rect); // level background

	App->render->Blit(map1Text, movementx, -55, &map1Rect); // level map

	App->render->Blit(bluePlanetText, 500 + movementxPlanetsBack, -10, &bluePlanetRect);

	movementx -= 0.83f; // for movement in x direction
	movementxBack -= 0.38f;
	movementxPlanetsBack -= 0.2f;


	return UPDATE_CONTINUE;
}