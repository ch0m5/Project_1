#ifndef __BOSS_H__
#define __BOSS_H__

#include "p2Point.h"
#include "Animation.h"


struct SDL_Texture;
struct Collider;

class Boss
{
protected:
	Animation* animation = nullptr;
	Collider* collider = nullptr;

public:
	iPoint position;

	int life = 1;	// Standard value for all enemies

public:
	Boss(int x, int y);
	virtual ~Boss();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual void Fire() {};


};

#endif // __BOSS_H__