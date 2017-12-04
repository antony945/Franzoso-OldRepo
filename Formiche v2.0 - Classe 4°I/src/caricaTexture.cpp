#include "../include/formica.h"

SDL_Texture* caricaTexture(Uint8 colore[], string path,SDL_Renderer* renderer){
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != NULL) { SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF)); }
    newTexture=SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_SetTextureColorMod(newTexture,colore[0],colore[1],colore[2]);
    return newTexture;
}
