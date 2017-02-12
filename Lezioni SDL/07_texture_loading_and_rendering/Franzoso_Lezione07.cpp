#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdlib.h>
#define WIDTH 640
#define HEIGHT 480

using namespace std;

/* PROTOTIPI FUNZIONI */
bool init();

bool loadMedia();

void close(void);

SDL_Texture* loadTexture(string path);

/* VARIABILI GLOBALI */
SDL_Window* myWindow = NULL;

SDL_Renderer* myRenderer = NULL;

SDL_Texture* myTexture = NULL;

int main(int argc, char* args[]){
    if(!init() || !loadMedia()){
        cout << endl << "ERRORE NEL PROGRAMMA! \n";
        cout << "Correggere gli errori proposti e riprovare.";
    }else{
        bool quit = false;
        SDL_Event event;

        while(!quit){
            while(SDL_PollEvent(&event) != 0){
                if(event.type == SDL_QUIT)
                    quit = true;
            }

            SDL_RenderClear(myRenderer);
            SDL_RenderCopy(myRenderer, myTexture, NULL, NULL);
            SDL_RenderPresent(myRenderer);
        }
    }

    close();

    system("PAUSE");
    return 0;
}

bool init(){
    //Dichiara variabile booleana che fornisce l'esito dell'inizializzazione (true or false). Inizializzata con true
	bool success = true;

	//Inizializza SDL VIDEO
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		//Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
		cout << endl << "IMPOSSIBILE INIZIALIZZARE SDL! \n";
		cout << "SDL Error: " << SDL_GetError() << endl;

		//Cambia il valore della variabile 'success'. Inizializzazione non riuscita
		success = false;
	}else{
		//Crea la finestra attraverso la funzione dedicata
		myWindow = SDL_CreateWindow("SDL - Lesson07", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

		//Controlla riuscita creazione
		if(myWindow == NULL){
			//Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
			cout << endl << "IMPOSSIBILE CREARE FINESTRA! \n";
			cout << "SDL Error: " << SDL_GetError() << endl;

			//Cambia il valore della variabile 'success'. Inizializzazione non riuscita
			success = false;
		}else{
			//Crea il renderer della finestra attraverso la funzione dedicata
			myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);

			//Controlla riuscita creazione
            if(myRenderer == NULL){
                //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
                cout << endl << "IMPOSSIBILE CREARE RENDERER FINESTRA! \n";
                cout << "SDL Error: " << SDL_GetError() << endl;

                //Cambia il valore della variabile 'success'. Inizializzazione non riuscita
                success = false;
            }else{
                //Inizializza il colore utilizzabile dal renderer (RGBA)
                SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Inizializza SDL_image per il caricamento PNG
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)){
                    //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
                    cout << endl << "IMPOSSIBILE INIZIALIZZARE SDL_image! \n";
                    cout << "SDL_image Error: " << IMG_GetError() << endl;

                    //Cambia il valore della variabile 'success'. Inizializzazione non riuscita
                    success = false;
                }
            }
		}
	}

	//La funzione ritorna il valore della variabile 'success'. Inizializzazione riuscita 'true', altrimenti 'false'
	return success;
}

SDL_Texture* loadTexture(string path){
    //Crea texture vuota che conterrà l'immagine
    SDL_Texture* imageTexture = NULL;

    //Carica l'immagine su una nuova superficie
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    //Controlla riuscita creazione
    if(loadedSurface == NULL){
        //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
        cout << endl << "IMPOSSIBILE CARICARE " << path.c_str() << "! \n";
        cout << "SDL_image Error: " << IMG_GetError() << endl;
    }else{
        //Crea texture in base alla superficie contenente l'immagine caricata
        imageTexture = SDL_CreateTextureFromSurface(myRenderer, loadedSurface);

        //Controlla riuscita creazione
        if(imageTexture == NULL){
            //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
            cout << endl << "IMPOSSIBILE CREARE TEXTURE CON IMMAGINE " << path.c_str() << "! \n";
            cout << "SDL Error: " << SDL_GetError() << endl;
        }
    }

    //Libera la memoria allocata
    SDL_FreeSurface(loadedSurface);

    //La funzione ritorna il valore della variabile 'success'. Quando la funzione verrà richiamata, l'immagine sarà caricata direttamente sulla texture
    return imageTexture;
}

bool loadMedia(){
    //Dichiara variabile booleana che fornisce l'esito del caricamento (true or false). Inizializzata con true
    bool success = true;

    //Carica all'interno della texture globale l'immagine "texture.png"
    myTexture = loadTexture("texture.png");

    //Controlla riuscita creazione
    if(myTexture == NULL){
        //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
        cout << endl << "IMPOSSIBILE CARICARE IMMAGINE TEXTURE! \n";

		//Cambia il valore della variabile 'success'. Caricamento immagine non riuscito
        success = false;
    }

    //La funzione ritorna il valore della variabile 'success'. Caricamento riuscito 'true', altrimenti 'false'
    return success;
}

void close(){
    //Distrugge renderer
    SDL_DestroyRenderer(myRenderer);
    myRenderer = NULL;

    //Distrugge texture
    SDL_DestroyTexture(myTexture);
    myTexture = NULL;

    //Distrugge finestra
    SDL_DestroyWindow(myWindow);
    myWindow = NULL;

    //Chiusura e spegnimento SDL + SDL_image
    SDL_Quit();
    IMG_Quit();
}

