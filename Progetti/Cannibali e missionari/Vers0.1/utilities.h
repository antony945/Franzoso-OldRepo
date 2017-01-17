//
//  utilities.h
//
//
//  Created by Alberto Carraro on 17/10/16.
//
//

#ifndef utilities_h
#define utilities_h
#include "data_types.h"

/*
 Autore: Riccardo
 Input: configurazione c
 è l'insieme dei dati che descrive la situazione attuale nel gioco
 non viene modificata dalla funzione
 supponiamo che i valori siano consistenti quindi non si fanno controlli
 Dipendenze da altre funzioni: nessuna
 Output: void
 disegna sullo standard output la situazione del gioco
 */
void disegnaConfigurazione(configurazione c);


/*
 Autore: Marco Lucio
 Input: configurazione c
 è l'insieme dei dati che descrive la situazione attuale nel gioco
 non viene modificata dalla funzione
 supponiamo che i valori siano consistenti quindi non si fanno controlli
 Dipendenze da altre funzioni: nessuna
 Output: bool
 vero se la configurazione è vincente (tutti i personaggi sulla riva sx) e falso altrimenti
 */
bool controllaVittoria(configurazione c);

/*
 Autore: Marco Lucio
 Input: configurazione c
 è l'insieme dei dati che descrive la situazione attuale nel gioco
 non viene modificata dalla funzione
 supponiamo che i valori siano consistenti quindi non si fanno controlli
 Dipendenze da altre funzioni: nessuna
 Output: bool
 vero se la configurazione è perdente (sulla stessa riva più cannibali che missionari) e falso altrimenti
 */
bool controllaSconfitta(configurazione c);

/*
 Autore: Lorenzo
 Input: configurazione& c
 è l'insieme dei dati che descrive la situazione attuale nel gioco
 viene modificata dalla funzione
 supponiamo che c non abbia valori preimpostati
 Dipendenze da altre funzioni: nessuna
 Output: void
 scrive nei campi del record c i valori per la configurazione inziale
 */
void inizializza(configurazione& c);

/*
 Autore: Niccolo'
 Input: mossa& m
 è l'insieme dei dati che descrive l'ultima mossa decisa dall'utente
 supponiamo che n non abbia valori preimpostati.
 Si fanno controlli sulla coerenza delle mosse dell'utente
 Dipendenze da altre funzioni: nessuna
 Output: void
 scrive nei campi del record m i valori per la mossa corrente
 */
void interazioneUtente(mossa& m, configurazione c);

/*
 Autore: Tiziano
 Input: configurazione c
 è l'insieme dei dati che descrive la configurazione attuale
 supponiamo che c abbia valori valori coerenti e completi
 Dipendenze da altre funzioni: nessuna
 Output: void
 scrive a video un messaggio per l'utente che lo informa se ha vinto o perso
 Da decidere: "pulisce" lo schermo prima di stampare il messaggio?
 */
void messaggioFinale(configurazione c);

/*
 Autore: Lorenzo
 Input: configurazione c
 è l'insieme dei dati che descrive la configurazione attuale
 supponiamo che c abbia valori valori coerenti e completi
    mossa m
 contiene la scelta di personaggio e mossa dell'utente
 assumiamo la coerenza dei valori scritti nella mossa, quindi non bisogna fare i controlli dovuti
 Dipendenze da altre funzioni: nessuna
 Output: void
 modifica la configurazione c secondo quanto dettato dalla mossa m
 */
void eseguiAzione(mossa m, configurazione& c);



#endif /* utilities_h */
