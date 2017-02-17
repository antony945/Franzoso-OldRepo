#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define LUNGHEZZA 640
#define ALTEZZA 480

using namespace std;

class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(string path );

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Mix_Music* gMusic = NULL;

LTexture::LTexture()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(string path )
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFF, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	if(mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

const int TOTAL_CLIP = 9;

bool inizializza();
bool caricaMedia();
void chiudi();

LTexture gScreenTexture;
LTexture gMapTexture;
LTexture gSpacemanTexture;

SDL_Rect gSpacemanRect[TOTAL_CLIP];

int main(int argc, char* argv[])
{
    if(!inizializza())
    {
        cerr << "Problemo.";
        exit(1);
    }
    else
    {
        if(!caricaMedia())
        {
            cerr << "Problemo.";
            exit(1);
        }
        else
        {
            SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);

            gScreenTexture.render(0, 0);
            gMapTexture.render(0, 0);

            SDL_RenderPresent(gRenderer);

            bool quit = false;
            SDL_Event e;
            int frame = 0;

            while(!quit)
            {
                while(!SDL_PollEvent(&e))
                {
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else
                    {
                        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_1)
                        {
                            if(Mix_PlayingMusic() == 0)
                            {
                                Mix_PlayMusic(gMusic, -1);
                            }
                            else
                            {
                                Mix_PauseMusic();
                            }
                        }
                    }
                }

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                SDL_Rect* currentClip = &gSpacemanRect[frame/8];
                gSpacemanTexture.render(LUNGHEZZA/2, ALTEZZA/2, currentClip);

                SDL_RenderPresent(gRenderer);

                frame++;

                if(frame/8 >= TOTAL_CLIP)
                {
                    frame = 0;
                }
            }
        }
    }

    chiudi();

    return 0;
}

void chiudi(){
    gScreenTexture.free();
    gMapTexture.free();
    gSpacemanTexture.free();

    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    SDL_DestroyWindow(gWindow);
    SDL_DestroyRenderer(gRenderer);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}

bool caricaMedia(){
    bool success = true;

    if(!gScreenTexture.loadFromFile("_res_/background.png"))
    {
        printf( "Failed to load BACKGROUND!\n" );
        success = false;
    }

    if(!gMapTexture.loadFromFile("_res_/map.png"))
    {
        printf( "Failed to load MAP!\n" );
        success = false;
    }

    if(!gSpacemanTexture.loadFromFile("_res_/spaceman.png"))
    {
        printf( "Failed to load SPACEMAN!\n" );
        success = false;
    }
    else
    {
        gSpacemanRect[0].x = 0;
        gSpacemanRect[0].y = 0;
        gSpacemanRect[0].w = 108;
        gSpacemanRect[0].h = 320;

        gSpacemanRect[1].x = 108;
        gSpacemanRect[1].y = 0;
        gSpacemanRect[1].w = 108;
        gSpacemanRect[1].h = 320;

        gSpacemanRect[2].x = 216;
        gSpacemanRect[2].y = 0;
        gSpacemanRect[2].w = 108;
        gSpacemanRect[2].h = 320;

        gSpacemanRect[3].x = 324;
        gSpacemanRect[3].y = 0;
        gSpacemanRect[3].w = 108;
        gSpacemanRect[3].h = 320;

        gSpacemanRect[4].x = 432;
        gSpacemanRect[4].y = 0;
        gSpacemanRect[4].w = 108;
        gSpacemanRect[4].h = 320;

        gSpacemanRect[5].x = 540;
        gSpacemanRect[5].y = 0;
        gSpacemanRect[5].w = 108;
        gSpacemanRect[5].h = 320;

        gSpacemanRect[6].x = 648;
        gSpacemanRect[6].y = 0;
        gSpacemanRect[6].w = 108;
        gSpacemanRect[6].h = 320;

        gSpacemanRect[7].x = 756;
        gSpacemanRect[7].y = 0;
        gSpacemanRect[7].w = 108;
        gSpacemanRect[7].h = 320;

        gSpacemanRect[8].x = 864;
        gSpacemanRect[8].y = 0;
        gSpacemanRect[8].w = 108;
        gSpacemanRect[8].h = 320;
    }

    gMusic = Mix_LoadMUS("_res_/beat.wav");
    if(gMusic == NULL)
    {
        printf( "Failed to load MUSIC!\n" );
        success = false;
    }

    return success;
}

bool inizializza(){
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("Progetto01", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LUNGHEZZA, ALTEZZA, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL)
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if(!(IMG_Init(imgFlags)&imgFlags))
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 24000) < 0)
				{
					cout << "Problemo.";
					success = false;
				}
            }
        }
    }

    return success;
}
