#ifndef _MODULE_SHIELD_P1_H_
#define _MODULE_SHIELD_P1_H_

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

// Shield used defines
#define RADIUS (24)

struct SDL_Texture;

class ModuleShieldsP1 : public Module {
public:
	ModuleShieldsP1();
	~ModuleShieldsP1();

	void OnCollision(Collider* col_1, Collider* col_2);
	bool Start();
	update_status Update();
	bool CleanUp();

	void spinTheShields(Animation* shield1Animation, Animation* shield2Animation, int greenLevel);
	int checkShieldsLife(int life);

public:
	int shieldWidth = 14;
	int shieldHeight = 16;

	SDL_Texture* graphics = nullptr;

	//Animation base_anim, lvl1, lvl2, lvl3;

	//Front
	Animation frontRed, frontGreen, frontYellow;

	//Back
	Animation backRed, backGreen, backYellow;

	//Top
	Animation topRed, topGreen, topYellow;

	//Bottom
	Animation bottomRed, bottomGreen, bottomYellow;

	//Rotate
	Animation rotateRed[8], rotateGreen[8], rotateYellow[8];

	int life = 0;	// carles edit
	float angle;

	Animation* shield1Animation = nullptr;
	Animation* shield2Animation = nullptr;

	Collider* shield1Collider = nullptr;
	Collider* shield2Collider = nullptr;

	iPoint shield1Pos, shield2Pos;

	//iPoint pos1_t1[8], pos2_t1[8];
	//int circ;
	//int life = 3;
};

#endif // !_MODULE_SHIELD_