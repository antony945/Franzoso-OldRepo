
#include "function.h"
#include "Variables.h"

void AggiornaCasella(int index, bool turno) {

	if (turno == false) {
		DisegnaCroce(index,height,width);
		Caselle[index] = Croce;
	}
	else
	{
		DisegnaCerchio(index, height, width);
		Caselle[index] = Cerchio;
	}

}