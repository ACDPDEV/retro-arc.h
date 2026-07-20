/// @file pantallas.h
/// @brief Pantallas del menú y presentación de Invasion Espacial.
/// @details Menu screens, intro, credits, game over, victory.
///          Uses terminal directly (not VirtualScreen) for non-game screens.
///          All functions in namespace InvasionEspacial.
#pragma once

#include <iostream>
#include <string>

#include "../../Common/Input.h"
#include "../../Common/Terminal.h"
#include "../../Common/Output.h"
#include "../../Common/Music.h"
#include "figuras.h"

using namespace std;

namespace InvasionEspacial {

//=========================================================
// FUNCIONES DEL JUEGO (declaración anticipada)
//=========================================================

/// @brief Función principal del juego (definida en juego.h)
/// @param usuario Nombre del jugador
void ejecutarJuego(string usuario);

//=========================================================
// PRESENTACIÓN
//=========================================================
/// @brief Pantalla de presentación con barra de carga
inline void presentacion()
{
    Common::Clear();

    fondoEspacialAnimado();
    dibujarTitulo();

    std::cout << "\033[96m";
    Common::GoToXY(62, 28);
    std::cout << "CARGANDO SISTEMA ESPACIAL...";

    Common::Sleep(500);

    Common::GoToXY(65, 32);
    std::cout << "\033[0m[                    ]";

    for(int i = 0; i <= 20; i++)
    {
        Common::GoToXY(66 + i, 32);
        std::cout << "\033[32m|";

        Common::GoToXY(70, 34);
        std::cout << "\033[0m" << i * 5 << "%";

        Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_mid.mp3");
        Common::Sleep(80);
    }

    std::cout << "\033[32m";
    Common::GoToXY(75, 37);
    std::cout << "SISTEMA ONLINE";
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_high.mp3");

    std::cout << "\033[0m";
    Common::Sleep(1000);
}

//=========================================================
// SEGURIDAD - CLAVE DE ACCESO
//=========================================================
/// @brief Pantalla de ingreso de clave (3 intentos)
/// @return true si la clave es correcta
inline bool clave()
{
    string codigo;

    const int MAX_INTENTOS = 3;

    for(int intento = 1; intento <= MAX_INTENTOS; intento++)
    {
        Common::Clear();

        std::cout << "\033[96m";
        Common::GoToXY(55, 8);
        std::cout << "==========================================";
        Common::GoToXY(65, 10);
        std::cout << "CENTRO DE DEFENSA ESPACIAL";
        Common::GoToXY(55, 12);
        std::cout << "==========================================";

        std::cout << "\033[0m";
        Common::GoToXY(65, 17);
        std::cout << "INGRESE CLAVE DE ACCESO:";

        std::cout << "\033[33m";
        Common::GoToXY(65, 18);
        std::cout << "Intento " << intento << " de " << MAX_INTENTOS;

        std::cout << "\033[0m";
        Common::GoToXY(65, 20);
        std::cout << "> ";

        getline(cin, codigo);

        if(codigo == "1234")
        {
            return true;
        }

        if(intento < MAX_INTENTOS)
        {
            std::cout << "\033[31m";
            Common::GoToXY(65, 23);
            std::cout << "CLAVE INCORRECTA. INTENTELO DE NUEVO.";
            Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_low.mp3");

            std::cout << "\033[0m";
            Common::Sleep(1400);
        }
    }

    return false;
}

//=========================================================
// SOLICITAR NOMBRE DE USUARIO
//=========================================================
/// @brief Pantalla de solicitud de nombre de usuario
/// @return Nombre ingresado o "COMANDANTE" si está vacío
inline string solicitarUsuario()
{
    string usuario;

    Common::Clear();

    std::cout << "\033[96m";
    Common::GoToXY(55, 8);
    std::cout << "==========================================";
    Common::GoToXY(65, 10);
    std::cout << "IDENTIFICACION DEL COMANDANTE";
    Common::GoToXY(55, 12);
    std::cout << "==========================================";

    std::cout << "\033[0m";
    Common::GoToXY(65, 16);
    std::cout << "Ingrese nombre de usuario:";
    Common::GoToXY(65, 18);
    std::cout << "> ";

    getline(cin, usuario);

    if(usuario == "")
    {
        usuario = "COMANDANTE";
    }

    return usuario;
}

//=========================================================
// ACCESO CORRECTO
//=========================================================
/// @brief Pantalla de bienvenida con animación de nave
/// @param usuario Nombre del jugador
inline void bienvenida(string usuario)
{
    Common::Clear();

    std::cout << "\033[32m";
    Common::GoToXY(65, 6);
    std::cout << "ACCESO AUTORIZADO";

    std::cout << "\033[96m";
    Common::GoToXY(55, 9);
    std::cout << "BIENVENIDO COMANDANTE " << usuario;

    // Animación: nave llega volando
    Common::VirtualScreenInit(screen);

    int xNave;
    int yNave = 15;

    for(xNave = 20; xNave <= 80; xNave += 4)
    {
        if(xNave > 20)
        {
            for(int i = 0; i < 23; i++)
            {
                Common::VirtualScreenSetCursor(screen, xNave - 4, yNave + i);
                Common::VirtualScreenPrint(screen, "                                             ");
            }
        }

        dibujarJugador(xNave, yNave);

        Common::VirtualScreenPresent(screen);
        Common::Sleep(25);
    }

    Common::VirtualScreenClear(screen);
    Common::VirtualScreenPresent(screen);

    std::cout << "\033[0m";
    Common::GoToXY(55, 40);
    std::cout << "Preparando sistemas de combate...";
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_high.mp3");

    Common::Sleep(1500);
}

//=========================================================
// CLAVE INCORRECTA
//=========================================================
/// @brief Pantalla de acceso denegado
inline void claveIncorrecta()
{
    Common::Clear();

    std::cout << "\033[31m";
    Common::GoToXY(40, 13);
    std::cout << "+--------------------------------------------------------------+";
    Common::GoToXY(40, 14);
    std::cout << "|                                                                |";
    Common::GoToXY(40, 15);
    std::cout << "|   ACCESO DENEGADO                                             |";
    Common::GoToXY(40, 16);
    std::cout << "|                                                                |";
    Common::GoToXY(40, 17);
    std::cout << "|   Intento 3 veces ingresar con una clave incorrecta.          |";
    Common::GoToXY(40, 18);
    std::cout << "|   Comuniquese con el administrador.                          |";
    Common::GoToXY(40, 19);
    std::cout << "|                                                                |";
    Common::GoToXY(40, 20);
    std::cout << "+--------------------------------------------------------------+";

    std::cout << "\033[0m";
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_low.mp3");
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_vlow.mp3");
    Common::Sleep(2500);
}

//=========================================================
// INSTRUCCIONES
//=========================================================
/// @brief Pantalla de instrucciones del juego
inline void instrucciones()
{
    Common::Clear();

    std::cout << "\033[96m";
    Common::GoToXY(55, 5);
    std::cout << "==========================================";
    Common::GoToXY(68, 7);
    std::cout << "INSTRUCCIONES";
    Common::GoToXY(55, 9);
    std::cout << "==========================================";

    std::cout << "\033[0m";
    Common::GoToXY(60, 12);
    std::cout << "OBJETIVO:";
    Common::GoToXY(60, 14);
    std::cout << "Defiende la galaxia de la invasion";
    Common::GoToXY(60, 15);
    std::cout << "alienigena y meteoritos.";
    Common::GoToXY(60, 18);
    std::cout << "CONTROLES:";
    Common::GoToXY(60, 20);
    std::cout << "Movimiento  :  FLECHAS IZQ/DER";
    Common::GoToXY(60, 21);
    std::cout << "Disparo     :  ESPACIO";
    Common::GoToXY(60, 24);
    std::cout << "Destruye enemigos y consigue";
    Common::GoToXY(60, 25);
    std::cout << "la mayor puntuacion.";

    std::cout << "\033[32m";
    Common::GoToXY(65, 30);
    std::cout << "Presione una tecla para volver";

    Common::Getch();
}

//=========================================================
// CRÉDITOS
//=========================================================
/// @brief Pantalla de créditos
inline void creditos()
{
    Common::Clear();

    std::cout << "\033[96m";
    Common::GoToXY(55, 7);
    std::cout << "==========================================";
    Common::GoToXY(70, 9);
    std::cout << "CREDITOS";
    Common::GoToXY(55, 11);
    std::cout << "==========================================";

    std::cout << "\033[0m";
    Common::GoToXY(60, 15);
    std::cout << "INVASORES ESPACIALES";
    Common::GoToXY(60, 18);
    std::cout << "Proyecto Final";
    Common::GoToXY(60, 20);
    std::cout << "Algoritmos y programacion";
    Common::GoToXY(60, 23);
    std::cout << "Desarrollado por: VASQUEZ CHAVEZ YAMILLET";
    Common::GoToXY(60, 25);
    std::cout << "Equipo de desarrollo";

    std::cout << "\033[32m";
    Common::GoToXY(65, 30);
    std::cout << "Presione una tecla para volver";

    Common::Getch();
}

//=========================================================
// DESPEDIDA
//=========================================================
/// @brief Pantalla de despedida con animación de nave
/// @param usuario Nombre del jugador
inline void despedida(string usuario)
{
    Common::Clear();

    std::cout << "\033[96m";
    Common::GoToXY(55, 6);
    std::cout << "==========================================";
    Common::GoToXY(63, 8);
    std::cout << "MISION FINALIZADA";
    Common::GoToXY(55, 10);
    std::cout << "==========================================";

    std::cout << "\033[0m";
    Common::GoToXY(50, 13);
    std::cout << "Gracias por defender la galaxia, comandante " << usuario << ".";

    // Animación: nave se aleja
    Common::VirtualScreenInit(screen);

    int xNave;
    int yNave = 18;

    for(xNave = 80; xNave >= 10; xNave -= 4)
    {
        if(xNave < 80)
        {
            for(int i = 0; i < 23; i++)
            {
                Common::VirtualScreenSetCursor(screen, xNave + 4, yNave + i);
                Common::VirtualScreenPrint(screen, "                                             ");
            }
        }

        dibujarJugador(xNave, yNave);

        Common::VirtualScreenPresent(screen);
        Common::Sleep(25);
    }

    Common::VirtualScreenClear(screen);
    Common::VirtualScreenPresent(screen);

    std::cout << "\033[32m";
    Common::GoToXY(60, 45);
    std::cout << "Hasta la proxima mision, " << usuario << "...";

    std::cout << "\033[0m";
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_mid.mp3");
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_mid.mp3");
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_low.mp3");
    Common::Sleep(2000);
}

//=========================================================
// MENÚ (al final para que vea las declaraciones)
//=========================================================
/// @brief Menú principal del juego
/// @param usuario Nombre del jugador
inline void menu(string usuario)
{
    int opcion;

    do
    {
        Common::Clear();

        std::cout << "\033[96m";
        Common::GoToXY(55, 5);
        std::cout << "==========================================";
        Common::GoToXY(62, 7);
        std::cout << "INVASORES ESPACIALES";
        Common::GoToXY(55, 9);
        std::cout << "==========================================";

        std::cout << "\033[0m";
        Common::GoToXY(70, 13);
        std::cout << "1. INICIAR MISION";
        Common::GoToXY(70, 15);
        std::cout << "2. INSTRUCCIONES";
        Common::GoToXY(70, 17);
        std::cout << "3. CREDITOS";
        Common::GoToXY(70, 19);
        std::cout << "4. SALIR";

        std::cout << "\033[32m";
        Common::GoToXY(65, 23);
        std::cout << "Seleccione una opcion: ";

        cin >> opcion;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
        }
        else
        {
            cin.ignore();
        }

        switch(opcion)
        {
            case 1:
                std::cout << "\033[32m";
                Common::GoToXY(65, 27);
                std::cout << "INICIANDO MISION...";
                Common::Sleep(1000);
                ejecutarJuego(usuario);
                break;

            case 2:
                instrucciones();
                break;

            case 3:
                creditos();
                break;

            case 4:
                despedida(usuario);
                break;

            default:
                std::cout << "\033[31m";
                Common::GoToXY(65, 27);
                std::cout << "OPCION INVALIDA";
                Common::Sleep(1000);
        }

    } while(opcion != 4);
}

} // namespace InvasionEspacial

// Incluir juego.h al final para resolver la referencia a ejecutarJuego
#include "juego.h"
