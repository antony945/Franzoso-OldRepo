//Inizializza SDL_image per il caricamento PNG
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) & imgFlags)){
                    cout << endl << "IMPOSSIBILE INIZIALIZZARE SDL_image! \n";
                    cout << "SDL_image Error: " << IMG_GetError() << endl;
                    
                    //Cambia il valore della variabile 'success'. Inizializzazione non riuscita
                    success = false;
                }