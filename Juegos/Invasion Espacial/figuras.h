/// @file figuras.h
/// @brief Figuras del juego Invasion Espacial (sprites, explosiones, HUD).
/// @details Figuras draw functions using Common::VirtualScreen for portable
///          cross-platform rendering. All functions wrapped in namespace InvasionEspacial.
#pragma once

//=========================================================
// NAVE DEL JUGADOR (OFICIAL)
//=========================================================
#include <iostream>
#include <string>

#include "../../Common/VirtualScreen.h"
#include "../../Common/Output.h"
#include "../../Common/Music.h"

namespace InvasionEspacial {

extern Common::VirtualScreen screen;

/// @brief Dibuja la nave del jugador en la posición (x, y)
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarJugador(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 11); // Celeste

    Common::VirtualScreenSetCursor(screen, x, y);      Common::VirtualScreenPrint(screen, "                    /|\\                    ");
    Common::VirtualScreenSetCursor(screen, x, y + 1);  Common::VirtualScreenPrint(screen, "                   /===\\                   ");
    Common::VirtualScreenSetCursor(screen, x, y + 2);  Common::VirtualScreenPrint(screen, "                  /=====\\                  ");
    Common::VirtualScreenSetCursor(screen, x, y + 3);  Common::VirtualScreenPrint(screen, "                 /.-----.\\                 ");
    Common::VirtualScreenSetCursor(screen, x, y + 4);  Common::VirtualScreenPrint(screen, "                / | :|: | \\                ");
    Common::VirtualScreenSetCursor(screen, x, y + 5);  Common::VirtualScreenPrint(screen, "               /  | :|: |  \\               ");
    Common::VirtualScreenSetCursor(screen, x, y + 6);  Common::VirtualScreenPrint(screen, "              / .## :|: ##. \\              ");
    Common::VirtualScreenSetCursor(screen, x, y + 7);  Common::VirtualScreenPrint(screen, "             /==.## :|: ##.==\\             ");
    Common::VirtualScreenSetCursor(screen, x, y + 8);  Common::VirtualScreenPrint(screen, "            /| : ## :|: ## : |\\            ");
    Common::VirtualScreenSetCursor(screen, x, y + 9);  Common::VirtualScreenPrint(screen, "           / | : #\\ :|: /# : | \\           ");
    Common::VirtualScreenSetCursor(screen, x, y +10);  Common::VirtualScreenPrint(screen, "          /  | :  |===|  : |  \\            ");
    Common::VirtualScreenSetCursor(screen, x, y +11);  Common::VirtualScreenPrint(screen, "    .----/---| :  |   |  : |---\\----.      ");
    Common::VirtualScreenSetCursor(screen, x, y +12);  Common::VirtualScreenPrint(screen, "   /    ( )  | :  |   |  : |  ( )    \\     ");
    Common::VirtualScreenSetCursor(screen, x, y +13);  Common::VirtualScreenPrint(screen, "  /______    |____|___|____|    ______\\    ");
    Common::VirtualScreenSetCursor(screen, x, y +14);  Common::VirtualScreenPrint(screen, " /       |---|    |   |    |---|       \\   ");
    Common::VirtualScreenSetCursor(screen, x, y +15);  Common::VirtualScreenPrint(screen, "|        |   |    |   |    |   |        |  ");
    Common::VirtualScreenSetCursor(screen, x, y +16);  Common::VirtualScreenPrint(screen, "|________|---|___\\\\_=_//___|---|________|  ");
    Common::VirtualScreenSetCursor(screen, x, y +17);  Common::VirtualScreenPrint(screen, " \\______/    |   |     |   |    \\______/   ");
    Common::VirtualScreenSetCursor(screen, x, y +18);  Common::VirtualScreenPrint(screen, "       .=====.   |/=====\\|   .=====.       ");
    Common::VirtualScreenSetCursor(screen, x, y +19);  Common::VirtualScreenPrint(screen, "       /###\\      /#####\\      /###\\       ");
    Common::VirtualScreenSetCursor(screen, x, y +20);  Common::VirtualScreenPrint(screen, "       |===|      (%%%%%)      |===|       ");
    Common::VirtualScreenSetCursor(screen, x, y +21);  Common::VirtualScreenPrint(screen, "       :###:      ;%%%%%;      :###:       ");
    Common::VirtualScreenSetCursor(screen, x, y +22);  Common::VirtualScreenPrint(screen, "       .##.        :#:#:        .##.       ");
}

//=========================================================
// BORRAR NAVE DEL JUGADOR
//=========================================================
/// @brief Borra la nave del jugador escribiendo espacios
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarJugador(int x, int y)
{
    for(int i = 0; i < 23; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y + i);
        Common::VirtualScreenPrint(screen, "                                             ");
    }
}

