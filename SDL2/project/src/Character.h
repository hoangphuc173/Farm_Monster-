#ifndef CHARACTER_H_
#define CHARACTER_H_

#define GRAVITY_SPEED 0.8
#define MAX_GRAVITY_SPEED 8
#define PLAYER_SPEED 7
#define BLANK_TILE 0
#define PLAYER_JUMP_VAL 20

#include "CommonFunction.h"
#include "BaseObject.h"

using namespace std;

class Character : public BaseObject
{
public:
    Character() ;
    ~Character() ;

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void InputAction(SDL_Event, SDL_Renderer* screen);  //đầu vào bàn phím
    void set_clip();
    
    void DoPlayer(Map& map_data );
    void CheckMap(Map& map_data);

    void SetMapXY(const int& map_x, const int& map_y) {map_x_ = map_x, map_y_ = map_y ;}
    void CenterOnMap(Map& map_data);

    void set_return_time(const int& time) {return_time_ = time;}

    SDL_Rect GetRectFrame();

    bool Attack();


private:
    double x_val_;    //biến di chuyển
    double y_val_;

    double x_pos_;    //biến vị trí hiện tại
    double y_pos_;

    int width_frame_;
    int height_frame_;

    int map_x_;
    int map_y_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_;
    bool attack_;
    int return_time_;  // thời gian hồi sinh
};

#endif