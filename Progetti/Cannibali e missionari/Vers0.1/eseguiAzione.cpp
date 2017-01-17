#include "utilities.h"

void eseguiAzione(mossa m, configurazione &c)
{
	if (m.elemento == 'b') /*se l'elemento da spostare è la barca si esegue direttamente lo spostamento*/
	{
		c.lato_barca=='s'? c.lato_barca='d' : c.lato_barca='s'; //se la barca è a sinistra si sposta a destra e viceversa
	}


	if (m.elemento == 'm') //si prende in considerazione l'elemento m
	{
		if(m.arrivo=='b') //se l'arrivo è la barca si esegue lo spostamento dalla sponda alla barca
		{
			c.lato_barca=='s'? c.missionari_sx-- : c.missionari_dx--; //se il lato della barca è sinistra si toglie un missionario dalla riva sinistra e viceversa
			c.missionari_barca ++; //come conseguenza dello spostamento si ha sempre l'aumento dei missionari all'interno della barca
		}
		else //se l'arrivo non è la barca lo spostamento viene eseguito logicamente dalla barca verso la sponda su cui è ormeggiata
		{
			c.missionari_barca--; //come conseguenza dello spostamento si ha sempre la diminuzione dei missionari all'interno della barca
			c.lato_barca=='s'? c.missionari_sx++ : c.missionari_dx++; //se la barca è a sinistra si aggiunge un missionario a sinistra e viceversa
		}
	}


	if(m.elemento == 'c')
	{
		if(m.arrivo=='b') //se l'arrivo è la barca si esegue lo spostamento
		{
			c.lato_barca=='s'? c.cannibali_sx-- : c.cannibali_dx--; //se la barca si trova a sinistra si diminuisce il numero di cannibali a sinistra e viceversa
			c.cannibali_barca ++; //come conseguenza dello spostamento si ha sempre l'aumento dei cannibali all'interno della barca
		}
		else //se l'arrivo non è la barca lo spostamento viene eseguito logicamente dalla barca verso la sponda su cui è ormeggiata
		{
			c.cannibali_barca--; //come conseguenza dello spostamento si ha sempre la diminuzione dei cannibalii all'interno della barca
			c.lato_barca=='s'? c.cannibali_sx++ : c.cannibali_dx++; //se la barca si trova a sinistra si aumenta il numero di cannibali a sinistra e viceversa
		}
	}
}
