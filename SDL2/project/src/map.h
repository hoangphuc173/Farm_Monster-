#ifndef MAP_H_
#define MAP_H_

#define MAX_TILES 20  //số loại ô

#include "CommonFunction.h"
#include "BaseObject.h"

class TileMat : public BaseObject
{
    public:
      TileMat() {;}
      ~TileMat() {;}
};

class GameMap
{
    public:
        GameMap() {;}
        ~GameMap() {;}

        void LoadMap(char* name);
        void LoadTiles(SDL_Renderer* screen);
        void DrawMap(SDL_Renderer* screen);
        Map getMap() const{return game_map_ ;};
        void SetMap(Map& map_data){game_map_ = map_data ;};

private:
     Map game_map_;  //biến lưu thông tin map
     TileMat tile_mat[MAX_TILES];       //biến lưu hình ảnh

        
};

#endif