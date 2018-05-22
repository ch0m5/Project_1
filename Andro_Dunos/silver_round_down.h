#ifndef __SILVER_ROUND_DOWN_H__
#define __SILVER_ROUND_DOWN_H__

#include "Enemy.h"
#include "NewPath.h"

class Silver_Round_Down : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = false;
	int original_y = 0;
	Animation left;
	Animation leftUp;
	Animation leftUP2;
	Animation down;
	Animation upRight;
	Animation upRight2;
	Animation right;

	Path Silver_Path;

	int Silver_posx;
	int Silver_posy;

public:
	Silver_Round_Down(int x, int y);
	virtual void OnCollision(Collider* collider) override;
	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();
	/*void Fire();*/

	bool dead = false;
	uint score = 100;
};

#endif // _ENEMY_GREYBALL_S_
