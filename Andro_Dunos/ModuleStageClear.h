
#ifndef __ModuleStageClear_H__
#define __ModuleStageClear_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleStageClear : public Module
{
public:
	ModuleStageClear();
	~ModuleStageClear();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Textures
	SDL_Texture* stageClearText = nullptr;

	//Rectangles
	SDL_Rect stageClearRect;

	float ySpeedAnimation = 0;

	//Music 
	Mix_Music * MusicStageClear = nullptr;
};




#endif