//=========================================================
// METEORITO 1 (PEQUEÑO)
//=========================================================
/// @brief Dibuja un meteorito pequeño
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarMeteorito1(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 8); // Gris

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, "      ^^      ");
    Common::VirtualScreenSetCursor(screen, x, y + 1); Common::VirtualScreenPrint(screen, "     ^^^      ");
    Common::VirtualScreenSetCursor(screen, x, y + 2); Common::VirtualScreenPrint(screen, "    .###.     ");
    Common::VirtualScreenSetCursor(screen, x, y + 3); Common::VirtualScreenPrint(screen, "  .######.    ");
    Common::VirtualScreenSetCursor(screen, x, y + 4); Common::VirtualScreenPrint(screen, " ####O####    ");
    Common::VirtualScreenSetCursor(screen, x, y + 5); Common::VirtualScreenPrint(screen, "###########   ");
    Common::VirtualScreenSetCursor(screen, x, y + 6); Common::VirtualScreenPrint(screen, "###O#####O#   ");
    Common::VirtualScreenSetCursor(screen, x, y + 7); Common::VirtualScreenPrint(screen, " #########    ");
    Common::VirtualScreenSetCursor(screen, x, y + 8); Common::VirtualScreenPrint(screen, "  .#####.     ");
    Common::VirtualScreenSetCursor(screen, x, y + 9); Common::VirtualScreenPrint(screen, "    ###       ");

    Common::VirtualScreenSetColor(screen, 15);
}

/// @brief Borra un meteorito pequeño
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarMeteorito1(int x, int y)
{
    for(int i = 0; i < 10; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y + i);
        Common::VirtualScreenPrint(screen, "               ");
    }
}

//=========================================================
// METEORITO 2 (MEDIANO)
//=========================================================
/// @brief Dibuja un meteorito mediano
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarMeteorito2(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 8);

    Common::VirtualScreenSetCursor(screen, x, y);      Common::VirtualScreenPrint(screen, "        ^^^        ");
    Common::VirtualScreenSetCursor(screen, x, y + 1);  Common::VirtualScreenPrint(screen, "      ^^^^^^^      ");
    Common::VirtualScreenSetCursor(screen, x, y + 2);  Common::VirtualScreenPrint(screen, "     .######.      ");
    Common::VirtualScreenSetCursor(screen, x, y + 3);  Common::VirtualScreenPrint(screen, "  .###########.    ");
    Common::VirtualScreenSetCursor(screen, x, y + 4);  Common::VirtualScreenPrint(screen, " ####O######O###   ");
    Common::VirtualScreenSetCursor(screen, x, y + 5);  Common::VirtualScreenPrint(screen, "#################  ");
    Common::VirtualScreenSetCursor(screen, x, y + 6);  Common::VirtualScreenPrint(screen, "###O###########O#  ");
    Common::VirtualScreenSetCursor(screen, x, y + 7);  Common::VirtualScreenPrint(screen, "#################  ");
    Common::VirtualScreenSetCursor(screen, x, y + 8);  Common::VirtualScreenPrint(screen, " ######O######     ");
    Common::VirtualScreenSetCursor(screen, x, y + 9);  Common::VirtualScreenPrint(screen, "   ##########      ");
    Common::VirtualScreenSetCursor(screen, x, y +10);  Common::VirtualScreenPrint(screen, "     ######        ");

    Common::VirtualScreenSetColor(screen, 15);
}

/// @brief Borra un meteorito mediano
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarMeteorito2(int x, int y)
{
    for(int i = 0; i < 11; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y + i);
        Common::VirtualScreenPrint(screen, "                    ");
    }
}

//=========================================================
// METEORITO 3 (GIGANTE)
//=========================================================
/// @brief Dibuja un meteorito gigante
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarMeteorito3(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 8);

    Common::VirtualScreenSetCursor(screen, x, y);      Common::VirtualScreenPrint(screen, "         ^^^^^         ");
    Common::VirtualScreenSetCursor(screen, x, y + 1);  Common::VirtualScreenPrint(screen, "       ^^^^^^^^^       ");
    Common::VirtualScreenSetCursor(screen, x, y + 2);  Common::VirtualScreenPrint(screen, "      ^^^^^^^^^^^      ");
    Common::VirtualScreenSetCursor(screen, x, y + 3);  Common::VirtualScreenPrint(screen, "     .#########.       ");
    Common::VirtualScreenSetCursor(screen, x, y + 4);  Common::VirtualScreenPrint(screen, "  .###############.    ");
    Common::VirtualScreenSetCursor(screen, x, y + 5);  Common::VirtualScreenPrint(screen, "#####################  ");
    Common::VirtualScreenSetCursor(screen, x, y + 6);  Common::VirtualScreenPrint(screen, "###O#############O###  ");
    Common::VirtualScreenSetCursor(screen, x, y + 7);  Common::VirtualScreenPrint(screen, "#####################  ");
    Common::VirtualScreenSetCursor(screen, x, y + 8);  Common::VirtualScreenPrint(screen, "#####O#########O#####  ");
    Common::VirtualScreenSetCursor(screen, x, y + 9);  Common::VirtualScreenPrint(screen, "#####################  ");
    Common::VirtualScreenSetCursor(screen, x, y +10);  Common::VirtualScreenPrint(screen, "  #################    ");
    Common::VirtualScreenSetCursor(screen, x, y +11);  Common::VirtualScreenPrint(screen, "     ###########       ");
    Common::VirtualScreenSetCursor(screen, x, y +12);  Common::VirtualScreenPrint(screen, "       #######         ");

    Common::VirtualScreenSetColor(screen, 15);
}

