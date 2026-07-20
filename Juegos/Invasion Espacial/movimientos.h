/// @file movimientos.h
/// @brief Movimientos de entidades del juego Invasion Espacial.
/// @details Player movement with arrow keys (cross-platform via Common::Getch),
///          enemy movement patterns. All functions in namespace InvasionEspacial.
#pragma once

#include <ctime>

#include "../../Common/Input.h"
#include "figuras.h"
#include "disparos.h"

using namespace std;

namespace InvasionEspacial {

//=========================================================
// CONSTANTES DE MOVIMIENTO
//=========================================================

/// @brief Velocidad horizontal del jugador (columnas por pulsación)
const int VELOCIDAD_JUGADOR = 6;

//=========================================================
// LEER TECLA DE FLECHA (cross-platform)
//=========================================================

/// @brief Decodifica código de flecha a partir del primer byte leído
/// @param firstByte Primer byte leído con Getch()
/// @return 75 si flecha izquierda, 77 si flecha derecha, 0 si no es flecha
inline int GetchArrowKey(int firstByte)
{
    #ifdef _WIN32
    if(firstByte == 0 || firstByte == 224)
    {
        return Common::Getch();
    }
    return 0;
    #else
    if(firstByte == 27)
    {
        if(Common::Kbhit())
        {
            int next = Common::Getch();
            if(next == '[')
            {
                int dir = Common::Getch();
                if(dir == 'D') return 75;
                if(dir == 'C') return 77;
            }
        }
        return 0;
    }
    return 0;
    #endif
}

//=========================================================
// MOVER JUGADOR
//=========================================================
/// @brief Mueve el jugador según input del teclado
/// @param x Columna del jugador (se modifica)
/// @param y Fila del jugador
/// @param xBala Columna de la bala (se modifica al disparar)
/// @param yBala Fila de la bala (se modifica al disparar)
/// @param disparando true si ya hay una bala en vuelo
inline void moverJugador(int &x, int y, int &xBala, int &yBala, bool &disparando)
{
    borrarJugador(x, y);

    if(Common::Kbhit())
    {
        int tecla = Common::Getch();

        if(tecla == ' ')
        {
            dispararJugador(x, y, xBala, yBala, disparando);
        }
        else
        {
            int flecha = GetchArrowKey(tecla);

            switch(flecha)
            {
                case 75: // FLECHA IZQUIERDA
                    x -= VELOCIDAD_JUGADOR;
                    if(x < 1)
                        x = 1;
                    break;

                case 77: // FLECHA DERECHA
                    x += VELOCIDAD_JUGADOR;
                    if(x > Common::VS_WIDTH - 42)
                        x = Common::VS_WIDTH - 42;
                    break;
            }
        }
    }

    dibujarJugador(x, y);
}

//=========================================================
// MOVER METEORITO 1
//=========================================================
/// @brief Mueve el meteorito 1 (pequeño) hacia abajo
/// @param x Columna (se modifica)
/// @param y Fila (se modifica)
/// @param escapo true si el meteorito salió de la pantalla
inline void moverMeteorito1(int &x, int &y, bool &escapo)
{
    borrarMeteorito1(x, y);

    escapo = false;

    static int contador = 0;
    contador++;

    if(contador >= 3)
    {
        contador = 0;
        y++;
    }

    if(y > Common::VS_HEIGHT)
    {
        escapo = true;
        y = 0;
        x = rand() % (Common::VS_WIDTH - 45) + 5;
    }

    dibujarMeteorito1(x, y);
}

//=========================================================
// MOVER METEORITO 2
//=========================================================
/// @brief Mueve el meteorito 2 (mediano) hacia abajo
/// @param x Columna (se modifica)
/// @param y Fila (se modifica)
/// @param escapo true si el meteorito salió de la pantalla
inline void moverMeteorito2(int &x, int &y, bool &escapo)
{
    borrarMeteorito2(x, y);

    escapo = false;

    static int contador = 0;
    contador++;

    if(contador >= 2)
    {
        contador = 0;
        y++;
    }

    if(y > Common::VS_HEIGHT)
    {
        escapo = true;
        y = 0;
        x = rand() % (Common::VS_WIDTH - 45) + 5;
    }

    dibujarMeteorito2(x, y);
}

//=========================================================
// MOVER METEORITO 3
//=========================================================
/// @brief Mueve el meteorito 3 (gigante) hacia abajo
/// @param x Columna (se modifica)
/// @param y Fila (se modifica)
/// @param escapo true si el meteorito salió de la pantalla
inline void moverMeteorito3(int &x, int &y, bool &escapo)
{
    borrarMeteorito3(x, y);

    escapo = false;

    static int contador = 0;
    contador++;

    if(contador >= 2)
    {
        contador = 0;
        y++;
    }

    if(y > Common::VS_HEIGHT)
    {
        escapo = true;
        y = 0;
        x = rand() % (Common::VS_WIDTH - 45) + 5;
    }

    dibujarMeteorito3(x, y);
}

//=========================================================
// MOVER OVNI 1
//=========================================================
/// @brief Mueve el OVNI tipo 1 (zigzag + caída)
/// @param x Columna (se modifica)
/// @param y Fila (se modifica)
/// @param direccion Dirección horizontal (1 o -1, se modifica)
inline void moverOvni1(int &x, int &y, int &direccion)
{
    borrarOvni1(x, y);

    static int contadorY = 0;
    contadorY++;

    if(contadorY >= 2)
    {
        contadorY = 0;
        y++;
    }

    x += direccion;

    if(x <= 2)
        direccion = 1;

    if(x >= Common::VS_WIDTH - 35)
        direccion = -1;

    if(y > Common::VS_HEIGHT)
    {
        y = 0;
        x = rand() % (Common::VS_WIDTH - 35) + 2;

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
/// @brief Mueve el OVNI tipo 2 (zigzag + caída lenta)
/// @param x Columna (se modifica)
/// @param y Fila (se modifica)
/// @param direccion Dirección horizontal (1 o -1, se modifica)
inline void moverOvni2(int &x, int &y, int &direccion)
{
    borrarOvni2(x, y);

    static int contadorY = 0;
    contadorY++;

    if(contadorY >= 3)
    {
        contadorY = 0;
        y++;
    }

    x += direccion;

    if(x <= 2)
        direccion = 1;

    if(x >= Common::VS_WIDTH - 46)
        direccion = -1;

    if(y > Common::VS_HEIGHT)
    {
        y = 0;
        x = rand() % (Common::VS_WIDTH - 46) + 2;

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
/// @brief Mueve el jefe final (zigzag horizontal)
/// @param x Columna (se modifica)
/// @param y Fila (se modifica)
/// @param direccion Dirección horizontal (1 o -1, se modifica)
inline void moverJefe(int &x, int &y, int &direccion)
{
    borrarJefeFinal(x, y);

    x += direccion;

    if(x <= 2)
        direccion = 1;

    if(x >= Common::VS_WIDTH - 55)
        direccion = -1;

    dibujarJefeFinal(x, y);
}

} // namespace InvasionEspacial
