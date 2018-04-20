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

	score = 0;
	player2Score = 0;
	char player1ScoreStr[8] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	char player2ScoreStr[8] = { NULL,NULL,NULL,NULL,NULL,NULL,NULL };
	font_score = App->fonts->Load("Assets/Sprites/User_Interface/fonts/Font-score-white.png", "1234567890P", 1);
	
	return ret;
}

// Unload assets
bool ModuleUserInterface::CleanUp()
{
	LOG("Unloading UI");
	//Unload fonts
	App->fonts->UnLoad(font_score);
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
	else if (App->stageClear->IsEnabled() == true)
	{
		CurrentStage = StageClear;
	}

	//Execute the logic and blits for each Scene
	switch (CurrentStage)
	{
		case MainMenu:
			{
				player1Score = 0;
				player2Score = 0;
				teamScore = 0;
			}break;

		case Stage1:
			{
				App->fonts->BlitText(10, 10, font_score, "1P");
				sprintf_s(player1Score_text, 10, "%7d", player1Score);
				App->fonts->BlitText(50, 10, 0, player1Score_text);

				if (App->input->secondPlayerState == true)
				{
					App->fonts->BlitText(210, 10, font_score, "2P");
					sprintf_s(player2Score_text, 10, "%7d", player2Score);
					App->fonts->BlitText(250, 10, 0, player2Score_text);
				}
			}break;

		case StageClear:
			{	//Print the scores, but as we are not playing we don't need to update if the score increases, print teamScore
				App->fonts->BlitText(10, 10, font_score, "1P");
				App->fonts->BlitText(50, 10, 0, player1Score_text);
				App->fonts->BlitText(210, 10, font_score, "2P");
				App->fonts->BlitText(250, 10, 0, player2Score_text);
				//Add the 2 scores to have the Team Score and blit them
				App->fonts->BlitText(120, 20, font_score, "00000");
				teamScore = player1Score + player2Score;
				sprintf_s(teamScore_text, 10, "%7d", teamScore);
				App->fonts->BlitText(110, 30, 0, teamScore_text);
			}break;
		
		case GameOver:
		{	//Print the scores, but as we are not playing we don't need to update if the score increases, print teamScore
			App->fonts->BlitText(10, 10, font_score, "1P");
			App->fonts->BlitText(50, 10, 0, player1Score_text);
			App->fonts->BlitText(210, 10, font_score, "2P");
			App->fonts->BlitText(250, 10, 0, player2Score_text);
			//Add the 2 scores to have the Team Score and blit them
			App->fonts->BlitText(120, 20, font_score, "00000");
			teamScore = player1Score + player2Score;
			sprintf_s(teamScore_text, 10, "%7d", teamScore);
			App->fonts->BlitText(110, 30, 0, teamScore_text);
		}break;
	}


	return UPDATE_CONTINUE;
}

