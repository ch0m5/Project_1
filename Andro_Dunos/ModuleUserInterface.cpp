#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMainMenu.h"
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
#include "ModuleUserInterface.h"
#include "ModuleFont.h"
#include "ModuleStageClear.h"
#include "ModuleParticles.h"
#include <stdio.h>
ModuleUserInterface::ModuleUserInterface()	//@DídacRomero
{
	
	// Beam Pushbacks P1
	p1BeamIdle.PushBack({ 29, 28, 64, 6 });

	p1BeamCharged.PushBack({ 165, 96, 64, 7 });
	p1BeamCharged.PushBack({ 165, 107, 64, 7 });
	p1BeamCharged.PushBack({ 165, 116, 64, 7 });
	p1BeamCharged.PushBack({ 165, 126, 64, 7 });
	p1BeamCharged.loop = true;
	p1BeamCharged.speed = 0.5f;

	p1BeamCharging.PushBack({ 29, 28, 64, 6 });
	p1BeamCharging.PushBack({ 29, 35, 64, 6 });
	p1BeamCharging.PushBack({ 29, 42, 64, 6 });
	p1BeamCharging.PushBack({ 29, 49, 64, 6 });
	p1BeamCharging.PushBack({ 29, 56, 64, 6 });
	p1BeamCharging.PushBack({ 29, 63, 64, 6 });
	p1BeamCharging.PushBack({ 29, 70, 64, 6 });
	p1BeamCharging.PushBack({ 29, 77, 64, 6 });
	p1BeamCharging.PushBack({ 29, 84, 64, 6 });
	p1BeamCharging.PushBack({ 29, 91, 64, 6 });
	p1BeamCharging.PushBack({ 29, 98, 64, 6 });
	p1BeamCharging.PushBack({ 29, 105, 64, 6 });
	p1BeamCharging.PushBack({ 29, 112, 64, 6 });
	p1BeamCharging.PushBack({ 29, 119, 64, 6 });
	p1BeamCharging.PushBack({ 29, 126, 64, 6 });
	p1BeamCharging.PushBack({ 29, 133, 64, 6 });
	p1BeamCharging.PushBack({ 29, 140, 64, 6 });
	p1BeamCharging.PushBack({ 29, 147, 64, 6 });
	p1BeamCharging.PushBack({ 29, 154, 64, 6 });
	p1BeamCharging.PushBack({ 29, 161, 64, 6 });
	p1BeamCharging.PushBack({ 29, 168, 64, 6 });
	p1BeamCharging.PushBack({ 29, 175, 64, 6 });
	p1BeamCharging.PushBack({ 29, 182, 64, 6 });
	p1BeamCharging.PushBack({ 29, 189, 64, 6 });
	p1BeamCharging.PushBack({ 29, 196, 64, 6 });
	p1BeamCharging.PushBack({ 29, 203, 64, 6 });
	p1BeamCharging.PushBack({ 29, 210, 64, 6 });
	p1BeamCharging.PushBack({ 29, 217, 64, 6 });
	p1BeamCharging.PushBack({ 29, 224, 64, 6 });
	p1BeamCharging.PushBack({ 97, 29, 64, 6 });		//Point of inflection bar clipping
	p1BeamCharging.PushBack({ 97, 36, 64, 6 });
	p1BeamCharging.PushBack({ 97, 43, 64, 6 });
	p1BeamCharging.PushBack({ 97, 50, 64, 6 });
	p1BeamCharging.PushBack({ 97, 57, 64, 6 });
	p1BeamCharging.PushBack({ 97, 64, 64, 6 });
	p1BeamCharging.PushBack({ 97, 71, 64, 6 });
	p1BeamCharging.PushBack({ 97, 78, 64, 6 });
	p1BeamCharging.PushBack({ 97, 85, 64, 6 });
	p1BeamCharging.PushBack({ 97, 92, 64, 6 });
	p1BeamCharging.PushBack({ 97, 99, 64, 6 });
	p1BeamCharging.PushBack({ 97, 106, 64, 6 });
	p1BeamCharging.PushBack({ 97, 113, 64, 6 });
	p1BeamCharging.PushBack({ 97, 120, 64, 6 });
	p1BeamCharging.PushBack({ 97, 127, 64, 6 });
	p1BeamCharging.PushBack({ 97, 134, 64, 6 });
	p1BeamCharging.PushBack({ 97, 141, 64, 6 });
	p1BeamCharging.PushBack({ 97, 148, 64, 6 });
	p1BeamCharging.PushBack({ 97, 155, 64, 6 });
	p1BeamCharging.PushBack({ 97, 162, 64, 6 });
	p1BeamCharging.PushBack({ 97, 169, 64, 6 });
	p1BeamCharging.PushBack({ 97, 176, 64, 6 });
	p1BeamCharging.PushBack({ 97, 183, 64, 6 });
	p1BeamCharging.PushBack({ 97, 190, 64, 6 });
	p1BeamCharging.PushBack({ 97, 197, 64, 6 });
	p1BeamCharging.PushBack({ 97, 204, 64, 6 });
	p1BeamCharging.PushBack({ 97, 211, 64, 6 });
	p1BeamCharging.PushBack({ 165, 29, 64, 6 });	//Point of inflection
	p1BeamCharging.PushBack({ 165, 36, 64, 6 });
	p1BeamCharging.PushBack({ 165, 43, 64, 6 });
	p1BeamCharging.PushBack({ 165, 50, 64, 6 });
	p1BeamCharging.PushBack({ 165, 57, 64, 6 });
	p1BeamCharging.PushBack({ 165, 64, 64, 6 });
	p1BeamCharging.PushBack({ 165, 74, 64, 6 }); //All good until here
	p1BeamCharging.PushBack({ 165, 82, 64, 7 });
	p1BeamCharging.PushBack({ 165, 88, 64, 7 });


	p1BeamCharging.loop = false;
	p1BeamCharging.speed = 0.5f;

	// Beam Pushbacks P2
	p2BeamIdle.PushBack({ 29, 28, 64, 6 });

	p2BeamCharged.PushBack({ 165, 96, 64, 7 });
	p2BeamCharged.PushBack({ 165, 107, 64, 7 });
	p2BeamCharged.PushBack({ 165, 116, 64, 7 });
	p2BeamCharged.PushBack({ 165, 126, 64, 7 });
	p2BeamCharged.loop = true;
	p2BeamCharged.speed = 0.5f;

	p2BeamCharging.PushBack({ 29, 28, 64, 6 });
	p2BeamCharging.PushBack({ 29, 35, 64, 6 });
	p2BeamCharging.PushBack({ 29, 42, 64, 6 });
	p2BeamCharging.PushBack({ 29, 49, 64, 6 });
	p2BeamCharging.PushBack({ 29, 56, 64, 6 });
	p2BeamCharging.PushBack({ 29, 63, 64, 6 });
	p2BeamCharging.PushBack({ 29, 70, 64, 6 });
	p2BeamCharging.PushBack({ 29, 77, 64, 6 });
	p2BeamCharging.PushBack({ 29, 84, 64, 6 });
	p2BeamCharging.PushBack({ 29, 91, 64, 6 });
	p2BeamCharging.PushBack({ 29, 98, 64, 6 });
	p2BeamCharging.PushBack({ 29, 105, 64, 6 });
	p2BeamCharging.PushBack({ 29, 112, 64, 6 });
	p2BeamCharging.PushBack({ 29, 119, 64, 6 });
	p2BeamCharging.PushBack({ 29, 126, 64, 6 });
	p2BeamCharging.PushBack({ 29, 133, 64, 6 });
	p2BeamCharging.PushBack({ 29, 140, 64, 6 });
	p2BeamCharging.PushBack({ 29, 147, 64, 6 });
	p2BeamCharging.PushBack({ 29, 154, 64, 6 });
	p2BeamCharging.PushBack({ 29, 161, 64, 6 });
	p2BeamCharging.PushBack({ 29, 168, 64, 6 });
	p2BeamCharging.PushBack({ 29, 175, 64, 6 });
	p2BeamCharging.PushBack({ 29, 182, 64, 6 });
	p2BeamCharging.PushBack({ 29, 189, 64, 6 });
	p2BeamCharging.PushBack({ 29, 196, 64, 6 });
	p2BeamCharging.PushBack({ 29, 203, 64, 6 });
	p2BeamCharging.PushBack({ 29, 210, 64, 6 });
	p2BeamCharging.PushBack({ 29, 217, 64, 6 });
	p2BeamCharging.PushBack({ 29, 224, 64, 6 });
	p2BeamCharging.PushBack({ 97, 29, 64, 6 });		//Point of inflection bar clipping
	p2BeamCharging.PushBack({ 97, 36, 64, 6 });
	p2BeamCharging.PushBack({ 97, 43, 64, 6 });
	p2BeamCharging.PushBack({ 97, 50, 64, 6 });
	p2BeamCharging.PushBack({ 97, 57, 64, 6 });
	p2BeamCharging.PushBack({ 97, 64, 64, 6 });
	p2BeamCharging.PushBack({ 97, 71, 64, 6 });
	p2BeamCharging.PushBack({ 97, 78, 64, 6 });
	p2BeamCharging.PushBack({ 97, 85, 64, 6 });
	p2BeamCharging.PushBack({ 97, 92, 64, 6 });
	p2BeamCharging.PushBack({ 97, 99, 64, 6 });
	p2BeamCharging.PushBack({ 97, 106, 64, 6 });
	p2BeamCharging.PushBack({ 97, 113, 64, 6 });
	p2BeamCharging.PushBack({ 97, 120, 64, 6 });
	p2BeamCharging.PushBack({ 97, 127, 64, 6 });
	p2BeamCharging.PushBack({ 97, 134, 64, 6 });
	p2BeamCharging.PushBack({ 97, 141, 64, 6 });
	p2BeamCharging.PushBack({ 97, 148, 64, 6 });
	p2BeamCharging.PushBack({ 97, 155, 64, 6 });
	p2BeamCharging.PushBack({ 97, 162, 64, 6 });
	p2BeamCharging.PushBack({ 97, 169, 64, 6 });
	p2BeamCharging.PushBack({ 97, 176, 64, 6 });
	p2BeamCharging.PushBack({ 97, 183, 64, 6 });
	p2BeamCharging.PushBack({ 97, 190, 64, 6 });
	p2BeamCharging.PushBack({ 97, 197, 64, 6 });
	p2BeamCharging.PushBack({ 97, 204, 64, 6 });
	p2BeamCharging.PushBack({ 97, 211, 64, 6 });
	p2BeamCharging.PushBack({ 165, 29, 64, 6 });	//Point of inflection
	p2BeamCharging.PushBack({ 165, 36, 64, 6 });
	p2BeamCharging.PushBack({ 165, 43, 64, 6 });
	p2BeamCharging.PushBack({ 165, 50, 64, 6 });
	p2BeamCharging.PushBack({ 165, 57, 64, 6 });
	p2BeamCharging.PushBack({ 165, 64, 64, 6 });
	p2BeamCharging.PushBack({ 165, 74, 64, 6 }); //All good until here
	p2BeamCharging.PushBack({ 165, 82, 64, 7 });
	p2BeamCharging.PushBack({ 165, 88, 64, 7 });


	p2BeamCharging.loop = false;
	p2BeamCharging.speed = 0.5f;
}

