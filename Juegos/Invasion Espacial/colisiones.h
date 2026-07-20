/// @file colisiones.h
/// @brief Detección de colisiones del juego Invasion Espacial.
/// @details Rectangle-based collision detection for all entity pairs.
///          All functions in namespace InvasionEspacial.
#pragma once

#include <iostream>

#include "figuras.h"

using namespace std;

namespace InvasionEspacial {

//=========================================================
// TAMAÑOS DE LAS FIGURAS
//=========================================================

/// @brief Ancho del jugador en caracteres
const int ANCHO_JUGADOR = 40;

/// @brief Alto del jugador en caracteres
const int ALTO_JUGADOR = 17;

/// @brief Ancho del meteorito 1
const int ANCHO_METEORITO1 = 14;

/// @brief Alto del meteorito 1
const int ALTO_METEORITO1 = 10;

/// @brief Ancho del meteorito 2
const int ANCHO_METEORITO2 = 19;

/// @brief Alto del meteorito 2
const int ALTO_METEORITO2 = 11;

/// @brief Ancho del meteorito 3
const int ANCHO_METEORITO3 = 23;

/// @brief Alto del meteorito 3
const int ALTO_METEORITO3 = 13;

/// @brief Ancho del OVNI 1
const int ANCHO_OVNI1 = 27;

/// @brief Alto del OVNI 1
const int ALTO_OVNI1 = 10;

/// @brief Ancho del OVNI 2
const int ANCHO_OVNI2 = 44;

/// @brief Alto del OVNI 2
const int ALTO_OVNI2 = 14;

/// @brief Ancho del jefe final
const int ANCHO_JEFE = 51;

/// @brief Alto del jefe final
const int ALTO_JEFE = 19;

/// @brief Margen de precisión para colisiones de bala
const int MARGEN_PRECISION = 4;

//=========================================================
// COLISION BALA - METEORITO 1
//=========================================================
/// @brief Verifica colisión bala contra meteorito 1
inline bool colisionBalaMeteorito1(int xBala, int yBala,
                            int xMeteorito, int yMeteorito)
{
    if(xBala >= xMeteorito - MARGEN_PRECISION &&
       xBala <= xMeteorito + ANCHO_METEORITO1 + MARGEN_PRECISION &&
       yBala >= yMeteorito - MARGEN_PRECISION &&
       yBala <= yMeteorito + ALTO_METEORITO1 + MARGEN_PRECISION)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION BALA - METEORITO 2
//=========================================================
/// @brief Verifica colisión bala contra meteorito 2
inline bool colisionBalaMeteorito2(int xBala, int yBala,
                            int xMeteorito, int yMeteorito)
{
    if(xBala >= xMeteorito - MARGEN_PRECISION &&
       xBala <= xMeteorito + ANCHO_METEORITO2 + MARGEN_PRECISION &&
       yBala >= yMeteorito - MARGEN_PRECISION &&
       yBala <= yMeteorito + ALTO_METEORITO2 + MARGEN_PRECISION)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION BALA - METEORITO 3
//=========================================================
/// @brief Verifica colisión bala contra meteorito 3
inline bool colisionBalaMeteorito3(int xBala, int yBala,
                            int xMeteorito, int yMeteorito)
{
    if(xBala >= xMeteorito - MARGEN_PRECISION &&
       xBala <= xMeteorito + ANCHO_METEORITO3 + MARGEN_PRECISION &&
       yBala >= yMeteorito - MARGEN_PRECISION &&
       yBala <= yMeteorito + ALTO_METEORITO3 + MARGEN_PRECISION)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION BALA - OVNI 1
//=========================================================
/// @brief Verifica colisión bala contra OVNI 1
inline bool colisionBalaOvni1(int xBala, int yBala,
                       int xOvni, int yOvni)
{
    if(xBala >= xOvni - MARGEN_PRECISION &&
       xBala <= xOvni + ANCHO_OVNI1 + MARGEN_PRECISION &&
       yBala >= yOvni - MARGEN_PRECISION &&
       yBala <= yOvni + ALTO_OVNI1 + MARGEN_PRECISION)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION BALA - OVNI 2
//=========================================================
/// @brief Verifica colisión bala contra OVNI 2
inline bool colisionBalaOvni2(int xBala, int yBala,
                       int xOvni, int yOvni)
{
    if(xBala >= xOvni - MARGEN_PRECISION &&
       xBala <= xOvni + ANCHO_OVNI2 + MARGEN_PRECISION &&
       yBala >= yOvni - MARGEN_PRECISION &&
       yBala <= yOvni + ALTO_OVNI2 + MARGEN_PRECISION)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION BALA - JEFE FINAL
//=========================================================
/// @brief Verifica colisión bala contra jefe final
inline bool colisionBalaJefeFinal(int xBala, int yBala,
                           int xJefe, int yJefe)
{
    if(xBala >= xJefe - MARGEN_PRECISION &&
       xBala <= xJefe + ANCHO_JEFE + MARGEN_PRECISION &&
       yBala >= yJefe - MARGEN_PRECISION &&
       yBala <= yJefe + ALTO_JEFE + MARGEN_PRECISION)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION JUGADOR - METEORITO 1
//=========================================================
/// @brief Verifica colisión jugador contra meteorito 1
inline bool colisionJugadorMeteorito1(int xJugador, int yJugador,
                               int xMeteorito, int yMeteorito)
{
    if(xJugador + ANCHO_JUGADOR >= xMeteorito &&
       xJugador <= xMeteorito + ANCHO_METEORITO1 &&
       yJugador + ALTO_JUGADOR >= yMeteorito &&
       yJugador <= yMeteorito + ALTO_METEORITO1)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION JUGADOR - METEORITO 2
//=========================================================
/// @brief Verifica colisión jugador contra meteorito 2
inline bool colisionJugadorMeteorito2(int xJugador, int yJugador,
                               int xMeteorito, int yMeteorito)
{
    if(xJugador + ANCHO_JUGADOR >= xMeteorito &&
       xJugador <= xMeteorito + ANCHO_METEORITO2 &&
       yJugador + ALTO_JUGADOR >= yMeteorito &&
       yJugador <= yMeteorito + ALTO_METEORITO2)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION JUGADOR - METEORITO 3
//=========================================================
/// @brief Verifica colisión jugador contra meteorito 3
inline bool colisionJugadorMeteorito3(int xJugador, int yJugador,
                               int xMeteorito, int yMeteorito)
{
    if(xJugador + ANCHO_JUGADOR >= xMeteorito &&
       xJugador <= xMeteorito + ANCHO_METEORITO3 &&
       yJugador + ALTO_JUGADOR >= yMeteorito &&
       yJugador <= yMeteorito + ALTO_METEORITO3)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION JUGADOR - OVNI 1
//=========================================================
/// @brief Verifica colisión jugador contra OVNI 1
inline bool colisionJugadorOvni1(int xJugador, int yJugador,
                          int xOvni, int yOvni)
{
    if(xJugador + ANCHO_JUGADOR >= xOvni &&
       xJugador <= xOvni + ANCHO_OVNI1 &&
       yJugador + ALTO_JUGADOR >= yOvni &&
       yJugador <= yOvni + ALTO_OVNI1)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION JUGADOR - OVNI 2
//=========================================================
/// @brief Verifica colisión jugador contra OVNI 2
inline bool colisionJugadorOvni2(int xJugador, int yJugador,
                          int xOvni, int yOvni)
{
    if(xJugador + ANCHO_JUGADOR >= xOvni &&
       xJugador <= xOvni + ANCHO_OVNI2 &&
       yJugador + ALTO_JUGADOR >= yOvni &&
       yJugador <= yOvni + ALTO_OVNI2)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION JUGADOR - BALA OVNI
//=========================================================
/// @brief Verifica colisión jugador contra bala de OVNI
inline bool colisionJugadorBalaOvni(int xJugador, int yJugador,
                             int xBala, int yBala)
{
    if(xBala >= xJugador &&
       xBala <= xJugador + ANCHO_JUGADOR &&
       yBala >= yJugador &&
       yBala <= yJugador + ALTO_JUGADOR)
    {
        return true;
    }
    return false;
}

//=========================================================
// COLISION JUGADOR - LASER JEFE
//=========================================================
/// @brief Verifica colisión jugador contra láser del jefe
inline bool colisionJugadorLaserJefe(int xJugador, int yJugador,
                              int xLaser, int yLaser)
{
    if(xLaser >= xJugador &&
       xLaser <= xJugador + ANCHO_JUGADOR &&
       yLaser >= yJugador &&
       yLaser <= yJugador + ALTO_JUGADOR)
    {
        return true;
    }
    return false;
}

} // namespace InvasionEspacial
