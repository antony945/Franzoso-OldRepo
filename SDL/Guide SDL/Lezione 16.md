# Lezione 16 - _True Type Fonts_

***

Tipi di variabili|Utilizzo
------------------|--------------
SDL_Color|
TTF_Font|Crea un font per scrivere un testo

#### **Classe**:
Tipo|Nome prototipo funzione|Input|Utilizzo
----|-------------|--------|-------
bool|loadFromRenderedText|_std::string_ textureText, _SDL_Color_ textColor| Funzione pubblica della classe. Crea un'immagine a partire da un testo e un colore.

#### **Funzioni SDL**:
Tipo|Nome funzione|Input|Utilizzo
----|-------------|--------|-------
SDL_Surface*|TTF_RenderText_Solid|_TTF_Font_ *font, _const char_ *text, _SDL_Color_ fg| Crea una superficie solida avendo in input il font, il testo, e il colore dato.
TTF_Font*|TTF_OpenFont|_const char*_ file, _int_ ptsize|Carica il file del font indicato nell'input e ne definisce la dimensione alla quale si vuole caricarlo.
void|TTF_CloseFont|_TTF_Font*_ font|Libera la memoria usata dal font e libera il font stesso.
int|TTF_Init|/|Inizializza SDL_ttf. Ritorna -1 se inizializzazione non riuscita, altrimenti 0.
char*|TTF_GetError|/| Fornisce all'utente in output la descrizione dell'ultimo errore rilevato da una funzione SDL_ttf.
void|TTF_Quit|/|Chiude la libreria SDL_ttf.


***

## Da ricordare
* Per utilizzare queste funzioni, è necessario includere la libreria **_SDL_ttf_** scaricabile da [questo](https://www.libsdl.org/projects/SDL_ttf/) link. Le modalità per configurarla sono le stesse usate per configurare le altre librerie SDL. Aggiungere però la dicitura _-lSDL2_ttf_ nelle impostazioni del linker di codeblocks.
* Per evitare errori nel caricamento del font e nelle funzioni della libreria, bisogna inizializzare **_SDL_ttf_** nella funzione dell'inizializzazione, subito dopo aver inizializzato _SDL_image_. Per fare ciò si usa la funzione **TTF_init** la quale fornisce un errore nel caso in cui essa sia uguale a **-1**. Si possono avere informazioni sull'errore in questione attraverso la funzione **TTF_GetError()**.

***

**Sintesi elaborata da Franzoso Antonio.**

Ref: [Lezione 16](http://lazyfoo.net/tutorials/SDL/16_true_type_fonts/index.php)