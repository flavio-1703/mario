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

};
