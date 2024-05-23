#include "Game.h"

Game::Game()
{
	for (int i = 0; i < 6; i++)
	{
		bossClips[i] = { i * 576, 0, 576, 675 };
	}
	for (int i = 0; i < 5; i++)
	{
		healthbarClips[i] = { i * 128, 0, 128, 34 };
	}
}

Game::~Game()
{

}

bool Game::Init()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_EVERYTHING);
	if (ret < 0) success = false;
	else
	{
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		window = SDL_CreateWindow("BAI_TAP_LON", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		if (window == nullptr)  success = false;
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) success = false;
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				int imgFlag = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlag) && imgFlag))  success = false;
			}
		}
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		success = false;
		std::cout << "AUDIO ERROR " << Mix_GetError() << std::endl;
	}

	if (TTF_Init() < 0)
	{
		success = false;
		std::cout << "TTF ERROR" << TTF_GetError() << std::endl;
	}
	// load ttf
	return success;
}

bool Game::LoadMedia()
{
	if (!loadFont("ttf/GulfsDisplay-NormalItalic.ttf"))
	{
		return false;
	}
	if (font==NULL||fontUpper==NULL) 
	{
		return false;
	}

	
	bgMusic = Mix_LoadMUS("sfx/xDeviruchi - Mysterious Dungeon.wav");
	if (bgMusic == NULL) return false;

	playerSFX[0] = Mix_LoadWAV("sfx/Shoot.wav");
	playerSFX[1] = Mix_LoadWAV("sfx/Jump.wav");
	playerSFX[2] = Mix_LoadWAV("sfx/Hit.wav");
	playerSFX[3] = Mix_LoadWAV("sfx/Run.wav");
	playerSFX[4] = Mix_LoadWAV("sfx/Click.wav");
	
	menuSFX[0] = Mix_LoadWAV("sfx/win.wav");
	menuSFX[1] = Mix_LoadWAV("sfx/Retry.wav");
	
	healthbarText = CommonFunc_SDL2::createTexture("Character/health_bar.png", renderer);
	bossText = CommonFunc_SDL2::createTexture("Boss/Demon.png", renderer);

	std::string map0 = "MAP/map_level0.tmx";
	map_path.push_back(map0);
	std::string map1 = "MAP/map_level1.tmx";
	map_path.push_back(map1);
	std::string map2 = "MAP/map_level2.tmx";
	map_path.push_back(map2);
	std::string map3 = "MAP/map_level3.tmx";
	map_path.push_back(map3);
	std::string map4 = "MAP/map_level4.tmx";
	map_path.push_back(map4);
	std::string map5 = "MAP/map_level5.tmx";
	map_path.push_back(map5);
	std::string map6 = "MAP/map_level6.tmx";
	map_path.push_back(map6);

	if (map_path.size() < TOTAL_MAP) return false;

	if (playerSFX[0] == NULL|| playerSFX[1] == NULL|| playerSFX[2] == NULL|| playerSFX[3] == NULL|| playerSFX[4] == NULL) return false;
	return true;
}

bool Game::loadFont(const char* path)
{
	//TTF_CloseFont(font);// neu load nhieu font-> dong font cu
	font = TTF_OpenFont(path, 30);//->load font moi
	fontUpper = TTF_OpenFont(path, 120);
	if (font == NULL||fontUpper==NULL)
	{
		std::cout << "load font error" << std::endl;
		return false;
	}
	return true;
}

bool Game::CreateBackground()
{
	BaseObject bg;
	bg.Load_Img("Background/0.png", renderer);
	bgList.push_back(bg);

	BaseObject bg1;
	bg1.Load_Img("Background/1.png", renderer);
	bgList.push_back(bg1);

	BaseObject bg2;
	bg2.Load_Img("Background/2.png", renderer);
	bgList.push_back(bg2);

	BaseObject bg3;
	bg3.Load_Img("Background/3.png", renderer);
	bgList.push_back(bg3);

	BaseObject bg4;
	bg4.Load_Img("Background/4.png", renderer);
	bgList.push_back(bg4);

	BaseObject bg5;
	bg5.Load_Img("Background/5.png", renderer);
	bgList.push_back(bg5);

	BaseObject bg6;
	bg6.Load_Img("Background/6.png", renderer);
	bgList.push_back(bg6);

	BaseObject bg7;
	bg7.Load_Img("Background/7.png", renderer);
	bgList.push_back(bg7);

	if (bgList.size() < 7)
	{
		return false;
	}
	return true;
}

