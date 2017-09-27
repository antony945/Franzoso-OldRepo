#include <iostream>
using namespace std;

class Rettangolo{
public:
    unsigned int base;
    unsigned int altezza;
public:
    unsigned int area();
    unsigned int perimetro();
};

int main(){
    Rettangolo rettangolo1;
    Rettangolo rettangolo2;

    rettangolo1.base = 5;
    rettangolo1.altezza = 2;
    rettangolo2.base = 30;
    rettangolo2.altezza = 6;

    rettangolo1.area();
    rettangolo1.perimetro();
    rettangolo2.area();
    rettangolo2.perimetro();

    return 0;
}

unsigned int Rettangolo::area(){
    unsigned int a = base*altezza;
    cout << "Valore area: " << a << endl;
    return a;
}

unsigned int Rettangolo::perimetro(){
    unsigned int p = (base+altezza)*2;
    cout << "Valore perimetro: " << p << endl;
    return p;
}
