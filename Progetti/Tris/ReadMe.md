#Progetto Tris

Come da accordi, questa è una suddivsione generica, non completa e abbozzata del progetto tris.
Di seguito una sommaria suddivisione delle funzioni, le assegnazioni arriveranno non appena avremo una struttura completa.
**Questa volta non è consigliato, bensì _obbligatorio_, esprimere la propria opinione e le proprie proposte di cambiamenti per la struttura**

``` c++
#define altezza 302
#define larghezza 302

SDL_Rect *Posizione[9] = new SDL_Rect;


main(int argc, char* args[])
{
	/*Polesel - Piegari*/
class cTexture{} //classe per la gesione delle informazioni di una texture

    Inizializza(); 
    CaricaTexture();
    DisegnaTabella(); 
    MessaggioIniziale();
    

    bool turno;
    while(!quit)
    {

        GestisciEvento();
        ControlloPosizione();
        ControlloCasella();
        DisegnaSimbolo(index, turno)
        quit = ControlloVittoria();
        quit = ControlloPareggio();
        turno = !turno;

    }
    MessaggioFinale();
    Chiusura();
}

/*Piegari:
funzione di inizializzazione delle variabili e dei puntatori*/
bool inizializza(); //funzione atta a inizializzare le librerie, strutture, array, variabili ecc.

/*Polesel:
funzione standard per il caricamento di texture da file .png*/
bool CaricaTexture(); //caricamento di tutte le texture

/*Piegari:
disegno della tabella principale*/
bool DisegnaTabella(); //Disegno tabella attraverso geometry rendering

/*Dittadi: 
display di un messaggio di benvenuto della durata di 5 secondi
*/
bool MessaggioIniziale(); //Display del messaggio di benvenuto 

/*Vio:
funzione per determinare l'index della casella in cui è stato cliccato il mouse
nota: l'ordine delle caselle procede da sinistra verso destra e dall'alto verso il basso*/
int GestisciEvento(); //deve dare in output l'index della casella

/*Polesel:
funzione per il controllo della disponibilità della casella*/
bool ControlloCasella(); //Restituisce vero se la casella è libera e falso se è già occupata

/*Mangiacapre:
funzione per il disegnamento di un cerchio che stia nella casella 100 x 100 attraverso il geometry rendering, in base alla posizione*/
void DisegnaCerchio(); //Disegna il simbolo 

/*Franzoso:
funzione per il disegnamento di una x in base alla posizione e utilizzando il geometry rendering*/
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
void MessaggioFInale(); //DIsplay del messaggio finale in base al risultato

/*Franzoso: 
gestione della chiusura di SDL*/
void Chiusura(); //Termina SDL, distrugge finestre, texture e superfici e annulla i puntatori.


```

In linea generale intendevamo gestire le funzioni con variabili indipendenti, non globali, e class per ogni texture creata.
Non rifaremo il render di tutta la finestra per ogni turno, ma solo della parte interessata dall'evento.
Intendevamo gestire le singole caselle attraverso un array di char. Un array di SDL_Rect dovrebbe essere utilizabile per la gestione del render delle caselle.
