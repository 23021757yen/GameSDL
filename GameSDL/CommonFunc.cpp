#include "CommonFunc.h"
#include "Monster.h"


bool CommonFunc_SDL2::checkCollision(SDL_Rect a, SDL_Rect b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) {
		return false;
	}

	if (topA >= bottomB) {
		return false;
	}

	if (rightA <= leftB) {
		return false;
	}

	if (leftA >= rightB) {
		return false;
	}

	return true;
}

void CommonFunc_SDL2::RenderAnimation(SDL_Renderer * des,SDL_Texture* p_text, float p_x, float p_y, SDL_Rect* clip, SDL_Rect* camera, double angle, SDL_Point* center, SDL_RendererFlip p_flip)
{
	SDL_Rect dst = { p_x, p_y, clip->w, clip->h }; 
	if (camera != NULL)
	{
		dst.x = p_x - camera->x;
		dst.y = p_y - camera->y;
	}
	SDL_RenderCopyEx(des, p_text, clip, &dst, angle, center, p_flip);
}

bool CommonFunc_SDL2::checkToMap(SDL_Rect& box, std::vector<map>& map_data)
{
	bool check = false;

	for (int i = 0; i < TOTAL_LEVEL; i++)
	{
		if (box.x >= map_data.at(i).map_start_ && box.x < map_data.at(i).map_start_ + LEVEL_WIDTH)
		{
			int cot1 = (box.x - map_data.at(i).map_start_) / TILE_SIZE;
			int dong1 = box.y / TILE_SIZE;
			int cot2 = cot1 + 1;
			int dong2 = dong1 + 1;
			int dong3 = dong2 + 1;
			if (map_data.at(i).tile[dong1][cot1] > 0 && map_data.at(i).tile[dong1][cot1] <= 60)
			{
				if (checkCollision(box, map_data.at(i).collision[dong1][cot1])) check = true;
			}
			if (map_data.at(i).tile[dong1][cot2] > 0 && map_data.at(i).tile[dong1][cot2] <= 60)
			{
				if (checkCollision(box, map_data.at(i).collision[dong1][cot2])) check = true;
			}
			if (map_data.at(i).tile[dong2][cot1] > 0 && map_data.at(i).tile[dong2][cot1] <= 60)
			{
				if (checkCollision(box, map_data.at(i).collision[dong2][cot1])) check = true;
			}
			if (map_data.at(i).tile[dong2][cot2] > 0 && map_data.at(i).tile[dong2][cot2] <= 60)
			{
				if (checkCollision(box, map_data.at(i).collision[dong2][cot2])) check = true;
			}
			if (map_data.at(i).tile[dong3][cot1] > 0 && map_data.at(i).tile[dong3][cot1] <= 60)
			{
				if (checkCollision(box, map_data.at(i).collision[dong3][cot1])) check = true;
			}
			if (map_data.at(i).tile[dong3][cot2] > 0 && map_data.at(i).tile[dong3][cot2] <= 60)
			{
				if (checkCollision(box, map_data.at(i).collision[dong3][cot2])) check = true;
			}
		}
		
	}

	return check;
}

bool CommonFunc_SDL2::checkToMap(SDL_Rect& box, std::vector<map>& map_data, bool& on_ground_, int& groundX, int& groundY, int& levelSTT) // check theo vertical
{
	bool check = false;
	for (int i = 0; i < TOTAL_LEVEL; i++)
	{
		if (box.x >= map_data.at(i).map_start_ && box.x < map_data.at(i).map_start_ + LEVEL_WIDTH)
		{
			int cot1 = (box.x - map_data.at(i).map_start_) / TILE_SIZE;
			int dong1 = box.y / TILE_SIZE; //
			int cot2 = cot1 + 1;//
			int dong2 = dong1 + 1;
			int dong3 = dong2 + 1;

			if (box.x < map_data.at(i).map_start_ || box.x >  map_data.at(i).map_start_ + LEVEL_WIDTH) // ngoài level
			{
				on_ground_ = false;
			}
			else
			{
				if (map_data.at(i).tile[dong1][cot1] > 0 && map_data.at(i).tile[dong1][cot1] <= 60)
				{
					if (checkCollision(box, map_data.at(i).collision[dong1][cot1])) check = true;
				}
				if (map_data.at(i).tile[dong1][cot2] > 0 && map_data.at(i).tile[dong1][cot2] <= 60)
				{
					if (checkCollision(box, map_data.at(i).collision[dong1][cot2])) check = true;
				}
				if (map_data.at(i).tile[dong2][cot1] > 0 && map_data.at(i).tile[dong2][cot1] <= 60)
				{
					if (checkCollision(box, map_data.at(i).collision[dong2][cot1])) check = true;
				}
				if (map_data.at(i).tile[dong2][cot2] > 0 && map_data.at(i).tile[dong2][cot2] <= 60)
				{
					if (checkCollision(box, map_data.at(i).collision[dong2][cot2])) check = true;
				}
				if (map_data.at(i).tile[dong3][cot1] > 0 && map_data.at(i).tile[dong3][cot1] <= 60)
				{
					if (checkCollision(box, map_data.at(i).collision[dong3][cot1])) check = true;
				}
				if (map_data.at(i).tile[dong3][cot2] > 0 && map_data.at(i).tile[dong3][cot2] <= 60)
				{
					if (checkCollision(box, map_data.at(i).collision[dong3][cot2])) check = true;
				}
				if (!(map_data.at(i).tile[dong3][cot1] > 0 && map_data.at(i).tile[dong3][cot1] <= 60) && !(map_data.at(i).tile[dong3][cot2] > 0 && map_data.at(i).tile[dong3][cot2] <= 60)) on_ground_ = false;
				if (!(map_data.at(i).tile[dong3][cot1] > 0 && map_data.at(i).tile[dong3][cot1] <= 60) && (map_data.at(i).tile[dong3][cot2] > 0 && map_data.at(i).tile[dong3][cot2] <= 60) && box.x + box.w <= cot2 * TILE_SIZE) on_ground_ = false;
			}

			groundX = cot1;
			groundY = dong3;
			levelSTT = i;
		}
		
		
	}
	return check;
}

SDL_Texture* CommonFunc_SDL2::createTexture(const char* path, SDL_Renderer* des)
{
	SDL_Texture* text = NULL;
	text = IMG_LoadTexture(des, path); //tao texture truc tiep:)))
	if (text == NULL)
	{
		std::cout << "IMG ERROR" << std::endl;
	}
	return text;
}