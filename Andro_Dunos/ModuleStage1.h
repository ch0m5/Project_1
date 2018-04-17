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

	//Rectangles
	SDL_Rect background1Rect;
	SDL_Rect map1Rect;
	SDL_Rect bluePlanetRect;
	SDL_Rect caveBackRect;

	// Background movement (position) values
	//X Axis
	float movementx = 0;
	float movementxBack = 0;
	float movementxPlanetsBack = 0;
	float  backmovementcaveX = 2946; 
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