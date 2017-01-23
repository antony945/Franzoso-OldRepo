#pragma once
#include "Variables.h"
/*Piegari:
funzione di inizializzazione delle variabili e dei puntatori*/
bool inizializza(); //funzione atta a inizializzare le librerie, strutture, array, variabili ecc.

					/*Polesel:
					funzione standard per il caricamento di texture da file .png*/
SDL_Texture* CaricaTexture(std::string path); //caricamento di tutte le texture

					  /*Piegari:
					  disegno della tabella principale*/
void DisegnaTabella(); //Disegno tabella attraverso viewport

					   /*Dittadi:
					   display di un messaggio di benvenuto della durata di 5 secondi
					   */
void MessaggioIniziale(); //Display del messaggio di benvenuto 

						  /*Vio:
						  funzione per determinare l'index della casella in cui è stato cliccato il mouse
						  nota: l'ordine delle caselle procede da sinistra verso destra e dall'alto verso il basso*/
int GestisciEvento(); //deve dare in output l'index della casella ; ritorna -1 se l utente non ha cliccato su una casella

					  /*Polesel:
					  funzione per il controllo della disponibilità della casella*/
bool ControlloCasella(); //Restituisce vero se la casella è libera e falso se è già occupata

						 /*Mangiacapre:
						viewport che renderizza la texture del cerchio trasformando l'index in coordinate x e y*/
void DisegnaCerchio(); //Disegna il simbolo 

					   /*Franzoso:
					   viewport che renderizza la texture del croce trasformando l'index in coordinate x e y */
void DisegnaCroce();

						/*Vio:
						funzione che restituisce vero in caso di vittoria*/
bool ControlloVittoria(); //restituisce vero in caso di vittoria

						  /*Dittadi:
						  restituisce verso in caso di pareggio */
bool ControlloPareggio(); //restituisce vero in caso di pareggio

						  /*Mangiacapre:
						  display del messaggio finale con il vincitore e il perdente
						  nota: in caso sia vero il giocatore del turno corrente ha PERSO la partita*/
void MessaggioFinale(); //DIsplay del messaggio finale in base al risultato

						/*Franzoso:
						gestione della chiusura di SDL*/
void Chiusura(); //Termina SDL, distrugge finestre, texture e superfici e annulla i puntatori.

void AggiornaCasella();
