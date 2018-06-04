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
	int powerUpFont = -1;
	int typeFont = -1;

	char player1Score_text[10];
	char player2Score_text[10];
	char teamScore_text[10];
	char gamepad_P1_LAxis_X [4];
	//P1 PowerUp Levels
	char p1BluePowerLevel[2];
	char p1OrangePowerLevel[2];
	char p1YellowPowerLevel[2];
	char p1GreenPowerLevel[2];
	//P2 PowerUp Levels
	char p2BluePowerLevel[2];
	char p2OrangePowerLevel[2];
	char p2YellowPowerLevel[2];
	char p2GreenPowerLevel[2];
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

	//Player Boxes textures
	SDL_Texture* hudTex = nullptr;

	//Player Boxes Squares
	SDL_Rect blueBoxNormalRect;
	SDL_Rect blueBoxReverseRect;
	SDL_Rect blueBoxWayRect;
	SDL_Rect blueBoxLaserRect;
	SDL_Rect redBoxFintaelRect;
	SDL_Rect redBoxHawkRect;
	SDL_Rect redBoxLaserRect;
	SDL_Rect redBoxNormalRect;
	SDL_Rect yellowBoxHomingRect;
	SDL_Rect greenBoxRollingRect;
	SDL_Rect greenBoxSideRect;
	SDL_Rect greenBoxRearRect;
	SDL_Rect greenBoxFrontRect;

	SDL_Rect livesP1;
	SDL_Rect livesP2;
	//Logic Variables
	int startTime;
	int p1TypeSwapStartTime;
	int p2TypeSwapStartTime;
	bool showPress1P;
	bool p1ShowType;
	bool p2ShowType;

};

#endif