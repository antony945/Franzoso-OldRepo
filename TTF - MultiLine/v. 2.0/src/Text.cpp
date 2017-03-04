#include "../lib/Text.h"

/*PROVA STRINGA\nVisualizzazione di una stringa di testo\nscritta su piu' righe,\nutlizzando il carattere\nterminatore di stringa,\ngrazie alla libreria SDL_ttf\ned alla libreria string. */

//PROVA STRINGA\nVisualizzazione di una stringa di testo scritta su piu' righe, utlizzando il carattere terminatore di stringa, grazie alla libreria SDL_ttf ed alla libreria string.

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

std::size_t Text::maxTextForLine(std::string textLine, int text_limit)
{
    /* This function returns the maximum text that can stay on one line, giving as input a limit beyond which we should wrap the text. */
    int w = 0;
    std::string maxTextForLine;
    std::cout << "\n\n";

        for(std::size_t i = 0; w <= text_limit; i++)
        {
            maxTextForLine.append(textLine, i, 1);
            TTF_SizeText(gFont, maxTextForLine.c_str(), &w, NULL);
            std::cout << "Width after " << i+1 << " character: " << w << "\n";
        }

    std::cout << "\n\n\nMax Text For Line: " << maxTextForLine << ".\n\n\n";

    return maxTextForLine.length();
}

Uint32 Text::getMaxWidth(std::string textureText)
{
    std::string maxTextLine;
    int maxLengthLine = 0;

    std::size_t lengthLine = 0;

    std::size_t exFinder = 0;
    std::size_t newLineFinder = 0;
    std::string newLine = "\n";
    bool stopFinder = false;

    std::string textLine;

    int w_line = 0;

    for(std::size_t i = 0; !stopFinder; i+=lengthLine+1)
    {
        do
        {
            if(w_line <= SCREEN_WIDTH)
            {
                if(newLineFinder == 0)
                    exFinder = newLineFinder;
                else
                    exFinder = newLineFinder + 1;
            }

            newLineFinder = textureText.find(newLine, i);

            stopFinder = (newLineFinder == std::string::npos);
            if (stopFinder)
            {
                if(i == 0)
                {
                    newLineFinder = 0;
                    lengthLine = textureText.length();
                }
                else
                {
                    newLineFinder = textureText.length();
                    lengthLine = newLineFinder - exFinder;
                }
            }
            else
            {
                    lengthLine = newLineFinder - exFinder; //LUNGHEZZA LINEA DI TESTO
                    if (lengthLine > maxLengthLine)
                    {
                        maxLengthLine = lengthLine;
                    }
            }

            std::cout << "New line found at " << newLineFinder << ".\n";
            std::cout << "Actual line is " << lengthLine << ".\n";

            /** TESTO LINEA **/
            textLine.assign(textureText, i, lengthLine);
            std::cout << "Text of this line is: '" << textLine << "'.\n\n";
            TTF_SizeText(gFont, textLine.c_str(), &w_line, NULL);

            std::cout << "Actual width of text is " << w_line << ".\n\n";

            std::string space(" ");

            if(textLine.length() > maxTextLine.length())
            {
                maxTextLine = textLine;
            }

            if(w_line > SCREEN_WIDTH)
            {
                std::size_t pos_last_space_allowed = textLine.find_last_of(space.c_str(), maxTextForLine(textLine, SCREEN_WIDTH)) + exFinder;
                std::cout << "Position of last space in textureText: " << pos_last_space_allowed << std::endl << std::endl;

                textureText.replace(pos_last_space_allowed, 1, newLine);

                std::cout << "TextureText: \n" << textureText << std::endl << std::endl;

                maxTextLine.clear();
            }

        }while(w_line > SCREEN_WIDTH);
    }

    TTF_SizeText(gFont, maxTextLine.c_str(), &maxLengthLine, NULL); //MASSIMA LUNGHEZZA DI UNA LINEA IN PIXEL

    std::cout << "All new line were been found.\n\n";
    std::cout << "Text of MAX line is: '" << maxTextLine << "'.\n\n";
    std::cout << "Total lenght of text: " << textureText.length() << ".\n";
    std::cout << "Max lenght in pixel for line: " << maxLengthLine << ".\n"; //(MINORE DI SCREEN_WIDTH)

    return maxLengthLine;
}


bool Text::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	Uint32 stringLength = getMaxWidth(textureText.c_str());

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( gFont, textureText.c_str(), textColor, stringLength );
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
