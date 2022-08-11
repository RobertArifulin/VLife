/*
#include <SDL.h>
#include <SDL_Image.h>
#include <cstdio>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Texture* flower = NULL;


bool init() {
    bool ok = 1;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "can't init: " << SDL_GetError() << '\n';
        ok = false;
    }

    win = SDL_CreateWindow("Texture", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        ok = 0;
        std::cout << "can't create window " << SDL_GetError() << '\n';
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        std::cout << "can't create render " << SDL_GetError() << '\n';
        ok = 0;
    }

    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);

    int flags = IMG_INIT_PNG;
    if (!(IMG_Init(flags) & flags)) {
        std::cout << "can't init IMG " << SDL_GetError() << '\n';
        ok = 0;
    }

    return ok;
}


bool load() {
    bool ok = 1;
    SDL_Surface* temp_surf = NULL;
    temp_surf = IMG_Load("images/flower.png");
    if (temp_surf == NULL) {
        std::cout << "Can't load FLOWER IMG : " << IMG_GetError() << std::endl;
        ok = 0;
    }


    flower = SDL_CreateTextureFromSurface(ren, temp_surf);
    if (flower == NULL) {
        std::cout << "Can't create texture : " << SDL_GetError() << std::endl;
        ok = 0;
    }

    return ok;
}


int quit() {
    SDL_DestroyWindow(win);
    win = NULL;

    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_DestroyTexture(flower);
    flower = NULL;

    SDL_Quit();
    IMG_Quit();

    return 0;
}

int main(int argc, char** args) {

    if (!init()) {
        quit();
        return 1;
    }

    if (!load()) {
        quit();
        return 1;
    }

    bool run = 1;
    SDL_Event e;

    SDL_Rect Tr;
    SDL_Rect TCord;

    Tr.w = 50;
    Tr.h = 50;
    Tr.x = 0;
    Tr.y = 0;
    TCord.w = 50;
    TCord.h = 50;

    SDL_RenderClear(ren);
    while (run) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                run = 0;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                std::cout << "MSB D \n" << Tr.x << " " << Tr.y << '\n';
                Uint32 buttons = SDL_GetMouseState(&Tr.x, &Tr.y);
                Tr.x -= 25;
                Tr.y -= 25;
            }
        }

        SDL_RenderCopy(ren, flower, NULL, &Tr);
        SDL_RenderPresent(ren);
    }

    quit();

    return 0;
}; */