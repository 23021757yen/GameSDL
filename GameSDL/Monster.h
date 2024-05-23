#ifndef MONSTER_H_
#define MONSTER_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "Menu.h"


class Character;

class Monster : BaseObject
{
public:
	Monster(float p_x,float p_y);
	~Monster();

	bool Load_Img(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des, SDL_Rect& camera);
	void GetHit(Character& p_player, SDL_Rect& camera);
	void Gravity();
	void Update(std::vector<map>& map_data,Character & p_player, SDL_Rect& camera);
	void MoveToPlayer(std::vector<map>& map_data, Character& p_player);
	void Set_Map_XY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }; 
	SDL_Rect getCollision() const { return collision; };
	float getX() const { return x_pos; };
	float getY() const { return y_pos; };
	bool isAttacking() { if (cnt_attack / delay == 4) return true; else return false; }
	SDL_RendererFlip getFlip() const { return flip_type_; };
	bool isDeath() const { if (cnt_die >= 29) return death_; else return false; };//chet do bi ban
	bool isDeath_() const { if (cnt_die >= 29) return death_boss; else return false; };// danh dau chet cho gan boss
	int GetCntAtack() const { return cnt_attack; };


private:

	float x_val;
	float y_val;

	float x_pos;
	float y_pos;

	float x_start;
	float y_start;

	float map_x_;
	float map_y_;

	int delay = 3;
	 
	int MARK_MONS = 10;

	const int FRAME_WIDTH = 192;
	const int FRAME_HEIGHT = 128;
	const int MONSTER_WIDTH = 32;
	const int MONSTER_HEIGHT = 64;
	const int MONSTER_VAL = 3;
	const int MAX_X = 50;
	//const int max_x = 50;

	bool run_ = false;
	bool attack_ = false;
	bool beinghit_ = false;
	bool death_ = false;
	bool idle_ =true ;
	bool on_ground = false;
	bool fall_ = false;
	bool death_boss = false;

	static const int FRAME_IDLE = 6;
	static const int FRAME_RUN = 8 ;
	static const int FRAME_ATTACK = 8 ;
	static const int FRAME_HIT = 4 ;
	static const int FRAME_DEATH = 10 ;

	int cnt_idle = 0;
	int cnt_run = 0;
	int cnt_attack = 0;
	int cnt_gotgun = 0;
	int cnt_die = 0;
	
	int count_mon = 0;

	int ground[2] = { 0 };
	SDL_Rect idle_clip[FRAME_IDLE];
	SDL_Rect run_clip[FRAME_RUN];
	SDL_Rect attack_clip[FRAME_ATTACK];
	SDL_Rect beinghit_clip[FRAME_HIT];
	SDL_Rect death_clip[FRAME_DEATH];

	SDL_Rect collision;

	SDL_Texture* p_text = NULL;

	int mons[20];
	int levelSTT = 0;
	float distanceToPlayer = 0;
};


#endif // !MONSTER_H_
