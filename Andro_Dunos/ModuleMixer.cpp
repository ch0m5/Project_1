#include "Globals.h"
#include "Application.h"
#include "ModuleMixer.h"
#include "SDL/include/SDL.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_mixer/libx86/SDL2_mixer.lib")

#define MUSIC 10
#define FX 50

ModuleMixer::ModuleMixer() : Module() {}

ModuleMixer::~ModuleMixer() {}

bool ModuleMixer::Init() 
{

	LOG("Creating the music");
	bool ret = true;

	if (SDL_Init(SDL_INIT_AUDIO) !=0) 
	{
		LOG("Broken: %s ", SDL_GetError());
		ret = false;
	}

	
	else	
	{
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		soundtrack = Mix_LoadMUS("Music/04_Stage_1-The Moon-Loop.ogg");
		Mix_VolumeMusic(MUSIC);
		Mix_PlayMusic(soundtrack, -1);
		

		shot = Mix_LoadWAV("Music/Laser_Shot_Type-1_(Main_Ships).wav");
		Mix_VolumeChunk(shot, FX);
	
	}

	if (soundtrack == NULL) 
	{
		LOG("Broken: %s", SDL_GetError());
		ret = false;
	}

	return ret;
	
}//@andressala

bool ModuleMixer::CleanUp() 
{

	if (soundtrack != nullptr) 
	{
		Mix_FreeMusic(soundtrack);

	}
	if (shot != nullptr)
	{
		Mix_FreeChunk(shot);
		Mix_Quit();
	}

	return true;
}//@andressala

update_status ModuleMixer::Update()
{

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		
		Mix_PlayChannel(3, shot, 0);
		// this function must be change once the array of laser is created
		
	}
	return update_status::UPDATE_CONTINUE;
}//@andressala