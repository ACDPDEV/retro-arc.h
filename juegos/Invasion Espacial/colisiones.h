#include <iostream>
#include "consola2.h"
#include "figuras.h"

using namespace std;

//=========================================================
// TAMAÑOS DE LAS FIGURAS
//=========================================================
const int ANCHO_JUGADOR = 40;
const int ALTO_JUGADOR = 17;

// Antes los 3 meteoritos compartian un unico tamaï¿½o (9x7), pero
// cada sprite es en realidad mas grande. Eso hacia que la bala
// solo detectara choque contra una esquina chiquita del dibujo,
// y la mayoria de los disparos que si tocaban visualmente al
// meteorito 2 o 3 no contaban como impacto.
const int ANCHO_METEORITO1 = 14;
const int ALTO_METEORITO1 = 10;

const int ANCHO_METEORITO2 = 19;
const int ALTO_METEORITO2 = 11;

const int ANCHO_METEORITO3 = 23;
const int ALTO_METEORITO3 = 13;

const int ANCHO_OVNI1 = 27;
const int ALTO_OVNI1 = 10;

const int ANCHO_OVNI2 = 44;
const int ALTO_OVNI2 = 14;

const int ANCHO_JEFE = 51;
const int ALTO_JEFE = 19;

// Margen extra de tolerancia para que un disparo que pasa MUY cerca
// del objetivo (pero no exactamente encima) tambien cuente como
// impacto. Mejora la sensacion de precision al disparar.
const int MARGEN_PRECISION = 4;
//=========================================================
// COLISION BALA - METEORITO 1
//=========================================================
bool colisionBalaMeteorito1(int xBala, int yBala,
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
bool colisionBalaMeteorito2(int xBala, int yBala,
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
bool colisionBalaMeteorito3(int xBala, int yBala,
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
bool colisionBalaOvni1(int xBala, int yBala,
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
bool colisionBalaOvni2(int xBala, int yBala,
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
bool colisionBalaJefeFinal(int xBala, int yBala,
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
bool colisionJugadorMeteorito1(int xJugador, int yJugador,
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
bool colisionJugadorMeteorito2(int xJugador, int yJugador,
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
bool colisionJugadorMeteorito3(int xJugador, int yJugador,
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
bool colisionJugadorOvni1(int xJugador, int yJugador,
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
bool colisionJugadorOvni2(int xJugador, int yJugador,
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
bool colisionJugadorBalaOvni(int xJugador, int yJugador,
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
bool colisionJugadorLaserJefe(int xJugador, int yJugador,
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
