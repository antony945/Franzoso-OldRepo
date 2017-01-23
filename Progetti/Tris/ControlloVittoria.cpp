#include "function.h"
#include "Variables.h"

bool ControlloVittoria()
{
	// Controlla se si ha vinto esaminando tutti i casi possibili per fare tris.  Se si ha vinto restituisce il valore vero, altrimenti il valore falso
	if ((Caselle[0] == Caselle[1]) && (Caselle[0] == Caselle[2]) && (Caselle[0] != Vuota))  {
		return true;
	}
	else if ((Caselle[3] == Caselle[4]) && (Caselle[3] == Caselle[5]) && (Caselle[3] != Vuota)) {
		return true;
	}
	else if ((Caselle[6] == Caselle[7]) && (Caselle[6] == Caselle[8]) && (Caselle[6] != Vuota)) {
		return true;
	}
	else if ((Caselle[0] == Caselle[3]) && (Caselle[0] == Caselle[6]) && (Caselle[0] != Vuota)) {
		return true;
	}
	else if ((Caselle[1] == Caselle[4]) && (Caselle[1] == Caselle[7]) && (Caselle[1] != Vuota)) {
		return true;
	}
	else if ((Caselle[2] == Caselle[5]) && (Caselle[2] == Caselle[8]) && (Caselle[2] != Vuota)) {
		return true;
	}
	else if ((Caselle[0] == Caselle[4]) && (Caselle[0] == Caselle[8]) && (Caselle[0] != Vuota)) {
		return true;
	}
	else if ((Caselle[2] == Caselle[4]) && (Caselle[2] == Caselle[6]) && (Caselle[2] != Vuota)) {
		return true;
	}
	else {
		return false;
	}
}

