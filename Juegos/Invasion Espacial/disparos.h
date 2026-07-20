/// @file disparos.h
/// @brief Sistema de disparos del juego Invasion Espacial.
/// @details Player bullets, enemy bullets, and boss lasers.
///          All functions in namespace InvasionEspacial.
#pragma once

#include <iostream>

#include "../../Common/Input.h"
#include "figuras.h"

using namespace std;

namespace InvasionEspacial {

//=========================================================
// DISPARAR JUGADOR
//=========================================================
/// @brief Activa el disparo del jugador
/// @param xJugador Columna del jugador
/// @param yJugador Fila del jugador
/// @param xBala Columna de la bala (se modifica)
/// @param yBala Fila de la bala (se modifica)
/// @param disparando Estado del disparo (se modifica)
inline void dispararJugador(int xJugador, int yJugador,
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
/// @brief Mueve la bala del jugador hacia arriba
/// @param x Columna de la bala (se modifica)
/// @param y Fila de la bala (se modifica)
/// @param disparando Estado del disparo (se modifica)
inline void moverBalaJugador(int &x, int &y,
                      bool &disparando)
{
    if(disparando)
    {
        borrarBalaJugador(x, y);

        y -= 2;

        if(y <= 0)
        {
            disparando = false;
            return;
        }

        dibujarBalaJugador(x, y);
    }
}

//=========================================================
// DISPARAR OVNI 1
//=========================================================
/// @brief Dispara bala desde OVNI 1 (con probabilidad aleatoria)
/// @param xOvni Columna del OVNI
/// @param yOvni Fila del OVNI
/// @param xBala Columna de la bala (se modifica)
/// @param yBala Fila de la bala (se modifica)
/// @param disparando Estado del disparo (se modifica)
inline void dispararOvni1(int xOvni, int yOvni,
                   int &xBala, int &yBala,
                   bool &disparando)
{
    if(!disparando)
    {
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
/// @brief Mueve la bala del OVNI 1 hacia abajo
/// @param x Columna de la bala (se modifica)
/// @param y Fila de la bala (se modifica)
/// @param disparando Estado del disparo (se modifica)
inline void moverBalaOvni1(int &x, int &y,
                    bool &disparando)
{
    if(disparando)
    {
        borrarBalaOvni(x, y);

        y++;

        if(y >= Common::VS_HEIGHT)
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
/// @brief Dispara bala desde OVNI 2 (mayor frecuencia)
/// @param xOvni Columna del OVNI
/// @param yOvni Fila del OVNI
/// @param xBala Columna de la bala (se modifica)
/// @param yBala Fila de la bala (se modifica)
/// @param disparando Estado del disparo (se modifica)
inline void dispararOvni2(int xOvni, int yOvni,
                   int &xBala, int &yBala,
                   bool &disparando)
{
    if(!disparando)
    {
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
/// @brief Mueve la bala del OVNI 2 hacia abajo (rápido)
/// @param x Columna de la bala (se modifica)
/// @param y Fila de la bala (se modifica)
/// @param disparando Estado del disparo (se modifica)
inline void moverBalaOvni2(int &x, int &y,
                    bool &disparando)
{
    if(disparando)
    {
        borrarBalaOvni(x, y);

        y += 2;

        if(y >= Common::VS_HEIGHT)
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
/// @brief Dispara doble láser desde el jefe final
/// @param xJefe Columna del jefe
/// @param yJefe Fila del jefe
/// @param xLaser1 Columna del láser izquierdo (se modifica)
/// @param yLaser1 Fila del láser izquierdo (se modifica)
/// @param xLaser2 Columna del láser derecho (se modifica)
/// @param yLaser2 Fila del láser derecho (se modifica)
/// @param disparando Estado del disparo (se modifica)
inline void dispararJefeFinal(int xJefe, int yJefe,
                       int &xLaser1, int &yLaser1,
                       int &xLaser2, int &yLaser2,
                       bool &disparando)
{
    if(!disparando)
    {
        if(rand() % 50 == 0)
        {
            xLaser1 = xJefe + 12;
            yLaser1 = yJefe + 18;

            xLaser2 = xJefe + 48;
            yLaser2 = yJefe + 18;

            disparando = true;
        }
    }
}

//=========================================================
// MOVER LASER DEL JEFE FINAL
//=========================================================
/// @brief Mueve ambos láseres del jefe hacia abajo
/// @param xLaser1 Columna del láser izquierdo (se modifica)
/// @param yLaser1 Fila del láser izquierdo (se modifica)
/// @param xLaser2 Columna del láser derecho (se modifica)
/// @param yLaser2 Fila del láser derecho (se modifica)
/// @param disparando Estado del disparo (se modifica)
inline void moverLaserJefe(int &xLaser1, int &yLaser1,
                    int &xLaser2, int &yLaser2,
                    bool &disparando)
{
    if(disparando)
    {
        borrarLaserJefe(xLaser1, yLaser1);
        borrarLaserJefe(xLaser2, yLaser2);

        yLaser1 += 2;
        yLaser2 += 2;

        if(yLaser1 >= Common::VS_HEIGHT)
        {
            disparando = false;
            return;
        }

        dibujarLaserJefe(xLaser1, yLaser1);
        dibujarLaserJefe(xLaser2, yLaser2);
    }
}

} // namespace InvasionEspacial
