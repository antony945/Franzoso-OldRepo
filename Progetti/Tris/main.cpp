#include <iostream>
#include <string>
#include "function.h"
#include "Variables.h"
int main() {

	Inizializza(); //inizializza sdl

	Croce = CaricaTexture("");//carica texture croce
	Cerchio = CaricaTexture("");//carica texture cerchio
	Tabella = CaricaTexture("");//carica texture tabella

	MessaggioIniziale(); //da il benvenuto
	DisegnaTabella(); //render della casella
        SDL_RenderPresent(Renderer);
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		else if(e.type == SDL_MOUSEBUTTONDOWN)
		{
			index = GestisciEvento(); //ottiene l'index della casella cliccata
		}
		
		if
			(ControlloCasella(index) == true)
		{ //controlla se è stata cliccata una casella e se quest'ultima è vuota
			AggiornaCasella(index, turno); //aggiorna la casella cliccata
			turno = !turno;//cambia il turno
			SDL_RenderPresent(Renderer);//aggiorna schermo

		}
		if (ControlloVittoria() || ControlloPareggio())
		{
			quit = true;
		}


	}
}


	MessaggioFinale();
	Chiusura();
	return 0;
}
