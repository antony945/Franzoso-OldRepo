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

Ambiente ambiente;
void drawNest();
void drawCircle(Ambiente *ambiente);

float calcoloDistanza(int p1x,int p1y,int p2x,int p2y);
void multipleObs(int Obs_x, int Obs_y, int quantita, SDL_Texture* texture, bool type);
class Soldato :public Formica {public:
	void tick(Ambiente* ambiente) {
		passo(ambiente);
		if (fabs(arrivo_x - pos_x) < 25 && fabs(arrivo_y - pos_y) < 25) {//funzione per il cambio di direzione una volta all'arrivo
		arrivo_x = rand() % 800;//numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
		arrivo_y = rand() % 800;//numero random di coordinata arrivo (utilizzabile nella ricerca cibo)

	}
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(Renderer, pos_x, pos_y, arrivo_x, arrivo_y); //linea di direzione con arrivo formica
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

}

Soldato() {
	//a = food_searching;
	//srand(time(NULL));
	arrivo_x = rand() % 800; //numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
	arrivo_y = rand() % 800;//numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
	Uint8 colore[3]{ 0, 0, 255 }; //colore formica soldato
	texture = caricaTexture(colore, "image.jpg", Renderer); //caricamento texture ruolo Soldato
	type = "soldato";
} };
class Regina : public Formica { public:

	void tick(Ambiente* ambiente) {  passo(ambiente); if (fabs(arrivo_x - pos_x) < 25 && fabs(arrivo_y - pos_y) < 25) {//funzione per il cambio di direzione una volta all'arrivo
		arrivo_x = rand() % 800; //numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
		arrivo_y = rand() % 800;//numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
	}
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(Renderer, pos_x, pos_y, arrivo_x, arrivo_y); //linea di direzione e arrivo
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	}
	Regina() {
		srand(time(NULL)); //inizializzazione seed funzione rand()
		arrivo_x = rand() % 800;//numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
		arrivo_y = rand() % 800;//numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
	Uint8 colore[3]{ 0, 255, 255 }; //colore formica Regina
	texture = caricaTexture(colore, "image.jpg", Renderer); //caricamento texture formica regina
	type = "regina";
}
};
class Operaie : public Formica {
public:
	void tick(Ambiente* ambiente) {
		passo(ambiente);
		if (fabs(arrivo_x - pos_x) < 25 && fabs(arrivo_y - pos_y) < 25) {//funzione per il cambio di direzione una volta all'arrivo
			arrivo_x = rand() % 800; //numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
			arrivo_y = rand() % 800;//numero random di coordinata arrivo (utilizzabile nella ricerca cibo)
		}
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
		SDL_RenderDrawLine(Renderer, pos_x, pos_y, arrivo_x, arrivo_y); //linea di direzione e arrivo
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	} Operaie() {
		type = "operaie"; a = idle; Uint8 colore[3]{ 255, 255, 0 }; //colore formica Regina
		texture = caricaTexture(colore, "image.jpg", Renderer); //caricamento texture formica regina }
	}
};
	void Cibo::tick(Ambiente* ambiente) { render(Renderer); };
int main(int argc, char* args[]) {
	init(); //funzioni di creazione finestra e renderer
	time_t start = time(NULL); //tempo di inizio del gioco
	time_t movement = 1; //delay in secondi di movimento sole

	ambiente.aggiungiFormica<Soldato>(10);//aggiunge n oggetti t all'array formiche
	ambiente.aggiungiFormica<Regina>(1);//aggiunge n oggetti t all'array formiche
	ambiente.aggiungiFormica<Operaie>(10);//aggiunge n oggetti t all'array formiche
	multipleObs(400, 400, 2500, obsTexture, true);
	//ambiente.aggiungiOstacolo<Cibo>(100, 100, 30, 30, obsTexture, true);//aggiunge un oggetto al vettore di pointer ostacolo
	//ambiente.aggiungiOstacolo<Cibo>(400, 400, 30, 30, obsTexture, true);//TRUE = CIBO, FALSE = OSTACOLO, vengono inseriti tutti nella stessa matrice
	ambiente.textureAmbiente = ambiente.caricaTexture("ambient.jpg", Renderer);




	SDL_Event e;
	while (close==false) {
		controllaEventi(&e); //controlla la queue di eventi e li attiva
		SDL_RenderClear(Renderer);

		aggiornaOstacoli(&ambiente);//aggiorna lo schermo in base al renderer, aggiornando tutte le formiche
		drawNest();
		drawCircle(&ambiente);
		aggiornaFormiche(&ambiente);
		SDL_RenderPresent(Renderer);
		time_t currentTime = time(NULL); //imposta il tempo corrente
		if ((fabs(difftime(start,currentTime)))> movement) {//movimento sole dopo "movement" secondi
			start += movement;//aumenta di "movement" secondi start e in modo da muovere il sole ogni "movement" secondi
			ambiente.setPosizioneSole();//muove il sole di un pixel
			//cout << ambiente.posizioneSole.x <<"  "<<ambiente.posizioneSole.y<< endl;//cout di prova della posizione del sole
		}

	}
	SDL_Quit(); //Chiude SDL
		return 0;
}

void drawNest()
{
	int circleRadius = 50;
	int radius = circleRadius;
	SDL_SetRenderDrawColor(Renderer, 139, 69, 19, 255); //draw color sul marrone

	SDL_Point point{ 0,0 }; //punto di disegno, inizializzazione

	while (circleRadius > 0)
	{
		if (circleRadius < 8) {
			SDL_SetRenderDrawColor(Renderer,0,0,0, 255); //draw color sul nero
		}
		for (int t = 0; t < 360; t++) //ciclo di draw del centro del nido
		{
			point.x = SCREEN_WIDTH - radius +circleRadius * cos(t);
			point.y = SCREEN_HEIGHT - radius + circleRadius * sin(t);
			SDL_RenderDrawPoint(Renderer, point.x, point.y); //disegna fisicamente il punto
		}
		circleRadius--;
	}
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);//inizializzazione draw color
}
void drawCircle(Ambiente *ambiente)//disegna cerchio  sul render
{
	int lato =ambiente->raggioSole ;
	SDL_Rect dstrect = { ambiente->posizioneSole.x , ambiente->posizioneSole.y , lato, lato }; //tutte le variabili sono usate come dichiarate in formica.h
	SDL_RenderCopyEx(Renderer,textureSole , NULL, &dstrect, 0, NULL, SDL_FLIP_NONE);//renderizza la texture secondo l'angolo dato
}

void multipleObs(int Obs_x, int Obs_y, int quantita, SDL_Texture* texture, bool type)//aggiunge cibi multipli
{
	int standard = 5 ;//grandezza standard
	int lato = sqrt(quantita); //lato "quadrato" cibo
	int i = 0; int k = 0;
	for (true; i<lato > 0; i++) {
	ambiente.aggiungiOstacolo<Cibo>(Obs_x + i, Obs_y + k, standard, standard, texture, type); //ciclo asse x

	for (k=0; k<lato; k++) {
		ambiente.aggiungiOstacolo<Cibo>(Obs_x + i, Obs_y + k, standard, standard, texture, type); //ciclo asse y
		}
	}
}

float calcoloDistanza(int p1x, int p1y, int p2x, int p2y)
{
	return sqrt(pow(p1x - p2x, 2) + pow(p1y - p2y, 2));
}
