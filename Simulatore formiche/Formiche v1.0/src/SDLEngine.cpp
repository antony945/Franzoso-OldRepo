#include "SDLclass.h"

LTimer::LTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;
}

Sprite::Sprite(const string& sprite_texture_path, long double x, long double y, int w, int h, int layer, SDL_Renderer* renderer)
	: x{ x }, y{ y }, width{ w }, height{ h }, layer{ layer }, last_update{ chrono::steady_clock::now() }
{
	s = createSurfaces(sprite_texture_path, renderer);
	collision_polygonx.push_back(x);
	collision_polygonx.push_back(x + w);
	collision_polygonx.push_back(x + w);
	collision_polygonx.push_back(x);
	collision_polygony.push_back(y);
	collision_polygony.push_back(y);
	collision_polygony.push_back(y + h);
	collision_polygony.push_back(y + h);
}


LightSource::LightSource(unsigned int x, unsigned int y, int range, int intensity, Uint8 r, Uint8 b, Uint8 g) {
	LightSource::x = x;
	LightSource::y = y;
	LightSource::range = range;
	LightSource::intensity = intensity;
	LightSource::r = r;
	LightSource::b = b;
	LightSource::g = g;
}

SDLclass::SDLclass(const char* title, int x, int y, int w, int h, string data_file)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw runtime_error(string("Failed to initialze SDL: ") + SDL_GetError());
	}
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		throw runtime_error(string("Failed to initialze SDL_Image: ") + IMG_GetError());
	}
	window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		throw runtime_error(string("Failed to create window: ") + SDL_GetError());
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		throw runtime_error(string("Failed to create renderer: ") + SDL_GetError());
	}
	addSpritePtr<Sprite>("black_pixe	l", 0, black_pixel_path, -1, -1, -1, 1);
	WIDTH = w;
	HEIGHT = h;
	loadSprites(data_file);

}

SDLclass::~SDLclass()
{
	layers.clear();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	paths.clear();
}


SDL_Surface* Sprite::loadTexture(string path, SDL_Renderer* renderer) {
	//Load image at specified path
	if (paths.find(path) == paths.end()) {
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface != NULL) { SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF)); }
		paths.insert(pair<string, SDL_Surface*>(path, loadedSurface));
		return loadedSurface;
	}
	else
	{
		return paths.at(path);
	}
}

vector<SDL_Surface*> Sprite::createSurfaces(const string& folder_path, SDL_Renderer* renderer) {
	vector<SDL_Surface*> s;
	experimental::filesystem::directory_iterator d{ experimental::filesystem::path{ folder_path } };
	for (auto i : d) {
		string path{ i.path().string() };
		SDL_Surface* surface{ NULL };

		if ((surface = loadTexture(path, renderer)) != NULL) {
			s.push_back(surface);
		}
	}
	return s;
}

void Sprite::changeTexture(const string& new_texture_path, SDL_Renderer* renderer) {
	loadTexture(new_texture_path, renderer);
}




void SDLclass::removeSprite(const string& sprite_name, int layer)
{
	delete layers.at(layer).sprite.at(sprite_name).get();
	layers.at(layer).sprite.erase(sprite_name);
}


LightSource& SDLclass::findLight(string name) {
	for (auto& i : layers) {
		for (auto& l : i.lights) {
			if (name == l.first) {
				return l.second;
			}
		}
	}
	LightSource l(1, 1, 1, 1, 1, 1, 1);
	return l;
}

void SDLclass::addLightSource(const string& light_name, int layer, unsigned int x, unsigned int y, int range, int intensity, Uint8 r, Uint8 b, Uint8 g) {
	if (layer > layers.size() - 1)
	{
		for (int i = layers.size() - 1; i < layer - 1; i++) {
			Layer l;
			layers.push_back(l);
		}
		Layer l;
		l.lights.insert(pair<string, LightSource>(light_name, LightSource(x, y, range, intensity, r, b, g)));
		layers.push_back(l);
	}
	else
	{
		layers.at(layer).lights.insert(pair<string, LightSource>(light_name, LightSource(x, y, range, intensity, r, b, g)));
	}
}

void SDLclass::removeLight(const string& light_name, int layer)
{
	layers.at(layer).lights.erase(light_name);
}

Sprite* SDLclass::findSprite(string name) {
	for (auto& i : layers) {
		for (auto& l : i.sprite) {
			if (name == l.first) {
				return l.second.get();
			}
		}
	}
	return NULL;
}

template<class T>
void SDLclass::addSpritePtr(string name, int layer, string texture_folder_path, long double x, long double y, int w, int h) {
	T t(texture_folder_path, x, y, w, h, layer, renderer);
	shared_ptr<Sprite> p = std::make_shared<T>(t);
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

void SDLclass::loadSprites(string data_file_path) {
	ifstream infile(data_file_path);
	if (infile.is_open()) {
		std::string line;
		while (std::getline(infile, line))
		{
			std::stringstream iss(line);
			string l;
			vector<string> tokens;
			while (std::getline(iss, l))
			{
				std::size_t prev = 0, pos;
				while ((pos = l.find_first_of("@", prev)) != std::string::npos)
				{
					if (pos > prev)
						tokens.push_back(l.substr(prev, pos - prev));
					prev = pos + 1;
				}
				if (prev < l.length())
					tokens.push_back(l.substr(prev, std::string::npos));
			}


			if (tokens.at(0) == "Sprite") {
				addSpritePtr<Sprite>(tokens.at(1), stoi(tokens.at(3)), tokens.at(2), (long double)stoi(tokens.at(4)), (long double)stoi(tokens.at(5)), stoi(tokens.at(6)), stoi(tokens.at(7)));
				if (tokens.size() >= 13) {
					vector<SDL_Point> new_c;
					for (int i = 8; i < tokens.size(); i += 2) {
						new_c.push_back({ stoi(tokens.at(i)), stoi(tokens.at(i + 1)) });
					}
					layers.at(stoi(tokens.at(3))).sprite.at(tokens.at(1)).get()->changePolygonShape(new_c);
					new_c.clear();
				}
			}
			if (tokens.at(0) == "Light") {
				addLightSource(tokens.at(1), stoi(tokens.at(2)), stoi(tokens.at(3)), stoi(tokens.at(4)), stoi(tokens.at(5)), stoi(tokens.at(6)), stoi(tokens.at(7)), stoi(tokens.at(8)), stoi(tokens.at(9)));
			}

			tokens.clear();
		}
	}
	infile.close();
}

void SDLclass::save(string data_file_path) {


}



void SDLclass::addExisistingDerivateToGroup(shared_ptr<Sprite> p, string group_name) {
	Groups.at(group_name).push_back(p);
}
void SDLclass::removeElementFromGroup(int index, string group_name) {
	Groups.at(group_name).erase(Groups.at(group_name).begin() + index);
}
