#include "function.h"
#include "Variables.h"

bool ControlloPareggio()
{
  bool FinePartita = true;      //Varibile che indica se una partita è finita (cioè se tutte le caselle sono piene).
  for(i = 0; i < 9; i++) {      //Ciclo for che controlla se c'è almeno una casella vuota, e, in questo caso, imposta FinePartita a false.
    if(Caselle[i] == Vuota) {
      FinePartita = false;
    }
  }
  if(!ControlloVittoria() && FinePartita) {   //Se la partita è finita, e nessuno ha vinto, c'è un pareggio.
    return true;
  }
  else {
    return false;
  }
}
