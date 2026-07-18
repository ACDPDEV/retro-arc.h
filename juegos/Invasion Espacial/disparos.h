#ifndef DISPAROS_H
#define DISPAROS_H

#include <iostream>
#include <windows.h>
#include <conio.h>

#include "consola2.h"
#include "figuras.h"

using namespace std;

//=========================================================
// DISPARAR JUGADOR
//=========================================================
void dispararJugador(int xJugador, int yJugador,
                     int &xBala, int &yBala,
                     bool &disparando)
{
    if(!disparando)
    {
        xBala = xJugador + 20;
        yBala = yJugador;

        disparando = true;
    }
}
//=========================================================
// MOVER BALA DEL JUGADOR
//=========================================================
void moverBalaJugador(int &x, int &y,
                      bool &disparando)
{
    if(disparando)
    {
        borrarBalaJugador(x,y);

        y -= 2;

        if(y<=0)
        {
            disparando=false;
            return;
        }

        dibujarBalaJugador(x,y);
    }
}
//=========================================================
// DISPARAR OVNI 1
//=========================================================
void dispararOvni1(int xOvni, int yOvni,
                   int &xBala, int &yBala,
                   bool &disparando)
{
    if(!disparando)
    {
        // Dispara pocas veces
        if(rand() % 120 == 0)
        {
            xBala = xOvni + 15;
            yBala = yOvni + 8;

            disparando = true;
        }
    }
}
//=========================================================
// MOVER BALA OVNI 1
//=========================================================
void moverBalaOvni1(int &x, int &y,
                    bool &disparando)
{
    if(disparando)
    {
        borrarBalaOvni(x, y);

        // Baja a velocidad normal
        y++;

        if(y >= ALTO_PANTALLA)
        {
            disparando = false;
            return;
        }

        dibujarBalaOvni(x, y);
    }
}
//=========================================================
// DISPARAR OVNI 2
//=========================================================
void dispararOvni2(int xOvni, int yOvni,
                   int &xBala, int &yBala,
                   bool &disparando)
{
    if(!disparando)
    {
        // Dispara con mayor frecuencia
        if(rand() % 70 == 0)
        {
            xBala = xOvni + 22;
            yBala = yOvni + 10;

            disparando = true;
        }
    }
}
//=========================================================
// MOVER BALA OVNI 2
//=========================================================
void moverBalaOvni2(int &x, int &y,
                    bool &disparando)
{
    if(disparando)
    {
        borrarBalaOvni(x, y);

        // Baja más rápido
        y += 2;

        if(y >= ALTO_PANTALLA)
        {
            disparando = false;
            return;
        }

        dibujarBalaOvni(x, y);
    }
}
//=========================================================
// DISPARAR JEFE FINAL
//=========================================================
void dispararJefeFinal(int xJefe, int yJefe,
                       int &xLaser1, int &yLaser1,
                       int &xLaser2, int &yLaser2,
                       bool &disparando)
{
    if(!disparando)
    {
        // Probabilidad de disparar
        if(rand() % 50 == 0)
        {
            // Láser izquierdo
            xLaser1 = xJefe + 12;
            yLaser1 = yJefe + 18;

            // Láser derecho
            xLaser2 = xJefe + 48;
            yLaser2 = yJefe + 18;

            disparando = true;
        }
    }
}
//=========================================================
// MOVER LASER DEL JEFE FINAL
//=========================================================
void moverLaserJefe(int &xLaser1, int &yLaser1,
                    int &xLaser2, int &yLaser2,
                    bool &disparando)
{
    if(disparando)
    {
        borrarLaserJefe(xLaser1, yLaser1);
        borrarLaserJefe(xLaser2, yLaser2);

        // Ambos láseres bajan
        yLaser1 += 2;
        yLaser2 += 2;

        // Cuando salen de la pantalla desaparecen
        if(yLaser1 >= ALTO_PANTALLA)
        {
            disparando = false;
            return;
        }

        dibujarLaserJefe(xLaser1, yLaser1);
        dibujarLaserJefe(xLaser2, yLaser2);
    }
}

#endif
