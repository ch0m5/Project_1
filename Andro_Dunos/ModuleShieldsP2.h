#ifndef _MODULE_SHIELD_P2_H_
#define _MODULE_SHIELD_P2_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleMixer.h"

struct SDL_Texture;

class ModuleShieldsP2 : public Module {
public:
	ModuleShieldsP2();
	~ModuleShieldsP2();

	void OnCollision(Collider* col_1, Collider* col_2);
	bool Start();
	update_status Update();
	bool CleanUp();

	void spinTheShields(Animation* shield1Animation, Animation* shield2Animation, int greenLevel);
	int checkShieldsLife(int life);

public:
	int shieldWidth = 16;
	int shieldHeight = 16;

	SDL_Texture* graphics = nullptr;

	//Front
	Animation frontRed, frontGreen, frontYellow;
	//Back
	Animation backRed, backGreen, backYellow;
	//Top
	Animation topRed, topGreen, topYellow;
	//Bottom
	Animation bottomRed, bottomGreen, bottomYellow;
	//Rotate
	Animation topRight, topLeft, bottomRight, bottomLeft;

	Mix_Chunk *shieldsEquipping = nullptr;
	Mix_Chunk *shieldsEquipped = nullptr;
	Mix_Chunk *shieldsTypeChange = nullptr;

	int life = 0;	// carles edit
	float angle;

	Animation* shield1Animation = nullptr;
	Animation* shield2Animation = nullptr;

	Collider* shield1Collider = nullptr;
	Collider* shield2Collider = nullptr;

	iPoint shield1Pos, shield2Pos;
};

#endif // !_MODULE_SHIELD_