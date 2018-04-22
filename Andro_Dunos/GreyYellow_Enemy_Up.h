#ifndef __GREYYELLOW_ENEMY_UP_H__
#define __GREYYELLOW_ENEMY_UP_H__

#include "Enemy.h"
#include "NewPath.h"

class GreyYellow_Enemy_Up : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	Path GreyYellow_Ship_Path;

	int GreyYellow_Ship_posx;
	int GreyYellow_Ship_posy;

public:
	virtual void OnCollision(Collider* collider) override;
	GreyYellow_Enemy_Up(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();

	uint score = 150;
	bool dead = false;

};

#endif // __GREYYELLOW_ENEMY_UP_H___