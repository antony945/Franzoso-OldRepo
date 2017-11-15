#include "../include/SDLclass.h"

string data_file = "C://path";

class Famiglia {
public:
	//atributi della famiglia
	string f = "famiglia";
};

class Genere {
public:
	//attributi del genere
	string g = "genere";
};

class Specie {
public:
	//attributi della specie
	string s = "specie";
};

class Formica {
public:
	//attributi formica
	string f = "formica";
	virtual void tick();
};

class Soldato : public Formica, public Specie, public Genere, public Famiglia, public Sprite {
public:
	//attributi lavoro
	void tick() {
	//Some stuff per il soldato
	};//fai qualcosa quando avviata
};


class Muratore : public Formica, public Specie, public Genere, public Famiglia, public Sprite {
public:
	//attributi lavoro
	void tick()
	{
	//Some stuff per il muratore
	};//fai qualcosa quando avviata
};


int main(int argc, char* args[]) {
	bool quit = false;
	float avgFPS = 0;
	SDLclass gioco("SDL", 10, 50, 700, 700, data_file);

	
	gioco.addGroup<Muratore>("muratori");
	gioco.addNewDerivateSpritesToGroup<Muratore>(100, "muratori", ...);

	while (!quit) {
		while (SDL_PollEvent(&gioco.events))
		{
			if (gioco.events.type == SDL_QUIT)
			{
				quit = true;
				gioco.save(data_file);
			}

		}
		//aggiorna tutte le formiche
		//--------------------------
		for (int i = 0; i < gioco.Groups.size(); i++)/*per ogni gruppo di formiche esistente*/
		{
			for (int y = 0; y < gioco.Groups.at(i).size(); y++) { /*per ogni oggetto del gruppo interessato*/
				gioco.Groups.at(i).at(y)->tick(); //avvia tutte le funzioni tick dell'oggetto all'interno di un dato gruppo 
			}
		}
		//-------------------------

		gioco.reloadScreen();

		
	}
	return 0;

}
