#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class Module;

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleMixer;
class ModuleFadeToBlack;
class ModulePlayer1;
class ModulePlayer2;
class ModuleParticles;
class ModuleMainMenu;
class ModuleStage1;
class ModuleStage2;
class ModuleHiScore;
class ModuleCollision;
class ModuleEnemies;
class ModuleFont;
class ModuleUserInterface;
class ModuleStageClear;
class Application
{
public:

	Module* modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleMixer* mixer = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModulePlayer1* player1 = nullptr;
	ModulePlayer2* player2 = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleMainMenu* mainMenu = nullptr;
	ModuleStage1* stage1 = nullptr;
	ModuleStage2* stage2 = nullptr;
	ModuleHiScore* scene_HiScore = nullptr;
	ModuleCollision* collision = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleFont* fonts = nullptr;
	ModuleUserInterface* UI = nullptr;
	ModuleStageClear* stageClear = nullptr;

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