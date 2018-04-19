#include "Globals.h"
#include "Application.h"
#include "ModuleMixer.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleMainMenu.h"

#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

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
		
		LOG("Broken: %s \n", SDL_GetError());
		ret = false;
		SDL_ClearError();
	}
	// Initialize Audio
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	return ret;
	
}

bool ModuleMixer::CleanUp()
{
	LOG("CleanUp Module Mixer. Cleaning music and Sound effects");

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
	Mix_Music *music = nullptr;

	music = Mix_LoadMUS(path);

	if (!music)
	{
		
		LOG("Couldn't load music: %s \n", SDL_GetError());
		SDL_ClearError();
	}
	
	return music;
}

bool ModuleMixer::UnloadMusic(Mix_Music * music)
{
	bool ret = false;

	if (music != nullptr)
	{
		for (int i = 0; i < MAX_MUSIC; ++i)
		{
			if (soundtrack[i] == music)
			{
				Mix_FreeMusic(music);
				soundtrack[i] = nullptr;
				ret = true;
				break;
			}
		}

		
	}

	return ret;
}

Mix_Chunk * const ModuleMixer::LoadFX(const char* path)	// Function to check a sound load, if fail SDL_GetError, if success execute it
{
	Mix_Chunk *sound = nullptr;

	sound = Mix_LoadWAV(path);

	if (!sound)
	{
		
		LOG("Couldn't load fx: %s \n", SDL_GetError());	// Does SDL_GetError work with Mix_LoadWAV?
		SDL_ClearError();
	}

	return sound;
}

bool ModuleMixer::UnloadFx(Mix_Chunk * soundfx)
{
	bool ret = false;

	if (soundfx != nullptr)
	{
		for (int i = 0; i < MAX_MUSIC; ++i)
		{
			if (fx[i] == soundfx)
			{

				Mix_FreeChunk(soundfx);
				fx[i] = nullptr;
				ret = true;
				break;
			}
		}

	}

	return ret;
}