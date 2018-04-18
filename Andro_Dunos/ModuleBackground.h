#ifndef __ModuleBackground_H__
#define __ModuleBackground_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_rect.h"

struct SDL_Texture;


class ModuleBackground : public Module
{
public:
	ModuleBackground();
	~ModuleBackground();

	bool Init();
	update_status Update();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* background1Text = nullptr;
	SDL_Texture* map1Text = nullptr;
	SDL_Texture* ship1Text = nullptr;
	SDL_Texture* bluePlanetText = nullptr;
	
	
	SDL_Rect background1Rect;
	SDL_Rect map1Rect;
	SDL_Rect bluePlanetRect;

	float movementx = 0;
	float movementxBack = 0;
	float movementxPlanetsBack = 0;
};//@AndresSala

#endif
