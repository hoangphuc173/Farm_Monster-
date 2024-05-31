#ifndef MONSTER_H_
#define MONSTER_H_

#define GRAVITY_SPEED 0.8
#define MAX_GRAVITY_SPEED 8
#define MONSTER_FRAME_NUM 8
#define THREAT_SPEED 3

#include "CommonFunction.h"
#include "BaseObject.h"

using namespace std;

class Monster : public BaseObject
{
public:
    Monster();
    ~Monster();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,

    };

    void set_x_val(const double& xVal) { x_val_ = xVal;}
    void set_y_val(const double& yVal) { y_val_ = yVal;}

    void set_x_pos(const double& xPos) { x_pos_ = xPos;}
    void set_y_pos(const double& yPos) { y_pos_ = yPos;}
    double get_x_pos() const{return x_pos_;}
    double get_y_pos() const{return y_pos_;}
    void setMapXY(const int& mp_x, const int& mp_y) {map_x_ = mp_x , map_y_ = mp_y;}

    void set_clips();
    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);

    int get_width_frame() const{return width_frame_;}
    int get_height_frame() const{return height_frame_;}

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);

    void set_type_move(const int& typeMove) {type_move_ = typeMove;}
    void SetAnimationPos(const int& pos_a, const int& pos_b) {animation_a_ = pos_a, animation_b_ = pos_b;}
    void set_input_left(const int& ipLeft) {input_type_.left_ = ipLeft;};
    void ImpMoveType(SDL_Renderer* screen);

   SDL_Rect GetRectFrame();

private:
    double x_pos_;
    double y_pos_;
    double x_val_;
    double y_val_;
    int map_x_;
    int map_y_;
    int width_frame_;
    int height_frame_;
    int frame_;
    SDL_Rect frame_clip_[MONSTER_FRAME_NUM];
    int come_back_time_;
    bool on_ground_; 

    int type_move_;
    int animation_a_;
    int animation_b_;
    Input input_type_;

    

};
#endif