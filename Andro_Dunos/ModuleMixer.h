#ifndef __ModuleMixer_H__
#define __ModuleMixer_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleInput.h"	//@XaviMarin @AndresSaladrigas

#define MUSICVol 50	// Volume values
#define FXVol 90
#define MAX_MUSIC 10  //Max number of elements
#define MAX_FX 60

typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

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
	
public:

	bool musicRunning = false;		
	Mix_Music * soundtrack[MAX_MUSIC];
	Mix_Chunk * fx[MAX_FX];

};

#endif
