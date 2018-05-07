#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleParticles.h"

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
	SDL_Init(SDL_INIT_GAMECONTROLLER);

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
		if (debugMode == false)
		{
			coliderView =false;
		} 

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

	//CONTROLLER INPUT
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) 
		{
			gamepadP1 = SDL_GameControllerOpen(i);
			if (SDL_GameControllerGetAttached(gamepadP1)) {
				gamepadP1LAxisX = SDL_GameControllerGetAxis(gamepadP1, SDL_CONTROLLER_AXIS_LEFTX);
				gamepadP1LAxisY = SDL_GameControllerGetAxis(gamepadP1, SDL_CONTROLLER_AXIS_LEFTY);
				gamepadP1APressed = SDL_GameControllerGetButton(gamepadP1, SDL_CONTROLLER_BUTTON_A);
				gamepadP1XPressed = SDL_GameControllerGetButton(gamepadP1, SDL_CONTROLLER_BUTTON_X);
				gamepadP1con = true;
				break;
			}
			else 
			{
				SDL_GameControllerClose(gamepadP1);
				gamepadP1 = nullptr;
				gamepadP1con = false;
			}
		}
	}

	//CHECK Left Axis X & Y
	if (gamepadP1LAxisX > 6400)
	{
		keyboard[SDL_SCANCODE_RIGHT] = KEY_STATE::KEY_REPEAT;
	}
	else if (gamepadP1LAxisX < -6400)
	{
		keyboard[SDL_SCANCODE_LEFT] = KEY_STATE::KEY_REPEAT;
	}

	if (gamepadP1LAxisY < -6400)
	{
		keyboard[SDL_SCANCODE_UP] = KEY_STATE::KEY_REPEAT;
	}
	else if (gamepadP1LAxisY > 6400)
	{
		keyboard[SDL_SCANCODE_DOWN] = KEY_STATE::KEY_REPEAT;
	}
	//CHECK P1 Buttons

	if (gamepadP1APressed == true && keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_IDLE)
	{
		keyboard[SDL_SCANCODE_P] = KEY_STATE::KEY_DOWN;
	}

	if (gamepadP1XPressed == true && keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_IDLE)
	{
		keyboard[SDL_SCANCODE_O] = KEY_STATE::KEY_DOWN;
	}
	/*else
	{
	keyboard[SDL_SCANCODE_O] = KEY_STATE::KEY_REPEAT;
	}*/
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}