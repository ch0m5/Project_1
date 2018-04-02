#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Start();
	update_status Update();

public:
	//Textures
	SDL_Texture* graphics = nullptr;
	SDL_Texture* background1Text = nullptr;		//
	SDL_Texture* map1Text = nullptr;			//
	SDL_Texture* ship1Text = nullptr;			//
	SDL_Texture* bluePlanetText = nullptr;		//

	//Rectangles
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect ship;
	SDL_Rect background1Rect;	//
	SDL_Rect map1Rect;			//
	SDL_Rect bluePlanetRect;	//

	Animation girl;
	Animation flag;

	float shipPos = 0;
	bool boatUp = true;

	float movementx = 0;
	float movementxBack = 0;
	float movementxPlanetsBack = 0;
};

#endif