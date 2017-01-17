// Franzoso_Starter.cpp, Antonio Franzoso, 3C

#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#define width 750
#define height 232

/* PROTOTIPI FUNZIONI */
void TestoEsercizio(void);
bool Inizializzazione();
bool CaricaImmagine();
void Close(void);

/* VARIABILI GLOBALI */
SDL_Window* window = NULL;
SDL_Surface* ScreenSurface = NULL;
SDL_Surface* BackSurface = NULL;

int main(int argc, char* args[]){
    TestoEsercizio();

    if(Inizializzazione() && CaricaImmagine()){
        SDL_BlitSurface(BackSurface, NULL, ScreenSurface, NULL);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(3000);
    }else
        std::cout << std::endl << "The image couldn't load correctly! \n";

    Close();

    return 0;
}

void TestoEsercizio(){
    std::cout << "#Starter \n\nE' richiesto il file sorgente (.cpp) che faccia il display in finestra dell'immagine caricata.\n";
    std::cout << "Caratteristiche immagine: Altezza = 232 pixel, larghezza = 750 pixel. \n";
    std::cout << "Utilizzare i files all'interno della cartella per sviluppare il progetto.\n\n";
    system("PAUSE");
}

bool Inizializzazione(){
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL Error: " << SDL_GetError();
        success = false;
    }else{
        window = SDL_CreateWindow("Esercizio Starter SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

        if(window == NULL){
            std::cout << "This element couldn't create! \n";
            std::cout << "Error: " << SDL_GetError();
            success = false;
        }else{
            ScreenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

bool CaricaImmagine(){
    bool success = true;

    BackSurface = SDL_LoadBMP("Starter/Starter.bmp");

    if(BackSurface == NULL){
        std::cout << "This element couldn't create! \n";
        std::cout << "Error: " << SDL_GetError();
        success = false;
    }

    return success;
}

void Close(){
    SDL_FreeSurface(BackSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
