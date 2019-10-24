// PROVA 1

#include<tarta_CodeBlocks13.h>

void Striscia(Tartaruga & T, float L){   // disegna un poligono di N lati
    for(int i=0; i<8; i++){
        T.VaiAvanti(L);
        T.GiraDestra(45);
        T.VaiAvanti(50);
        T.VaiIndietro(50);
        T.GiraSinistra(90);
        T.VaiAvanti(50);
        T.VaiIndietro(50);
        T.GiraDestra(45);
        T.VaiIndietro(L);
        T.GiraDestra(45);
    }
}

int main(){
    Tartaruga T; // creazione dell'oggetto di tipo tartaruga
    T.PulisciSchermo(Rosso);
    Striscia(T,150); // disegna ettagono con il lato lungo 100
    system("PAUSE");
    return 0;
}
