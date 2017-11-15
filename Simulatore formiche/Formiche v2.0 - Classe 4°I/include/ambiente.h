#pragma once
#include "ostacoli.h"
#include "formica.h"
#ifndef AMBIENTE_H
#define AMBIENTE_H
const int SCREEN_HEIGHT = 15;
const int SCREEN_WIDTH = 15;
class Ambiente {
public:

	int Ostacoli[SCREEN_WIDTH][SCREEN_HEIGHT];

	vector<shared_ptr<Formica>>formiche; //array di pointer alla classe Formica
	vector<shared_ptr<Ostacolo>>ostacoli; //array di pointer alla classe Ostacolo

	template<class T> //aggiunge una formica, si può sostituire il T con il ruolo
	void aggiungiFormica(int n)//aggiunge n formiche al vettore formiche creato prima
	{
		for(int i=0;i<n;i++ ){ //ciclo for che crea un oggetto t nell'array formiche
		T t;
		shared_ptr<Formica> ptr = make_shared<T>(t); //crea un pointer dell'oggetto nella classe T
		formiche.push_back(ptr); //aggiunge il pointer all'oggetto t all'array formiche
		}

	}

	template<class T>
	void aggiungiOstacolo(int pos_x, int pos_y, int larghezza, int altezza, string path, int type)//aggiunge n ostacoli al vettore ostacoli creato prima
	{
		
			T t(pos_x, pos_y, larghezza, altezza, path, type);
		
			
			shared_ptr<Ostacolo> ptr = make_shared<T>(t); //crea un pointer dell'oggetto nella classe T
			ostacoli.push_back(ptr); //aggiunge il pointer all'oggetto t all'array formiche
			
			for(int i=0;i<larghezza;i++){//vanno invertiti i cicli perchè risultano invertite le assi al momento
				for (int k = 0; k < altezza; k++) {
					Ostacoli[i + pos_x][k + pos_y] = type;
				}
				
			}
			

	}
	void rimuoviOstacolo(int index) {
		for (int i = 0; i< ostacoli.at(index).get()->larghezza; i++) { //vanno invertiti i cicli perchè risultano invertite le assi al momento
			for (int k = 0; k < ostacoli.at(index).get()->altezza; k++) {
				Ostacoli[i + ostacoli.at(index).get()->pos_x][k + ostacoli.at(index).get()->pos_y] = 0;
			}

		}
		ostacoli.at(index).get()->~Ostacolo(); //chiama il distruttore della classe per eliminare l'oggetto a cui il pointer punta
		ostacoli.at(index).~shared_ptr(); //distrugge il pointer nel vettore
		ostacoli.erase(ostacoli.begin() + index); //elimina la casella dell'index dal vettore
		
	}
	
};

bool close = false;
SDL_Window* gWindow;
SDL_Renderer* gRenderer;

bool init() //funzione standard di inizializzazione SDL
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Simulatore Formiche", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void controllaEventi(SDL_Event *e){
	while (SDL_PollEvent(*&e) != 0)
	{
		//User requests quit
		if (e->type == SDL_QUIT)
		{
			close = true;
		}
	}

}

void aggiornaSchermo(Ambiente *ambiente) {
	SDL_RenderClear(gRenderer);
	for (unsigned int i = 0; i < ambiente->formiche.size(); i++) {//.size restituisce unsigned int
		ambiente->formiche[i].get()->tick(*&ambiente);
	}

}


#endif // !AMBIENTE_H
