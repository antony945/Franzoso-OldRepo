#include "../include/radice.h"
#include <cmath>

Reale proceduraMisteriosa(Reale x, Reale y){
    if(x!=y)//in realtà non dovrebbero essere mai uguali ma il computer non se ne accorge. La condizione corretta sarebbe fabs(x-y) < 1E-<numero grande>
        return proceduraMisteriosa(((2*x*y)/(x+y)), ((x+y)/2));
    else
        return x;
}

Reale radq(Reale radicando){
    return proceduraMisteriosa(1.0, radicando);
}
