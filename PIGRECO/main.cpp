#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include "include/radice.h" //libreria contenente funzione radice quadrata utilizzando procedura misteriosa

using namespace std;

typedef struct Poligono{
    int n;
    Reale lato;
    Reale apotema;
    Reale differenza;
    Reale perimetro;
    Reale pigreco_vecchio;
    Reale pigreco_nuovo;
    Reale errore;
}Poligono;

Reale metodoArchimede(Poligono i, int n_lati){
    i.n = n_lati;

    i.apotema = radq((1*1)-((i.lato/2)*(i.lato/2)));

    i.perimetro = i.lato*i.n;
    i.pigreco_vecchio = i.pigreco_nuovo;
    i.pigreco_nuovo = i.perimetro/2;

    i.differenza = 1-i.apotema;
    i.lato = radq(((i.lato/2)*(i.lato/2))+(i.differenza*i.differenza));

    i.errore = fabs(i.pigreco_nuovo-i.pigreco_vecchio);

    cout << setprecision(16) << fixed;
    cout << "Il pigreco e': " << i.pigreco_nuovo << endl;
    cout << "L'errore e':   " << i.errore << endl << endl;
    cout << "Il rapporto e':" << i.lato/i.n << endl << endl;

    if(i.lato/i.n < 1E-15)
        return i.pigreco_nuovo;
    else
        return metodoArchimede(i, 2*i.n);
}

int main(){
    Poligono inscritto = {6.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0};

    Reale pigreco = metodoArchimede(inscritto, inscritto.n);

    cout << setprecision(16) << fixed;
    cout << endl << endl << endl << "Il pigreco e': " << pigreco << endl << endl;

    return 0;
}
