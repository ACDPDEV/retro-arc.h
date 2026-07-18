#ifndef FIGURITAS_H
#define FIGURITAS_H
//=========================================================
// NAVE DEL JUGADOR (OFICIAL)
//=========================================================
#include <iostream>
#include "consola2.h"

using namespace std;

void dibujarJugador(int x, int y)
{
    color(11); // Celeste

    gotoxy(x, y);      cout << "                    /|\\                    ";
    gotoxy(x, y + 1);  cout << "                   /===\\                   ";
    gotoxy(x, y + 2);  cout << "                  /=====\\                  ";
    gotoxy(x, y + 3);  cout << "                 /.-----.\\                 ";
    gotoxy(x, y + 4);  cout << "                / | :|: | \\                ";
    gotoxy(x, y + 5);  cout << "               /  | :|: |  \\               ";
    gotoxy(x, y + 6);  cout << "              / .## :|: ##. \\              ";
    gotoxy(x, y + 7);  cout << "             /==.## :|: ##.==\\             ";
    gotoxy(x, y + 8);  cout << "            /| : ## :|: ## : |\\            ";
    gotoxy(x, y + 9);  cout << "           / | : #\\ :|: /# : | \\           ";
    gotoxy(x, y +10);  cout << "          /  | :  |===|  : |  \\            ";
    gotoxy(x, y +11);  cout << "    .----/---| :  |   |  : |---\\----.      ";
    gotoxy(x, y +12);  cout << "   /    ( )  | :  |   |  : |  ( )    \\     ";
    gotoxy(x, y +13);  cout << "  /______    |____|___|____|    ______\\    ";
    gotoxy(x, y +14);  cout << " /       |---|    |   |    |---|       \\   ";
    gotoxy(x, y +15);  cout << "|        |   |    |   |    |   |        |  ";
    gotoxy(x, y +16);  cout << "|________|---|___\\\\_=_//___|---|________|  ";
    gotoxy(x, y +17);  cout << " \\______/    |   |     |   |    \\______/   ";
    gotoxy(x, y +18);  cout << "       .=====.   |/=====\\|   .=====.       ";
    gotoxy(x, y +19);  cout << "       /###\\      /#####\\      /###\\       ";
    gotoxy(x, y +20);  cout << "       |===|      (%%%%%)      |===|       ";
    gotoxy(x, y +21);  cout << "       :###:      ;%%%%%;      :###:       ";
    gotoxy(x, y +22);  cout << "       .##.        :#:#:        .##.       ";
}
//=========================================================
// BORRAR NAVE DEL JUGADOR
//=========================================================
void borrarJugador(int x, int y)
{
    for(int i = 0; i < 23; i++)
    {
        gotoxy(x, y + i);
        cout << "                                             ";
    }
}
//=========================================================
// METEORITO 1 (PEQUEÑO)
//=========================================================
void dibujarMeteorito1(int x, int y)
{
    color(8); // Gris

    gotoxy(x, y);     cout << "      ^^      ";
    gotoxy(x, y + 1); cout << "     ^^^      ";
    gotoxy(x, y + 2); cout << "    .###.     ";
    gotoxy(x, y + 3); cout << "  .######.    ";
    gotoxy(x, y + 4); cout << " ####O####    ";
    gotoxy(x, y + 5); cout << "###########   ";
    gotoxy(x, y + 6); cout << "###O#####O#   ";
    gotoxy(x, y + 7); cout << " #########    ";
    gotoxy(x, y + 8); cout << "  .#####.     ";
    gotoxy(x, y + 9); cout << "    ###       ";
    
    color(15);
}

void borrarMeteorito1(int x, int y)
{
    for(int i = 0; i < 10; i++)
    {
        gotoxy(x, y + i);
        cout << "               ";
    }
}
//=========================================================
// METEORITO 2 (MEDIANO)
//=========================================================
void dibujarMeteorito2(int x, int y)
{
    color(8);

    gotoxy(x, y);      cout << "        ^^^        ";
    gotoxy(x, y + 1);  cout << "      ^^^^^^^      ";
    gotoxy(x, y + 2);  cout << "     .######.      ";
    gotoxy(x, y + 3);  cout << "  .###########.    ";
    gotoxy(x, y + 4);  cout << " ####O######O###   ";
    gotoxy(x, y + 5);  cout << "#################  ";
    gotoxy(x, y + 6);  cout << "###O###########O#  ";
    gotoxy(x, y + 7);  cout << "#################  ";
    gotoxy(x, y + 8);  cout << " ######O######     ";
    gotoxy(x, y + 9);  cout << "   ##########      ";
    gotoxy(x, y +10);  cout << "     ######        ";
    
    color(15);
}

