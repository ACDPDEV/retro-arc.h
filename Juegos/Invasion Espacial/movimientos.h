#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H

#include <windows.h>
#include <conio.h>
#include <ctime>
#include "consola2.h"
#include "figuritas.h"

using namespace std;

//=========================================================
// MOVER JUGADOR
//=========================================================
void moverJugador(int &x, int y)
{
    borrarJugador(x, y);

    if(kbhit())
    {
        char tecla = getch();

        switch(tecla)
        {
            case 'a':
            case 'A':
                if(x > 1)
                    x--;
                break;

            case 'd':
            case 'D':
                if(x < ANCHO_PANTALLA - 42)
                    x++;
                break;
        }
    }

    dibujarJugador(x, y);
}
//=========================================================
// MOVER METEORITO 1
//=========================================================
void moverMeteorito1(int &x, int &y)
{
    borrarMeteorito1(x, y);

    y++;

    if(y > ALTO_PANTALLA)
	{
    y = 0;
    x = rand() % (ANCHO_PANTALLA - 45) + 5;
	}

    dibujarMeteorito1(x, y);
}
//=========================================================
// MOVER METEORITO 2
//=========================================================
void moverMeteorito2(int &x, int &y)
{
    borrarMeteorito2(x, y);

    y += 2;

	if(y > ALTO_PANTALLA)
	{
    	y = 0;
    	x = rand() % (ANCHO_PANTALLA - 45) + 5;
	}

    dibujarMeteorito2(x, y);
}
//=========================================================
// MOVER METEORITO 3
//=========================================================
void moverMeteorito3(int &x, int &y)
{
    borrarMeteorito3(x, y);

    y += 3;

	if(y > ALTO_PANTALLA)
	{
   	 y = 0;
   	 x = rand() % (ANCHO_PANTALLA - 45) + 5;
	}

    dibujarMeteorito3(x, y);
}
//=========================================================
// MOVER OVNI 1
//=========================================================
void moverOvni1(int &x, int &y, int &direccion)
{
    borrarOvni1(x, y);

    // Movimiento vertical
    y++;

    // Movimiento horizontal
    x += direccion;

    // Cambia de dirección en los bordes
    if(x <= 2)
        direccion = 1;

    if(x >= ANCHO_PANTALLA - 35)
        direccion = -1;

    // Vuelve a aparecer arriba
    if(y > ALTO_PANTALLA)
    {
        y = 0;
        x = rand() % (ANCHO_PANTALLA - 35) + 2;

        if(rand() % 2 == 0)
            direccion = 1;
        else
            direccion = -1;
    }

    dibujarOvni1(x, y);
}
//=========================================================
// MOVER OVNI 2
//=========================================================
void moverOvni2(int &x, int &y, int &direccion)
{
    borrarOvni2(x, y);

    // Movimiento vertical
    y++;

    // Movimiento horizontal
    x += direccion;

    // Cambia de dirección
    if(x <= 2)
        direccion = 1;

    if(x >= ANCHO_PANTALLA - 35)
        direccion = -1;

    // Reinicia al salir de la pantalla
    if(y > ALTO_PANTALLA)
    {
        y = 0;
        x = rand() % (ANCHO_PANTALLA - 35) + 2;

        if(rand() % 2 == 0)
            direccion = 1;
        else
            direccion = -1;
    }

    dibujarOvni2(x, y);
}
//=========================================================
// MOVER JEFE FINAL
//=========================================================
void moverJefe(int &x,int &y,int &direccion)
{
    borrarJefeFinal(x, y);

    // Movimiento horizontal
    x += direccion;

    // Rebotar en los bordes
    if(x <= 2)
        direccion = 1;

    if(x >= ANCHO_PANTALLA - 55)
        direccion = -1;

    dibujarJefeFinal(x, y);
}
#endif
