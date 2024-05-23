#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_


#pragma once

#include <iostream>
#include <Windows.h>
#include <cmath>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <SDL.h>
#include <string>
#include<SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;

static SDL_Event e;

const int SCREEN_WIDTH = 1280 ; 
const int SCREEN_HEIGHT = 640; 

const int LEVEL_WIDTH = 1600;
const int LEVEL_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;
const int DRAW_COLOR_KEY = 0xff;

const int TILE_SIZE = 32;
const int MAX_MAP_X = 50;
const int MAX_MAP_Y = 20; 

const int FRAME_PER_SEC = 28; 

const int PLAYER_VAL = 10;
const float GRAVITY = 0.5;
const float MAX_GRAVITY = 10;

const int TOTAL_MAP = 7;
const int TOTAL_LEVEL = 3;	

struct map
{
	int start_x;
	int start_y;

	int map_x;
	int map_y;

	int map_start_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	SDL_Rect collision[MAX_MAP_Y][MAX_MAP_X];
	std::string file_map;
	std::vector<int> monsterPos;
};

namespace CommonFunc_SDL2
{
	bool checkCollision(SDL_Rect a, SDL_Rect b);
	void RenderAnimation(SDL_Renderer* des, SDL_Texture* p_text, float p_x, float p_y, SDL_Rect* clip = NULL, SDL_Rect* camera = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip p_flip = SDL_FLIP_NONE);
	bool checkToMap(SDL_Rect& box, std::vector<map>& game_map);
	bool checkToMap(SDL_Rect& box, std::vector<map>& game_map, bool& on_ground_, int& groundX, int& groundY, int& levelSTT);
	SDL_Texture* createTexture(const char* path, SDL_Renderer* des);

}

#endif // !COMMON_FUNC_H_