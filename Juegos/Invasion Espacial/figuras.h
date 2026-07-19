#ifndef FIGURAS_H
#define FIGURAS_H
//=========================================================
// NAVE DEL JUGADOR (OFICIAL)
//=========================================================
#include <iostream>
#include "consola2.h"

using namespace std;

void dibujarJugador(int x, int y)
{
    color(11); // Celeste

    gotoxy(x, y);      imprimir("                    /|\\                    ");
    gotoxy(x, y + 1);  imprimir("                   /===\\                   ");
    gotoxy(x, y + 2);  imprimir("                  /=====\\                  ");
    gotoxy(x, y + 3);  imprimir("                 /.-----.\\                 ");
    gotoxy(x, y + 4);  imprimir("                / | :|: | \\                ");
    gotoxy(x, y + 5);  imprimir("               /  | :|: |  \\               ");
    gotoxy(x, y + 6);  imprimir("              / .## :|: ##. \\              ");
    gotoxy(x, y + 7);  imprimir("             /==.## :|: ##.==\\             ");
    gotoxy(x, y + 8);  imprimir("            /| : ## :|: ## : |\\            ");
    gotoxy(x, y + 9);  imprimir("           / | : #\\ :|: /# : | \\           ");
    gotoxy(x, y +10);  imprimir("          /  | :  |===|  : |  \\            ");
    gotoxy(x, y +11);  imprimir("    .----/---| :  |   |  : |---\\----.      ");
    gotoxy(x, y +12);  imprimir("   /    ( )  | :  |   |  : |  ( )    \\     ");
    gotoxy(x, y +13);  imprimir("  /______    |____|___|____|    ______\\    ");
    gotoxy(x, y +14);  imprimir(" /       |---|    |   |    |---|       \\   ");
    gotoxy(x, y +15);  imprimir("|        |   |    |   |    |   |        |  ");
    gotoxy(x, y +16);  imprimir("|________|---|___\\\\_=_//___|---|________|  ");
    gotoxy(x, y +17);  imprimir(" \\______/    |   |     |   |    \\______/   ");
    gotoxy(x, y +18);  imprimir("       .=====.   |/=====\\|   .=====.       ");
    gotoxy(x, y +19);  imprimir("       /###\\      /#####\\      /###\\       ");
    gotoxy(x, y +20);  imprimir("       |===|      (%%%%%)      |===|       ");
    gotoxy(x, y +21);  imprimir("       :###:      ;%%%%%;      :###:       ");
    gotoxy(x, y +22);  imprimir("       .##.        :#:#:        .##.       ");
}
//=========================================================
// BORRAR NAVE DEL JUGADOR
//=========================================================
void borrarJugador(int x, int y)
{
    for(int i = 0; i < 23; i++)
    {
        gotoxy(x, y + i);
        imprimir("                                             ");
    }
}
//=========================================================
// METEORITO 1 (PEQUEÑO)
//=========================================================
void dibujarMeteorito1(int x, int y)
{
    color(8); // Gris

    gotoxy(x, y);     imprimir("      ^^      ");
    gotoxy(x, y + 1); imprimir("     ^^^      ");
    gotoxy(x, y + 2); imprimir("    .###.     ");
    gotoxy(x, y + 3); imprimir("  .######.    ");
    gotoxy(x, y + 4); imprimir(" ####O####    ");
    gotoxy(x, y + 5); imprimir("###########   ");
    gotoxy(x, y + 6); imprimir("###O#####O#   ");
    gotoxy(x, y + 7); imprimir(" #########    ");
    gotoxy(x, y + 8); imprimir("  .#####.     ");
    gotoxy(x, y + 9); imprimir("    ###       ");
    
    color(15);
}

