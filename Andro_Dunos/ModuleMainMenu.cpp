#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMainMenu.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleStage1.h"
#include "ModuleInput.h"
#include "ModuleHiScore.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMixer.h"


ModuleMainMenu::ModuleMainMenu()	//@CarlesHoms
{
	//ANDRO DUNOS RECTS

	// BackgroundRect
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = 320;
	backgroundRect.h = 224;

	// TitleBoxRect (blue box behind the title letters)
	titleBoxRect.x = 9;
	titleBoxRect.y = 162;
	titleBoxRect.w = 208;
	titleBoxRect.h = 44;

	// TitleRect
	titleRect.x = 7;
	titleRect.y = 47;
	titleRect.w = 240;
	titleRect.h = 112;

	// ViscoGamesRect
	viscoGamesRect.x = 40;
	viscoGamesRect.y = 116;
	viscoGamesRect.w = 167;
	viscoGamesRect.h = 15;
}

ModuleMainMenu::~ModuleMainMenu()
{}

// Load assets
bool ModuleMainMenu::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	backgroundText = App->textures->Load("Sprites/User_Interface/Intro/logo-background.png");
	titleText = App->textures->Load("Sprites/User_Interface/Intro/logo.png");
	viscoGamesText = App->textures->Load("Sprites/User_Interface/Intro/visco_games.png");
	//orangeLettersText = App->textures->Load("Sprites/Backgrounds/1_FullMap.png");
	//whiteLettersText = App->textures->Load("Sprites/Backgrounds/1_FullMap.png");

	App->player1->Disable();
	App->player2->Disable();

	//Music
	MusicMainMenu = App->mixer->LoadMusic("Music/02_Title.ogg");
	Mix_Volume(-1, MUSIC);
	Mix_FadeInMusic(MusicMainMenu, 0, 1000);
	
	return ret;
}

// Update: draw background
update_status ModuleMainMenu::Update()
{
	App->render->Blit(backgroundText, 0, 0, &backgroundRect); // background
	App->render->Blit(titleText, 52, 60, &titleBoxRect); // logo back mark
	App->render->Blit(titleText, 36, 27, &titleRect); // logo
	App->render->Blit(viscoGamesText, 75, 160, &viscoGamesRect); // Visco Games

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->stage1, 0.5);
	}

	if (App->input->keyboard[SDL_SCANCODE_1] == 1) //press for 1 player mode @AndresSala
	{
		App->input->secondPlayerState = false;
	}


	if (App->input->keyboard[SDL_SCANCODE_2] == 1) // press for 2 players mode  @AndresSala
	{
		App->input->secondPlayerState = true;
	}

	return UPDATE_CONTINUE;
}

bool ModuleMainMenu::CleanUp()
{
	App->player1->Disable();
	App->player2->Disable();
	
	LOG("Unloading Main Menu");
	App->textures->Unload(backgroundText);
	App->textures->Unload(titleText);
	App->textures->Unload(viscoGamesText);
	//App->textures->Unload(orangeLettersText);
	//App->textures->Unload(whiteLettersText);

	return true;
}