bool Game::CreateMap()
{
	for (int i = 0; i < TOTAL_LEVEL; i++)
	{
		int random = std::rand() % (TOTAL_MAP - 1) + 1;
		if (i == 0) random = 0;
		GameMap level;
		level.SetMapSTT(i);
		level.LoadMap_text(map_path.at(random));
		level.LoadTile(renderer);
		mapList.push_back(level);
		map map_data = mapList.at(i).Get_map();
		mapDataList.push_back(map_data);
	}
	if (mapList.size() < 1)
	{
		return false;
	}
	return true;
}

bool Game::CreateMenu()
{
	Menu menu;
	menu.Load_Img("menu/mix.png", renderer);
	menuList.push_back(menu);
	if (menuList.size() < 1)
	{
		return false;
	}
	return true;
}

bool Game::CreateCharacter()
{
	Character character;
	Character character2;
	character.Load_Img("Character/Gun_Yellow.png", renderer);
	character2.Load_Img("Character/Gun_Blue.png", renderer);
	characterList.push_back(character);
	characterList.push_back(character2);
	if (characterList.size() < 2)
	{
		return false;
	}
	return true;
}

bool Game::CreateMonster()
{
	for (int i = 0; i < TOTAL_LEVEL; i++)
	{
		for (int j = 0; j < mapDataList.at(i).monsterPos.size(); j++)
		{
			Monster* monster = new Monster((mapDataList.at(i).monsterPos.at(j) / TILE_SIZE) * TILE_SIZE - 80 + mapDataList.at(i).map_start_, (mapDataList.at(i).monsterPos.at(j) % TILE_SIZE) * TILE_SIZE - 128);
			monster->Load_Img("Monster/monster.png", renderer);
			monsterList.push_back(monster);
		}
	}
	return true;
}

void Game::HandleGameInput(SDL_Event& event)
{
	if (event.type == SDL_QUIT)
	{
		running = false;
	}
	menuList.at(0).HandleInput(event, playerSFX);
	
	if (menuList.at(0).isContinue() && !menuList.at(0).isPause() && !menuList.at(0).isExit()&&!menuList.at(0).isGuide())
	{
		if (menuList.at(0).isCheck_1())
		{
			characterList.at(0).KeyBoard(event, playerSFX, menuList.at(0));
		}
		if (menuList.at(0).isCheck_2())
		{
			characterList.at(1).KeyBoard(event, playerSFX, menuList.at(0));
		}
	}
	

}

void Game::Render_MainMenu()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	bgList.at(0).Render(renderer, &bg, camera);
	bgList.at(1).Render(renderer, &bg, camera);
	menuList.at(0).RenderMainMenu(renderer);
	SDL_RenderPresent(renderer);
}

void Game::Render_GuideMenu()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	bgList.at(0).Render(renderer, &bg, camera);
	bgList.at(7).Render(renderer, &bg, camera);
	menuList.at(0).RenderGuideMenu(renderer);
	SDL_RenderPresent(renderer);
}

