#include "Globals.h"
#include "Application.h"
#include "ModuleMixer.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleMainMenu.h"

#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

#define MUSIC 60
#define FX 70

ModuleMixer::ModuleMixer() : Module() {}

ModuleMixer::~ModuleMixer() {}

bool ModuleMixer::Init()
{

	LOG("Creating the music");
	bool ret = true;

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		LOG("Broken: %s ", SDL_GetError());
		ret = false;
	}


	else
	{ 
		//Music
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		soundtrack0 = Mix_LoadMUS("Music/02_Title.ogg");
		/*soundtrack1 = Mix_LoadMUS("Music/04_Stage_1-The Moon-Loop.ogg");
		soundtrack2 = Mix_LoadMUS("Music/07_Stage_2 -Mechanized-Unit-Loop.ogg");
		soundtrack3 = Mix_LoadMUS("Music/18_Game_Over.ogg");*/
		//
		//Mix_PlayMusic(soundtrack0, 1);
		//
		Mix_FadeInMusic(soundtrack0,1,1500);

		Mix_VolumeMusic(MUSIC);


		//FX
		shot = Mix_LoadWAV("Music/Laser_Shot_Type-1_(Main_Ships).wav");
		Mix_VolumeChunk(shot, FX);

	}

	if (soundtrack0 == NULL/* || soundtrack1==NULL || soundtrack2==NULL || soundtrack3==NULL*/)
	{
		LOG("Broken: %s", SDL_GetError());
		ret = false;
	}

	return ret;

}

bool ModuleMixer::CleanUp()
{

	if (soundtrack0 != nullptr /*|| soundtrack1 != NULL || soundtrack2 != NULL || soundtrack3 != NULL*/)
	{
		Mix_FreeMusic(soundtrack0);
		/*Mix_FreeMusic(soundtrack1);
		Mix_FreeMusic(soundtrack2);
		Mix_FreeMusic(soundtrack3);
*/
	}
	if (shot != nullptr)
	{
		Mix_FreeChunk(shot);
		Mix_Quit();
	}

	return true;
}

update_status ModuleMixer::Update()
{
	
	// laser FX when pressing space
	if (App->input->keyboard[SDL_SCANCODE_M] == 1 && currentScreen != MAIN_MENU)
	{

		Mix_PlayChannel(3, shot, 0);	
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		currentScreen++;

		musicRunning == false;

		if (currentScreen == 4)
			currentScreen = MAIN_MENU;
	}

 	if (currentScreen == MAIN_MENU && musicRunning == false)
	{
		soundtrack0 = Mix_LoadMUS("Music/02_Title.ogg");

		Mix_FadeInMusic(soundtrack0, 1, 1000);

		Mix_VolumeMusic(MUSIC);

		musicRunning = true;
	}

	else if (currentScreen == STAGE_1 && musicRunning == false)
	{
		soundtrack0 = Mix_LoadMUS("Music/04_Stage_1-The Moon-Loop.ogg");

		Mix_FadeInMusic(soundtrack0, 1, 1000);

		Mix_VolumeMusic(MUSIC);

		musicRunning = true;
	}

	else if (currentScreen == STAGE_2 && musicRunning == false)
	{
		soundtrack0 = Mix_LoadMUS("Music/07_Stage_2 -Mechanized-Unit-Loop.ogg");

		Mix_FadeInMusic(soundtrack0, 1, 1000);

		Mix_VolumeMusic(MUSIC);

		musicRunning = true;
	}

	else if (currentScreen == CRASHED_SHIP && musicRunning == false)
	{
		soundtrack0 = Mix_LoadMUS("Music/18_Game_Over.ogg");

		Mix_FadeInMusic(soundtrack0, 1, 1000);

		Mix_VolumeMusic(MUSIC);

		musicRunning = true;
	}
	/*
  	else if (counter == 1)
	{

		soundtrack0 = nullptr;
		Mix_FreeMusic(soundtrack0);

		soundtrack0 = Mix_LoadMUS("Music/04_Stage_1-The Moon-Loop.ogg");

		Mix_FadeInMusic(soundtrack0, -1, 1000);

		Mix_VolumeMusic(MUSIC);
		counter = 10;
	}

	else if (counter == 2)
	{
		
		soundtrack0 = nullptr;
		Mix_FreeMusic(soundtrack0);

		soundtrack0 = Mix_LoadMUS("Music/07_Stage_2 -Mechanized-Unit-Loop.ogg");

		Mix_FadeInMusic(soundtrack0, -1, 1000);

		Mix_VolumeMusic(MUSIC);
		counter = 20;
	}

	else if (counter == 3)
	{
		
		soundtrack0 = nullptr;
		Mix_FreeMusic(soundtrack0);

		soundtrack0 = Mix_LoadMUS("Music/18_Game_Over.ogg");

		Mix_FadeInMusic(soundtrack0, 1, 1000);

		Mix_VolumeMusic(MUSIC);
		counter = 30;

	}
	*/

	return update_status::UPDATE_CONTINUE;
}
