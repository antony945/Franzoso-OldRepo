#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window* myWindow = NULL;
SDL_Surface* myScreenSurface = NULL;
SDL_Surface* myImage = NULL;

bool init(){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        cout << "SDL couldn't initialize." << endl << "SDL Error: " << SDL_GetError() << endl;
        success = false;
    }else{
        myWindow = SDL_CreateWindow("002 Lesson", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(myWindow == NULL){
            cout << "Window couldn't be created." << endl << "SDL Error: " << SDL_GetError() << endl;
            success = false;
        }else{
            myScreenSurface = SDL_GetWindowSurface(myWindow);
        }
    }

    return success;
}

bool loadMedia(){
    bool success = true;
    myImage = SDL_LoadBMP("hello_world.bmp");

    if(myImage == NULL){
        cout << "Image couldn't be loaded." << endl << "SDL Error: " << SDL_GetError() << endl;
        success = false;
    }

    return success;
}

void close(){
    SDL_DestroyWindow(myWindow);
    myWindow = NULL;

    SDL_FreeSurface(myImage);
    myImage = NULL;

    SDL_Quit();
}

int main(int argc, char* argv[]){
    if(!init()){
        cout << "SDL could not initialize!" << endl;
    }else{
        if(!loadMedia()){
            cout << "Media could not be loaded!" << endl;
        }else{
            SDL_BlitSurface(myImage, NULL, myScreenSurface, NULL);
            SDL_UpdateWindowSurface(myWindow);

            SDL_Delay(2000);
        }

    }

    close();

    return 0;
}
