//#include <math.h>
//#include "p2Point.h"
//#include "Globals.h"
//#include "Application.h"
//#include "ModuleShieldsP1.h"
//#include "ModuleTextures.h"
//#include "ModuleRender.h"
//#include "ModuleParticles.h"
//#include "ModuleCollision.h"
//#include "ModulePlayer1.h"
//#include "ModulePlayer2.h"
//#include "ModuleTextures.h"
//#include "ModuleMixer.h"
//
//ModuleShieldsP1::ModuleShieldsP1()
//{
//
//	circ = 0;
//
//	// ---- Animation for the base od the shield
//	base_anim.PushBack({ 0, 0, 9, 16 });
//	base_anim.PushBack({ 11, 0, 9, 16 });
//	base_anim.PushBack({ 22, 0, 9, 16 });
//	base_anim.PushBack({ 33, 0, 9, 16 });
//	base_anim.PushBack({ 44, 0, 9, 16 });
//	base_anim.PushBack({ 55, 0, 9, 16 });
//	base_anim.loop = true;
//	base_anim.speed = 0.2f;
//
//	// ---- Animation for lvl1 LaserShield (Red)
//	lvl1.PushBack({ 46, 18, 5, 14 });
//	lvl1.PushBack({ 0, 18, 5, 14 });
//	lvl1.PushBack({ 7, 18, 5, 14 });
//	lvl1.PushBack({ 0, 18, 5, 14 });
//	lvl1.loop = true;
//	lvl1.speed = 0.5f;
//
//	// ---- Animation for the TYPE-1 laser's shield (rotating)
//	rotation_lvl1[0].PushBack({ 0,0,9,16 });
//	rotation_lvl1[0].PushBack({ 11,0,9,16 });
//	rotation_lvl1[0].PushBack({ 22,0,9,16 });
//	rotation_lvl1[0].PushBack({ 33,0,9,16 });
//	rotation_lvl1[0].PushBack({ 44,0,9,16 });
//	rotation_lvl1[0].PushBack({ 57,0,9,16 });
//	rotation_lvl1[0].loop = true;
//	rotation_lvl1[0].speed = 0.25f;
//
//	rotation_lvl1[1].PushBack({ 128,16,9,16 });
//	rotation_lvl1[1].PushBack({ 117,16,9,16 });
//	rotation_lvl1[1].PushBack({ 106,16,9,16 });
//	rotation_lvl1[1].PushBack({ 95,16,9,16 });
//	rotation_lvl1[1].PushBack({ 84,16,9,16 });
//	rotation_lvl1[1].PushBack({ 72,16,9,16 });
//	rotation_lvl1[1].loop = true;
//	rotation_lvl1[1].speed = 0.25f;
//
//	rotation_lvl1[2].PushBack({ 109,52,14,16 });
//	rotation_lvl1[2].PushBack({ 109,75,15,14 });
//	rotation_lvl1[2].PushBack({ 109,98,14,16 });
//	rotation_lvl1[2].PushBack({ 107,16,16,15 });
//	rotation_lvl1[2].loop = true;
//	rotation_lvl1[2].speed = 0.25f;
//
//	rotation_lvl1[3].PushBack({ 87,50,14,16 });
//	rotation_lvl1[3].PushBack({ 84,73,15,14 });
//	rotation_lvl1[3].PushBack({ 86,95,14,16 });
//	rotation_lvl1[3].PushBack({ 86,117,16,15 });
//	rotation_lvl1[3].loop = true;
//	rotation_lvl1[3].speed = 0.25f;
//
//	rotation_lvl1[4].PushBack({ 56,45,9,16 });
//	rotation_lvl1[4].PushBack({ 56,56,9,16 });
//	rotation_lvl1[4].PushBack({ 56,67,9,16 });
//	rotation_lvl1[4].PushBack({ 56,78,9,16 });
//	rotation_lvl1[4].PushBack({ 56,89,9,16 });
//	rotation_lvl1[4].PushBack({ 56,102,9,16 });
//	rotation_lvl1[4].loop = true;
//	rotation_lvl1[4].speed = 0.25f;
//
//	rotation_lvl1[5].PushBack({ 3,98,16,9 });
//	rotation_lvl1[5].PushBack({ 3,87,16,9 });
//	rotation_lvl1[5].PushBack({ 3,76,16,9 });
//	rotation_lvl1[5].PushBack({ 3,67,16,9 });
//	rotation_lvl1[5].PushBack({ 3,54,16,9 });
//	rotation_lvl1[5].PushBack({ 3,42,16,9 });
//	rotation_lvl1[5].loop = true;
//	rotation_lvl1[5].speed = 0.25f;
//
//	rotation_lvl1[6].PushBack({ 109,52,14,16 });
//	rotation_lvl1[6].PushBack({ 109,75,15,14 });
//	rotation_lvl1[6].PushBack({ 109,98,14,16 });
//	rotation_lvl1[6].PushBack({ 107,16,16,15 });
//	rotation_lvl1[6].loop = true;
//	rotation_lvl1[6].speed = 0.25f;
//
//	rotation_lvl1[7].PushBack({ 87,50,14,16 });
//	rotation_lvl1[7].PushBack({ 84,73,15,14 });
//	rotation_lvl1[7].PushBack({ 86,95,14,16 });
//	rotation_lvl1[7].PushBack({ 86,117,16,15 });
//	rotation_lvl1[7].loop = true;
//	rotation_lvl1[7].speed = 0.25f;
//
//	for (int counter = 0; counter < ROT_STEPS; counter++)
//	{
//		rotation_level[counter] = rotation_lvl1[counter];
//	}
//
//
//	//// ---- Animation for lvl2 LaserShield (Yellow)
//	//lvl2.PushBack({ 46, 18, 5, 14 });
//	//lvl2.PushBack({ 30, 18, 5, 14 });
//	//lvl2.PushBack({ 36, 18, 5, 14 });
//	//lvl2.PushBack({ 30, 18, 5, 14 });
//	//lvl2.loop = true;
//	//lvl2.speed = 0.5f;
//
//	//// ---- Animation for lvl3 LaserShield (Green)
//	//lvl3.PushBack({ 46, 18, 5, 14 });
//	//lvl3.PushBack({ 15, 18, 5, 14 });
//	//lvl3.PushBack({ 22, 18, 5, 14 });
//	//lvl3.PushBack({ 15, 18, 5, 14 });
//	//lvl3.loop = true;
//	//lvl3.speed = 0.5f;
//}
//
//ModuleShieldsP1::~ModuleShieldsP1() {}
//
//bool ModuleShieldsP1::Start()
//{
//	bool ret = true;
//	/*
//	graphics = App->textures->Load("Assets/Sprites/player1/shield.png"); //Loads shield image bank
//
//	if (graphics == nullptr)
//		ret = false;
//	*/
//	timer = 0;
//	life = 0;
//
//	switch (App->player1->type) {
//
//		// ---- Stays in front of ship
//	case TYPE_1:
//
//		//give_position_x(radius, deg);
//		//give_position_x(radius, deg);
//
//		pos1_t1[0].x = App->player1->position.x + give_position_x(RADIUS, 0.0);
//		pos1_t1[0].y = App->player1->position.y + give_position_y(RADIUS, 0.0);
//		pos2_t1[0].x = App->player1->position.x + give_position_x(RADIUS, 180.0);
//		pos2_t1[0].y = App->player1->position.y + give_position_y(RADIUS, 180.0);
//
//		position1.x = pos1_t1[0].x;
//		position1.y = pos1_t1[0].y;
//		position2.x = pos2_t1[0].x;
//		position2.y = pos2_t1[0].y;
//
//		break;
//
//		// ---- Stays on either side of the ship
//	case TYPE_2:
//		position1.x = App->player1->position.x + 5;
//		position1.y = App->player1->position.y - 8;
//		position2.x = App->player1->position.x + 5;
//		position2.y = App->player1->position.y + 10;
//		break;
//
//		// ---- Stays in front of ship
//	case TYPE_3:
//		position1.x = App->player1->position.x + 29;
//		position1.y = App->player1->position.y - 8;
//		position2.x = App->player1->position.x + 29;
//		position2.y = App->player1->position.y + 10;
//		break;
//
//		// ---- Stays behind ship
//	case TYPE_4:
//		position1.x = App->player1->position.x + 29;
//		position1.y = App->player1->position.y - 8;
//		position2.x = App->player1->position.x + 29;
//		position2.y = App->player1->position.y + 10;
//		break;
//	}
//
//
//	// ---- Declares colliders for shield parts individually
//	collider1 = App->collision->AddCollider({ position1.x, position1.y, 14, 16 }, COLLIDER_PLAYER_SHIELD, this);
//	collider2 = App->collision->AddCollider({ position2.x, position2.y, 14, 16 }, COLLIDER_PLAYER_SHIELD, this);
//
//
//	return ret;
//}
//
//update_status ModuleShieldsP1::Update()
//{
//
//	/*if (life == 1) current_lvl = &lvl1;
//	else if (life == 2)	current_lvl = &lvl2;
//	else if (life == 3)	current_lvl = &lvl3;
//	*/
//	current_lvl = &lvl1;
//
//	// ---- Keeps realtive position to the ship
//	switch (App->player1->type) {
//
//		// ---- Stays in front of ship
//	case TYPE_1:
//
//		//give_position_y(rad, angle_deg)
//		//give_position_x(rad, angle_deg)
//
//		/*
//		- -	-
//		-	  -		-
//		-		  -			-
//		-		  - 		-
//		--------------------- 0º/360º
//		-		  -			-
//		-		  -			-
//		-	  -		-
//		- -	-
//
//		*/
//		pos1_t1[0].x = App->player1->position.x + give_position_x(RADIUS, 0.0);
//		pos1_t1[0].y = App->player1->position.y + give_position_y(RADIUS, 0.0);
//		pos2_t1[0].x = App->player1->position.x + give_position_x(RADIUS, 180.0);
//		pos2_t1[0].y = App->player1->position.y + give_position_y(RADIUS, 180.0);
//
//		pos1_t1[1].x = App->player1->position.x + give_position_x(RADIUS, 90 + 67.5);
//		pos1_t1[1].y = App->player1->position.y + give_position_y(RADIUS, 90 + 67.5);
//		pos2_t1[1].x = App->player1->position.x + give_position_x(RADIUS, 270 + 67.5);
//		pos2_t1[1].y = App->player1->position.y + give_position_y(RADIUS, 270 + 67.5);
//
//		pos1_t1[2].x = App->player1->position.x + give_position_x(RADIUS, 90 + 45.0);
//		pos1_t1[2].y = App->player1->position.y + give_position_y(RADIUS, 90 + 45.0);
//		pos2_t1[2].x = App->player1->position.x + give_position_x(RADIUS, 270 + 45.0);
//		pos2_t1[2].y = App->player1->position.y + give_position_y(RADIUS, 270 + 45.0);
//
//		pos1_t1[3].x = App->player1->position.x + give_position_x(RADIUS, 90 + 22.5);
//		pos1_t1[3].y = App->player1->position.y + give_position_y(RADIUS, 90 + 22.5);
//		pos2_t1[3].x = App->player1->position.x + give_position_x(RADIUS, 270 + 22.5);
//		pos2_t1[3].y = App->player1->position.y + give_position_y(RADIUS, 270 + 22.5);
//
//		pos1_t1[4].x = App->player1->position.x + give_position_x(RADIUS, 90.0);
//		pos1_t1[4].y = App->player1->position.y + give_position_y(RADIUS, 90.0);
//		pos2_t1[4].x = App->player1->position.x + give_position_x(RADIUS, 270.0);
//		pos2_t1[4].y = App->player1->position.y + give_position_y(RADIUS, 270.0);
//
//		pos1_t1[5].x = App->player1->position.x + give_position_x(RADIUS, 67.5);
//		pos1_t1[5].y = App->player1->position.y + give_position_y(RADIUS, 67.5);
//		pos2_t1[5].x = App->player1->position.x + give_position_x(RADIUS, 180.0 + 67.5);
//		pos2_t1[5].y = App->player1->position.y + give_position_y(RADIUS, 180.0 + 67.5);
//
//		pos1_t1[6].x = App->player1->position.x + give_position_x(RADIUS, 45.0);
//		pos1_t1[6].y = App->player1->position.y + give_position_y(RADIUS, 45.0);
//		pos2_t1[6].x = App->player1->position.x + give_position_x(RADIUS, 180 + 45.0);
//		pos2_t1[6].y = App->player1->position.y + give_position_y(RADIUS, 180.0 + 45.0);
//
//		pos1_t1[7].x = App->player1->position.x + give_position_x(RADIUS, 22.5);
//		pos1_t1[7].y = App->player1->position.y + give_position_y(RADIUS, 22.5);
//		pos2_t1[7].x = App->player1->position.x + give_position_x(RADIUS, 180.0 + 22.5);
//		pos2_t1[7].y = App->player1->position.y + give_position_y(RADIUS, 180.0 + 22.5);
//
//		position1.x = pos1_t1[circ].x;
//		position1.y = pos1_t1[circ].y;
//		position2.x = pos2_t1[circ].x;
//		position2.y = pos2_t1[circ].y;
//		break;
//
//		// ---- Stays on either side of the ship
//	case TYPE_2:
//		position1.x = App->player1->position.x + 5;
//		position1.y = App->player1->position.y - 15;
//		position2.x = App->player1->position.x + 5;
//		position2.y = App->player1->position.y + 17;
//		break;
//
//		// ---- Stays in front of ship
//	case TYPE_3:
//		position1.x = App->player1->position.x + 29;
//		position1.y = App->player1->position.y - 8;
//		position2.x = App->player1->position.x + 29;
//		position2.y = App->player1->position.y + 10;
//		break;
//
//		// ---- Stays behind ship
//	case TYPE_4:
//		position1.x = App->player1->position.x - 16;
//		position1.y = App->player1->position.y - 8;
//		position2.x = App->player1->position.x - 16;
//		position2.y = App->player1->position.y + 10;
//		break;
//	}
//
//	// ---- Updates colliders
//	collider1->SetPos(position1.x, position1.y);
//	collider2->SetPos(position2.x, position2.y);
//
//	SDL_Rect base = base_anim.GetCurrentFrame();
//	SDL_Rect light = current_lvl->GetCurrentFrame();
//
//	timer++;
//
//	// ---- Draw Everything
//	if (App->player1->type == TYPE_1)
//	{
//		App->render->Blit(graphics, position1.x, position1.y, &rotation_level[0].GetCurrentFrame());
//		App->render->Blit(graphics, position2.x, position2.y, &rotation_level[1].GetCurrentFrame());
//
//		if (timer >= 3)
//		{
//			circ++;
//			timer = 0;
//		}
//
//		if (circ > 7)
//		{
//			circ = 0;
//		}
//	}
//
//	else
//	{
//		App->render->Blit(graphics, position1.x, position1.y, &base);
//		App->render->Blit(graphics, position2.x, position2.y, &base);
//		App->render->Blit(graphics, position1.x + 8, position1.y + 1, &light);
//		App->render->Blit(graphics, position2.x + 8, position2.y + 1, &light);
//	}
//
//	return update_status::UPDATE_CONTINUE;
//}
//
//void ModuleShieldsP1::OnCollision(Collider* c1, Collider* c2)
//{
//	if (c1->type == COLLIDER_PLAYER_SHIELD)
//	{
//		if (life > 1)
//			life--;
//
//		else
//		{
//			circ = 0;
//			collider1->to_delete = true;
//			collider2->to_delete = true;
//			Disable();	// Could create problems, maybe a direct deletion is needed
//		}
//	}
//
//}
//
//bool ModuleShieldsP1::CleanUp()
//{
//	// Remove all memory leaks
//	LOG("Unloading shield");
//	App->textures->Unload(graphics);
//
//	//Get rid of colliders;
//	collider1 = nullptr;
//	collider2 = nullptr;
//
//	return true;
//}