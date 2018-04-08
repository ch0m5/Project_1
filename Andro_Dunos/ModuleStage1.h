#ifndef __ModuleStage1_H__
#define __ModuleStage1_H__	//@DídacRomero @AndresSaladrigas

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

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

	//Rectangles
	SDL_Rect background1Rect;
	SDL_Rect map1Rect;
	SDL_Rect bluePlanetRect;

	// Background movement (position) values
	//X Axis
	float movementx = 0;
	float movementxBack = 0;
	float movementxPlanetsBack = 0;
	//Y Axis
	float movementy = 0;
	float movementyBack = 0;

	//Background Movement logic variables
	bool moveMapRight = true;
	bool moveMapUp = false;
	bool moveMapDown = false;  
};

#endif