#include "../include/formica.h"

void Formica::render(SDL_Renderer* renderer){
    SDL_Rect dstrect = {pos_x, pos_y, lunghezza, altezza}; //tutte le variabili sono usate come dichiarate in formica.h
    SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, angolo_vel, NULL, NULL);
}
