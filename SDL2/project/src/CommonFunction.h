#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <bits/stdc++.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include <memory>


static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event ;



//screen
const int FRAME_PER_SECOND = 60;   //FPS
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B =180;

const int RENDER_DRAW_COLOR = 0Xff;


#define TILE_SIZE 64
#define MAX_MAP_X 200
#define MAX_MAP_Y 10

//input
struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
    int attack_;
};
//map
struct Map 
{
    int start_x_; //vi tri theo toa do x
    int start_y_;

    int max_x_;     // vi tri theo ô
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLCommonFunction
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}

#endif