#include "../header/Game.h"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "ERROR: FAILED SDL INIT: " << SDL_GetError() << std::endl;
    }
    SDL_CreateWindowAndRenderer(W_WIDTH, W_HEIGHT, 0, &this->window, &this->renderer);
    SDL_SetWindowTitle(this->window, "Mario");
    this->LoadMap("level/1.level");
    this->running = true;
    this->count = 0;
    this->mapX = 0;
    this->mapY = 0;
    this->speed = 4;
    
    
    this->player.SetDest(100, W_HEIGHT/2, P_SIZE, P_SIZE);
    
    this->player.SetImage("assets/mario.png", this->renderer);
    this->player.SetSrc(0, 0, 16, 16);
    this->run_r = this->player.CreateCycle(2, 16, 16, 4, 10);
    this->run_l = this->player.CreateCycle(3, 16, 16, 4, 10);
    this->idle_r = this->player.CreateCycle(1, 16, 16, 1, 0);

    this->player.SetCurrAnim(this->idle_r);
    
    
    this->GameLoop();
}

Game::~Game()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    IMG_Quit();
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
    this->Draw(this->player);

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
    static int lastTime = 0;
    while (running)
    {
        this->lastFrame = SDL_GetTicks();

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
            if (e.key.keysym.sym == SDLK_d)
            {
                //run right
                this->r = true;
                this->l = false;
                this->player.SetCurrAnim(run_r);
            }
            if (e.key.keysym.sym == SDLK_a)
            {
                //run left
                this->l = true;
                this->r = false;   
                this->player.SetCurrAnim(run_l);
            }
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                //jump
                this->jmp = 1;
            }
        }
        if(e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_d)
            {
                //run right
                this->r = false;
                this->player.SetCurrAnim(this->idle_r);
            }
            if (e.key.keysym.sym == SDLK_a)
            {
                //run left
                this->l = false;
                this->player.SetCurrAnim(this->idle_r);   
            }
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                //jump
                this->jmp = 0;
            }
        }
    }
    
}

void Game::Update()
{
    if(this->l)
    {
        if(this->player.GetCurrAnim() != this->run_l)
        {
            this->player.SetCurrAnim(this->run_l);   
        }
        this->player.SetDest(this->player.GetDX() - this->speed, this->player.GetDY());
    }
    if(this->r)
    {
        if(this->player.GetCurrAnim() != this->run_r)
        {
            this->player.SetCurrAnim(this->run_r);
        }
        this->player.SetDest(this->player.GetDX() + this->speed, this->player.GetDY());
    }
    this->player.UpdateAnim();
    this->fall = true;
    for (int i = 0; i < map.size(); i++)
    {
        if(this->Collison(this->player, map[i]))
        {
            if(map[i].GetSolid())
            {
                this->fall = false;
            }
            if(map[i].GetObjID() == 0)
            {
                this->player.SetDest(this->player.GetDX(), this->player.GetDY() - 10* TILE_SIZE);
            }
        }
    }

    if(this->fall == true)
    {
        this->player.SetDest(this->player.GetDX(), this->player.GetDY() + GRAVITY);
    }

    if(this->player.GetDX() < 300)
    {
        this->player.SetDest(300, this->player.GetDY());
        this->ScrollMap(this->speed, 0);
    }
    if(this->player.GetDX() > W_WIDTH - 300)
    {
        this->player.SetDest(W_WIDTH - 300, this->player.GetDY());
        this->ScrollMap(-this->speed, 0);
    }
    if(this->player.GetDY() < 100)
    {
        this->player.SetDest(this->player.GetDX(), 100);
        this->ScrollMap(0, this->speed);
    }
    if(this->player.GetDY() > W_HEIGHT - 100)
    {
        this->player.SetDest(this->player.GetDX(), W_HEIGHT - 100);
        this->ScrollMap(0, -this->speed);
    }
    //this->ScrollMap();
}

void Game::LoadMap(const char* filename)
{
    Object tmp;
    tmp.SetImage("assets/Tile.png", this->renderer);
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
                tmp.SetSrc((curr-1)* TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
                tmp.SetDest((j*TILE_SIZE*4)+mx, (i*TILE_SIZE*4)+my, TILE_SIZE * 4, TILE_SIZE * 4);
                tmp.SetObjID(curr);
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
        if(map[i].GetDX() >= this->mapX - TILE_SIZE 
        & map[i].GetDY() >= this->mapY - TILE_SIZE
        & map[i].GetDX() <= this->mapX + W_WIDTH + TILE_SIZE
        & map[i].GetDY() <= this->mapY + W_HEIGHT + TILE_SIZE)
        {
            this->Draw(map[i]);
        }
        
    }
}

void Game::ScrollMap(int x, int y)
{
    for (int i = 0; i < map.size(); i++)
    {
        map[i].SetDest(map[i].GetDX() + x, map[i].GetDY() + y);
    }
}

bool Game::Collison(Object a, Object b)
{
    if((a.GetDX() < b.GetDX() + b.GetDW())
    && (a.GetDX() + a.GetDW() > b.GetDX())
    && (a.GetDY() < b.GetDY() + b.GetDH())
    && (a.GetDY() + a.GetDH() > b.GetDY()))
    {
        return true;
    }
    else
    {
        return false;
    }
}