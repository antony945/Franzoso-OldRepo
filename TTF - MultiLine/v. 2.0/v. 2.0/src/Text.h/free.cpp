#include "../../lib/Text.h"

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
