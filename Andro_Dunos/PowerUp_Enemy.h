#ifndef __POWERUP_ENEMY_H__
#define __POWERUP_ENEMY_H__

#include "Enemy.h"
#include "NewPath.h"

class PowerUp_Enemy : public Enemy
{
private:
	iPoint originalPos;
	Animation left, stop1, leftdown, stop2, leftup, stop3, right, stop4, left2, left3;
	Path PowerUpEnemy_Path;

	int PowerUpEnemy_posx;
	int PowerUpEnemy_posy;

public:
	virtual void OnCollision(Collider* collider) override;
	PowerUp_Enemy(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	uint score = 100;

	bool dead = false;

	int disappear;
};

#endif // __POWERUP_ENEMY_H__

