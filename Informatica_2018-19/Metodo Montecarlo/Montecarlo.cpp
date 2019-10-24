#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>
#include <time.h>

using namespace std;

class Punto{
private:
    double x,y,raggio;
    double contatoreQuadrato=0, contatoreCerchio=0;
    void randomizzaPunto();
public:
    void contaPunti();
    double calcoloPigreco();
};

void Punto::randomizzaPunto(){
    x = rand()%201;
    y = rand()%201;

    raggio = 100;
}

void Punto::contaPunti(){
    int MAX=10000000; //Numero di iterazioni del ciclo

    srand(time(NULL));//inizializza i valori
    for(int i=0;i<MAX;i++){
        randomizzaPunto();
        //CONTA PUNTI QUADRATO
        if(x >=0 && x <=(2*raggio) && y>=0 && y <=(2*raggio)){
            contatoreQuadrato++;
        }

        //CONTA PUNTI CERCHIO
        if(sqrt(((x-raggio)*(x-raggio)+(y-raggio)*(y-raggio)))<=raggio){
            contatoreCerchio++;
        }
    }
}

double Punto::calcoloPigreco(){
    double Pi=0;
    cout << "I punti finali nel cerchio sono: " << contatoreCerchio << endl;
    cout << "I punti finali nel quadrato sono: " << contatoreQuadrato << endl;
    Pi=(contatoreCerchio/contatoreQuadrato)*4;
    return Pi;
}

int main(){
    Punto A;

    A.contaPunti();

    cout << endl << endl << "Il Pigreco e': " << A.calcoloPigreco();

    return 0;
}

