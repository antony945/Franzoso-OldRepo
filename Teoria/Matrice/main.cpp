#include <iostream>
#include <stdlib.h>
using namespace std;

const int NR=3, NC=3;     // Il numero di righe e il numero di colonne devono essere dichiarate costanti
void CaricaMatrice (int m[][NC]); // Prototipo che carica la matrice
void VisualizzaMatrice (int m[][NC]); //Protopico che visualizza la matrice
int main()
{
    int Matrice [NR][NC];
    CaricaMatrice( Matrice );  //richiama procedura passandole il parametro attuale
    VisualizzaMatrice( Matrice ); //richiama procedura passandole il parametro attuale
    system ("PAUSE");
    return 0;
}
void CaricaMatrice(int m[][NC]) {
  int i,j;
    for (i=0;i<NR;i++) {
        for (j=0;j<NC;j++) {
            cout<<"Inserire numero da caricare nella matrice nella posizione ["<<i+1<<";"<<j+1<<"]"<<endl;
            cin>>m[i][j];
        }
    }
}

void VisualizzaMatrice( int m[][NC]) {
    int i,j;
    for (i=0;i<NR;i++) {
            for (j=0;j<NC;j++) {
                cout<<"Ecco l'elemento caricato nella posizione ["<<i+1<<":"<<j+1<<"]"<<": "<<m[i][j]<<endl;
            }
    }
}
