#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>

using namespace std;

double f(double variabile){
    return pow(2.7182818284, (-(variabile*variabile)/2));
}

double integrale(double a, double b, double l){
    double area = 0;

    for(double altezza=a; altezza<b; altezza+=l){
        area+=(f(altezza)+f(altezza+l))*l/2;
    }

    return area;
}

int main(){
    double a, b;

    cout << "Calcolo integrale della funzione: e^-x^2/2 da 'a' a 'b'" << endl;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;

    double l=(b-a)/1E+06;

    cout << endl;

    cout << "L'integrale e': " << integrale(a,b,l);

    cout << endl << endl;
    system("PAUSE");
    return 0;
}

