#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#define WIDTH 640
#define HEIGHT 480

using namespace std;

bool inizializza(SDL_Window*& window, SDL_Renderer*& renderer){
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        success = false;
    }else{
        // setta texture lineare
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            cout << "Texture non lineare.";
        }

        // crea finestrra
        window = SDL_CreateWindow("Test 01", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            success = false;
        }else{
            // crea renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == NULL){
                success = false;
            }else{
                // inizializza colore renderer
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                // inizializza altre librerie
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags)){
                    success = false;
                }
            }
        }
    }

    return success;
}
