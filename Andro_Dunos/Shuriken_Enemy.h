#ifndef __SHURIKEN_ENEMY_H__
#define __SHURIKEN_ENEMY_H__

#include "Enemy.h"
#include "NewPath.h"

class Shuriken_Enemy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	Path ShurikenEnemy_Path;

	int ShurikenEnemy_posx;
	int ShurikenEnemy_posy;

public:
	virtual void OnCollision(Collider* collider) override;
	Shuriken_Enemy(int x, int y);

	// Enemy Hitbox
	int hitboxWidth;
	int hitboxHeight;

	void Move();

	uint score = 200;
	bool dead = false;

	//void Fire();

};

#endif // __SHURIKEN_ENEMY_H__

