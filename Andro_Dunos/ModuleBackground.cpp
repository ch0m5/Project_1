#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleBackground.h"

// Reference at https://www.youtube.com/watch?v=iQOrXlf34es&t=993s

ModuleBackground::ModuleBackground()
{
	

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
	////ship1Rect	
	//ship1Rect.x = 0;
	//ship1Rect.y = 0;
	//ship1Rect.w = 27;
	//ship1Rect.h = 17;

	//// animation template for busters
	//flag.PushBack({ 848, 208, 40, 40 });
	//flag.PushBack({ 848, 256, 40, 40 });
	//flag.PushBack({ 848, 304, 40, 40 });
	//flag.speed = 0.08f;

}//@AndresSala

ModuleBackground::~ModuleBackground()
{}

// Load assets
bool ModuleBackground::Init()
{
	LOG("Loading background assets");
	bool ret = true;
	map1Text = App->textures->Load("Sprites/Backgrounds/1_FullMap.png");
	background1Text = App->textures->Load("Sprites/Backgrounds/1_Background1.png");
	bluePlanetText = App->textures->Load("Sprites/Levels/STAGE 1/Tileset/Background/Moon.png");
	return ret;
}//@AndresSala & @DídacRo

// Update: draw background
update_status ModuleBackground::Update()
{
	// Draw everything --------------------------------------
	App->render->Blit(background1Text, movementxBack, 118, &background1Rect); // level background
	
	App->render->Blit(map1Text, movementx, -55, &map1Rect); // level map
	
	App->render->Blit(bluePlanetText, 500 + movementxPlanetsBack, -10, &bluePlanetRect);

	movementx-=0.83; // for movement in x direction
	movementxBack-=0.39;
	movementxPlanetsBack-= 0.2;
	return UPDATE_CONTINUE;
}//@AndresSala  & DídacRo