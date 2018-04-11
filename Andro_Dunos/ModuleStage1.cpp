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
#include "ModuleCollision.h"

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
	if (App->input->secondPlayerState == true)  //@AndresSala
	{
		App->player2->Enable();
	}
	// we shoukd log the problem if not loaded correctly
	
	// Collider
	App->collision->Enable();

	// Ground Collider
	
	App->collision->AddCollider({ 0, 195, 4000, 30 }, COLLIDER_WALL);


	//Music
	MusicLvl1 = App->mixer->LoadMusic("Music/04_Stage_1-The Moon-Loop.ogg");
	Mix_FadeInMusic(MusicLvl1, -1, 1000);
	Mix_VolumeMusic(MUSICVol);
	return ret;

}

// Unload assets
bool ModuleStage1::CleanUp()
{

	// reset Background movement (position) values
	//X Axis
	 movementx = 0;
	 movementxBack = 0;
	 movementxPlanetsBack = 0;
	//Y Axis
	 movementy = 0;
	 movementyBack = 0;

	 //--------
	LOG("Unloading players");
	App->player1->Disable();
	if (App->input->secondPlayerState == true) //@AndresSala
	{
		App->player2->Disable();
	}

	LOG("Unloading stage 1");
	App->textures->Unload(map1Text);
	App->textures->Unload(background1Text);
	App->textures->Unload(bluePlanetText);

	LOG("Unloading colliders")
	App->collision->Disable();

	

	return true;
}

// Update: draw background
update_status ModuleStage1::Update()
{


	// Draw everything -------------------------------------- Andro Dunos
	App->render->Blit(background1Text, movementxBack, 120 + movementyBack, &background1Rect); // level background

	App->render->Blit(map1Text, movementx, -55 + movementy, &map1Rect); // level map

	App->render->Blit(bluePlanetText, 500 + movementxPlanetsBack, -10, &bluePlanetRect); // Moon

																						 //Level 1 Map movement Code
	if (moveMapRight == true && fasterX == false)
	{
		movementx -= xSpeedMultiplier*0.83f; // for movement in x direction
		LOG("%0.3f", movementx);
		movementxBack -= xSpeedMultiplier*0.38f;
		movementxPlanetsBack -= xSpeedMultiplier*0.2f;
	}
	if (moveMapDown == true)
	{
		movementy -= ySpeedMultiplier * 0.82f;
		movementyBack -= ySpeedMultiplier * 0.38f;
	}
	if (moveMapUp == true)
	{
		movementy += ySpeedMultiplier * 0.82f;
		movementyBack += ySpeedMultiplier * 0.38f;
	}
	//Conditions: Where does the background change X and Y speeds
	if (movementx < -2920) // 1st SPEED CHANGE: Ships enter the inside of the Moon 
	{
		moveMapRight = false;
		moveMapDown = true;
		moveMapUp = false;
	}
	if (movementy < -226 && moveMapUp == false) // 2nd SPEED CHANGE: Ships continue through the inside of the Moon
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	if (movementx < -4015) // 3rd SPEED CHANGE: Ships continue through the inside of the Moon:: Diagonal Upwards movement 1/2
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = true;
		//xSpeedMultiplier =1;
	}
	if (movementx < -4145) // 4th SPEED CHANGE: Ships continue through the inside of the Moon:: now straight to Right 1/4
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
		//xSpeedMultiplier = 7;
	}
	if (movementx < -4530) // 5th SPEED CHANGE: Ships continue through the inside of the Moon:: Diagonal Downwards to Right 1/2
	{
		//xSpeedMultiplier = 1;
		moveMapRight = true;
		moveMapDown = true;
		moveMapUp = false;
	}
	if (movementx < -4658) // 6th SPEED CHANGE: Ships continue through the inside of the Moon:: now Straight to Right 2/4
	{
		//xSpeedMultiplier = 7;
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	if (movementx < -5071) // 7th SPEED CHANGE: Ships continue through the inside of the Moon:: Diagonal Upwards to Right 2/2
	{
		//xSpeedMultiplier = 1;
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = true;
	}
	if (movementx < -5300) // 8th SPEED CHANGE: Ships continue through the inside of the Moon:: Straight to Right 3/4
	{
		//xSpeedMultiplier = 7;
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	if (movementx < -6044) // 9th SPEED CHANGE: Ships continue through the inside of the Moon:: Downwards to Right 2/2
	{
		//xSpeedMultiplier = 1;
		ySpeedMultiplier = 0.65;
		moveMapRight = true;
		moveMapDown = true;
		moveMapUp = false;
	}
	if (movementx < -6390) // 10th SPEED CHANGE: Ships continue through the inside of the Moon:: Straight to Right 4/4
	{
		//xSpeedMultiplier = 7;
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	if (movementx < -7130) // 11th SPEED CHANGE: Ships EXIT the inside of the Moon
	{

		moveMapRight = false;
		moveMapDown = false;
		moveMapUp = true;
	}
	if (movementy > 0 && moveMapUp == true && movementx < -7130) // 12th SPEED CHANGE: Ships are OUTSIDE the Moon. They leave to the right
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}

	//make so pressing SPACE the other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->stage1, App->stage2, 1);
	}

	/*
	//Debugging purpose methods
	if (App->input->keyboard[SDL_SCANCODE_LSHIFT] == 1 && fasterX == false)
	{
	fasterX = true;
	}
	else if (App->input->keyboard[SDL_SCANCODE_LSHIFT] == 1 && fasterX == true)
	{
	fasterX == false;
	}

	if (fasterX == true)
	{
	movementx -= 5*0.83f; // for movement in x direction
	LOG("%0.3f", movementx);
	movementxBack -= 5*0.38f;
	movementxPlanetsBack -= 5*0.2f;
	}
	*/
	return UPDATE_CONTINUE;

}