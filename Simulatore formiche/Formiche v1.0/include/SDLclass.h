#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept> //Useremo le exceptions
#if defined(_WIN32)
#include <../lib/SDL.h>
#include <../lib/SDL_image.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <../lib/Linux/SDL.h>
#include <../lib/Linux/SDL_image.h>
#endif
#include <algorithm>
#include <map>
#include <math.h>
#include <random>
#include <fstream>
#include <sstream>
#include <iterator>
#include <experimental/filesystem>
#include <functional>
#include <chrono>
#include <set>
#include <SDL_gfx>

using namespace std;

const double PI = 3.14159265359;
map<string, SDL_Surface*> paths;


class SDLclass;


struct Vettore {
	long double x, y;
	Vettore& operator+=(const Vettore& v);
	Vettore& operator-=(const Vettore& v);
	Vettore& operator*=(long double scalar);
	Vettore& operator/=(long double scalar);
};

Vettore operator-(const Vettore& a);
Vettore operator+(const Vettore& a, const Vettore& b);
Vettore operator-(const Vettore& a, const Vettore& b);
Vettore operator*(const Vettore& a, long double scalar);
Vettore operator/(const Vettore& a, long double scalar);
bool operator==(const Vettore& a, const Vettore& b);
bool operator!=(const Vettore& a, const Vettore& b);



class Sprite {
	SDL_Surface* loadTexture(string path, SDL_Renderer* renderer);
	map<string, Vettore> forces;
	Vettore velocity = { 0,0 };
	chrono::steady_clock::time_point last_update;
	Vettore resultant();

	void updateVelocity(chrono::duration<long double> delta_t);
	void updatePos(chrono::duration<long double> delta_t, const Vettore& old_v);
public:
	Sprite* ptr;
	const long double mass = 1;
	vector<long double> collision_polygony;
	vector<long double> collision_polygonx;
	vector<SDL_Surface*> s;
	SDL_RendererFlip flip;
	long double x, y;
	long double old_x, old_y;
	int width, height, layer;
	int surface_index = 0;
	
	
	Sprite(const string& sprite_texture_path, long double x, long double y, int w, int h, int layer, SDL_Renderer* renderer);

	void changeTexture(const string& new_texture_path, SDL_Renderer* renderer);
	
	/*
	Cambia la cartella dalla quale le texture vengono caricate
	Input:
	tipo: string contenuto: percorso di una cartella
	tipo: SDL_Renderer* contenuto: il renderer della classe SDLclass
	*/
	void changePolygonShape(vector<SDL_Point> points);
	/*
	Cambia la forma del poligono della sprite
	Input:
	tipo: vector  contenuto: punti (xy) dei vertici
	*/
	void updatePolygonPosition();
	/*
	
	*/
	void teleport(int new_x, int new_y);
	/*
	Sposta la sprite da un punto ad un altro
	Input:
	tipo: int contenuto: coordinate xy del nuovo punto
	*/
	void insertPolygonVertex(int vertex_index, SDL_Point new_pos);
	/*
	Aggiunge un array di vertici al poligono
	Input:
	tipo: int contenuto: index dove inserire l'array
	tipo: vector<SDL_Point> contenuto: veetore con coordinate xy dei nuovi vertici
	*/
	void insertPolygonVertexArray(int vertex_index, vector<SDL_Point> new_pos);
	/*
	Aggiunge un vertice al poligono
	Input:
	tipo: int contenuto: index dove inserire il vertice
	tipo: SDL_Point contenuto: coordinate xy del nuovo vertice
	*/
	void removePolygonVertexArray(int vertex_index, int number_of_vertices);
	/*
	Rimuove n vertici dal poligono
	Input:
	tipo: int contenuto: index dal quale inizia a rimuovere i vertici
	tipo: int contenuto: numero di vertici da rimuovere
	*/
	void movePolygonVertex(int vertex_index, SDL_Point new_pos);
	/*
	Sposta un vertice del poligono
	Input:
	tipo: int contenuto: index del vertice da spostare
	tipo: SDL_Point contenuto: coordinate xy del vertice spostato
	*/
	vector<SDL_Surface*> createSurfaces(const string& folder_path, SDL_Renderer* renderer);
	/*
	Carica le immagini da un cartella 
	Input:
	string :percorso programma
	renderer: renderer per le immagini
	output:
	vettore con le immagini caricate
	*/
	
	
	pair<map<string, Vettore>::iterator, bool> applyForce(Vettore v, string key);
	/*
	Aggiunge una forza alla sprite
	Input:
	tipo: Vettore contenuto: coordinate xy della forza vettore
	tipo: string contenuto: nome della forza da aggiungere
	*/
	map<string, Vettore>::size_type removeForce(string key);
	/*
	Rimuove una forza dalla sprite
	Input:
	tipo: string contenuto: nome della forza da rimuovere
	output:
	size_type: lunghezza del map
	*/
	void updateSpritePosition();
	/*
	Aggiorna la posizione della Sprite in funzione del tempo t
	*/
	void shrinkSurface(int index, int factorx, int factory);
	/*
	Restringe la superficie da renderizzare
	input:
	indice: frame da stringere
	int x: divisore dell'asse x da applicare al restringimento
	int y: divisore dell'asse y da applicare al restringimento
	*/
};



