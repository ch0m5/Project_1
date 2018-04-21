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
#include "ModuleEnemies.h"
#include "ModuleHiScore.h"
#include "ModuleStageClear.h"
#include "ModuleParticles.h"

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

	// redPlanetRect
	redPlanetRect.x = 0;
	redPlanetRect.y = 0;
	redPlanetRect.w = 65;
	redPlanetRect.h = 65;

	// caveBackRect
	caveBackRect.x = 0;
	caveBackRect.y = 0;
	caveBackRect.w = 4509;
	caveBackRect.h = 489;
	
	// starBlue4Rect
	starBlue4Rect.x = 5;
	starBlue4Rect.y = 18;
	starBlue4Rect.w = 3;
	starBlue4Rect.h = 3;

	//starRed1Rect
	starRed1Rect.x = 5;
	starRed1Rect.y = 3;
	starRed1Rect.w = 3;
	starRed1Rect.h = 3;

	//starWhite2Rect
	starWhite2Rect.x = 5;
	starWhite2Rect.y = 8;
	starWhite2Rect.w = 3;
	starWhite2Rect.h = 3;

	//starWhite8Rect
	starWhite8Rect.x = 21;
	starWhite8Rect.y = 34;
	starWhite8Rect.w = 1;
	starWhite8Rect.h = 1;

	//starGreen3rect
	starGreen3Rect.x = 5;
	starGreen3Rect.y = 13;
	starGreen3Rect.w = 3;
	starGreen3Rect.h = 3;

	//starOrange5Rect
	starOrange5Rect.x = 6;
	starOrange5Rect.y = 23;
	starOrange5Rect.w = 1;
	starOrange5Rect.h = 1;
}

ModuleStage1::~ModuleStage1()
{}

