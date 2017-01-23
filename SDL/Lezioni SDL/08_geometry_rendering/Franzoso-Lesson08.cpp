#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

const int WIDTH = 640;
const int HEIGHT = 480;

SDL_Window* myWindow = NULL;
SDL_Renderer* myRenderer = NULL;
SDL_Texture* myTexture = NULL;

SDL_Texture* loadTexture(string path){
    //Dichiara texture finale
    SDL_Texture* newTexture = NULL;

    //Carica l'immagine su una superficie
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    //Controlla riuscita caricamento
    if(loadedSurface == NULL){
        cout << endl << "Impossibile caricare immagine su superficie. Chiudere il programma e riprovare. \n";
    }else{
        //Crea textura dalla superficie contenente l'immagine
        newTexture = SDL_CreateTextureFromSurface(myRenderer, loadedSurface);

        //Controlla riuscita creazione
        if(newTexture == NULL){
            cout << endl << "Impossibile creare texture da immagine. Chiudere il programma e riprovare. \n";
        }
    }

    //Libera la memoria della superficie
    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;

    //Ritorna newTexture
    return newTexture;
}

bool init(){
    bool success = true;

    //Inizializza SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << endl << "Impossibile inizializzare SDL! \nSDL Error: " << SDL_GetError() << endl;
        success = false;
    }else{
        //Imposta texture lineare
        if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            cout << endl << "ATTENZIONE! Texture impostata non come lineare. \n";

        //Crea finestra
        myWindow = SDL_CreateWindow("Lesson 08", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

        if(myWindow == NULL){
            cout << endl << "Impossibile creare finestra! \nSDL Error: " << SDL_GetError() << endl;
            success = false;
        }else{
            //Crea renderer
            myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);

            if(myRenderer == NULL){
                cout << endl << "Impossibile creare renderer! \nSDL Error: " << SDL_GetError() << endl;
                success = false;
            }else{
                //Setta colori iniziali renderer
                SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Inizializza SDL_image
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)& imgFlags)){
                    cout << endl << "Impossibile inizializzare SDL image! \nSDL image Error: " << IMG_GetError() << endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia(){
    bool success = true;

    myTexture = loadTexture("viewport.png");

    if(myTexture == NULL){
        cout << endl << "Impossibile caricare texture. Chiudere il programma e riprovare. \n";
        success = false;
    }

    return success;
}

void close(){
    //Distruggi texture
    SDL_DestroyTexture(myTexture);
    myTexture = NULL;

    //Distruggi finestra
    SDL_DestroyRenderer(myRenderer);
    SDL_DestroyWindow(myWindow);
    myRenderer = NULL;
    myWindow = NULL;

    //Chiudi SDL e SDL_image
    SDL_Quit();
    IMG_Quit();
}

int main(int argc, char* args[]){
    if(!init())
        cout << endl << "Errore di inizializzazione. Chiudere il programma e riprovare. \n";
    else{
        if(!loadMedia())
            cout << endl << "Impossibile caricare l'immagine. Chiudere il programma e riprovare. \n";
        else{
            bool quit = false;
            SDL_Event e;

            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT)
                        quit = true;
                }

                //Pulisce schermo (sfondo bianco)
                SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(myRenderer);

                //Copia texture in porzione superiore schermo
                SDL_Rect viewport_dimension = {WIDTH/4, 0, WIDTH/2, HEIGHT/4};
                SDL_RenderSetViewport(myRenderer, &viewport_dimension);
                SDL_RenderCopy(myRenderer, myTexture, NULL, NULL);
                SDL_RenderSetViewport(myRenderer, NULL);

                //Disegna rettangolo rosso riempito (dimensioni, colore, disegno)
                SDL_Rect fillRect = {WIDTH/4, HEIGHT/4, WIDTH/2, HEIGHT/2};
                SDL_SetRenderDrawColor(myRenderer, 255, 0, 0, 255);
                SDL_RenderFillRect(myRenderer, &fillRect);

                //Disegna rettangolo esterno contorno
                SDL_Rect outlineRect = {WIDTH/6, HEIGHT/6, WIDTH*2/3, HEIGHT*2/3};
                SDL_SetRenderDrawColor(myRenderer, 0, 255, 0, 255);
                SDL_RenderDrawRect(myRenderer, &outlineRect);

                //Disegna diagonali oblique blu
                SDL_SetRenderDrawColor(myRenderer, 0, 0, 255, 255);
                SDL_RenderDrawLine(myRenderer, 0, 0, WIDTH, HEIGHT);
                SDL_RenderDrawLine(myRenderer, WIDTH, 0, 0, HEIGHT);

                //Disegna linea puntiforme orizzontale
                SDL_SetRenderDrawColor(myRenderer, 255, 255, 0, 0);
                for(int i=0; i<WIDTH; i+=4){
                    SDL_RenderDrawPoint(myRenderer, i, HEIGHT/2);
                }

                //Update screen
                SDL_RenderPresent(myRenderer);
            }
        }
    }

    close();

    system("PAUSE");
    return 0;
}
