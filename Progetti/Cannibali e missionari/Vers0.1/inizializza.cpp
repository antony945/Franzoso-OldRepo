#include "utilities.h"

void inizializza (configurazione& c)
{
	c.cannibali_barca=0; //inizializzazione del numero dei cannibali all'interno della barca, 0 per iniziare
	c.cannibali_dx=3; //inizializzazione del numero dei cannibali sull'isola di destra, 3 per iniziare
	c.cannibali_sx=0; //inizializzazione del numero dei cannibali sull'isola sinistra, 0 per iniziare
	c.lato_barca='d'; //inizializzazione del lato della barca, destra per iniziare
	c.missionari_barca=0; //inizializzazione del numero dei missionari all'interno della barca, 0 per iniziare
	c.missionari_dx=3; //inizializzazione del numero dei missionari sull'isola di destra, 3 per iniziare
	c.missionari_sx=0; //inizializzazione del numero dei cannibali sull'isola di sinistra, 0 per iniziare
}

