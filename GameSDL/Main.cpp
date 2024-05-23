
#include "Game.h"

int main(int argc, char* argv[])
{
	Game game;
	srand(time(NULL));
	if (!game.Init())
	{
		return -1;
	}
	if (!game.LoadMedia() || !game.CreateBackground() || !game.CreateMap() || !game.CreateMenu() || !game.CreateCharacter() || !game.CreateMonster())
	{
		return -1;
	}
	while (game.isRunning())
	{
		game.PlayMusic();
		while (SDL_PollEvent(&e) != 0)
		{
			game.HandleGameInput(e);
		}
		if (game.GetMenuList().at(0).isMenu())
		{
			game.Render_MainMenu();
		}
		else if (game.GetMenuList().at(0).isChoose())
		{
			game.Render_ChooseMenu();
		}
		else if (game.GetMenuList().at(0).isPause())
		{
			game.Render_PauseMenu();
		}
		else if (game.GetMenuList().at(0).isRetry())
		{
			game.Render_RetryMenu();
		}
		else if (game.GetMenuList().at(0).isExit())
		{
			game.Render_ExitMenu();
		}
		else if (game.GetMenuList().at(0).isGuide())
		{
			game.Render_GuideMenu();
		}
		else
		{
			game.Render_ContinueMenu();
		}
	}
	game.Delete_game();
	
	return 0;
}