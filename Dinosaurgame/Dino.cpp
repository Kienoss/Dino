 #include <iostream>
    #include <string>
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_ttf.h>
    #include <SDL_mixer.h>
    #include <stdio.h>
    #define WIDTH 800
    #define HEIGHT 300
    using namespace std;
    //--------------------------------------------------------
    bool running;
    SDL_Renderer* ren;
    SDL_Window* win;
    SDL_Event event;
    bool isBottom = true;
    bool isJumping = false;
    bool isFalling;
    int timer;
    int timer2;
    int timer3;
    int score=0;
    SDL_Surface* surf;
    SDL_Texture* tex=nullptr;
    bool isHighest;
    bool collide;
    bool pause= true;
    Mix_Chunk *jumpsound = nullptr;
    //--------------------------------------------------------

    //--------------------------------------------------------
    struct ground{
    int x;
    int y;
    void render(SDL_Renderer* ren){
    //SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    surf = IMG_Load("data/ground.png");
    tex = SDL_CreateTextureFromSurface (ren,surf);
    SDL_Rect rect;
    rect.x=1;
    rect.y=138;
    rect.w=WIDTH;
    rect.h=30;
    SDL_RenderCopy(ren, tex, nullptr, &rect);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
    //SDL_RenderFillRect(ren, &rect);
    }

    };
    ground ground;
    //--------------------------------------------------------
    struct dino{
        float x=20;
        float y=95;
        float w=35;
        float h=45;
        void render(SDL_Renderer* ren){
            surf = IMG_Load("data/dino0000.png");
            tex = SDL_CreateTextureFromSurface(ren, surf);
            SDL_Rect rect;

            rect.x = x;
            rect.y = y;
            rect.w=w;
            rect.h=h;
            SDL_RenderCopy(ren, tex, nullptr, &rect);
            SDL_DestroyTexture(tex);
            SDL_FreeSurface(surf);
        }
        void dinojump(SDL_Renderer* ren){
            surf = IMG_Load("data/dinoJump0000.png");
            tex = SDL_CreateTextureFromSurface(ren, surf);
            SDL_Rect rect;

            rect.x = x;
            rect.y = y;
            rect.w=w;
            rect.h=h;
            SDL_RenderCopy(ren, tex, nullptr, &rect);
            SDL_DestroyTexture(tex);
            SDL_FreeSurface(surf);
        }
    };
    dino dino;
    //--------------------------------------------------------
    struct cactus{
    float x=WIDTH;
    float y=105;
    float w=15;
    float h=35;
    void render(SDL_Renderer* ren){
    surf = IMG_Load("data/cactusBig0000.png");
    tex = SDL_CreateTextureFromSurface(ren,surf);
    //SDL_SetRenderDrawColor(ren, 0, 255, 127, 0);
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;
    rect.w=w;
    rect.h=h;
    SDL_RenderCopy(ren,tex,nullptr,&rect);
    //SDL_RenderFillRect(ren, &rect);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
    }
    };
    cactus cactus;
    //--------------------------------------------------------
    struct cactus_number_2{
    float x=WIDTH;
    float y=105;
    float w=15;
    float h=35;
    void render(SDL_Renderer* ren){
    surf = IMG_Load("data/cactusBig0000.png");
    tex = SDL_CreateTextureFromSurface(ren,surf);
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;
    rect.w=w;
    rect.h=h;
    SDL_RenderCopy(ren,tex,nullptr,&rect);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);

    }
    };
    cactus_number_2 cactus2;
    //--------------------------------------------------------
    void printScore(){              //make window not responding for some reason
    TTF_Font *font = TTF_OpenFont("data/sans.ttf", 24);
    SDL_Color color;
    color.r=0;
    color.g=0;
    color.b=0;
    color.a=255;
    SDL_Rect rect;
    surf = TTF_RenderText_Solid(font, "testing", color);
    tex = SDL_CreateTextureFromSurface(ren, surf);
    rect.x=200;
    rect.y=140;
    rect.w=100;
    rect.h=100;
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(tex);

    }
    //--------------------------------------------------------
        void sound_jump(){
            jumpsound = Mix_LoadWAV("data/dino.mp3");
            Mix_PlayChannel (-1,jumpsound, 0);
            Mix_FreeChunk (jumpsound);
            jumpsound = nullptr;
            Mix_CloseAudio();
        }
    //--------------------------------------------------------
    void drawbackground(){
         //render back ground white
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_Rect rect;
        rect.x=rect.y=0;
        rect.w=WIDTH;
        rect.h=HEIGHT;
        SDL_RenderFillRect(ren, &rect);
    }
    //----------------------------------------------------------
    void draw(){
        drawbackground();
        //pause screen until press S
        if(pause == true){
            drawbackground();
            dino.render(ren);
            ground.render(ren);
            //cactus.render(ren);
            SDL_RenderPresent(ren);
        }
        //draw dino-------------------------------------------------------------
    if (pause == false){
        if(isJumping== false && isFalling==false && isBottom == true){
        dino.render(ren);
        }

        if   (isJumping && timer2 >= 0 && collide == false){
            dino.y -= 0.35;
            dino.dinojump(ren);
            if(dino.y <= 95-70){
                isJumping = false;
                isFalling = true;
                isHighest = true;
                timer = 0;
            }
        }
        else
        {

            timer2++;
        }
        if(isHighest==true){
                dino.dinojump(ren);
        }

        if (isFalling && timer >= 270 && collide == false){
            dino.y += 0.45;
            dino.dinojump(ren);
            if(dino.y >= 95){
                isFalling = false;
                isBottom = true;
                isHighest = false;
                timer2 = 0;
            }
        }
        else
            {
                timer++;
            }

        //draw cactus-------------------------------------------------------------
        cactus.render(ren);
        if(running==true){
            cactus.x -= 0.28 ;
            if(cactus.x <= -30){
                cactus.x = WIDTH-15;
                score++;
            }
            timer3++;
        }
        if(running==true){
                if(timer3 >= 1100){
                cactus2.x -=0.28;
                cactus2.render(ren);
                    if(cactus2.x <= -30){
                        cactus2.x = WIDTH-15;
                        score++;
                    }
                }
        }




        //draw Ground------------------------------------------------------------
        ground.render(ren);
        //draw Sky---------------------------------------------------------------

        SDL_RenderPresent(ren);
    }

    }
    //--------------------------------------------------------
    void input(){
        while(SDL_PollEvent(&event)){
            if( event.type == SDL_QUIT ) running = false;
            if( event.type == SDL_KEYDOWN ) {
                if( event.key.keysym.sym == SDLK_ESCAPE ) running = false;
                 if( event.key.keysym.sym == SDLK_SPACE ) pause = false;
                if( event.key.keysym.sym == SDLK_SPACE ) {
                        sound_jump();
                    if(isBottom && !isJumping){
                    isJumping = true;
                    isBottom = false;
                    }
                }
            }
        }

    }
    //--------------------------------------------------------
    void update(){
         if((dino.x+dino.w<cactus.x +10 || dino.y+dino.h<cactus.y)&&(dino.x+dino.w<cactus2.x +10 || dino.y+dino.h<cactus2.y)){
            collide = false;
        }
        else{collide = true;}
        if(collide == true){

                //dino.dino_dead(ren);
                //SDL_RenderPresent(ren);

                cout<<"YOUR TOTAL SCORE IS "<<score<<endl<<endl<<endl;

                SDL_Delay(2000);
                running = false;
        }
    }
    //--------------------------------------------------------

    int main(int argc, char* argv[]){
        SDL_Init ( SDL_INIT_EVERYTHING );
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        //Mix_Init(MIX_INIT_MP3);
        Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
        SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0,&win,&ren);
        SDL_SetWindowTitle(win, "Dinosaur Game");
        running =true;
        pause = true;

        while (running){
            input();
            update();
            draw();

        }
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        TTF_Quit();
        IMG_Quit();
        //Mix_Quit();
        SDL_Quit();

    }
