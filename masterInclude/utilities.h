#ifndef SDL_UTILITIES
#define SDL_UTILITIES

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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

void renderTexture(SDL_Texture * tex, SDL_Renderer * ren, SDL_Rect dst, SDL_Rect * clip = nullptr){
	SDL_RenderCopy(ren, tex, clip, &dst);
}

void renderTexture(SDL_Texture * tex, SDL_Renderer * ren, int x, int y, SDL_Rect * clip = nullptr){
	SDL_Rect dst;
	dst.x = x;
    dst.y = y;
    if (clip != nullptr){
        dst.w = clip->w;
        dst.h = clip->h;
    } else {
	    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    }
	renderTexture(tex, ren, dst, clip);
}

SDL_Texture * renderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize, SDL_Renderer * renderer){
    TTF_Font * font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if(font == nullptr){
        logSDLError(std::cout, "TTF_OpenFont");
        return nullptr;
    }

    SDL_Surface * surf = TTF_RenderText_Blended(font, message.c_str(), color);
    if(surf == nullptr){
        TTF_CloseFont(font);
        logSDLError(std::cout, "TTF_RenderTextBlended");
        return nullptr;
    }

    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
    if(texture == nullptr){
        logSDLError(std::cout, "CreateTexture");
    }
    
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

#endif
