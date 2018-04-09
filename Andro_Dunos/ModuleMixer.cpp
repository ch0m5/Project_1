#include "Globals.h"
#include "Application.h"
#include "ModuleMixer.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleMainMenu.h"

#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

#define MUSIC 60	// Volume values
#define FX 70

ModuleMixer::ModuleMixer() : Module() {

	for (int i = 0; i < MAX_MUSIC; ++i) {
		soundtrack[i] = nullptr;
	}

	for (int i = 0; i < MAX_FX; ++i) {
		fx[i] = nullptr;
	}
}

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
	// Initialize Audio
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

		/*soundtrack1 = Mix_LoadMUS("Music/04_Stage_1-The Moon-Loop.ogg");
		soundtrack2 = Mix_LoadMUS("Music/07_Stage_2 -Mechanized-Unit-Loop.ogg");
		soundtrack3 = Mix_LoadMUS("Music/18_Game_Over.ogg");*/
		//
		//Mix_PlayMusic(soundtrack0, 1);
		//
	return ret;
	
}

bool ModuleMixer::CleanUp()
{
	LOG("Free Audio");

	for (int i = 0; i < MAX_MUSIC; ++i) {
		if (soundtrack[i] != nullptr) {
			Mix_FreeMusic(soundtrack[i]);
			soundtrack[i] = nullptr;
		}
	}

	for (int i = 0; i < MAX_FX; ++i) {
		if (fx[i] != nullptr) {
			Mix_FreeChunk(fx[i]);
			fx[i] = nullptr;
		}
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

update_status ModuleMixer::Update()
{
	if (!musicRunning) {
		Mix_PlayMusic(soundtrack[0], -1);
		musicRunning = true;
	}

	return UPDATE_CONTINUE;
};

Mix_Music * const ModuleMixer::LoadMusic(const char* path)	// Function to check a music load, if fail SDL_GetError, if success execute it
{
	bool ret = true;
	Mix_Music * music = nullptr;

	music = Mix_LoadMUS(path);

	if (!music)
	{
		LOG("Couldn't load music: %s", SDL_GetError());
		ret = false;
	}
	
	return music;
}

Mix_Chunk * const ModuleMixer::LoadFX(const char* path)	// Function to check a sound load, if fail SDL_GetError, if success execute it
{
	bool ret = true;
	Mix_Chunk * shot = nullptr;

	shot = Mix_LoadWAV(path);

	if (!shot)
	{
		LOG("Couldn't load fx: %s", SDL_GetError());	// Does SDL_GetError work with Mix_LoadWAV?
		ret = false;
	}

	return shot;
}