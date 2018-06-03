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
#include <stdio.h>
ModuleUserInterface::ModuleUserInterface()	//@DídacRomero
{
	//ANDRO DUNOS RECTS

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
	p1Dead = true;
	p2Dead = true;
	player1Score = 0;
	player2Score = 0;
	//Load fonts
	font_score = App->fonts->Load("Assets/Sprites/User_Interface/fonts/Font-score-white.png", "1234567890P", 1);
	font_yellowtxt = App->fonts->Load("Assets/Sprites/User_Interface/fonts/yellow_font.png", "0123456789abcdefghiklmnoprstuvy©        ", 4);
	debug_font= App->fonts->Load("Assets/Sprites/User_Interface/fonts/blue_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);
	
	//Load player boxes
	hudTex = App->textures->Load("Assets/Sprites/User_Interface/Grafical_Interface/hud_elements.png");
	

	//Setting up all the Rects
	blueBoxNormalRect = {1,13, 32, 7};
	redBoxFintaelRect = {1,58, 32, 7 };
	yellowBoxHomingRect = { 1,103, 32, 7 };
	greenBoxRollingRect = { 34,13, 32, 7 };
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
	return true;
}

// Update: draw background
update_status ModuleUserInterface::Update()
{
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
		//	App->fonts->BlitText(65, 190, font_yellowtxt, "press space to play");
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
			App->fonts->BlitText(65, 201, font_yellowtxt, "all rights reserved");

			player1Score = 0;
				player2Score = 0;
				teamScore = 0;
			}break;

		case Stage1:
			{
			//Blit SCORE
				App->fonts->BlitText(10, 10, font_score, "1P");
				sprintf_s(player1Score_text, 10, "%7d", player1Score);
				App->fonts->BlitText(50, 10, 0, player1Score_text);


				//Blit SCORE
				if (App->input->secondPlayerState == true)
				{
					App->fonts->BlitText(210, 10, font_score, "2P");
					sprintf_s(player2Score_text, 10, "%7d", player2Score);
					App->fonts->BlitText(250, 10, 0, player2Score_text);
				}
				//Blit Boxes
				App->render->Blit(hudTex, 10, 20, &blueBoxNormalRect, false);
				App->render->Blit(hudTex, 42, 20, &redBoxFintaelRect, false);
				App->render->Blit(hudTex, 74, 20, &yellowBoxHomingRect, false);
				App->render->Blit(hudTex, 106, 20, &greenBoxRollingRect, false);





				//DEBUG mode
				if (App->input->debugMode == true)
				{
					App->fonts->BlitText(10, 20, debug_font, "debug mode");
				}
				if (App->player1->godMode == true && App->input->debugMode == true || App->player2->godMode == true && App->input->debugMode == true)
				{
					App->fonts->BlitText(10, 30, debug_font, "god mode");
				}
				if (App->input->coliderView == true && App->input->debugMode == true)
				{
					App->fonts->BlitText(10, 40, debug_font, "collider view");
				}
				if (App->stage1->fasterX == true && App->input->debugMode == true)
				{
					App->fonts->BlitText(10, 50, debug_font, "super speed");
				}
				//Controller Debug P1
      				if (App->input->debugMode == true && App->input->gamepadP1con == true)
				{
					App->fonts->BlitText(100, 20, debug_font, "p1 controller on");
					if (App->input->gamepadP1APressed == true)
					{
						App->fonts->BlitText(100, 30, debug_font, "a");
					}
					if (App->input->gamepadP1XPressed == true)
					{
						App->fonts->BlitText(110, 30, debug_font, "x");
					}
					//Check BUTTONS & AXIS Currently PC CRASH DO NOT UNCOMMENT
					/*sprintf_s(gamepad_P1_LAxis_X, 4, "%7d", App->input->gamepadP1LAxisX);
					App->fonts->BlitText(100, 30, 0, gamepad_P1_LAxis_X);*/
					
				}
				if (App->input->debugMode == true && App->input->gamepadP1con == false)
				{
					App->fonts->BlitText(100, 20, debug_font, "p1 controller off");
				}
				//Controller Debug P2
				if (App->input->debugMode == true && App->input->gamepadP2con == true)
				{
					App->fonts->BlitText(160, 50, debug_font, "p2 controller on");
					if (App->input->gamepadP2APressed == true)
					{
						App->fonts->BlitText(170, 60, debug_font, "a");
					}
					if (App->input->gamepadP2XPressed == true)
					{
						App->fonts->BlitText(180, 60, debug_font, "x");
					}
					//Check BUTTONS & AXIS Currently PC CRASH DO NOT UNCOMMENT
					/*sprintf_s(gamepad_P1_LAxis_X, 4, "%7d", App->input->gamepadP1LAxisX);
					App->fonts->BlitText(100, 30, 0, gamepad_P1_LAxis_X);*/
				}
				if (App->input->debugMode == true && App->input->gamepadP2con == false)
				{
					App->fonts->BlitText(160, 50, debug_font, "p2 controller off");
				}
			}break;
		
		case Stage2:
		{
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
			//DEBUG mode
			if (App->input->debugMode == true)
			{
				App->fonts->BlitText(10, 20, debug_font, "debug mode");
			}
			if (App->player1->godMode == true && App->input->debugMode == true || App->player2->godMode == true && App->input->debugMode == true)
			{
				App->fonts->BlitText(10, 30, debug_font, "god mode");
			}
			if (App->input->coliderView == true && App->input->debugMode == true)
			{
				App->fonts->BlitText(10, 40, debug_font, "collider view");
			}
			if (App->stage1->fasterX == true && App->input->debugMode == true)
			{
				App->fonts->BlitText(10, 50, debug_font, "super speed");
			}
			//Controller Debug P1
			if (App->input->debugMode == true && App->input->gamepadP1con == true)
			{
				App->fonts->BlitText(100, 20, debug_font, "p1 controller on");
				if (App->input->gamepadP1APressed == true)
				{
					App->fonts->BlitText(100, 30, debug_font, "a");
				}
				if (App->input->gamepadP1XPressed == true)
				{
					App->fonts->BlitText(110, 30, debug_font, "x");
				}
				//Check BUTTONS & AXIS Currently PC CRASH DO NOT UNCOMMENT
				/*sprintf_s(gamepad_P1_LAxis_X, 4, "%7d", App->input->gamepadP1LAxisX);
				App->fonts->BlitText(100, 30, 0, gamepad_P1_LAxis_X);*/

			}
			if (App->input->debugMode == true && App->input->gamepadP1con == false)
			{
				App->fonts->BlitText(100, 20, debug_font, "p1 controller off");
			}
			//Controller Debug P2
			if (App->input->debugMode == true && App->input->gamepadP2con == true)
			{
				App->fonts->BlitText(160, 50, debug_font, "p2 controller on");
				if (App->input->gamepadP2APressed == true)
				{
					App->fonts->BlitText(170, 60, debug_font, "a");
				}
				if (App->input->gamepadP2XPressed == true)
				{
					App->fonts->BlitText(180, 60, debug_font, "x");
				}
				//Check BUTTONS & AXIS Currently PC CRASH DO NOT UNCOMMENT
				/*sprintf_s(gamepad_P1_LAxis_X, 4, "%7d", App->input->gamepadP1LAxisX);
				App->fonts->BlitText(100, 30, 0, gamepad_P1_LAxis_X);*/
			}
			if (App->input->debugMode == true && App->input->gamepadP2con == false)
			{
				App->fonts->BlitText(160, 50, debug_font, "p2 controller off");
			}
		}break;

		case StageClear:
			{	//Print the scores, but as we are not playing we don't need to update if the score increases, print teamScore
				App->fonts->BlitText(10, 10, font_score, "1P");
				App->fonts->BlitText(50, 10, 0, player1Score_text);
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

