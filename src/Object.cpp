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
    SDL_Surface* surface = IMG_Load(filename);
    this->tex = SDL_CreateTextureFromSurface(ren, surface);
}
