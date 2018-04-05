#ifndef __ModuleHiScore_H__
#define __ModuleHiScore_H__


#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleHiScore : public Module
{
public:
	ModuleHiScore();
	~ModuleHiScore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Textures
	SDL_Texture* hiScoreBackTex = nullptr;
	
	//Rectangles
	SDL_Rect hiScoreBackRect;

	float ySpeedAnimation = 0;
};




#endif