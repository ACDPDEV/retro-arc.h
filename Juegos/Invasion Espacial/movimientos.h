#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H

#include <windows.h>
#include <conio.h>
#include <ctime>
#include "consola2.h"
<<<<<<< HEAD
#include "figuras.h"
#include "disparos.h"
=======
#include "figuritas.h"
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

using namespace std;

//=========================================================
<<<<<<< HEAD
// VELOCIDAD DE LA NAVE
//=========================================================
// Cuantas columnas avanza la nave por cada pulsacion de flecha
const int VELOCIDAD_JUGADOR = 6;

//=========================================================
// MOVER JUGADOR
//=========================================================
void moverJugador(int &x, int y, int &xBala, int &yBala, bool &disparando)
=======
// MOVER JUGADOR
//=========================================================
void moverJugador(int &x, int y)
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
{
    borrarJugador(x, y);

    if(kbhit())
    {
<<<<<<< HEAD
        int tecla = getch();

        // Las flechas del teclado llegan como 2 codigos seguidos:
        // primero 0 o 224 (aviso de "tecla especial"), y despues
        // el codigo real de la flecha (75=izquierda, 77=derecha).
        if(tecla == 0 || tecla == 224)
        {
            int codigo = getch();

            switch(codigo)
            {
                case 75: // FLECHA IZQUIERDA
                    x -= VELOCIDAD_JUGADOR;
                    if(x < 1)
                        x = 1;
                    break;

                case 77: // FLECHA DERECHA
                    x += VELOCIDAD_JUGADOR;
                    if(x > ANCHO_PANTALLA - 42)
                        x = ANCHO_PANTALLA - 42;
                    break;
            }
        }
        else if(tecla == ' ')
        {
            dispararJugador(x, y, xBala, yBala, disparando);
=======
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
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
        }
    }

    dibujarJugador(x, y);
}
//=========================================================
// MOVER METEORITO 1
//=========================================================
<<<<<<< HEAD
void moverMeteorito1(int &x, int &y, bool &escapo)
{
    borrarMeteorito1(x, y);

    escapo = false;

    static int contador = 0;
    contador++;

    // Cae 1 fila cada 3 frames (antes caia 1 fila CADA frame)
    if(contador >= 3)
    {
        contador = 0;
        y++;
    }

    if(y > ALTO_PANTALLA)
	{
    escapo = true;
=======
void moverMeteorito1(int &x, int &y)
{
    borrarMeteorito1(x, y);

    y++;

    if(y > ALTO_PANTALLA)
	{
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    y = 0;
    x = rand() % (ANCHO_PANTALLA - 45) + 5;
	}

    dibujarMeteorito1(x, y);
}
//=========================================================
// MOVER METEORITO 2
//=========================================================
<<<<<<< HEAD
void moverMeteorito2(int &x, int &y, bool &escapo)
{
    borrarMeteorito2(x, y);

    escapo = false;

    static int contador = 0;
    contador++;

    // Cae 1 fila cada 2 frames (antes caia 2 filas CADA frame)
    if(contador >= 2)
    {
        contador = 0;
        y++;
    }

	if(y > ALTO_PANTALLA)
	{
    	escapo = true;
=======
void moverMeteorito2(int &x, int &y)
{
    borrarMeteorito2(x, y);

    y += 2;

	if(y > ALTO_PANTALLA)
	{
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    	y = 0;
    	x = rand() % (ANCHO_PANTALLA - 45) + 5;
	}

    dibujarMeteorito2(x, y);
}
//=========================================================
// MOVER METEORITO 3
//=========================================================
<<<<<<< HEAD
void moverMeteorito3(int &x, int &y, bool &escapo)
{
    borrarMeteorito3(x, y);

    escapo = false;

    static int contador = 0;
    contador++;

    // Cae 1 fila cada 2 frames (antes caia 1 fila CADA frame)
    if(contador >= 2)
    {
        contador = 0;
        y++;
    }

	if(y > ALTO_PANTALLA)
	{
   	 escapo = true;
=======
void moverMeteorito3(int &x, int &y)
{
    borrarMeteorito3(x, y);

    y += 3;

	if(y > ALTO_PANTALLA)
	{
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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

<<<<<<< HEAD
    // Movimiento vertical (cae 1 fila cada 2 frames, antes caia cada frame)
    static int contadorY = 0;
    contadorY++;

    if(contadorY >= 2)
    {
        contadorY = 0;
        y++;
    }
=======
    // Movimiento vertical
    y++;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

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

<<<<<<< HEAD
    // Movimiento vertical (cae 1 fila cada 3 frames, antes caia cada frame)
    static int contadorY = 0;
    contadorY++;

    if(contadorY >= 3)
    {
        contadorY = 0;
        y++;
    }
=======
    // Movimiento vertical
    y++;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    // Movimiento horizontal
    x += direccion;

    // Cambia de dirección
    if(x <= 2)
        direccion = 1;

<<<<<<< HEAD
    if(x >= ANCHO_PANTALLA - 46)
=======
    if(x >= ANCHO_PANTALLA - 35)
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
        direccion = -1;

    // Reinicia al salir de la pantalla
    if(y > ALTO_PANTALLA)
    {
        y = 0;
<<<<<<< HEAD
        x = rand() % (ANCHO_PANTALLA - 46) + 2;
=======
        x = rand() % (ANCHO_PANTALLA - 35) + 2;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

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
