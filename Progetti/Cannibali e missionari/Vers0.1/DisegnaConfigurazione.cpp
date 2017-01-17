#include <iostream>
#include <string>
#include "utilities.h"

void disegnaConfigurazione(configurazione c) {
	std::string riva_sx ="_____________"; //creazione della riva senza personaggi (riva: sinistra)
    std::string riva_dx = "_____________";//creazione della riva senza personaggi (riva: destra)
    int n = 1; //distacco tra "C" e "_" e "M" questa variabile deve mantenere il distacco ad un numero dispari
    for (int i = 0; i < c.cannibali_sx; i++) { //disegna cannibali di sinistra con parte dell' isola di sinistra
        riva_sx[i+n]='C';//scrive "C" (cannibali) al posto di "_" sulla stringa riva_sx ogni 2 "_" ("_" dispari)
        n++;//aumenta n distacco per mantenere la scrittura su "_" dispari
    }
    n += 3;//aumenta il distacco di 3 per mantenere la scrittura dei personaggi sugli "_" dispari
    for (int i = 0; i < c.missionari_sx; i++) { //disegna missionari di sinistra con parte dell' isola di sinistra
        riva_sx[i+n]='M';
        n++;
    }
    std::cout << riva_sx; //scrive la stringa (disegna riva di sinistra completa di personaggi)
    std::cout << "..";//crea uno spazio tra riva e barca/acqua

    switch (c.lato_barca) {  //controllo lato barca
    case('s'):  //caso : a sinistra

        std::cout << "|_" ;//disegna la perta sinistra della barca
        if (c.missionari_barca == 1 || c.missionari_barca == 2) {
            std::cout << "M";//disegna personaggi nella barca
        }
        if (c.missionari_barca == 2) {
            std::cout << "M";
        }
        if (c.cannibali_barca == 1 || c.cannibali_barca == 2) {
            std::cout << "C";
        }
        if (c.cannibali_barca == 2) {
            std::cout << "C";
        }
        if (c.cannibali_barca + c.missionari_barca == 0)
        {
            std::cout << "__";//visto che la barca è lunga 4 caratteri scrive "_" aggiuntivi se mancano personaggi sulla barca
        }
        if (c.cannibali_barca + c.missionari_barca == 1)
        {
            std::cout << "_";
        }
        std::cout << "_|.........";//chiude la barca e disegna l'acqua
        break;

    case('d'):  //caso: a destra

        std::cout << "........." << "|_" ;
        if (c.missionari_barca == 1 || c.missionari_barca == 2) {
            std::cout << 'M';
        }
        if (c.missionari_barca == 2) {
            std::cout << 'M';
        }
        if (c.cannibali_barca == 1 || c.cannibali_barca == 2) {
            std::cout << 'C';
        }
        if (c.cannibali_barca == 2) {
            std::cout << 'C';
        }
        if (c.cannibali_barca + c.missionari_barca == 0)
        {
            std::cout << "__";
        }
        if (c.cannibali_barca + c.missionari_barca == 1)
        {
            std::cout << "_";
        }
        std::cout << "_|";
        break;
    }

    std::cout << "..";
    n = 1;//reset di n allo stato originale 1
    for (int i = 0; i <c.cannibali_dx; i++) {  //disegna cannibali di destra con parte dell' isola di destra
        riva_dx[i+n]='C';
        n++;
    }
    n += 3;
    for (int i = 0; i <c.missionari_dx; i++) { //disegna missionari di destra con parte dell' isola di destra
        riva_dx[i+n]='M';
        n++;
    }
    std::cout << riva_dx;//disegna riva di destra
    std::cout << std::endl; // crea uno spazio per una lettura piu semplificata
}
