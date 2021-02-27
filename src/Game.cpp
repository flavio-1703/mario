#include "../header/Game.h"

Game::Game()
{
    SDL_Init(0);
    SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &this->window, &this->renderer);
    SDL_SetWindowTitle(this->window, "Mario");
    this->running = true;
    this->count = 0;

    this->LoadMap("level/1.level");
    this->GameLoop();
}

Game::~Game()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Game::Render()
{
    SDL_SetRenderDrawColor(this->renderer, 126, 192, 238, 0.2);
    SDL_Rect rect;
    rect.x = rect.y = 0;
    rect.w = W_WIDTH;
    rect.h = W_HEIGHT;
    SDL_RenderFillRect(this->renderer, &rect);

    this->DrawMap();

    this->frameCount++;
    int timerFps = SDL_GetTicks() - this->lastFrame;

    if(timerFps < 1000/60)
    {
        SDL_Delay((1000/60) - timerFps);
    }

    SDL_RenderPresent(this->renderer);
}

void Game::GameLoop()
{
    while (running)
    {
        this->lastFrame = SDL_GetTicks();
        static int lastTime;

        if (this->lastFrame >= (lastTime + 1000))
        {
            lastTime = this->lastFrame;
            frameCount = 0;
        }
        

        this->Render();
        this->Input();
        this->Update();
    }
}

void Game::Draw(Object obj)
{
    SDL_Rect dst = obj.GetDest();
    SDL_Rect src = obj.GetSrc();

    SDL_RenderCopyEx(this->renderer, obj.GetTex(), &src, &dst, 0, NULL, SDL_FLIP_NONE );
}

void Game::Input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            this->running = false;
        }
        if(e.type == SDL_KEYDOWN)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE)
            {
                this->running = false;
            }
        }
    }
    
}

void Game::Update()
{
    //this->player.UpdateAnim();
}

void Game::LoadMap(const char* filename)
{
    int curr, mx, my, mw, mh;
    std::ifstream in(filename);

    if(!in.is_open())
    {
        std::cout << "ERROR: LOADMAP: COULD NOT OPEN FILE: " << filename << std::endl;
        return;
    }
    in >> mw;
    in >> mh;
    in >> mx;
    in >> my;
    for (int i = 0; i < mh; i++)
    {
        for (int j = 0; j < mw; j++)
        {
            if (in.eof())
            {
                std::cout << "REACHED END OF FILE" << std::endl;
                return;
            }
            in >> curr;

            if(curr != 0)
            {
                Object tmp;
                tmp.SetImage("assets/Tile.png", this->renderer);
                tmp.SetSrc((curr-1)* TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
                tmp.SetDest((j*TILE_SIZE)*mx, (i*TILE_SIZE)*my, TILE_SIZE * 4, TILE_SIZE * 4);
               
                // if(curr == 2 || curr == 4)
                // {
                //     tmp.SetSolid(false);
                // }
                map.push_back(tmp);
            }
            
        }
        
    }
    in.close();
}

void Game::DrawMap()
{
    for (int i = 0; i < map.size(); i++)
    {
        this->Draw(map[i]);
    }
    
}