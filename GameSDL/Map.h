#ifndef MAP_H_
#define MAP_H_


#include "BaseObject.h"
#include "CommonFunc.h"


class TileMat : public BaseObject// ke thua 
{
public:
	TileMat() { ; }
	~TileMat() { ; }
private:
	SDL_Rect Collision;
};

class GameMap// quan ly tile
{
public :
	GameMap() { ; }
	~GameMap() { ; }

	void LoadMap_text(std::string  name);
	void LoadTile(SDL_Renderer* screen);
	void DrawTile(SDL_Renderer* screen, SDL_Rect& camera);
	map Get_map() const  { return game_map_; };
	void SetMap(map& map_data) { game_map_ = map_data; };
	void SetMapSTT(int p_mapSTT)
	{
		mapSTT = p_mapSTT;
		map_start = mapSTT * LEVEL_WIDTH;
	}
	int GetStartX() const { return map_start; };
private :
	map game_map_;
	TileMat tile_mat[90];// baseobject
	int mapSTT;
	int map_start;
};


#endif // !MAP_H_

