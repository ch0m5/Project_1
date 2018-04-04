#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMainMenu.h"

ModuleMainMenu::ModuleMainMenu()	//@CarlesHoms
{
	//ANDRO DUNOS RECTS

	// BackgroundRect
	backgroundRect.x = 0;
	backgroundRect.y = 16;
	backgroundRect.w = 256;
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
	viscoGamesRect.x = 0;
	viscoGamesRect.x = 0;
	viscoGamesRect.x = 0;
	viscoGamesRect.x = 0;
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
	return ret;
}

// Update: draw background
update_status ModuleMainMenu::Update()
{
	App->render->Blit(backgroundText, 0, 0, &backgroundRect); // background
	App->render->Blit(titleText, 20, 20, &titleBoxRect); // logo back mark
	App->render->Blit(titleText, 20, 20, &titleRect); // logo
	App->render->Blit(viscoGamesText, 20, 120, &viscoGamesRect); // Visco Games

	return UPDATE_CONTINUE;
}