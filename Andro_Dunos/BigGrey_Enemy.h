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
	virtual void OnCollision(Collider* collider) override;
	BigGrey_Enemy(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	//void Fire();
	bool dead = false;
	uint score = 150;

	int maxShots = 50;
	int currentShot = 0;

	int maxDistance = 30;

	void Fire();
};

#endif // __BIGGREY_ENEMY_H__
