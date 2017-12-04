#pragma once
#include "ambiente.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector> //per creare gli array con nomi
#include <memory> //per evitare errori di memoria nei vettori di classi
#include <time.h>

#include <stdio.h>
#include <cstdlib>
#include <math.h>

using namespace std;
#ifndef FORMICHE_H
#define FORMICHE_H
class Formica { //da spostare nel .h
public:
	float arrivo_x=200, arrivo_y=800;
	float pos_x=50, pos_y=50; //sarà un punto in una matrice 800x800
	Uint8 colore[4]; //colore della formica, dalla texture base (nera) si cambiano i colori con i comandi di SDL
	int larghezza=50, altezza=50; //dimensioni della formica
	float mod_vel=1; //modulo della velocità della formica, assume valori 0 (ferma), 1 (in moviemento), 2 (evento)
	float angolo =0;//attuale angolo della formica
	SDL_Texture* texture;
	Formica();
	void trasportaOggetto(SDL_Renderer *renderer, SDL_Texture* obsTexture);
	string type;
	float calcoloDistanza(int p1x, int p1y, int p2x, int p2y);
	SDL_Point* bestChoice(int x1, int y1);
	enum azione //enumerazione di azioni da sostituire con la matrice di azioni per gli automi a stati finiti
	{
		going_to_base,
		idle,
		moving,
		eating,
		food_searching,//stato di ricerca random del cibo
		trasporting,
		dead
	};
	azione a;
	void ruota(int angolo); //imposta l'angolo della texture formica
	void setAngolo(); //imposta l'angolo di direzione della formica
	void passo(Ambiente *ambiente); //la formica esegue un passo verso le coordinate di arrivo in base al modulo della sua velocità
	/*bool afferra();
	bool mangia();*/
	/*bool rilascia();
	bool controllaCambiamenti();*/
	void render(SDL_Renderer* renderer); //azioni standard delle formiche
	virtual void tick(Ambiente* ambiente) { cout << "Formica" << endl; } //tick di azione per la formica
	SDL_Texture* caricaTexture(Uint8 colore[], string path, SDL_Renderer* renderer); //carica la texture della formica
};

Formica::Formica()//costruttore standard oggetto Formica
{

}
void Formica::ruota(int angolo) { Formica::angolo = angolo; }
void Formica::passo(Ambiente *ambiente) { //esegue un passo verso le coordinate di arrivo, in base alla velocità
	setAngolo();//imposta l'angolo
	pos_x += cos(angolo)*mod_vel; //esegue tot passi lungo l'asse x
	pos_y += sin(angolo)*mod_vel; //esegue tot passi lungo l'asse y
	/*int x = pos_x + cos(angolo)*larghezza / 2;
	int y = pos_y + sin(angolo)*altezza / 2;*/



	/*if (ambiente->Ostacoli[x][y] != 0&&(a==food_searching||a==going_to_base)) {
		SDL_Point* choice = bestChoice(pos_x, pos_y);
		arrivo_x = choice->x;
		arrivo_y = choice->y;
		a = going_to_base;*/
		//pos_x -= cos(angolo)*mod_vel; //esegue tot passi lungo l'asse x
		//pos_y -= sin(angolo)*mod_vel; //esegue tot passi lungo l'asse y
		//	rimbalzo_x = pos_x - cos(angolo)*mod_vel;
		//	rimbalzo_y= pos_y - sin(angolo)*mod_vel;
		/*	return -1;
		}*/


	//return 1;

}
void Formica::setAngolo() {

	Formica::angolo =  180 / 3.14*atan((arrivo_y - pos_y) / (arrivo_x - pos_x)); //conversioni in gradi dell'angolo della formica
}
void Formica::render(SDL_Renderer* renderer){ //render formica
	int angolo2=angolo;//se l'angolo non è compreso tra 90° e 270°, l'angolo di render rimane invariato
	if(cos(angolo)<0) //se l'angolo è compreso tra 90° e 270°, aggiunge 180° alla rotazione della texture (per direzionare la formica correttamente)
	{
		angolo2 = 180+angolo;
	}

	SDL_Rect dstrect = { pos_x-(larghezza/2), pos_y-(altezza/2), larghezza, altezza }; //tutte le variabili sono usate come dichiarate in formica.h
		SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, angolo2+90, NULL, SDL_FLIP_NONE);//renderizza la texture secondo l'angolo dato
}
SDL_Texture* Formica::caricaTexture(Uint8 colore[], string path, SDL_Renderer* renderer)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str()); //carica l'immagine da un percorso
	if (loadedSurface != NULL) { SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format,  0, 0, 0)); } //elimina il nero nell'immagine, rimpiazzandolo con pixel vuoti
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface); //crea la texture
	SDL_SetTextureColorMod(newTexture, colore[0], colore[1], colore[2]); //imposta una mask sui pixel rimanenti
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

void Formica::trasportaOggetto(SDL_Renderer *renderer, SDL_Texture* obsTexture)
{
	SDL_Rect dstrect = { pos_x-larghezza/10+cos(angolo)*larghezza/3, pos_y-altezza/10+sin(angolo)*altezza/3, larghezza/5, altezza/5 }; //tutte le variabili sono usate come dichiarate in formica.h
	SDL_RenderCopyEx(renderer, obsTexture, NULL, &dstrect, 0, NULL, SDL_FLIP_NONE);//renderizza la texture secondo l'angolo dato

}
SDL_Point* Formica::bestChoice(int x1, int y1)
{
	int stdNest = 750;
	int min_x, min_y;
	float p1, p2, p3, p4;

	p1 = calcoloDistanza(x1 + 1, y1, stdNest, stdNest);
	p2 = calcoloDistanza(x1 - 1, y1, stdNest, stdNest);
	p3 = calcoloDistanza(x1, y1 + 1, stdNest, stdNest);
	p4 = calcoloDistanza(x1, y1 - 1, stdNest, stdNest);

	if (p1 <= p2&&p1<=p3&&p1<=p4)
	{
		min_x = x1 + 1;
		min_y = y1;
	}
	if (p2 <= p1&&p2<=p3&&p2<=p4)
	{
		min_x = x1 - 1;
		min_y = y1;
	}
	if (p3 <= p1&&p3<=p2&&p3<=p4)
	{
		min_x = x1;
		min_y = y1 + 1;
	}
	if (p4 <= p1&&p4<=p3&&p4<=p2)
	{
		min_x = x1 + 1;
		min_y = y1;
	}





	SDL_Point min={ min_x, min_y};

	return &min;

}
float Formica::calcoloDistanza(int p1x, int p1y, int p2x, int p2y)
{
	return sqrt(pow(p1x - p2x, 2) + pow(p1y - p2y, 2));
}
#endif // !FORMICHE_H
