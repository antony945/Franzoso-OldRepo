
 // PROVA 1

#include<tarta_CodeBlocks13.h>

void SpiraleCrescente(Tartaruga & T, float L) {
     if (L<500) {                   // se il lato non supera il valore 500
       T.Avanti(L);
       T.Destra(12);
       SpiraleCrescente(T, L*1.02); // chiamata ricorsiva
     }
     }

void Poligono(Tartaruga & T, float L, int Nlati)   // disegna un poligono di N lati
     {
         for(int i=0; i<Nlati; i++) {T.Avanti(L); T.Destra(360.0/Nlati);}
     }

int main() {
     Tartaruga T; // creazione dell'oggetto di tipo tartaruga
     SpiraleCrescente(T,10); // disegno di una spirale ricorsiva
     T.PulisciSchermo(Rosso);
     Poligono(T,100,7); // disegna ettagono con il lato lungo 100
     return 0;
}
