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
        std::cout << "Text of this line is: " << textLine << ".\n\n";

        if(lengthLine > maxTextLine.length())
        {
            maxTextLine = textLine;
        }
    }

    TTF_SizeText(gFont, maxTextLine.c_str(), &maxLengthLine, NULL); //MASSIMA LUNGHEZZA DI UNA LINEA IN PIXEL

    std::cout << "All new line were been found.\n\n";
    std::cout << "Text of MAX line is: " << maxTextLine << ".\n\n";
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