void Game::RenderBullet()
{
	map map_data = mapList.at(0).Get_map();
	if (menuList.at(0).isCheck_1())
	{
		std::vector<Item*> bulletList = characterList.at(0).GetBulletList();
		for (int i = 0; i < characterList.at(0).GetBulletList().size(); i++)
		{
			if (bulletList.at(i) != NULL)
			{
				if (bulletList.at(i)->GetMove())
				{
					bulletList.at(i)->Load_Img("Character/bullet.png", renderer);
					bulletList.at(i)->SetColor(false);
					bulletList.at(i)->Update(mapDataList);
					bulletList.at(i)->Show(renderer, camerabg);
				}
				else
				{
					delete bulletList.at(i);
					bulletList.at(i) = NULL;
					bulletList.erase(bulletList.begin() + i);
					characterList.at(0).SetBulletList(bulletList);
				}
			}
			
		}
	}
	if (menuList.at(0).isCheck_2())
	{
		std::vector<Item*> bulletList = characterList.at(1).GetBulletList();
		for (int i = 0; i < characterList.at(1).GetBulletList().size(); i++)
		{
			if (bulletList.at(i) != NULL)
			{
				if (bulletList.at(i)->GetMove())
				{
					bulletList.at(i)->Load_Img("Character/bullet.png", renderer);
					bulletList.at(i)->SetColor(false);
					bulletList.at(i)->Update(mapDataList);
					bulletList.at(i)->Show(renderer, camerabg);
				}
				else
				{
					delete bulletList.at(i);
					bulletList.at(i) = NULL;
					bulletList.erase(bulletList.begin() + i);
					characterList.at(1).SetBulletList(bulletList);
				}
			}

		}
	}
	
}

void Game::Render_ChooseMenu()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	bgList.at(0).Render(renderer, &bg, camera);
	bgList.at(2).Render(renderer, &bg, camera);
	menuList.at(0).RenderChooseMenu(renderer);
	SDL_RenderPresent(renderer);
}

void Game::Render_PauseMenu()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	bgList.at(0).Render(renderer, &bg, camera);
	bgList.at(3).Render(renderer, &bg, camera);
	menuList.at(0).RenderPauseMenu(renderer);
	SDL_RenderPresent(renderer);
}

void Game::Render_RetryMenu()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	bgList.at(0).Render(renderer, &bg, camera);
	bgList.at(4).Render(renderer, &bg, camera);
	scoreText.str("");
	scoreText << "SCORE: ";
	SDL_Color camsp = { 249, 141, 77, 255 };
	BaseObject currentScore;
	currentScore.setRect(SCREEN_WIDTH / 2-200, 150);
	currentScore.CreateTexture(scoreText.str().c_str(), camsp, fontUpper, renderer);
	currentScore.Render(renderer, NULL, camera);

	
	Score_.str("");
	Score_ << lastscore;
	//SDL_Color camsp = { 249, 141, 77, 255 };
	currentScore.setRect(SCREEN_WIDTH / 2-70, 270);
	currentScore.CreateTexture(Score_.str().c_str(), camsp, fontUpper, renderer);
	currentScore.Render(renderer, NULL, camera);
	
	menuList.at(0).RenderRetryMenu(renderer,menuSFX,menuList.at(0));
	SDL_RenderPresent(renderer);
}

void Game::Render_ExitMenu()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	bgList.at(0).Render(renderer, &bg, camera);
	bgList.at(6).Render(renderer, &bg, camera);
	menuList.at(0).RenderExitMenu(renderer);
	
	if (menuList.at(0).Num() == 13)
	{
		running = false;
	}
	
	SDL_RenderPresent(renderer);
}

void Game::Render_ContinueMenu()
{
	time_fps.start();
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	bgList.at(0).Render(renderer, &bg, camera);
	RenderMap();
	RenderCharacter();
	RenderBullet();
	RenderMonster();
	RenderBoss();
	menuList.at(0).RenderContinueMenu(renderer);
	if (characterList.at(0).isDeath() || characterList.at(1).isDeath())
	{
		lastscore = score;
		if (menuList.at(0).isOnsound() && !menuList.at(0).isMute())
		{
			Mix_PlayChannel(-1, menuSFX[1], 0);
		}
		ResetGame();
		menuList.at(0).SetRetry(true);
		UpdateScore();
		score = 0;
	}

	RenderScore();
	Render_HealthBar();
	SDL_RenderPresent(renderer);
	int real_time = time_fps.get_ticks(); 
	int time_one_frame = 1000 / FRAME_PER_SEC;
	if (real_time < time_one_frame) 
	{
		int delay_time = time_one_frame - real_time;
		SDL_Delay(delay_time);
	}
}

