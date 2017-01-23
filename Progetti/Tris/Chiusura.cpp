
#include "function.h"
#include "Variables.h"

void Chiusura(SDL_Renderer& renderer, SDL_Window& window){
    //Distrugge renderer e finestra
    SDL_DestroyRenderer(renderer)
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;

    //Chiude SDL e SDL_image
    SDL_Quit();
    IMG_Quit();
}
