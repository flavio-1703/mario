#pragma once
#include <SDL2/SDL.h>
#include "Object.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include <vector>

#define W_WIDTH 1280
#define W_HEIGHT 720
#define TILE_SIZE 16
#define P_SIZE 64
#define GRAVITY 10

class Game
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
private:
    bool running;
    int count;
    //FPS
    int frameCount, timerFPS, lastFrame;
    Entity player;
    int mapX;
    int mapY;
    int speed;
    bool l, r, u, d, fall;
    int idle_l, idle_r, run_l, run_r, jmp;
    std::vector<Object> map;
public:
    Game();
    ~Game();
public:
    void GameLoop();
    void Update();
    void Render();
    void Input();
    void Draw(Object obj);
    void LoadMap(const char* filename);
    void DrawMap();
    void ScrollMap(int x, int y);
    bool Collison(Object a, Object b);
};
