#ifndef __WHITEORANGETURRET_ENEMY_H__
#define __WHITEORANGETURRET_ENEMY_H__

#include "Enemy.h"
#include "NewPath.h"

class Down_WhiteOrangeTurret : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9;
	Path Down_WhiteOrangeTurret_Path;

	int Down_WhiteOrangeTurret_posx;
	int Down_WhiteOrangeTurret_posy;

public:
	virtual void OnCollision(Collider* collider) override;
	Down_WhiteOrangeTurret(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	float resultingAngle();

	uint score = 200;
	bool dead = false;

	void Fire();

};

#endif 