#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

const int WIDTH = 302;
const int HEIGHT = 302;

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
        myWindow = SDL_CreateWindow("Prova disegno croce", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

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
                //Pulisce schermo (sfondo bianco)
                SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(myRenderer);

                SDL_SetRenderDrawColor(myRenderer, 0x00, 0x00, 0x00, 0x00 );
                SDL_RenderDrawLine(myRenderer, 100, 0, 100, HEIGHT );
                SDL_RenderDrawLine(myRenderer, 200, 0, 200, HEIGHT );
                SDL_RenderDrawLine(myRenderer, 0, 200, WIDTH, 200 );
                SDL_RenderDrawLine(myRenderer, 0, 100, WIDTH, 100 );

                //Lato del quadrato nel quale viene inscritto il GR della croce

                int index = 6;
                int x1_a = 46;
                int x1_b = 56;
                int y1 = 46;

                //Calcolo posizione partenza linee in base al valore dell'index
                if(index < 4){
                    x1_a+=((index-1)*100);
                    x1_b+=((index-1)*100);
                }else{
                    if(index < 7){
                        x1_a+=(index-4)*100;
                        x1_b+=(index-4)*100;
                        y1+=101;
                    }else{
                        x1_a+=(index-7)*100;
                        x1_b+=(index-7)*100;
                        y1+=2*100;
                    }
                }

                int x2_a = x1_a+10;
                int x2_b = x2_a-10;
                int y2 = y1+10;

                //Inizializza colore nero
                SDL_SetRenderDrawColor(myRenderer, 0x00, 0x00, 0x00, 0x00);

                //Disegno due linee oblique
                SDL_RenderDrawLine(myRenderer, x1_a, y1, x2_a, y2); //LINEA A
                SDL_RenderDrawLine(myRenderer, x1_b, y1, x2_b, y2); //LINEA B

                //Update screen
                SDL_RenderPresent(myRenderer);
                system("PAUSE");
        }
    }

    close();

    system("PAUSE");
    return 0;
}
