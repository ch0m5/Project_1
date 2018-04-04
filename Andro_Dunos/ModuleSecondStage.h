#ifndef __ModuleStage1_H__
#define __ModuleStage1_H__	//@DídacRomero

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSecondStage : public Module
{
public:
	ModuleSecondStage();
	~ModuleSecondStage();

	bool Start();
	update_status Update();

public:
	//Textures

	SDL_Texture* background2Text = nullptr;		//
	SDL_Texture* map2Text = nullptr;			//
	//SDL_Texture* bluePlanetText = nullptr;		//

												//Rectangles

	SDL_Rect background2Rect;	//
	SDL_Rect map2Rect;			//
	//SDL_Rect bluePlanetRect;	//


	float movementx = 48 ;
	float movementxBack = 0;
	float movementxPlanetsBack = 0;
	float movementy = -55;
};

#endif