/// @brief Borra un meteorito gigante
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarMeteorito3(int x, int y)
{
    for(int i = 0; i < 13; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y + i);
        Common::VirtualScreenPrint(screen, "                         ");
    }
}

//=========================================================
// OVNI TIPO 1 (OFICIAL)
//=========================================================
/// @brief Dibuja un OVNI tipo 1
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarOvni1(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 12);   // Rojo

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, "         .------.         ");
    Common::VirtualScreenSetCursor(screen, x, y+1);   Common::VirtualScreenPrint(screen, "      _.'  ||  `._        ");
    Common::VirtualScreenSetCursor(screen, x, y+2);   Common::VirtualScreenPrint(screen, "    .'  _(_)(_)_  `.      ");
    Common::VirtualScreenSetCursor(screen, x, y+3);   Common::VirtualScreenPrint(screen, " .-=================-.    ");
    Common::VirtualScreenSetCursor(screen, x, y+4);   Common::VirtualScreenPrint(screen, " | (*) (*) (*) (*) |      ");
    Common::VirtualScreenSetCursor(screen, x, y+5);   Common::VirtualScreenPrint(screen, " |_________________|      ");
    Common::VirtualScreenSetCursor(screen, x, y+6);   Common::VirtualScreenPrint(screen, "  `._ *********** _.'      ");
    Common::VirtualScreenSetCursor(screen, x, y+7);   Common::VirtualScreenPrint(screen, "     `-----------'        ");
    Common::VirtualScreenSetCursor(screen, x, y+8);   Common::VirtualScreenPrint(screen, "      / /     \\ \\        ");
    Common::VirtualScreenSetCursor(screen, x, y+9);   Common::VirtualScreenPrint(screen, "     V_/       \\_V       ");

    Common::VirtualScreenSetColor(screen, 15);
}

//=========================================================
// BORRAR OVNI TIPO 1
//=========================================================
/// @brief Borra un OVNI tipo 1
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarOvni1(int x, int y)
{
    for(int i = 0; i < 10; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "                            ");
    }
}

//=========================================================
// OVNI TIPO 2 (OFICIAL)
//=========================================================
/// @brief Dibuja un OVNI tipo 2
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarOvni2(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 12); // Rojo

    Common::VirtualScreenSetCursor(screen, x, y);      Common::VirtualScreenPrint(screen, "              .------------.              ");
    Common::VirtualScreenSetCursor(screen, x, y+1);    Common::VirtualScreenPrint(screen, "         _.-'   /||||\\\\   `-._          ");
    Common::VirtualScreenSetCursor(screen, x, y+2);    Common::VirtualScreenPrint(screen, "      .-'  _.-==========-._  `  -.       ");
    Common::VirtualScreenSetCursor(screen, x, y+3);    Common::VirtualScreenPrint(screen, "    .'  .-'##############`-.     `.      ");
    Common::VirtualScreenSetCursor(screen, x, y+4);    Common::VirtualScreenPrint(screen, " __/===|  (@)  (@)  (@)  (@) |===\\\\__  ");
    Common::VirtualScreenSetCursor(screen, x, y+5);    Common::VirtualScreenPrint(screen, "|======|______________________|======| ");
    Common::VirtualScreenSetCursor(screen, x, y+6);    Common::VirtualScreenPrint(screen, "|===[###]====  ********  ====[###]===|    ");
    Common::VirtualScreenSetCursor(screen, x, y+7);    Common::VirtualScreenPrint(screen, "|____________________________________|    ");
    Common::VirtualScreenSetCursor(screen, x, y+8);    Common::VirtualScreenPrint(screen, " \\\\_____.------------------._____/    ");
    Common::VirtualScreenSetCursor(screen, x, y+9);    Common::VirtualScreenPrint(screen, "      /==/   /========\\\\   \\\\==\\\\     ");
    Common::VirtualScreenSetCursor(screen, x, y+10);   Common::VirtualScreenPrint(screen, "     /__/___/__________\\\\___\\\\__\\\\    ");
    Common::VirtualScreenSetCursor(screen, x, y+11);   Common::VirtualScreenPrint(screen, "      <VVV>               <VVV>          ");
    Common::VirtualScreenSetCursor(screen, x, y+12);   Common::VirtualScreenPrint(screen, "       ||||                ||||         ");
    Common::VirtualScreenSetCursor(screen, x, y+13);   Common::VirtualScreenPrint(screen, "       ^^ ^^              ^^ ^^         ");

    Common::VirtualScreenSetColor(screen, 15);
}

