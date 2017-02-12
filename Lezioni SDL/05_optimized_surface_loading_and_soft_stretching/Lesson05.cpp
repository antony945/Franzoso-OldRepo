#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#define WIDTH 1080
#define HEIGHT 720

using namespace std;

bool Init(SDL_Window* &window, SDL_Surface* &surface);
bool CaricaImmagine();
void ChiudiSDL();
SDL_Surface* LoadSurface(string path);

SDL_Window* MyWindow = NULL;
SDL_Surface* MySurface = NULL;
SDL_Surface* ImageSurface = NULL;

bool Init(SDL_Window* &window, SDL_Surface* &surface){
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
		window = SDL_CreateWindow("Nome Finestra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

		//Controlla riuscita creazione
		if(window == NULL){
			//Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
			cout << endl << "IMPOSSIBILE CREARE FINESTRA! \n";
			cout << "SDL Error: " << SDL_GetError() << endl;

			//Cambia il valore della variabile 'success'. Inizializzazione non riuscita
			success = false;
		}else{
			//Crea la superficie della finestra attraverso la funzione dedicata
			surface = SDL_GetWindowSurface(window);
		}
	}

	//La funzione ritorna il valore della variabile 'success'. Inizializzazione riuscita 'true', altrimenti 'false'
	return success;
}

bool CaricaImmagine(){
    bool success = true;

    ImageSurface = LoadSurface("03_event_driven_programming/x.bmp");

    if(ImageSurface == NULL){
        cout << "IMPOSSIBILE CARICARE IMMAGINE! \nSDL Error: " << SDL_GetError();
        success = false;
    }

    return success;
}

SDL_Surface* LoadSurface(string path){
    SDL_Surface* OptimizedSurface = NULL;
    SDL_Surface* LoadedSurface = SDL_LoadBMP(path.c_str());

    if(LoadedSurface == NULL){
        cout << "IMPOSSIBILE CARICARE L'IMMAGINE " << path.c_str();
        cout << endl << "SDL Error: " << SDL_GetError();
    }else{
        OptimizedSurface = SDL_ConvertSurface(LoadedSurface, MySurface->format, NULL);

        if(LoadedSurface == NULL){
            cout << "IMPOSSIBILE OTTIMIZZARE L'IMMAGINE " << path.c_str();
            cout << endl << "SDL Error: " << SDL_GetError();
        }

        SDL_FreeSurface(LoadedSurface);
    }

    return OptimizedSurface;
}

void ChiudiSDL(){
    SDL_FreeSurface(ImageSurface);
    ImageSurface = NULL;

    SDL_DestroyWindow(MyWindow);
    MyWindow = NULL;

    SDL_Quit();
}

int main(int argc, char* args[]){

    if(Init(*&MyWindow, *&MySurface) && CaricaImmagine()){
        bool quit = false;
        SDL_Event event;

        while(!quit){
            while(SDL_PollEvent(&event) != 0){
                if(event.type == SDL_QUIT)
                    quit = true;
            }

            SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = WIDTH;
				stretchRect.h = HEIGHT;

            SDL_BlitScaled(ImageSurface, NULL, MySurface, &stretchRect);
            SDL_UpdateWindowSurface(MyWindow);
        }

    }else
        cout << "\nERRORE NEL PROGRAMMA! \nCorreggere gli errori e riprovare.";

    ChiudiSDL();

    system("PAUSE");
    return 0;
}