// Load assets
bool ModuleStage1::Start()
{
	LOG("Loading background assets");	// Temporal, must decide if we load a full image,
 	bool ret = true;					// a single enormous tileset, maybe a tile array for the background

	background1Text = App->textures->Load("Assets/Sprites/Levels/STAGE 1/Tileset/Background/1_Background1.png");
	bluePlanetText = App->textures->Load("Assets/Sprites/Levels/STAGE 1/Tileset/Background/Moon.png");
 	map1Text = App->textures->Load("Assets/Sprites/Levels/STAGE 1/Tileset/Background/FullMap1_1.png");
	caveBackText = App->textures->Load("Assets/Sprites/Levels/STAGE 1/Tileset/Background/cave_background.png");
	redPlanetText = App->textures->Load("Assets/Sprites/Levels/STAGE 1/Tileset/Background/mars.png");
	starsText = App->textures->Load("Assets/Sprites/Levels/STAGE 1/Tileset/Background/Stars.png");


	App->player1->Enable();
	if (App->input->secondPlayerState == true)  //@AndresSala
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

	// First Enemy: GreyBall (4 waves, with 1wave&3wave same position.y and 2wave&4wave same position.y)
	//wave 1 ------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 480, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 495, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 510, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 525, 50);
	
	//wave 2 ------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 480 + 120, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 495 + 120, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 510 + 120, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 525 + 120, 130);
	
	//wave 3 ------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 480 + 270, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 495 + 270, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 510 + 270, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 525 + 270, 50);

	//wave 4 ------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 480 + 370, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 495 + 370, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 510 + 370, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_UP_DOWN, 525 + 370, 130);

	//Powerup------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_ENEMY, 950, 75); // must deliver a powerup particle
	
	// Second Enemy: GreyYellowShip (Several waves, no symetry between them)
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1200, 30); // X axis +20 & Y axis -20
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1180, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1200, 70);

	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1280, 110); // X axis +20 & Y axis +20
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1260, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1280, 150);
	
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1360, 30); // X axis +20 & Y axis -20
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1340, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1360, 70);

	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1460, 60); // X axis -10 & Y axis +20
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1450, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1440, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1425, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1450, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1460, 140);
	
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1540, 70); // X axis +15 & Y axis -15
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1555, 55);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1570, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1650, 110); // X axis +15 & Y axis +15
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1665, 125);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 1680, 140);
	/*
	App->enemies->AddEnemy(ENEMY_TYPES::REDLINE_SHIP, 720, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::REDLINE_SHIP, 760, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDLINE_SHIP, 800, 65);
	App->enemies->AddEnemy(ENEMY_TYPES::REDLINE_SHIP, 840, 100);
	*/

	//wave 5 ------------------------------------------------------
	/*
	App->enemies->AddEnemy(ENEMY_TYPES::BIGGREY_ENEMY, 1200, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::BIGGREY_ENEMY, 1230, 105);
	App->enemies->AddEnemy(ENEMY_TYPES::BIGGREY_ENEMY, 1260, 135);
	App->enemies->AddEnemy(ENEMY_TYPES::BIGGREY_ENEMY, 1290, 80);

	//wave 6 ------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPES::BIGGREY_ENEMY, 1200 + 300, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::BIGGREY_ENEMY, 1230 + 300, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::BIGGREY_ENEMY, 1260 + 300, 75);
	App->enemies->AddEnemy(ENEMY_TYPES::BIGGREY_ENEMY, 1290 + 300, 130);
	*/
   


	// Ground Collider @Andres&Didac
	App->collision->AddCollider({ 0, 195, 3000, 275 }, COLLIDER_WALL);  // Moon ground collider 
	App->collision->AddCollider({ 906,180, 100, 45 }, COLLIDER_WALL);  // crater 1
	App->collision->AddCollider({ 1565, 187, 99, 40 }, COLLIDER_WALL);  // crater 2
	App->collision->AddCollider({ 2363, 185, 103, 41 }, COLLIDER_WALL);  // crater 3
	App->collision->AddCollider({ 2605, 180, 97, 46 }, COLLIDER_WALL);  // crater 4
	App->collision->AddCollider({ 3203, 180, 54, 109 }, COLLIDER_WALL);  // crater 5 cave
	App->collision->AddCollider({ 2999, 400, 53, 53 }, COLLIDER_WALL);  // cave wall
	// -------------------------------------------------------------
	App->collision->AddCollider({ 3203, 257, 50, 43 }, COLLIDER_WALL);  // cave *
	App->collision->AddCollider({ 3248, 226, 817, 20 }, COLLIDER_WALL);  // roof *
	App->collision->AddCollider({ 3248, 245, 177, 17 }, COLLIDER_WALL);  // roof details *
	App->collision->AddCollider({ 3248, 262, 98, 7 }, COLLIDER_WALL);  // roof details *
	 // -------------------------------------------------------------
	App->collision->AddCollider({ 3894, 417, 66, 33 }, COLLIDER_WALL);  // floor details *
	// --------------------------------------------------------------
	App->collision->AddCollider({ 3052, 430, 1030, 50 }, COLLIDER_WALL);  // Cave ground Collider
	// --------------------------------------------------------------
	App->collision->AddCollider({ 4074, 163, 55, 33 }, COLLIDER_WALL);  // roof stairs up *
	App->collision->AddCollider({ 4129, 133, 26, 32 }, COLLIDER_WALL);  // roof stairs up *
	App->collision->AddCollider({ 4155, 113, 30, 21 }, COLLIDER_WALL);  // roof stairs up *
	App->collision->AddCollider({ 4185, 80, 696, 35 }, COLLIDER_WALL);  // roof flat *
	// ---------------------------------------------------------------
	App->collision->AddCollider({ 4074, 418, 55, 33 }, COLLIDER_WALL);  // floor stairs up *
	App->collision->AddCollider({ 4028, 194, 46, 33 }, COLLIDER_WALL);  // roof stairs up *
	App->collision->AddCollider({ 4113, 387, 43, 33 }, COLLIDER_WALL);  // floor stairs up *
	App->collision->AddCollider({ 4138, 357, 49, 33 }, COLLIDER_WALL);  // floor stairs up *
	App->collision->AddCollider({ 4185, 325, 434, 33 }, COLLIDER_WALL);  // floor stairs up *
	App->collision->AddCollider({ 4203, 310, 402, 18 }, COLLIDER_WALL);  // floor stairs up *
	// ---------------------------------------------------------------
	App->collision->AddCollider({ 4620, 356, 54, 65 }, COLLIDER_WALL);  // floor stair down *
	App->collision->AddCollider({ 4674, 388, 27, 42 }, COLLIDER_WALL);  // floor stair down *
	App->collision->AddCollider({ 4701, 419, 29, 31 }, COLLIDER_WALL);  // floor stair down *
	App->collision->AddCollider({ 4730, 429, 491, 20 }, COLLIDER_WALL);  // floor falt  *
	 // ---------------------------------------------------------------
	App->collision->AddCollider({ 5220, 419, 29, 31 }, COLLIDER_WALL);  // floor stair up *
	App->collision->AddCollider({ 5220, 419, 29, 31 }, COLLIDER_WALL);  // floor stair up *
	App->collision->AddCollider({ 5249, 388, 27, 31 }, COLLIDER_WALL);  // floor stair up *
	App->collision->AddCollider({ 5275, 355, 50, 38 }, COLLIDER_WALL);  // floor stair up *
	App->collision->AddCollider({ 5324, 307, 34, 52 }, COLLIDER_WALL);  // floor stair up *
	App->collision->AddCollider({ 5358, 276, 31, 37 }, COLLIDER_WALL);  // floor stair up *
	App->collision->AddCollider({ 5389, 245, 52, 36 }, COLLIDER_WALL);  // floor stair up *
	// ----------------------------------------------------------------
	App->collision->AddCollider({ 5440, 212, 781, 41 }, COLLIDER_WALL);  // floor falt *
	// ----------------------------------------------------------------
	App->collision->AddCollider({ 6221, 243, 53, 38 }, COLLIDER_WALL);  // floor stairs down *
	App->collision->AddCollider({ 6273, 274, 29, 33 }, COLLIDER_WALL);  // floor stairs down *
	App->collision->AddCollider({ 6302, 308, 34, 55 }, COLLIDER_WALL);  // floor stairs down *
	App->collision->AddCollider({ 6336, 357, 50, 40 }, COLLIDER_WALL);  // floor stairs down *
	App->collision->AddCollider({ 6385, 389, 27, 47 }, COLLIDER_WALL);  // floor stairs down *
	App->collision->AddCollider({ 6413, 421, 53, 38 }, COLLIDER_WALL);  // floor stairs down *
	App->collision->AddCollider({ 6440, 437, 1015, 13 }, COLLIDER_WALL);  // floor flat *
	// ----------------------------------------------------------------
	App->collision->AddCollider({ 6208, -57, 29, 16 }, COLLIDER_WALL);  // roof stairs down *
	App->collision->AddCollider({ 6236, -46, 47, 47 }, COLLIDER_WALL);  // roof stairs down *
	App->collision->AddCollider({ 6285, -8, 33, 43 }, COLLIDER_WALL);  // roof stairs down *
	App->collision->AddCollider({ 6317, 36, 28, 34 }, COLLIDER_WALL);  // roof stairs down *
	App->collision->AddCollider({ 6345, 70, 52, 31 }, COLLIDER_WALL);  // roof stairs down *
	App->collision->AddCollider({ 6397, 100, 35, 50 }, COLLIDER_WALL);  // roof stairs down *
	App->collision->AddCollider({ 6317, 36, 28, 34 }, COLLIDER_WALL);  // roof stairs down *
	// ----------------------------------------------------------------
	App->collision->AddCollider({ 6432, 149, 30, 33 }, COLLIDER_WALL);  // roof stairs down *
	App->collision->AddCollider({ 6462, 180, 50, 33 }, COLLIDER_WALL);  // roof stairs down *
	App->collision->AddCollider({ 6511, 210, 693, 31 }, COLLIDER_WALL);  // roof flat  *
