#ifndef __ModuleMixer_H__
#define __ModuleMixer_H__

#include "Module.h"
#include "Globals.h"

typedef struct _Mix_Music Mix_Music;

class ModuleMixer : public Module {

public:
	ModuleMixer();
	~ModuleMixer();

	bool Init();
	bool CleanUp();

public:

	Mix_Music* soundtrack = nullptr;

};

#endif