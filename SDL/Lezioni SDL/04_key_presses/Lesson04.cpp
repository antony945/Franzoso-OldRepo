#include <SDL.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#define Altez 480
#define Largh 640

bool Start();
void Close();
bool Load();
SDL_Surface* loadSurface(string path);

enum KeyPressSUurfaces
{
	KEY_Default,
	KEY_Up,
	KEY_Down,
	KEY_Left,
	KEY_Right,
	KEY_Total
};

SDL_Window* Finestra = NULL;
SDL_Surface* Schermo = NULL;
SDL_Surface* Corrente = NULL;
SDL_Surface* Stack[KEY_Total];


bool Start()
{
	bool success = true;

	if ( SDL_Init(SDL_INIT_VIDEO) < 0)
        success = false;
	else {
		Finestra = SDL_CreateWindow("KeyBoardInput", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Largh, Altez, SDL_WINDOW_SHOWN);
		if ( Finestra == NULL)
            success = false;
		else {
			Schermo = SDL_GetWindowSurface ( Finestra );
		}
	}

	return success;
}

SDL_Surface* loadSurface(string path)
{
	SDL_Surface *Superficie = SDL_LoadBMP(path.c_str());
	if(Superficie == NULL)
        cout<<"loadSurface error! "<< endl;
	return Superficie;
}

bool Load()
{
	bool success = true;

	Stack[KEY_Default] = loadSurface("04_key_presses/press.bmp");

	Stack[KEY_Up] = loadSurface("04_key_presses/up.bmp");

	Stack[KEY_Down] = loadSurface("04_key_presses/down.bmp");

	Stack[KEY_Left] = loadSurface("04_key_presses/left.bmp");

	Stack[KEY_Right] = loadSurface("04_key_presses/right.bmp");

	return success;
}

void Close()
{
	for(int i = 0; i < KEY_Total; i++)
	{
		SDL_FreeSurface(Stack[i]);
		Stack[i] = NULL;
	}

	SDL_DestroyWindow(Finestra);
	Finestra = NULL;

	SDL_Quit();

}

int main(int argc, char* args[] )
{
	bool quit = false;

    if(!Start() || !Load()){
        cout<<"Error"<<endl;
    }else{
        SDL_Event e;
        Corrente = Stack[KEY_Default];

        while(!quit){
            while( SDL_PollEvent( &e ) != 0 ){
                if(e.type == SDL_QUIT)
                    quit = true;

                if (e.type == SDL_KEYDOWN){
                    switch( e.key.keysym.sym ){
                        case SDLK_DOWN:
                            Corrente = Stack[KEY_Down];
                            break;

                        case SDLK_UP:
                            Corrente = Stack[KEY_Up];
                            break;

                        case SDLK_LEFT:
                            Corrente = Stack[KEY_Left];
                            break;

                        case SDLK_RIGHT:
                            Corrente = Stack[KEY_Right];
                            break;

                        default:
                            Corrente = Stack[KEY_Default ];
                            break;
                    }
                }
            }

            SDL_BlitSurface(Corrente, NULL, Schermo, NULL);
            SDL_UpdateWindowSurface(Finestra);
        }
    }

    Close();

    system("PAUSE");
    return 0;
}
