#ifndef __MModuleMixer_H__
#define __ModuleMixer_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleInput.h"

typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

enum StageStatus	// Signals which screen we are currently in
{
	MAIN_MENU,
	STAGE_1,
	STAGE_2,
	CRASHED_SHIP,
	END_REACHED
};

class ModuleMixer : public Module
{

public:
	ModuleMixer();
	~ModuleMixer();

	void LoadMusic(Mix_Music* music, char* audioPath);	// Function to check a music load, if fail SDL_Error, if success execute it
	void LoadSound(Mix_Chunk* sound);	// Function to check a sound load, if fail SDL_Error, if success execute it

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	

public:
	int currentScreen = MAIN_MENU;	// Variable that will update to current screen
	bool musicRunning = false;		// Flag for music playing

	Mix_Music * soundtrack0 = nullptr;
	Mix_Music * soundtrack1 = nullptr;
	Mix_Music * soundtrack2 = nullptr;
	Mix_Music * soundtrack3 = nullptr;
	Mix_Chunk* shot = nullptr;

};

#endif
