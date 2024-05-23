#ifndef GAME_H_
#define GAME_H_

#pragma once


#include "CommonFunc.h"
#include "BaseObject.h"
#include "Character.h"
#include "Map.h"
#include "Monster.h"
#include "Menu.h"
#include "Timer.h"
#include "Item.h"

static TTF_Font* font = nullptr;
static TTF_Font* fontUpper = nullptr;

class Game
{
public:
	Game();
	~Game();
	bool Init();
	bool LoadMedia();
	bool CreateBackground();
	bool CreateMap();
	bool CreateMenu();
	bool CreateCharacter();
	bool CreateMonster();
	
	void Render_MainMenu();
	void Render_ChooseMenu();
	void Render_PauseMenu();
	void Render_RetryMenu();
	void Render_ContinueMenu();
	void RenderCharacter();
	void RenderMonster();
	void RenderBullet();
	void RenderMap();
	//void Render_WinMenu();
	void Render_ExitMenu();
	void Render_GuideMenu();
	void Render_HealthBar();
	void RenderBoss();

	void RenderScore();
	void UpdateScore();
	void PlayMusic();

	void Delete_game();

	void HandleGameInput(SDL_Event& event);
	void ResetGame();
	bool loadFont(const char* path);
	bool isRunning() const { return running; };
	std::vector<Menu> GetMenuList() const { return menuList; };

	int Score() { return score; };
	
private:
	bool running = true;
	Timer time_fps;
	std::vector<BaseObject> bgList;
	std::vector<GameMap> mapList;
	std::vector<Menu> menuList;
	std::vector<Character> characterList;
	std::vector<Monster*> monsterList;
	std::vector<map> mapDataList;

	int score = 0;
	int lastscore = 0;
	int highscore = 0;

	std::stringstream scoreText;
	std::stringstream Score_;
	std::stringstream highscoreText;

	Mix_Music* bgMusic = NULL; 
	Mix_Chunk* playerSFX[7] = { NULL };
	Mix_Chunk* menuSFX[3] = { NULL };
	SDL_Rect camerabg = { 0,0,1280,640 };
	SDL_Rect camera = { 0,0,1280,640 };
	SDL_Rect bg = { 0,0,1280,640 };

	SDL_Texture* healthbarText = NULL;
	SDL_Texture* bossText = NULL;
	SDL_Rect bossClips[6];
	SDL_Rect healthbarClips[5];
	int health_ = 4;
	int runCounter = 0;

	int camera_val = 1;
	int mapSTT = 2;
	std::vector<std::string> map_path;
	int levelSTT;
	
};




#endif 