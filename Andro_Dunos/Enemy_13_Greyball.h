#ifndef __ENEMY_13_GREYBALL_H__
#define __ENEMY_13_GREYBALL_H__

#include "Enemy.h"

class Enemy_13_Greyball : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = false;
	int original_y = 0;
	Animation fly;

public:
	Enemy_13_Greyball(int x, int y);
	virtual void OnCollision(Collider* collider) override;
	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	void Fire();

	bool dead = false;
	uint score = 100;
};

#endif // __ENEMY_EXAMPLE_H__