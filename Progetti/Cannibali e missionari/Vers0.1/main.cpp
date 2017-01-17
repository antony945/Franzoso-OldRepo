//
//  Created by Alberto Carraro on 27/09/16.
//  Copyright (c) 2016 Alberto Carraro. All rights reserved.
//

#include "utilities.h"

int main()
{
    configurazione c;
    inizializza(c);
    while(!controllaVittoria(c) && !controllaSconfitta(c)){
        disegnaConfigurazione(c);
        mossa m;
        interazioneUtente(m, c);
        eseguiAzione(m, c);
    }
    messaggioFinale(c);

    return 0;
}
