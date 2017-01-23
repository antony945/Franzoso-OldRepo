#include "function.h"
#include "Variables.h"

bool ControlloCasella(int index) {
	if(index >= 0) {
		if (Caselle[index] == Vuota) {
			return true;
		}
		else
		{
			return false;
		}
	}
	else {
		return false;
	}
}
