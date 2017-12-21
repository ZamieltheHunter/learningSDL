#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <utilities.h>
#include <res_path.h>
#include <cleanup.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 40;


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
	SDL_Texture * background = loadTexture(resPath + "background.png", renderer);
	SDL_Texture * image = loadTexture(resPath + "image.png", renderer);

	if(background == nullptr || image == nullptr){
		cleanup(background, image, window, renderer);
		IMG_Quit();
		SDL_Quit();
		return 1;
	}

	for( int i = 0; i < 5; i++){
		for(float j = 0; j < SCREEN_WIDTH / TILE_SIZE; j++){
			for(float k = 0; k < SCREEN_HEIGHT / TILE_SIZE; k++){
				renderTexture(background, renderer, SCREEN_WIDTH * (j/(SCREEN_WIDTH/TILE_SIZE)), SCREEN_HEIGHT * (k / (SCREEN_HEIGHT/TILE_SIZE)),TILE_SIZE, TILE_SIZE);
			}
		}
		int iW, iH;
		SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
		renderTexture(image, renderer, SCREEN_WIDTH / 2 - iW / 2, SCREEN_HEIGHT / 2 - iH / 2);
		
		SDL_RenderPresent(renderer);
		SDL_Delay(1000);
	}
	
	cleanup(background, image, renderer, window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
