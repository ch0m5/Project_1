#ifndef __POWERUP_ENEMY_H__
#define __POWERUP_ENEMY_H__

#include "Enemy.h"
#include "NewPath.h"

class PowerUp_Enemy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
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
};

#endif // __POWERUP_ENEMY_H__

