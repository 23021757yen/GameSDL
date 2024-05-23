#ifndef MENU_H_
#define MENU_H_

#pragma once
#include "CommonFunc.h"
#include "BaseObject.h"
#include "Character.h"

class Chaacter;
class Menu : BaseObject
{
public:
	Menu();
	~Menu() { ; };
	void HandleInput(SDL_Event& event, Mix_Chunk* p_sfx[]);
	bool checkMouse(const int& p_x, const int& p_y);  // toạ đọ của cái nút
	bool Load_Img(std::string p_path, SDL_Renderer* des);
	void SetButton();
	int Num() { return num; };

	void RenderMainMenu(SDL_Renderer* des);
	void RenderChooseMenu(SDL_Renderer* des);
	void RenderPauseMenu(SDL_Renderer* des);
	void RenderRetryMenu(SDL_Renderer* des,Mix_Chunk* menuSFX[],Menu menu);// bao gom viec nhan vat chet hoac la di het duong nma chua het quai(bao gom ca score)
	void RenderContinueMenu(SDL_Renderer* des);
	//void RenderWinMenu(SDL_Renderer* des, Mix_Chunk* menuSFX[]);
	void RenderExitMenu(SDL_Renderer* des);
	void RenderGuideMenu(SDL_Renderer* des);

	bool isMenu() const { return menu_; };
	bool isChoose() const { return choose_; };
	bool isRetry() const { return retry_; };
	bool isPause() const { return pause_; };
	
	//bool isWin() const { return win_; };
	bool isExit() const { return exit_; };
	bool isGuide() const { return guide; };
	bool isCheck_1() const { return check_choose_1; }; // khi clean rooif mình ko dùng cái này nữa thay bằng cái này
	bool isCheck_2() const { return check_choose_2; };
	bool isContinue() const { return continue_game; };
	bool GetNumPlayer() const { return num_player; };
	bool isOnsound() const { return onsound; };
	bool isMute() const { return mute; };
	void SetRetry(bool p_retry) { retry_ = p_retry; };
	//void SetWin(bool p_win) { win_ = p_win; };
	enum
	{
		clickSFX = 4,
	};
	
private:
	const int BUTTON_WIDTH = 128;
	const int BUTTON_HEIGHT = 128;


	static const int BUTTON_TYPE = 3;
	static const int BUTTON_TYPE_CHOOSE = 5;

	SDL_Rect playButton[BUTTON_TYPE]; // lưu toạ đổ vị trí nút trong ảnh
	SDL_Rect exitButton[BUTTON_TYPE]; 
	SDL_Rect soundButton[BUTTON_TYPE];
	SDL_Rect muteButton[BUTTON_TYPE];
	SDL_Rect chooseButton_1_1[BUTTON_TYPE_CHOOSE];
	SDL_Rect chooseButton_1_2[BUTTON_TYPE_CHOOSE];
	SDL_Rect chooseButton_1_3[BUTTON_TYPE_CHOOSE];
	SDL_Rect chooseButton_2_1[BUTTON_TYPE_CHOOSE];
	SDL_Rect chooseButton_2_2[BUTTON_TYPE_CHOOSE];
	SDL_Rect chooseButton_2_3[BUTTON_TYPE_CHOOSE];
	SDL_Rect guideButton[BUTTON_TYPE];
	SDL_Rect pauseButton[BUTTON_TYPE];
	SDL_Rect continueButton[BUTTON_TYPE];
	SDL_Rect retryButton[BUTTON_TYPE];
	SDL_Rect yesButton[BUTTON_TYPE];
	SDL_Rect noButton[BUTTON_TYPE];

	SDL_Point button0 = { 560,220}; // nút play
	SDL_Point button1 = { 560,360}; // nut exit
	SDL_Point button2 = { 1210 -80,30 }; // nut sound
	SDL_Point button3 = { 50, 120 };// nut chon nhan vat 1 // set vij tri sai thi cx lien quan den vu load dau
	SDL_Point button4 = { 700 , 120 }; // nut chon nhan vat 2

	SDL_Point button5 = { 1210-10,30}; //nut ngung game;
	SDL_Point button6 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 , SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2+50 }; // nut tiep tuc game;
	SDL_Point button7 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 -300, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 +50};// retry menu thua
	SDL_Point button8 = { 10,30 };//nut exit or menu chinh
	//SDL_Point button9 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 50 };// retry o menu win
	SDL_Point button10 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 +300, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 50 };//nut exit menu thua
	//SDL_Point button11 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 + 300, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 50 };//nut exit menu win
	SDL_Point button12 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 100 };//yes->no
	SDL_Point button13 = { SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2 + 100 };//no->yes
	SDL_Point button14 = { 560,500 };// guide
	SDL_Point button15 = { 10,30 };// exit guidemenu

	bool menu_ = true; 
	bool choose_ = false; 
	bool retry_ = false;
	bool guide = false;
	bool pause_ = false;
	bool continue_game = false;
	bool check_choose_1 = false;
	bool check_choose_2 = false;
	bool onsound = true;
	bool mute = false;
	//bool win_ = false;
	bool exit_ = false;
	
	int num = 0;// luu trangthai truoc khi exit

	SDL_Texture* bgText = NULL;
	SDL_Texture* buttonText = NULL;

	bool selected[16] = { false }; 
	bool pressed[16] = { false };

	bool quit_ = false;

	int idle_choose = 0;
	int delay = 3;
	int num_player = -1;
};



#endif // !MENU_H_

