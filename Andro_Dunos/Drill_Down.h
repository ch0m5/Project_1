#ifndef __DRILL_DOWN_H__
#define __DRILL_DOWN_H__

#include "Enemy.h"
#include "NewPath.h"

class Drill_Down : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = false;
	int original_y = 0;
	Animation fly;

	Path Path;

	int posx;
	int posy;

public:
	Drill_Down(int x, int y);
	virtual void OnCollision(Collider* collider) override;
	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	/*void Fire();*/

	bool dead = false;
	uint score = 100;
};

#endif // _Drill_Down_