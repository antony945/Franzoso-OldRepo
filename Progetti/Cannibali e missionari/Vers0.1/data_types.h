/*
 Strutture dati definite per rappresentare configurazione del gioco corrente e mossa corrente.
*/
struct configurazione{
    unsigned char missionari_sx;
    unsigned char missionari_dx;
    // numero di missionari presenti su ciascuna sponda
    // assumono valori tra 0 e 3
    unsigned char cannibali_sx;
    unsigned char cannibali_dx;
    // numero di cannibali presenti su ciascuna sponda
    // assumono valori tra 0 e 3
    unsigned char missionari_barca;
    unsigned char cannibali_barca;
    // assumono valori da 0 a 2 e la loro somma e' <= 2
    char lato_barca;
    // assume solo due valori: 'd' e 's'
};

struct mossa{
    char elemento;
    char partenza;
    char arrivo;
};