// ----------------------------------------------------------------
	App->collision->AddCollider({ 7011, 226, 195, 34 }, COLLIDER_WALL);  // roof flat detail *
// ----------------------------------------------------------------
	App->collision->AddCollider({ 7360, 400, 48, 51 }, COLLIDER_WALL);  // floor flat detail *
	// ----------------------------------------------------------------
	App->collision->AddCollider({ 7156, 172, 51, 120  }, COLLIDER_WALL);  // out of crater left  *
	App->collision->AddCollider({ 7408, 189, 46, 260 }, COLLIDER_WALL);  // out of crater right  *
	// ----------------------------------------------------------------
	App->collision->AddCollider({ 7408, 197, 1897, 45 }, COLLIDER_WALL);  // moon surface 2*
	App->collision->AddCollider({ 7785, 188, 99, 45 }, COLLIDER_WALL);  // moon surface 2 crater 1*
	App->collision->AddCollider({ 8409, 188, 99, 45 }, COLLIDER_WALL);  // moon surface 2 crater 2 * 
	App->collision->AddCollider({ 8651, 183, 99, 45 }, COLLIDER_WALL);  // moon surface 2 crater 3*
	// ----------------------------------------------------------------
	//App->collision->AddCollider({ 300, 20, 87, 282 }, COLLIDER_WALL);		// Giant wall to test bullets

	//Music
	MusicLvl1 = App->mixer->LoadMusic("Assets/Audio/Music/04_Stage_1-The Moon-Loop.ogg");
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
	 //STars X axis
	 movementXBlueStar = 420;
	 movementXRedStar = 320;
	 movementXWhiteStar = 320;
	 movementXWhite8Star = 370;
	 movementXGreen3Star = 470;
	 movementXWhite8StarBack1 = 320;
	 movementXWhite8StarBack2 = 400;
	 movementXWhite8StarBack3 = 420;
	 movementXOrange5Star1 = 400;
	 movementXOrange5Star2 = 450;
	//Y Axis
	 movementy = 0;
	 movementyBack = 0;
	 //Reset Camera Position
	 App->render->camera.x = 0;
	 App->render->camera.y = 0;
	 //Reset starting directions
	 moveMapRight = true;
	 moveMapDown = false;
	 moveMapUp = false;

	 //----------------

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
	App->textures->Unload(caveBackText);
	App->textures->Unload(redPlanetText);
	App->textures->Unload(starsText);

	LOG("Unloading enemies");
	App->enemies->Disable();

	LOG("Unloading colliders")
	App->collision->Disable();

	LOG("Unloading particles")
	App->particles->Disable();

	Mix_FadeOutMusic(TIMEFADE);
	App->mixer->UnloadMusic(MusicLvl1);

	

	return true;
}

