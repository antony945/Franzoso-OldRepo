# TTF - MultiLine v.1.0

Questa cartella contiene una prima versione dell'implementazione del rendering di testo a schermo su pi� linee grazie al carattere '\n', dal momento che questa feature non � supportata nativamente dalle librerie usate.

Il metodo consiste semplicemente nel cercare all'interno della stringa inserita la presenza di '\n' e memorizzarli in varie variabili al fine di trovare la linea di larghezza maggiore che sar� colei che fornir� la lunghezza della texture contenente il testo.

### Es. per capire

L'utente inserisce:
Ciao\nMi chiamo Pinco Pallino\ne vengo da Milano.

Il testo verr� suddiviso in:

```
Ciao                   |
Mi chiamo Pinco Pallino| //Le barrette indicano la lunghezza massima della texture
e vengo da Milano      |
```