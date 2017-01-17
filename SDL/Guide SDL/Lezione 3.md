# Lezione 3 - _Event Driven Programming_

***

Tipi di variabili|Utilizzo
------------------|--------------
SDL_Window|Crea la finestra fisica nella quale si lavorerà
SDL_Surface|Crea una superficie di lavoro
SDL_Event|Gestisce gli eventi in input, contiene le strutture per i diversi tipi di eventi (in questa guida solo SDL_QUIT)

Nuove funzioni|Input|Utilizzo
-----------------|--------|-------
SDL_PollEvent|&Variabile SDL_Event|Svolge gli eventi aggiunti alla coda finchè essa non è vuota, in quel caso restituisce il valore **zero**.
***

## Da ricordare
* La funzione SDL_PollEvent va utilizzata come condizione del ciclo al fine di eseguire una data azione quando avviene un determinato evento.
**Codice controllo chiusura programma**:
```c++
bool quit = false;
SDL_Event event;

while(!quit){
    while(SDL_PollEvent(&event)!=0){
        if(event.type==SDL_QUIT)
            quit = true;
    }
    //Applica immagine con funzione dedicata e aggiorna la finestra
}
```
* Con il codice riportato sopra il programma termina e la finestra si chiude **SOLAMENTE** quando l'utente esprime la volontà di chiudere il programma premendo sulla X in alto a destra.

***

**Sintesi elaborata da Franzoso Antonio.**

Ref: [Lezione 3](http://lazyfoo.net/tutorials/SDL/03_event_driven_programming/index.php)