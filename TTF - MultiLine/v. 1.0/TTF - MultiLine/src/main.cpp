/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, SDL_ttf, standard IO, math, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>

//Texture wrapper class
class Text
{
	public:
		//Initializes variables
		Text();

		//Deallocates memory
		~Text();

		//Loads image at specified path
		Uint32 getMaxWidth(std::string textureText);

		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);

		//Deallocates texture
		void free();

		void render(int x, int y);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* tTexture;

		//Image dimensions
		int tWidth;
		int tHeight;
};

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Rendered texture
Text gTextTexture;


Text::Text()
{
	//Initialize
	tTexture = NULL;
	tWidth = 0;
	tHeight = 0;
}

Text::~Text()
{
	//Deallocate
	free();
}

Uint32 Text::getMaxWidth(std::string textureText)
{
    std::string maxTextLine;

    int maxLengthLine = 0;

    std::string newLine = "\n";

    bool stopFinder = false;
    std::size_t newLineFinder = 0;

    std::size_t lengthLine = 0;
    std::size_t exFinder = 0;

    for(std::size_t i = 0; !stopFinder; i+=lengthLine+1)
    {
        /** LUNGHEZZA LINEA **/
        if(newLineFinder == 0)
            std::size_t exFinder = newLineFinder;
        else
            exFinder = newLineFinder + 1;

        newLineFinder = textureText.find(newLine, i);

        stopFinder = (newLineFinder == std::string::npos);
        if (stopFinder)
        {
            newLineFinder = textureText.length();
        }

        std::cout << "New line found at " << newLineFinder << ".\n";

        lengthLine = newLineFinder - exFinder; //LUNGHEZZA LINEA DI TESTO
        std::cout << "Actual line is " << lengthLine << ".\n";
        if (lengthLine > maxLengthLine)
        {
            maxLengthLine = lengthLine;
        }

        /** TESTO LINEA **/
        char textLine[100]; //PORZIONE DI TESTO DI OGNI LINEA
        std::size_t lengthTextLine = textureText.copy(textLine, lengthLine, i); //LUNGHEZZA PORZIONE DI TESTO DI OGNI LINEA
        textLine[lengthTextLine] = '\0'; //CARATTERE TERMINATORE DI STRINGA
        std::cout << "Text of this line is: '" << textLine << "'.\n\n";

        if(lengthLine > maxTextLine.length())
        {
            maxTextLine = textLine;
        }
    }

    TTF_SizeText(gFont, maxTextLine.c_str(), &maxLengthLine, NULL); //MASSIMA LUNGHEZZA DI UNA LINEA IN PIXEL

    std::cout << "All new line were been found.\n\n";
    std::cout << "Text of MAX line is: '" << maxTextLine << "'.\n\n";
    std::cout << "Total lenght of text: " << textureText.length() << ".\n";
    std::cout << "Max lenght for line: " << maxLengthLine << ".\n";

    return maxLengthLine;
}


bool Text::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	Uint32 stringLength = getMaxWidth(textureText.c_str());

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( gFont, textureText.c_str(), textColor, stringLength);
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        tTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( tTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			tWidth = textSurface->w;
			tHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return tTexture != NULL;
}

void Text::free()
{
	//Free texture if it exists
	if( tTexture != NULL )
	{
		SDL_DestroyTexture( tTexture );
		tTexture = NULL;
		tWidth = 0;
		tHeight = 0;
	}
}

void Text::render( int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, tWidth, tHeight };

	//Render to screen
	SDL_RenderCopy(gRenderer, tTexture, NULL, &renderQuad);
}

int Text::getWidth()
{
	return tWidth;
}

int Text::getHeight()
{
	return tHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				 //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "../res/lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };

        if( !gTextTexture.loadFromRenderedText( "PROVA STRINGA\nVisualizzazione di una stringa di testo\nscritta su piu' righe,\nutlizzando il carattere\nterminatore di stringa,\ngrazie alla libreria SDL_ttf\ned alla libreria string.", textColor ) )
        {
            printf( "Failed to render text texture!\n" );
            success = false;
        }
        else
        {
            if( gTextTexture.getWidth() > SCREEN_WIDTH )
            {
                std::cout << "\nImpossible render text! Text it's greater to the width of the window. \n";
                success = false;
            }
        }
	}

	return success;
}

void close()
{
	//Free loaded images
	gTextTexture.free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render current frame
				gTextTexture.render( (SCREEN_WIDTH-gTextTexture.getWidth())/2, (SCREEN_HEIGHT-gTextTexture.getHeight())/2 );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
