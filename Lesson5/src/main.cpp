#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
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

	SDL_Window * window = SDL_CreateWindow("Lesson 3", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr){
		logSDLError(std::cout, "SDL_CreateWindow()");
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr){
		logSDLError(std::cout, "SDL_CreateRenderer()");
		cleanup(window);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}
	const std::string resPath = getResourcePath();
	SDL_Texture * image = loadTexture(resPath + "image.png", renderer);
	if(image == nullptr){
		cleanup(image, window, renderer);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

    int iW = 100, iH = 100;
    int x = SCREEN_WIDTH / 2 - iW / 2;
    int y = SCREEN_HEIGHT / 2 - iH / 2;


    SDL_Rect clips[4];
    for( int i = 0; i < 4; ++i){
        clips[i].x = i / 2 * iW;
        clips[i].y = i % 2 * iH;
        clips[i].w = iW;
        clips[i].h = iH;
    }

    int useClip = 0;

	bool quit = false;
	SDL_Event e;
	while(!quit){
		while (SDL_PollEvent(&e)){
			if(e.type == SDL_QUIT){
				quit = true;
			}
			if(e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym) { 
                    case SDLK_1:
                        useClip = 0;
                        break;
                    case SDLK_2:
                        useClip = 1;
                        break;
                    case SDLK_3:
                        useClip = 2;
                        break;
                    case SDLK_4:
                        useClip = 3;
                        break;
                    default:
                        break;
                }
			}
		}
		SDL_RenderClear(renderer);
		renderTexture(image, renderer, x, y, &clips[useClip]);
		SDL_RenderPresent(renderer);
	}
	IMG_Quit();
	SDL_Quit();
	return 0;
}
