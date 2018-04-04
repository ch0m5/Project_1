#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 10

class Module;

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleMixer;
class ModuleFadeToBlack;
class ModulePlayer1;
class ModulePlayer2;
class ModuleStage1;
class ModuleSecondStage;

class Application
{
public:

	Module * modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleMixer* mixer = nullptr;
	ModulePlayer1* player1 = nullptr;
	ModulePlayer2* player2 = nullptr;		// Player 2 comes before player 1 so that 1 renders over 2.
	ModuleFadeToBlack* fade = nullptr;
	ModuleStage1* stage1 = nullptr;
	ModuleSecondStage* stage2 = nullptr;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__