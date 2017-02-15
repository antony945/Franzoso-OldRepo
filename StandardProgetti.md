Come vi ho già anticipato, lo standard nella realizzazione dei progetti cambierà un po'.
Avremo alcune nuove direttive da rispettare durante la realizzazione di ogni progetto.

***

## Project folder standard

Come dice il nome stesso, si tratta di uno standard per la disposizione interna della cartella del progetto.
Qui abbiamo vari standard utilizzabili. Quello che adotteremo noi sarà il seguente:
Tutto il progetto sarà diviso in  5 cartelle:

* __bin__
  * La cartella bin conterrà i files eseguibili.
 
* __include__
  * La cartella include conterrà tutti gli header da includere per la corretta esecuzione del progetto.
  
* __lib__
  * La cartella lib conterrà tutte le librerie necessarie all'esecuzione del progetto.
 
* __res__
  * La cartella res conterrà tutte le risorse che serviranno al progetto (files audio, video, immagini, etc.).
  
* __src__
  * La cartella src conterrà tutti i files sorgente necessari al progetto.
  
Tutto qui per quanto riguarda la struttura della cartella.


***

## .gitignore

Il file .gitignore contiene un elenco di tutte le estensioni di files da non clonare quando si lavora con  GitHub.
A questo file, che deve essere necessariamente presente in ogni cartella principale del progetto, bisogna aggiungere tutte le estensioni 
dei propri files progetto e di tutti quelli che, generalmente, variano di computer in computer e di Sistema Operativo in Sistema Operativo.

*** 

## Naming conventions

Le naming conventions non sono altro che semplici regole da rispettare quando si da il nome ad una funzione, il file di una funzione o una variabile.
Queste regole comprendono anche la scrittura del codice in generale.
Quelle che seguiremo noi saranno le seguenti:

* __I nomi dei files delle funzioni devono essere necessariamente uguali all'intestazione della funzione e dovranno terminare con .cpp.__

Esempio:
 void eseguiAzione(); ==> eseguiAzione.cpp
 
* __I nomi delle funzioni dovranno essere di contenuta lunghezza e non dovranno contenere caratteri speciali ma solo lettere e, se necessario, numeri.__

Esempio: 
void eseguiAzione();

NO : ~~void esegui_Azione();~~

Ciò garantirà più compattezza e ordine.

* __I nomi delle variabili non dovranno contenere caratteri speciali ma solo lettere e, se necessario, numeri.__

Penso non ci sia bisogno di esempi.

* __La chiusura delle parentesi grafe deve essere effettuata la riga successiva all'ultima riga di codice, indendandola con la relativa apertura.__

``` c++

if()
{
  *codice*
}

```

***

## I Commenti

I commenti sono da sempre un grande ostacolo per la "standardizzazione" dei progetti.
Adotteremo quindi solo poche semplici regole in modo da non mettere nessuno in difficoltà.

* __I commenti vanno fatti a lato di ogni inizio di qualsiasi ciclo, spiegandone il fine__


``` c++

for() //Questo ciclo serve come dimostrazione per la guida sugli standard dei progetti
{
  *codice*
}

```

* __I commenti vanno inoltre utilizzati per spiegare la funzione di una determinata variabile il cui nome non ne spiega l'utilità. 
bisogna poi spiegare l'eventuale motivo per cui è inizializzata ad un certo valore.__


``` c++

if()
{
 int a = 10; //Questa variabile serve come spiegazione per la guida sugli standard dei progetti, è inizializzata a 10 perchè ...
  *codice*
}

```

* __I commenti NON vanno utilizzati per esprimere opinioni o dubbi, per quelli esistono le Issues.__


``` c++

for() 
``` 
~~//Questo ciclo secondo me va spostato in un altro luogo~~




***
# Attenzione:
### Questo file è in continuo aggiornamento, in base alle esigenze del team e alle modifiche che saranno fatte per una migliore gestione del tutto.
### Vi prego quindi di rimanere sempre aggiornati.



