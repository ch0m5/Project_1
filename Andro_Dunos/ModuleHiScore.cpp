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
#include "ModuleShieldsP1.h"
#include "ModuleShieldsP2.h"


ModuleHiScore::ModuleHiScore()	//@D�dacRomero
{
	//ANDRO DUNOS RECTS
	//Crashed Ships Background 
	hiScoreBackRect.x = 110;
	hiScoreBackRect.y = 193;
	hiScoreBackRect.w = 320;
	hiScoreBackRect.h = 224;
}

ModuleHiScore::~ModuleHiScore()
{}

// Load assets
bool ModuleHiScore::Start()
{
	LOG("Loading background assets");	// Temporal, must decide if we load a full image,
	bool ret = true;					// a single enormous tileset, maybe a tile array for the background
	hiScoreBackTex = App->textures->Load("Assets/Sprites/User_Interface/Grafical_Interface/game_over_background.png");

	App->collision->Disable();
	

	//Set the animation Speed to initial condition
	ySpeedAnimation = 0;
	//Music
	MusicHighScore = App->mixer->LoadMusic("Assets/Audio/Music/18_Game_Over.ogg");
	Mix_FadeInMusic(MusicHighScore, 0, 1000);
	Mix_VolumeMusic(MUSICVol);

	return ret;
}

// Update: draw background
update_status ModuleHiScore::Update()
{
	// Draw everything -------------------------------------- Andro Dunos
	
	App->render->Blit(hiScoreBackTex,10,200+ySpeedAnimation, &hiScoreBackRect); // Crashed Ship background Drawn on Screen
	
	//Small animation, Crashed ship appears from the lower part until all the sprite is seen
	if (200+ySpeedAnimation>100)
	{
		ySpeedAnimation -= 1;
	}
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->scene_HiScore, App->mainMenu, 1);
	}
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->scene_HiScore, App->stage1, 1);
	}

	return UPDATE_CONTINUE;
}

bool ModuleHiScore::CleanUp()
{
	LOG("Cleaning HiScore Module");	// Temporal, must decide if we load a full image,
	bool ret = true;					// a single enormous tileset, maybe a tile array for the background
	App->textures->Unload(hiScoreBackTex);
	App->scene_HiScore->Disable();
	Mix_FadeOutMusic(TIMEFADE);
	App->mixer->UnloadMusic(MusicHighScore);
	
	return ret;
}