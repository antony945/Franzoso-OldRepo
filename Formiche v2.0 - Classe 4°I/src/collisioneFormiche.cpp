#include "../include/formica.h"
#include <SDL.h>
#include <stdlib.h>
#include <math.h>

class Segmento{ //distanza tra centri come variabile di tipo Segmento
    int modulo;
    SDL_Point inizio, fine;

public:
    Segmento(SDL_Point inizio, SDL_Point fine):inizio(inizio), fine(fine){
        int x_axis = pow(2, (fine.x-inizio.x));
        int y_axis = pow(2, (fine.y-inizio.y));
        modulo = sqrt(x_axis+y_axis);
    }

    int getModulo(){
        return modulo;
    }
};

bool collisioneFormiche(SDL_Point C1, SDL_Point C2, int R1, int R2){
    Segmento distanza(C1,C2);
    int sommaRaggi = R1+R2;
    int differenzaRaggi = abs(R1-R2);
    int distanzaCentri = distanza.getModulo();

    bool collisione = ((distanzaCentri<sommaRaggi) && (distanzaCentri>differenzaRaggi));

    return collisione;
}
