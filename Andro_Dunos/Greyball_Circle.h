#ifndef __GREYBALL_CIRCLE_H__
#define __GREYBALL_CIRCLE_H__

#include "Enemy.h"
#include "NewPath.h"

class Greyball_Circle : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = false;
	int original_y = 0;
	Animation fly;

	Path S_Path;

	int GreyS_posx;
	int GreyS_posy;

public:
	Greyball_Circle(int x, int y);
	virtual void OnCollision(Collider* collider) override;
	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	/*void Fire();*/

	bool dead = false;
	uint score = 100;
};

#endif // _Greybll_Circle_
