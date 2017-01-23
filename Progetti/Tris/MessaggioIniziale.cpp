#include "function.h"
#include "Variables.h"

void MessaggioIniziale()
{
  SDL_Texture* Messaggio = NULL;  //Texture contenente il messaggio iniziale.
  Messaggio = CaricaTexture("");
  SDL_RenderCopy(Renderer, Messaggio, NULL, NULL);  //La texture del messaggio iniziale viene copiata nel renderer principale.
	SDL_RenderPresent(Renderer);
	SDL_Delay(5000);
  SDL_DestroyTexture(Messaggio);
  Messaggio = NULL;
}
