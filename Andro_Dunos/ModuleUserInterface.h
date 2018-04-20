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
	char player1Score_text[10];
	char player2Score_text[10];
	char teamScore_text[10];

	enum Scenes
	{
		GameOver = -1,
		MainMenu,
		Stage1,
		StageClear
	};

	int CurrentStage;
};

#endif