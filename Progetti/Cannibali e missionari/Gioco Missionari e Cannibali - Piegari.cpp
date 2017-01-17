#include <iostream>
#include <stdio.h>
using namespace std;
void UserInput();//interazione con l'utente
void Elaboration();//elaborazione dei dati forniti in input
void StateOutput();//Output dello stato attuale del gioco: isola1, barca ed isola 2
void Start();//reset variabili
void Finalmsg();//messaggio finale in base allo stato di gioco
void BoatClear(); //variabile atta a svuotare la barca sull'isola in cui è approdata
void IslandsConfigure(); //funzione atta a rivedere la grafica delle isole in base ai dati di gioco del momento
void BoatConfigure(); //funzione atta a rivedere la grafica della barca in base ai dati di gioco del momento
void WinCheck(); //funzione atta a determinare la vittoria o la sconfitta

char game_state, restart='\0', temp; /*game_state: stato del gioco (0 perso, 1 vinto); restart: variabile per far ricominciare 
il gioco (S ricomincia, N non ricomincia), temp: variabile di interazione con l'utente in input*/
string boat, island1, island2; /*boat: variabile grafica della barca; island 1, island2: variabili grafiche delle isole*/
int cISL1, cISL2, mISL1, mISL2, mBOAT, cBOAT; /*Numero di cannibali e missionari rispettivamente in: isola sinistra, isola destra e barca*/
bool boatside, boatstate, yesorno; /*boatside: lato in cui si trova la barca(0=sinistra, 1=destra); boatstate: 0= barca vuota, 1= barca piena, yesorno: variabile di sicurezza
per l'utente in caso voglia rivedere le sue scelte di movimento della barca.*/


int main() 
{
do{
	Start();
			UserInput(); //Questa funzione contiene un ciclo interno che fa ripetere il tutto fino ad una modifica dello stato del gioco
	Finalmsg();
	cin;
	cout<<"\n\n\n\n\n\n\n\n\n\n"<<"Vuoi ricominciare il gioco? Sì per ricominciare, No per terminare la sessione.\n";
	cin>>restart; /*variabile per ricominciare il gioco*/
	}while(restart=='S' || restart =='s');
	cout<<"\t\tGrazie per aver giocato!\n\n";
	return 0;
}

void UserInput()
	{ 
	while(game_state==2) /*il ciclo continua finchè non cambia lo stato del gioco*/
		{
		cout<<"L'attuale situazione di gioco è la seguente: \n";
		StateOutput();
		cout<<endl;
		if(boatstate==0){ /*controllo dello stato della barca*/
			cout<<"La tua barca è vuota!"<<endl;	
		}
		else
		{
			cout<<"La tua barca ha uno o più personaggi al suo interno: "<<boat
			<<"Quest'ultima verrà svuotata e i personaggi messi al loro posto nell'isola"
			<<"Su cui sono approdati\n";
			BoatClear();/*in caso ci sia uno o più personaggi all'interno della barca, essa verrà svuotata sulla sponda su cui si trova*/
			cout<<"La tua situazione ora è questa:";
			StateOutput(); 
			cout<<endl;
		}
			for(int i=1;i<=2;i++)/*il ciclo si ripete due volte*/
				{
					if(i!=2) /*Primo messaggio*/
					{
						cout<<"Scrivi l'iniziale del primo personaggio che vuoi far salire sulla barca.\n";
						cin>>temp;
							while(temp!='0' && temp!='c' && temp!='m') /*Controllo del carattere inserito*/
							{
								cout<<"Carattere non valido. Inserisci un carattere valido: '0', 'n', 'm'.\n";
								cin>>temp;
								cout<<endl<<endl<<endl<<endl<<endl<<endl;
							}
						cout<<endl<<endl<<endl<<endl<<endl<<endl;
						Elaboration();
						StateOutput();
					}
					else/*Secondo messaggio */
					{
						cout<<"Scrivi l'iniziale del secondo personaggio che vuoi far salire sulla barca, in \ncaso "
								<<"non voglia far salire nessun altro digita 0\n";
						cin>>temp;
							while(temp!='0' && temp!='c' && temp!='m')
							{
								cout<<"Carattere non valido. Inserisci un carattere valido: '0', 'n', 'm'.\n";
								cin>>temp;
								cout<<endl<<endl<<endl<<endl<<endl<<endl;
							}
						if(temp!=0) /*Se, nel secondo ciclo l'utente decide di far partire la barca, essa si muove*/
						{
							Elaboration();
							StateOutput();					}
						else if(temp==0)
						{
							StateOutput();
							break;
						}
					}
				}
			cout<<"Sei sicuro di voler far navigare la seguente barca verso la riva opposta? Digita 1 per sì e"
					<<" 0 per togliere tutti i personaggi dalla barca e depositari sulla riva su cui essa si trova\n"<<boat<<endl<<endl<<endl<<endl;
			cin>>yesorno; /*variabile per controllare la scelta dell'utente e dargli la possibilità di tornare sui suoi passi*/
				if(yesorno==0)
				{
					BoatClear();
					BoatConfigure();
					IslandsConfigure();
					WinCheck();
				}
				if(yesorno==1) /*In caso l'utente voglia continuare, la barca si muove*/
				{
						boatside= !boatside;
						BoatClear();
						BoatConfigure();
						IslandsConfigure();
						WinCheck();
				}
			
	}
}

