#pragma once
#ifndef __POWERUP_BONUS_H__
#define __POWERUP_BONUS_H__

#include "Enemy.h"
#include "NewPath.h"

class PowerUp_Bonus : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
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
	uint score = 100;
	bool dead = false;
};

#endif // __POWERUP_BONUS_H__

