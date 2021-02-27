#pragma once
#include "Object.h"
#include <vector>

class Entity : public Object
{
private:
    
    int currAnim;
    int begin;
    bool rev, nAb;
    int newAnim;

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
public:
    inline int GetCurrAnim() const {return this->currAnim; }
    inline void Reverse(bool r) {this->rev = r; }
    inline void Reverse(bool r, int nA) { this->rev; this->nAb = true; nA = this->newAnim; }
};
