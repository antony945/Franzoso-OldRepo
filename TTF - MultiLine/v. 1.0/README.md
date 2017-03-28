# TTF - MultiLine v.1.0

Questa cartella contiene una prima versione dell'implementazione del rendering di testo a schermo su più linee grazie al carattere '\n', dal momento che questa feature non è supportata nativamente dalle librerie in uso (SDL + librerie base C++).

Il metodo consiste semplicemente nel cercare all'interno della stringa inserita la presenza di caratteri '\n' e memorizzare il risulato in variabili le quali scopo è il trovare la riga di testo con lunghezza maggiore, che fornirà la lunghezza della texture contenente il testo.
### Esempio pratico
Proviamo a confrontare due possibilità di inserimento testo per vedere dove e come cambia la larghezza della texture.
* Nel primo caso l'utente inserisce:
"Ciao, **\n** mi chiamo Pinco Pallino **\n** e vivo a Milano."
* Nel secondo:
"Ciao, **\n** mi chiamo Pinco Pallino **\n** e vivo a Milano, in Lombardia, da 25 anni."

L'output di entrambe sarà:
```
Ciao,                  |
mi chiamo Pinco Pallino|
e vivo a Milano.       |
```
```
Ciao,                                     |
mi chiamo Pinco Pallino                   |
e vivo a Milano, in Lombardia, da 25 anni.|
```

Dove le barrette indicano la lunghezza massima della texture, che varia a seconda della lunghezza della riga più lunga in ciasuna stringa di testo.

Mettendo a confronto i due esempi, si capisce come cambia la scelta della lunghezza della texture.
Ciò è stato fatto per permettere un maggiore controllo della posizione della texture sullo schermo in fase di rendering che, altrimenti, inserendo come lunghezza della texture la larghezza della finestra, cioè un valore non calcolato ma scelto dal programmatore, sarebbe stato difficile, se non impossibile da attuare. Questa scelta porta due vantaggi:
* Gestione **autonoma** della posizione della texture sullo schermo a seconda della lunghezza del testo senza dover cambiare manualmente i valori _x_ e _y_ da inserire in input nel rendering.
* Possibilità di creare **textbox** per contenere il testo, avendo una misura precisa di larghezza e altezza (v. _speech bubble_, textbox molto usate per contenere dialoghi nei giochi).

In questa versione del gioco manca, e verrà implementata nella prossima, l'importante feature che consentirà all'utente di passare alla riga successiva in due modi anzichè uno:
* inserendo appunto '\n' all'interno del testo nel punto in cui si vuole andare a capo;
* scrivendo il testo che andrà a capo automaticamente quando non ci sarà più spazio tra lunghezza designata come limite e la lunghezza del testo (cioè quando queste due lunghezze coincideranno).

___

*©antony945*
