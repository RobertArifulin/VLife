#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "../nuklear_cross/nuklear_cross.h"


using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* ren = NULL;
SDL_Texture* flower = NULL;


int init() {
	struct nk_context* ctx;
	struct nk_colorf bg;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "can't init video: " << SDL_GetError() << '\n';
		return 1;
	}
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {
		cout << "can't init IMG: " << IMG_GetError() << '\n';
		return 1;
	}


	window = SDL_CreateWindow("ViewPoint", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "can't create window: " << SDL_GetError() << '\n';
		return 1;
	}

	ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		cout << "can't create renderer: " << SDL_GetError() << '\n';
		return 1;
	}

	return 0;
}

int load() {
	SDL_Surface* tmp_surf = NULL;
	tmp_surf = IMG_Load("images/flower.png");
	if (tmp_surf == NULL) {
		cout << " can't load image: " << IMG_GetError() << '\n';
		return 1;
	}
	
	flower = SDL_CreateTextureFromSurface(ren, tmp_surf);
	if (flower == NULL) {
		cout << "Can't create texture from surface: " << SDL_GetError() << endl;
		SDL_FreeSurface(tmp_surf);
		tmp_surf = NULL;
		return 1;
	}
	SDL_FreeSurface(tmp_surf);
	tmp_surf = NULL;
	return 0;
}


void quit() {
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(ren);
	ren = NULL;

	SDL_DestroyTexture(flower);
	flower = NULL;
	
	SDL_Quit();
	IMG_Quit();
}

int main(int arhc, char** argv) {
	
	if (init()) {
		quit();
		system("pause");
		return 1;
	}

	if (load()) {
		quit();
		system("pause");
		return 1;
	}

	SDL_Rect top_vp = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	SDL_Rect bottom_vp = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
	
	SDL_RenderSetViewport(ren, &top_vp);
	SDL_RenderCopy(ren, flower, NULL, NULL);

	SDL_RenderSetViewport(ren, &bottom_vp);
	SDL_RenderCopy(ren, flower, NULL, NULL);

	SDL_RenderPresent(ren);

	SDL_Delay(10000);

	quit();
	

	return 0;
}


