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
#include "ModuleMixer.h"

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
	
	background2Text = App->textures->Load("Sprites/Levels/STAGE 2/Tileset/Background_lvl_2.png");

	App->player1->Enable();
	App->player2->Enable();

	//Music
	MusicLvl2 = App->mixer->LoadMusic("Music/07_Stage_2 -Mechanized-Unit-Loop.ogg");
	Mix_FadeInMusic(MusicLvl2, -1, 1000);
	Mix_Volume(-1, MUSIC);
	return ret;
}

bool ModuleStage2::CleanUp()
{
	App->player1->Disable();
	App->player2->Disable();
	
	//LOG("Unloading players stage");
	App->textures->Unload(background2Text);

	return true;
}

// Update: draw background
update_status ModuleStage2::Update()
{
	// Draw everything -------------------------------------- Andro Dunos
	App->render->Blit(background2Text, movementxBack, 0, &background2Rect); // level background

	//make so pressing SPACE the other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->stage2, App->scene_HiScore, 1);
	}

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