struct Layer {

	map<string, shared_ptr<Sprite>> sprite;//mappa principale di sprite
};
struct line { SDL_Point s, e; }; //linea per le collision, controlla se due poligoni si intersecano
struct linep { long double sx, sy, ex, ey; };//linea per i moviementi


class SDLclass {

	template<class T>
	void addSpritePtr(string name, int layer, string texture_folder_path, long double x, long double y, int w, int h);

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	vector<Layer> layers;


	map<string, vector<shared_ptr<Sprite>>> Groups;
	SDL_Event events;
	SDLclass(const char* title, int x, int y, int w, int h, string data_file);
	int WIDTH;
	int HEIGHT;
	~SDLclass();

	string black_pixel_path = "C:/Users/01c_polesel_riccar/Documents/Visual Studio 2015/Projects/SDL2/Boia";



	/*
	Aggiunge una Luce alla finestra
	Input:
	tipo: string contenuto: nome della nuova luce
	tipo: int contenuto: numero del layer di renderizzazione
	tipo: int contenuto: posizione sull'asse x della luce
	tipo: int contenuto: posizione sull'asse y della luce
	tipo: int contenuto: raggio della luce
	tipo: int contenuto: intensità della luce
	tipo: Uint8 contenuto: colore rosso della luce (0-255)
	tipo: Uint8 contenuto: colore blu della luce (0-255)
	tipo: Uint8 contenuto: colore verde della luce (0-255)
	*/
	void addLightSource(const string& light_name, int layer, unsigned int x, unsigned int y, int range, int intensity, Uint8 r, Uint8 b, Uint8 g);
	/*
	Rimuove una Sprite dato il suo nome e il layer di renderizzamento
	Input:
	tipo: string contenuto: nome della Sprite da rimuovere
	tipo: int contenuto: layer della sprite da rimuovere
	*/
	void removeSprite(const string& sprite_name, int layer);
	/*
	Rimuove una Luce dato il suo nome e il layer di renderizzamento
	Input:
	tipo: string contenuto: nome della Luce da rimuovere
	tipo: int contenuto: layer della Luce da rimuovere
	*/
	void removeLight(const string& light_name, int layer);
	/*
	Aggiorna lo schermo
	*/
	void reloadScreen();
	void raycast(int layer, string light_name);
	bool linecheck(line a, vertexstruct v, int layer);
	void loadSprites(string data_file_path);
	void save(string data_file_path);
	/*
	riduce le dimensione di una texture x
	Input:
	tipo: SDL_Surface* contenuto: pointer alla superfice da ridurre ( contenuto in sprite nel vettore "s"
	tipo: int contenuto: fattore di riduzione dell'asse x (2=metà, 4= un quarto dell'originale)
	tipo: int contenuto: fattore di riduzione dell'asse y (2=metà, 4= un quarto dell'originale)
	*/

