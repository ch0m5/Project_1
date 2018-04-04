#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleStage1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleStage2.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"


ModuleStage1::ModuleStage1()	//@AndresSaladrigas
{
	//ANDRO DUNOS RECTS
	// Background1Rect  
	background1Rect.x = 0;
	background1Rect.y = 0; 
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

ModuleStage1::~ModuleStage1()
{}

// Load assets
bool ModuleStage1::Start()
{
	LOG("Loading background assets");	// Temporal, must decide if we load a full image,
	bool ret = true;					// a single enormous tileset, maybe a tile array for the background
	map1Text = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/1_FullMap1.png");
	background1Text = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/1_Background1.png");
	bluePlanetText = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/Moon.png");

	App->player1->Enable();
	App->player2->Enable();
	
	return ret;

}

// Unload assets
bool ModuleStage1::CleanUp()
{
	App->player1->Disable();
	App->player2->Disable();
	
	//LOG("Unloading players stage");

	return true;
}

// Update: draw background
update_status ModuleStage1::Update()
{


	// Draw everything -------------------------------------- Andro Dunos
	App->render->Blit(background1Text, movementxBack, 118, &background1Rect); // level background

	App->render->Blit(map1Text, movementx, movementy, &map1Rect); // level map

	App->render->Blit(bluePlanetText, 500 + movementxPlanetsBack, -10, &bluePlanetRect); // Moon

	movementx -= 0.83f; // for movement in x direction
	LOG("%0.3f", movementx);
	movementxBack -= 0.38f;
	movementxPlanetsBack -= 0.2f;

	//make so pressing SPACE the other stage is loaded
	/*if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->stage1, App->stage2, 1);
	}*/

	//if (movementx >-2925.0) //2925
	//movementx -= 0.83f; // for movement in x direction
	////if (movementx == -2925.0 && movementy > -280.0) 
	////{
	////movementy -= 0.83f; 
	////}
	////if (movementx == -2925 && movementy == -280)
	////{
	////	movementx -= 0.83f;
	////}
	////if (movementx < -2925 && movementy >= -280)
	//{
	//	movementx -= 0.83f;
	//}//@andressala


	return UPDATE_CONTINUE;
}