//=========================================================
// BORRAR OVNI TIPO 2
//=========================================================
/// @brief Borra un OVNI tipo 2
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarOvni2(int x, int y)
{
    for(int i = 0; i < 14; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "                                              ");
    }
}

//=========================================================
// NAVE NODRIZA (JEFE FINAL)
//=========================================================
/// @brief Dibuja la nave nodriza (jefe final)
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarJefeFinal(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 13);   // Magenta

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, "                  .------------.                  ");
    Common::VirtualScreenSetCursor(screen, x, y + 1); Common::VirtualScreenPrint(screen, "              _.-'   /||||\\\\   `-._              ");
    Common::VirtualScreenSetCursor(screen, x, y + 2); Common::VirtualScreenPrint(screen, "           .-'  _.-==========-._  `-.           ");
    Common::VirtualScreenSetCursor(screen, x, y + 3); Common::VirtualScreenPrint(screen, "         .'  .-' ################ `-.  `.       ");
    Common::VirtualScreenSetCursor(screen, x, y + 4); Common::VirtualScreenPrint(screen, "       .'  .' #################### `.  `.     ");
    Common::VirtualScreenSetCursor(screen, x, y + 5); Common::VirtualScreenPrint(screen, "     _/====|   (@)  (@)  (@)  (@)   |===\\_     ");
    Common::VirtualScreenSetCursor(screen, x, y + 6); Common::VirtualScreenPrint(screen, "    |======|________________________|======|    ");
    Common::VirtualScreenSetCursor(screen, x, y + 7); Common::VirtualScreenPrint(screen, "    |===||||||||||||||||||||||||||||||||===|    ");
    Common::VirtualScreenSetCursor(screen, x, y + 8); Common::VirtualScreenPrint(screen, "    |==[#####]===  **********  ===[#####]==|  ");
    Common::VirtualScreenSetCursor(screen, x, y + 9); Common::VirtualScreenPrint(screen, "    |______________________________________|  ");
    Common::VirtualScreenSetCursor(screen, x, y + 10);Common::VirtualScreenPrint(screen, "     \\_____   .------------------.   _____/   ");
    Common::VirtualScreenSetCursor(screen, x, y + 11);Common::VirtualScreenPrint(screen, "           \\==\\  /============\\\\  /==/        ");
    Common::VirtualScreenSetCursor(screen, x, y + 12);Common::VirtualScreenPrint(screen, "            \\==\\/______________\\\\/==/         ");
    Common::VirtualScreenSetCursor(screen, x, y + 13);Common::VirtualScreenPrint(screen, "            /__/___/________\\\\___\\\\__\\        ");
    Common::VirtualScreenSetCursor(screen, x, y + 14);Common::VirtualScreenPrint(screen, "             <VVV>              <VVV>             ");
    Common::VirtualScreenSetCursor(screen, x, y + 15);Common::VirtualScreenPrint(screen, "              ||||              ||||              ");
    Common::VirtualScreenSetCursor(screen, x, y + 16);Common::VirtualScreenPrint(screen, "              ||||              ||||              ");
    Common::VirtualScreenSetCursor(screen, x, y + 17);Common::VirtualScreenPrint(screen, "              ~~~~              ~~~~              ");
    Common::VirtualScreenSetCursor(screen, x, y + 18);Common::VirtualScreenPrint(screen, "              ^  ^              ^  ^              ");

    Common::VirtualScreenSetColor(screen, 15);
}

//=========================================================
// BORRAR NAVE NODRIZA
//=========================================================
/// @brief Borra la nave nodriza
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarJefeFinal(int x, int y)
{
    for(int i = 0; i < 19; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y + i);
        Common::VirtualScreenPrint(screen, "                                                            ");
    }
}

//=========================================================
// DISPARO DEL JUGADOR
//=========================================================
/// @brief Dibuja la bala del jugador
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarBalaJugador(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 11); // Celeste

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, " ^ ");
    Common::VirtualScreenSetCursor(screen, x, y+1);   Common::VirtualScreenPrint(screen, " | ");
    Common::VirtualScreenSetCursor(screen, x, y+2);   Common::VirtualScreenPrint(screen, " | ");
}

//=========================================================
// BORRAR DISPARO DEL JUGADOR
//=========================================================
/// @brief Borra la bala del jugador
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarBalaJugador(int x, int y)
{
    for(int i = 0; i < 3; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "   ");
    }
}

