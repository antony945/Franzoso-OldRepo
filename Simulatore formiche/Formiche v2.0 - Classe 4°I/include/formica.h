#pragma once
class Ambiente;
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector> //per creare gli array con nomi
#include <memory> //per evitare errori di memoria nei vettori di classi
using namespace std;
#ifndef FORMICHE_H
#define FORMICHE_H
class Formica { //da spostare nel .h
public:
	int pos_x, pos_y; //sarà un punto in una matrice 800x800
	int colore[4]; //colore della formica, dalla texture base (nera) si cambiano i colori con i comandi di SDL
	int anni; //anni della formica
	int larghezza, lunghezza; //dimensioni della formica
	float mod_vel; //modulo della velocità della formica
	int visione; //raggio di visione della formica
	unsigned int angolo_vel; //angolo in gradi della velocità (0 - 359)
	SDL_Texture* texture;
	Formica();

	virtual enum azione
	{
		idle,
		moving,
		eating,
		food_searching //stato di ricerca random del cibo

	};

/*
	void ruota();
	void passo();
	void salto();
	bool afferra();
	bool mangia();
	bool rilascia();
	bool controllaCambiamenti();
	void render();*/
	virtual void tick(Ambiente* ambiente) { cout << "Formica" << endl; }
//	SDL_Texture* caricaTexture(int colore[], string path);
};

Formica::Formica()
{
	
}

#endif // !FORMICHE_H