void borrarMeteorito1(int x, int y)
{
    for(int i = 0; i < 10; i++)
    {
        gotoxy(x, y + i);
        imprimir("               ");
    }
}
//=========================================================
// METEORITO 2 (MEDIANO)
//=========================================================
void dibujarMeteorito2(int x, int y)
{
    color(8);

    gotoxy(x, y);      imprimir("        ^^^        ");
    gotoxy(x, y + 1);  imprimir("      ^^^^^^^      ");
    gotoxy(x, y + 2);  imprimir("     .######.      ");
    gotoxy(x, y + 3);  imprimir("  .###########.    ");
    gotoxy(x, y + 4);  imprimir(" ####O######O###   ");
    gotoxy(x, y + 5);  imprimir("#################  ");
    gotoxy(x, y + 6);  imprimir("###O###########O#  ");
    gotoxy(x, y + 7);  imprimir("#################  ");
    gotoxy(x, y + 8);  imprimir(" ######O######     ");
    gotoxy(x, y + 9);  imprimir("   ##########      ");
    gotoxy(x, y +10);  imprimir("     ######        ");
    
    color(15);
}

void borrarMeteorito2(int x, int y)
{
    for(int i = 0; i < 11; i++)
    {
        gotoxy(x, y + i);
        imprimir("                    ");
    }
}
//=========================================================
// METEORITO 3 (GIGANTE)
//=========================================================
void dibujarMeteorito3(int x, int y)
{
    color(8);

    gotoxy(x, y);      imprimir("         ^^^^^         ");
    gotoxy(x, y + 1);  imprimir("       ^^^^^^^^^       ");
    gotoxy(x, y + 2);  imprimir("      ^^^^^^^^^^^      ");
    gotoxy(x, y + 3);  imprimir("     .#########.       ");
    gotoxy(x, y + 4);  imprimir("  .###############.    ");
    gotoxy(x, y + 5);  imprimir("#####################  ");
    gotoxy(x, y + 6);  imprimir("###O#############O###  ");
    gotoxy(x, y + 7);  imprimir("#####################  ");
    gotoxy(x, y + 8);  imprimir("#####O#########O#####  ");
    gotoxy(x, y + 9);  imprimir("#####################  ");
    gotoxy(x, y +10);  imprimir("  #################    ");
    gotoxy(x, y +11);  imprimir("     ###########       ");
    gotoxy(x, y +12);  imprimir("       #######         ");
    
    color(15);
}

