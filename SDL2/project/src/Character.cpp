#include "Character.h"

using namespace std;

Character::Character()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = 0;
    input_type_.left_= 0;
    input_type_.right_ = 0;
    input_type_.jump_ = 0;
    input_type_.down_ = 0;
    input_type_.up_ = 0;
    input_type_.attack_ = 0;
    on_ground_ = false;
    return_time_ = 0;
    attack_ = false;
    map_x_ = 0;
    map_y_ = 0;
}

Character::~Character()
{
    free;
}

bool Character::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);  //dung vistual o baseobject

    if(ret == true)
    {
        width_frame_ = rect_.w/10;
        height_frame_ = rect_.h;
    }
    return ret;
}

void Character::set_clip()
{
    if(width_frame_ > 0 && height_frame_ > 0)
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

        frame_clip_[8].x = 8 * width_frame_;
        frame_clip_[8].y = 0;
        frame_clip_[8].w = width_frame_;
        frame_clip_[8].h = height_frame_;

        frame_clip_[9].x = 9 * width_frame_;
        frame_clip_[9].y = 0;
        frame_clip_[9].w = width_frame_;
        frame_clip_[9].h = height_frame_;
    }   
} 

//LOAD animation
void Character::Show(SDL_Renderer* des)
{
    if (status_ == WALK_LEFT)
    {
        if(on_ground_ == true)
        {
            LoadImg("C:/recover/SDL2/project/data/images/run_left.png", des);
            if(attack_ == true)
            {
                LoadImg("C:/recover/SDL2/project/data/images/attack_left.png", des);
            }
        }
        else if (on_ground_ == false)
        {
            LoadImg("C:/recover/SDL2/project/data/images/jump_left.png", des);
            if(attack_ == true)
            {
                LoadImg("C:/recover/SDL2/project/data/images/attack_left.png", des);
            }
        }
    }
    else if( status_ == WALK_RIGHT)
    {
        if(on_ground_ == true)
        {
            LoadImg("C:/recover/SDL2/project/data/images/run_right.png", des);
            if(attack_ == true)
            {
                LoadImg("C:/recover/SDL2/project/data/images/attack_right.png", des);
            }
        }
        else if(on_ground_ == false)
        {
            LoadImg("C:/recover/SDL2/project/data/images/jump_right.png", des);
            if(attack_ == true)
            {
                LoadImg("C:/recover/SDL2/project/data/images/attack_right.png", des);
            }
        }
    }

    if(input_type_.left_ == 1 || input_type_.right_ == 1 || input_type_.jump_ == 1 || input_type_.attack_ == 1)
    {
        frame_++;
    }
    else 
    {
        frame_ = 0;
    }
    if(frame_ >=8 )
    {
        frame_ = 0;
    }

    rect_.x = x_pos_ - map_x_;
    rect_.y = y_pos_ - map_y_;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect rendererQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_object_, current_clip, &rendererQuad);
}

//xử lý bàn phím
void Character::InputAction(SDL_Event events, SDL_Renderer* screen)
{
    if( events.type == SDL_KEYDOWN)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_RIGHT:
            {
                status_ = WALK_RIGHT;
                input_type_.right_ = 1;
            }
            break;
             
            case SDLK_LEFT:
            {
                status_ = WALK_LEFT;
                input_type_.left_ = 1;
            }   
            break;  

            case SDLK_SPACE:
            {
                input_type_.jump_ = 1;
            }  
            break;    
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch (events.key.keysym.sym)
        {
            case SDLK_RIGHT:
            {
                input_type_.right_ = 0;
            }
            break;
             
            case SDLK_LEFT:
            {
                input_type_.left_ = 0;
            }   
            break;

            case SDLK_SPACE:
            {
                input_type_.jump_ = 0;
            }
            break;
        }
    }
    if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        switch(events.button.button)
        {
            case SDL_BUTTON_LEFT:
            {
                input_type_.attack_ = 1;
                attack_ = true;
            }
            break;
        }
    }    
    else if(events.type == SDL_MOUSEBUTTONUP)
    {
        switch(events.button.button)
        {
        case SDL_BUTTON_LEFT:
        {
            input_type_.attack_ = 0;
            attack_ = false;
        }
        break;
        }
    }
}


void Character::CenterOnMap(Map& map_data)
{
    map_data.start_x_ = x_pos_ - (SCREEN_WIDTH /3);
    if(map_data.start_x_ < 0)
    {
        map_data.start_x_ = 0;
    }
    else if(map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
    {
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = y_pos_ -(SCREEN_HEIGHT / 2);
    if(map_data.start_y_ <0 )
    {
        map_data.start_y_ = 0;
    }
    else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_)
    {
        map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}

void Character::DoPlayer(Map& map_data)
{
    if(return_time_ == 0)
    {
       x_val_ = 0;
       y_val_ += GRAVITY_SPEED;
       if(y_val_ >= MAX_GRAVITY_SPEED)
       {
           y_val_ = MAX_GRAVITY_SPEED;
       }

       if(input_type_.right_ == 1)
       {
           x_val_ += PLAYER_SPEED;
       }
       else if(input_type_.left_ == 1)
       {
           x_val_ -= PLAYER_SPEED;
       }
       if(input_type_.jump_ == 1)
       {
           if(on_ground_ == true)
           {
              y_val_ = - PLAYER_JUMP_VAL;
           }
           on_ground_ = false;
           input_type_.jump_ = 0;
       }
       CheckMap(map_data);
       CenterOnMap(map_data);
    }
    if(return_time_ > 0)
    {
        return_time_ -- ;
       if(return_time_ == 0)
       {
          y_pos_ = 0;
          x_val_ = 0;
          y_val_ = 0;
       }
    }
    
}

//
/// @param map_data 
void Character::CheckMap(Map& map_data)
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
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if(x_val_ < 0)
        {
            if(map_data.tile[y1][x1]!= BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
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
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile [y2][x2] != BLANK_TILE)
            {
                y_pos_ = y2* TILE_SIZE;
                y_pos_ -= (height_frame_ + 1);
                y_val_ = 0;
                on_ground_ = true;
            }
        }
        if(y_val_ < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile [y1][x2] != BLANK_TILE)
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
        return_time_ = 10;
    }
}

SDL_Rect Character::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

bool Character::Attack()
{
    if(attack_ == false ) return false;
    return true;
}