//=========================================================
// DISPARO DEL OVNI
//=========================================================
/// @brief Dibuja la bala de un OVNI
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarBalaOvni(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 12); // Rojo

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, " * ");
    Common::VirtualScreenSetCursor(screen, x, y+1);   Common::VirtualScreenPrint(screen, "(@)");
    Common::VirtualScreenSetCursor(screen, x, y+2);   Common::VirtualScreenPrint(screen, " * ");
}

//=========================================================
// BORRAR DISPARO DEL OVNI
//=========================================================
/// @brief Borra la bala de un OVNI
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarBalaOvni(int x, int y)
{
    for(int i = 0; i < 3; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "   ");
    }
}

//=========================================================
// LASER DEL JEFE FINAL
//=========================================================
/// @brief Dibuja el láser del jefe final
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarLaserJefe(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 14); // Amarillo

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, "#####");
    Common::VirtualScreenSetCursor(screen, x, y+1);   Common::VirtualScreenPrint(screen, "|||||");
    Common::VirtualScreenSetCursor(screen, x, y+2);   Common::VirtualScreenPrint(screen, "|||||");
    Common::VirtualScreenSetCursor(screen, x, y+3);   Common::VirtualScreenPrint(screen, "|||||");
    Common::VirtualScreenSetCursor(screen, x, y+4);   Common::VirtualScreenPrint(screen, "#####");
}

//=========================================================
// BORRAR LASER DEL JEFE FINAL
//=========================================================
/// @brief Borra el láser del jefe final
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarLaserJefe(int x, int y)
{
    for(int i = 0; i < 5; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "     ");
    }
}

//=========================================================
// EXPLOSION 1
//=========================================================
/// @brief Dibuja explosión tipo 1
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarExplosion1(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 14); // Amarillo

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, "   *   ");
    Common::VirtualScreenSetCursor(screen, x, y+1);   Common::VirtualScreenPrint(screen, "  ***  ");
    Common::VirtualScreenSetCursor(screen, x, y+2);   Common::VirtualScreenPrint(screen, " ***** ");
    Common::VirtualScreenSetCursor(screen, x, y+3);   Common::VirtualScreenPrint(screen, "  ***  ");
    Common::VirtualScreenSetCursor(screen, x, y+4);   Common::VirtualScreenPrint(screen, "   *   ");
}

/// @brief Borra explosión tipo 1
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarExplosion1(int x, int y)
{
    for(int i = 0; i < 5; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "       ");
    }
}

//=========================================================
// EXPLOSION 2
//=========================================================
/// @brief Dibuja explosión tipo 2
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarExplosion2(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 12); // Rojo

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, " * * * ");
    Common::VirtualScreenSetCursor(screen, x, y+1);   Common::VirtualScreenPrint(screen, "*******");
    Common::VirtualScreenSetCursor(screen, x, y+2);   Common::VirtualScreenPrint(screen, "***@***");
    Common::VirtualScreenSetCursor(screen, x, y+3);   Common::VirtualScreenPrint(screen, "*******");
    Common::VirtualScreenSetCursor(screen, x, y+4);   Common::VirtualScreenPrint(screen, " * * * ");
}

/// @brief Borra explosión tipo 2
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarExplosion2(int x, int y)
{
    for(int i = 0; i < 5; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "       ");
    }
}

//=========================================================
// EXPLOSION 3
//=========================================================
/// @brief Dibuja explosión tipo 3
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarExplosion3(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 8); // Gris

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, "  .*.  ");
    Common::VirtualScreenSetCursor(screen, x, y+1);   Common::VirtualScreenPrint(screen, " .*#*. ");
    Common::VirtualScreenSetCursor(screen, x, y+2);   Common::VirtualScreenPrint(screen, "*#%#*");
    Common::VirtualScreenSetCursor(screen, x, y+3);   Common::VirtualScreenPrint(screen, " .*#*. ");
    Common::VirtualScreenSetCursor(screen, x, y+4);   Common::VirtualScreenPrint(screen, "  .*.  ");
}

/// @brief Borra explosión tipo 3
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarExplosion3(int x, int y)
{
    for(int i = 0; i < 5; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "       ");
    }
}

//=========================================================
// VIDA (CORAZON)
//=========================================================
/// @brief Dibuja un corazón de vida
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarVida(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 12); // Rojo

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, " ##  ## ");
    Common::VirtualScreenSetCursor(screen, x, y + 1); Common::VirtualScreenPrint(screen, "########");
    Common::VirtualScreenSetCursor(screen, x, y + 2); Common::VirtualScreenPrint(screen, " ###### ");
    Common::VirtualScreenSetCursor(screen, x, y + 3); Common::VirtualScreenPrint(screen, "  ####  ");
    Common::VirtualScreenSetCursor(screen, x, y + 4); Common::VirtualScreenPrint(screen, "   ##   ");
}