void Game::RenderCharacter()
{
	map map_data = mapList.at(0).Get_map();
	if (menuList.at(0).isCheck_1())
	{
		characterList.at(0).Update(mapDataList, monsterList, playerSFX,menuList.at(0),camerabg);
		characterList.at(0).HandleCamera(camerabg, camera_val);
		characterList.at(0).Show_Frames(renderer, camerabg);
		health_ = characterList.at(0).Mark_cha(); // 
	}

	if (menuList.at(0).isCheck_2())
	{
		characterList.at(1).Update(mapDataList, monsterList, playerSFX,menuList.at(0),camerabg);
		characterList.at(1).HandleCamera(camerabg, camera_val);
		characterList.at(1).Show_Frames(renderer, camerabg);
		health_ = characterList.at(1).Mark_cha(); // 
	}
}

void Game::RenderMonster()
{
	map map_data = mapList.at(0).Get_map();
	if (menuList.at(0).isCheck_1())
	{
		for (int i = 0; i < monsterList.size(); i++)
		{
			if (monsterList.at(i) != NULL)
			{
				if (!monsterList.at(i)->isDeath()&&!monsterList.at(i)->isDeath_())
				{
					monsterList.at(i)->Update(mapDataList, characterList.at(0), camerabg);
					monsterList.at(i)->Show(renderer, camerabg);
				}
				else 
				{
					if (monsterList.at(i)->isDeath())
					{
						score++;
						delete monsterList.at(i);
						monsterList.at(i) = NULL;
						monsterList.erase(monsterList.begin() + i);
					}
					else if (monsterList.at(i)->isDeath_())
					{
						score--;
						if (score <= 0) // sao aam dduowcj hay vay
						{
							score = 0;
						}
						delete monsterList.at(i);
						monsterList.at(i) = NULL;
						monsterList.erase(monsterList.begin() + i);
					}
				}
			}
		}
	}
	if (menuList.at(0).isCheck_2())
	{
		for (int i = 0; i < monsterList.size(); i++)
		{
			if (monsterList.at(i) != NULL)
			{
				if (!monsterList.at(i)->isDeath()&&!monsterList.at(i)->isDeath_()) 
				{
					monsterList.at(i)->Update(mapDataList, characterList.at(1), camerabg);
					monsterList.at(i)->Show(renderer, camerabg);
				}
				else
				{
					if (monsterList.at(i)->isDeath())
					{
						score++;
						delete monsterList.at(i);
						monsterList.at(i) = NULL;
						monsterList.erase(monsterList.begin() + i);
					}
					if (monsterList.at(i)->isDeath_())
					{
						score--;
						if (score <= 0)
						{
							score = 0;
						}
						delete monsterList.at(i);
						monsterList.at(i) = NULL;
						monsterList.erase(monsterList.begin() + i);
					}
				}
			}
		}
	}
}

void Game::RenderMap()
{
	
	if (mapList.at(0).GetStartX() - camerabg.x <= -LEVEL_WIDTH)
	{
		int random = std::rand() % (TOTAL_MAP - 1) + 1;
		std::cout << random << std::endl;
		mapSTT++;
		mapList.at(0).SetMapSTT(mapSTT);
		mapList.at(0).LoadMap_text(map_path.at(random));
		mapList.at(0).LoadTile(renderer);
		GameMap level = mapList.at(0);
		mapList.push_back(level);
		mapList.erase(mapList.begin());
		map map_data = mapList.at(2).Get_map();
		mapDataList.push_back(map_data);
		mapDataList.erase(mapDataList.begin());
		for (int j = 0; j < mapDataList.at(2).monsterPos.size(); j++)
		{
			Monster* monster = new Monster((mapDataList.at(2).monsterPos.at(j) / TILE_SIZE) * TILE_SIZE - 80 + mapDataList.at(2).map_start_, (mapDataList.at(2).monsterPos.at(j) % TILE_SIZE) * TILE_SIZE - 128);
			monster->Load_Img("Monster/monster.png", renderer);
			monsterList.push_back(monster);
		}
	}
	
	for (int i = 0; i < TOTAL_LEVEL; i++)
	{
		mapList.at(i).DrawTile(renderer, camerabg);
	}
}

