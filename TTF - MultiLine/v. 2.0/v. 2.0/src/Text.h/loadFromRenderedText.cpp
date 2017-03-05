#include "../../lib/Text.h"

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
