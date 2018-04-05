#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleMixer.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleMainMenu.h"
#include "ModuleStage1.h"
#include "ModuleStage2.h"
#include "ModuleHiScore.h"

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = mixer = new ModuleMixer();
	modules[5] = stage2 = new ModuleStage2();
	modules[6] = stage1 = new ModuleStage1();
	modules[7] = scene_HiScore = new ModuleHiScore();
	modules[8] = mainMenu = new ModuleMainMenu();
	modules[9] = player1 = new ModulePlayer1();
	modules[10] = player2 = new ModulePlayer2();
	modules[11] = fade = new ModuleFadeToBlack();

}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Player will be disabled on the first update of a new scene
	player1->Disable();
	player2->Disable();

	// Disable all maps that you do not start with
	stage1->Disable();
	stage2->Disable(); 
	scene_HiScore->Disable();

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