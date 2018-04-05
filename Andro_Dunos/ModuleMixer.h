#ifndef __MModuleMixer_H__
#define __ModuleMixer_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleInput.h"

typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

enum StageStatus
{
	MAIN_MENU,
	STAGE_1,
	STAGE_2,
	CRASHED_SHIP
};

class ModuleMixer : public Module
{

public:
	ModuleMixer();
	~ModuleMixer();

	bool Init();
	update_status Update();
	bool CleanUp();
	

public:
	int currentScreen = MAIN_MENU;
	bool musicRunning = false;

	Mix_Music * soundtrack0 = nullptr;
	Mix_Music * soundtrack1 = nullptr;
	Mix_Music * soundtrack2 = nullptr;
	Mix_Music * soundtrack3 = nullptr;
	Mix_Chunk* shot = nullptr;

};

#endif
