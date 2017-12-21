#ifndef SDL_UTILITIES
#define SDL_UTILITIES

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture * loadTexture(const std::string &file, SDL_Renderer * ren){

	SDL_Texture * texture = IMG_LoadTexture(ren, file.c_str());

	if(texture == nullptr){
		logSDLError(std::cout, "CreateTextureFromSurface");
	}

	return texture;
}

void renderTexture(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, int w, int h){
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderTexture(SDL_Texture * tex, SDL_Renderer * ren, int x, int y){
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(tex, ren, x, y, w, h);
}

#endif
