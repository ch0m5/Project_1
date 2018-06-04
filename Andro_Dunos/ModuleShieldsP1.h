//#ifndef _MODULE_SHIELD_P1_H_
//#define _MODULE_SHIELD_P1_H_
//
//#include "Module.h"
//#include "Animation.h"
//#include "Globals.h"
//
//// Shield used defines	// TEMPORAL, REMOVE NEEDED
//#define ROT_STEPS (8)
//#define RADIUS (27)
//
//// Temporal	// TEMPORAL, REMOVE NEEDED
//int give_position_y(int radius, float angle_deg) // preparations for later
//{
//	int center_y = 0; // to be determined
//
//	float rad = ((angle_deg * PI) / 180);
//
//	return radius * sinf(rad)*(-1) + center_y;
//
//}
//
//int give_position_x(int radius, float angle_deg) // preparations for later
//{
//	int center_x = 5; // to be determined
//
//	float rad = ((angle_deg * PI) / 180);
//
//	return radius * cosf(rad)*(1) + center_x;
//}
//// Temporal
//
//struct SDL_Texture;
//
//class ModuleShieldsP1 : public Module {
//public:
//	ModuleShieldsP1();
//	~ModuleShieldsP1();
//
//	void OnCollision(Collider* col_1, Collider* col_2);
//	bool Start();
//	update_status Update();
//	bool CleanUp();
//
//public:
//	SDL_Texture* graphics = nullptr;
//
//	Animation base_anim, lvl1, lvl2, lvl3;
//	Animation rotation_lvl1[ROT_STEPS];
//	Animation rotation_level[ROT_STEPS];
//
//	Animation* current_lvl;
//	int timer;
//	int life;	// carles edit
//
//	Collider* collider1;
//	Collider* collider2;
//
//	iPoint position1, position2;
//	iPoint pos1_t1[8], pos2_t1[8];
//	int circ;
//	//int life = 3;
//};
//
//#endif // !_MODULE_SHIELD_