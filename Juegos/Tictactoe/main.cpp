#include "game.h"
#include "console.h"
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

char tablero[TAM][TAM];


int main(){

    srand(time(NULL));

    char opcion;


    while(true){

        menuPrincipal();

        opcion = getch();


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
