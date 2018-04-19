#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()	//@CarlesHoms
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);
	secondPlayerState = true; //statr with one player

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
		SDL_ClearError();
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if (keyboard[SDL_SCANCODE_ESCAPE])		// If the Escape key is pressed, exit game
		return update_status::UPDATE_STOP;
	
	if (App->input->keyboard[SDL_SCANCODE_F1] == KEY_DOWN) //enter debug mode @andres
	{
		debugMode = !debugMode;
	}
	if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN && debugMode == true) //enter debug mode @andres
	{
		coliderView = !coliderView;
	}


	while (SDL_PollEvent(&e))	// If the windows application is required to quit (press x button), exit game
	{
		if (e.type == SDL_QUIT)
		{
			return update_status::UPDATE_STOP;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}