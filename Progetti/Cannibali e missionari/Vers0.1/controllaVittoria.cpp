#include "utilities.h"

bool controllaVittoria(configurazione c)
{
	if ((c.cannibali_sx == 3) && (c.missionari_sx == 3)) {
		return true;
	}
	else {
		return false;
	}
}
