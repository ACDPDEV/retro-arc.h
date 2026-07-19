#include "game.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

char tablero[TAM][TAM];


int main(){

    Common::InitTerminalRawMode();
    Common::EnableTrueColor();
    Common::EnableUTF8();

    srand(time(NULL));
	intro();
    char opcion;


    while(true){

        menuPrincipal();

        opcion = Common::Getch();


        if(opcion == '1'){

            do{

                jugarOriginal();

            }while(jugarNuevamente());

        }


        else if(opcion == '2'){

            do{

                jugarFutbol();

            }while(jugarNuevamente());

        }


        else if(opcion == '3'){

            break;

        }

    }


    return 0;
}
