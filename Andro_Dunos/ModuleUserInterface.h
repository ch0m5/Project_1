#ifndef __MODULEUSERINTERFACE_H__
#define __MODULEUSERINTERFACE_H__	//@DídacRomero 
#include "Module.h"
#include "SDL\include\SDL_pixels.h"


#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleUserInterface : public Module
{
public:
	ModuleUserInterface();
	~ModuleUserInterface();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Variables
	uint score;
	uint player1Score;
	uint player2Score;
	uint teamScore;
	
	int font_score = -1;
	int font_yellowtxt = -1;
	int debug_font = -1;
	char player1Score_text[10];
	char player2Score_text[10];
	char teamScore_text[10];
	char gamepad_P1_LAxis_X [4];

	enum Scenes
	{
		GameOver = -1,
		MainMenu,
		Stage1,
		Stage2,
		StageClear
	};

	int CurrentStage;
	int CompletedLevel;

	//Player Variables
	bool p1Dead;
	bool p2Dead;

	//Logic Variables
	int startTime;
	bool showPress1P;
};

#endif