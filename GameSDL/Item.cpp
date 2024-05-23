#include "CommonFunc.h"
#include "BaseObject.h"
#include "Character.h"
#include "Map.h"
#include "Item.h"

Item::Item(float p_x, float p_y, SDL_RendererFlip p_flip)  
{
	x_pos = p_x;
	y_pos = p_y;

	flip_type_ = p_flip;
	collision.x = getX();
	collision.y = getY();
	collision.w = FRAME_WIDTH;
	collision.h = FRAME_HEIGHT;

	for (int i = 0; i < FRAME_YELLOW; i++)
	{
		clip_bullet_yellow[i] = { i * FRAME_WIDTH, 0 ,FRAME_WIDTH,FRAME_HEIGHT };
	}
	for (int i = 0; i < FRAME_BLUE; i++)
	{
		clip_bullet_blue[i] = { i * FRAME_WIDTH,1 * FRAME_HEIGHT ,FRAME_WIDTH,FRAME_HEIGHT };
	}
}

bool Item::Load_Img(std::string path, SDL_Renderer* des)
{
	bool ret = BaseObject::Load_Img(path, des);
	return ret;
}

void Item::Update(std::vector<map>& map_data)
{
	x_val = ITEM_VAL;
	if (getFlip() == SDL_FLIP_NONE)
	{
		x_pos += x_val;
	}
	if (getFlip() == SDL_FLIP_HORIZONTAL)
	{
		x_pos -= x_val;
	}
	collision.x = getX();

	if (CommonFunc_SDL2::checkToMap(collision, map_data))
	{
		if (getFlip() == SDL_FLIP_NONE)
		{
			x_pos -= x_val;
			SetMove(false);
		}
		if (getFlip() == SDL_FLIP_HORIZONTAL)
		{
			x_pos += x_val;
			SetMove(false);
		}
	}
}

void Item::SetPosition(float p_x, float p_y)
{
	if (getFlip() == SDL_FLIP_HORIZONTAL)
	{
		x_pos = p_x;
		y_pos = p_y;
	}
}

void Item::Show(SDL_Renderer* des, SDL_Rect& camera)
{
	if (!color_)
	{
		CommonFunc_SDL2::RenderAnimation(des, p_object, x_pos, y_pos, &clip_bullet_yellow[cnt_yellow / delay], &camera, 0, NULL, flip_type_);
		cnt_yellow++;
		if (cnt_yellow / 10 >= 1) cnt_yellow += 5;
		if (cnt_yellow / delay >= FRAME_YELLOW)
		{
			cnt_yellow = 0;
			SetMove(false);
		}
		
	}
	else cnt_yellow = 0;

	if (color_)
	{
		CommonFunc_SDL2::RenderAnimation(des, p_object, x_pos, y_pos, &clip_bullet_blue[cnt_blue / delay], &camera, 0, NULL, flip_type_);
		cnt_blue++;
		if (cnt_blue / delay >= FRAME_BLUE)
		{
			cnt_blue = 0;
			SetMove(false);
		}
		
	}
	else cnt_blue = 0;
}