//=========================================================
// BORRAR VIDA
//=========================================================
/// @brief Borra un corazón de vida
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarVida(int x, int y)
{
    for(int i = 0; i < 5; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "        ");
    }
}

//=========================================================
// VIDA ROTA (CORAZON ROTO)
//=========================================================
/// @brief Dibuja un corazón roto
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarVidaRota(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 12); // Rojo

    Common::VirtualScreenSetCursor(screen, x, y);     Common::VirtualScreenPrint(screen, " ##  ## ");
    Common::VirtualScreenSetCursor(screen, x, y + 1); Common::VirtualScreenPrint(screen, "### \\ ##");
    Common::VirtualScreenSetCursor(screen, x, y + 2); Common::VirtualScreenPrint(screen, " ## \\ # ");
    Common::VirtualScreenSetCursor(screen, x, y + 3); Common::VirtualScreenPrint(screen, "  #  \\  ");
    Common::VirtualScreenSetCursor(screen, x, y + 4); Common::VirtualScreenPrint(screen, "   #    ");
}

//=========================================================
// BORRAR VIDA ROTA
//=========================================================
/// @brief Borra un corazón roto
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarVidaRota(int x, int y)
{
    for(int i = 0; i < 5; i++)
    {
        Common::VirtualScreenSetCursor(screen, x, y+i);
        Common::VirtualScreenPrint(screen, "        ");
    }
}

//=========================================================
// COPA DE VICTORIA (OFICIAL)
//=========================================================
/// @brief Dibuja la copa de victoria
/// @param x Columna inicial
/// @param y Fila inicial
inline void dibujarCopa(int x, int y)
{
    Common::VirtualScreenSetColor(screen, 14); // Oro

    Common::VirtualScreenSetCursor(screen, x, y + 0);  Common::VirtualScreenPrint(screen, "|||||||||||||||||||||||||||||");
    Common::VirtualScreenSetCursor(screen, x, y + 1);  Common::VirtualScreenPrint(screen, "||                         ||");

    Common::VirtualScreenSetCursor(screen, x, y + 2);  Common::VirtualScreenPrint(screen, " ||                       || ");
    Common::VirtualScreenSetCursor(screen, x, y + 3);  Common::VirtualScreenPrint(screen, "  ||     N U M B E R     ||  ");
    Common::VirtualScreenSetCursor(screen, x, y + 4);  Common::VirtualScreenPrint(screen, "   ||        #1         ||   ");
    Common::VirtualScreenSetCursor(screen, x, y + 5);  Common::VirtualScreenPrint(screen, "    ||                 ||    ");
    Common::VirtualScreenSetCursor(screen, x, y + 6);  Common::VirtualScreenPrint(screen, "     ||               ||     ");
    Common::VirtualScreenSetCursor(screen, x, y + 7);  Common::VirtualScreenPrint(screen, "      ||||         ||||      ");
    Common::VirtualScreenSetCursor(screen, x, y + 8);  Common::VirtualScreenPrint(screen, "        |||||||||||||        ");

    Common::VirtualScreenSetCursor(screen, x - 4, y + 1); Common::VirtualScreenPrint(screen, "_||||");
    Common::VirtualScreenSetCursor(screen, x - 5, y + 2); Common::VirtualScreenPrint(screen, "||");
    Common::VirtualScreenSetCursor(screen, x - 5, y + 3); Common::VirtualScreenPrint(screen, "||");
    Common::VirtualScreenSetCursor(screen, x - 5, y + 4); Common::VirtualScreenPrint(screen, "||");
    Common::VirtualScreenSetCursor(screen, x - 4, y + 5); Common::VirtualScreenPrint(screen, "||||");

    Common::VirtualScreenSetCursor(screen, x + 28, y + 1); Common::VirtualScreenPrint(screen, "||||_");
    Common::VirtualScreenSetCursor(screen, x + 31, y + 2); Common::VirtualScreenPrint(screen, "||");
    Common::VirtualScreenSetCursor(screen, x + 31, y + 3); Common::VirtualScreenPrint(screen, "||");
    Common::VirtualScreenSetCursor(screen, x + 31, y + 4); Common::VirtualScreenPrint(screen, "||");
    Common::VirtualScreenSetCursor(screen, x + 28, y + 5); Common::VirtualScreenPrint(screen, "||||");

    Common::VirtualScreenSetCursor(screen, x, y + 9);   Common::VirtualScreenPrint(screen, "           |||||             ");
    Common::VirtualScreenSetCursor(screen, x, y +10);   Common::VirtualScreenPrint(screen, "           |||||             ");
    Common::VirtualScreenSetCursor(screen, x, y +11);   Common::VirtualScreenPrint(screen, "           |||||             ");
    Common::VirtualScreenSetCursor(screen, x, y +12);   Common::VirtualScreenPrint(screen, "           |||||             ");
    Common::VirtualScreenSetCursor(screen, x, y +13);   Common::VirtualScreenPrint(screen, "          _|||||_            ");

    Common::VirtualScreenSetCursor(screen, x, y +14);   Common::VirtualScreenPrint(screen, "        _|||||||||_          ");
    Common::VirtualScreenSetCursor(screen, x, y +15);   Common::VirtualScreenPrint(screen, "      _|||||||||||||_        ");
    Common::VirtualScreenSetCursor(screen, x, y +16);   Common::VirtualScreenPrint(screen, "    |||||||||||||||||||      ");
    Common::VirtualScreenSetCursor(screen, x, y +17);   Common::VirtualScreenPrint(screen, "  |||||||||||||||||||||||    ");
    Common::VirtualScreenSetCursor(screen, x, y +18);   Common::VirtualScreenPrint(screen, "|||||||||||||||||||||||||||  ");
    Common::VirtualScreenSetCursor(screen, x, y +19);   Common::VirtualScreenPrint(screen, "|||||||||||||||||||||||||||  ");
}

