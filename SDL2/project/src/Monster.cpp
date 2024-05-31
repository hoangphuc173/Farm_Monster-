#include "Monster.h"

using namespace std;

Monster::Monster()
{
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    on_ground_ =  false;
    frame_ = 0;
    come_back_time_ = 0;
    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 1;
    type_move_ = STATIC_THREAT;
}

Monster::~Monster()
{
    free;
}

bool Monster::LoadImg( string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);
    
    if(ret ==  true)
    {
        width_frame_ = rect_.w/8;
        height_frame_ = rect_.h;
    }
    return ret;
}

void Monster::set_clips()
{
    frame_clip_[0].x = 0;
    frame_clip_[0].y = 0;
    frame_clip_[0].w = width_frame_;
    frame_clip_[0].h = height_frame_;

    frame_clip_[1].x = width_frame_;
    frame_clip_[1].y = 0;
    frame_clip_[1].w = width_frame_;
    frame_clip_[1].h = height_frame_;

    frame_clip_[2].x = 2*width_frame_;
    frame_clip_[2].y = 0;
    frame_clip_[2].w = width_frame_;
    frame_clip_[2].h = height_frame_;

    frame_clip_[3].x = 3*width_frame_;
    frame_clip_[3].y = 0;
    frame_clip_[3].w = width_frame_;
    frame_clip_[3].h = height_frame_;

    frame_clip_[4].x = 4*width_frame_;
    frame_clip_[4].y = 0;
    frame_clip_[4].w = width_frame_;
    frame_clip_[4].h = height_frame_;

    frame_clip_[5].x = 5 * width_frame_;
    frame_clip_[5].y = 0;
    frame_clip_[5].w = width_frame_;
    frame_clip_[5].h = height_frame_;

    frame_clip_[6].x = 6 * width_frame_;
    frame_clip_[6].y = 0;
    frame_clip_[6].w = width_frame_;
    frame_clip_[6].h = height_frame_;

    frame_clip_[7].x = 7 * width_frame_;
    frame_clip_[7].y = 0;
    frame_clip_[7].w = width_frame_;
    frame_clip_[7].h = height_frame_;
}

//load quái
void Monster::Show(SDL_Renderer* des)
{
    if(come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_ ++ ;
        if(frame_ >=8)
        {
            frame_ = 0;
        }

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect rendererQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip, &rendererQuad);
    }
}

void Monster::DoPlayer(Map& map_data)
{
    if(come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;
        if(y_val_ > MAX_GRAVITY_SPEED )
        {
            y_val_ = MAX_GRAVITY_SPEED;
        }

        if(input_type_.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if(input_type_.right_ == 1){
            x_val_ += THREAT_SPEED;
        }

        CheckToMap(map_data);
    }
    else if(come_back_time_ > 0)
        {
            come_back_time_ --;
            if(come_back_time_ == 0)
            {
                y_pos_ = 0;
                x_val_ = 0;
                y_val_ = 0;
                if(x_pos_ > 256)
                {
                    x_pos_ -= 256;
                    animation_a_ -= 256;
                    animation_b_ -= 256;
                }
                else x_pos_ = 0;
                input_type_.left_ = 1;
            }
        }
}

void Monster::CheckToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    int height_min;
    if(height_frame_ >=  TILE_SIZE)
    {
        height_min = TILE_SIZE;
    }
    else if(height_frame_ < TILE_SIZE)
    {
        height_min = height_frame_;
    }

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1 )/TILE_SIZE;

    y1 = y_pos_/TILE_SIZE;
    y2 = (y_pos_ +  height_min - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if(x_val_ > 0)
        {
            if(map_data.tile[y1][x2] != 0 || map_data.tile[y2][x2] != 0)
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if(x_val_ < 0)
        {
            if(map_data.tile[y1][x1]!= 0 || map_data.tile[y2][x1] != 0)
            {
                x_pos_ = (x1 + 1)* TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    int width_min;
    if(width_frame_ > TILE_SIZE)
    {
        width_min = TILE_SIZE;
    }
    else 
    {
        width_min = width_frame_;
    }

    x1 = x_pos_ / TILE_SIZE;
    x2 = (x_pos_ + width_min)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_min -1 )/TILE_SIZE;

    if(x1>=0 && x2 < MAX_MAP_X && y1 >=0 && y2 < MAX_MAP_Y)
    {
        if(y_val_ > 0)
        {
            if(map_data.tile[y2][x1] != 0 || map_data.tile [y2][x2] != 0)
            {
                y_pos_ = y2* TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        if(y_val_ < 0)
        {
            if(map_data.tile[y1][x1] != 0 || map_data.tile [y1][x2] != 0)
            {
                y_pos_ = (y1 + 1)*TILE_SIZE;
                y_val_ = 0;
            }
        }
    }
    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame_ > map_data.max_x_)
    {
        x_pos_ = map_data.max_x_ - width_frame_ -1;
    }
    
    if(y_pos_ > map_data.max_y_)
    {
        come_back_time_ = 10;
    }
}

void Monster::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move_ == STATIC_THREAT)
    {

    }
    else 
    {
        if(on_ground_ == true)
        {
            if(x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("C:/recover/SDL2/project/data/images//threat_left.png",screen);
            }
            else if(x_pos_ < animation_a_)
            {
                input_type_.right_ = 1;
                input_type_.left_ =0;
                LoadImg("C:/recover/SDL2/project/data/images//threat_right.png",screen);
            }
        }
        else 
        {
            if(input_type_.left_ == 1)
            {
                LoadImg("C:/recover/SDL2/project/data/images//threat_left.png",screen);
            }
            else if(input_type_.right_ == 1)
            {
               LoadImg("C:/recover/SDL2/project/data/images//threat_right.png",screen); 
            }
        }
    }
}

SDL_Rect Monster::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

