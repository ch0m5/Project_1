#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStage1.h"
#include "ModuleStage2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleHiScore.h"

ModuleStage2::ModuleStage2()	//@AndresSala
{
	//ANDRO DUNOS RECTS
	// Background1Rect  
	background2Rect.x = 48;
	background2Rect.y = 27;
	background2Rect.w = 410;
	background2Rect.h = 224;

	//map1Rect	
	map2Rect.x = 0;
	map2Rect.y = 60; // 60
	map2Rect.w = 9305;
	map2Rect.h = 505;

	// bluePlanetRect
	/*bluePlanetRect.x = 0;
	bluePlanetRect.y = 0;
	bluePlanetRect.w = 165;
	bluePlanetRect.h = 152;*/
}

ModuleStage2::~ModuleStage2()
{}

// Load assets
bool ModuleStage2::Start()
{
	LOG("Loading background assets");	// Temporal, must decide if we load a full image,
	bool ret = true;					// a single enormous tileset, maybe a tile array for the background

										//map2Text = App->textures->Load("Sprites/Levels/STAGE 2/Tileset/Background_lvl_2.png");
	background2Text = App->textures->Load("Sprites/Levels/STAGE 2/Tileset/Background_lvl_2.png");
	/*bluePlanetText = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/Moon.png");*/

	App->player1->Enable();
	App->player2->Enable();

	return ret;
}

bool ModuleStage2::CleanUp()
{
	LOG("Unloading stage 2");
	App->textures->Unload(background2Text);

	LOG("Unloading players");
	App->player1->Disable();
	App->player2->Disable();

	return true;
}

// Update: draw background
update_status ModuleStage2::Update()
{
	//App->render->Blit(background2Text, 0, 0, &background2Rect); // level background

	/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->scene_HiScore, 0.5);
	}*/

	//@andressala


	return UPDATE_CONTINUE;
}