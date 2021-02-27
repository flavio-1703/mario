#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Object
{
private:
    SDL_Rect dest;
    SDL_Rect src;
    SDL_Texture* tex;
    bool solid;

public:
    Object();
    ~Object();
public:
    inline SDL_Rect GetDest() const { return this->dest; }
    inline SDL_Rect GetSrc() const { return this->src; }
    inline SDL_Texture* GetTex() const { return this->tex; }
    inline bool GetSolid() const  {return this->solid; }
public:
    void SetDest(int x, int y, int w, int h);
    void SetSrc(int x, int y, int w, int h);
    void SetImage(const char*, SDL_Renderer* ren);
    inline void SetSolid(bool solid) { this->solid = solid; }
};

