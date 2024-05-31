
#ifndef BOSS_H
#define BOSS_H

#include "BaseObject.h"
#include "CommonFunction.h"

#define GRAVITY_BOSS 1.0
#define MAX_FALL_SPEED 10
#define BOSS_SPEED 2
#define BOSS_HIGH_VAL 18 
#define BOSS_HP 9
#define BOSS_FRAME_NUM 6
#define BLANK_TILE 0

using namespace std;

class Boss : public BaseObject
{
public:
    Boss();
    ~Boss();
    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,

    };

    void set_x_val(double x_val_){x_val = x_val_;}
    void set_y_val(double y_val_){y_val = y_val_;}

    void set_x_pos(const int& xp_){ x_pos = xp_;}
    void set_y_pos(const int& yp_) {y_pos = yp_;}
    int get_x_pos() {return x_pos;}
    int get_y_pos() {return y_pos;}

    void Show(SDL_Renderer* des);
    bool LoadImg(string path, SDL_Renderer* screen);
    void set_clips_();
    void reset();

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    void SetMapXY(const int& map_x, const int& map_y) 
    {
        map_x_ = map_x;
        map_y_= map_y;
    }
    SDL_Rect GetRectFRAME();

    void CheckToMap(Map& map_data );
    void CenterOnMap(Map& map_data);
    void DoPlayer(Map& map_data);
    void InitBoss();
    void HP_BOSS_Decrease() {health_boss -= 1;}
    int get_boss_HP() const {return health_boss;}
    void boss_renderHP(SDL_Renderer* des, Boss* bosses);

    void set_type_move(const int& typeMove) {type_move_ = typeMove;}
    void SetAnimationPos(const int& pos_a, const int& pos_b) {animation_a_ = pos_a, animation_b_ = pos_b;}
    void set_input_left(const int& ipLeft) {input_type_.left_ = ipLeft;};
    void ImpMoveType(SDL_Renderer* screen);


private:
    int map_x_;
    int map_y_;
    double x_val;
    double y_val;
    int x_pos;
    int y_pos;
    int width_frame_;
    int height_frame_;
    bool on_ground;
    int return_time;
    int frame_;
    SDL_Rect frame_clip_[BOSS_FRAME_NUM];
    Input input_type_;
    int last_fr_;
    int health_boss;
    int type_move_;
    int animation_a_;
    int animation_b_;

};


#endif