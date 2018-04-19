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
#include "ModuleMainMenu.h"
#include "ModuleMixer.h"
#include "ModuleCollision.h"
#include "ModuleStageClear.h"



ModuleStageClear::ModuleStageClear()	//@Andres
{
	//ANDRO DUNOS RECTS
	//Stage Clear Background 
	stageClearRect.x = 108;
	stageClearRect.y = 232;
	stageClearRect.w = 304;
	stageClearRect.h = 48;
}

ModuleStageClear::~ModuleStageClear()
{}

// Load assets
bool ModuleStageClear::Start()
{
	LOG("Loading background assets");	// 
	bool ret = true;					//
	stageClearText = App->textures->Load("Assets/Sprites/User_Interface/Stage_Clear/StageClear-(1).png");

	App->collision->Disable();
	App->player1->Disable();
	App->player2->Disable();

	//Set the animation Speed to initial condition
	ySpeedAnimation = 0;
	//Music
	MusicStageClear = App->mixer->LoadMusic("Assets/Audio/Music/06_Stage_Clear.ogg");
	Mix_FadeInMusic(MusicStageClear, 0, 1000);
	Mix_VolumeMusic(MUSICVol);

	return ret;
}

// Update: draw background
update_status ModuleStageClear::Update()
{
	// Draw everything -------------------------------------- Andro Dunos

	App->render->Blit(stageClearText, 10, 200 + ySpeedAnimation, &stageClearRect); // Crashed Ship background Drawn on Screen
	
																				   //Small animation, Crashed ship appears from the lower part until all the sprite is seen
	if (200 + ySpeedAnimation>50)
	{
		ySpeedAnimation -= 1;
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->stageClear, App->mainMenu, 1);
	}


	return UPDATE_CONTINUE;
}

bool ModuleStageClear::CleanUp()
{
	LOG("Cleaning HiScore Module");	// Temporal, must decide if we load a full image,
	bool ret = true;					// a single enormous tileset, maybe a tile array for the background
	App->textures->Unload(stageClearText);
	App->stageClear->Disable();
	App->mixer->UnloadMusic(MusicStageClear);

	return ret;
}