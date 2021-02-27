#include "../header/Entity.h"

Entity::Entity(/* args */)
{
    this->rev = false;
}

Entity::~Entity()
{
}

int Entity::CreateCycle(int row, int width, int height, int amount, int speed)
{
    cycle tmp;
    tmp.row = row - 1;
    tmp.width = width;
    tmp.height = height;
    tmp.amount = amount;
    tmp.speed = speed;
    tmp.tick = 0;
    this->animation.push_back(tmp);
    return this->animation.size() - 1;
}

void Entity::UpdateAnim()
{
    this->SetSrc(
        animation[this->currAnim].width * animation[this->currAnim].tick, 
        animation[this->currAnim].row * animation[this->currAnim].height,
        animation[this->currAnim].width,
        animation[this->currAnim].height);

    if(this->begin > animation[this->currAnim].speed)
    {
        if(!this->rev)
        {
            animation[this->currAnim].tick++;
        }
        if(this->rev)
        {
            animation[this->currAnim].tick--;
        }
    
        this->begin = 0;
    
    }
    this->begin++;
    
    if(animation[this->currAnim].tick >= animation[this->currAnim].amount)
    {
        animation[this->currAnim].tick = 0;
    }
    if(animation[this->currAnim].tick <= 0)
    {
        if(this->nAb)
        {
            this->currAnim = this->newAnim;
            this->nAb = 0;
            this->rev = 0;
        }
        else
        {
            animation[this->currAnim].tick = 0;
        }
    }
}