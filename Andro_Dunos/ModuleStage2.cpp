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
	
	// More Ground Colliders @XaviMarin
	App->collision->AddCollider({ 935, 105, 94, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1400, 210, 856, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1458, 192, 113, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1503, 180, 53, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1593, 0, 508, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1936, 14, 114, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 1983, 34, 54, 7 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2100, 194, 112, 16 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2141, 181, 57, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2350, 215, 97, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2526, 215, 97, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2430, 0, 97, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2627, 0, 114, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2668, 14, 70, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2764, 215, 114, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 2810, 200, 70, 9 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3006, 198, 942, 29 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3035, 180, 51, 12 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3110, 180, 532, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3172, 158, 108, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3332, 158, 108, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3492, 158, 108, 20 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3825, 174, 108, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3863, 235, 103, 45 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3967, 245, 42, 98 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4010, 290, 19, 51 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4035, 340, 44, 75 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4077, 388, 18, 208 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4096, 435, 46, 161 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4144, 527, 58, 68 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4204, 580, 19, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4185, 602, 39, 34 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4225, 626, 42, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3063, 0, 535, 15 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3079, 16, 502, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3103, 29, 440, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3232, 46, 17, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3394, 46, 17, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3356, 45, 91, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3416, 45, 91, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3273, 58, 70, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 3435, 58, 70, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4425, 606, 181, 29 }, COLLIDER_WALL);

	App->collision->AddCollider({ 4555, 587, 30, 16 }, COLLIDER_WALL); //blue walls (orange rocks passed)
	App->collision->AddCollider({ 3273, 58, 70, 13 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4760, 585, 210, 51 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4730, 611, 26, 24 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4691, 625, 32, 10 }, COLLIDER_WALL);
	App->collision->AddCollider({ 4998, 601, 102, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5220, 610, 30, 26 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5285, 565, 58, 69 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5356, 583, 51, 41 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5429, 610, 103, 25 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5465, 585, 38, 23 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5540, 605, 98, 31 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5785, 593, 426, 42 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5945, 532, 25, 54 }, COLLIDER_WALL);
	App->collision->AddCollider({ 5994, 570, 37, 14 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6215, 600, 172, 36 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6475, 588, 144, 47 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6536, 565, 29, 22 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6684, 595, 144, 41 }, COLLIDER_WALL);
	App->collision->AddCollider({ 6830, 605, 152, 31 }, COLLIDER_WALL);


	//enemies
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 480, 50);


	

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
		
		movementy += ySpeedMultiplier*0.45f;
	

		App->render->camera.y = 3*movementy/3;  //Must change this HARDCODE to 1 single value

	}
	if (moveMapUp == true)
	{
		movementy -= ySpeedMultiplier * 0.82f;
		App->render->camera.y = 3.25*movementy / 3;  //Must change this HARDCODE to 1 single value
	}

	//Conditions: Where does the background change X and Y speeds
	if (App->render->camera.x > 3750 * SCREEN_SIZE && App->render->camera.y < 411 * SCREEN_SIZE) // 1st SPEED CHANGE: Ships enter the inside of the Moon 
	{
		ySpeedMultiplier = 2;
		xSpeedMultiplier = 1;
		moveMapRight = true;
		moveMapDown = true;
		moveMapUp = false;
	}

	else if (App->render->camera.y > 411 * SCREEN_SIZE /*&& App->render->camera.y > 4279 * SCREEN_SIZE*/ && moveMapUp == false) // 2nd SPEED CHANGE: Ships continue through the inside of the Moon
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