void Game::RenderScore()
{
	scoreText.str("");
	scoreText << "SCORE: " << score;
	SDL_Color camsp = { 249, 141, 77, 255 };
	BaseObject currentScore;
	currentScore.setRect(SCREEN_WIDTH/2-128,10);
	currentScore.CreateTexture(scoreText.str().c_str(), camsp, font, renderer);
	currentScore.Render(renderer, NULL, camera);

	std::ifstream readFile;
	readFile.open("score/HighScore.txt");
	if (readFile.fail()) UpdateScore();
	readFile >> highscore;
	if (highscore < score) highscore = score;
	highscoreText.str("");
	highscoreText << "HIGH SCORE: " << highscore;
	SDL_Color white = { 255, 255, 255, 255 };
	BaseObject highScore;
	highScore.setRect(SCREEN_WIDTH / 2-128,58);
	highScore.CreateTexture(highscoreText.str().c_str(), white, font, renderer);
	highScore.Render(renderer, NULL, camera);
}

void Game::Render_HealthBar()
{
	CommonFunc_SDL2::RenderAnimation(renderer, healthbarText, 0, 0, &healthbarClips[4 - health_], &camera, 0, NULL, SDL_FLIP_NONE);
	if (health_ <= 0) health_ = 0;
}

void Game::RenderBoss()
{
	CommonFunc_SDL2::RenderAnimation(renderer, bossText, camerabg.x - 128, camerabg.y + 32, &bossClips[runCounter / 8], &camerabg, 0, NULL, SDL_FLIP_NONE);
	runCounter++; 
	if (runCounter / 8 >= 5)
	{
		runCounter = 0;
	}
}

void Game::UpdateScore()
{
	std::ofstream outFile;
	outFile.open("score/HighScore.txt");
	outFile.clear();
	outFile << highscore;
	outFile.close();
}

void Game::PlayMusic()
{
	
	if (Mix_PlayingMusic() == 0) // nếu ko chơi nhạc thì bắt đầu chơi
	{
		Mix_FadeInMusic(bgMusic, -1, 1000);
		Mix_VolumeMusic(30);
	}
	
	if (menuList.at(0).isMute()||menuList.at(0).isRetry())
	{
		Mix_PauseMusic();
	}
	else
	{
		Mix_ResumeMusic();
	}
}

void Game::ResetGame()
{
	
	camerabg.x = 0;
	camera.y = 0;
	camera_val = 1;
	mapSTT = 2;
	if (!monsterList.empty()) 
	{
		for (int i = monsterList.size() - 1; i >= 0; i--)
		{
			delete monsterList.at(i);
			monsterList.at(i) = NULL;
			monsterList.erase(monsterList.begin() + i);
		}
	}
	for (int i = 2; i >= 0; i--)
	{
		mapList.erase(mapList.begin());
		mapDataList.erase(mapDataList.begin());
	}
	CreateMap();
	CreateMonster();
	

	characterList.at(0).ResetCharacter();
	characterList.at(1).ResetCharacter();

}

void Game::Delete_game()
{
	
	if (!monsterList.empty())
	{
		for (int i = monsterList.size() - 1; i >= 0; i--)
		{
			delete monsterList.at(i);
			monsterList.at(i) = NULL;
			monsterList.erase(monsterList.begin() + i); // cậu gọi cái này thì số phần tử mảng giảm đi 1 nó xoá đến 1 nửa thì lỗi 
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	
}



