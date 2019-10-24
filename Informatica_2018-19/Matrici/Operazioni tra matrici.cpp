#include <iostream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

/*
void somma(int tab1[][], int tab2[][]){
    //SOMMA
    system("PAUSE");
    system("CLS");

    int somma[4][2];

    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            somma[r][c] = tab1[r][c]+tab2[r][c];
        }
    }
    cout << endl;
    cout << "Somma tra tab1 e tab2" << endl;
    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            cout << somma[r][c] << " ";
        }

        cout << endl;
    }
    cout << endl;
}

void differenza(int tab1[][], int tab2[][]){
    //DIFFERENZA
    system("PAUSE");
    system("CLS");

    int differenza[4][2];

    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            differenza[r][c] = tab1[r][c]-tab2[r][c];
        }
    }
    cout << endl;
    cout << "Differenza tra tab1 e tab2" << endl;
    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            cout << differenza[r][c] << " ";
        }

        cout << endl;
    }
    cout << endl;
}
*/

int main(){
    int righe;
    cout << "Inserisci righe: ";
    cin >> righe;
    int colonne;
    cout << "Inserisci colonne:";
    cin >> colonne;




    int tab1[4][2];
    int tab2[4][2];
    int valore;

    //TABELLA 1
    /*Inserimento tabella 1*/
    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            cout << "Inserisci tab1[" << r << "][" << c << "]: ";
            cin >> valore;
            tab1[r][c] = valore;
        }
    }
    cout << endl;

    /*Lettura tabella 1*/
    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            cout << tab1[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //TABELLA 2
    /*Inserimento tabella 2*/
    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            cout << "Inserisci tab2[" << r << "][" << c << "]: ";
            cin >> valore;
            tab2[r][c] = valore;
        }
    }
    cout << endl;

    /*Lettura tabella 2*/
    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            cout << tab2[r][c] << " ";
        }
        cout << endl;
    }

    cout << endl;

    /*
    somma(tab1, tab2);
    differenza(tab1, tab2);
    */

    //SOMMA
    system("PAUSE");
    system("CLS");

    int somma[4][2];

    cout << endl;
    cout << "Somma tra tab1 e tab2" << endl;

    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            somma[r][c] = tab1[r][c]+tab2[r][c];
            cout << somma[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //DIFFERENZA
    system("PAUSE");
    system("CLS");

    int differenza[4][2];

    cout << endl;
    cout << "Differenza tra tab1 e tab2" << endl;

    for(int r=0;r<4;r++){
        for(int c=0;c<2;c++){
            differenza[r][c] = tab1[r][c]-tab2[r][c];
            cout << differenza[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //TRASPOSTA
    system("PAUSE");
    system("CLS");

    int trasposta[2][4];

    cout << endl;
    cout << "Trasposta di tab1" << endl;

    for(int r=0;r<2;r++){
        for(int c=0;c<4;c++){
            trasposta[r][c] = tab1[c][r];
            cout << trasposta[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //FINE
    cout << endl;
    system("PAUSE");
    return 0;
};