void borrarMeteorito3(int x, int y)
{
    for(int i = 0; i < 13; i++)
    {
        gotoxy(x, y + i);
        imprimir("                         ");
    }
}
//=========================================================
// OVNI TIPO 1 (OFICIAL)
//=========================================================
void dibujarOvni1(int x, int y)
{
    color(12);   // Rojo

    gotoxy(x,y);   imprimir("         .------.         ");
    gotoxy(x,y+1); imprimir("      _.'  ||  `._        ");
    gotoxy(x,y+2); imprimir("    .'  _(_)(_)_  `.      ");
    gotoxy(x,y+3); imprimir(" .-=================-.    ");
    gotoxy(x,y+4); imprimir(" | (*) (*) (*) (*) |      ");
    gotoxy(x,y+5); imprimir(" |_________________|      ");
    gotoxy(x,y+6); imprimir("  `._ *********** _.'      ");
    gotoxy(x,y+7); imprimir("     `-----------'        ");
    gotoxy(x,y+8); imprimir("      / /     \\ \\        ");
    gotoxy(x,y+9); imprimir("     V_/       \\_V       ");
    
    color(15);
}
//=========================================================
// BORRAR OVNI TIPO 1
//=========================================================
void borrarOvni1(int x,int y)
{
    for(int i=0;i<10;i++)
    {
        gotoxy(x,y+i);
        imprimir("                            ");
    }
}
//=========================================================
// OVNI TIPO 2 (OFICIAL)
//=========================================================
void dibujarOvni2(int x,int y)
{
    color(12); // Rojo

    gotoxy(x,y);      imprimir("              .------------.              ");
    gotoxy(x,y+1);    imprimir("         _.-'   /||||\\\\   `-._          ");
    gotoxy(x,y+2);    imprimir("      .-'  _.-==========-._  `  -.       ");
    gotoxy(x,y+3);    imprimir("    .'  .-'##############`-.     `.      ");
    gotoxy(x,y+4);    imprimir(" __/===|  (@)  (@)  (@)  (@) |===\\\\__  ");
    gotoxy(x,y+5);    imprimir("|======|______________________|======| ");
    gotoxy(x,y+6);    imprimir("|===[###]====  ********  ====[###]===|    ");
    gotoxy(x,y+7);    imprimir("|____________________________________|    ");
    gotoxy(x,y+8);    imprimir(" \\\\_____.------------------._____/    ");
    gotoxy(x,y+9);    imprimir("      /==/   /========\\\\   \\\\==\\\\     ");
    gotoxy(x,y+10);   imprimir("     /__/___/__________\\\\___\\\\__\\\\    ");
    gotoxy(x,y+11);   imprimir("      <VVV>               <VVV>          ");
    gotoxy(x,y+12);   imprimir("       ||||                ||||         ");
    gotoxy(x,y+13);   imprimir("       ^^ ^^              ^^ ^^         ");
    
    color(15);
}
//=========================================================
// BORRAR OVNI TIPO 2
//=========================================================
void borrarOvni2(int x,int y)
{
    for(int i=0;i<14;i++)
    {
        gotoxy(x,y+i);
        imprimir("                                              ");
    }
}
//=========================================================
// NAVE NODRIZA (JEFE FINAL)
//=========================================================
void dibujarJefeFinal(int x, int y)
{
    color(13);   // Magenta

	gotoxy(x, y);     imprimir("                  .------------.                  "); 
    gotoxy(x, y + 1); imprimir("              _.-'   /||||\\\\   `-._              ");
    gotoxy(x, y + 2); imprimir("           .-'  _.-==========-._  `-.           "); 
    gotoxy(x, y + 3); imprimir("         .'  .-' ################ `-.  `.       "); 
    gotoxy(x, y + 4); imprimir("       .'  .' #################### `.  `.     "); 
    gotoxy(x, y + 5); imprimir("     _/====|   (@)  (@)  (@)  (@)   |===\\_     "); 
    gotoxy(x, y + 6); imprimir("    |======|________________________|======|    "); 
    gotoxy(x, y + 7); imprimir("    |===||||||||||||||||||||||||||||||||===|    "); 
    gotoxy(x, y + 8); imprimir("    |==[#####]===  **********  ===[#####]==|  "); 
    gotoxy(x, y + 9); imprimir("    |______________________________________|  "); 
    gotoxy(x, y + 10);imprimir("     \\_____   .------------------.   _____/   "); 
    gotoxy(x, y + 11);imprimir("           \\==\\  /============\\\\  /==/        "); 
    gotoxy(x, y + 12);imprimir("            \\==\\/______________\\\\/==/         "); 
    gotoxy(x, y + 13);imprimir("            /__/___/________\\\\___\\\\__\\        "); 
    gotoxy(x, y + 14);imprimir("             <VVV>              <VVV>             "); 
    gotoxy(x, y + 15);imprimir("              ||||              ||||              "); 
    gotoxy(x, y + 16);imprimir("              ||||              ||||              "); 
    gotoxy(x, y + 17);imprimir("              ~~~~              ~~~~              "); 
    gotoxy(x, y + 18);imprimir("              ^  ^              ^  ^              "); 
    
    color(15);
}
//=========================================================
// BORRAR NAVE NODRIZA
//=========================================================
void borrarJefeFinal(int x, int y)
{
    for(int i = 0; i < 19; i++)
    {
        gotoxy(x, y + i);
        imprimir("                                                            ");
    }
}
//=========================================================
// DISPARO DEL JUGADOR
//=========================================================
void dibujarBalaJugador(int x,int y)
{
    color(11); // Celeste

    gotoxy(x,y);     imprimir(" ^ ");
    gotoxy(x,y+1);   imprimir(" | ");
    gotoxy(x,y+2);   imprimir(" | ");
}
//=========================================================
// BORRAR DISPARO DEL JUGADOR
//=========================================================
void borrarBalaJugador(int x,int y)
{
    for(int i=0;i<3;i++)
    {
        gotoxy(x,y+i);
        imprimir("   ");
    }
}
//=========================================================
// DISPARO DEL OVNI
//=========================================================
void dibujarBalaOvni(int x,int y)
{
    color(12); // Rojo

    gotoxy(x,y);     imprimir(" * ");
    gotoxy(x,y+1);   imprimir("(@)");
    gotoxy(x,y+2);   imprimir(" * ");
}
//=========================================================
// BORRAR DISPARO DEL OVNI
//=========================================================
void borrarBalaOvni(int x,int y)
{
    for(int i=0;i<3;i++)
    {
        gotoxy(x,y+i);
        imprimir("   ");
    }
}
//=========================================================
// LASER DEL JEFE FINAL
//=========================================================
void dibujarLaserJefe(int x,int y)
{
    color(14); // Amarillo

    gotoxy(x,y);     imprimir("#####");
    gotoxy(x,y+1);   imprimir("|||||");
    gotoxy(x,y+2);   imprimir("|||||");
    gotoxy(x,y+3);   imprimir("|||||");
    gotoxy(x,y+4);   imprimir("#####");
}
//=========================================================
// BORRAR LASER DEL JEFE FINAL
//=========================================================
void borrarLaserJefe(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        imprimir("     ");
    }
}
//=========================================================
// EXPLOSION 1
//=========================================================
void dibujarExplosion1(int x,int y)
{
    color(14); // Amarillo

    gotoxy(x,y);     imprimir("   *   ");
    gotoxy(x,y+1);   imprimir("  ***  ");
    gotoxy(x,y+2);   imprimir(" ***** ");
    gotoxy(x,y+3);   imprimir("  ***  ");
    gotoxy(x,y+4);   imprimir("   *   ");
}
void borrarExplosion1(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        imprimir("       ");
    }
}
//=========================================================
// EXPLOSION 2
//=========================================================
void dibujarExplosion2(int x,int y)
{
    color(12); // Rojo

    gotoxy(x,y);     imprimir(" * * * ");
    gotoxy(x,y+1);   imprimir("*******");
    gotoxy(x,y+2);   imprimir("***@***");
    gotoxy(x,y+3);   imprimir("*******");
    gotoxy(x,y+4);   imprimir(" * * * ");
}
void borrarExplosion2(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        imprimir("       ");
    }
}
//=========================================================
// EXPLOSION 3
//=========================================================
void dibujarExplosion3(int x,int y)
{
    color(8); // Gris

    gotoxy(x,y);     imprimir("  .*.  ");
    gotoxy(x,y+1);   imprimir(" .*#*. ");
    gotoxy(x,y+2);   imprimir("*#%#*");
    gotoxy(x,y+3);   imprimir(" .*#*. ");
    gotoxy(x,y+4);   imprimir("  .*.  ");
}
void borrarExplosion3(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        imprimir("       ");
    }
}
//=========================================================
// VIDA (CORAZON)
//=========================================================
void dibujarVida(int x,int y)
{
    color(12); // Rojo

    gotoxy(x, y);     imprimir(" ##  ## ");
    gotoxy(x, y + 1); imprimir("########");
    gotoxy(x, y + 2); imprimir(" ###### ");
    gotoxy(x, y + 3); imprimir("  ####  ");
    gotoxy(x, y + 4); imprimir("   ##   ");
}
//=========================================================
// BORRAR VIDA
//=========================================================
void borrarVida(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        imprimir("        ");
    }
}
//=========================================================
// VIDA ROTA (CORAZON ROTO)
//=========================================================
void dibujarVidaRota(int x,int y)
{
    color(12); // Rojo

    gotoxy(x, y);     imprimir(" ##  ## ");
    gotoxy(x, y + 1); imprimir("### \\ ##");
    gotoxy(x, y + 2); imprimir(" ## \\ # ");
    gotoxy(x, y + 3); imprimir("  #  \\  ");
    gotoxy(x, y + 4); imprimir("   #    ");
}
//=========================================================
// BORRAR VIDA ROTA
//=========================================================
void borrarVidaRota(int x,int y)
{
    for(int i=0; i<5; i++)
    {
        gotoxy(x, y+i);
        imprimir("        ");
    }
}	
//=========================================================
// COPA DE VICTORIA (OFICIAL)
//=========================================================
void dibujarCopa(int x,int y)
{
    color(14); // Oro

    gotoxy(x, y + 0);  imprimir("|||||||||||||||||||||||||||||");
    gotoxy(x, y + 1);  imprimir("||                         ||");

    gotoxy(x, y + 2);  imprimir(" ||                       || ");
    gotoxy(x, y + 3);  imprimir("  ||     N U M B E R     ||  ");
    gotoxy(x, y + 4);  imprimir("   ||        #1         ||   ");
    gotoxy(x, y + 5);  imprimir("    ||                 ||    ");
    gotoxy(x, y + 6);  imprimir("     ||               ||     ");
    gotoxy(x, y + 7);  imprimir("      ||||         ||||      ");
    gotoxy(x, y + 8);  imprimir("        |||||||||||||        ");

    gotoxy(x - 4, y + 1); imprimir("_||||");
    gotoxy(x - 5, y + 2); imprimir("||");
    gotoxy(x - 5, y + 3); imprimir("||");
    gotoxy(x - 5, y + 4); imprimir("||");
    gotoxy(x - 4, y + 5); imprimir("¯||||");

    gotoxy(x + 28, y + 1); imprimir("||||_");
    gotoxy(x + 31, y + 2); imprimir("||");
    gotoxy(x + 31, y + 3); imprimir("||");
    gotoxy(x + 31, y + 4); imprimir("||");
    gotoxy(x + 28, y + 5); imprimir("||||¯");

    gotoxy(x, y + 9);   imprimir("           |||||             ");
    gotoxy(x, y +10);   imprimir("           |||||             ");
    gotoxy(x, y +11);   imprimir("           |||||             ");
    gotoxy(x, y +12);   imprimir("           |||||             ");
    gotoxy(x, y +13);   imprimir("          _|||||_            ");

    gotoxy(x, y +14);   imprimir("        _|||||||||_          ");
    gotoxy(x, y +15);   imprimir("      _|||||||||||||_        ");
    gotoxy(x, y +16);   imprimir("    |||||||||||||||||||      ");
    gotoxy(x, y +17);   imprimir("  |||||||||||||||||||||||    ");
    gotoxy(x, y +18);   imprimir("|||||||||||||||||||||||||||  ");
    gotoxy(x, y +19);   imprimir("¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯  ");
}
//=========================================================
// BORRAR COPA
//=========================================================
void borrarCopa(int x,int y)
{
    for(int i = 0; i < 20; i++)
    {
        gotoxy(x - 5, y + i);
        imprimir("                                          ");
    }
}
//=========================================================
// TITULO DEL JUEGO
//=========================================================
void dibujarTitulo()
{
    color(11);

    gotoxy(61,4);
    imprimir("/============================================================================\\");
    Sleep(60);

    gotoxy(69,6);
    imprimir(" _____ _   ___      __      _____  ____  _____  ______  _____ ");
    Sleep(45);

    gotoxy(69,7);
    imprimir("|_   _| \\ | \\ \\    / /\\    / ____|/ __ \\|  __ \\|  ____|/ ____|");
    Sleep(45);

    gotoxy(69,8);
    imprimir("  | | |  \\| |\\ \\  / /  \\  | (___ | |  | | |__) | |__  | (___  ");
    Sleep(45);

    gotoxy(69,9);
    imprimir("  | | | . ` | \\ \\/ / /\\ \\  \\___ \\| |  | |  _  /|  __|  \\___ \\ ");
    Sleep(45);

    gotoxy(69,10);
    imprimir(" _| |_| |\\  |  \\  / ____ \\ ____) | |__| | | \\ \\| |____ ____) |");
    Sleep(45);

    gotoxy(69,11);
    imprimir("|_____|_| \\_|   \\/_/    \\_\\_____/ \\____/|_|  \\_\\______|_____/ ");
    Sleep(45);

    Beep(700,100);

    color(14);
    gotoxy(64,12);
    imprimir("-------------------------------- < * > --------------------------------");
    Sleep(60);

    color(10);

    gotoxy(65,14);
    imprimir(" ______  _____ _____        _____ _____          _      ______  _____ ");
    Sleep(45);

    gotoxy(65,15);
    imprimir("|  ____|/ ____|  __ \\ /\\   / ____|_   _|   /\\   | |    |  ____|/ ____|");
    Sleep(45);

    gotoxy(65,16);
    imprimir("| |__  | (___ | |__) /  \\ | |      | |    /  \\  | |    | |__  | (___  ");
    Sleep(45);

    gotoxy(65,17);
    imprimir("|  __|  \\___ \\|  ___/ /\\ \\| |      | |   / /\\ \\ | |    |  __|  \\___ \\ ");
    Sleep(45);

    gotoxy(65,18);
    imprimir("| |____ ____) | |  / ____ \\ |____ _| |_ / ____ \\| |____| |____ ____) |");
    Sleep(45);

    gotoxy(65,19);
    imprimir("|______|_____/|_| /_/    \\_\\_____|_____/_/    \\_\\______|______|_____/ ");
    Sleep(45);

    color(10);
    gotoxy(61,21);
    imprimir("\\============================================================================/");
    Sleep(60);

    Beep(1000,250);

}
//=========================================================
// GAME OVER
//=========================================================

