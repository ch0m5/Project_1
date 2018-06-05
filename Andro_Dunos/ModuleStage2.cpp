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
#include "ModuleShieldsP1.h"
#include "ModuleShieldsP2.h"

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

	if (App->shieldsP1->life > 0)
		App->shieldsP1->Enable();

	if (App->input->secondPlayerState == true) //@AndresSala
	{
		App->player2->Enable();

		if (App->shieldsP2->life > 0)
			App->shieldsP2->Enable();
	}

	loopNotPlaying = true;
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
	MusicLvl2_intro = App->mixer->LoadMusic("Assets/Audio/Music/13_Stage_6 -Secret-Base-Intro.ogg");
	MusicLvl2_loop = App->mixer->LoadMusic("Assets/Audio/Music/13_Stage_6-Secret-Base-Loop.ogg");
	Mix_FadeInMusic(MusicLvl2_intro, 0, 1000);
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
	/*App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 480, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 266, 121);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 300, 121);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 349, 121);
	App->enemies->AddEnemy(ENEMY_TYPES::DRILL_DOWN, 500, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::DRILL_UP, 520, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 540, 0);*/



	/*App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 400, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 410, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 420, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 430, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 440, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 450, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 460, 50);

	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 400, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 410, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 420, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 430, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 440, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 450, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 460, 60);*/

	//Torrent Down
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 270, 121);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 301, 121);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 338, 121);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 358, 121);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 401, 121);

	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 968, 118);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 1000, 118);

	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 3278, 67);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 3312, 67);

	//Torrent Up AQUI DEBERIA IR LAS UP TURRETS
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 253, 104);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 288, 104);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 323, 104);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 373, 104);

	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 481, 218);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 545, 218);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 584, 218);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 646, 218);

	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 944, 107);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 982, 107);

	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 3213, 158);
	App->enemies->AddEnemy(ENEMY_TYPES::DOWN_WHITEORANGETURRET, 3256, 158);

	//GreyYellow Enemy

	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 430, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 440, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 450, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 460, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 470, 30);


	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 430, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 440, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 450, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 460, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 470, 200);

	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 750, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 760, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 770, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 770, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 780, 140);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 780, 60);

	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 820, 65);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 835, 85);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 835, 45);

	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 860, 130);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 875, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 875, 150);

	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 2103, 46);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 2113, 46);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 2123, 46);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 2133, 46);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_DOWN, 2134, 46);

	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 2163, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 2173, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 2183, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 2193, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_UP, 2203, 200);

	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_DOWN, 2208, 64);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_DOWN, 2218, 64);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_DOWN, 2228, 64);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_DOWN, 2238, 64);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_RIGHT_DOWN, 2248, 64);

	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_UP, 2270, 46);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_UP, 2280, 46);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_UP, 2290, 46);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_UP, 2300, 46);
	App->enemies->AddEnemy(ENEMY_TYPES::YELLOWSHIP_UP, 2310, 46);

	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 2910, 60);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 2966, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 2989, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3022, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3070, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3090, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3133, 110);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3140, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3176, 90);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3197, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3224, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3256, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::GREY_YELLOW_SHIP, 3270, 90);

	//drill enemy
	App->enemies->AddEnemy(ENEMY_TYPES::DRILL_UP, 2392, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::DRILL_UP, 2567, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::DRILL_UP, 2825, 200);
	App->enemies->AddEnemy(ENEMY_TYPES::DRILL_DOWN, 2698, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::DRILL_DOWN, 2484, 0);

	//Greyball S
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 490, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 500, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 510, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 520, 40);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 530, 40);

	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 630, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 640, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 650, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 660, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_S, 670, 120);


	//greyball circle 
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1030, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1090, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1050, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1100, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1070, 0);

	//powerup
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_ENEMY, 1273, 50);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_ENEMY, 1899, 50);


	//greyball circle
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1300, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1350, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1320, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1370, 0);
	App->enemies->AddEnemy(ENEMY_TYPES::GREYBALL_CIRCLE, 1340, 0);


	//silver round
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 820, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 860, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 840, 180);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND, 880, 180);

	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 820, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 860, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 840, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::SILVER_ROUND_DOWN, 880, 30);

	//rock enemy
	App->enemies->AddEnemy(ENEMY_TYPES::ROCKSUBBOSS, 3903, 166);

	//Green sub enemy
	App->enemies->AddEnemy(ENEMY_TYPES::GREENSUBBOSS, 5744, 449);
	return ret;
}

bool ModuleStage2::CleanUp()
{
	// reset Background movement (position) values
	movementx = 0;
	movementxBack = 0;
	movementy = 0;

	//Reset Camera Position
	App->render->camera.x = 0;
	App->render->camera.y = 0;
	//Reset starting directions
	moveMapRight = true;
	moveMapDown = false;
	moveMapUp = false;

	loopNotPlaying = false;
	//--------
	LOG("Unloading players");

	App->player1->Disable();
	App->shieldsP1->Disable();

	if (App->input->secondPlayerState == true) //@AndresSala
	{
		App->player2->Disable();
		App->shieldsP2->Disable();
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
	App->mixer->UnloadMusic(MusicLvl2_intro);
	App->mixer->UnloadMusic(MusicLvl2_loop);
	return true;
}

//Function that will only be called when a song is finished (Will play th eloop after the intro)
void musicFinished()
{
	if (App->stage2->IsEnabled()==true)
	{
		Mix_PlayMusic(App->stage2->MusicLvl2_loop, -1);
	}
}

// Update: draw background
update_status ModuleStage2::Update()
{
	//If intro stops/ends play the loop
	if (loopNotPlaying == true)
	{
		Mix_HookMusicFinished(musicFinished);
		loopNotPlaying = false;
	}
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
	if (App->render->camera.x > 3790 * SCREEN_SIZE && App->render->camera.y < 411 * SCREEN_SIZE) // 1st SPEED CHANGE: Ships enter the inside of the Moon 
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
		App->UI->CompletedLevel = App->UI->Stage2;
		App->fade->FadeToBlack(this, App->stageClear, 1);
	}

	//make so pressing SPACE Scene HiScore is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && App->input->debugMode == true)
	{
		App->UI->CompletedLevel = App->UI->Stage2;
		App->fade->FadeToBlack(App->stage2, App->stageClear, 1);
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