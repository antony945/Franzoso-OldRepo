//FILE VERSIONE 2

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <quadmath.h>
#include <iomanip>
#include <quadmath.h>

using namespace std;

/* DIRETTIVE AL PREPROCESSORE */
#define LONGDOUBLE
#if defined(FLOAT128)
    typedef __float128 Reale;
    #define ERR_MAX 1E-34Q
    #define LIMITE_CIFRE 18
#elif defined(LONGDOUBLE)
    typedef long double Reale;
    #define ERR_MAX 1E-19L
    #define LIMITE_CIFRE 18
#endif

/* STRUCT POLIGONO */
typedef struct Poligono{
    int n;
    Reale lato;
    Reale apotema;
    Reale differenza;
    Reale perimetro;
    Reale pigreco_vecchio;
    Reale pigreco_nuovo;
    Reale errore_vecchio;
    Reale errore_nuovo;
}Poligono;

/* PROTOTIPI FUNZIONI */
char* stampaNumero(Reale, int);
bool uguali(Reale, Reale);
Reale proceduraMisteriosa(Reale, Reale);
Reale radq(Reale);
Reale metodoArchimede(Poligono&, int);

int main(){
    Poligono inscritto = {6,1,0,0,0,0,0,0};
    Reale pigreco = metodoArchimede(inscritto, inscritto.n);

    cout << "-*-*-*-*-*-*-*-*-*-*-| PIGRECO - METODO DI ARCHIMEDE |-*-*-*-*-*-*-*-*-*-*-" << endl << endl;
    cout << "Tipo utilizzato = ";
    #if defined(FLOAT128)
    cout << "'__float128'";
    #elif defined(LONGDOUBLE)
    cout << "'long double'";
    #endif

    cout << endl;
    cout << "Pigreco = ";

    #if defined(FLOAT128)
    cout << stampaNumero(pigreco, LIMITE_CIFRE);
    #elif defined(LONGDOUBLE)
    cout << setprecision(LIMITE_CIFRE) << scientific;
    cout << showpos << pigreco;
    #endif

    cout << endl;
    cout << "Errore  = ";

    #if defined(FLOAT128)
    cout << stampaNumero(inscritto.errore_vecchio, LIMITE_CIFRE);
    #elif defined(LONGDOUBLE)
    cout << setprecision(LIMITE_CIFRE) << scientific;
    cout << showpos << inscritto.errore_vecchio;
    #endif

    cout << endl << endl;

    cout << "---------------------------------------------------------------------------" << endl << endl;
    system("PAUSE");
    return 0;
}

#if defined(FLOAT128)
char* stampaNumero(Reale num, int n_cifre){
    int n = quadmath_snprintf(NULL, 0, "%+-#46.*Qe", n_cifre, num);
    if(n>-1){
        char* str = (char*)malloc(n+1);
        if(str){
            quadmath_snprintf(str, n+1, "%+-#46.*Qe", n_cifre, num);
            return str;
        }else{
            return "ERRORE! Impossibile stampare il numero __float128 dato.";
        }
    }else{
        return "ERRORE! Impossibile stampare il numero __float128 dato.";
    }
}
#endif

bool uguali(Reale x, Reale y){
    bool uguali = false;

    #if defined(FLOAT128)
        if(fabsq(x-y) < ERR_MAX)
            uguali = true;
    #elif defined(LONGDOUBLE)
        if(fabsl(x-y) < ERR_MAX)
            uguali = true;
    #endif

    return uguali;
}

Reale proceduraMisteriosa(Reale x, Reale y){
    if(uguali(x,y))
        return x;
    else
        #if defined(FLOAT128)
        return proceduraMisteriosa(2.0Q*x*y/(x+y), (x+y)/2.0Q);
        #elif defined(LONGDOUBLE)
        return proceduraMisteriosa(2.0L*x*y/(x+y), (x+y)/2.0L);
        #endif
}

Reale radq(Reale radicando){
    #if defined(FLOAT128)
    return proceduraMisteriosa(1.0Q, radicando);
    #elif defined(LONGDOUBLE)
    return proceduraMisteriosa(1.0L, radicando);
    #endif
}

Reale metodoArchimede(Poligono& poligono, int n_lati){
    poligono.n = n_lati;

    #if defined(FLOAT128)
        poligono.perimetro = poligono.lato*poligono.n;
        poligono.pigreco_vecchio = poligono.pigreco_nuovo;
        poligono.pigreco_nuovo = poligono.perimetro/2.0Q;
        poligono.errore_vecchio = poligono.errore_nuovo;
        poligono.errore_nuovo = fabsq(poligono.pigreco_vecchio-poligono.pigreco_nuovo);

        poligono.apotema = radq((1.0Q*1.0Q)-((poligono.lato/2.0Q)*(poligono.lato/2.0Q)));
        poligono.differenza = 1.0Q-poligono.apotema;
        poligono.lato = radq(((poligono.lato/2.0Q)*(poligono.lato/2.0Q))+(poligono.differenza*poligono.differenza));
        if((poligono.errore_nuovo>1)&&(poligono.n!=6))
            return poligono.pigreco_vecchio;
        else
            return metodoArchimede(poligono, 2.0Q*poligono.n);
    #elif defined(LONGDOUBLE)
        poligono.perimetro = poligono.lato*poligono.n;
        poligono.pigreco_vecchio = poligono.pigreco_nuovo;
        poligono.pigreco_nuovo = poligono.perimetro/2.0L;
        poligono.errore_vecchio = poligono.errore_nuovo;
        poligono.errore_nuovo = fabs(poligono.pigreco_vecchio-poligono.pigreco_nuovo);

        poligono.apotema = radq((1.0L*1.0L)-((poligono.lato/2.0L)*(poligono.lato/2.0L)));
        poligono.differenza = 1.0L-poligono.apotema;
        poligono.lato = radq(((poligono.lato/2.0L)*(poligono.lato/2.0L))+(poligono.differenza*poligono.differenza));

        if((poligono.errore_nuovo>1)&&(poligono.n!=6))
            return poligono.pigreco_vecchio;
        else
            return metodoArchimede(poligono, 2.0L*poligono.n);
    #endif
}
