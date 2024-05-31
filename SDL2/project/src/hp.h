#ifndef HP_H_
#define HP_H_

#include "CommonFunction.h"
#include "BaseObject.h"


using namespace std;

class hp : public BaseObject
{
public: 
     hp();
     ~hp();

    void SetNum(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen); 

    void InitCrease();
    void DeCrease();

private:
    int number_;
    vector<int> pos_list_;     
       
};

#endif
