#include "CommonFunction.h"
#include "BaseObject.h"
#include "map.h"
#include "Character.h"
#include "Timer.h"
#include "Monster.h"
#include "Explosion.h"
#include "Font.h"
#include "hp.h"
#include "Boss.h"

BaseObject g_background;

TTF_Font* font;

bool InitData()
{
   bool success = true;

   int ret = SDL_Init(SDL_INIT_VIDEO);
   if(ret < 0) 
       return false;

   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1"); 

   g_window = SDL_CreateWindow("Game",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

   if(g_window == NULL)  
        success = false;
   else 
   {
    g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
    if(g_screen == NULL)
         success = false;
    else 
    {
         SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
         int img_Flags= IMG_INIT_PNG;
         if(!IMG_Init(img_Flags) && img_Flags)
         success = false;
    }


    if(TTF_Init() == -1)    {success = false;}
    font = TTF_OpenFont("C:/recover/SDL2/project/data/font/font.ttf", 15);
    if(font == NULL)
    {
        success = false;
    }
   }
   return success;

   int ret2 = Mix_Init(0);

}



bool LoadBackground()
{
    bool ret = g_background.LoadImg("C:/recover/SDL2/project/data/images/background.png", g_screen);
    if(ret == false )
       return false;

    return true;
}

void close()
{
    
    g_background.~BaseObject();     // Giải phóng bộ nhớ của g_background
    
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();

}



//??
vector<Monster*> MonsterList()
{
    vector<Monster*> list_monster;


    Monster* dynamic_monster = new Monster[10];
    for(int i=0;i<10;i++)
    {
        Monster* p_monster = dynamic_monster + i;
        if(p_monster != NULL)
        {
            p_monster -> LoadImg("C:/recover/SDL2/project/data/images/threat_left.png",g_screen);
            p_monster ->set_clips();
            p_monster ->set_type_move(Monster::MOVE_IN_SPACE_THREAT);
            p_monster -> set_x_pos(500+i*1000);
            p_monster -> set_y_pos(250);

            int pos1 = p_monster -> get_x_pos() - 60;
            int pos2 = p_monster -> get_x_pos() + 60;
            p_monster -> SetAnimationPos(pos1,pos2);

            list_monster.push_back(p_monster);
        }
    }
    Monster* monster_obj = new Monster[10];

    for(int i=0; i<10; i++)
    {   
        Monster* p_monster = monster_obj + i;
       if(p_monster != NULL)
       {
        p_monster -> LoadImg("C:/recover/SDL2/project/data/images/monster.png",g_screen);
        p_monster -> set_clips();
        p_monster -> set_type_move(Monster::STATIC_THREAT);
        p_monster -> set_input_left(0);
        p_monster -> set_x_pos(300+1000*i);
        p_monster -> set_y_pos(250);

        list_monster.push_back(p_monster); 
       }
    }
    return list_monster;
}

    vector<Boss*> BossList()
    {
    vector<Boss*> list_boss;
    Boss* boss_obj = new Boss[10];

    for(int i=0; i<10; i++)
    {   
        Boss* bossObject = boss_obj + i;
       if(bossObject != NULL)
       {
        bossObject -> LoadImg("C:/recover/SDL2/project/data/images/boss_left.png",g_screen);
        bossObject -> set_clips_();
        bossObject -> set_type_move(Boss::STATIC_THREAT);
        bossObject -> set_input_left(0);
        bossObject -> set_x_pos(400+2000*i);
        bossObject -> set_y_pos(250);

        list_boss.push_back(bossObject); 
       }
    }
    return list_boss;
    }




int main(int argc, char* argv[])
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *  music  = Mix_LoadMUS("C:/recover/SDL2/project/data/audio/sound_game.wav");
    if(!music)
    {
        cout<<"Music Error"<<Mix_GetError() <<endl;
    }
    Mix_Chunk* sound = Mix_LoadWAV("C:/recover/SDL2/project/data/audio/explosion.wav");
    if(!sound)
    {
        cout<<"Sound Error" << Mix_GetError() <<endl;

    }

    Mix_PlayMusic(music, -1);

    Timer fps_time;
    if(InitData() ==  false )
        return -1;
    if(LoadBackground() == false )
        return -1;
    
    
    GameMap game_map;
    char data[] = "C:/recover/SDL2/project/data/map/map01.dat";
    game_map.LoadMap(data);
    game_map.LoadTiles(g_screen); 


    Character p_player;
    p_player.LoadImg("C:/recover/SDL2/project/data/images/Idle_character.png", g_screen);
    p_player.set_clip();


    vector<Monster*> monster_list = MonsterList();

    vector<Boss*> boss_list = BossList();


    


    Explosion p_explosion;
    bool expRet = p_explosion.LoadImg("C:/recover/SDL2/project/data/images/explosion.png", g_screen) ;
    p_explosion.set_clips();


    int hp_player = 3;


    Font time_game;   
    time_game.SetColor(Font::WHITE_TEXT);
    Font font_point;
    font_point.SetColor(Font::BLACK_TEXT);
    UINT point = 0;


    hp health_player;
    health_player.Init(g_screen);
    


    bool is_quit = false ;
    while(!is_quit) 
    {
        
        fps_time.start();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }

            p_player.InputAction(g_event, g_screen);
        }
     
        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen,NULL);

        Map map_data = game_map.getMap();

        health_player.Show(g_screen);

 
        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);


        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);


        SDL_Rect rect_player = p_player.GetRectFrame();
        for(int i=0; i < monster_list.size(); i++)
        {
            Monster*  p_monster = monster_list.at(i);
            if(p_monster != NULL)
            {
                p_monster -> setMapXY(map_data.start_x_, map_data.start_y_);
                p_monster -> ImpMoveType(g_screen);
                p_monster -> DoPlayer(map_data);
                p_monster -> Show(g_screen);



                
                SDL_Rect  rect_monster = p_monster->GetRectFrame();
                
        
                bool bCol = false;
                bCol = SDLCommonFunction::CheckCollision(rect_player, rect_monster);
                bool attack;
                attack = p_player.Attack();
					if (bCol)
					{
                        if(attack)
                        {
                            for(int i=0;i<8;i++)
                            {
                                int x_pos = rect_player.x + 100*0.5 ;
                                int y_pos = rect_player.y - 100*0.5 ;

                                p_explosion.set_frame(i);
                                p_explosion.SetRect(x_pos,y_pos);
                                SDL_GetTicks();
                                p_explosion.Show(g_screen);
                                SDL_RenderPresent(g_screen);
                            }

                            p_monster -> Free();
                            monster_list.erase(monster_list.begin() + i);
                            point+=10;
                            Mix_PlayChannel(-1, sound, 0);
                            
                        }
                        
                        if(attack == false)
                        {
                            p_monster -> Free();
                            monster_list.erase(monster_list.begin() + i);
                            hp_player --;
                            if(hp_player > 0)
                            {
                                p_player.SetRect(0,0);
                                p_player.set_return_time(30);
                                SDL_Delay(10);
                                health_player.DeCrease();
                                health_player.Render(g_screen);
                                continue;
                            }
                            else
                            {
						    if (MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
							  {  
                                p_monster ->Free();                         
								close();
								SDL_Quit();
								return 0;
							  }
                            }  
                        }    
					}
            }
        }
        for(int i=0; i < boss_list.size(); i++)
        {
            Boss*  bossObject = boss_list.at(i);
            if(bossObject != NULL)
            {
                bossObject-> SetMapXY(map_data.start_x_, map_data.start_y_);
                bossObject -> ImpMoveType(g_screen);
                bossObject -> DoPlayer(map_data);
                bossObject -> Show(g_screen);
            }    

        
        SDL_Rect rect_boss = bossObject->GetRectFRAME();
        bool bCol2 = false;
        bCol2 = SDLCommonFunction::CheckCollision(rect_player, rect_boss);
        if (bCol2)
        {
            hp_player++;
            health_player.InitCrease();
            health_player.Render(g_screen);
            bossObject->Free();  
            boss_list.erase(boss_list.begin() + i);
            
        }
        }




        //time
        string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks()/1000;
        Uint32 val_time = 300 - time_val;
        if(val_time == 0)
        {
            if (MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
			 {  
                is_quit = true;
                break;
			 }
        }
        else 
        {
                string str_val = to_string(val_time);
                str_time += str_val;

                time_game.SetText(str_time);
                time_game.LoadRenderText(font, g_screen);
                time_game.RenderText(g_screen, SCREEN_WIDTH - 200,15);
        
        }

//point
        string str_point = "Point: ";
        Uint32 point_val = point;
        string str_point_val = to_string(point_val);
        str_point += str_point_val;

        font_point.SetText(str_point);
        font_point.LoadRenderText(font, g_screen);
        font_point.RenderText(g_screen, SCREEN_WIDTH - 200, 50);        

        
        if(point == 200){
        if (MessageBoxW(NULL, L"YOU WIN", L"Info", MB_OK | MB_ICONSTOP) == IDOK)
		{                           
			close();
			SDL_Quit();
			return 0;
		}
        }
        

        SDL_RenderPresent(g_screen);
    
        int real_time = fps_time.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;

        if(real_time < time_one_frame )
        {
            int delay_time = time_one_frame - real_time;
            SDL_Delay(delay_time);
        }
    }
    close();
    
    return 0;
    
}


