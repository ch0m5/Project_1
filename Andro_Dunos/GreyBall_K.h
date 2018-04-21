#ifndef __ENEMY_GREYBALL_K_H__
#define __ENEMY_GREYBALL_K__H__

#include "Enemy.h"
#include "NewPath.h"

class Enemy_Greyball_K : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = false;
	int original_y = 0;
	Animation fly;

	Path K_Path;

	int GreyK_posx;
	int GreyK_posy;

public:
	Enemy_Greyball_K(int x, int y);
	virtual void OnCollision(Collider* collider) override;
	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	/*void Fire();*/

	bool dead = false;
	uint score = 100;
	float velocityX = 0;
};

#endif // _ENEMY_GREYBALL_S_