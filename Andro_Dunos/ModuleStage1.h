#ifndef __ModuleStage1_H__
#define __ModuleStage1_H__	//@DídacRomero @AndresSaladrigas

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleStage1 : public Module
{
public:
	ModuleStage1();
	~ModuleStage1();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Textures
	SDL_Texture* background1Text = nullptr;
	SDL_Texture* map1Text = nullptr;
	SDL_Texture* bluePlanetText = nullptr;
	SDL_Texture* caveBackText = nullptr;
	SDL_Texture* redPlanetText = nullptr;
	//Star textures
	SDL_Texture* starsText = nullptr;

	//Rectangles
	SDL_Rect background1Rect;
	SDL_Rect map1Rect;
	SDL_Rect bluePlanetRect;
	SDL_Rect caveBackRect;
	SDL_Rect redPlanetRect;
	//Star Rectangles
	SDL_Rect starBlue4Rect;
	SDL_Rect starRed1Rect;
	SDL_Rect starWhite2Rect;
	SDL_Rect starWhite8Rect;
	SDL_Rect starGreen3Rect;
	SDL_Rect starOrange5Rect;

	// Background movement (position) values
	//X Axis
	float movementx = 0;
	float movementxBack = 0;
	float movementxPlanetsBack = 0;
	float  backmovementcaveX = 2946; 
	//Star X Vars
	float movementXBlueStar = 420;
	float movementXRedStar = 320;
	float movementXWhiteStar = 320;
	float movementXWhite8Star = 370;
	float movementXGreen3Star = 470;
	float movementXWhite8StarBack1 = 320;
	float movementXWhite8StarBack2 = 400;
	float movementXWhite8StarBack3 = 420;
	float movementXOrange5Star1 = 400;
	float movementXOrange5Star2 = 450;
	//Y Axis
	float movementy = 0;
	float movementyBack = 0;

	//Background Movement logic variables
	bool moveMapRight = true;
	bool moveMapUp = false;
	bool moveMapDown = false; 
	int xSpeedMultiplier = 1;
	float ySpeedMultiplier = 1;



	//Debug and Developing purpose variables
	bool fasterX = false;

	//Music									@XaviMarin
	Mix_Music * MusicLvl1 = nullptr;
};

#endif