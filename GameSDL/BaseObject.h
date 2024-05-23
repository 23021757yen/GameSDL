

#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_


#include "CommonFunc.h"


class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	void setRect(const int& x, const int& y)
	{
		rect.x = x; 
		rect.y = y;
	}
	SDL_Rect getRect() const { return rect; }
	SDL_Texture* getObject() const { return p_object; }

	virtual bool Load_Img(std::string text, SDL_Renderer* screen);
	bool CreateTexture(std::string path, SDL_Color p_color, TTF_Font* p_font, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, SDL_Rect* clip, SDL_Rect& camrea);
	void Free();

	SDL_RendererFlip getFlip() const { return flip_type_; };


protected:
	SDL_Texture* p_object;
	SDL_Rect rect;
	SDL_RendererFlip flip_type_ = SDL_FLIP_NONE;
};
#endif // !BASE_OBJECT_H_