#include "Globals.h"
#include "Application.h"
#include "ModuleMixer.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

ModuleMixer::ModuleMixer() : Module()
{}

ModuleMixer::~ModuleMixer() {}

bool ModuleMixer::Init() {

	LOG("Creating the music");
	bool ret = true;

	if (SDL_Init(SDL_INIT_AUDIO) !=0) {
		LOG("Broken: %s ", SDL_GetError());
		ret = false;
	}
	
	else	
	{
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		soundtrack = Mix_LoadMUS("Music/04_Stage_1-The Moon-Loop.ogg");
		Mix_VolumeMusic(20);
		Mix_PlayMusic(soundtrack, -1);
	}

	if (soundtrack == NULL) {
		LOG("Broken: %s", SDL_GetError());
		ret = false;
	}

	return ret;
	
}

bool ModuleMixer::CleanUp() {

	if (soundtrack != nullptr) {
		Mix_FreeMusic(soundtrack);
		Mix_Quit();
	}

	return true;
}
