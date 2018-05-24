#ifndef __MODULEBOSS_H__
#define __MODULEBOSS_H__

#include "Module.h"			// Following: Includes of all enemy headers
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_BOSS 500

enum BOSS_TYPES
{
	YES_TYPE=0,
	TYPE
	


};

class Boss;

struct BossInfo
{
	BOSS_TYPES type = BOSS_TYPES::YES_TYPE;
	int x, y;
};

class ModuleBoss : public Module
{
public:

	ModuleBoss();
	~ModuleBoss();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddBoss(BOSS_TYPES type, int x, int y);

	Mix_Chunk *explosion1 = nullptr;
	Mix_Chunk *explosion2 = nullptr;
	Mix_Chunk *enemyHit = nullptr;



private:

	void SpawnBoss(const BossInfo& info);

private:

	BossInfo queue[MAX_BOSS];
	Boss* Boss[MAX_BOSS];
	SDL_Texture* sprites;

};

#endif // __ModuleBoss_H__