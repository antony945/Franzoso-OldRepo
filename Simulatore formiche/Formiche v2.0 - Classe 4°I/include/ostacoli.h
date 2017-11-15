#pragma once
class Ambiente;
#include <SDL.h>
#include "ambiente.h"
#include <SDL_image.h>
#include <iostream>
#include <vector> //per creare gli array con nomi
#include <memory> //per evitare errori di memoria nei vettori di classi
using namespace std;
#ifndef OSTACOLI_H
#define OSTACOLI_H

class Ostacolo {
public:
	int type;
	string path;
	int pos_x, pos_y, larghezza, altezza;
	SDL_Texture* texture;
	virtual void tick(Ambiente* ambiente) {};
};






class Cibo :public Ostacolo {
public:
	Cibo(int pos_x, int pos_y, int larghezza, int altezza, string path, int type);
	int unità_cibo;
	void tick(Ambiente *ambiente) { if (unità_cibo == 0) { } }
};
Cibo::Cibo(int pos_x, int pos_y, int larghezza, int altezza, string path, int type){

	Cibo::pos_x = pos_x;
	Cibo::pos_y = pos_y;
	Cibo::larghezza = larghezza;
	Cibo::altezza = altezza;
	Cibo::path = path;
	Cibo::type = type;
}



#endif // !OSTACOLI_H
