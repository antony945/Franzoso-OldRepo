

#include "function.h"
#include "Variables.h"
SDL_Texture* CaricaTexture(std::string path){
SDL_Texture* newTexture = NULL;
SDL_Surface* newSurface = IMG_Load(path.c_str());
newTexture = SDL_CreateTextureFromSurface(Renderer, newSurface);
SDL_FreeSurface(newSurface);
return newTexture;
}