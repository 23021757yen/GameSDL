#include "Menu.h"

Menu::Menu()
{
	for (int i = 0; i < BUTTON_TYPE; i++)
	{
		playButton[i] = { i * BUTTON_WIDTH, 0, BUTTON_WIDTH, BUTTON_HEIGHT };
		soundButton[i] = { i * BUTTON_WIDTH, 1 * BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
		pauseButton[i] = { i * BUTTON_WIDTH, 3 * BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
		exitButton[i] = { i * BUTTON_WIDTH, 4 * BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
		retryButton[i] = { i * BUTTON_WIDTH, 5 * BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
		continueButton[i] = { i * BUTTON_WIDTH, 0 , BUTTON_WIDTH , BUTTON_HEIGHT };
		muteButton[i] = { i * BUTTON_WIDTH, 2 * BUTTON_HEIGHT, BUTTON_WIDTH, BUTTON_HEIGHT };
		yesButton[i] = { i * BUTTON_WIDTH, 18*BUTTON_HEIGHT,BUTTON_WIDTH,BUTTON_HEIGHT };
		noButton[i] = { i * BUTTON_WIDTH,19 * BUTTON_HEIGHT,BUTTON_WIDTH,BUTTON_HEIGHT };
		guideButton[i] = { i * BUTTON_WIDTH,20 * BUTTON_HEIGHT,BUTTON_WIDTH,BUTTON_HEIGHT };
	}
	for (int i = 0; i < BUTTON_TYPE_CHOOSE; i++)
	{
		chooseButton_1_1[i] = { i * 4 * BUTTON_WIDTH,6 * BUTTON_HEIGHT,BUTTON_WIDTH * 4,BUTTON_HEIGHT * 4 };
		chooseButton_1_2[i] = { i * 4 * BUTTON_WIDTH,10 * BUTTON_HEIGHT,BUTTON_WIDTH * 4,BUTTON_HEIGHT * 4 };
		chooseButton_1_3[i] = { i * 4 * BUTTON_WIDTH,14 * BUTTON_HEIGHT,BUTTON_WIDTH * 4,BUTTON_HEIGHT * 4 };

		chooseButton_2_1[i] = { i * 4 * BUTTON_WIDTH + 5 * 4 * BUTTON_WIDTH,6 * BUTTON_HEIGHT,BUTTON_WIDTH * 4 ,BUTTON_HEIGHT * 4 };
		chooseButton_2_2[i] = { i * 4 * BUTTON_WIDTH + 5 * 4 * BUTTON_WIDTH,10 * BUTTON_HEIGHT,BUTTON_WIDTH * 4 ,BUTTON_HEIGHT * 4 };
		chooseButton_2_3[i] = { i * 4 * BUTTON_WIDTH + 5 * 4 * BUTTON_WIDTH,14 * BUTTON_HEIGHT,BUTTON_WIDTH * 4 ,BUTTON_HEIGHT * 4 };

	}
}
bool Menu::Load_Img(std::string p_path, SDL_Renderer* des)
{
	bool ret = BaseObject::Load_Img(p_path.c_str(), des);
	if (ret)
	{
		buttonText = p_object;
	}
	return ret;
}

void Menu::SetButton()
{
	
}

void Menu::HandleInput(SDL_Event& event, Mix_Chunk* p_sfx[])
{
	switch (event.type)
	{

	case SDL_MOUSEMOTION:

		if (menu_)
		{
			if (checkMouse(button0.x, button0.y))
			{
				selected[0] = true;
			}
			else selected[0] = false;
			if (checkMouse(button1.x, button1.y))// exit o menu main
			{
				selected[1] = true;
			}
			else selected[1] = false;
			if (checkMouse(button14.x, button14.y))//nut guide

			{
				selected[14] = true;
			}
			else selected[14] = false;
		}
		if (choose_)
		{
			if (checkMouse(button3.x, button3.y))
			{
				selected[3] = true;
			}
			else selected[3] = false;

			if (checkMouse(button4.x, button4.y))
			{
				selected[4] = true;
			}
			else selected[4] = false;
		}
		if (continue_game)
		{
			if (checkMouse(button2.x, button2.y))
			{
				selected[2] = true;
			}
			else selected[2] = false;

			if (checkMouse(button5.x, button5.y))
			{
				selected[5] = true;
			}
			else selected[5] = false;
		}
		if (pause_)
		{
			if (checkMouse(button6.x, button6.y))
			{
				selected[6] = true;
			}
			else selected[6] = false;

			if (checkMouse(button8.x, button8.y))
			{
				selected[8] = true;
			}
			else selected[8] = false;
		}
		if (retry_)// thua
		{
			if (checkMouse(button7.x, button7.y))// retry thua
			{
				selected[7] = true;
			}
			else selected[7] = false;

			if (checkMouse(button10.x, button10.y))// exit thua
			{
				selected[10] = true;
			}
			else selected[10] = false;
		}

		/*if (win_)
		{
			if (checkMouse(button9.x, button9.y))// retry thang
			{
				selected[9] = true;
			}
			else selected[9] = false;

			if (checkMouse(button11.x, button11.y))// exit thang
			{
				selected[11] = true;
			}
			else selected[11] = false;
		}
		*/
		if (exit_)
		{
			if (checkMouse(button12.x, button12.y))//no
			{
				selected[12] = true;
			}
			else selected[12] = false;

			if (checkMouse(button13.x, button13.y))//yes
			{
				selected[13] = true;
			}
			else selected[13] = false;
		}
		if (guide)
		{
			if (checkMouse(button15.x, button15.y))
			{
				selected[15] = true;
			}
			else selected[15] = false;
		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (menu_)
		{
			if (checkMouse(button0.x, button0.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[0] = true;
				menu_ = false;
				continue_game = false;
				guide = false;
				choose_ = true;

			}

			if (checkMouse(button1.x, button1.y))// exit menu main
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[1] = true;
				menu_ = false;
				guide = false;
				exit_ = true;
				num = 1;
				//choose_ = false;
			}
			if (checkMouse(button14.x, button14.y))// exit menu main
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[14] = true;
				menu_ = false;
				guide = true;
				//choose_ = false;
			}

		}
		if (choose_)
		{
			if (checkMouse(button3.x, button3.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[3] = true;
				check_choose_1 = true;
				check_choose_2 = false;
				choose_ = false;
				guide = false;
				continue_game = true;
			}
			if (checkMouse(button4.x, button4.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[4] = true;
				check_choose_2 = true;
				check_choose_1 = false;
				guide = false;
				choose_ = false;
				continue_game = true;
			}
		}
		if (continue_game)
		{
			if (checkMouse(button2.x, button2.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[2] = true;
				if (onsound && !mute)
				{
					onsound = false;
					mute = true;
				}
				else if (!onsound && mute)
				{
					onsound = true;
					mute = false;
				}
				continue_game = true;

			}

			if (checkMouse(button5.x, button5.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[5] = true;
				continue_game = false;
				guide = false;
				pause_ = true;
			}

		}

		if (pause_)
		{
			if (checkMouse(button6.x, button6.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[6] = true;
				pause_ = false;
				guide = false;
				continue_game = true;
			}

			if (checkMouse(button8.x, button8.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[8] = true;
				num = 8;
				guide = false;
				continue_game = false;
				pause_ = false;
				exit_ = true;
			}
		}

		if (retry_)
		{

			if (checkMouse(button7.x, button7.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[7] = true;
				continue_game = false;
				menu_ = false;
				pause_ = false;
				guide = false;
				retry_ = false;
				choose_ = true;
				check_choose_1 = false;
				check_choose_2 = false;
			}

			if (checkMouse(button10.x, button10.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[10] = true;
				continue_game = false;
				menu_ = false;
				pause_ = false;
				guide = false;
				retry_ = false;
				num = 10;
				exit_ = true;
			}
		}

		/*if (win_)
		{
			if (checkMouse(button9.x, button9.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[9] = true;
				continue_game = false;
				menu_ = false;
				pause_ = false;
				guide = false;
				retry_ = false;
				choose_ = true;
				win_ = false;
				check_choose_1 = false;
				check_choose_2 = false;
			}
			if (checkMouse(button11.x, button11.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[11] = true;
				num = 11;
				exit_ = true;
				win_ = false;
				check_choose_1 = false;
				guide = false;
				check_choose_2 = false;
				menu_ = false;
				pause_ = false;
				retry_ = false;
			}
		}
		*/
		if (guide)
		{
			if (checkMouse(button15.x, button15.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[15] = true;
				exit_ = false;
				//win_ = false;
				check_choose_1 = false;
				check_choose_2 = false;
				menu_ = true;
				pause_ = false;
				retry_ = false;
			}
		}

		if (exit_)
		{
			if (checkMouse(button12.x, button12.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[12] = true;
				exit_ = false;
				if (num == 1)
				{
					menu_ = true;

				}
				if (num == 8)
				{
					pause_ = true;
				}
				if (num == 10 || num == 11)
				{

					choose_ = true;
				}
			}

			if (checkMouse(button13.x, button13.y))
			{
				if (onsound && !mute)
				{
					Mix_PlayChannel(-1, p_sfx[clickSFX], 0);
				}
				pressed[13] = true;
				num = 13;
			}
		}

		break;
	case SDL_MOUSEBUTTONUP:

		for (int i = 0; i < 11; i++)
		{
			pressed[i] = false;
		}

		break;
	case SDL_QUIT:
		quit_ = true;
		break;
	default:
		break;
	}
}

bool Menu::checkMouse(const int& p_x, const int& p_y)
{
	int x, y; 
	SDL_GetMouseState(&x, &y);
	if (menu_ || retry_ || pause_|| exit_)
	{
		if (x >= p_x && x <= p_x + BUTTON_WIDTH && y >= p_y && y <= p_y + BUTTON_HEIGHT)
		{
			return true;
		}
	}
	else if (choose_)
	{
		if (x >= p_x && x <= p_x + 4*BUTTON_WIDTH && y >= p_y && y <= p_y + 4*BUTTON_HEIGHT)
		{
			return true;
		}
	}
	else if (continue_game||guide)
	{
		if (x >= p_x && x <= p_x + BUTTON_WIDTH / 2  && y >= p_y && y <= p_y + BUTTON_HEIGHT / 2)
		{
			return true;
		}
	}
	return false;
}

void Menu::RenderMainMenu(SDL_Renderer* des)
{
	if (menu_)
	{
		
		if (selected[0])
		{
			SDL_Rect src = { button0.x, button0.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &playButton[1], &src);
		}
		else if (pressed[0])
		{
			SDL_Rect src = { button0.x, button0.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &playButton[2], &src);
		}
		else
		{
			SDL_Rect src = { button0.x, button0.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &playButton[0], &src);
		}
		if (selected[1])
		{
			SDL_Rect src = { button1.x, button1.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[1], &src);
		}
		else if (pressed[1])
		{
			SDL_Rect src = { button1.x, button1.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[2], &src);
		}
		else
		{
			SDL_Rect src = { button1.x, button1.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
		if (selected[14])
		{
			SDL_Rect src = { button14.x, button14.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &guideButton[1], &src);
		}
		else if (pressed[14])
		{
			SDL_Rect src = { button14.x, button14.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &guideButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button14.x, button14.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &guideButton[0], &src);
		}
	}
}


void Menu::RenderChooseMenu(SDL_Renderer * des)
{
	if (choose_)
	{
		if (selected[3])
		{
			CommonFunc_SDL2::RenderAnimation(des,buttonText, button3.x, button3.y, &chooseButton_1_2[idle_choose/120], NULL, 0, NULL, flip_type_);
			idle_choose++; 
			if (idle_choose / 120 >= 5)
			{
				idle_choose = 0;
			}
		}
		else if (pressed[3] )
		{
			CommonFunc_SDL2::RenderAnimation(des,buttonText, button3.x, button3.y, &chooseButton_1_3[idle_choose/120], NULL, 0, NULL, flip_type_);
			idle_choose++;
			if (idle_choose / 120 >=5)
			{
				idle_choose = 0;
			}
		}
		else
		{
			CommonFunc_SDL2::RenderAnimation(des,buttonText, button3.x, button3.y, &chooseButton_1_1[idle_choose/120], NULL, 0, NULL, flip_type_);
			idle_choose++;
			if (idle_choose / 120 >=5 )
			{
				idle_choose = 0;
			}
		}
		if (selected[4])
		{
			CommonFunc_SDL2::RenderAnimation(des,buttonText, button4.x, button4.y, &chooseButton_2_2[idle_choose/120], NULL, 0, NULL, flip_type_);
			idle_choose++;
			if (idle_choose / 120 >= 5)
			{
				idle_choose = 0;
			}
		}
		else if (pressed[4] )
		{
			CommonFunc_SDL2::RenderAnimation(des,buttonText, button4.x, button4.y, &chooseButton_2_3[idle_choose/120], NULL, 0, NULL, flip_type_);
			idle_choose++;
			if (idle_choose /  120 >= 5)
			{
				idle_choose = 0;
			}
		}
		else
		{
			CommonFunc_SDL2::RenderAnimation(des,buttonText, button4.x, button4.y, &chooseButton_2_1[idle_choose/ 120 ], NULL, 0, NULL, flip_type_);
			idle_choose++;
			if (idle_choose / 120 >=5)
			{
				idle_choose = 0;
			}
		}
	}
}

void Menu::RenderPauseMenu(SDL_Renderer* des)
{
	if (pause_)
	{
		if (selected[6])
		{
			SDL_Rect src = { button6.x, button6.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &continueButton[1], &src);
		}
		else if (pressed[6])
		{
			SDL_Rect src = { button6.x, button6.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText , &continueButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button6.x, button6.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &continueButton[0], &src);
		}

		if (selected[8])
		{
			SDL_Rect src = { button8.x, button8.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
			SDL_RenderCopy(des, buttonText, &exitButton[1], &src);
		}
		else if (pressed[8])
		{
			SDL_Rect src = { button8.x, button8.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button8.x, button8.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
	}
}

void Menu::RenderContinueMenu(SDL_Renderer* des)
{
	if (continue_game)
	{
		if (selected[2])
		{
			if (onsound && !mute)
			{
				SDL_Rect src = { button2.x, button2.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
				SDL_RenderCopy(des, buttonText, &soundButton[1], &src);
			}
			else
			{
				SDL_Rect src = { button2.x, button2.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
				SDL_RenderCopy(des, buttonText, &muteButton[1], &src);
			}
		}
		else if (pressed[2])
		{
			if (onsound && !mute)
			{
				SDL_Rect src = { button2.x, button2.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
				SDL_RenderCopy(des, buttonText, &soundButton[0], &src);
			}
			else
			{
				SDL_Rect src = { button2.x, button2.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2};
				SDL_RenderCopy(des, buttonText, &muteButton[0], &src);
			}
		}
		else
		{
			if (onsound && !mute)
			{
				SDL_Rect src = { button2.x, button2.y, BUTTON_WIDTH/2, BUTTON_HEIGHT /2};
				SDL_RenderCopy(des, buttonText, &soundButton[0], &src);
			}
			else
			{
				SDL_Rect src = { button2.x, button2.y, BUTTON_WIDTH/2, BUTTON_HEIGHT/2 };
				SDL_RenderCopy(des, buttonText, &muteButton[0], &src);
			}
		}

		if (selected[5])
		{
			SDL_Rect src = { button5.x, button5.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
			SDL_RenderCopy(des, buttonText, &pauseButton[1], &src);
		}
		else if (pressed[5])
		{
			SDL_Rect src = { button5.x, button5.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
			SDL_RenderCopy(des, buttonText, &pauseButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button5.x, button5.y, BUTTON_WIDTH / 2, BUTTON_HEIGHT / 2 };
			SDL_RenderCopy(des, buttonText, &pauseButton[0], &src);
		}
		

	}
}

void Menu::RenderRetryMenu(SDL_Renderer* des,Mix_Chunk* menuSFX[],Menu menu)
{
	if (retry_)
	{
		
		if (selected[7])
		{
			SDL_Rect src = { button7.x, button7.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &retryButton[1], &src);
		}
		else if (pressed[7])
		{
			SDL_Rect src = { button7.x, button7.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &retryButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button7.x, button7.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &retryButton[0], &src);
		}

		if (selected[10])
		{
			SDL_Rect src = { button10.x, button10.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[1], &src);
		}
		else if (pressed[10])
		{
			SDL_Rect src = { button10.x, button10.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button10.x, button10.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
	}
}

/*void Menu::RenderWinMenu(SDL_Renderer* des, Mix_Chunk* menuSFX[])
{
	if (win_)
	{
		if (selected[9])
		{
			SDL_Rect src = { button9.x, button9.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &retryButton[1], &src);
		}
		else if (pressed[9])
		{
			SDL_Rect src = { button9.x, button9.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &retryButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button9.x, button9.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &retryButton[0], &src);
		}

		if (selected[11])
		{
			SDL_Rect src = { button11.x, button11.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[1], &src);
		}
		else if (pressed[11])
		{
			SDL_Rect src = { button11.x, button11.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button11.x, button11.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
	}
}*/

void Menu::RenderExitMenu(SDL_Renderer* des)
{
	if (exit_)
	{
		if (selected[12])
		{
			SDL_Rect src = { button12.x, button12.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &noButton[1], &src);
		}
		else if (pressed[12])
		{
			SDL_Rect src = { button12.x, button12.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &noButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button12.x, button12.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &noButton[0], &src);
		}

		if (selected[13])
		{
			SDL_Rect src = { button13.x, button13.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &yesButton[1], &src);
		}
		else if (pressed[13])
		{
			SDL_Rect src = { button13.x, button13.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &yesButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button13.x, button13.y, BUTTON_WIDTH, BUTTON_HEIGHT };
			SDL_RenderCopy(des, buttonText, &yesButton[0], &src);
		}
	}
}

void Menu::RenderGuideMenu(SDL_Renderer* des)
{
	if (guide)
	{
		if (selected[15])
		{
			SDL_Rect src = { button15.x, button15.y, BUTTON_WIDTH/2, BUTTON_HEIGHT/2 };
			SDL_RenderCopy(des, buttonText, &exitButton[1], &src);
		}
		else if (pressed[15])
		{
			SDL_Rect src = { button15.x, button15.y, BUTTON_WIDTH/2, BUTTON_HEIGHT/2 };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
		else
		{
			SDL_Rect src = { button15.x, button15.y, BUTTON_WIDTH/2, BUTTON_HEIGHT/2 };
			SDL_RenderCopy(des, buttonText, &exitButton[0], &src);
		}
	}
}


