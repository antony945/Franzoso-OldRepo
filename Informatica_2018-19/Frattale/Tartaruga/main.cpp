// PROVA 1

#include<tarta_CodeBlocks13.h>

int n=5;
int P=0;

void Frattale(Tartaruga & T, float L, float x, float y){   // disegna un poligono di N lati
    for(int i=0; i<4; i++){
        T.Salta(x+L/3*i, y);
        T.VaiAvanti(L);
    }
    T.GiraDestra(90);
    for(int i=0; i<4; i++){
        T.Salta(x, y+L/3*i);
        T.VaiAvanti(L);
    }
    T.GiraSinistra(90);
}

void RipetizioneFrattali(Tartaruga & T, float L, float x, float y){
    switch(P){
    case 0:
        x = x; //-150
        y = y; //-150
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    case 1:
        x = x+L; //-50
        y = y;   //-150
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    case 2:
        x = x+L; //
        y = y;
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    case 3:
        x = x-2*L;
        y = y+L;
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    case 4:
        x = x+L;
        y = y;
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    case 5:
        x = x+L;
        y = y;
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    case 6:
        x = x-2*L;
        y = y+L;
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    case 7:
        x = x+L;
        y = y;
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    case 8:
        x = x+2*L;
        y = y;
        cout << "x e': "<< x << endl;
        cout << "y e': "<< y << endl << endl;
        P++;
        Frattale(T, L, x, y);
    }

    if(n!=0){
        P=0;
        RipetizioneFrattali(T, L/3, x, y);
    }
}

int main(){
    Tartaruga T; // creazione dell'oggetto di tipo tartaruga
    T.PulisciSchermo(Nero);
    T.Velocita(600);
    Frattale(T, 300, -150, -150); // disegna ettagono con il lato lungo 100
    RipetizioneFrattali(T, 100, -150, -150);
    system("PAUSE");
    return 0;
}

