#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <time.h>

using namespace std;

class Punto{
public:
    double x,y;
    void randomizzaPunto();
    void contaPunti();
};

void Punto::randomizzaPunto(){
    int contatorePunti=0;

    Punto.x = rand()%3;
    Punto.y = rand()%3;
}

void Punto::contaPunti(){
    int contatoreQuadrato=0;
    int contatoreCerchio=0;

    srand(time(NULL));//inizializza i valori
    for(int i=0, i<100, i++){
        randomizzaPunto();
        //CONTA PUNTI QUADRATO
        if(Punto.x >=0 && Punto.x <=2 && Punto.y>=0 && Punto.y <=2){
            contatoreQuadrato++;
        }
        //CONTA PUNTI CERCHIO
        if(Punto.x >=0 && Punto.x <=2 && Punto.y>=0 && Punto.y <=2){
            contatoreQuadrato++;
        }
    }

}

//PUNTI DENTRO IL QUADRATO. ASCISSA STA DA 0 a 2R. ORDINATA STA DA 0 A 2R
double contaQuadrato(double punto){
    if(punto)
    return pow(2.7182818284, (-(variabile*variabile)/2));
}


int main(){

    return 0;
}

