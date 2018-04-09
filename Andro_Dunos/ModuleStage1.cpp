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
#include "ModuleHiScore.h"
#include "ModuleMixer.h"


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
	map1Rect.y = 58; // 60
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

	
	background1Text = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/1_Background1.png");
	bluePlanetText = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/Moon.png");
 	map1Text = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/FullMap1.png");

	App->player1->Enable();
	App->player2->Enable();
	// we shoukd log the problem if not loaded correctly
	
	//Music
	MusicLvl1 = App->mixer->LoadMusic("Music/04_Stage_1-The Moon-Loop.ogg");
	Mix_FadeInMusic(MusicLvl1, -1, 1000);
	Mix_Volume(-1, 15);
	return ret;

}

// Unload assets
bool ModuleStage1::CleanUp()
{
	LOG("Unloading players");
	App->player1->Disable();
	App->player2->Disable();

	LOG("Unloading stage 1");
	App->textures->Unload(map1Text);
	App->textures->Unload(background1Text);
	App->textures->Unload(bluePlanetText);
	

	

	return true;
}

// Update: draw background
update_status ModuleStage1::Update()
{


	// Draw everything -------------------------------------- Andro Dunos
	App->render->Blit(background1Text, movementxBack, 118 + movementyBack, &background1Rect); // level background

	App->render->Blit(map1Text, movementx, -55 + movementy, &map1Rect); // level map

	App->render->Blit(bluePlanetText, 500 + movementxPlanetsBack, -10, &bluePlanetRect); // Moon

	//Level 1 Map movement Code

	if (moveMapRight==true)
	{
		movementx -= 0.83f; // for movement in x direction
		LOG("%0.3f", movementx);
		movementxBack -= 0.38f;
		movementxPlanetsBack -= 0.2f;
	}
	// TO BE IMPLEMENTED if's for moveMapUp & moveMapDown
	if (moveMapDown == true)
	{
		movementy -= 0.82f;
		movementyBack -= 0.38f;
	}
	if (moveMapUp == true)
	{
		movementy += 0.82f;
		movementyBack += 0.38f;
	}
	//Conditions: Where does the background change X and Y speeds
	if (movementx < -2920) // 1st SPEED CHANGE: Ships enter the inside of the Moon 
	{
		moveMapRight = false;
		moveMapDown = true;
	}
	if (movementy < -226) // 2nd SPEED CHANGE: Ships continue through the inside of the Moon
	{
		moveMapRight = true;
		moveMapDown = false;
	}
	if (movementx < -4015) // 3rd SPEED CHANGE: Ships continue through the inside of the Moon:: Diagonal Upwards movement 1/3
	{
		moveMapRight = false;
		moveMapUp = true;
	}

	// Implement the other SPEED CHANGES Currently 3/12


	//make so pressing SPACE the other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->stage1, App->stage2, 1);
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