## Cose fondamentali
* Aggiungere tutte le librerie non-standard incluse nella cartella lib
* Creare classi derivate genere ✓
* Creare classi derivate ruolo ✓
* Creare classe comune formiche ✓
* Creare ambiente gioco e relative funzioni ✓*
* Creare matrici feromoni e ambiente con relativo funzionamento
* Creare sole e suo spostamento ✓
* Creare funzione void tick() per movimento ✓
* Rendering formiche e ambiente ✓
* Gestione input formiche ✓
* Collisions formiche con oggetti o altre formiche 
* Creazione classe Ostacolo e derivate (cibo, filo d'erba, sasso) ✓*
* Proprietà formiche: sono codificati con il punto in alto a sinistra di una matrice da cui si disloca una texture
* Gestione ostacoli all'interno della matrice ✓
* Reimpostare setPosizioneSole in base al tempo trascorso✓ 
* Render nido ✓
* Collisions formiche con oggetti ✓
* Tana delle formiche: posizione ed interazione con essa. ✓
## Cose secondarie
* Migliorare prestazioni (una formica allo stato attuale "pesa" circa 6MB di ram!)
* Aggiungere i suoni
* Aggiungere exceptions per facilitare il debug
* Creare un database di salvataggio dei dati
* Migliorare algoritmo di randomizzazione coordinate di arrivo

## Definito
* Funzionamento feromoni (ad area o linea continua oppure punto) - Punto su matrice
* Nella colonia, ci sono più specie di formiche? - NO 
* La specie corrisponde al ruolo? No, l'unica divisione sotto al genere è il ruolo 
* nRuoli -> dipende da genere 
* Codifica ostacoli con numeri (matrice di stringe si riduce a matrice di interi) 
* Codifica azioni con matrice (input in riga e stati in colonna) in cui ogni punto della matrice contiene un record con stato di arrivo e azione da compiere, ognuno codificato con un numeroo diverso. IN ogni stato si attende l'input per lo stato successivo. Si ha bisogno di una variabile per contenere lo stato attuale della formica come punto in una matrice. Il numero di input e stati va determinato con una costate all'inizio. 
* Workflow progetto: una volta terminata la struttura della parte di programma interessata su FLowChart va creato il corrispondente codice nel progetto. 

## Da Definire




*=da terminare
