#pragma once
class Ambiente;
#include <SDL.h>
#include "ambiente.h"
#include <SDL_image.h>
#include <iostream>
#include <vector> //per creare gli array con nomi
#include <memory> //per evitare errori di memoria nei vettori di classi

#include <stdio.h>
#include <cstdlib>
#include <math.h>

using namespace std;
#ifndef OSTACOLI_H
#define OSTACOLI_H

class Ostacolo {
public:
	int type;//identificatore tipo ostacolo
	string path; //percorso texture ostacolo
	int pos_x, pos_y, larghezza, altezza;//posizione e dimensioni ostacolo
	SDL_Texture* texture;
	void render(SDL_Renderer* renderer) { //render ostacolo

		SDL_Rect dstrect = { pos_x, pos_y, larghezza, altezza }; //tutte le variabili sono usate come dichiarate in formica.h
		SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, NULL, NULL, SDL_FLIP_NONE);//renderizza la texture secondo l'angolo dato
	}
	virtual void tick(Ambiente* ambiente) {  }; //funzione standard tick per l'ostacolo
};






class Cibo :public Ostacolo {
public:
	Cibo(int pos_x, int pos_y, int larghezza, int altezza, SDL_Texture* texture, bool type);//costruttore non-standard per l'oggetto cibo
	void tick(Ambiente *ambiente);

		//texture = caricaTexture("C:/formiche/dot.jpg", renderer);
		//SDL_Rect dstrect = { pos_x, pos_y, larghezza, altezza }; //tutte le variabili sono usate come dichiarate in formica.h
		//SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, NULL , NULL, SDL_FLIP_NONE);//renderizza la texture secondo l'angolo dato

};
Cibo::Cibo(int pos_x, int pos_y, int larghezza, int altezza, SDL_Texture* texture, bool type){ //costruttore non standard
	Cibo::type = type;
	Cibo::pos_x = pos_x;
	Cibo::pos_y = pos_y;
	Cibo::larghezza = larghezza;
	Cibo::altezza = altezza;
	Cibo::texture = texture;
	Cibo::type = type;
}





#endif // !OSTACOLI_H
