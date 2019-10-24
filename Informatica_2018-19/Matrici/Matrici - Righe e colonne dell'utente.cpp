#include <iostream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

/*
void somma(int tab1[][], int tab2[][]){
    //SOMMA
    system("PAUSE");
    system("CLS");

    int somma[righe][colonne];

    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
            somma[r][c] = tab1[r][c]+tab2[r][c];
        }
    }
    cout << endl;
    cout << "Somma tra tab1 e tab2" << endl;
    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
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

    int differenza[righe][colonne];

    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
            differenza[r][c] = tab1[r][c]-tab2[r][c];
        }
    }
    cout << endl;
    cout << "Differenza tra tab1 e tab2" << endl;
    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
            cout << differenza[r][c] << " ";
        }

        cout << endl;
    }
    cout << endl;
}
*/

int main(){
    int righe;
    cout << "Inserisci n. righe: ";
    cin >> righe;
    int colonne;
    cout << "Inserisci n. colonne: ";
    cin >> colonne;

    system("CLS");

    int tab1[righe][colonne];
    int tab2[righe][colonne];
    int valore;

    //TABELLA 1
    /*Inserimento tabella 1*/
    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
            cout << "Inserisci tab1[" << r << "][" << c << "]: ";
            cin >> valore;
            tab1[r][c] = valore;
        }
    }
    cout << endl;

    /*Lettura tabella 1*/
    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
            cout << tab1[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //TABELLA colonne
    /*Inserimento tabella colonne*/
    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
            cout << "Inserisci tab2[" << r << "][" << c << "]: ";
            cin >> valore;
            tab2[r][c] = valore;
        }
    }
    cout << endl;

    /*Lettura tabella colonne*/
    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
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

    int somma[righe][colonne];

    cout << endl;
    cout << "Somma tra tab1 e tab2" << endl;

    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
            somma[r][c] = tab1[r][c]+tab2[r][c];
            cout << somma[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //DIFFERENZA
    system("PAUSE");
    system("CLS");

    int differenza[righe][colonne];

    cout << endl;
    cout << "Differenza tra tab1 e tab2" << endl;

    for(int r=0;r<righe;r++){
        for(int c=0;c<colonne;c++){
            differenza[r][c] = tab1[r][c]-tab2[r][c];
            cout << differenza[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;

    //TRASPOSTA
    system("PAUSE");
    system("CLS");

    int trasposta[colonne][righe];

    cout << endl;
    cout << "Trasposta di tab1" << endl;

    for(int r=0;r<colonne;r++){
        for(int c=0;c<righe;c++){
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
