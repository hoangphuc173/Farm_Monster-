#include "hp.h"

using namespace std;

hp::hp()
{
    number_ = 0;
}

hp::~hp()
{
    
}

void hp::AddPos(const int& xp)
{
    pos_list_.push_back(xp);
}

void hp::Init(SDL_Renderer* screen)
{
    if (!LoadImg("C:/recover/SDL2/project/data/images/health.png", screen))
    {
        // Xử lý lỗi khi không thể load ảnh
        cerr << "Error loading image" << endl;
        return;
    }
    number_ = 3;
    pos_list_.clear(); // Xóa danh sách vị trí trước khi thêm các vị trí mới
    AddPos(30);
    AddPos(60);
    AddPos(90);
}

void hp::Show(SDL_Renderer* screen)
{
    for (int i = 0; i < pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 0;
        Render(screen);
    }
}

void hp::DeCrease()
{
    if (number_ > 0)
    {
        number_--;
        if (!pos_list_.empty())
        {
            pos_list_.pop_back();
        }
    }
}

void hp::InitCrease()
{
    number_++;
    if (!pos_list_.empty())
    {
        int last_pos = pos_list_.back();
        last_pos += 40;
        pos_list_.push_back(last_pos);
    }
    else
    {
        AddPos(30); // Nếu danh sách rỗng, thêm vị trí đầu tiên
    }
}
