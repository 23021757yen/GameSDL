#include "Map.h"

void GameMap::LoadMap_text(std::string  name) 
{
	FILE* fp = nullptr;
	fopen_s(&fp, name.c_str(), "rb");
	if (fp == nullptr)
	{
		return;
	}

	if (game_map_.monsterPos.size() != 0)
	{
		for (int i = game_map_.monsterPos.size() - 1; i >= 0; i--)
		{
			game_map_.monsterPos.erase(game_map_.monsterPos.begin());
		}
	}
	game_map_.map_x = 0;
	game_map_.map_y = 0;

	for (int i = 0; i < MAX_MAP_Y; i++)
	{
		for (int j = 0; j < MAX_MAP_X; j++)
		{
			fscanf_s(fp, "%d", &game_map_.tile[i][j]);
			int value = game_map_.tile[i][j];

			if (value > 0)
			{
				if (j > game_map_.map_x)
				{
					 game_map_.map_x= j;
				}
				if (i > game_map_.map_y)
				{
					 game_map_.map_y = i;
				}
				game_map_.collision[i][j].x = j * TILE_SIZE + mapSTT * LEVEL_WIDTH;
				game_map_.collision[i][j].y = i * TILE_SIZE;
				game_map_.collision[i][j].w = TILE_SIZE;
				game_map_.collision[i][j].h = TILE_SIZE;
				
			}
			if (value == 7)
			{
				game_map_.monsterPos.push_back(j * TILE_SIZE + i);
			}
		}
	}
	game_map_.map_x = (game_map_.map_x + 1) * TILE_SIZE;
	game_map_.map_y = (game_map_.map_y + 1) * TILE_SIZE;
	game_map_.map_start_ = mapSTT * LEVEL_WIDTH;
	game_map_.start_x = 0;
	game_map_.start_y = 0;
	game_map_.file_map = name;

	fclose(fp);
}

void GameMap::LoadTile(SDL_Renderer * screen)
{
	char file_img[70];
	FILE* fp = nullptr;

	for (int i = 0; i < 90 ; i++)
	{
		sprintf_s(file_img, "MAP/%d.png", i);
		fopen_s(&fp, file_img, "rb");
		if (fp == nullptr)
		{
			continue;
		}
		fclose(fp);
		tile_mat[i].Load_Img(file_img, screen);

	}
}


void GameMap::DrawTile(SDL_Renderer* screen, SDL_Rect& camera)
{
	
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;
	
	int mapnow_x = game_map_.start_x / TILE_SIZE;
	
	x1 = (game_map_.start_x % TILE_SIZE) * -1;
	if (x1 == 0)
	{
		x2 = x1 + SCREEN_WIDTH;
	}
	else
	{
		x2 = x1 + SCREEN_WIDTH + TILE_SIZE;
	}
	
	int mapnow_y = game_map_.start_y / TILE_SIZE;
	
	y1 = (game_map_.start_y % TILE_SIZE) * -1;
	if (y1 == 0)
	{
		y2 = y1 + SCREEN_HEIGHT;
	}
	else
	{
		y2 = y1 + SCREEN_HEIGHT + TILE_SIZE;
	}
	
	for (int i = 0; i < LEVEL_HEIGHT; i+=TILE_SIZE)
	{
		mapnow_x = game_map_.start_x / TILE_SIZE;
		for (int j = 0; j < LEVEL_WIDTH; j+=TILE_SIZE)
		{
			int value = game_map_.tile[mapnow_y][mapnow_x];  
			if (value > 0)
			{
				tile_mat[value].setRect(j + mapSTT * MAX_MAP_X * TILE_SIZE, i); 
				tile_mat[value].Render(screen, nullptr, camera);
			}
		
		mapnow_x++;
		}
		mapnow_y++;

	}


}
