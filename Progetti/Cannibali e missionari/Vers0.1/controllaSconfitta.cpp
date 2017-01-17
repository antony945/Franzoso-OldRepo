#include "utilities.h"

bool controllaSconfitta(configurazione c)
{
	if (c.lato_barca == 'd') {
		if ((((c.cannibali_barca + c.cannibali_dx) > (c.missionari_barca + c.missionari_dx)) && ((c.missionari_barca + c.missionari_dx) != 0)) || ((c.cannibali_sx > c.missionari_sx) && (c.missionari_sx != 0))) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if ((((c.cannibali_barca + c.cannibali_sx) > (c.missionari_barca + c.missionari_sx)) && ((c.missionari_barca + c.missionari_sx) != 0)) || ((c.cannibali_dx > c.missionari_dx) && (c.missionari_dx != 0))) {
			return true;
		}
		else {
			return false;
		}
	}
   
}