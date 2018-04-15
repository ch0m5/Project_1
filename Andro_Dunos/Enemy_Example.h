#ifndef __ENEMY_EXAMPLE_H__
#define __ENEMY_EXAMPLE_H__

#include "Enemy.h"

class Enemy_Example : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;

public:

	Enemy_Example(int x, int y);

	void Move();
};

#endif // __ENEMY_EXAMPLE_H__