void borrarMeteorito2(int x, int y)
{
    for(int i = 0; i < 11; i++)
    {
        gotoxy(x, y + i);
        cout << "                    ";
    }
}
//=========================================================
// METEORITO 3 (GIGANTE)
//=========================================================
void dibujarMeteorito3(int x, int y)
{
    color(8);

    gotoxy(x, y);      cout << "         ^^^^^         ";
    gotoxy(x, y + 1);  cout << "       ^^^^^^^^^       ";
    gotoxy(x, y + 2);  cout << "      ^^^^^^^^^^^      ";
    gotoxy(x, y + 3);  cout << "     .#########.       ";
    gotoxy(x, y + 4);  cout << "  .###############.    ";
    gotoxy(x, y + 5);  cout << "#####################  ";
    gotoxy(x, y + 6);  cout << "###O#############O###  ";
    gotoxy(x, y + 7);  cout << "#####################  ";
    gotoxy(x, y + 8);  cout << "#####O#########O#####  ";
    gotoxy(x, y + 9);  cout << "#####################  ";
    gotoxy(x, y +10);  cout << "  #################    ";
    gotoxy(x, y +11);  cout << "     ###########       ";
    gotoxy(x, y +12);  cout << "       #######         ";
    
    color(15);
}

void borrarMeteorito3(int x, int y)
{
    for(int i = 0; i < 13; i++)
    {
        gotoxy(x, y + i);
        cout << "                         ";
    }
}
//=========================================================
// OVNI TIPO 1 (OFICIAL)
//=========================================================
void dibujarOvni1(int x, int y)
{
    color(12);   // Rojo

    gotoxy(x,y);   cout<<"         .------.         ";
    gotoxy(x,y+1); cout<<"      _.'  ||  `._        ";
    gotoxy(x,y+2); cout<<"    .'  _(_)(_)_  `.      ";
    gotoxy(x,y+3); cout<<" .-=================-.    ";
    gotoxy(x,y+4); cout<<" | (*) (*) (*) (*) |      ";
    gotoxy(x,y+5); cout<<" |_________________|      ";
    gotoxy(x,y+6); cout<<"  `._ *********** _.'      ";
    gotoxy(x,y+7); cout<<"     `-----------'        ";
    gotoxy(x,y+8); cout<<"      / /     \\ \\        ";
    gotoxy(x,y+9); cout<<"     V_/       \\_V       ";
    
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
        cout<<"                            ";
    }
}
//=========================================================
// OVNI TIPO 2 (OFICIAL)
//=========================================================
void dibujarOvni2(int x,int y)
{
    color(12); // Rojo

    gotoxy(x,y);      cout<<"              .------------.              ";
    gotoxy(x,y+1);    cout<<"         _.-'   /||||\\\\   `-._          ";
    gotoxy(x,y+2);    cout<<"      .-'  _.-==========-._  `  -.       ";
    gotoxy(x,y+3);    cout<<"    .'  .-'##############`-.     `.      ";
    gotoxy(x,y+4);    cout<<" __/===|  (@)  (@)  (@)  (@) |===\\\\__  ";
    gotoxy(x,y+5);    cout<<"|======|______________________|======| ";
    gotoxy(x,y+6);    cout<<"|===[###]====  ********  ====[###]===|    ";
    gotoxy(x,y+7);    cout<<"|____________________________________|    ";
    gotoxy(x,y+8);    cout<<" \\\\_____.------------------._____/    ";
    gotoxy(x,y+9);    cout<<"      /==/   /========\\\\   \\\\==\\\\     ";
    gotoxy(x,y+10);   cout<<"     /__/___/__________\\\\___\\\\__\\\\    ";
    gotoxy(x,y+11);   cout<<"      <VVV>               <VVV>          ";
    gotoxy(x,y+12);   cout<<"       ||||                ||||         ";
    gotoxy(x,y+13);   cout<<"       ^^ ^^              ^^ ^^         ";
    
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
        cout<<"                                              ";
    }
}
//=========================================================
// NAVE NODRIZA (JEFE FINAL)
//=========================================================
void dibujarJefeFinal(int x, int y)
{
    color(13);   // Magenta

	gotoxy(x, y);     cout << "                  .------------.                  "; 
    gotoxy(x, y + 1); cout << "              _.-'   /||||\\\\   `-._              ";
    gotoxy(x, y + 2); cout << "           .-'  _.-==========-._  `-.           "; 
    gotoxy(x, y + 3); cout << "         .'  .-' ################ `-.  `.       "; 
    gotoxy(x, y + 4); cout << "       .'  .' #################### `.  `.     "; 
    gotoxy(x, y + 5); cout << "     _/====|   (@)  (@)  (@)  (@)   |===\\_     "; 
    gotoxy(x, y + 6); cout << "    |======|________________________|======|    "; 
    gotoxy(x, y + 7); cout << "    |===|¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦|===|    "; 
    gotoxy(x, y + 8); cout << "    |==[#####]===  **********  ===[#####]==|  "; 
    gotoxy(x, y + 9); cout << "    |______________________________________|  "; 
    gotoxy(x, y + 10);cout << "     \\_____   .------------------.   _____/   "; 
    gotoxy(x, y + 11);cout << "           \\==\\  /============\\\\  /==/        "; 
    gotoxy(x, y + 12);cout << "            \\==\\/______________\\\\/==/         "; 
    gotoxy(x, y + 13);cout << "            /__/___/________\\\\___\\\\__\\        "; 
    gotoxy(x, y + 14);cout << "             <VVV>              <VVV>             "; 
    gotoxy(x, y + 15);cout << "              ||||              ||||              "; 
    gotoxy(x, y + 16);cout << "              ||||              ||||              "; 
    gotoxy(x, y + 17);cout << "              ~~~~              ~~~~              "; 
    gotoxy(x, y + 18);cout << "              ^  ^              ^  ^              "; 
    
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
        cout << "                                                            ";
    }
}
//=========================================================
// DISPARO DEL JUGADOR
//=========================================================
void dibujarBalaJugador(int x,int y)
{
    color(11); // Celeste

    gotoxy(x,y);     cout<<" ^ ";
    gotoxy(x,y+1);   cout<<" | ";
    gotoxy(x,y+2);   cout<<" | ";
}
//=========================================================
// BORRAR DISPARO DEL JUGADOR
//=========================================================
void borrarBalaJugador(int x,int y)
{
    for(int i=0;i<3;i++)
    {
        gotoxy(x,y+i);
        cout<<"   ";
    }
}
//=========================================================
// DISPARO DEL OVNI
//=========================================================
void dibujarBalaOvni(int x,int y)
{
    color(12); // Rojo

    gotoxy(x,y);     cout<<" * ";
    gotoxy(x,y+1);   cout<<"(@)";
    gotoxy(x,y+2);   cout<<" * ";
}
//=========================================================
// BORRAR DISPARO DEL OVNI
//=========================================================
void borrarBalaOvni(int x,int y)
{
    for(int i=0;i<3;i++)
    {
        gotoxy(x,y+i);
        cout<<"   ";
    }
}
//=========================================================
// LASER DEL JEFE FINAL
//=========================================================
void dibujarLaserJefe(int x,int y)
{
    color(14); // Amarillo

    gotoxy(x,y);     cout<<"#####";
    gotoxy(x,y+1);   cout<<"|||||";
    gotoxy(x,y+2);   cout<<"|||||";
    gotoxy(x,y+3);   cout<<"|||||";
    gotoxy(x,y+4);   cout<<"#####";
}
//=========================================================
// BORRAR LASER DEL JEFE FINAL
//=========================================================
void borrarLaserJefe(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        cout<<"     ";
    }
}
//=========================================================
// EXPLOSION 1
//=========================================================
void dibujarExplosion1(int x,int y)
{
    color(14); // Amarillo

    gotoxy(x,y);     cout<<"   *   ";
    gotoxy(x,y+1);   cout<<"  ***  ";
    gotoxy(x,y+2);   cout<<" ***** ";
    gotoxy(x,y+3);   cout<<"  ***  ";
    gotoxy(x,y+4);   cout<<"   *   ";
}
void borrarExplosion1(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        cout<<"       ";
    }
}
//=========================================================
// EXPLOSION 2
//=========================================================
void dibujarExplosion2(int x,int y)
{
    color(12); // Rojo

    gotoxy(x,y);     cout<<" * * * ";
    gotoxy(x,y+1);   cout<<"*******";
    gotoxy(x,y+2);   cout<<"***@***";
    gotoxy(x,y+3);   cout<<"*******";
    gotoxy(x,y+4);   cout<<" * * * ";
}
void borrarExplosion2(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        cout<<"       ";
    }
}
//=========================================================
// EXPLOSION 3
//=========================================================
void dibujarExplosion3(int x,int y)
{
    color(8); // Gris

    gotoxy(x,y);     cout<<"  .*.  ";
    gotoxy(x,y+1);   cout<<" .*#*. ";
    gotoxy(x,y+2);   cout<<"*#%#*";
    gotoxy(x,y+3);   cout<<" .*#*. ";
    gotoxy(x,y+4);   cout<<"  .*.  ";
}
void borrarExplosion3(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(x,y+i);
        cout<<"       ";
    }
}
//=========================================================
// VIDA (CORAZON)
//=========================================================
void dibujarVida(int x,int y)
{
    color(12); // Rojo

	gotoxy(x, y);     cout << "  ####  ####   "; 
    gotoxy(x, y + 1); cout << " ############ "; 
    gotoxy(x, y + 2); cout << "##############";
    gotoxy(x, y + 3); cout << "  ########### "; 
    gotoxy(x, y + 4); cout << "    ######     "; 
    gotoxy(x, y + 5); cout << "      ###       "; 
    gotoxy(x, y + 6); cout << "       #        "; 
}
//=========================================================
// BORRAR VIDA
//=========================================================
void borrarVida(int x,int y)
{
    for(int i=0;i<7;i++)
    {
        gotoxy(x,y+i);
        cout<<"         ";
    }
}
//=========================================================
// VIDA ROTA (CORAZON ROTO)
//=========================================================
void dibujarVidaRota(int x,int y)
{
    color(12); // Rojo

    gotoxy(x, y);     cout << " ####   #### ";
    gotoxy(x, y + 1); cout << "###### \\\\ ######";
    gotoxy(x, y + 2); cout << "######## \\\\ ####";
    gotoxy(x, y + 3); cout << " ####### \\\\ ### ";
    gotoxy(x, y + 4); cout << "   ####  \\\\ ##  ";
    gotoxy(x, y + 5); cout << "     ##  //     ";
    gotoxy(x, y + 6); cout << "      #         ";
}
//=========================================================
// BORRAR VIDA ROTA
//=========================================================
void borrarVidaRota(int x,int y)
{
    for(int i=0; i<7; i++)
    {
        gotoxy(x, y+i);
        cout << "                ";
    }
}	
//=========================================================
// COPA DE VICTORIA (OFICIAL)
//=========================================================
void dibujarCopa(int x,int y)
{
    color(14); // Oro

    gotoxy(x, y + 0);  cout << "¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦";
    gotoxy(x, y + 1);  cout << "¦¦                         ¦¦";

    gotoxy(x, y + 2);  cout << " ¦¦                       ¦¦ ";
    gotoxy(x, y + 3);  cout << "  ¦¦     N U M B E R     ¦¦  ";
    gotoxy(x, y + 4);  cout << "   ¦¦        #1         ¦¦   ";
    gotoxy(x, y + 5);  cout << "    ¦¦                 ¦¦    ";
    gotoxy(x, y + 6);  cout << "     ¦¦               ¦¦     ";
    gotoxy(x, y + 7);  cout << "      ¦¦¦¦         ¦¦¦¦      ";
    gotoxy(x, y + 8);  cout << "        ¦¦¦¦¦¦¦¦¦¦¦¦¦        ";

    gotoxy(x - 4, y + 1); cout << "_¦¦¦¦";
    gotoxy(x - 5, y + 2); cout << "¦¦";
    gotoxy(x - 5, y + 3); cout << "¦¦";
    gotoxy(x - 5, y + 4); cout << "¦¦";
    gotoxy(x - 4, y + 5); cout << "¯¦¦¦¦";

    gotoxy(x + 28, y + 1); cout << "¦¦¦¦_";
    gotoxy(x + 31, y + 2); cout << "¦¦";
    gotoxy(x + 31, y + 3); cout << "¦¦";
    gotoxy(x + 31, y + 4); cout << "¦¦";
    gotoxy(x + 28, y + 5); cout << "¦¦¦¦¯";

    gotoxy(x, y + 9);   cout << "           ¦¦¦¦¦             ";
    gotoxy(x, y +10);   cout << "           ¦¦¦¦¦             ";
    gotoxy(x, y +11);   cout << "           ¦¦¦¦¦             ";
    gotoxy(x, y +12);   cout << "           ¦¦¦¦¦             ";
    gotoxy(x, y +13);   cout << "          _¦¦¦¦¦_            ";

    gotoxy(x, y +14);   cout << "        _¦¦¦¦¦¦¦¦¦_          ";
    gotoxy(x, y +15);   cout << "      _¦¦¦¦¦¦¦¦¦¦¦¦¦_        ";
    gotoxy(x, y +16);   cout << "    ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦      ";
    gotoxy(x, y +17);   cout << "  ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦    ";
    gotoxy(x, y +18);   cout << "¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦  ";
    gotoxy(x, y +19);   cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯  ";
}
//=========================================================
// BORRAR COPA
//=========================================================
void borrarCopa(int x,int y)
{
    for(int i = 0; i < 20; i++)
    {
        gotoxy(x - 5, y + i);
        cout << "                                          ";
    }
}
//=========================================================
// TITULO DEL JUEGO
//=========================================================
void dibujarTitulo()
{
color(11);

	gotoxy(42,8);
	cout << "¦¦+¦¦¦+   ¦¦+¦¦+   ¦¦+ ¦¦¦¦¦+ ¦¦¦¦¦¦¦+ ¦¦¦¦¦¦+ ¦¦¦¦¦¦+ ¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+";
	Sleep(80);

	gotoxy(42,9);
	cout << "¦¦¦¦¦¦¦+  ¦¦¦¦¦¦   ¦¦¦¦¦+--¦¦+¦¦+----+¦¦+---¦¦+¦¦+--¦¦+¦¦+----+¦¦+----+";
	Sleep(80);

	gotoxy(42,10);
	cout << "¦¦¦¦¦+¦¦+ ¦¦¦¦¦¦   ¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦¦+¦¦¦   ¦¦¦¦¦¦¦¦¦++¦¦¦¦¦+  ¦¦¦¦¦¦¦+";
	Sleep(80);

	gotoxy(42,11);
	cout << "¦¦¦¦¦¦+¦¦+¦¦¦+¦¦+ ¦¦++¦¦+--¦¦¦+----¦¦¦¦¦¦   ¦¦¦¦¦+--¦¦+¦¦+--+  +----¦¦¦";
	Sleep(80);

	gotoxy(42,12);
	cout << "¦¦¦¦¦¦ +¦¦¦¦¦ +¦¦¦¦++ ¦¦¦  ¦¦¦¦¦¦¦¦¦¦¦+¦¦¦¦¦¦++¦¦¦  ¦¦¦¦¦¦¦¦¦¦+¦¦¦¦¦¦¦¦";
	Sleep(80);

	gotoxy(42,13);
	cout << "+-++-+  +---+  +---+  +-+  +-++------+ +-----+ +-+  +-++------++------+";

	Beep(900,120);

	color(10);

	gotoxy(55,17);
	cout << "¦¦¦¦¦¦¦+¦¦¦¦¦¦+  ¦¦¦¦¦+  ¦¦¦¦¦¦+¦¦+ ¦¦¦¦¦+ ¦¦+     ¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+";
	Sleep(80);

	gotoxy(55,18);
	cout << "¦¦+----+¦¦+--¦¦+¦¦+--¦¦+¦¦+----+¦¦¦¦¦+--¦¦+¦¦¦     ¦¦+----+¦¦+----+";
	Sleep(80);

	gotoxy(55,19);
	cout << "¦¦¦¦¦+  ¦¦¦¦¦¦++¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦¦¦+  ¦¦¦¦¦¦¦+";
	Sleep(80);

	gotoxy(55,20);
	cout << "¦¦+--+  ¦¦+--¦¦+¦¦+--¦¦¦¦¦¦     ¦¦¦¦¦+--¦¦¦¦¦¦     ¦¦+--+  +----¦¦¦";
	Sleep(80);

	gotoxy(55,21);
	cout << "¦¦¦¦¦¦¦+¦¦¦  ¦¦¦¦¦¦  ¦¦¦+¦¦¦¦¦¦+¦¦¦¦¦¦  ¦¦¦¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+¦¦¦¦¦¦¦¦";
	Sleep(80);

	gotoxy(55,22);
	cout << "+------++-+  +-++-+  +-+ +-----++-++-+  +-++------++------++-----+";

    Beep(1000,250);
}
#endif