void Elaboration()
{
	
	if(temp=='c') /*In base all'input inserito, vengono elaborati i dati in modo diverso*/
	{
		if (boatside==0)
		{
			cISL1--;
			cBOAT++;
		}
		else
		{
			cISL2--;
			cBOAT++;
		}
		
	}
	if(temp=='m')
	{
		if ( boatside==0)
		{
			mISL1--;
			mBOAT++;
		}
		else 
		{
			mISL2--;
			mBOAT++;
		}
	}
	;
	IslandsConfigure();
	BoatConfigure();
	
}

void StateOutput() /*Variabile che, quando chiamata, da in output la situazione di gioco*/
{
	IslandsConfigure();
	BoatConfigure();
	if(boatside==0)
	{
		cout<<endl<<endl<<island1<<"__"<<boat<<"_______"<<island2<<endl<<endl;
	}
	else
	{
		cout<<endl<<endl<<island1<<"_______"<<boat<<"__"<<island2<<endl<<endl;
	}
}

void Start()/*Funzione atta al ripristino delle variabili allo stato di gioco iniziale*/
{
	cout<<"-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n"
			<<" Gioco in versione alpha sviluppato da Piegari Lorenzo.\n"
			<<"-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n";
	game_state=2, restart='\0', temp='\0'; 
	boat="|--_---_--|"; 
	island1 = "-_-_-_-_-_-_-"; 
	island2="-c-c-c-m-m-m-"; 
	cISL1=0, mISL1=0; 
	cISL2=3, mISL2=3; 
	boatside=1, boatstate=0;
	cBOAT=0, mBOAT=0;
}


void IslandsConfigure()/*Fuzione atta alla configurazione delle isole in base ai dati di gioco*/
{
	island1 = "-_-_-_-_-_-_-", island2 = "-_-_-_-_-_-_-";
	switch(cISL1)
	{
		case 0:
			break;
		case 1:
			island1[1]='c';
			break;
		case 2:
			island1[1]='c';
			island1[3]='c';
			break;
		case 3:
			island1[1]='c';
			island1[3]='c';
			island1[5]='c';
			break;
	}
	switch(mISL1)
	{
		case 0:
			break;
		case 1:
			island1[7]='m';
			break;
		case 2:
			island1[7]='m';
			island1[9]='m';
			break;
		case 3:
			island1[7]='m';
			island1[9]='m';
			island1[11]='m';
			break;
	}
	switch(cISL2)
	{
		case 0:
			break;
		case 1:
			island2[1]='c';
			break;
		case 2:
			island2[1]='c';
			island2[3]='c';
			break;
		case 3:
			island2[1]='c';
			island2[3]='c';
			island2[5]='c';
			break;
	}
	switch(mISL2)
	{
		case 0:
			break;
		case 1:
			island2[7]='m';
			break;
		case 2:
			island2[7]='m';
			island2[9]='m';
			break;
		case 3:
			island2[7]='m';
			island2[9]='m';
			island2[11]='m';
			break;
	}
}

void Finalmsg()/*Funzione atta a dare in output il messaggio finale*/
{
	cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
	if(game_state==1)
	{
		cout<<"=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=\n"
				<<"     Compliementi! Hai vinto la partita!\n"
				<<"=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=\n";
	}
	else if (game_state==0) 
	{
		cout<<"=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=\n"
				<<"       Mi spiace, hai perso la partita!\n"
				<<"=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=\n";
				cout<<endl<<endl;
				StateOutput();
				cout<<endl<<endl;
	}
	else if (game_state!=0 && game_state!=1)
	{
		cout<<"Finalmsg Error, game_state return !=0 && !=1";
	}
}

void BoatClear()/*Funzione atta a svuotare la barca e depositarne i personaggi sulla riva su cui si trovano*/
{
	int u;
	for(int i=0; i<2; ){ /*Ciclo for per rendere più semplice la configurazione della barca*/
		if(i==0)
		{
			u=3;
		}
		else if(i==1)
		{
			u=7;
		}
		i++;
				if(boat[u]=='_')
				{ 
					continue;
				}
				if(boat[u]=='c')
				{
					if(boatside==0)
					{
						cISL1++;
					}
					else
					{
						cISL2++;
					}
				}
				if(boat[u]=='m')
				{
					if(boatside==0)
					{
						mISL1++;
					}
					else
					{
						mISL2++;
					}
				}
	}
	mBOAT=0, cBOAT=0;
	boatstate=0;
	boat="|--_---_--|"; //il solo scopo della funzione è svuotare la barca
	BoatConfigure();
	IslandsConfigure(); //dopo lo svuotamento della barca vengono riconfigurate le isole
}


void BoatConfigure()/*Funzione atta a riconfigurare la barca*/
{
	boat="|--_---_--|";
	switch(cBOAT)
	{
		case 0:
			break;
		case 1:
			boat[3]='c';
			break;
		case 2:
			boat[3]='c';
			boat[7]='c';
			break;
	}
	switch(mBOAT)
	{
		case 0:
			break;
		case 1:
			boat[7]='m';
			break;
		case 2:
			boat[7]='m';
			boat[3]='m';
			break;
	}
	if(cBOAT+mBOAT > 2)
	{
		cout<<"\nERROR: cBOAT + mBOAT > 2. BoatConfigure Error\n";
	}
}


void WinCheck()/*Funzione con il solo scopo di modificare lo stato di gioco adattandolo alla situazione*/
{
	if(cISL1 > mISL1 || cISL2 > mISL2)
	{
		game_state=0;
	}
	if(cISL1==3 && mISL1==3)
	{
		game_state=1;
	}
}
