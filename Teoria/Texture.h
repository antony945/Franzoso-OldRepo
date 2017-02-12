using namespace std;

class Texture{
    public:
        // costruttore
        Texture();

        // distruttore
        ~Texture();

        // carica file
        bool loadFromFile(string path);

        // libera memoria
        void free();

        // renderizza in posizione specifica
        void render(int x, int y);

        // dimensioni immagini pubbliche
        int Width();
        int Height();

    private:
        // texture attuale
        SDL_Texture* cTexture;
        SDL_Renderer* cRenderer;

        // dimensioni immagini
        int cWidth;
        int cHeight;
};

Texture::Texture(){
    cTexture = NULL;
    cWidth = 0;
    cHeight = 0;
}

Texture::~Texture(){
    free();
}

void Texture::free(){
    SDL_DestroyTexture(cTexture);
    cTexture = NULL;

    cWidth = 0;
    cHeight = 0;
}

bool Texture::loadFromFile(string path){
    free();

    SDL_Texture* finalTexture = NULL;

    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if(imageSurface == NULL){
        cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError();
    }else{
        SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 0, 0xFF, 0xFF));

        finalTexture = SDL_CreateTextureFromSurface(cRenderer, imageSurface);
        if(imageSurface == NULL){
            cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError();
        }else{
            cWidth = imageSurface->w;
            cHeight = imageSurface->h;
        }

        SDL_FreeSurface(imageSurface);
    }

    cTexture = finalTexture;

    return cTexture != NULL;
}

void Texture::render(int x, int y){
    // rettangolo destinazione dove renderizzare la texture
    SDL_Rect dst_rect = {x, y, cWidth, cHeight};

    // renderizza la texture a schermo nella posizione scelta
    SDL_RenderCopy(cRenderer, cTexture, NULL, &dst_rect);
}

int Texture::Width(){
    return cWidth;
}

int Texture::Height(){
    return cHeight;
}
