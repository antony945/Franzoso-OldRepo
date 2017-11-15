 # Riassunto e descrizione di alcune funzioni utilizzate nel programma
 
 ## Ogni nuova funzione verrà aggiunta qui di seguito.


FUNZIONI CLASSE SPRITE:

|Funzione| Nome | Descrizione | Inputs |    
|-----|-----|-----|-----|
|void |change_texture|Cambia la cartella dalla quale le texture vengono caricate|Input:
||||tipo: string contenuto: percorso di una cartella 
||||tipo: SDL_Renderer* *contenuto: il renderer della classe SDLclass |
|void | change_collision_polygon|	Cambia la forma del poligono della sprite |Input:
||||tipo: vector  contenuto: punti (xy) dei vertici|
|void|teleport|	Sposta la sprite da un punto ad un altro|Input:
||||tipo: int contenuto: coordinate xy del nuovo punto|
|void|insert_collision_vertex|Aggiunge un vertice al poligono|	Input:
||||tipo: int contenuto: index dove inserire il vertice
||||tipo: SDL_Point contenuto: coordinate xy del nuovo vertice|
|void|insert_collision_vertex_array|Aggiunge un array di vertici al poligono|Input:
||||tipo: int contenuto: index dove inserire l'array
||||tipo: vector<SDL_Point> contenuto: veetore con coordinate xy dei nuovi vertici|
|void|remove_collision_vertex|Rimuove n vertici dal poligono|Input:
||||tipo: int contenuto: index dal quale inizia a rimuovere i vertici
||||tipo: int contenuto: numero di vertici da rimuovere|
|void|move_collision_vertex|cambia le coordinate di un vertice del poligono|Input:
||||tipo: int contenuto: index del vertice da spostare
||||tipo: SDL_Point contenuto: coordinate xy del vertice spostato|
|pair<map<string, Vettore>::iterator, bool>|apply_force|Aggiunge una forza alla sprite|Input:
||||tipo: Vettore contenuto: coordinate xy della forza vettore
||||tipo: string contenuto: nome della forza da aggiungere|
|map<string, Vettore>::size_type|remove_force|Rimuove una forza dalla sprite|Input:
||||tipo: string contenuto: nome della forza da rimuovere|
|void|update_position|Aggiorna la posizione della Sprite in funzione del tempo t|nulla|
	
	
FUNZIONI CLASSE GIOCO:

|Funzione| Nome | Descrizione | Inputs |    
|-----|-----|-----|-----|
|void|add_light_source|Aggiunge una Luce alla finestra|Input:
||||tipo: string contenuto: nome della nuova luce
||||tipo: int contenuto: numero del layer di renderizzazione
||||tipo: int contenuto: posizione sull'asse x della luce
||||tipo: int contenuto: posizione sull'asse y della luce
||||tipo: int contenuto: raggio della luce
||||tipo: int contenuto: intensità della luce
||||tipo: Uint8 contenuto: colore rosso della luce (0-255)
||||tipo: Uint8 contenuto: colore blu della luce (0-255)
||||tipo: Uint8 contenuto: colore verde della luce (0-255)|
|void|remove_sprite|Rimuove una Sprite dato il suo nome e il layer di renderizzamento|Input:
||||tipo: string contenuto: nome della Sprite da rimuovere
||||tipo: int contenuto: layer della sprite da rimuovere|
|void|reload_screen|Aggiorna lo schermo|nulla|
|SDL_Surface*|shrinkSurface|riduce le dimensione di una texture x|Input:
||||tipo: SDL_Surface* contenuto: pointer alla superfice da ridurre ( contenuto in sprite nel vettore "s"
||||tipo: int contenuto: fattore di riduzione dell'asse x (2=metà, 4= un quarto dell'originale)
||||tipo: int contenuto: fattore di riduzione dell'asse y (2=metà, 4= un quarto dell'originale)|
|Sprite*|find_sprite|Trova una Sprite dato un nome x|Input:
||||tipo: string contenuto: nome della sprite da cercare|	
|template<class T> T*|GetVar|Ottiene le variabili della classe T derivata da Sprite|Input:
||||tipo: classe contenuto: nome della classe derivata 
||||tipo: string contenuto: nome dell'oggetto della classe derivata T|
|void|add_user_sprite_ptr|Aggiunge una Sprite alla finestra|Input:
||||tipo: classe contenuto:nome della classe derivata 
||||tipo: string contenuto: nome della nuova sprite
||||tipo: string contenuto: nome della cartella dalla quale carica le texture
||||tipo: int contenuto: numero del layer di renderizzazione
||||tipo: int contenuto: posizione sull'asse x della sprite
||||tipo: int contenuto: posizione sull'asse y della sprite
||||tipo: int contenuto: larghezza della sprite
||||tipo: int contenuto: altezza della sprite|
|void|add_new_elements_to_group|aggiunge n elementi al gruppo x e ai layer (i nomi nel layer sono il nome del gruppo + index)|Input:
||||tipo: classe contenuto:nome della classe derivata 
||||tipo: int contenuto: numero di elementi da creare
||||tipo: string contenuto: nome della nuova sprite
||||tipo: string contenuto: nome della cartella dalla quale carica le texture
||||tipo: int contenuto: numero del layer di renderizzazione
||||tipo: int contenuto: posizione sull'asse x della sprite
||||tipo: int contenuto: posizione sull'asse y della sprite
||||tipo: int contenuto: larghezza della sprite
||||tipo: int contenuto: altezza della sprite|
|template<class T> T*|GetGroupVar|Ottiene le variabili della classe T derivata da Sprite e contenuta in un gruppo x|Input:
||||tipo: classe contenuto: nome della classe derivata 
||||tipo: int contenuto: index della sprite nel gruppo x
||||tipo: string contenuto: nome del gruppo della classe derivata T|
|LightSource&|find_light|Trova una Luce dato un nome x|Input:
||||tipo: string contenuto: nome della luce da cercare|
|void|add_group|Aggiunge un gruppo x|Input:
||||tipo: classe contenuto: nome della classe degli elementi del nuovo gruppo
||||tipo: string contenuto: nome del nuovo gruppo|
|void|add_element_to_group|Aggiunge un elemento gia esistente al gruppo x|Input:
||||tipo: shared_ptr<Sprite> contenuto: pointer alla sprite da aggiungere (GetVar(nome))|
|void|remove_element_to_group|rimuove un elemento da un gruppo x|Input:
||||tipo int contenuto: index della sprite da rimuovere dal gruppo x
||||tipo: string contenuto: nome del gruppo al quale rimuovere la sprite|
	