	/*
	Trova una Sprite dato un nome x
	Input:
	tipo: string contenuto: nome della sprite da cercare
	*/
	Sprite* findSprite(string name);
	template<class T>
	T* getDerivateVariables(string name);
	/*
	Aggiunge una Sprite alla finestra
	Input:
	tipo: string contenuto: nome della nuova sprite
	tipo: string contenuto: nome della cartella dalla quale carica le texture
	tipo: int contenuto: numero del layer di renderizzazione
	tipo: int contenuto: posizione sull'asse x della sprite
	tipo: int contenuto: posizione sull'asse y della sprite
	tipo: int contenuto: larghezza della sprite
	tipo: int contenuto: altezza della sprite
	*/
	template<class T>
	void addDerivateSprite(string name, int layer, string texture_folder_path, long double x, long double y, int w, int h);
	template<class T>
	void addNewDerivateSpritesToGroup(int n, string group_name, string texture_folder_path, long double x, long double y, int w, int h, int layer);
	template<class T>
	T* getGroupDerivateVariables(int index, string group_name);
	/*
	Trova una Luce dato un nome x
	Input:
	tipo: string contenuto: nome della luce da cercare
	*/
	LightSource& findLight(string name);
	template<class T>
	void addGroup(string name);
	void addExisistingDerivateToGroup(shared_ptr<Sprite> p, string group_name);
	void removeElementFromGroup(int index, string group_name);
};

template<class T>
T* SDLclass::getDerivateVariables(string name) {
	Sprite* ptr = findSprite(name);
	return static_cast<T*>(ptr);
}

template<class T>
void SDLclass::addDerivateSprite(string name, int layer, string texture_folder_path, long double x, long double y, int w, int h) {
	T t(texture_folder_path, x, y, w, h, layer, renderer);
	shared_ptr<Sprite> p = make_shared<T>(t);
	if (layer >= layers.size()) {

		for (int y = layers.size(); y <= layer; y++) {
			Layer l;
			layers.push_back(l);
			addSpritePtr<Sprite>("light_corners", y, black_pixel_path, 0, 0, WIDTH, HEIGHT);
		}
		layers.at(layer).sprite.try_emplace(name, p);
	}
	else
	{
		layers.at(layer).sprite.try_emplace(name, p);
	}
}

template<class T>
void SDLclass::addNewDerivateSpritesToGroup(int n, string group_name, string texture_folder_path, long double x, long double y, int w, int h, int layer) {
	string name = group_name;
	for (int u = 0; u <= n; u++) {
		T t(texture_folder_path, x, y, w, h, layer, renderer);
		shared_ptr<Sprite> p = make_shared<T>(t);
		if (findSprite(name) == NULL) {
			layers.at(layer).sprite.try_emplace(name, p);
		}
		else
		{
			int j = 0;
			while (findSprite(name) != NULL) {
				name = group_name;
				name += to_string(j);
				j++;

			}
			layers.at(layer).sprite.try_emplace(name, p);
		}
		Groups.at(group_name).push_back(p);
	}
}

template<class T>
void SDLclass::addGroup(string name) {
	vector<shared_ptr<Sprite>> p;
	Groups.insert(pair<string, vector<shared_ptr<Sprite>>>(name, p));
}

template<class T>
T* SDLclass::getGroupDerivateVariables(int index, string group_name) {
	Sprite* ptr = Groups.at(group_name).at(index).get();
	return static_cast<T*>(ptr);
}

bool rect_collision(SDL_Rect a, SDL_Rect b);

struct Segment;

struct Polygon_point {
	long double x, y;
	Polygon_point* succ;
	Polygon_point(long double x, long double y, Polygon_point* succ = nullptr) : x(x), y(y), succ(succ) {}
	Polygon_point() : x(0), y(0), succ(nullptr) {}
	bool is_left();
	Segment line();
};

bool operator==(Polygon_point a, Polygon_point b);

struct Segment {
	Polygon_point a, b;
	operator linep() const {
		return{ a.x, a.y , b.x, b.y };
	}
};

bool operator==(Segment a, Segment b);
bool operator<(Segment a, Segment b);

bool point_inside_polygon(Polygon_point point, const Sprite& polygon);
bool polygon_collision(const Sprite& a, const Sprite& b);