// Update: draw background
update_status ModuleStage1::Update()
{
	//Level 1 Map movement Code
	
	if (moveMapRight == true)
	{
		movementx += xSpeedMultiplier*0.83f; // for movement in x direction
		//LOG("%0.3f", movementx);
		movementxBack += xSpeedMultiplier*0.5f ;
		movementxPlanetsBack += xSpeedMultiplier*0.7f;
		
		App->render->camera.x = 3.25*movementx;

		//fast movement testing 
		//movementx -= xSpeedMultiplier*0.83f*2; // for movement in x direction
		//movementxBack += xSpeedMultiplier*0.5f*2;
		//movementxPlanetsBack += xSpeedMultiplier*0.7f*2;
		//App->render->camera.x = 3.25*movementx*2;
	
	}
	if (moveMapDown == true)
	{
		movementy += ySpeedMultiplier * 0.82f;
		movementyBack += ySpeedMultiplier * 0.38f; 
		App->render->camera.y = 3.25*movementy;
		
	}
	if (moveMapUp == true)
	{
		movementy -= ySpeedMultiplier * 0.82f;
		movementyBack -= ySpeedMultiplier * 0.38f;
		App->render->camera.y = 3.25*movementy;
	}

	//Conditions: Where does the background change X and Y speeds
	if (App->render->camera.x > 2920* SCREEN_SIZE) // 1st SPEED CHANGE: Ships enter the inside of the Moon 
	{
		moveMapRight = false;
		moveMapDown = true;
		moveMapUp = false;
	}
	
	if (App->render->camera.y > 226* SCREEN_SIZE && moveMapUp == false) // 2nd SPEED CHANGE: Ships continue through the inside of the Moon
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	
	if (App->render->camera.x > 4015* SCREEN_SIZE) // 3rd SPEED CHANGE: Ships continue through the inside of the Moon:: Diagonal Upwards movement 1/2
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = true;
		
	}
	if (App->render->camera.x > 4145* SCREEN_SIZE) // 4th SPEED CHANGE: Ships continue through the inside of the Moon:: now straight to Right 1/4
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
		
	}
	if (App->render->camera.x > 4530* SCREEN_SIZE) // 5th SPEED CHANGE: Ships continue through the inside of the Moon:: Diagonal Downwards to Right 1/2
	{
		
		moveMapRight = true;
		moveMapDown = true;
		moveMapUp = false;
	}
	if (App->render->camera.x > 4658* SCREEN_SIZE) // 6th SPEED CHANGE: Ships continue through the inside of the Moon:: now Straight to Right 2/4
	{
	
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	if (App->render->camera.x > 5071* SCREEN_SIZE) // 7th SPEED CHANGE: Ships continue through the inside of the Moon:: Diagonal Upwards to Right 2/2
	{
	
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = true;
	}
	if (App->render->camera.x > 5300* SCREEN_SIZE) // 8th SPEED CHANGE: Ships continue through the inside of the Moon:: Straight to Right 3/4
	{
		
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	if (App->render->camera.x > 6044* SCREEN_SIZE) // 9th SPEED CHANGE: Ships continue through the inside of the Moon:: Downwards to Right 2/2
	{
		
		ySpeedMultiplier = 0.65;
		moveMapRight = true;
		moveMapDown = true;
		moveMapUp = false;
	}
	if (App->render->camera.x > 6390* SCREEN_SIZE) // 10th SPEED CHANGE: Ships continue through the inside of the Moon:: Straight to Right 4/4
	{
	
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	if (App->render->camera.x > 7135* SCREEN_SIZE) // 11th SPEED CHANGE: Ships EXIT the inside of the Moon
	{
		ySpeedMultiplier = 1;
		moveMapRight = false;
		moveMapDown = false;
		moveMapUp = true;
	}

	if (App->render->camera.y < 0 && moveMapUp == true && App->render->camera.x > 7120* SCREEN_SIZE) // 12th SPEED CHANGE: Ships are OUTSIDE the Moon. They leave to the right
	{
		moveMapRight = true;
		moveMapDown = false;
		moveMapUp = false;
	}
	// Win Condition
	if (App->render->camera.x / SCREEN_SIZE > 8912)
	{
		App->fade->FadeToBlack(this, App->stageClear, 1);
	}

	//make so pressing SPACE the other stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(App->stage1, App->scene_HiScore, 1);
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

		if (fasterX == true )
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
	//BLIT STARS This code it's not clean and we must make it work as particles, but we mut do it after fixing all problems there
	if (moveMapRight == true)
	{
		if (movementXBlueStar * SCREEN_SIZE > App->render->camera.x)
		{
			movementXBlueStar -= 1;
			//Blit the Blue Star
			App->render->Blit(starsText, movementXBlueStar, 100, &starBlue4Rect);
		}
		else
		{
			movementXBlueStar += SCREEN_WIDTH;
		}
		if (movementXRedStar * SCREEN_SIZE > App->render->camera.x)
		{
			movementXRedStar -= 1;
			//Blit the Red Star
			App->render->Blit(starsText, movementXRedStar, 30, &starRed1Rect);
		}
		else
		{
			movementXRedStar += SCREEN_WIDTH;
		}

		if (movementXWhiteStar * SCREEN_SIZE > App->render->camera.x)
		{
			movementXWhiteStar -= 0.15f;
			//Blit the White Star
			App->render->Blit(starsText, movementXWhiteStar, 40, &starWhite2Rect);
		}
		else
		{
			movementXWhiteStar += SCREEN_WIDTH;
		}

		if (movementXWhite8Star * SCREEN_SIZE > App->render->camera.x)
		{
			movementXWhite8Star -= 0.15f;
			//Blit the White Star
			App->render->Blit(starsText, movementXWhite8Star, 95, &starWhite8Rect);
		}
		else
		{
			movementXWhite8Star += SCREEN_WIDTH;
		}

		if (movementXWhite8StarBack1 * SCREEN_SIZE > App->render->camera.x)
		{
			movementXWhite8StarBack1 += 0.20f;
			//Blit the White Star
			App->render->Blit(starsText, movementXWhite8StarBack1, 70, &starWhite8Rect);
		}
		else
		{
			movementXWhite8StarBack1 += SCREEN_WIDTH;
		}

		if (movementXWhite8StarBack2 * SCREEN_SIZE > App->render->camera.x)
		{
			movementXWhite8StarBack2 += 0.20f;
			//Blit the White Star
			App->render->Blit(starsText, movementXWhite8StarBack2, 50, &starWhite8Rect);
		}
		else
		{
			movementXWhite8StarBack2 += SCREEN_WIDTH;
		}

		if (movementXWhite8StarBack3 * SCREEN_SIZE > App->render->camera.x)
		{
			movementXWhite8StarBack3 += 0.20f;
			//Blit the White Star
			App->render->Blit(starsText, movementXWhite8StarBack3, 60, &starWhite8Rect);
		}
		else
		{
			movementXWhite8StarBack3 += SCREEN_WIDTH;
		}

		if (movementXOrange5Star1 * SCREEN_SIZE > App->render->camera.x)
		{
			movementXOrange5Star1 -= 0.10f;
			//Blit the White Star
			App->render->Blit(starsText, movementXOrange5Star1, 70, &starOrange5Rect);
		}
		else
		{
			movementXOrange5Star1 += SCREEN_WIDTH;
		}

		if (movementXOrange5Star2 * SCREEN_SIZE > App->render->camera.x)
		{
			movementXOrange5Star2 -= 0.30f;
			//Blit the White Star
			App->render->Blit(starsText, movementXOrange5Star2, 40, &starOrange5Rect);
		}
		else
		{
			movementXOrange5Star2 += SCREEN_WIDTH;
		}

		if (movementXGreen3Star * SCREEN_SIZE > App->render->camera.x)
		{
			movementXGreen3Star += 0.20f;
			//Blit the White Star
			App->render->Blit(starsText, movementXGreen3Star, 97, &starGreen3Rect);
		}
		else
		{
			movementXGreen3Star += SCREEN_WIDTH;
		}
	}
	else
	{
		App->render->Blit(starsText, movementXBlueStar, 100, &starBlue4Rect);
		App->render->Blit(starsText, movementXRedStar, 30, &starRed1Rect);
		App->render->Blit(starsText, movementXWhiteStar, 40, &starWhite2Rect);
		App->render->Blit(starsText, movementXWhite8Star, 95, &starWhite8Rect);
		App->render->Blit(starsText, movementXWhite8StarBack2, 50, &starWhite8Rect);
		App->render->Blit(starsText, movementXWhite8StarBack3, 60, &starWhite8Rect);
		App->render->Blit(starsText, movementXOrange5Star1, 70, &starOrange5Rect);
		App->render->Blit(starsText, movementXOrange5Star2, 40, &starOrange5Rect);
		App->render->Blit(starsText, movementXGreen3Star, 97, &starGreen3Rect);
	}
																			//These two if's control the first part of the level outside and the end of the level also outside
	if (App->render->camera.y < 180 * SCREEN_SIZE)
	{
		App->render->Blit(background1Text, movementxBack, 120 + movementyBack, &background1Rect); // level background

	}
	if (App->render->camera.x > 7130 * SCREEN_SIZE && App->render->camera.x < 7131 * SCREEN_SIZE)
	{
		movementxBack = 0;
		movementxPlanetsBack = 0;
	}
	if (App->render->camera.x > 7130 * SCREEN_SIZE && App->render->camera.y < 180 * SCREEN_SIZE)
	{
		App->render->Blit(redPlanetText, 7450 + movementxPlanetsBack, 40, &redPlanetRect); // Mars
		App->render->Blit(background1Text, 7130 + movementxBack, 120 + movementyBack, &background1Rect); // level background
	}
	App->render->Blit(caveBackText, backmovementcaveX, -40, &caveBackRect); // cave background

	App->render->Blit(map1Text, 0, -55, &map1Rect); // level map

	App->render->Blit(bluePlanetText, 500 + movementxPlanetsBack, -10, &bluePlanetRect); // Moon 

	return UPDATE_CONTINUE;

}