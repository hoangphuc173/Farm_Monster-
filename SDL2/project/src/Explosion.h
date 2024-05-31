#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "CommonFunction.h"
#include "BaseObject.h"

using namespace std;

class Explosion : public BaseObject
{
    public:
        Explosion();
        ~Explosion();

        void set_clips();
        void set_frame(int fr) {frame_ = fr;}
        bool LoadImg(string path, SDL_Renderer* screen);
        void Show(SDL_Renderer* des);
    
    private:
       
       int frame_;
       int width_frame_;
       int height_frame_;
       SDL_Rect frame_clip_[8];


};

#endif