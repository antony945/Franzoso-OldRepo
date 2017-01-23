# Lezione 10 - _Color Keying_
*__Come rendere background trasparente in rendering multiplo di immagini sullo schermo.__*

***

Tipi di variabili|Utilizzo
------------------|--------------
SDL_Window|Crea la finestra fisica nella quale si lavorerà
SDL_Surface|Crea una superficie di lavoro
SDL_Renderer|Gestisce gli eventi in input, contiene le strutture per i diversi tipi di eventi
SDL_Texture|Crea una texture

Nuove funzioni|Input|Utilizzo
-----------------|--------|-------
SDL_SetColorKey|variabile SDL_Surface* surface, SDL_TRUE, SDL_MapRGB(...)|Questa funzione serve per rendere trasparente uno o più pixel di una superficie indicati dal terzo parametro. SDL_TRUE se si vuole attivare la color key, altrimenti SDL_FALSE.
SDL_MapRGB|loadedSurface->format, 0, 0xFF, 0xFF|Questa funzione mappa un valore di colore RGB in formato pixel. Gli ultimi tre parametri indicano le componenti del colore RGB da mappare, in questo caso il blu chiaro, ovvero il colore dello sfondo da far diventare trasparente.
***

## Da ricordare
Per la prima volta nelle lezioni si fa cenno alle classi al fine di semplificare il codice.
In questo caso viene creata una classe contenente tutte le informazioni necessarie a proposito della texture.
E' presente una coppia costruttore/distruttore, una funzoine che carica i file, una che libera la memoria deallocando le variabile, un renderer che renderizza in una posizione specifica, e una funzione che ottiene le dimensioni della texture. Ci sono infine una texture e le variabili che contengono larghezza e altezza.
```c++
class LTexture
{
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile( std::string path );

        //Deallocates texture
        void free();

        //Renders texture at given point
        void render( int x, int y );

        //Gets image dimensions
        int getWidth();
        int getHeight();

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};
```

* Utilizzare la funzione _SDL_SetColorKey_ **PRIMA** di creare una texture dalla superficie nella funzione _LTexture::loadFromFile( std::string path )_.
* Quando si renderizza una texture in una determinata posizione, bisogna specificare un rettangolo che contiene la posizione della x e della y + l'altezza e la larghezza della texture che si vuole copiare sullo schermo. Perciò quando viene renderizzata la nostra texture, viene creato un rettangolo attraverso _SDL_Rect_ con la posizione e altezza/larghezza come argomenti, per poi copiare la nostra texture sullo schermo grazie a **SDL_RenderCopy** specificando tra i parametri il luogo, indicato dal rettangolo appena creato, nel quale verrà copiata la texture.
    ```c++
    void LTexture::render( int x, int y )
    {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };
        SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
    }
    ```

***

**Sintesi elaborata da Franzoso Antonio.**

Ref: [Lezione 10](http://lazyfoo.net/tutorials/SDL/10_color_keying/index.php)