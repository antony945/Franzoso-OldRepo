#include Variables.h
#include function.h

bool Inizializza()
{
bool successo = true;

if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout<<"Impossibile inizializzare SDL, errore: "<<SDL_GetError()<<endl;
		successo = false;
	}
	else
	{
		Finestra = SDL_CreateWindow( "Tris!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGHEZZA, ALTEZZA, SDL_WINDOW_SHOWN );
		if( Finestra == NULL )
		{
			cout<<"Impossibile creare la finestra, errore: "<<SDL_GetError()<<endl;
			successo = false;
		}
		else
		{
			Renderer = SDL_CreateRenderer( Finestra, -1, SDL_RENDERER_ACCELERATED );
			if( Renderer == NULL )
			{
				cout<<"Impossibile creare il Renderer, errore: "<<SDL_GetError()<<endl;
				successo = false;
			}
			else
			{
				SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );        
                                SDL_RenderClear(Renderer);
        
				int Flag = IMG_INIT_PNG;
				if( !( IMG_Init( Flag ) & Flag ) )
				{
					cout<<"Impossibile inizializzare SDL_Image, errore: "<<IMG_GetError()<<endl;
					successo = false;
				}
			}
		}
	}

return successo;
}
