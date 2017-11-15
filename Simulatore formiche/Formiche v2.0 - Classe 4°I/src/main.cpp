#include "ambiente.h"
Ambiente ambiente;


class Soldato :public Formica { void tick(Ambiente* ambiente) {  } };
class Regina : public Formica { void tick(Ambiente* ambiente) {  } };
class Operaie : public Formica { void tick(Ambiente* ambiente) { } };

int main(int argc, char* args[]) {
	init(); //funzioni di creazione finestra e renderer	
	
	ambiente.aggiungiFormica<Soldato>(100);//aggiunge 100 oggetti t all'array formiche
	ambiente.aggiungiFormica<Regina>(1);//aggiunge 1 oggetti t all'array formiche
	ambiente.aggiungiFormica<Operaie>(10);//aggiunge 100 oggetti t all'array formiche
	ambiente.aggiungiOstacolo<Cibo>(0, 0, 10, 10, "", 2);
	ambiente.aggiungiOstacolo<Cibo>(11, 0, 2, 2, "", 3);


	for (int i = 0; i<SCREEN_HEIGHT; i++) {
		for (int k = 0; k < SCREEN_WIDTH; k++) {
			cout<<ambiente.Ostacoli[i][k]<<" ";
		}
		cout << "\n";
	}
	ambiente.rimuoviOstacolo(0);
	cout << endl<<endl<<endl;

	for (int i = 0; i<SCREEN_HEIGHT; i++) {
		for (int k = 0; k < SCREEN_WIDTH; k++) {
			cout << ambiente.Ostacoli[i][k] << " ";
		}
		cout << "\n";
	}
	SDL_Event e;
	while (close==false) {
		controllaEventi(&e); //controlla la queue di eventi e li attiva
		aggiornaSchermo(&ambiente); //aggiorna lo schermo in base al renderer, aggiornando tutte le formiche
		SDL_Delay(50);
	}
	SDL_Quit(); //Chiude SDL
		return 0;
}

