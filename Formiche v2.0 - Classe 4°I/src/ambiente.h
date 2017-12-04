#pragma once
#include "ostacoli.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector> //per creare gli array con nomi
#include <memory> //per evitare errori di memoria nei vettori di classi
#include <time.h>

#include <stdio.h>
#include <cstdlib>
#include <math.h>


class Formica;
#ifndef AMBIENTE_H

#define AMBIENTE_H
SDL_Window* gWindow;//creazione finestra
SDL_Renderer* Renderer; //creazione renderer
const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 800;
string pathObs = "dot.jpg";
SDL_Texture* caricaTexture2(string path, SDL_Renderer* renderer); //caricamento texture ambiente
SDL_Texture* caricaTexture3(string path, SDL_Renderer* renderer);
SDL_Texture *obsTexture;


class Sole {

public:
	int raggioSole = 100;
	SDL_Point posizioneSole = {SCREEN_WIDTH-raggioSole, SCREEN_HEIGHT/2};

	void setPosizioneSole() {//cambia la posizione del sole in base ai cicli (da vedere se aggiornare e farlo in base al tempo)
		if (posizioneSole.x <= 0)//se il sole esce dallo schermo, ricomincia la giornata dal punto più a est della futura matrice
		{
			posizioneSole.x = (SCREEN_WIDTH -1);
		}
		else{ posizioneSole.x -= 1; }

		}

};
SDL_Texture* textureSole;


class Ambiente : public Sole {
public:
	SDL_Texture* textureAmbiente;
	int Ostacoli[SCREEN_WIDTH][SCREEN_HEIGHT]; //matrice ostacoli, sovrapponibile con la finestra del gioco

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
	void aggiungiOstacolo(int pos_x, int pos_y, int larghezza, int altezza, SDL_Texture* texture, bool type)//aggiunge n ostacoli al vettore ostacoli creato prima
	{
		Uint8 colore[3]{ 0, 0, 0 };

		SDL_SetTextureColorMod(texture, colore[0], colore[1], colore[2]); //imposta una mask sui pixel rimanenti


			T t(pos_x, pos_y, larghezza, altezza, texture, type); //creazione oggetto del template T

			int type1 = type;
			shared_ptr<Ostacolo> ptr = make_shared<T>(t); //crea un pointer dell'oggetto nella classe T
			ostacoli.push_back(ptr); //aggiunge il pointer all'oggetto t all'array formiche

			for(int i=0;i<altezza;i++){
				for (int k = 0; k < larghezza; k++) {
					Ostacoli[i + pos_x][k + pos_y] = type1; //impostazione tipo di ostacolo all'interno di una matrice
				}

			}


	}
	void rimuoviOstacolo(int index) { //funzione per la rimozione di un ostacolo (ad esempio un cibo)
		for (int i = 0; i< ostacoli.at(index).get()->altezza; i++) { //ciclo per l'eliminazione dalla matrice
			for (int k = 0; k < ostacoli.at(index).get()->larghezza; k++) {
				Ostacoli[i + ostacoli.at(index).get()->pos_x][k + ostacoli.at(index).get()->pos_y] = 0;
			}

		}
		ostacoli.at(index).get()->~Ostacolo(); //chiama il distruttore della classe per eliminare l'oggetto a cui il pointer punta
		ostacoli.at(index).~shared_ptr(); //distrugge il pointer nel vettore
		ostacoli.erase(ostacoli.begin() + index); //elimina la casella dell'index dal vettore

	}

	SDL_Texture* caricaTexture(string path, SDL_Renderer* renderer) //caricamento texture ambiente
	{
		SDL_Texture* newTexture = NULL;

		SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //carica l'immagine da un percorso
		if (loadedSurface != NULL) { SDL_SetColorKey(loadedSurface, SDL_FALSE, SDL_MapRGB(loadedSurface->format, 0, 0, 0)); }
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); //crea la texture
		SDL_FreeSurface(loadedSurface);
		return newTexture;
	}




};
#include "formica.h"

bool close = false;


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
			Renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

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
	textureSole = caricaTexture3(pathObs, Renderer);
	obsTexture = caricaTexture2(pathObs, Renderer);
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

void aggiornaOstacoli(Ambiente *ambiente) {

	SDL_Rect dstrect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; //tutte le variabili sono usate come dichiarate in formica.h
	SDL_RenderCopyEx(Renderer, ambiente->textureAmbiente, NULL, &dstrect, NULL, NULL, SDL_FLIP_NONE);//renderizza la texture secondo l'angolo dato
	for (unsigned int i = 0; i < ambiente->ostacoli.size(); i++) {//.size restituisce unsigned int || esegue i tick di ogni formica
			ambiente->ostacoli[i].get()->tick(*&ambiente);
		}
}
void aggiornaFormiche(Ambiente *ambiente)
{
	for (unsigned int i = 0; i < ambiente->formiche.size(); i++) {//.size restituisce unsigned int || esegue i tick di ogni formica
		ambiente->formiche[i].get()->render(Renderer);
		ambiente->formiche[i].get()->tick(*&ambiente);
	}
}
SDL_Texture* caricaTexture2(string path, SDL_Renderer* renderer) //caricamento texture ambiente
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //carica l'immagine da un percorso
	if (loadedSurface != NULL) { SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0)); }
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); //crea la texture
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

SDL_Texture* caricaTexture3(string path, SDL_Renderer* renderer) //caricamento texture ambiente
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //carica l'immagine da un percorso
	if (loadedSurface != NULL) { SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0)); }
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); //crea la texture
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}
#endif // !AMBIENTE_H
