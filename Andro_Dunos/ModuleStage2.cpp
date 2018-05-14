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
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleStageClear.h"
#include "ModuleParticles.h"
#include "ModuleUserInterface.h"

ModuleStage2::ModuleStage2()	//@AndresSala
{
	//ANDRO DUNOS RECTS
	// Background1Rect  
	background2Rect.x = 0;
	background2Rect.y = 0;
	background2Rect.w = 2101; 
	background2Rect.h = 224;

	// Backgroundciry 
	backgroundCityRect.x = 0;
	backgroundCityRect.y = 0;
	backgroundCityRect.w = 1663;
	backgroundCityRect.h = 98;


	//map1Rect	
	map2Rect.x = 0;
	map2Rect.y = 0; 
	map2Rect.w = 6983;
	map2Rect.h = 636;

}

ModuleStage2::~ModuleStage2()
{}

// Load assets
bool ModuleStage2::Start()
{
	LOG("Loading background assets");	// Temporal, must decide if we load a full image,
	bool ret = true;					// a single enormous tileset, maybe a tile array for the background
	
	background2Text = App->textures->Load("Assets/Sprites/Levels/STAGE 6/Tileset/background.png");
	backgroundCityText = App->textures->Load("Assets/Sprites/Levels/STAGE 6/Tileset/background_city.png");
	map2Text = App->textures->Load("Assets/Sprites/Levels/STAGE 6/Tileset/floor lvl 6.png");

	App->player1->godMode = false;
	App->player2->godMode = false;
	App->player1->Enable();
	if (App->input->secondPlayerState == true) //@AndresSala
	{
		App->player2->Enable();
	}


	// we should log the problem if not loaded correctly

	App->collision->Enable();
	App->particles->Enable();

	//ship position
	App->player1->position.x = 20;
	App->player2->position.x = 20;
	App->player1->position.y = 50;
	App->player2->position.y = 100;

	// Enemies
	App->enemies->Enable();

	//Score
	App->UI->teamScore = 0;
	App->UI->player1Score = 0;
	App->UI->player2Score = 0;

	//Music
	MusicLvl2 = App->mixer->LoadMusic("Assets/Audio/Music/13_Stage_6 -Secret-Base-Intro.ogg");
	Mix_FadeInMusic(MusicLvl2, -1, 1000);
	Mix_VolumeMusic(MUSICVol);
	

	// Ground Collider @Andres
	App->collision->AddCollider({ 91, 0 , 495, 10}, COLLIDER_WALL);
	App->collision->AddCollider({ 0, 198 , 160, 26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 56, 176 , 68, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 174, 216 , 97, 8 }, COLLIDER_WALL);
	App->collision->AddCollider({ 238, 106 , 188, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 692, 197 , 181, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 394, 217 , 494, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 716, 183 , 116, 11 }, COLLIDER_WALL);
	App->collision->AddCollider({ 586, 11 , 111, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 629, 31 , 67, 9 }, COLLIDER_WALL);
	return ret;
}

bool ModuleStage2::CleanUp()
{
	// reset Background movement (position) values
	movementx = 0;
	movementxBack = 0;
	movementy = -55;

	//Reset Camera Position
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	//Reset starting directions
	moveMapRight = true;
	moveMapDown = false;
	moveMapUp = false;


	//--------
	LOG("Unloading players");
	App->player1->Disable();
	if (App->input->secondPlayerState == true) //@AndresSala
	{
		App->player2->Disable();
	}

	LOG("Unloading enemies");
	App->enemies->Disable();

	LOG("Unloading stage 2");
	App->textures->Unload(background2Text);
	App->textures->Unload(map2Text);
	App->textures->Unload(backgroundCityText);

	LOG("Unloading colliders")
		App->collision->Disable();

	LOG("Unloading particles")
		App->particles->Disable();

	Mix_FadeOutMusic(TIMEFADE);
	App->mixer->UnloadMusic(MusicLvl2);

	return true;
}

// Update: draw background
update_status ModuleStage2::Update()
{
	//Level 1 Map movement Code

	if (moveMapRight == true)
	{
		movementx += xSpeedMultiplier*0.83f; // for movement in x direction
											 //LOG("%0.3f", movementx);
		movementxBack += xSpeedMultiplier*0.37f;
		
		App->render->camera.x = 3.25*movementx / 3;		//Must change this HARDCODE to 1 single value
		
		
	}
	if (moveMapDown == true)
	{
		
		movementy += ySpeedMultiplier*0.25f;
	

		App->render->camera.y = 3*movementy/3;  //Must change this HARDCODE to 1 single value

	}
	if (moveMapUp == true)
	{
		movementy -= ySpeedMultiplier * 0.82f;
		App->render->camera.y = 3.25*movementy / 3;  //Must change this HARDCODE to 1 single value
	}

	//Conditions: Where does the background change X and Y speeds
	if (App->render->camera.x > 3800 * SCREEN_SIZE) // 1st SPEED CHANGE: Ships enter the inside of the Moon 
	{
		moveMapRight = false;
		moveMapDown = true;
		moveMapUp = false;
	}

	if (App->render->camera.y > 411 * SCREEN_SIZE /*&& App->render->camera.y > 4279 * SCREEN_SIZE*/ && moveMapUp == false) // 2nd SPEED CHANGE: Ships continue through the inside of the Moon
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}

	
	// Win Condition
	if (App->render->camera.x / SCREEN_SIZE > 6700)
	{
		App->fade->FadeToBlack(this, App->stageClear, 1);
	}

	//make so pressing SPACE the other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && App->input->debugMode == true)
	{
		App->fade->FadeToBlack(App->stage2, App->scene_HiScore, 1);
	}

	//enter direct win condition @Andres
	if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_DOWN && App->input->debugMode == true)
	{
		App->fade->FadeToBlack(App->stage1, App->stageClear, 1);
	}
	//enter direct lose condition @Andres
	if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN && App->input->debugMode == true)
	{
		App->fade->FadeToBlack(App->stage1, App->scene_HiScore, 1);
	}

	//FasterX function Increase the horizontal velocity 
	if (App->input->debugMode == false)
	{

		fasterX = false;
		xSpeedMultiplier = 1;

	}
	if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_DOWN && App->input->debugMode == true)
	{
		if (App->input->keyboard[SDL_SCANCODE_F4] != KEY_REPEAT)
		{
			fasterX = !fasterX;
		}

		if (fasterX == true)
		{
			xSpeedMultiplier = 10;
		}
		else if (fasterX == false)
		{
			xSpeedMultiplier = 1;
		}

		if (App->render->camera.x / SCREEN_SIZE > 8912)
		{
			App->fade->FadeToBlack(this, App->stageClear, 1);
		}

	}

	// Draw everything -------------------------------------- Andro Dunos
	
	//These two if's control the first part of the level outside and the end of the level also outside
	
	App->render->Blit(backgroundCityText, 4112, 538, &backgroundCityRect); // level background

	App->render->Blit(background2Text, movementxBack, 0, &background2Rect); // level background
	
	App->render->Blit(map2Text, 0, 0, &map2Rect); // level map


	return UPDATE_CONTINUE;
}