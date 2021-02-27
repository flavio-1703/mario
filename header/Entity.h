#pragma once
#include "Object.h"
#include <vector>

class Entity : public Object
{
private:
    
    int currAnim;
    int begin;

    struct cycle
    {
        int row;
        int width;
        int height;
        int amount;
        int tick;
        int speed;
    };

    std::vector<cycle> animation;
public:
    Entity();
    ~Entity();
public:
    int CreateCycle(int row, int width, int height, int amount, int speed);
    void UpdateAnim();
public:
    inline void SetCurrAnim(int currAnim) { this->begin =0, this->currAnim = currAnim; }
};
