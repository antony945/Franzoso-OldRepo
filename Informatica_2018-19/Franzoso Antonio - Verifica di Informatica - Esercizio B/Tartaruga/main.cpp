// ES 2

#include<tarta_CodeBlocks13.h>

void Sole(Tartaruga & T, float R, float x, float y){   // disegna un poligono di N lati
    T.Salta(x,y);
    T.CambiaColorePennello(RossoChiaro);
    T.Cerchio(R);
    //ottagono
    T.CambiaColorePennello(Azzurro);
    T.AlzaPennello();
    for(int i=0;i<8;i++){
        T.VaiAvanti(R+20);
        T.Cerchio(R/10);
        T.VaiIndietro(R+20);
        T.GiraDestra(45);
    }

    T.Tana();
}

void Esagono(Tartaruga & T, float R, float x, float y){   // disegna un poligono di N lati
    T.Salta(x,y);
    T.CambiaColorePennello(RossoChiaro);
    T.Cerchio(R);
    //esagono
    T.CambiaColorePennello(Azzurro);
    T.AlzaPennello();
    for(int i=0;i<6;i++){
        T.VaiAvanti(R+50);
        T.Cerchio(R+5);
        T.VaiIndietro(R+50);
        T.GiraDestra(60);
    }
}

int main(){
    Tartaruga T; // creazione dell'oggetto di tipo tartaruga
    T.PulisciSchermo(Nero);
    Sole(T,30,150,150); // disegna sole di raggio 30
    Esagono(T,30,-100,-100);
    system("PAUSE");
    return 0;
}
