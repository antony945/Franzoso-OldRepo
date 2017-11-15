# Progetto formiche
Questo progetto si basa sull'engine fatta da Polesel R. e Dittadi N. .
E' stata fatta una prima riorganizzazione generale della repository rispetto alla versione "engine", adattata al progetto che dovremmo svolgere.
Il progetto verrà utilizzato poi dalla classe 4°I come base per creare il gioco, aggiungendo elementi di programmazione basici (classi, funzioni, variabili) senza entrare nel merito
della grafica del gioco.

## Linee guida progetto:
### Caratteristiche formiche
* Collisione tra formiche: le formiche ovviamente dovrano collidere tra loro senza sovrapporsi.
* Feromoni: Le formiche rilasceranno feromoni in continuazione, che come pacchetti di dati indicheranno direzione, tipo di feromone, oggetto con cui la formica sta interagendo, etc. 
Dobbiamo quindi decidere quando e come vengono rilasciati i feromoni, i vari tipi che esistono e il loro raggio d'azione.*
* Modifica della velocità in base alla posizione di una fonte di particelle: le formiche devono modificare la loro velocità in base all'intensificarsi delle particelle.
* Interazione formica: Decisione su come dovrà interagire la formica con il mondo e con le altre formiche (creazione di priorities, exceptions, scambi di pacchetti di informazioni tra formiche**)
* Diversi tipi di formica: Per creare i diversi tipi di formiche 

### Caratteristiche formali codice
* Classi derivate: si potrebbero usare le classi derivate per creare delle funzioni e/o variabili standard, alle quali la classe potrebbe aggiungere la classe da loro creata. Un'idea
potrebbe essere una classe base di attributi dela formica, con inizializzazione per i diversi tipi (Magari attraverso le sprite e i gruppi già creati)
* Commenti: si dovrà commentare ogni parte di codice, per renderla fruibile alla classe che lo utilizzerà
* Semplificazione nomi funzioni: dove possibile, come già discusso con Riccardo e Nicolò, si dovrebbero semplificare i nomi delle funzioni che talvolta risultano di difficile comprensione.

### Caratteristiche ambiente
* L'ambiente dovrà contenere molti feromoni, particelle emanate dal cibo e/o dalle altre cose con cui le formiche dovranno interagire.

### Tests funzioni
* Si dovrà pensare ad un modo "poco invadente" di testare nuove funzioni non necessarie per il programma, ma importanti per un miglioramento dello stesso (Cartella temporanea, cartella spazzatura, ecc). Questo al fine di non "sporcare" il programma principale che va mantenuto il più attinente possibile al progetto "nudo".

### Generali progetto 
* Come gestire il comportamento delle formiche: si dovrebbe creare una seconda finestra di input per "avviare" il gioco e generare i vari eventi dando, ad esempio, posizione e grandezza di un cibo da generare.


*Possibilmente pensando ad un engine di base


**Se possibile gestendo un DataBase di informazioni delle interazioni 

credits to: Polesel Riccardo, Dittadi Nicolò, Piegari Lorenzo
