#include Variables.h
#include function.h

void DisegnaTabella()
{
SDL_SetRenderDrawColor( Renderer, 0x00, 0x00, 0x00, 0x00 );
SDL_RenderDrawLine( Renderer, 101, 0, 101, ALTEZZA );
SDL_RenderDrawLine( Renderer, 202, 0, 202, ALTEZZA );
SDL_RenderDrawLine( Renderer, 0, 202, LARGHEZZA, 202 );
SDL_RenderDrawLine( Renderer, 0, 101, LARGHEZZA, 101 );
}
