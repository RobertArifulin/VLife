#include "SDL.h"
#include <cstdio>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* win = NULL;
SDL_Surface* scr = NULL;
SDL_Surface* smile = NULL;


int init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Can't init: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    win = SDL_CreateWindow("События", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    scr = SDL_GetWindowSurface(win);

    return 0;
}


int load() {
    smile = SDL_LoadBMP("smile.bmp");

    if (smile == NULL) {
        std::cout << "Can't load image: " << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    return 0;
}

int quit() {
    SDL_FreeSurface(smile);

    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}


int main(int argc, char** args) {
    if (init() == 1) {
        return 1;

    }

    if (load() == 1) {
        return 1;
    }

    bool run = true;
    SDL_Event e;
    SDL_Rect r;

    int x = 300;
    int y = 300;

    r.x = x;
    r.y = y;

    while (run) {
        while (SDL_PollEvent(&e) != NULL) {
            if (e.type == SDL_QUIT) {
                run = false;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {

                case SDLK_UP:
                    y -= 40;
                    break;
                case SDLK_DOWN:
                    y += 40;
                    break;
                case SDLK_RIGHT:
                    x += 40;
                    break;
                case SDLK_LEFT:
                    x -= 40;
                    break;
                }
            }
        }

        r.x = x;
        r.y = y;

        SDL_FillRect(scr, NULL, SDL_MapRGB(scr->format, 255, 255, 255));

        SDL_BlitSurface(smile, NULL, scr, &r);

        SDL_UpdateWindowSurface(win);
    }

    return quit();
}