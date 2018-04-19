#ifndef __REDLINESHIP_ENEMY_H__
#define __REDLINESHIP_ENEMY_H__

#include "Enemy.h"
#include "NewPath.h"

class RedLineShip_Enemy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	Path RedLineShip_Path;

	int RedLineShip_posx;
	int RedLineShip_posy;

public:
	virtual void OnCollision(Collider* collider) override;
	RedLineShip_Enemy(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();

	uint score = 200;
	bool dead = false;

};

#endif // __REDLINESHIP_ENEMY_H__
