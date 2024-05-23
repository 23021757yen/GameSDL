#ifndef ITEM_H_
#define ITEM_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "Map.h"

class Item : BaseObject
{
public:

	Item(float p_x, float p_y, SDL_RendererFlip p_flip); // set clip
	~Item() { Free(); };

	bool Load_Img(std::string path, SDL_Renderer* des);
	float getX() const { return x_pos; };
	float getY() const { return y_pos; };
	void Update(std::vector<map>& map_data);
	void Show(SDL_Renderer* des, SDL_Rect& camera);
	void SetMove(bool p_move) { move_ = p_move; };
	void SetColor(bool p_color) { color_ = p_color; }; //SetColor(true);
	bool GetMove() const { return move_; };
	void SetPosition(float p_x, float p_y);
	SDL_Rect GetCollision() const { return collision; }; //đạn có va chạm nên chắc chắc cái này có

private:
	float x_val;

	float x_pos;
	float y_pos;

	SDL_Rect collision;

	const int FRAME_WIDTH = 32;
	const int FRAME_HEIGHT = 32;
	const float ITEM_VAL = 10;

	static const int FRAME_YELLOW = 4;
	static const int FRAME_BLUE = 4;

	int delay = 10;

	int cnt_yellow = 0;
	int cnt_blue = 0;

	bool move_ = false;
	bool color_ = false;

	SDL_Rect clip_bullet_yellow[FRAME_YELLOW];
	SDL_Rect clip_bullet_blue[FRAME_BLUE];

};

#endif // !ITEM_H_

