#ifndef CHARACTER_H_
#define CHARACTER_H_

#pragma once

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "Menu.h"
#include "Item.h"
#include "Monster.h"

class Menu;
class Monster;

class Character : BaseObject
{
public:
	Character();
	~Character();
	enum
	{
		shootSFX = 0,
		jumpSFX = 1,
		hitSFX = 2,
	};

	bool Load_Img(std::string path, SDL_Renderer* screen);
	void Show_Frames(SDL_Renderer* des, SDL_Rect& camera);
	void GetHit(std::vector<Monster*>& monsterList, Mix_Chunk* p_sfx[],Menu menu,SDL_Rect & camera);
	void KeyBoard(SDL_Event& e, Mix_Chunk* p_sfx[],Menu menu );
	void HandleCamera(SDL_Rect& camera, int& cam_val);
	void Update(std::vector<map>& map_data, std::vector<Monster*>& monsterList, Mix_Chunk* p_sfx[], Menu menu, SDL_Rect& camera);
	void Set_Map_XY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; };
	void Jump();
	void Gravity();
	SDL_Rect getCollision() const { return collision; };
	float getX() const { return x_pos; };
	float getY() const { return y_pos; };
	bool isDeath() const { if (deathCounter >= 23) return death_; else return false; };
	
	std::vector<Item*> GetBulletList() const { return bulletList; };
	void SetBulletList(std::vector<Item*>& p_bulletList) { bulletList = p_bulletList; };

	int Mark_cha()const { return MARK_CHA; };
	

	void ResetCharacter()
	{
		x_pos = 15* TILE_SIZE;
		y_pos = 12 * TILE_SIZE;
		death_ = false;
		MARK_CHA = 4;
		flip_type_ = SDL_FLIP_NONE;
		x_val = 0;
		y_val = 0;
	}

private:
	float x_pos;
	float y_pos;

	float x_val ;
	float y_val ;

	int map_x_;
	int map_y_;

	const int PLAYER_WIDTH = 32;
	const int PLAYER_HEIGHT = 64;

	static const int FRAME_RUN = 6;
	static const int FRAME_JUMP = 2;
	static const int FRAME_DEATH = 8;
	static const int FRAME_IDLE = 5;

	SDL_Rect run_clip[FRAME_RUN];
	SDL_Rect jump_clip[FRAME_JUMP];
	SDL_Rect death_clip[FRAME_DEATH];
	SDL_Rect idle_clip[FRAME_IDLE];

	SDL_Rect collision;

	int delay_ = 3;

	bool idle_ = false;
	bool run_ = false;
	bool jump_ = false;
	bool death_ = false;
	bool fall_ = false;
	bool on_ground_ = false;

	int idleCounter = 0;
	int runCounter = 0;
	int jumpCounter = 0;
	int fallCounter = 1;
	int deathCounter = 0;

	int MARK_CHA = 4;
	int levelSTT = 0;
	int ground[2] = {0};
	
	const int FRAME_WIDTH = 96 ;
	const int FRAME_HEIGHT = 96;
	SDL_Texture* p_text = NULL;

	std::vector<Item*> bulletList;
	int lastTakenDmg = 0;
};

#endif 

