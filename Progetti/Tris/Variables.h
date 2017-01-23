#pragma once


#define ALTEZZA 302  //altezza finestra
#define LARGHEZZA 302 //larghezza finestra
#define HEIGHT 10 //altezza di una casella
#define WIDTH 10 //larghezza di una casella
enum Stato { Vuota, Croce, Cerchio }; //stato di una casella
bool quit = false;
int index = -1;//index della casella cliccata
SDL_Renderer* Renderer = NULL;
SDL_Event e;
bool turno = true; //true = cerchio, false = croce
Stato Caselle[9]; //insieme degli stati delle caselle
