#include <iostream>
#include <string>
#include <cmath>
#include <windows.h>

using namespace std;

double f(double variabile){
    return pow(2.7182818284, (-variabile/2));
}

double integrale_1(double a, double b, double l){
    double area_1 = 0;

    for(double altezza=a+l; altezza<=b; altezza+=l){
        area_1+=l*f(altezza);
    }

    return area_1;
}

double integrale_2(double a, double b, double l){
    double area_2 = 0;

    for(double altezza=a; altezza<b; altezza+=l){
        area_2+=l*f(altezza);
    }

    return area_2;
}

int main(){
    double a, b;

    cout << "Calcolo integrale della funzione: e^-x/2 da 'a' a 'b'" << endl;
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;

    double l=(b-a)/1E+06;

    cout << endl;

    if(integrale_1(0,1,l)<integrale_2(0,1,l)){
        cout << integrale_1(0,1,l) << " < integrale < " << integrale_2(0,1,l);
    }else if(integrale_1(0,1,l)>integrale_2(0,1,l)){
        cout << integrale_2(0,1,l) << " < integrale < " << integrale_1(0,1,l);
    }

    cout << endl << endl;
    system("PAUSE");
    return 0;
}

