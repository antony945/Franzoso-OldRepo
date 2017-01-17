#include <iostream>
#include "utilities.h"

using namespace std;

void richiestaPartenza(mossa& m, configurazione c, char elemento_scelto); //Funzione che richiede il luogo in cui si trova l'elemento che l'utente vuole spostare, e controlla se è coerente con gli altri dati.
void richiestaArrivo(mossa& m, configurazione c, char elemento_scelto, char partenza_scelta); //Funzione che richiede il luogo in cui l'utente vuole spostare l'elemento scelto, e controlla se è coerente con gli altri dati.

void interazioneUtente(mossa& m, configurazione c)
{
  char elemento_scelto; //Variabile che contiene l'elemento che l'utente vuole spostare.
  cout << "\nScegliere l'elemento da spostare (m = missionario, c = cannibale, b = barca): ";
  cin >> elemento_scelto;
  //Se l'elemento scelto è la barca, la funzione controlla se questa ha almeno un personaggio per potersi muovere, e assegna subito i dati alla struct mossa:
  if(elemento_scelto == 'b'){
    if(c.cannibali_barca + c.missionari_barca > 0){
      m.elemento = 'b';
      m.partenza = c.lato_barca; //Il punto di partenza deve essere il lato in cui sta la barca.
      c.lato_barca == 's'? m.arrivo = 'd' : m.arrivo = 's'; //Se la barca è a destra dovrà essere spostata a sinistra, e viceversa.
    }
    else{
      cout << "\nDeve esserci almeno un personaggio sulla barca per poterla muovere. Riprovare.\n";
      interazioneUtente(m, c);
    }
  }
  else{
    //Se l'input dell'utente ha un significato, cioè è uguale a 'm', 'c' o 'b', viene richiamata la funzione richiestaPartenza, se no la funzione chiede all'utente di riprovare e si riavvia.
    if(elemento_scelto == 'm' || elemento_scelto == 'c'){
      richiestaPartenza(m, c, elemento_scelto);
    }
    else{
      cout << "\nL'elemento inserito non è valido. Riprovare.\n";
      interazioneUtente(m, c);
    }
  }
}

void richiestaPartenza(mossa& m, configurazione c, char elemento_scelto)
{
  char partenza_scelta; //Variabile che contiene luogo in cui si trova l'elemento scelto dall'utente.
  cout << "\nScegliere il luogo in cui si trova l'elemento da spostare (d = sponda destra, s = sponda sinistra, b = barca): ";
  cin >> partenza_scelta;
  //Viene controllato se l'input dell'utente ha un significato, cioè è uguale a 'd', 's' o 'b':
  if(partenza_scelta == 'd' || partenza_scelta == 's' || partenza_scelta == 'b'){
    //Per ogni caso possibile, se l'elemento scelto esiste nel punto di partenza scelto viene richiamata la funzione richiestaArrivo, se no la funzione chiede all'utente di riprovare e si riavvia.
    if(elemento_scelto == 'm'){
      switch (partenza_scelta){
        case ('d'):
        if(c.missionari_dx > 0){
          richiestaArrivo(m, c, elemento_scelto, partenza_scelta);
        }
        else{
          cout << "\nNon ci sono missionari nella sponda destra. Riprovare.\n";
          interazioneUtente(m, c);
        }
        break;
        case ('s'):
        if(c.missionari_sx > 0){
          richiestaArrivo(m, c, elemento_scelto, partenza_scelta);
        }
        else{
          cout << "\nNon ci sono missionari nella sponda sinistra. Riprovare.\n";
          interazioneUtente(m, c);
        }
        break;
        case ('b'):
        if(c.missionari_barca > 0){
          richiestaArrivo(m, c, elemento_scelto, partenza_scelta);
        }
        else{
          cout << "\nNon ci sono missionari nella barca. Riprovare.\n";
          interazioneUtente(m, c);
        }
      }
    }
    else{
      switch (partenza_scelta){
        case ('d'):
        if(c.cannibali_dx > 0){
          richiestaArrivo(m, c, elemento_scelto, partenza_scelta);
        }
        else{
          cout << "\nNon ci sono cannibali nella sponda destra. Riprovare.\n";
          interazioneUtente(m, c);
        }
        break;
        case ('s'):
        if(c.cannibali_sx > 0){
          richiestaArrivo(m, c, elemento_scelto, partenza_scelta);
        }
        else{
          cout << "\nNon ci sono cannibali nella sponda sinistra. Riprovare.\n";
          interazioneUtente(m, c);
        }
        break;
        case ('b'):
        if(c.cannibali_barca > 0){
          richiestaArrivo(m, c, elemento_scelto, partenza_scelta);
        }
        else{
          cout << "\nNon ci sono cannibali nella barca. Riprovare.\n";
          interazioneUtente(m, c);
        }
      }
    }
  }
  else{
    cout << "\nIl luogo inserito non è valido. Riprovare.\n";
    interazioneUtente(m, c);
  }
}

void richiestaArrivo(mossa& m, configurazione c, char elemento_scelto, char partenza_scelta)
{
  char arrivo_scelto; //Variabile che contiene il luogo in cui l'utente vuole spostare l'elemento scelto.
  cout << "\nScegliere il luogo in cui spostare l'elemento (d = sponda destra, s = sponda sinistra, b = barca): ";
  cin >> arrivo_scelto;
  //Viene controllato se l'arrivo scelto ha un significato, cioè è uguale a 'd', 's' o 'b'. Se non lo è la funzione chiede all'utente di riprovare e si riavvia.
  if(arrivo_scelto == 'd' || arrivo_scelto == 's' || arrivo_scelto == 'b'){
    //Viene controllato se il luogo di arrivo è uguale a quello della partenza. Se si la funzione chiede all'utente di riprovare e si riavvia.
    if(arrivo_scelto != partenza_scelta){
      //Viene controllato se l'elemento scelto può essere spostato nella destinazione scelta. Se non è così la funzione chiede all'utente di riprovare e si riavvia.
      if((partenza_scelta == 'b' && arrivo_scelto == c.lato_barca) || (partenza_scelta != 'b' && arrivo_scelto == 'b')){
        //Nel caso l'arrivo scelto sia la barca, viene controllato se c'è almeno un posto libero. Se si vengono assegnati i dati allo struct mossa, se no la funzione chiede all'utente di riprovare e si riavvia.
        //Ovviamente nel caso l'arrrivo scelto non sia la barca vengono assegnati direttamente i dati allo struct mossa.
        if((arrivo_scelto == 'b' && c.cannibali_barca + c.missionari_barca < 2) || arrivo_scelto != 'b'){
          m.elemento = elemento_scelto;
          m.partenza = partenza_scelta;
          m.arrivo = arrivo_scelto;
        }
        else{
          cout << "\nLa barca può portare al massimo 2 personaggi. Riprovare.\n";
          interazioneUtente(m, c);
        }
      }
      else{
        cout << "\nL'elemento scelto non può essere spostato in quel luogo. Riprovare.\n";
        interazioneUtente(m, c);
      }
    }
    else{
      cout << "\nIl luogo d'arrivo dev'essere diverso da quello di partenza. Riprovare.\n";
      interazioneUtente(m, c);
    }
  }
  else{
    cout << "\nIl luogo inserito non è valido. Riprovare.\n";
    interazioneUtente(m, c);
  }
}
