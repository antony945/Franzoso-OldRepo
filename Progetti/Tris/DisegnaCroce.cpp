#include "function.h"
#include "Variables.h"

void DisegnaCroce(SDL_Renderer& renderer, int& index){
    /* GEOMETRY RENDERING DELLA CROCE
       Si effettua il disegno della croce nella posizione indicata dall'index attraverso geometry rendering.
       Altezza e lunghezza geometry rendering = 10.
       Index può assumere 9 valori, le 9 caselle. Dall'index si ottiene la posizione della croce nella finestra. */

    int x1_a = 45;
    int x1_b = 55;
    int y1 = 45;

    //Calcolo posizione partenza linee
    if(index < 4){
        x1_a+=((index-1)*101);
        x1_b+=((index-1)*101);
    }else{
        if(index < 7){
            x1_a+=(index-4)*101;
            x1_b+=(index-4)*101;
            y1+=101;
        }else{
            x1_a+=(index-7)*101;
            x1_b+=(index-7)*101;
            y1+=2*101;
        }
    }

    //Calcolo posizione finale linee
    int x2_a = x1_a+10;
    int x2_b = x2_a-10;
    int y2 = y1+10;

    //Setta il colore nero sul render
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

    //Disegno della croce (due linee oblique)
    SDL_RenderDrawLine(renderer, x1_a, y1, x2_a, y2); //LINEA A
    SDL_RenderDrawLine(renderer, x1_b, y1, x2_b, y2); //LINEA B
}
