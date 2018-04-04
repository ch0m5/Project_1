#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleMixer.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer1.h"
#include "ModulePlayer2.h"
#include "ModuleStage1.h"
<<<<<<< HEAD
#include "Module"
=======
#include "ModuleMainMenu.h"
>>>>>>> afb90c6a89fee0c68193bd2ff67e24fc52b13e97

Application::Application()
{
	modules[0] = window = new ModuleWindow();
	modules[1] = render = new ModuleRender();
	modules[2] = input = new ModuleInput();
	modules[3] = textures = new ModuleTextures();
	modules[4] = mixer = new ModuleMixer();
	modules[5] = fade = new ModuleFadeToBlack();
	modules[6] = stage1 = new ModuleStage1();
	modules[7] = player2 = new ModulePlayer2();
	modules[8] = player1 = new ModulePlayer1();
<<<<<<< HEAD
	modules[9] = stage2 = new ModuleSecondStage();
=======
	//modules[9] = mainMenu = new ModuleMainMenu();
>>>>>>> afb90c6a89fee0c68193bd2ff67e24fc52b13e97
}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->PreUpdate();

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->Update();

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->PostUpdate();

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}