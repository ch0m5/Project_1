#ifndef __ROCK_SUB_BOSS_H__
#define __ROCK_SUB_BOSS_H__

#include "Enemy.h"
#include "NewPath.h"

class Rock_Sub_Boss : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = false;
	int original_y = 0;
	Animation fly;

	Path Path;

	int posx;
	int posy;

public:
	Rock_Sub_Boss(int x, int y);
	virtual void OnCollision(Collider* collider) override;
	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	void Fire();

		int maxShots = 50;
	int currentShot = 0;

	bool dead = false;
	uint score = 1000;
};

#endif // _Drill_Up_