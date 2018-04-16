#ifndef __ENEMY_13_GREYBALL_H__
#define __ENEMY_13_GREYBALL_H__

#include "Enemy.h"

class Enemy_13_Greyball : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_13_Greyball(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	void Fire();
};

#endif // __ENEMY_EXAMPLE_H__