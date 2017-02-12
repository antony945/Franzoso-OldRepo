#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "texture.h"
#define WIDTH 640
#define HEIGHT 480

using namespace std;

/* PROTOTIPI FUNZIONI */
bool inizializza();
bool loadMedia();
void close();

Texture Boy_Texture;
Texture Screen_Texture;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* args[]){
    if(!inizializza()){
        cout << endl;
        cout << "Impossibile inizializzare il programma! \n";
    }else{
        if(!loadMedia()){
            cout << endl;
            cout << "Impossibile caricare la/e immagine/i! \n";
        }else{
            bool quit = false;
            SDL_Event e;

            while(!quit){
                while(!SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT)
                        quit = true;
                }

                SDL_RenderClear(renderer);

                Screen_Texture.render(0, 0);
                Boy_Texture.render(240, 190);

                SDL_RenderPresent(renderer);
            }
        }
    }

    close();

    return 0;
}

bool inizializza(){
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError();
        success = false;
    }else{
        // setta texture lineare
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
            cout << "Texture non lineare.";
        }

        // crea finestrra
        window = SDL_CreateWindow("Test 01", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            cout << "Window could not be created! SDL Error: " << SDL_GetError();
            success = false;
        }else{
            // crea renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(renderer == NULL){
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError();
                success = false;
            }else{
                // inizializza colore renderer
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                // inizializza altre librerie
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags)){
                    cout << "SDL_image could not initialize! SDL Error: " << SDL_GetError();
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(){
    bool success = true;

    if(!Boy_Texture.loadFromFile("foo.png")){
        cout << "Failed to load Foo' texture image!\n";
        success = false;
    }

    if(!Screen_Texture.loadFromFile("background.png")){
        cout << "Failed to load background texture image!\n";
        success = false;
    }

    return success;
}

void close(){
    Boy_Texture.free();
    Screen_Texture.free();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
}
