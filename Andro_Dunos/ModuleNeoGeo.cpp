#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleNeoGeo.h"
#include "ModulePlayer1.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMainMenu.h"
#include "ModuleInput.h"
#include "ModuleMixer.h"


ModuleNeoGeo::ModuleNeoGeo()
{
	current_animation = NULL;

	NeoGeoAnim.PushBack({ 0, 0, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 40, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 80, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 120, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 160, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 200, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 240, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 280, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 320, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 360, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 400, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 440, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 480, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 520, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 560, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 600, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 640, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 680, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 720, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 760, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 800, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 840, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 880, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 920, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 960, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1000, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1040, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1080, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1120, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1160, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1200, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1240, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1280, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1320, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1360, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1400, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1440, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1480, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1520, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1560, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1600, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1640, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1680, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1720, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1760, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1800, 227, 40 });
	NeoGeoAnim.PushBack({ 0, 1840, 227, 40 });

	NeoGeoAnim.loop = false;
	NeoGeoAnim.speed = 0.3f;
}

ModuleNeoGeo::~ModuleNeoGeo()
{}

// Load assets
bool ModuleNeoGeo::Start()
{
	LOG("Loading music and textures");
	App->mixer->LoadMusic("Assets/Audio/neoGeo.ogg");
	graphics = App->textures->Load("Assets/Sprites/NeoGeo/neogeo.png");
	return true;
}

// UnLoad assets
bool ModuleNeoGeo::CleanUp()
{
	LOG("Unloading NeoGeo scene");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleNeoGeo::Update()

{
	current_animation = &NeoGeoAnim;
	SDL_Rect r = current_animation->GetCurrentFrame();
	// Draw everything --------------------------------------
	App->render->Blit(graphics, 44, 80, &r, 1);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
	{
		App->fade->FadeToBlack(App->neogeo, App->mainMenu, 1.0f);
	}

	return UPDATE_CONTINUE;
}