ModuleUserInterface::~ModuleUserInterface()
{}

// Load assets
bool ModuleUserInterface::Start()
{
	LOG("Loading User Interface");	
	bool ret = true;
	startTime = SDL_GetTicks();
	showPress1P = false;
	p1ShowType = false;
	p2ShowType = false;
	hiScore = 0;
	coins = 0;
	p1Dead = true;
	p2Dead = true;
	player1Score = 0;
	player2Score = 0;
	//Load fonts
	font_score = App->fonts->Load("Assets/Sprites/User_Interface/fonts/Font-score-white.png", "1234567890P", 1);
	font_yellowtxt = App->fonts->Load("Assets/Sprites/User_Interface/fonts/yellow_font.png", "0123456789abcdefghiklmnoprstuvy©        ", 4);
	debug_font= App->fonts->Load("Assets/Sprites/User_Interface/fonts/blue_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);
	powerUpFont = App->fonts->Load("Assets/Sprites/User_Interface/fonts/numbers_powerup.png", "012345678", 1);
	typeFont = App->fonts->Load("Assets/Sprites/User_Interface/fonts/type_font.png", "1234-type ", 2);
	hiScoreFont = App->fonts->Load("Assets/Sprites/User_Interface/fonts/red_font_high_score.png", "1234567890hi- ", 2);
	creditsFont = App->fonts->Load("Assets/Sprites/User_Interface/fonts/credits_font.png", "0123456789cdeirtscder         ", 3);
	//Load player boxes
	hudTex = App->textures->Load("Assets/Sprites/User_Interface/Grafical_Interface/hud_elements.png");
	beamTex = App->textures->Load("Assets/Sprites/User_Interface/Grafical_Interface/pritesheet-charge-beam.png");
	coinInserted = App->mixer->LoadFX("Assets/Audio/Sounds_FX/COIN_inserted.wav");
	//Setting up all the Rects
	blueBoxNormalRect = {1,13, 32, 7};
	blueBoxReverseRect = { 1,24, 32, 7 };
	blueBoxWayRect = { 1,35, 32, 7 };
	blueBoxLaserRect = { 1,47, 32, 7 };
	redBoxFintaelRect = {1,58, 32, 7 };
	redBoxHawkRect = { 1,69, 32, 7 };
	redBoxLaserRect = { 1,80, 32, 7 };
	redBoxNormalRect = { 1,92, 32, 7 };
	yellowBoxHomingRect = { 1,103, 32, 7 };
	greenBoxRollingRect = { 34,13, 32, 7 };
	greenBoxSideRect = { 34,24, 32, 7 };
	greenBoxRearRect = { 34,35, 32, 7 };
	greenBoxFrontRect = { 34,47, 32, 7 };
	//lives rects
	livesP1 = {2,2,7,7};
	livesP2 = {14,2,7,7};

	return ret;
}

// Unload assets
bool ModuleUserInterface::CleanUp()
{
	LOG("Unloading UI");
	//Unload Textures
	App->textures->Unload(hudTex);
	hudTex = nullptr;
	//Unload fonts
	App->fonts->UnLoad(font_score);
	App->fonts->UnLoad(font_yellowtxt);
	App->fonts->UnLoad(debug_font);
	App->fonts->UnLoad(powerUpFont);
	App->fonts->UnLoad(typeFont);
	App->fonts->UnLoad(hiScoreFont);
	App->textures->Unload(hudTex);
	App->textures->Unload(beamTex);
	App->mixer->UnloadFx(coinInserted);

	return true;
}

// Update: draw background
update_status ModuleUserInterface::Update()
{
	//Coins inserted code
	if (App->input->keyboard[SDL_SCANCODE_3] == KEY_DOWN)
	{
		Mix_PlayChannel(4,coinInserted,0);
		coins++;
		if (coins > 99) { coins = 99; }
		if (coins < 0) { coins = 0; }
	}
	//Determine which of the Stages we're currently in
	if (App->scene_HiScore->IsEnabled() == true)
	{
		CurrentStage = GameOver;
	}
	else if (App->mainMenu->IsEnabled() == true)
	{
		CurrentStage = MainMenu;
	}
	else if (App->stage1->IsEnabled() == true)
	{
		CurrentStage = Stage1;
	}
	else if (App->stage2->IsEnabled() == true)
	{
		CurrentStage = Stage2;
	}
	else if (App->stageClear->IsEnabled() == true)
	{
		CurrentStage = StageClear;
	}

	//Execute the logic and blits for each Scene
	switch (CurrentStage)
	{
		case MainMenu:
			{
			if (SDL_GetTicks() - startTime >= 750)
			{
				showPress1P = !showPress1P;
				startTime = SDL_GetTicks();
			}
			if (showPress1P == true)
			{
				App->fonts->BlitText(85, 140, font_yellowtxt, "press 1p start");
			}
			App->fonts->BlitText(40, 193, font_yellowtxt, "© 1992 visco corporation");
			App->fonts->BlitText(65, 202, font_yellowtxt, "all rights reserved");
			//Blit Coins
			App->fonts->BlitText(230, 210, creditsFont, "credit ");
			sprintf_s(coins_text, 10, "%7d", coins);
			if (coins < 10)
			{
				App->fonts->BlitText(280, 210, creditsFont, "0");
				App->fonts->BlitText(241, 210, creditsFont, coins_text);
			}
			else
			{
				App->fonts->BlitText(241, 210, creditsFont, coins_text);
			}
			player1Score = 0;
				player2Score = 0;
				teamScore = 0;
			}break;

		case Stage1:
		{
			if (p1Dead == true && p2Dead == true && coins < 1)
			{
				App->fade->FadeToBlack(App->stage1, App->scene_HiScore);
			}
			//Blit Coins
			App->fonts->BlitText(230, 210, creditsFont, "credit ");
			sprintf_s(coins_text, 10, "%7d", coins);
			if (coins < 10)
			{
				App->fonts->BlitText(280, 210, creditsFont, "0");
				App->fonts->BlitText(241, 210, creditsFont, coins_text);
			}
			else
			{
				App->fonts->BlitText(241, 210, creditsFont, coins_text);
			}
			//Calculate hiScore
			if (player1Score > hiScore) { hiScore = player1Score;}
			if (player2Score > hiScore) { hiScore = player2Score;}
			//Blit Hi Score
			App->fonts->BlitText(120, 10, hiScoreFont, "hi-");
			sprintf_s(hiScore_text, 10, "%7d", hiScore);
			App->fonts->BlitText(145, 10, hiScoreFont, hiScore_text);
			//Blit SCORE
			App->fonts->BlitText(10, 10, font_score, "1P");
			sprintf_s(player1Score_text, 10, "%7d", player1Score);
			App->fonts->BlitText(50, 10, 0, player1Score_text);


			//Blit P2 SCORE
			if (App->input->secondPlayerState == true)
			{
				App->fonts->BlitText(210, 10, font_score, "2P");
				sprintf_s(player2Score_text, 10, "%7d", player2Score);
				App->fonts->BlitText(250, 10, 0, player2Score_text);
			}

			//Blit P1 Charging Special Attack beam
			if (p1Dead == false)
			{
				if (App->player1->destroyed == false)
				{
					if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_REPEAT)
					{
						
						if (p1BeamCharging.Finished())
						{
							App->render->Blit(beamTex, 74, 27, &(p1BeamCharged.GetCurrentFrame()), 1, false);
						}
						else
						{
							App->render->Blit(beamTex, 74, 28, &(p1BeamCharging.GetCurrentFrame()), 1, false);
						}
						if (App->player1->bluePower < 2)
						{
							App->render->Blit(beamTex, 74, 28, &(p1BeamIdle.GetCurrentFrame()), 1, false);
						}
					}
					else
					{
						p1BeamCharging.Reset();
						p1BeamCharging.ResetLoops();
						App->render->Blit(beamTex, 74, 28, &(p1BeamIdle.GetCurrentFrame()), 1, false);
					}
				}
			}
			
			//Blit P2 Charging Special Attack beam
			if (p2Dead == false)
			{
				if (App->player2->destroyed == false)
				{
					if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_REPEAT)
					{

						if (p2BeamCharging.Finished())
						{
							App->render->Blit(beamTex, 249, 28, &(p2BeamCharged.GetCurrentFrame()), 1, false);
						}
						else
						{
							App->render->Blit(beamTex, 249, 28, &(p2BeamCharging.GetCurrentFrame()), 1, false);
						}
						if (App->player2->bluePower < 2)
						{
							App->render->Blit(beamTex, 249, 28, &(p2BeamIdle.GetCurrentFrame()), 1, false);
						}
					}
					else
					{
						p2BeamCharging.Reset();
						p2BeamCharging.ResetLoops();
						App->render->Blit(beamTex, 249, 28, &(p2BeamIdle.GetCurrentFrame()), 1, false);
					}
				}
			}

		//TYPE banner that doesn't let boxes to be seen
			if (App->input->keyboard[SDL_SCANCODE_O] == KEY_DOWN && p1Dead == false)
			{
				p1TypeSwapStartTime = SDL_GetTicks();
				p1ShowType = true;
			}
				
			
			if (p1ShowType == true)
			{
				if (SDL_GetTicks() - p1TypeSwapStartTime >= 300)
				{
					p1ShowType = false;
				}
				switch (App->player1->type)	// Shield position and particle maximum variation
				{
				case weapon_types::TYPE_1:
					App->fonts->BlitText(10, 20, typeFont, "type-1");
					break;
				case weapon_types::TYPE_2:
					App->fonts->BlitText(10, 20, typeFont, "type-2");
					break;
				case weapon_types::TYPE_3:
					App->fonts->BlitText(10, 20, typeFont, "type-3");
					break;
				case weapon_types::TYPE_4:
					App->fonts->BlitText(10, 20, typeFont, "type-4");
					break;
				};
			}
			else
			{
				//Blit Boxes (P1)
				if (App->player1->type == weapon_types::TYPE_1)
				{
					App->render->Blit(hudTex, 10, 20, &blueBoxNormalRect, false);
					App->render->Blit(hudTex, 42, 20, &redBoxFintaelRect, false);
					App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
					App->render->Blit(hudTex, 106, 20, &greenBoxRollingRect, false);
				}
				else if (App->player1->type == weapon_types::TYPE_2)
				{
					App->render->Blit(hudTex, 10, 20, &blueBoxReverseRect, false);
					App->render->Blit(hudTex, 42, 20, &redBoxHawkRect, false);
					App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
					App->render->Blit(hudTex, 106, 20, &greenBoxSideRect, false);
				}
				else if (App->player1->type == weapon_types::TYPE_3)
				{
					App->render->Blit(hudTex, 10, 20, &blueBoxWayRect, false);
					App->render->Blit(hudTex, 42, 20, &redBoxLaserRect, false);
					App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
					App->render->Blit(hudTex, 106, 20, &greenBoxRearRect, false);
				}
				else if (App->player1->type == weapon_types::TYPE_4)
				{
					App->render->Blit(hudTex, 10, 20, &blueBoxLaserRect, false);
					App->render->Blit(hudTex, 42, 20, &redBoxNormalRect, false);
					App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
					App->render->Blit(hudTex, 106, 20, &greenBoxFrontRect, false);
				}
			
				//Blit powerUp levels in the boxes
				if (p1Dead == false)
				{
					sprintf_s(p1BluePowerLevel, 10, "%7d", App->player1->bluePower);
					App->fonts->BlitText(12, 21, powerUpFont, p1BluePowerLevel);
					sprintf_s(p1OrangePowerLevel, 10, "%7d", App->player1->orangePower);
					App->fonts->BlitText(44, 21, powerUpFont, p1OrangePowerLevel);
					sprintf_s(p1YellowPowerLevel, 10, "%7d", App->player1->yellowPower);
					App->fonts->BlitText(76, 21, powerUpFont, p1YellowPowerLevel);
					sprintf_s(p1GreenPowerLevel, 10, "%7d", App->player1->greenPower);
					App->fonts->BlitText(108, 21, powerUpFont, p1GreenPowerLevel);
				}
			}

			//TYPE banner that doesn't let boxes to be seen P2
			if (App->input->keyboard[SDL_SCANCODE_B] == KEY_DOWN && p1Dead == false)
			{
				p2TypeSwapStartTime = SDL_GetTicks();
				p2ShowType = true;
			}


			if (p2ShowType == true)
			{
				if (SDL_GetTicks() - p2TypeSwapStartTime >= 300)
				{
					p2ShowType = false;
				}
				switch (App->player2->type)	// Shield position and particle maximum variation
				{
				case weapon_types::TYPE_1:
					App->fonts->BlitText(185, 20, typeFont, "type-1");
					break;
				case weapon_types::TYPE_2:
					App->fonts->BlitText(185, 20, typeFont, "type-2");
					break;
				case weapon_types::TYPE_3:
					App->fonts->BlitText(185, 20, typeFont, "type-3");
					break;
				case weapon_types::TYPE_4:
					App->fonts->BlitText(185, 20, typeFont, "type-4");
					break;
				};
			}
			else
			{
				//Blit Boxes (P2)
				if (App->player2->type == weapon_types::TYPE_1)
				{
					App->render->Blit(hudTex, 185, 20, &blueBoxNormalRect, false);
					App->render->Blit(hudTex, 217, 20, &redBoxFintaelRect, false);
					App->render->Blit(hudTex, 249, 20, &yellowBoxHomingRect, false);
					App->render->Blit(hudTex, 281, 20, &greenBoxRollingRect, false);
				}
				else if (App->player2->type == weapon_types::TYPE_2)
				{
					App->render->Blit(hudTex, 185, 20, &blueBoxReverseRect, false);
					App->render->Blit(hudTex, 217, 20, &redBoxHawkRect, false);
					App->render->Blit(hudTex, 249, 20, &yellowBoxHomingRect, false);
					App->render->Blit(hudTex, 281, 20, &greenBoxSideRect, false);
				}
				else if (App->player2->type == weapon_types::TYPE_3)
				{
					App->render->Blit(hudTex, 185, 20, &blueBoxWayRect, false);
					App->render->Blit(hudTex, 217, 20, &redBoxLaserRect, false);
					App->render->Blit(hudTex, 249, 20, &yellowBoxHomingRect, false);
					App->render->Blit(hudTex, 281, 20, &greenBoxRearRect, false);
				}
				else if (App->player2->type == weapon_types::TYPE_4)
				{
					App->render->Blit(hudTex, 185, 20, &blueBoxLaserRect, false);
					App->render->Blit(hudTex, 217, 20, &redBoxNormalRect, false);
					App->render->Blit(hudTex, 249, 20, &yellowBoxHomingRect, false);
					App->render->Blit(hudTex, 281, 20, &greenBoxFrontRect, false);
				}
				//Blit powerUp levels in the boxes
				if (p2Dead == false)
				{
					sprintf_s(p2BluePowerLevel, 10, "%7d", App->player2->bluePower);
					App->fonts->BlitText(187, 21, powerUpFont, p2BluePowerLevel);
					sprintf_s(p2OrangePowerLevel, 10, "%7d", App->player2->orangePower);
					App->fonts->BlitText(219, 21, powerUpFont, p2OrangePowerLevel);
					sprintf_s(p2YellowPowerLevel, 10, "%7d", App->player2->yellowPower);
					App->fonts->BlitText(243, 21, powerUpFont, p2OrangePowerLevel);
					sprintf_s(p2GreenPowerLevel, 10, "%7d", App->player2->greenPower);
					App->fonts->BlitText(283, 21, powerUpFont, p2GreenPowerLevel);
				}
			}
		
		//HUD Lives 1P
			if (p1Dead == false)
			{
				if (App->player1->lives == 2 || App->player1->lives == 3)
				{
					App->render->Blit(hudTex, 18, 28, &livesP1, false);
				}
				if (App->player1->lives == 3)
				{
					App->render->Blit(hudTex, 26, 28, &livesP1, false);
				}
			}
		//HUD Lives 2P
			if (p2Dead == false)
			{
				if (App->player2->lives == 2 || App->player2->lives == 3)
				{
					App->render->Blit(hudTex, 193, 28, &livesP2, false);
				}
				if (App->player2->lives == 3)
				{
					App->render->Blit(hudTex, 201, 28, &livesP2, false);
				}
			}
				//DEBUG mode
				if (App->input->debugMode == true)
				{
					App->fonts->BlitText(10, 40, debug_font, "debug mode");
				}
				if (App->player1->godMode == true && App->input->debugMode == true || App->player2->godMode == true && App->input->debugMode == true)
				{
					App->fonts->BlitText(10, 50, debug_font, "god mode");
				}
				if (App->input->coliderView == true && App->input->debugMode == true)
				{
					App->fonts->BlitText(10, 60, debug_font, "collider view");
				}
				if (App->stage1->fasterX == true && App->input->debugMode == true)
				{
					App->fonts->BlitText(10, 70, debug_font, "super speed");
				}
				//Controller Debug P1
      				if (App->input->debugMode == true && App->input->gamepadP1con == true)
				{
					App->fonts->BlitText(150, 50, debug_font, "p1 controller on");
					if (App->input->gamepadP1APressed == true)
					{
						App->fonts->BlitText(150, 60, debug_font, "a");
					}
					if (App->input->gamepadP1XPressed == true)
					{
						App->fonts->BlitText(160, 60, debug_font, "x");
					}
					//Check BUTTONS & AXIS Currently PC CRASH DO NOT UNCOMMENT
					/*sprintf_s(gamepad_P1_LAxis_X, 4, "%7d", App->input->gamepadP1LAxisX);
					App->fonts->BlitText(100, 30, 0, gamepad_P1_LAxis_X);*/
					
				}
				if (App->input->debugMode == true && App->input->gamepadP1con == false)
				{
					App->fonts->BlitText(150, 50, debug_font, "p1 controller off");
				}
				//Controller Debug P2
				if (App->input->debugMode == true && App->input->gamepadP2con == true)
				{
					App->fonts->BlitText(150, 70, debug_font, "p2 controller on");
					if (App->input->gamepadP2APressed == true)
					{
						App->fonts->BlitText(150, 80, debug_font, "a");
					}
					if (App->input->gamepadP2XPressed == true)
					{
						App->fonts->BlitText(160, 80, debug_font, "x");
					}
					//Check BUTTONS & AXIS Currently PC CRASH DO NOT UNCOMMENT
					/*sprintf_s(gamepad_P1_LAxis_X, 4, "%7d", App->input->gamepadP1LAxisX);
					App->fonts->BlitText(100, 30, 0, gamepad_P1_LAxis_X);*/
				}
				if (App->input->debugMode == true && App->input->gamepadP2con == false)
				{
					App->fonts->BlitText(150, 70, debug_font, "p2 controller off");
				}
			}break;
		
		case Stage2:
		{
			if (p1Dead == true && p2Dead == true && coins < 1)
			{
				App->fade->FadeToBlack(App->stage2, App->scene_HiScore);
			}
			//Blit Coins
			App->fonts->BlitText(230, 210, creditsFont, "credit ");
			sprintf_s(coins_text, 10, "%7d", coins);
			if (coins < 10)
			{
				App->fonts->BlitText(280, 210, creditsFont, "0");
				App->fonts->BlitText(241, 210, creditsFont, coins_text);
			}
			else
			{
				App->fonts->BlitText(241, 210, creditsFont, coins_text);
			}
			//Calculate hiScore
			if (player1Score > hiScore) { hiScore = player1Score; }
			if (player2Score > hiScore) { hiScore = player2Score; }
			//Blit Hi Score
			App->fonts->BlitText(120, 10, hiScoreFont, "hi-");
			sprintf_s(hiScore_text, 10, "%7d", hiScore);
			App->fonts->BlitText(145, 10, hiScoreFont, hiScore_text);
			//Blit SCORE
			App->fonts->BlitText(10, 10, font_score, "1P");
			sprintf_s(player1Score_text, 10, "%7d", player1Score);
			App->fonts->BlitText(50, 10, 0, player1Score_text);

			if (App->input->secondPlayerState == true)
			{
				App->fonts->BlitText(210, 10, font_score, "2P");
				sprintf_s(player2Score_text, 10, "%7d", player2Score);
				App->fonts->BlitText(250, 10, 0, player2Score_text);
			}
			//Blit P1 Charging Special Attack beam
			if (p1Dead == false)
			{
				if (App->player1->destroyed == false)
				{
					if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_REPEAT)
					{

						if (p1BeamCharging.Finished())
						{
							App->render->Blit(beamTex, 74, 27, &(p1BeamCharged.GetCurrentFrame()), 1, false);
						}
						else
						{
							App->render->Blit(beamTex, 74, 28, &(p1BeamCharging.GetCurrentFrame()), 1, false);
						}
						if (App->player1->bluePower < 2)
						{
							App->render->Blit(beamTex, 74, 28, &(p1BeamIdle.GetCurrentFrame()), 1, false);
						}
					}
					else
					{
						p1BeamCharging.Reset();
						p1BeamCharging.ResetLoops();
						App->render->Blit(beamTex, 74, 28, &(p1BeamIdle.GetCurrentFrame()), 1, false);
					}
				}
			}

			//Blit P2 Charging Special Attack beam
			if (p2Dead == false)
			{
				if (App->player2->destroyed == false)
				{
					if (App->input->keyboard[SDL_SCANCODE_V] == KEY_STATE::KEY_REPEAT)
					{

						if (p2BeamCharging.Finished())
						{
							App->render->Blit(beamTex, 249, 28, &(p2BeamCharged.GetCurrentFrame()), 1, false);
						}
						else
						{
							App->render->Blit(beamTex, 249, 28, &(p2BeamCharging.GetCurrentFrame()), 1, false);
						}
						if (App->player2->bluePower < 2)
						{
							App->render->Blit(beamTex, 249, 28, &(p2BeamIdle.GetCurrentFrame()), 1, false);
						}
					}
					else
					{
						p2BeamCharging.Reset();
						p2BeamCharging.ResetLoops();
						App->render->Blit(beamTex, 249, 28, &(p2BeamIdle.GetCurrentFrame()), 1, false);
					}
				}
			}
			//Blit Boxes
			if (App->player1->type == weapon_types::TYPE_1)
			{
				App->render->Blit(hudTex, 10, 20, &blueBoxNormalRect, false);
				App->render->Blit(hudTex, 42, 20, &redBoxFintaelRect, false);
				App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 106, 20, &greenBoxRollingRect, false);
			}
			else if (App->player1->type == weapon_types::TYPE_2)
			{
				App->render->Blit(hudTex, 10, 20, &blueBoxReverseRect, false);
				App->render->Blit(hudTex, 42, 20, &redBoxHawkRect, false);
				App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 106, 20, &greenBoxSideRect, false);
			}
			else if (App->player1->type == weapon_types::TYPE_3)
			{
				App->render->Blit(hudTex, 10, 20, &blueBoxWayRect, false);
				App->render->Blit(hudTex, 42, 20, &redBoxLaserRect, false);
				App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 106, 20, &greenBoxRearRect, false);
			}
			else if (App->player1->type == weapon_types::TYPE_4)
			{
				App->render->Blit(hudTex, 10, 20, &blueBoxLaserRect, false);
				App->render->Blit(hudTex, 42, 20, &redBoxNormalRect, false);
				App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 106, 20, &greenBoxFrontRect, false);
			}
			//Blit Boxes P2
			if (App->player2->type == weapon_types::TYPE_1)
			{
				App->render->Blit(hudTex, 185, 20, &blueBoxNormalRect, false);
				App->render->Blit(hudTex, 217, 20, &redBoxFintaelRect, false);
				App->render->Blit(hudTex, 249, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 281, 20, &greenBoxRollingRect, false);
			}
			else if (App->player2->type == weapon_types::TYPE_2)
			{
				App->render->Blit(hudTex, 185, 20, &blueBoxReverseRect, false);
				App->render->Blit(hudTex, 217, 20, &redBoxHawkRect, false);
				App->render->Blit(hudTex, 249, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 281, 20, &greenBoxSideRect, false);
			}
			else if (App->player2->type == weapon_types::TYPE_3)
			{
				App->render->Blit(hudTex, 185, 20, &blueBoxWayRect, false);
				App->render->Blit(hudTex, 217, 20, &redBoxLaserRect, false);
				App->render->Blit(hudTex, 249, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 281, 20, &greenBoxRearRect, false);
			}
			else if (App->player2->type == weapon_types::TYPE_4)
			{
				App->render->Blit(hudTex, 185, 20, &blueBoxLaserRect, false);
				App->render->Blit(hudTex, 217, 20, &redBoxNormalRect, false);
				App->render->Blit(hudTex, 249, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 281, 20, &greenBoxFrontRect, false);
			}
			//Blit powerUp levels in the boxes
			if (p1Dead == false)
			{
				sprintf_s(p1BluePowerLevel, 10, "%7d", App->player1->bluePower);
				App->fonts->BlitText(12, 21, powerUpFont, p1BluePowerLevel);
				sprintf_s(p1OrangePowerLevel, 10, "%7d", App->player1->orangePower);
				App->fonts->BlitText(44, 21, powerUpFont, p1OrangePowerLevel);
				sprintf_s(p1YellowPowerLevel, 10, "%7d", App->player1->yellowPower);
				App->fonts->BlitText(76, 21, powerUpFont, p1YellowPowerLevel);
				sprintf_s(p1GreenPowerLevel, 10, "%7d", App->player1->greenPower);
				App->fonts->BlitText(108, 21, powerUpFont, p1GreenPowerLevel);
			}

			if (p2Dead == false)
			{
				sprintf_s(p2BluePowerLevel, 10, "%7d", App->player2->bluePower);
				App->fonts->BlitText(187, 21, powerUpFont, p2BluePowerLevel);
				sprintf_s(p2OrangePowerLevel, 10, "%7d", App->player2->orangePower);
				App->fonts->BlitText(219, 21, powerUpFont, p2OrangePowerLevel);
				sprintf_s(p2YellowPowerLevel, 10, "%7d", App->player2->yellowPower);
				App->fonts->BlitText(243, 21, powerUpFont, p2OrangePowerLevel);
				sprintf_s(p2GreenPowerLevel, 10, "%7d", App->player2->greenPower);
				App->fonts->BlitText(283, 21, powerUpFont, p2GreenPowerLevel);
			}
			//HUD Lives 1P
			if (p1Dead == false)
			{
				if (App->player1->lives == 2 || App->player1->lives == 3)
				{
					App->render->Blit(hudTex, 18, 28, &livesP1, false);
				}
				if (App->player1->lives == 3)
				{
					App->render->Blit(hudTex, 26, 28, &livesP1, false);
				}
			}
			//HUD Lives 2P
			if (p2Dead == false)
			{
				if (App->player2->lives == 2 || App->player2->lives == 3)
				{
					App->render->Blit(hudTex, 193, 28, &livesP2, false);
				}
				if (App->player2->lives == 3)
				{
					App->render->Blit(hudTex, 201, 28, &livesP2, false);
				}
			}
			//DEBUG mode
			if (App->input->debugMode == true)
			{
				App->fonts->BlitText(10, 40, debug_font, "debug mode");
			}
			if (App->player1->godMode == true && App->input->debugMode == true || App->player2->godMode == true && App->input->debugMode == true)
			{
				App->fonts->BlitText(10, 50, debug_font, "god mode");
			}
			if (App->input->coliderView == true && App->input->debugMode == true)
			{
				App->fonts->BlitText(10, 60, debug_font, "collider view");
			}
			if (App->stage2->fasterX == true && App->input->debugMode == true)
			{
				App->fonts->BlitText(10, 70, debug_font, "super speed");
			}
			//Controller Debug P1
			if (App->input->debugMode == true && App->input->gamepadP1con == true)
			{
				App->fonts->BlitText(150, 50, debug_font, "p1 controller on");
				if (App->input->gamepadP1APressed == true)
				{
					App->fonts->BlitText(150, 60, debug_font, "a");
				}
				if (App->input->gamepadP1XPressed == true)
				{
					App->fonts->BlitText(160, 60, debug_font, "x");
				}
				//Check BUTTONS & AXIS Currently PC CRASH DO NOT UNCOMMENT
				/*sprintf_s(gamepad_P1_LAxis_X, 4, "%7d", App->input->gamepadP1LAxisX);
				App->fonts->BlitText(100, 30, 0, gamepad_P1_LAxis_X);*/

			}
			if (App->input->debugMode == true && App->input->gamepadP1con == false)
			{
				App->fonts->BlitText(150, 50, debug_font, "p1 controller off");
			}
			//Controller Debug P2
			if (App->input->debugMode == true && App->input->gamepadP2con == true)
			{
				App->fonts->BlitText(150, 70, debug_font, "p2 controller on");
				if (App->input->gamepadP2APressed == true)
				{
					App->fonts->BlitText(150, 80, debug_font, "a");
				}
				if (App->input->gamepadP2XPressed == true)
				{
					App->fonts->BlitText(160, 80, debug_font, "x");
				}
				//Check BUTTONS & AXIS Currently PC CRASH DO NOT UNCOMMENT
				/*sprintf_s(gamepad_P1_LAxis_X, 4, "%7d", App->input->gamepadP1LAxisX);
				App->fonts->BlitText(100, 30, 0, gamepad_P1_LAxis_X);*/
			}
			if (App->input->debugMode == true && App->input->gamepadP2con == false)
			{
				App->fonts->BlitText(150, 70, debug_font, "p2 controller off");
			}
		}break;

		case StageClear:
			//Blit Coins
			App->fonts->BlitText(230, 210, creditsFont, "credit ");
			sprintf_s(coins_text, 10, "%7d", coins);
			if (coins < 10)
			{
				App->fonts->BlitText(280, 210, creditsFont, "0");
				App->fonts->BlitText(241, 210, creditsFont, coins_text);
			}
			else
			{
				App->fonts->BlitText(241, 210, creditsFont, coins_text);
			}
			{	//Print the scores, but as we are not playing we don't need to update if the score increases, print teamScore
				App->fonts->BlitText(10, 10, font_score, "1P");
				App->fonts->BlitText(50, 10, 0, player1Score_text);
				App->fonts->BlitText(120, 10, hiScoreFont, "hi-");
				App->fonts->BlitText(145, 10, hiScoreFont, hiScore_text);
				if (App->input->secondPlayerState == true)
				{
					App->fonts->BlitText(210, 10, font_score, "2P");
					App->fonts->BlitText(250, 10, 0, player2Score_text);
				}
				//Print replay
				if (CompletedLevel == 2)
				{
					App->fonts->BlitText(35, 175, font_yellowtxt, "press enter to play again");
					App->fonts->BlitText(10, 190, font_yellowtxt, "press space to go to main menu");
				}
				//Add the 2 scores to have the Team Score and blit them
				App->fonts->BlitText(115, 20, font_yellowtxt, "teamscore");
				if (App->input->secondPlayerState == true)
				{
					teamScore = player1Score + player2Score;
				} 
				else {
					teamScore = player1Score;
				}
				sprintf_s(teamScore_text, 10, "%7d", teamScore);
				App->fonts->BlitText(110, 30, font_yellowtxt, teamScore_text);
			}break;
		
		case GameOver:
		{	//Print the scores, but as we are not playing we don't need to update if the score increases, print teamScore
			App->fonts->BlitText(10, 10, font_score, "1P");
			App->fonts->BlitText(50, 10, 0, player1Score_text);
			App->fonts->BlitText(145, 10, hiScoreFont, hiScore_text);
			App->fonts->BlitText(120, 10, hiScoreFont, "hi-");
			if (App->input->secondPlayerState == true)
			{
				App->fonts->BlitText(210, 10, font_score, "2P");
				App->fonts->BlitText(250, 10, 0, player2Score_text);
			}
			//Print replay 
			App->fonts->BlitText(35,85, font_yellowtxt, "press enter to play again");
			App->fonts->BlitText(10, 100, font_yellowtxt, "press space to go to main menu");
			
			//Add the 2 scores to have the Team Score and blit them
			App->fonts->BlitText(115, 20, font_yellowtxt, "teamscore");
			if (App->input->secondPlayerState == true)
			{
				teamScore = player1Score + player2Score;
			}
			else {
				teamScore = player1Score;
			}
			sprintf_s(teamScore_text, 10, "%7d", teamScore);
			App->fonts->BlitText(110, 30, font_yellowtxt, teamScore_text);
		}break;
	}


	return UPDATE_CONTINUE;
}

