#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleMixer.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleParticles.h"
#include "ModuleMainMenu.h"
#include "ModuleStage1.h"
#include "ModuleStage2.h"
#include "ModuleHiScore.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleFont.h"
#include "ModuleUserInterface.h"
#include "ModuleStageClear.h"


Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = mixer = new ModuleMixer();
	//modules[i++] = stage2 = new ModuleStage2();
	modules[i++] = stage1 = new ModuleStage1();
	modules[i++] = stageClear = new ModuleStageClear();
	modules[i++] = scene_HiScore = new ModuleHiScore();
	modules[i++] = mainMenu = new ModuleMainMenu();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = player2 = new ModulePlayer2();
	modules[i++] = player1 = new ModulePlayer1();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = fonts = new ModuleFont();
	modules[i++] = UI = new ModuleUserInterface();
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Characters will be disabled on the first update of a new scene
	player1->Disable();
	player2->Disable();
	enemies->Disable();

	// Disable all maps that you do not start with
	stage1->Disable();
	//stage2->Disable(); 
	scene_HiScore->Disable();
	stageClear->Disable();
	// Disable collisions
	collision->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}