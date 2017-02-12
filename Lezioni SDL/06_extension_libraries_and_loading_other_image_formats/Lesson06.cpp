#include <SDL.h> //Libreria standard SDL
#include <SDL_image.h> //Libreria SDL Image
#include <iostream> //Libreria standard C++
#include <stdlib.h> //Libreria standard C
#include <string> //Libreria necessaria per utilizzare stringhe

#define WIDTH 640 //Definisce la costante per la lunghezza della schermata (WIDTH)
#define HEIGHT 480 //           "     "          altezza della schermata (HEIGHT)

using namespace std;

bool Init();
//FUNZIONE CHE INIZIALIZZA IL PROGRAMMA e LE VARIABILI.
//Restituisce "TRUE" o "FALSE" a seconda dell'esito dell'operazione

bool loadMedia();
//FUNZIONE CHE CARICA TUTTE LE IMMAGINI NELLE VARIABILI CORRISPONDENTI.
//Restituisce "TRUE" o "FALSE" a seconda dell'esito dell'operazione

SDL_Surface* loadSurface(string path);
//FUNZIONE CHE CARICA LE IMMAGINI INDIVIDUALMENTE.
//Restituisce una variabile SDL_Surface* nella quale poter caricare l'immagine.

void Quit();
//FUNZIONE CHE LIBERA LA MEMORIA E CHIUDE SDL + SDL_image.

SDL_Window* myWindow = NULL; //Finestra

SDL_Surface* mySurface = NULL; //Superficie primaria finestra

SDL_Surface* pngSurface = NULL; //Superficie nella quale viene caricata l'immagine .png

int main(int argc, char* args[]){
    if(!Init() || !loadMedia()){
        cout << endl << "ERRORE NEL PROGRAMMA! \nCorreggere errore/i proposto/i e riprovare." << endl;
    }else{
        //Variabile booleana per il ciclo while, diventra true se l'utente richiede la chiusura
        bool quit = false;

        //Dichiarazione variabile evento
        SDL_Event event;

        //Main loop (continua finchè l'utente non richiede la chiusura)
        while(!quit){
            //Cattura gli eventi accaduti e li aggiunge alla coda svolgendoli
            while(SDL_PollEvent(&event) != 0){
                //Controllo richiesta chiusura
                if(event.type == SDL_QUIT)
                    //Cambia il valore della variabile 'quit'. Chiusura richiesta
                    quit = true;
            }

            //Copia il contentuto dela superficie con immagine nella superficie primaria
            SDL_BlitSurface(pngSurface, NULL, mySurface, NULL);

            //Apllica modifiche alla finestra
            SDL_UpdateWindowSurface(myWindow);
        }
    }

    Quit();
    system("PAUSE");
    return 0;
}

bool Init(){
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
		myWindow = SDL_CreateWindow("Nome Finestra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

		//Controlla riuscita creazione
		if(myWindow == NULL){
			//Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
			cout << endl << "IMPOSSIBILE CREARE FINESTRA! \n";
			cout << "SDL Error: " << SDL_GetError() << endl;

			//Cambia il valore della variabile 'success'. Inizializzazione non riuscita
			success = false;
		}else{
		    //Inizializza IMG_INIT_PNG
		    int imgFlags = IMG_INIT_PNG;
		    if(!IMG_Init(imgFlags)&imgFlags){
                //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
                cout << endl << "IMPOSSIBILE INIZIALIZZARE SDL_image! \n";
                cout << "SDL_image Error: " << IMG_GetError() << endl;

                //Cambia il valore della variabile 'success'. Inizializzazione non riuscita
                success = false;
		    }
			//Crea la superficie della finestra attraverso la funzione dedicata
			mySurface = SDL_GetWindowSurface(myWindow);
		}
	}

	//La funzione ritorna il valore della variabile 'success'. Inizializzazione riuscita 'true', altrimenti 'false'
	return success;
}

bool loadMedia(){
    //Dichiara variabile booleana che fornisce l'esito del caricamento (true or false). Inizializzata con true
    bool success = true;

    //Carica immagine .png
    pngSurface = loadSurface("loaded.png");

    if(pngSurface == NULL){
		//Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
        cout << endl << "IMPOSSIBILE CARICARE IMMAGINE .png! \n";
        cout << "SDL_image Error: " << IMG_GetError() << endl;

        //Cambia il valore della variabile 'success'. Caricamento non riuscito
		success = false;
	}

	//La funzione ritorna il valore della variabile 'success'. Caricamento riuscito 'true', altrimenti 'false'
	return success;
}

SDL_Surface* loadSurface(string path){
    SDL_Surface* immagineOttimizzata = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    //Controllo creazione superficie
    if(loadedSurface == NULL){
        //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
        cout << endl << "IMPOSSIBILE CARICARE IMMAGINE " << path.c_str() << "! \n";
        cout << "SDL_image Error: " << IMG_GetError() << endl;
    }else{
        //Conversione della superficie nel formato dello schermo
        immagineOttimizzata = SDL_ConvertSurface(loadedSurface, mySurface->format, NULL);

        //Controllo creazione superficie
        if(immagineOttimizzata == NULL){
            //Messaggio di errore + visualizzazione dell'errore attraverso funzione dedicata
            cout << endl << "IMPOSSIBILE OTTIMIZZARE IMMAGINE " << path.c_str() << "! \n";
            cout << "SDL_image Error: " << IMG_GetError() << endl;
        }
    }

    return immagineOttimizzata;
}

void Quit(){
    //Libera la memoria
    SDL_FreeSurface(pngSurface);
    pngSurface = NULL;

    //Elimina la finestra
    SDL_DestroyWindow(myWindow);
    myWindow = NULL;

    //Chiude SDL e SDL_Image
    SDL_Quit();
    IMG_Quit();
}