//=========================================================
// BORRAR COPA
//=========================================================
/// @brief Borra la copa de victoria
/// @param x Columna inicial
/// @param y Fila inicial
inline void borrarCopa(int x, int y)
{
    for(int i = 0; i < 20; i++)
    {
        Common::VirtualScreenSetCursor(screen, x - 5, y + i);
        Common::VirtualScreenPrint(screen, "                                          ");
    }
}

//=========================================================
// TITULO DEL JUEGO (usa terminal directamente)
//=========================================================
/// @brief Dibuja el título del juego con efecto de escritura secuencial
inline void dibujarTitulo()
{
    Common::VirtualScreenSetColor(screen, 11);

    Common::VirtualScreenSetCursor(screen, 61, 4);
    Common::VirtualScreenPrint(screen, "/============================================================================\\");
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_mid.mp3");
    Common::Sleep(60);

    Common::VirtualScreenSetCursor(screen, 69, 6);
    Common::VirtualScreenPrint(screen, " _____ _   ___      __      _____  ____  _____  ______  _____ ");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 69, 7);
    Common::VirtualScreenPrint(screen, "|_   _| \\ | \\ \\    / /\\    / ____|/ __ \\|  __ \\|  ____|/ ____|");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 69, 8);
    Common::VirtualScreenPrint(screen, "  | | |  \\| |\\ \\  / /  \\  | (___ | |  | | |__) | |__  | (___  ");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 69, 9);
    Common::VirtualScreenPrint(screen, "  | | | . ` | \\ \\/ / /\\ \\  \\___ \\| |  | |  _  /|  __|  \\___ \\ ");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 69, 10);
    Common::VirtualScreenPrint(screen, " _| |_| |\\  |  \\  / ____ \\ ____) | |__| | | \\ \\| |____ ____) |");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 69, 11);
    Common::VirtualScreenPrint(screen, "|_____|_| \\_|   \\/_/    \\_\\_____/ \\____/|_|  \\_\\______|_____/ ");
    Common::Sleep(45);

    Common::VirtualScreenSetColor(screen, 14);
    Common::VirtualScreenSetCursor(screen, 64, 12);
    Common::VirtualScreenPrint(screen, "-------------------------------- < * > --------------------------------");
    Common::Sleep(60);

    Common::VirtualScreenSetColor(screen, 10);

    Common::VirtualScreenSetCursor(screen, 65, 14);
    Common::VirtualScreenPrint(screen, " ______  _____ _____        _____ _____          _      ______  _____ ");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 65, 15);
    Common::VirtualScreenPrint(screen, "|  ____|/ ____|  __ \\ /\\   / ____|_   _|   /\\   | |    |  ____|/ ____|");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 65, 16);
    Common::VirtualScreenPrint(screen, "| |__  | (___ | |__) /  \\ | |      | |    /  \\  | |    | |__  | (___  ");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 65, 17);
    Common::VirtualScreenPrint(screen, "|  __|  \\___ \\|  ___/ /\\ \\| |      | |   / /\\ \\ | |    |  __|  \\___ \\ ");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 65, 18);
    Common::VirtualScreenPrint(screen, "| |____ ____) | |  / ____ \\ |____ _| |_ / ____ \\| |____| |____ ____) |");
    Common::Sleep(45);

    Common::VirtualScreenSetCursor(screen, 65, 19);
    Common::VirtualScreenPrint(screen, "|______|_____/|_| /_/    \\_\\_____|_____/_/    \\_\\______|______|_____/ ");
    Common::Sleep(45);

    Common::VirtualScreenSetColor(screen, 10);
    Common::VirtualScreenSetCursor(screen, 61, 21);
    Common::VirtualScreenPrint(screen, "\\============================================================================/");
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_high.mp3");
    Common::Sleep(60);
}

