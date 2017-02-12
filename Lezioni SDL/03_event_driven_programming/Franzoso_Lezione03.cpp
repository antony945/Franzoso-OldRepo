#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#define WIDTH 640
#define HEIGHT 480

using namespace std;

bool init();
bool loadMedia();
void close();

SDL_Window* myWindow = NULL;
SDL_Surface* mySurface = NULL;
SDL_Surface* imageSurface = NULL;

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
		myWindow = SDL_CreateWindow("Nome Finestra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

		//Controlla riuscita creazione
		if(myWindow == NULL){
			//Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
			cout << endl << "IMPOSSIBILE CREARE FINESTRA! \n";
			cout << "SDL Error: " << SDL_GetError() << endl;

			//Cambia il valore della variabile 'success'. Inizializzazione non riuscita
			success = false;
		}else{
			//Crea la superficie della finestra attraverso la funzione dedicata
			mySurface = SDL_GetWindowSurface(myWindow);
		}
	}

	//La funzione ritorna il valore della variabile 'success'. Inizializzazione riuscita 'true', altrimenti 'false'
	return success;
}

bool loadMedia(){
    bool success = false;

    imageSurface = SDL_LoadBMP("x.bmp");

    //Controlla riuscita creazione
    if(imageSurface == NULL){
        //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
        cout << endl << "IMPOSSIBILE CREARE FINESTRA! \n";
        cout << "SDL Error: " << SDL_GetError() << endl;

        //Cambia il valore della variabile 'success'. Inizializzazione non riuscita
        success = false;
    }
}

void close(){
    SDL_FreeSurface(imageSurface);
    imageSurface = NULL;

    SDL_DestroyWindow(myWindow);
    myWindow = NULL;

    SDL_Quit();
}


int main(int argc, char* args[]){
    if(init() && loadMedia()){
        bool quit = false;
        SDL_Event event;

        while(!quit){
            while(SDL_PollEvent(&event) != 0){
                if(event.type == SDL_QUIT)
                    quit = true;
            }

            SDL_BlitSurface(imageSurface, NULL, mySurface, NULL);
            SDL_UpdateWindowSurface(myWindow);
        }
    }else{
        cout << endl << "ERRORE NEL PROGRAMMA! \n";
        cout << "Correggere gli errori proposti e riprovare.";
    }

    system("PAUSE");
    return 0;
}
