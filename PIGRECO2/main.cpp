#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <quadmath.h>
#include <iomanip>

using namespace std;

#define Reale __float128
#define ERR_MAX 1E-32Q

char* cifreStampate(Reale num, int n_cifre){
    int n = quadmath_snprintf(NULL, 0, "%+-#46.*Qe", n_cifre, num);
    if(n>-1){
        char* str = (char*)malloc(n+1);
        if(str){
            quadmath_snprintf(str, n+1, "%+-#46.*Qe", n_cifre, num);
            return str;
        }else{
            return "quadmath_snprintf non riuscita";
        }
    }else{
        return "quadmath_snprintf non riuscita";
    }
}

bool uguali(Reale x, Reale y){
    bool uguali = false;

    if(fabsq(x-y) < ERR_MAX)
        uguali = true;

    return uguali;
}

Reale proceduraMisteriosa(Reale x, Reale y){
    if(uguali(x,y))
        return x;
    else
        return proceduraMisteriosa(2.0Q*x*y/(x+y), (x+y)/2.0Q);
}

Reale radq(Reale radicando){
    return proceduraMisteriosa(1.0Q, radicando);

}


//-----------------------------------------------

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

    i.apotema = radq((1.0Q*1.0Q)-((i.lato/2.0Q)*(i.lato/2.0Q)));

    i.perimetro = i.lato*i.n;
    i.pigreco_vecchio = i.pigreco_nuovo;
    i.pigreco_nuovo = i.perimetro/2.0Q;

    i.differenza = 1.0Q-i.apotema;
    i.lato = radq(((i.lato/2.0Q)*(i.lato/2.0Q))+(i.differenza*i.differenza));

    i.errore = fabsq(i.pigreco_vecchio-i.pigreco_nuovo);

    cout << "Il pigreco e': " << cifreStampate(i.pigreco_nuovo, 31) << endl;

    if(i.lato/i.n < ERR_MAX)
        return i.pigreco_nuovo;
    else
        return metodoArchimede(i, 2.0Q*i.n);
}

int main(){
    const int LIMITE_CIFRE = 31;

    Poligono inscritto = {6,1.0,0.0,0.0,0.0,0.0,0.0,0.0};

    Reale pigreco = metodoArchimede(inscritto, inscritto.n);

    return 0;
}
