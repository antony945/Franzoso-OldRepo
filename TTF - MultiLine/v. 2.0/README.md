# TTF - MultiLine v.2.0

Questa cartella contiene una seconda versione dell'implementazione del rendering di testo a schermo su più linee grazie al carattere '\n', dal momento che questa feature non è supportata nativamente dalle librerie in uso (SDL + librerie base C++).

In questa versione è stato implementata una feature mancante nella versione precedente, ossia il **text wrapping**, ossia l'andare a capo automaticamente alla fine dell'ultima parola visualizzabile interamente sulla stessa linea quando si cerca di renderizzare una porzione di testo troppo lunga per la lunghezza limite designata (nel caso descritto dalla guida, essa coincide con la dimensione della finestra).

1. Il programma _controlla_ se è necessario andare a capo per non superare il limite e, in caso positivo, **cerca** l'ultimo spazio (" ") esistente a partire dalla posizione dell'ultimo carattere del testo che è possibile scrivere su una stessa linea (ritornato da una nuova funzione, _maxTextForLine_, che riceve in input il testo della linea su cui si sta operando e il limite imposto).

2. A questo punto, **sostituisce** lo spazio trovato con un newLine ("**\n**") e poi, con l'ausilio di alcuni cicli e controlli, si metterà in atto la prima feature, quella descritta nella v.1.0, dal momento che saremo in presenza di un testo con un newLine al suo interno.

Questa procedura dovrebbe coprire **OGNI** possibile caso di inserimento di testo, in quanto le due feature si possono amalgamare e unire rendendo funzionante il tutto anche nel caso in cui nel testo sia già presente un newLine e, però, una delle due parti in cui si vuole dividere il testo risulti più lunga della finestra.

Provate il programma inserendo vari casi di inserimento di testo con e senza '\n', e aprite una issue nel caso doveste trovare dei problemi o proporre suggerimenti, grazie.
___

*©antony945*
