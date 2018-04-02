#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

ModuleRender::ModuleRender() : Module()
{}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	// load a texture 
	
	map1Text = App->textures->Load("Sprites/Backgrounds/1_FullMap.png");
	background1Text = App->textures->Load("Sprites/Backgrounds/1_Background1.png");
	ship1Text = App->textures->Load("Sprites/Ship_1/1_3_Ship.png");
	/*mediumBulletText = App->textures->Load("Sprites/Medium_Blue.png");
	smallBulletText = App->textures->Load("Sprites/Small_Blue.png");
	ship1UpText = App->textures->Load("Sprites/1_1_Ship_Up.png");
	ship1TiltUpText = App->textures->Load("Sprites/1_2_Ship_Tilt_Up.png");
	ship1TiltDownText = App->textures->Load("Sprites/1_4_Ship_Tilt_Down.png");
	ship1DownText = App->textures->Load("Sprites/1_5_Ship_Down.png");*/
	

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	//Clear the screen to black before starting every frame

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);


	//Blit texture to check functionality
	SDL_Rect background1Rect = { 0, 0, 1684, 85 };
	SDL_Rect map1Rect = { 0, 0, 9305, 563 };
	SDL_Rect ship1Rect = { 0, 0, 27, 17 };

	//SDL_RenderCopy(renderer, tex, &rect, NULL);
	Blit(background1Text, horizontalCounter1, 118, &background1Rect);
	Blit(map1Text, horizontalCounter1, -115, &map1Rect);
	Blit(ship1Text, horizontalCounter2, 150, &ship1Rect);

	horizontalCounter1--;
	horizontalCounter2++;


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	//Switch buffers so we actually render

	SDL_RenderPresent(renderer);

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section)
{
	bool ret = true;
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;

	if(section != nullptr)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}

	if(SDL_RenderCopy(renderer, texture, section, &rect) != 0)
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
