#include "Globals.h"
#include "Application.h"
#include "ModuleMixer.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleMainMenu.h"

#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

#define MUSIC 60	// Volume values
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
		// Initialize Audio
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

		/*soundtrack1 = Mix_LoadMUS("Music/04_Stage_1-The Moon-Loop.ogg");
		soundtrack2 = Mix_LoadMUS("Music/07_Stage_2 -Mechanized-Unit-Loop.ogg");
		soundtrack3 = Mix_LoadMUS("Music/18_Game_Over.ogg");*/
		//
		//Mix_PlayMusic(soundtrack0, 1);
		//
	}

	return ret;
}

bool ModuleMixer::Start()	// Here we load and start the first music track and load all other FX sounds
{
	// Music
	LoadMusic(soundtrack0, "Music/02_Title.ogg");
	
	//soundtrack0 = Mix_LoadMUS("Music/02_Title.ogg");
	//if (soundtrack0 == NULL/* || soundtrack1==NULL || soundtrack2==NULL || soundtrack3==NULL*/)
	//{
		//LOG("Broken: %s", SDL_GetError());
	//}

	// Sounds
	shot = Mix_LoadWAV("Music/Laser_Shot_Type-1_(Main_Ships).wav");
	LoadSound(shot);

	// Sounds
	//shot = Mix_LoadWAV("Music/Laser_Shot_Type-1_(Main_Ships).wav");
	//Mix_VolumeChunk(shot, FX);
	

	return true;
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
	}

	Mix_Quit();

	return true;
}

update_status ModuleMixer::Update()
{
	// Kaser FX when pressing space
	if (App->input->keyboard[SDL_SCANCODE_P] == 1 && currentScreen != MAIN_MENU)
	{
		Mix_PlayChannel(3, shot, 0);	
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)	// When Spacebar is pressed, change currentScreen to the next and signal that the music must stop
	{
		currentScreen++;

		musicRunning == false;

		if (currentScreen == END_REACHED)
			currentScreen = MAIN_MENU;
	}

 	if (currentScreen == MAIN_MENU && musicRunning == false)	// Condition for every stage so it initializes the music (and sounds?) needed.
	{
		LoadMusic(soundtrack0, "Music/02_Title.ogg");
		
		//soundtrack0 = Mix_LoadMUS("Music/02_Title.ogg");
		//Mix_FadeInMusic(soundtrack0, 1, 1000);
		//Mix_VolumeMusic(MUSIC);

		musicRunning = true;
	}

	else if (currentScreen == STAGE_1 && musicRunning == false)
	{
		LoadMusic(soundtrack0, "Music/04_Stage_1-The Moon-Loop.ogg");

		//soundtrack0 = Mix_LoadMUS("Music/04_Stage_1-The Moon-Loop.ogg");
		//Mix_FadeInMusic(soundtrack0, 1, 1000);
		//Mix_VolumeMusic(MUSIC);

		musicRunning = true;
	}

	else if (currentScreen == STAGE_2 && musicRunning == false)
	{
		LoadMusic(soundtrack0, "Music/07_Stage_2 -Mechanized-Unit-Loop.ogg");

		//soundtrack0 = Mix_LoadMUS("Music/07_Stage_2 -Mechanized-Unit-Loop.ogg");
		//Mix_FadeInMusic(soundtrack0, 1, 1000);
		//Mix_VolumeMusic(MUSIC);

		musicRunning = true;
	}

	else if (currentScreen == CRASHED_SHIP && musicRunning == false)
	{
		LoadMusic(soundtrack0, "Music/18_Game_Over.ogg");

		//soundtrack0 = Mix_LoadMUS("Music/18_Game_Over.ogg");
		//Mix_FadeInMusic(soundtrack0, 1, 1000);
		//Mix_VolumeMusic(MUSIC);

		musicRunning = true;
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleMixer::LoadMusic(Mix_Music* music, char* audioPath)	// Function to check a music file load and send an SDL_Error otherwise
{
	bool ret = true;

	music = Mix_LoadMUS(audioPath);

	if (music == nullptr)
	{
		LOG("Couldn't load music: %s", SDL_GetError());
		ret = false;
	}

	else
	{
		Mix_FadeInMusic(music, 1, 1000);
		Mix_VolumeMusic(MUSIC);
	}
}

void ModuleMixer::LoadSound(Mix_Chunk* sound)	// Function to check a sound file load and send an SDL_Error otherwise
{
	bool ret = true;

	if (sound == nullptr)
	{
		LOG("Couldn't load sound: %s", SDL_GetError());	// Does SDL_GetError work with Mix_LoadWAV?
		ret = false;
	}

	else
	{
		Mix_VolumeChunk(sound, FX);
	}
}