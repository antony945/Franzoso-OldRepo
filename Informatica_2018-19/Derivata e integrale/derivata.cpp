#include <iostream>
#include <windows.h>

using namespace std;

double derivataPrima(int variabile){
    double h;
    double f_pos, f_neg, derivata_1;

    if(variabile>=0){
        h = variabile*1E-08;
    }else if(variabile<0){
        h = -variabile*1E-08;
    }

    f_pos = (3*(variabile+h)*(variabile+h)+5*(variabile+h)-7);
    f_neg = (3*(variabile-h)*(variabile-h)+5*(variabile-h)-7);

    if(variabile==0){
        derivata_1 = 0;
    }else{
        derivata_1 = ((f_pos-f_neg)/(2*h));
    }

    return derivata_1;
}

double derivataSeconda(int variabile){
    double h;
    double f, f_pos, f_neg, derivata_2;

    if(variabile>=0){
        h = variabile*1E-04;
    }else if(variabile<0){
        h = -variabile*1E-04;
    }

    f = (3*(variabile)*(variabile)+5*(variabile)-7);
    f_pos = (3*(variabile+h)*(variabile+h)+5*(variabile+h)-7);
    f_neg = (3*(variabile-h)*(variabile-h)+5*(variabile-h)-7);

    if(variabile==0){
        derivata_2 = 0;
    }else{
        derivata_2 = ((f_pos-2*f+f_neg)/(h*h));
    }

    return derivata_2;
}

int main(){
    //3x^2+5x-7
    int x;
    cout << "Calcolo derivata prima e seconda della funzione: 3x^2 + 5x - 7" << endl << endl;
    cout << "Inserisci la variabile x per la quale vuoi derivare: ";
    cin >> x;

    cout << endl;
    cout << "La derivata prima nel punto x = " << x << " della funzione data  e': " << derivataPrima(x);
    cout << endl;
    cout << "La derivata seconda nel punto x = " << x << " della funzione data e': " << derivataSeconda(x);

    cout << endl;
    cout << endl;
    system("PAUSE");
    return 0;
};
