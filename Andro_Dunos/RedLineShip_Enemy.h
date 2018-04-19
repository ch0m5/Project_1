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

	RedLineShip_Enemy(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();

};

#endif // __REDLINESHIP_ENEMY_H__
