/// @file juego.h
/// @brief Bucle principal y lógica del juego Invasion Espacial.
/// @details Game loop, initialization, HUD, collision response, level progression.
///          Uses Common::VirtualScreen for portable double buffering.
///          All functions in namespace InvasionEspacial.
#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../../Common/VirtualScreen.h"
#include "../../Common/Input.h"
#include "../../Common/Output.h"
#include "../../Common/Music.h"
#include "figuras.h"
#include "movimientos.h"
#include "disparos.h"
#include "colisiones.h"

using namespace std;

namespace InvasionEspacial {

//=========================================================
// VIRTUAL SCREEN GLOBAL
//=========================================================

/// @brief Buffer virtual global del juego (reemplaza HANDLE doble buffer Win32)
Common::VirtualScreen screen;

//=========================================================
// FUNCIONES DE PANTALLAS (declaraciones anticipadas)
//=========================================================

/// @brief Pantalla de victoria (definida en figuras.h)
/// @param usuario Nombre del jugador
/// @param puntaje Puntuación final
void victoria(string usuario, int puntaje);

/// @brief Pantalla de game over (definida en figuras.h)
/// @param usuario Nombre del jugador
/// @param puntaje Puntuación final
void gameOver(string usuario, int puntaje);

//=========================================================
// FUNCIONES AUXILIARES
//=========================================================

/// @brief Genera posición aleatoria para un meteorito
/// @return Columna aleatoria dentro del rango válido
inline int posicionAleatoriaMeteorito()
{
    return rand() % (Common::VS_WIDTH - 23 - 2) + 1;
}

/// @brief Genera posición aleatoria para OVNI 1
/// @return Columna aleatoria dentro del rango válido
inline int posicionAleatoriaOvni1()
{
    return rand() % (Common::VS_WIDTH - 27 - 2) + 1;
}

/// @brief Genera posición aleatoria para OVNI 2
/// @return Columna aleatoria dentro del rango válido
inline int posicionAleatoriaOvni2()
{
    return rand() % (Common::VS_WIDTH - 44 - 2) + 1;
}

/// @brief Genera posición aleatoria para el jefe final
/// @return Columna aleatoria dentro del rango válido
inline int posicionAleatoriaJefe()
{
    return rand() % (Common::VS_WIDTH - 51 - 2) + 1;
}

//=========================================================
// CONFIGURACIÓN DEL JUEGO
//=========================================================

/// @brief Vidas iniciales del jugador
const int VIDAS_INICIALES = 5;

/// @brief Puntos por destruir un meteorito
const int PUNTOS_METEORITO = 10;

/// @brief Puntos por destruir un OVNI tipo 1
const int PUNTOS_OVNI1 = 20;

/// @brief Puntos por destruir un OVNI tipo 2
const int PUNTOS_OVNI2 = 40;

/// @brief Puntos por dañar al jefe final
const int PUNTOS_JEFE = 100;

//=========================================================
// JUGADOR
//=========================================================

/// @brief Columna del jugador
int xJugador = 80;

/// @brief Fila del jugador
int yJugador = 42;

//=========================================================
// ESTADÍSTICAS
//=========================================================

/// @brief Vidas restantes
int vidas = VIDAS_INICIALES;

/// @brief Puntuación actual
int puntos = 0;

/// @brief Nivel actual
int nivel = 1;

//=========================================================
// METEORITOS
//=========================================================

int xMeteorito1;
int yMeteorito1;

bool explotandoMeteorito1 = false;
int  contadorExplosion1 = 0;

int xMeteorito2;
int yMeteorito2;

bool explotandoMeteorito2 = false;
int  contadorExplosion2 = 0;

int xMeteorito3;
int yMeteorito3;

bool explotandoMeteorito3 = false;
int  contadorExplosion3 = 0;

/// @brief Duración de la animación de explosión en frames
const int DURACION_EXPLOSION = 8;

//=========================================================
// OVNIS
//=========================================================

int xOvni1;
int yOvni1;

int xOvni2;
int yOvni2;

/// @brief Dirección horizontal del OVNI 1 (1=derecha, -1=izquierda)
int direccionOvni1 = 1;

/// @brief Dirección horizontal del OVNI 2 (1=derecha, -1=izquierda)
int direccionOvni2 = 1;

//=========================================================
// JEFE FINAL
//=========================================================

int xJefe;
int yJefe;

/// @brief Dirección horizontal del jefe (1=derecha, -1=izquierda)
int direccionJefe = 1;

//=========================================================
// DISPARO DEL JUGADOR
//=========================================================

int xBalaJugador;
int yBalaJugador;
bool disparandoJugador = false;

//=========================================================
// DISPAROS OVNI
//=========================================================

int xBalaOvni1;
int yBalaOvni1;
bool disparandoOvni1 = false;

int xBalaOvni2;
int yBalaOvni2;
bool disparandoOvni2 = false;

//=========================================================
// LASER DEL JEFE
//=========================================================

int xLaser1;
int yLaser1;

int xLaser2;
int yLaser2;

bool disparandoJefe = false;

//=========================================================
// VIDA DEL JEFE FINAL
//=========================================================

/// @brief Vidas iniciales del jefe final
const int VIDA_INICIAL_JEFE = 5;

/// @brief Vidas restantes del jefe
int vidaJefe = VIDA_INICIAL_JEFE;

//=========================================================
// INVULNERABILIDAD TEMPORAL DEL JUGADOR
//=========================================================

bool invulnerable = false;
int contadorInvulnerable = 0;

/// @brief Duración de la invulnerabilidad en frames
const int DURACION_INVULNERABILIDAD = 20;

//=========================================================
// ESTADO DEL JUEGO
//=========================================================

bool juegoTerminado = false;
bool juegoVictoria = false;

//=========================================================
// INICIALIZAR JUEGO
//=========================================================
/// @brief Inicializa todas las variables del juego para una nueva partida
inline void inicializarJuego()
{
    srand(time(NULL));

    xJugador = 80;
    yJugador = 42;

    vidas = VIDAS_INICIALES;
    puntos = 0;
    nivel = 1;

    xMeteorito1 = posicionAleatoriaMeteorito();
    yMeteorito1 = -5;
    explotandoMeteorito1 = false;
    contadorExplosion1 = 0;

    xMeteorito2 = posicionAleatoriaMeteorito();
    yMeteorito2 = -20;
    explotandoMeteorito2 = false;
    contadorExplosion2 = 0;

    xMeteorito3 = posicionAleatoriaMeteorito();
    yMeteorito3 = -35;
    explotandoMeteorito3 = false;
    contadorExplosion3 = 0;

    xOvni1 = posicionAleatoriaOvni1();
    yOvni1 = -40;

    xOvni2 = posicionAleatoriaOvni2();
    yOvni2 = -70;

    xJefe = posicionAleatoriaJefe();
    yJefe = -120;

    disparandoJugador = false;
    xBalaJugador = 0;
    yBalaJugador = 0;

    disparandoOvni1 = false;
    xBalaOvni1 = 0;
    yBalaOvni1 = 0;

    disparandoOvni2 = false;
    xBalaOvni2 = 0;
    yBalaOvni2 = 0;

    disparandoJefe = false;
    xLaser1 = 0;
    yLaser1 = 0;
    xLaser2 = 0;
    yLaser2 = 0;

    vidaJefe = VIDA_INICIAL_JEFE;

    invulnerable = false;
    contadorInvulnerable = 0;

    juegoTerminado = false;
    juegoVictoria = false;
}

//=========================================================
// MOSTRAR HUD
//=========================================================
/// @brief Dibuja la interfaz de usuario (borde, vidas, puntos, nivel)
inline void mostrarHUD()
{
    Common::VirtualScreenSetColor(screen, 11);

    // BORDE SUPERIOR
    Common::VirtualScreenSetCursor(screen, 0, 0);
    Common::VirtualScreenPrint(screen, "+");
    for(int i = 1; i < Common::VS_WIDTH - 1; i++)
        Common::VirtualScreenPrint(screen, "-");
    Common::VirtualScreenPrint(screen, "+");

    // BORDES LATERALES
    Common::VirtualScreenSetCursor(screen, 0, 1);
    Common::VirtualScreenPrint(screen, "|");
    Common::VirtualScreenSetCursor(screen, Common::VS_WIDTH - 1, 1);
    Common::VirtualScreenPrint(screen, "|");

    // BORDE INFERIOR
    Common::VirtualScreenSetCursor(screen, 0, 2);
    Common::VirtualScreenPrint(screen, "+");
    for(int i = 1; i < Common::VS_WIDTH - 1; i++)
        Common::VirtualScreenPrint(screen, "-");
    Common::VirtualScreenPrint(screen, "+");

    Common::VirtualScreenSetColor(screen, 15);

    // VIDAS
    Common::VirtualScreenSetCursor(screen, 3, 1);
    Common::VirtualScreenPrint(screen, "VIDAS:");

    if(vidas >= 1)
        dibujarVida(14, 0);
    if(vidas >= 2)
        dibujarVida(24, 0);
    if(vidas >= 3)
        dibujarVida(34, 0);
    if(vidas >= 4)
        dibujarVida(44, 0);
    if(vidas >= 5)
        dibujarVida(54, 0);

    // PUNTAJE
    Common::VirtualScreenSetCursor(screen, 80, 1);
    Common::VirtualScreenPrint(screen, "PUNTOS: ");
    Common::VirtualScreenPrint(screen, to_string(puntos));

    // NIVEL
    Common::VirtualScreenSetCursor(screen, 155, 1);
    Common::VirtualScreenPrint(screen, "NIVEL: ");
    Common::VirtualScreenPrint(screen, to_string(nivel));
}

//=========================================================
// VERIFICAR COLISIONES
//=========================================================
/// @brief Verifica todas las colisiones del juego y aplica efectos
inline void verificarColisiones()
{
    // BALA - METEORITO 1
    if(disparandoJugador &&
       !explotandoMeteorito1 &&
       colisionBalaMeteorito1(xBalaJugador, yBalaJugador, xMeteorito1, yMeteorito1))
    {
        puntos += PUNTOS_METEORITO;
        disparandoJugador = false;
        explotandoMeteorito1 = true;
        contadorExplosion1 = DURACION_EXPLOSION;
        Common::PlayAudio("Juegos/Invasion Espacial/Sounds/explosion_small.mp3");
    }

    // BALA - METEORITO 2
    if(disparandoJugador &&
       !explotandoMeteorito2 &&
       colisionBalaMeteorito2(xBalaJugador, yBalaJugador, xMeteorito2, yMeteorito2))
    {
        puntos += PUNTOS_METEORITO;
        disparandoJugador = false;
        explotandoMeteorito2 = true;
        contadorExplosion2 = DURACION_EXPLOSION;
        Common::PlayAudio("Juegos/Invasion Espacial/Sounds/explosion_med.mp3");
    }

    // BALA - METEORITO 3
    if(disparandoJugador &&
       !explotandoMeteorito3 &&
       colisionBalaMeteorito3(xBalaJugador, yBalaJugador, xMeteorito3, yMeteorito3))
    {
        puntos += PUNTOS_METEORITO;
        disparandoJugador = false;
        explotandoMeteorito3 = true;
        contadorExplosion3 = DURACION_EXPLOSION;
        Common::PlayAudio("Juegos/Invasion Espacial/Sounds/explosion_big.mp3");
    }

    // BALA - OVNI 1
    if(nivel >= 2 &&
       disparandoJugador &&
       colisionBalaOvni1(xBalaJugador, yBalaJugador, xOvni1, yOvni1))
    {
        puntos += PUNTOS_OVNI1;
        disparandoJugador = false;
        yOvni1 = -40;
        xOvni1 = posicionAleatoriaOvni1();
        Common::PlayAudio("Juegos/Invasion Espacial/Sounds/explosion_med.mp3");
    }

    // BALA - OVNI 2
    if(nivel >= 3 &&
       disparandoJugador &&
       colisionBalaOvni2(xBalaJugador, yBalaJugador, xOvni2, yOvni2))
    {
        puntos += PUNTOS_OVNI2;
        disparandoJugador = false;
        yOvni2 = -70;
        xOvni2 = posicionAleatoriaOvni2();
        Common::PlayAudio("Juegos/Invasion Espacial/Sounds/explosion_big.mp3");
    }

    // BALA - JEFE FINAL
    if(nivel >= 4 &&
       disparandoJugador &&
       colisionBalaJefeFinal(xBalaJugador, yBalaJugador, xJefe, yJefe))
    {
        puntos += PUNTOS_JEFE;
        disparandoJugador = false;
        vidaJefe--;

        if(vidaJefe <= 0)
        {
            juegoVictoria = true;
            Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_vlow.mp3");
        }
        else
        {
            Common::PlayAudio("Juegos/Invasion Espacial/Sounds/impact.mp3");
        }
    }

    //=====================================================
    // DAÑO AL JUGADOR (con invulnerabilidad temporal)
    //=====================================================

    if(!invulnerable)
    {
        bool golpeado = false;

        if(!explotandoMeteorito1 &&
           colisionJugadorMeteorito1(xJugador, yJugador, xMeteorito1, yMeteorito1))
        {
            golpeado = true;
            explotandoMeteorito1 = true;
            contadorExplosion1 = DURACION_EXPLOSION;
        }

        if(!explotandoMeteorito2 &&
           colisionJugadorMeteorito2(xJugador, yJugador, xMeteorito2, yMeteorito2))
        {
            golpeado = true;
            explotandoMeteorito2 = true;
            contadorExplosion2 = DURACION_EXPLOSION;
        }

        if(!explotandoMeteorito3 &&
           colisionJugadorMeteorito3(xJugador, yJugador, xMeteorito3, yMeteorito3))
        {
            golpeado = true;
            explotandoMeteorito3 = true;
            contadorExplosion3 = DURACION_EXPLOSION;
        }

        if(nivel >= 2 &&
           colisionJugadorOvni1(xJugador, yJugador, xOvni1, yOvni1))
        {
            golpeado = true;
            yOvni1 = -40;
            xOvni1 = posicionAleatoriaOvni1();
        }

        if(nivel >= 3 &&
           colisionJugadorOvni2(xJugador, yJugador, xOvni2, yOvni2))
        {
            golpeado = true;
            yOvni2 = -70;
            xOvni2 = posicionAleatoriaOvni2();
        }

        if(disparandoOvni1 &&
           colisionJugadorBalaOvni(xJugador, yJugador, xBalaOvni1, yBalaOvni1))
        {
            golpeado = true;
            disparandoOvni1 = false;
        }

        if(disparandoOvni2 &&
           colisionJugadorBalaOvni(xJugador, yJugador, xBalaOvni2, yBalaOvni2))
        {
            golpeado = true;
            disparandoOvni2 = false;
        }

        if(disparandoJefe &&
           (colisionJugadorLaserJefe(xJugador, yJugador, xLaser1, yLaser1) ||
            colisionJugadorLaserJefe(xJugador, yJugador, xLaser2, yLaser2)))
        {
            golpeado = true;
            disparandoJefe = false;
        }

        if(golpeado)
        {
            vidas--;
            invulnerable = true;
            contadorInvulnerable = DURACION_INVULNERABILIDAD;
            Common::PlayAudio("Juegos/Invasion Espacial/Sounds/alarm.mp3");
        }
    }
}

//=========================================================
// ACTUALIZAR EXPLOSIONES
//=========================================================
/// @brief Actualiza animaciones de explosión y reposiciona meteoritos
inline void actualizarExplosiones()
{
    if(explotandoMeteorito1)
    {
        dibujarExplosion1(xMeteorito1 + 3, yMeteorito1 + 2);
        contadorExplosion1--;

        if(contadorExplosion1 <= 0)
        {
            explotandoMeteorito1 = false;
            xMeteorito1 = posicionAleatoriaMeteorito();
            yMeteorito1 = -10;
        }
    }

    if(explotandoMeteorito2)
    {
        dibujarExplosion2(xMeteorito2 + 6, yMeteorito2 + 3);
        contadorExplosion2--;

        if(contadorExplosion2 <= 0)
        {
            explotandoMeteorito2 = false;
            xMeteorito2 = posicionAleatoriaMeteorito();
            yMeteorito2 = -20;
        }
    }

    if(explotandoMeteorito3)
    {
        dibujarExplosion3(xMeteorito3 + 8, yMeteorito3 + 4);
        contadorExplosion3--;

        if(contadorExplosion3 <= 0)
        {
            explotandoMeteorito3 = false;
            xMeteorito3 = posicionAleatoriaMeteorito();
            yMeteorito3 = -30;
        }
    }
}

//=========================================================
// ACTUALIZAR NIVEL
//=========================================================
/// @brief Actualiza el nivel según la puntuación
inline void actualizarNivel()
{
    if(puntos >= 500)
        nivel = 4;
    else if(puntos >= 250)
        nivel = 3;
    else if(puntos >= 100)
        nivel = 2;
    else
        nivel = 1;
}

//=========================================================
// ACTUALIZAR JUEGO
//=========================================================
/// @brief Actualiza todas las entidades del juego un frame
inline void actualizarJuego()
{
    // MOVIMIENTO JUGADOR
    moverJugador(xJugador, yJugador, xBalaJugador, yBalaJugador, disparandoJugador);

    // METEORITOS
    bool escapoMeteorito1 = false;
    bool escapoMeteorito2 = false;
    bool escapoMeteorito3 = false;

    if(!explotandoMeteorito1)
        moverMeteorito1(xMeteorito1, yMeteorito1, escapoMeteorito1);

    if(!explotandoMeteorito2)
        moverMeteorito2(xMeteorito2, yMeteorito2, escapoMeteorito2);

    if(!explotandoMeteorito3)
        moverMeteorito3(xMeteorito3, yMeteorito3, escapoMeteorito3);

    if(escapoMeteorito1 || escapoMeteorito2 || escapoMeteorito3)
        vidas--;

    // OVNI 1
    if(nivel >= 2)
    {
        moverOvni1(xOvni1, yOvni1, direccionOvni1);
        dispararOvni1(xOvni1, yOvni1, xBalaOvni1, yBalaOvni1, disparandoOvni1);
        moverBalaOvni1(xBalaOvni1, yBalaOvni1, disparandoOvni1);
    }

    // OVNI 2
    if(nivel >= 3)
    {
        moverOvni2(xOvni2, yOvni2, direccionOvni2);
        dispararOvni2(xOvni2, yOvni2, xBalaOvni2, yBalaOvni2, disparandoOvni2);
        moverBalaOvni2(xBalaOvni2, yBalaOvni2, disparandoOvni2);
    }

    // JEFE FINAL
    if(nivel >= 4)
    {
        moverJefe(xJefe, yJefe, direccionJefe);
        dispararJefeFinal(xJefe, yJefe, xLaser1, yLaser1, xLaser2, yLaser2, disparandoJefe);
        moverLaserJefe(xLaser1, yLaser1, xLaser2, yLaser2, disparandoJefe);
    }

    // BALA JUGADOR
    moverBalaJugador(xBalaJugador, yBalaJugador, disparandoJugador);

    // INVULNERABILIDAD TEMPORAL
    if(invulnerable)
    {
        contadorInvulnerable--;
        if(contadorInvulnerable <= 0)
            invulnerable = false;
    }
}

//=========================================================
// DIBUJAR JUEGO
//=========================================================
/// @brief Dibuja el estado actual del juego (HUD)
inline void dibujarJuego()
{
    mostrarHUD();
}

//=========================================================
// EJECUTAR JUEGO
//=========================================================
/// @brief Función principal que ejecuta el ciclo del juego
/// @param usuario Nombre del jugador
inline void ejecutarJuego(string usuario)
{
    Common::Clear();
    inicializarJuego();

    Common::VirtualScreenInit(screen);

    // CICLO PRINCIPAL
    while(vidas > 0 && !juegoVictoria)
    {
        Common::VirtualScreenClear(screen);

        actualizarJuego();
        verificarColisiones();
        actualizarExplosiones();
        actualizarNivel();
        dibujarJuego();

        Common::VirtualScreenPresent(screen);

        Common::Sleep(40);
    }

    Common::Clear();

    // FINAL DEL JUEGO
    if(juegoVictoria)
    {
        victoria(usuario, puntos);
    }
    else
    {
        gameOver(usuario, puntos);
    }
}

} // namespace InvasionEspacial
