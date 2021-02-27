#include "../header/Object.h"

Object::Object()
{
    this->solid = true;
}

Object::~Object()
{
}

void Object::SetDest(int x, int y, int w, int h)
{
    this->dest.x = x;
    this->dest.y = y;
    this->dest.w = w;
    this->dest.h = h;
}

void Object::SetSrc(int x, int y, int w, int h)
{
    this->src.x = x;
    this->src.y = y;
    this->src.w = w;
    this->src.h = h;
}

void Object::SetImage(const char* filename, SDL_Renderer* ren)
{
    SDL_Surface* surface;

    if(IMG_Load(filename) < 0)
    {
        std::cout << "ERROR: IMG_Load() COULD NOT LOAD IMAGE " << filename << std::endl;
    }
    else
    {
        surface = IMG_Load(filename);
    }
    
    //this->tex = SDL_CreateTextureFromSurface(ren, surface);

    this->tex = IMG_LoadTexture(ren, filename);
}

int Object::GetDX()
{
    return this->dest.x;
}


int Object::GetDY()
{
    return this->dest.y;
}

void Object::SetDest(int x, int y)
{
    this->dest.x = x;
    this->dest.y = y;
}

int Object::GetDW()
{
    return this->dest.w;
}

int Object::GetDH()
{
    return this->dest.h;
}

int Object:: GetObjID()
{
    return this->obj_id;
}