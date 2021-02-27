#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Object
{
private:
    SDL_Rect dest;
    SDL_Rect src;
    SDL_Texture* tex;
    bool solid;
    int obj_id;

public:
    Object();
    ~Object();
public:
    inline SDL_Rect GetDest() const { return this->dest; }
    inline SDL_Rect GetSrc() const { return this->src; }
    inline SDL_Texture* GetTex() const { return this->tex; }
    inline bool GetSolid() const  {return this->solid; }
    int GetDX();
    int GetDY();
    int GetDW();
    int GetDH();
    int GetObjID();
public:
    void SetDest(int x, int y, int w, int h);
    void SetDest(int x, int y);
    void SetSrc(int x, int y, int w, int h);
    void SetImage(const char*, SDL_Renderer* ren);
    inline void SetSolid(bool solid) { this->solid = solid; }
    inline void SetObjID(int obj_id) { this->obj_id = obj_id; }
};