//=========================================================
// GAME OVER (usa terminal directamente)
//=========================================================
/// @brief Muestra la pantalla de game over
/// @param usuario Nombre del jugador
/// @param puntaje Puntuación final
inline void gameOver(std::string usuario, int puntaje)
{
    Common::Clear();

    Common::GoToXY(65, 6);
    std::cout << "/====================================================================\\";

    Common::GoToXY(69, 8);
    std::cout << "  _____          __  __ ______    ______      ________ _____  ";

    Common::GoToXY(69, 9);
    std::cout << " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ";

    Common::GoToXY(69, 10);
    std::cout << "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |";

    Common::GoToXY(69, 11);
    std::cout << "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ";

    Common::GoToXY(69, 12);
    std::cout << "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ";

    Common::GoToXY(69, 13);
    std::cout << " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\";

    Common::GoToXY(65, 14);
    std::cout << "\\====================================================================/";

    std::cout << "\033[0m";

    Common::GoToXY(63, 18);
    std::cout << "La invasion ha terminado";

    Common::GoToXY(58, 20);
    std::cout << "La Tierra necesita otra oportunidad";

    Common::GoToXY(63, 23);
    std::cout << "COMANDANTE: " << usuario;

    std::cout << "\033[33m";
    Common::GoToXY(63, 25);
    std::cout << "PUNTAJE FINAL: " << puntaje;

    std::cout << "\033[0m";
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_low.mp3");
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_low.mp3");
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_vlow.mp3");
    Common::Sleep(2500);
}

//=========================================================
// VICTORIA (usa terminal directamente)
//=========================================================
/// @brief Muestra la pantalla de victoria
/// @param usuario Nombre del jugador
/// @param puntaje Puntuación final
inline void victoria(std::string usuario, int puntaje)
{
    Common::Clear();

    std::cout << "\033[32m";

    Common::GoToXY(67, 6);
    std::cout << "/================================================================\\";

    Common::GoToXY(71, 8);
    std::cout << "__      _______ _____ _______ ____  _____  _____          ";

    Common::GoToXY(71, 9);
    std::cout << "\\ \\    / /_   _/ ____|__   __/ __ \\|  __ \\|_   _|   /\\    ";

    Common::GoToXY(71, 10);
    std::cout << " \\ \\  / /  | || |       | | | |  | | |__) | | |    /  \\   ";

    Common::GoToXY(71, 11);
    std::cout << "  \\ \\/ /   | || |       | | | |  | |  _  /  | |   / /\\ \\  ";

    Common::GoToXY(71, 12);
    std::cout << "   \\  /   _| || |____   | | | |__| | | \\ \\ _| |_ / ____ \\ ";

    Common::GoToXY(71, 13);
    std::cout << "    \\/   |_____\\_____|  |_|  \\____/|_|  \\_\\_____/_/    \\_\\";

    Common::GoToXY(67, 14);
    std::cout << "\\================================================================/";

    std::cout << "\033[0m";

    Common::GoToXY(66, 18);
    std::cout << "MISION COMPLETADA";
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_mid.mp3");

    Common::GoToXY(60, 20);
    std::cout << "La galaxia esta a salvo";
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_high.mp3");

    Common::GoToXY(63, 23);
    std::cout << "COMANDANTE: " << usuario;

    std::cout << "\033[33m";
    Common::GoToXY(63, 25);
    std::cout << "PUNTAJE FINAL: " << puntaje;
    Common::PlayAudio("Juegos/Invasion Espacial/Sounds/beep_vhigh.mp3");

    std::cout << "\033[0m";

    Common::GoToXY(58, 28);
    std::cout << "*** Presione una tecla para continuar ***";

    Common::Getch();
}

//=========================================================
// FONDO ESPACIAL ANIMADO (usa terminal directamente)
//=========================================================
/// @brief Dibuja fondo de estrellas animado
inline void fondoEspacialAnimado()
{
    static bool creado = false;

    const int CANTIDAD_ESTRELLAS = 60;

    static int x[CANTIDAD_ESTRELLAS];
    static int y[CANTIDAD_ESTRELLAS];
    static bool brillo[CANTIDAD_ESTRELLAS];

    if(!creado)
    {
        srand(time(NULL));

        for(int i = 0; i < CANTIDAD_ESTRELLAS; i++)
        {
            x[i] = rand() % Common::VS_WIDTH;
            y[i] = rand() % Common::VS_HEIGHT;
            brillo[i] = rand() % 2;
        }

        creado = true;
    }

    for(int i = 0; i < CANTIDAD_ESTRELLAS; i++)
    {
        Common::GoToXY(x[i], y[i]);

        if(brillo[i])
        {
            std::cout << "\033[97m*\033[0m";
        }
        else
        {
            std::cout << "\033[90m.\033[0m";
        }

        if(rand() % 5 == 0)
        {
            brillo[i] = !brillo[i];
        }
    }
}

} // namespace InvasionEspacial