void gameOver(string usuario, int puntaje)
{
    system("cls");

    color(12);

    gotoxy(65,6);
    cout<<"/====================================================================\\";

    gotoxy(69,8);
    cout<<"  _____          __  __ ______    ______      ________ _____  ";

    gotoxy(69,9);
    cout<<" / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ ";

    gotoxy(69,10);
    cout<<"| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |";

    gotoxy(69,11);
    cout<<"| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / ";

    gotoxy(69,12);
    cout<<"| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ ";

    gotoxy(69,13);
    cout<<" \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\";

    gotoxy(65,14);
    cout<<"\\====================================================================/";

    color(15);

    gotoxy(63,18);
    cout<<"La invasion ha terminado";

    gotoxy(58,20);
    cout<<"La Tierra necesita otra oportunidad";

    gotoxy(63,23);
    cout<<"COMANDANTE: "<<usuario;

    color(14);
    gotoxy(63,25);
    cout<<"PUNTAJE FINAL: "<<puntaje;

    color(12);

    Beep(400,300);
    Beep(300,300);
    Beep(200,400);

    Sleep(2500);
}

void victoria(string usuario, int puntaje)
{
    system("cls");

    color(10);

    gotoxy(67,6);
    cout<<"/================================================================\\";

    gotoxy(71,8);
    cout<<"__      _______ _____ _______ ____  _____  _____          ";

    gotoxy(71,9);
    cout<<"\\ \\    / /_   _/ ____|__   __/ __ \\|  __ \\|_   _|   /\\    ";

    gotoxy(71,10);
    cout<<" \\ \\  / /  | || |       | | | |  | | |__) | | |    /  \\   ";

    gotoxy(71,11);
    cout<<"  \\ \\/ /   | || |       | | | |  | |  _  /  | |   / /\\ \\  ";

    gotoxy(71,12);
    cout<<"   \\  /   _| || |____   | | | |__| | | \\ \\ _| |_ / ____ \\ ";

    gotoxy(71,13);
    cout<<"    \\/   |_____\\_____|  |_|  \\____/|_|  \\_\\_____/_/    \\_\\";

    gotoxy(67,14);
    cout<<"\\================================================================/";

    color(15);

    gotoxy(66,18);
    cout<<"MISION COMPLETADA";

    gotoxy(60,20);
    cout<<"La galaxia esta a salvo";

    gotoxy(63,23);
    cout<<"COMANDANTE: "<<usuario;

    color(14);
    gotoxy(63,25);
    cout<<"PUNTAJE FINAL: "<<puntaje;

    color(10);

    gotoxy(58,28);
    cout<<"*** Presione una tecla para continuar ***";

    Beep(700,150);
    Beep(900,150);
    Beep(1200,300);

    getch();
}
#endif
