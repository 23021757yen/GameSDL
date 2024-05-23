#include "CommonFunc.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
	p_object = nullptr;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

BaseObject::~BaseObject()
{
	//Free();
}

bool BaseObject::Load_Img(std::string path, SDL_Renderer* screen)
{
	Free();
	SDL_Texture* new_object = NULL;

	SDL_Surface* load_surface = IMG_Load(path.c_str());// IMG_Load: xoa phong, xet rect :))) tao texture gian tiep qua surface:)))
	
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, DRAW_COLOR_KEY, DRAW_COLOR_KEY, DRAW_COLOR_KEY)); 
		new_object = SDL_CreateTextureFromSurface(screen, load_surface);

		if (new_object != NULL)
		{
			rect.w = load_surface->w;
			rect.h = load_surface->h;
		}

		SDL_FreeSurface(load_surface);
	}
	else
	{
		std::cout << "LOAD_IMG ERROR" << SDL_GetError() << std::endl;
	}
	p_object = new_object;
	return p_object != NULL;

}

bool BaseObject::CreateTexture(std::string text, SDL_Color p_color, TTF_Font* p_font, SDL_Renderer* screen)
{
	SDL_Surface* text_surface = TTF_RenderText_Solid(p_font, text.c_str(), p_color);
	SDL_Texture* new_object = NULL;
	if (text_surface != NULL)
	{
		new_object = SDL_CreateTextureFromSurface(screen, text_surface);

		if (new_object == NULL)
		{
			std::cout << "LOAD_TTF ERROR" << TTF_GetError() << std::endl;
		}
		else
		{
			rect.w = text_surface->w;
			rect.h = text_surface->h;
		}

		SDL_FreeSurface(text_surface);
	}
	else
	{
		std::cout << "TTF ERROR " << TTF_GetError() << std::endl;
	}
	p_object = new_object;
	return p_object != NULL;
}


void BaseObject::Render(SDL_Renderer* des, SDL_Rect* clip, SDL_Rect& camera)
{
	SDL_Rect renderquad = { rect.x ,rect.y, rect.w  ,rect.h };
	if (clip != NULL)
	{
		renderquad.w = clip->w;
		renderquad.h = clip->h;
	}
	
	renderquad.x = rect.x - camera.x;
	renderquad.y = rect.y - camera.y;
	
	SDL_RenderCopy(des, p_object, clip, &renderquad);
	//std::cout << SDL_GetError() << std::endl;
}

void BaseObject::Free()
{
	if (p_object != nullptr)
	{
		SDL_DestroyTexture(p_object);
		p_object = nullptr;
		rect.w = 0;
		rect.h = 0;
	}
}