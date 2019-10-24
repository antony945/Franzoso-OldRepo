// PROVA 1

#include<tarta_CodeBlocks13.h>

void ScriviNome(Tartaruga & T, float L, float x, float y){   // disegna un poligono di N lati
    int ang0=90;
    // A
    int ang1_A=20;
    int ang2_A=140;
    int lat1_A=L/sin(ang1_A);
    int lat2_A=2*lat1_A/5;
    T.Salta(x,y);
    T.GiraDestra(ang1_A);
    T.VaiAvanti(lat1_A);
    T.GiraDestra(ang2_A);
    T.VaiAvanti(lat1_A);
    T.Salta(x,y);
    T.Direzione(ang0);
    T.GiraDestra(ang1_A);
    T.VaiAvanti(lat2_A);
    T.GiraDestra(ang0-ang1_A);
    T.VaiAvanti(lat2_A);
    x+=lat1_A;

    T.Salta(x,y);
    T.Direzione(ang0);

    //N
    int ang1_N=135;
    int lat1_N=L;
    int lat2_N=L/sin(ang1_N);
    T.VaiAvanti(lat1_N); //per trovare la giusta lunghezza verticolare
    T.GiraDestra(ang1_N);
    T.VaiAvanti(lat2_N);
    T.GiraSinistra(ang1_N);
    T.VaiAvanti(lat1_N);
}

int main(){
    Tartaruga T; // creazione dell'oggetto di tipo tartaruga
    T.PulisciSchermo(Rosso);
    ScriviNome(T,100,-250,0); // disegna ettagono con il lato lungo 100
    system("PAUSE");
    return 0;
}
