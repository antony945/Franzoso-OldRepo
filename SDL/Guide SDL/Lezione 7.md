# Lezione 7

***

Tipi di variabili|Utilizzo
:------------:|------------
SDL_Window*|Crea la finestra nel quale verrà visualizzato l'output del programma
SDL_Texture*|Crea la texture contenenente l'immagine
SDL_Renderer*|Crea il renderer nel quale verrà caricata la texture
SDL_Surface*|Crea una superficie di lavoro
SDL Event|Crea una variabile che acquisisce il tipo degli eventi compiuti (SDL_QUIT, SDL_KEYDOWN, ecc.).

Funzioni|Input|Utilizzo
:-------:|:-----:|--------
SDL_Init|SDL_INIT_VIDEO|Inizializza SDL; restituisce valore negativo nel caso in cui l'inizializzazione non riesca.
SDL_GetError|/|Se richiamata con istruzione di output, stampa a video l'eventuale errore dovuto alla mancata riuscita di una funzione di SDL.
SDL_CreateWindow|"Nome Finestra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Larghezza finestra, Altezza finestra, SDL_WINDOW_SHOWN|Genera la finestra di lavoro di larghezza e altezza pari rispettivamente al valore di 'Larghezza finestra' e a quello di 'Altezza finestra'.
SDL_CreateRenderer|Variabile SDL_Window*, -1, SDL_WINDOW_ACCELERATED|Genera il renderer per la finestra.
SDL_SetRenderDrawColor|Variabile SDL_Renderer*, 0xFF, 0xFF, 0xFF, 0xFF|Inizializza i colori usabili dal renderer.
IMG_Init|_int_ flags|(flags = IMG_INIT_VIDEO). Inizializza SDL_image. Nel caso in cui 'IMG_Init(flags)&flags' sia diverso da 0, inizializzazione di SDL_image non riuscita.
IMG_GetError|/|Se richiamata con istruzione di output, stampa a video l'eventuale errore dovuto alla mancata riuscita di una funzione di SDL_image.
IMG_Load|"Percorso file"|Carica all'interno di una variabile SDL_Surface* l'immagine indicata in input.
SDL_CreateTextureFromSurface|Variabile SDL_Renderer*, Variabile SDL_Surface*|Genera una texture da una superficie pre-esistente.
SDL_FreeSurface|Variabile SDL_Surface*|Libera la memoria allocata alla variabile SDL_Surface* indicata in input.
SDL_DestroyTexture|Variabile SDL_Texture*|Distrugge la texture indicata in input.
SDL_DestroyRenderer|Variabile SDL_Renderer*|Distrugge il renderer indicato in input.
SDL_DestroyWindow|Variabile SDL_Window*|Distrugge la finestra indicata in input.
SDL_Quit|/|Chiude ed esce dal sottosistema SDL.
IMG_Quit|/|Chiude ed esce dal sottosistema SDL_image.
SDL_PollEvent|Variabile SDL_Event&|Cattura le azioni compiute dall'utente e le aggiunge alla coda. Ritorna 1 se ci sono ancora eventi da svolgere, altrimenti 0.
SDL_RenderClear|Variabile SDL_Renderer*|Pulisce e riempie lo schermo con il colore settato nella funzione SDL_SetRenderDrawColor.
SDL_RenderCopy|Variabile SDL_Renderer*, Variabile SDL_Texture*|Copia e renderizza la texture sullo schermo.
SDL_RenderUpdate|Variabile SDL_Renderer*|Aggiorna la finestra applicando le modifiche.

***

### Da ricordare

* Utilizzare le funzioni *SDL_DestroyTexture*, *SDL_DestroyRenderer*, *SDL_DestroyWindow*, *SDL_Quit* e *IMG_Quit* per liberare la memoria e chiudere il programma.

* Nelle funzioni *IMG_Init* e *IMG_Load* usare *IMG_GetError* per visualizzare l'errore, in tutti gli altri casi di questa lezione utilizzare *SDL_GetError*.

**Ref:** [Lezione 7](http://lazyfoo.net/tutorials/SDL/07_texture_loading_and_rendering/index.php)

Sintesi elaborata da Franzoso Antonio

__*N.b. la sintesi è elaborata solo in base alle informazioni contenute all'interno della lezione 7*__