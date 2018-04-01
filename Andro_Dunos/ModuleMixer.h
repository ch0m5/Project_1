#ifndef __ModuleMixer_H__
#define __ModuleMixer_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleInput.h"

typedef struct _Mix_Music Mix_Music;
struct Mix_Chunk;

class ModuleMixer : public Module {

public:
	ModuleMixer();
	~ModuleMixer();

	bool Init();
	update_status Update();
	bool CleanUp();

public:

	Mix_Music* soundtrack = nullptr;
	Mix_Chunk* shot = nullptr;

};//@andressala

#endif