#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include <utilities.h>
#include <res_path.h>
#include <cleanup.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int  argc, char ** argsv){

	if((SDL_Init(SDL_INIT_EVERYTHING) != 0)){
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}
	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError(std::cout, "IMG_Init");
		SDL_Quit();
		return 1;
	}
    if(TTF_Init() != 0){
        logSDLError(std::cout, "TTF_Init");
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

	SDL_Window * window = SDL_CreateWindow("Lesson 3", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr){
		logSDLError(std::cout, "SDL_CreateWindow()");
		IMG_Quit();
        TTF_Quit();
		SDL_Quit();
		return 1;
	}
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr){
		logSDLError(std::cout, "SDL_CreateRenderer()");
		cleanup(window);
		IMG_Quit();
        TTF_Quit();
		SDL_Quit();
		return 1;
	}
	const std::string resPath = getResourcePath();

    SDL_Color color = {255, 255, 255, 255};
    SDL_Texture * image = renderText("TTF fonts are cool!", resPath + "sample.ttf", color, 64, renderer);

    if(image == nullptr){
        cleanup(renderer, window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    int iW, iH;
    SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;


	bool quit = false;
	SDL_Event e;
	while(!quit){
		while (SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT){
				quit = true;
			}
		}
		SDL_RenderClear(renderer);
		renderTexture(image, renderer, x, y);
		SDL_RenderPresent(renderer);
	}
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	return 0;
}
