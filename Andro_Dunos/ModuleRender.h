#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status PreUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section = nullptr);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* background1Text;
	SDL_Texture* map1Text;
	SDL_Texture* mediumBulletText;
	SDL_Texture* smallBulletText;
	SDL_Texture* ship1UpText;
	SDL_Texture* ship1TiltUpText;
	SDL_Texture* ship1Text;
	SDL_Texture* ship1TiltDownText;
	SDL_Texture* ship1DownText; //@AndresSala, copied from @Didac

	int horizontalCounter1 = 0, horizontalCounter2 = 0, verticalCounter = 0;
};

#endif //__ModuleRenderer_H__