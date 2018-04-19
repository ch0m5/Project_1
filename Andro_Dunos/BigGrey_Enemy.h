#ifndef __BIGGREY_ENEMY_H__
#define __BIGGREY_ENEMY_H__

#include "Enemy.h"
#include "NewPath.h"

class BigGrey_Enemy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = false;
	int original_y = 0;
	Animation fly;

	Path BigGrey_Path;

	int BigGrey_posx;
	int BigGrey_posy;

public:

	BigGrey_Enemy(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	//void Fire();
};

#endif // __BIGGREY_ENEMY_H__
