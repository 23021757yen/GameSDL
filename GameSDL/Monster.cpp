#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"
#include "Monster.h"

Monster::Monster(float p_x, float p_y)
{
	//run_ = true;

	x_val = 0;
	y_val = 0;

	x_pos = p_x;
	y_pos = p_y;

	x_start = p_x;
	y_start = p_y;

	map_x_ = 0;
	map_y_ = 0;

	collision.x = getX() + 80; 
	collision.y = getY() + 64;
	collision.w = 32; 
	collision.h = 64;


	for (int i = 0; i < FRAME_IDLE; i++)
	{
		idle_clip[i] = { i * FRAME_WIDTH, 0 ,FRAME_WIDTH,FRAME_HEIGHT };
	}
	for (int i = 0; i < FRAME_RUN; i++)
	{
		run_clip[i] = { i * FRAME_WIDTH,1 * FRAME_HEIGHT ,FRAME_WIDTH,FRAME_HEIGHT };
	}
	for (int i = 0; i < FRAME_ATTACK; i++)
	{
		attack_clip[i] = { i * FRAME_WIDTH,2 * FRAME_HEIGHT ,FRAME_WIDTH,FRAME_HEIGHT };
	}
	for (int i = 0; i < FRAME_HIT; i++)
	{
		beinghit_clip[i] = { i * FRAME_WIDTH,3 * FRAME_HEIGHT ,FRAME_WIDTH,FRAME_HEIGHT };
	}
	for (int i = 0; i < FRAME_DEATH; i++)
	{
		death_clip[i] = { i * FRAME_WIDTH,4 * FRAME_HEIGHT ,FRAME_WIDTH,FRAME_HEIGHT };
	}

}

Monster :: ~Monster()
{
	Free(); // cậu phải gọi free ở đây để nó huỷ texture đi    do nó là con trỏ nên cần cái này nếu là thường thì ko cần
}


bool Monster:: Load_Img (std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::Load_Img(path, screen);
	return ret;
}

void Monster::Show(SDL_Renderer* des, SDL_Rect& camera)
{

	if (idle_)
	{
		CommonFunc_SDL2::RenderAnimation(des, p_object, x_pos, y_pos, &idle_clip[cnt_idle / delay], &camera, 0, NULL, flip_type_);
		cnt_idle++;
		if (cnt_idle / delay >= FRAME_IDLE)
		{
			cnt_idle = 0;
		}
	}
	else cnt_idle = 0;

	if (run_ || fall_)
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &run_clip[cnt_run / delay], &camera, 0, NULL, flip_type_);
		cnt_run++;
		if (cnt_run / delay >= FRAME_RUN)
		{
			cnt_run = 0;
		}
	}
	else cnt_run = 0;

	if (attack_)
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &attack_clip[cnt_attack / delay], &camera, 0, NULL, flip_type_);
		cnt_attack++;
		if (cnt_attack / delay >= FRAME_ATTACK)
		{
			cnt_attack = 0;
		}
	}
	else cnt_attack = 0;

	if (beinghit_)
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &beinghit_clip[cnt_gotgun / delay], &camera, 0, NULL, flip_type_);
		cnt_gotgun++;
		if (cnt_gotgun / delay >= FRAME_HIT)
		{
			cnt_gotgun = 0;
		}
	}
	else cnt_gotgun = 0;

	if (death_||death_boss)
	{
		CommonFunc_SDL2::RenderAnimation(des,p_object, x_pos, y_pos, &death_clip[cnt_die / delay], &camera, 0, NULL, flip_type_);
		cnt_die++;
		if (cnt_die / delay >= FRAME_DEATH)
		{
			cnt_die = 29;
		}
	}
	else cnt_die = 0;
}

void Monster::Gravity()
{
	if (!on_ground)
	{
		y_val += GRAVITY;
		if (y_val >= MAX_GRAVITY) y_val = MAX_GRAVITY;
	}
	else
	{
		y_val = 0;
	}
}

