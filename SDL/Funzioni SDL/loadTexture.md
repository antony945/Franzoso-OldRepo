``` c++
SDL_Texture* loadTexture(string path){
    //Dichiara texture finale
    SDL_Texture* newTexture = NULL;

    //Carica l'immagine su una superficie
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    //Controlla riuscita caricamento
    if(loadedSurface == NULL){
        cout << endl << "Impossibile caricare immagine su superficie! \nIMG error: " << IMG_GetError() << endl;
    }else{
        //Crea textura dalla superficie contenente l'immagine
        newTexture = SDL_CreateTextureFromSurface(myRenderer, loadedSurface);

        //Controlla riuscita creazione
        if(newTexture == NULL){
            cout << endl << "Impossibile creare texture da immagine! \nSDL error: " << SDL_GetError() << endl;
        }
    }

    //Libera la memoria della superficie
    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;

    //Ritorna newTexture
    return newTexture;
}
```