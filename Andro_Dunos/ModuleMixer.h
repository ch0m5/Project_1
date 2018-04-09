#ifndef __ModuleMixer_H__
#define __ModuleMixer_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleInput.h"	//@XaviMarin

#define MAX_MUSIC 10
#define MAX_FX 60

typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;
/*
enum StageStatus	// Signals which screen we are currently in
{
	MAIN_MENU,
	STAGE_1,
	STAGE_2,
	CRASHED_SHIP,
	END_REACHED
};
*/
class ModuleMixer : public Module
{

public:
	ModuleMixer();
	~ModuleMixer();
	
	bool Init();
	update_status Update();
	bool CleanUp();
	
	Mix_Music * const LoadMusic(const char * path);
	Mix_Chunk * const LoadFX(const char * path);
	/*
	void LoadMusic(Mix_Music* music, char* audioPath);	// Function to check a music load, if fail SDL_GetError, if success execute it
	void LoadSound(Mix_Chunk* sound);	// Function to check a sound load, if fail SDL_GetError, if success execute it
	*/
public:
//	int currentScreen = MAIN_MENU;	// Variable that will update to current screen
	bool musicRunning = false;		// Flag for music playing
	int last_audio = 0;
	Mix_Music * soundtrack[MAX_MUSIC];
	Mix_Chunk * fx[MAX_FX];

};

#endif