void Monster::Update(std::vector<map>& map_data, Character& p_player, SDL_Rect& camera)
{
	Gravity();
	if (x_val > 0) flip_type_ = SDL_FLIP_NONE;
	if (x_val < 0) flip_type_ = SDL_FLIP_HORIZONTAL;

	MoveToPlayer(map_data, p_player);
	GetHit(p_player, camera);
	if (x_val != 0 && on_ground && !death_ && !death_boss && !attack_)
	{
		run_ = true;
	}
	else
	{
		run_ = false;
	}
	if (x_val == 0 && on_ground && !death_ && !death_boss && !attack_)
	{
		idle_ = true;
	}
	else
	{
		idle_ = false;
	}

	if (!death_ && !death_boss && y_val > 0 && !on_ground)
	{
		idle_ = false;
		fall_ = true;
	}
	else
	{
		fall_ = false;
	}
	
	if (!death_ && !death_boss && !attack_)
	{
		x_pos += x_val;
		collision.x = getX() + 80;
		if (CommonFunc_SDL2::checkToMap(collision, map_data))
		{
			idle_ = true;
			run_ = false;
			x_pos -= x_val;
			if (distanceToPlayer > 5 * TILE_SIZE)
			{
				x_val *= -1;
			}
			collision.x = getX() + 80;
		}
		
	}
	y_pos += y_val;
	collision.y = getY() + 64;
	if (CommonFunc_SDL2::checkToMap(collision, map_data, on_ground, ground[0], ground[1], levelSTT))
	{
		if (y_val > 0)
		{
			y_pos = ground[1] * TILE_SIZE - 192 + 64;

			if (fall_)
			{
				on_ground = true;
			}
		}

		if (y_val < 0)
		{
			y_pos += 16 + y_val;

		}

		collision.y = getY() + 64;
	}
}

void Monster::GetHit(Character& p_player, SDL_Rect& camera)
{
	for (int i = 0; i < p_player.GetBulletList().size(); i++)
	{
		if (p_player.GetBulletList().at(i) != NULL)
		{
			if (CommonFunc_SDL2::checkCollision(collision, p_player.GetBulletList().at(i)->GetCollision()))
			{
				MARK_MONS -= 2;
				p_player.GetBulletList().at(i)->SetMove(false);
			}
		}
	}
	if (MARK_MONS <= 0)
	{
		death_ = true;
		death_boss = false;
	}
	else if (camera.x + 380 >= getX() + 80)
	{
		death_boss = true;
		death_ = false;
	}
}

void Monster::MoveToPlayer(std::vector<map>& map_data, Character& p_player)
{
	distanceToPlayer = sqrt((collision.x - p_player.getCollision().x) * (collision.x - p_player.getCollision().x) + (collision.y-p_player.getCollision().y )* (collision.y-p_player.getCollision().y));
	if (distanceToPlayer <= 7 * TILE_SIZE)
	{
		if (collision.x - p_player.getCollision().x > 32)
		{
			
			x_val = -MONSTER_VAL;
		}
		else if (collision.x - p_player.getCollision().x == 32)
		{
			x_val = 0;
			idle_ = true;
			flip_type_ = SDL_FLIP_HORIZONTAL;
		}

		if (collision.x - p_player.getCollision().x < -32)
		{
			
			x_val = MONSTER_VAL;
		}
		else if (collision.x - p_player.getCollision().x ==-32)
		{
			x_val = 0;
			idle_= true;
			flip_type_ = SDL_FLIP_NONE;

		}
	}
	if (map_data.at(levelSTT).tile[ground[1]][ground[0]] == 0 || map_data.at(levelSTT).tile[ground[1]][ground[0]] > 61)
	{
		x_val = 0;
		idle_ = true;
		flip_type_ = SDL_FLIP_HORIZONTAL;
	}
	if (map_data.at(levelSTT).tile[ground[1]][ground[0] + 1] == 0 || map_data.at(levelSTT).tile[ground[1]][ground[0] + 1] > 61)
	{
		x_val = 0;
		idle_ = true;
		flip_type_ = SDL_FLIP_NONE;
	}
	if (distanceToPlayer <= TILE_SIZE * 1.5 && !death_) //:)) cái này tớ hay cậu viết nhỉmayf you viet do :) thé á:)))) moe tao bay dong gop chu yeu ma
	{
		idle_ = false;
		run_ = false;
		attack_ = true;
	}
	else
	{
		attack_ = false;
		run_ = false;
		idle_ = true;
	}
}