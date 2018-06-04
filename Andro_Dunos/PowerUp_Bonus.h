#pragma once
#ifndef __POWERUP_BONUS_H__
#define __POWERUP_BONUS_H__

#include "Enemy.h"
#include "NewPath.h"

class PowerUp_Bonus : public Enemy
{
private:
	iPoint originalPos;
	Animation blueMode, blueClose, blueOpen, redMode, redClose, redShine, redOpen;
	Path PowerUpBonus_Path;

	int PowerUpBonus_posx;
	int PowerUpBonus_posy;

public:
	virtual void OnCollision(Collider* collider) override;
	PowerUp_Bonus(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	uint score = 500;
	bool dead = false;
	bool blue = true;
	bool orange = false;
	bool yellow = false;
	bool green = false;
	bool move_init = true;
	uint start_time = 0;
};

#endif // __POWERUP_BONUS_H__
