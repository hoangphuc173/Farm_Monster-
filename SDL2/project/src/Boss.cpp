
#include "Boss.h"
using namespace std;

Boss::Boss() 
{
    frame_ = 0;
    x_val = 0.0;
    y_val = 0.0;
    x_pos = 0;
    y_pos = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    return_time = 0;
    map_y_ = 0;
    map_x_ = 0;
    on_ground = false;
    last_fr_ = 0;
    health_boss = 9;
    type_move_ = STATIC_THREAT;
}

Boss::~Boss()
{

}

void Boss::reset() 
{
    frame_ = 0;
    return_time = 0;
    map_y_ = 0;
    map_x_ = 0;
    on_ground = false;
    last_fr_ = 0;
    health_boss = 9;
    type_move_ = STATIC_THREAT;
}

bool Boss::LoadImg(std::string path, SDL_Renderer *screen) 
{
    bool ret = BaseObject::LoadImg(path, screen);
    if(ret== true){
        width_frame_ = rect_.w/BOSS_FRAME_NUM;
        height_frame_ =rect_.h;
    }
    return ret;
}



void Boss::set_clips_() 
{
    if(width_frame_ > 0 && height_frame_ > 0){
        for(int i = 0; i < BOSS_FRAME_NUM; i++){
            frame_clip_[i].x = width_frame_*i;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void Boss::Show(SDL_Renderer *des) {
    if(return_time == 0){
        rect_.x = x_pos - map_x_;
        rect_.y = y_pos - map_y_;

        int frameDelay = 5000 / FRAME_PER_SECOND;

        Uint32 currentFrameTime = SDL_GetTicks() - last_fr_;
        if (currentFrameTime >= frameDelay) {
            frame_++;
            if (frame_ >= 6) frame_ = 0;
            last_fr_ = SDL_GetTicks();
        }

        SDL_Rect* current_clip = &frame_clip_[frame_];

        SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
        if(current_clip != NULL){
            renderQuad.w = current_clip->w;
            renderQuad.h = current_clip->h;
        }

        SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
    }
}

void Boss::DoPlayer(Map &map_data) {
    if(return_time == 0){
         x_val = 0;
        y_val += GRAVITY_BOSS;
        if(y_val > MAX_FALL_SPEED )
        {
            y_val = MAX_FALL_SPEED;
        }

        if(input_type_.left_ == 1)
        {
            x_val -= BOSS_SPEED;
        }
        else if(input_type_.right_ == 1){
            x_val += BOSS_SPEED;
        }
        CheckToMap(map_data);
        
    }
    else if(return_time > 0){
        return_time --;
        if(return_time == 0)
        { 
            InitBoss();
        }
    }
}

void Boss::InitBoss() {
    y_pos = 0;
    x_val = 0;
    y_val = 0;
    if(x_pos > 256)
    {
        x_pos -= 256;
        animation_a_ -= 256;
        animation_b_ -= 256;
    }
    else x_pos = 0;
    input_type_.left_ = 1;;
}



void Boss::CenterOnMap(Map &map_data) 
{
    map_data.start_x_ = (int) x_pos - (SCREEN_WIDTH/2);
    if(map_data.start_x_ < 0){
        map_data.start_x_ = 0;
    }
    else if(map_data.start_x_ + (SCREEN_WIDTH) >= map_data.max_x_){
        map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
    }

    map_data.start_y_ = (int) y_pos - (SCREEN_HEIGHT/2);
    if(map_data.start_y_ < 0){
        map_data.start_y_= 0;
    }
    else if(map_data.start_y_+ (SCREEN_HEIGHT) >= map_data.max_y_){
       map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
    }
}

void Boss::CheckToMap(Map &map_data)
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

    x1 = (x_pos+ x_val)/TILE_SIZE;
    x2 = (x_pos + x_val+ width_frame_ - 1 )/TILE_SIZE;

    y1 = y_pos/TILE_SIZE;
    y2 = (y_pos +  height_min - 1)/TILE_SIZE;

    if(x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
    {
        if(x_val > 0)
        {
            if(map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
            {
                x_pos = x2 * TILE_SIZE;
                x_pos -= width_frame_ + 1;
                x_val = 0;
            }
        }
        else if(x_val < 0)
        {
            if(map_data.tile[y1][x1]!= BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
            {
                x_pos = (x1 + 1)* TILE_SIZE;
                x_val = 0;
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

    x1 = x_pos / TILE_SIZE;
    x2 = (x_pos + width_min)/TILE_SIZE;

    y1 = (y_pos + y_val)/TILE_SIZE;
    y2 = (y_pos + y_val + height_min -1 )/TILE_SIZE;

    if(x1>=0 && x2 < MAX_MAP_X && y1 >=0 && y2 < MAX_MAP_Y)
    {
        if(y_val > 0)
        {
            if(map_data.tile[y2][x1] != BLANK_TILE || map_data.tile [y2][x2] != BLANK_TILE)
            {
                y_pos = y2* TILE_SIZE;
                y_pos -= (height_frame_ + 1);
                y_val = 0;
                on_ground = true;
            }
        }
        if(y_val < 0)
        {
            if(map_data.tile[y1][x1] != BLANK_TILE || map_data.tile [y1][x2] != BLANK_TILE)
            {
                y_pos = (y1 + 1)*TILE_SIZE;
                y_val = 0;
            }
        }
    }
    x_pos += x_val;
    y_pos += y_val;

    if(x_pos < 0)
    {
        x_pos = 0;
    }
    else if(x_pos + width_frame_ > map_data.max_x_)
    {
        x_pos = map_data.max_x_ - width_frame_ -1;
    }
    
    if(y_pos > map_data.max_y_)
    {
        return_time = 10;
    }
}


SDL_Rect Boss::GetRectFRAME() {
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_; 
    rect.h = height_frame_;

    return rect;
}



void Boss::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move_ == STATIC_THREAT)
    {
             LoadImg("C:/recover/SDL2/project/data/images/boss_left.png",screen);
    }
    else 
    {
        if(on_ground == true)
        {
            if(x_pos > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("C:/recover/SDL2/project/data/images/boss_left.png",screen);
            }
            else if(x_pos < animation_a_)
            {
                input_type_.right_ = 1;
                input_type_.left_ =0;
                LoadImg("C:/recover/SDL2/project/data/images/boss_left.png",screen);
            }
        }
        else 
        {
            if(input_type_.left_ == 1)
            {
                LoadImg("C:/recover/SDL2/project/data/images/boss_left.png",screen);
            }
            else if(input_type_.right_ == 1)
            {
               LoadImg("C:/recover/SDL2/project/data/images/boss_left.png",screen); 
            }
        }
    }
}

void Boss::boss_renderHP(SDL_Renderer *des, Boss *bosses) {
    int current_hp = bosses->get_boss_HP();
    int maxHP = BOSS_HP;
    if(current_hp >= 0){
        double ratioHealth = (double)current_hp/(double)maxHP;
        int healthBarLen = (int)(BOSS_HP * ratioHealth); ///

        SDL_Rect HP_Bar = {bosses->GetRectFRAME().x + 25, bosses->GetRectFRAME().y - 25, healthBarLen, 30};

        SDL_SetRenderDrawColor(des, 255, 0, 0, 255); // Red bar
        SDL_RenderFillRect(des, &HP_Bar);
    }

}


