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
	backgroundRect.y = 0;
	backgroundRect.w = 1654; //1654
	backgroundRect.h = 85;

	// TitleBoxRect (blue box behind the title letters)
	titleBoxRect.x = 0;
	titleBoxRect.y = 0;
	titleBoxRect.w = 0;
	titleBoxRect.h = 0;

	// TitleRect
	titleRect.x = 0;
	titleRect.y = 0;
	titleRect.w = 0;
	titleRect.h = 0;

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
	//backgroundText = App->textures->Load("Sprites/User_Interface/Intro/logo-background.png");
	//titleText = App->textures->Load("Sprites/User_Interface/Intro/1_FullMap.png");
	//viscoGamesText = App->textures->Load("Sprites/User_Interface/Intro/1_FullMap.png");
	//orangeLettersText = App->textures->Load("Sprites/Backgrounds/1_FullMap.png");
	//whiteLettersText = App->textures->Load("Sprites/Backgrounds/1_FullMap.png");
	return ret;
}

// Update: draw background
update_status ModuleMainMenu::Update()
{


	// Draw everything -------------------------------------- Andro Dunos
	//App->render->Blit(background1Text, movementxBack, 118, &background1Rect); // level background

	//App->render->Blit(map1Text, movementx, movementy, &map1Rect); // level map

	//App->render->Blit(bluePlanetText, 500 + movementxPlanetsBack, -10, &bluePlanetRect); // Moon

	return UPDATE_CONTINUE;
}