#include "utilities.h"
#include <iostream>

void messaggioFinale(configurazione c)
{
	if ((c.cannibali_sx == 3) && (c.missionari_sx == 3)) {
		std::cout << "HAI VINTO!!! Hai trasportato tutti i personaggi sulla sponda sinistra." << std::endl;
		//se il giocatore ha vinto viene visualizzato questo messaggio
	}
	// da qui in poi vengono esaminate le varie possibilità di sconfitta
    else if (c.lato_barca == 'd') {
		if (((c.cannibali_barca + c.cannibali_dx) > (c.missionari_barca + c.missionari_dx)) && ((c.missionari_barca + c.missionari_dx) != 0)) {
			std::cout << "Hai perso!" << std::endl;
		}
		else if ((c.cannibali_sx > c.missionari_sx) && (c.missionari_sx != 0)) {
			std::cout << "Hai perso!" << std::endl;
		}
	}
	else {
		if (((c.cannibali_barca + c.cannibali_sx) > (c.missionari_barca + c.missionari_sx)) && ((c.missionari_barca + c.missionari_sx) != 0)) {
			std::cout << "Hai perso!" << std::endl;
		}
		else if ((c.cannibali_dx > c.missionari_dx) && (c.missionari_dx != 0)) {
			std::cout << "Hai perso!" << std::endl;
		}
	}
}
