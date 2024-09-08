#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"


#define MAX_TILE 1000
class TileMat : public BaseObject
{
public:
	TileMat() { ; }
	~TileMat(){; }
};

class GameMap
{
public: 
	GameMap(){ ; }
	~GameMap(){ ; }
	void LoadMap(char *name);
	void LoadTiles(SDL_Renderer * screen);
	void DawnMap(SDL_Renderer * screen);
	Map getMap() const { return game_map_; }
	void SetMap(Map& map_data){ game_map_ = map_data; };

	void set_name_map( char* s){
		name_map = s;
	}
	char* get_name_map() { return name_map; }
private:
	Map game_map_;
	TileMat tile_map[MAX_TILE];

	char* name_map;
	
};




#endif