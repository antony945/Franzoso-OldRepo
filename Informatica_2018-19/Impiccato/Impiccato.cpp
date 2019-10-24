#include <iostream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

bool endGame(char user_word[], char word[], int life){
    if(!life){
        system("CLS");
        cout << "Vite rimaste: " << life << endl << endl;
        cout << "Parola: ";
        for(int i=0;i<8;i++){
            cout << user_word[i] << " ";
        }
        cout << endl << endl;
        cout << "Hai terminato le vite!" << endl;
        return true;
    }

    for(int i=0;i<8;i++){
        if(user_word[i]!=word[i]){
            return false;
        }
    }

    system("CLS");
    cout << "Vite rimaste: " << life << endl << endl;
    cout << "Parola: ";
    for(int i=0;i<8;i++){
        cout << user_word[i] << " ";
    }
    cout << endl << endl;
    cout << "Hai indovinato la parola!" << endl;
    return true;
}

int main(){
    char word[8] = {'p','o','l','i','t','a','n','o'};
    char user_word[8] = {'_','_','_','_','_','_','_','_'};
    int life=5;

    do{
        system("CLS");

        cout << "Vite rimaste: " << life << endl << endl;
        cout << "Parola: ";
        for(int i=0;i<8;i++){
            cout << user_word[i] << " ";
        }
        cout << endl << endl;

        char letter;
        int correct_char = 0;

        cout << "Inserisci lettera: ";
        cin >> letter;

        for(int i=0;i<8;i++){
            if(tolower(letter)==word[i]){
                user_word[i]=word[i];
                correct_char++;
            }
        }

        if(!correct_char)
            life--;

        for(int i=0;i<8;i++){
            cout << user_word[i] << " ";
        }

        cout << endl << endl;

    }while(!endGame(user_word, word, life));

    cout << endl;
    system("PAUSE");
    return 0;
}
