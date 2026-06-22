#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h> // Libreria necesaria para reproducir musica MP3

using namespace std;

/*
IMPORTANTE PARA USAR MP3 EN DEV-C++:

1. Ir a:
   Herramientas -> Opciones del compilador

2. Buscar la opcion:
   "Anadir estos comandos al linker" o "Comandos del enlazador"

3. Escribir:
   -lwinmm

4. El archivo shake.mp3 , happy.mp3 y los que use deben estar en la misma carpeta del programa .exe
*/

// Funcion para cambiar el color del texto en consola
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/*
Codigos de colores:
color(12); // rojo claro
color(4);  // rojo oscuro
color(14); // amarillo
color(10); // verde
color(11); // celeste
color(13); // rosado
color(7);  // blanco normal
*/

// Funcion para ubicar el cursor en una posicion especifica
// x representa la columna
// y representa la fila
void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hcon, dwPos);
}

// Musica sencilla usando Beep()
// Cada Beep tiene una frecuencia y una duracion
void musicaCampeon()
{
    Beep(523, 250);  // Do
    Beep(659, 250);  // Mi
    Beep(784, 250);  // Sol
    Beep(1046, 500); // Do alto

    Beep(784, 250);
    Beep(1046, 250);
    Beep(1318, 600); // Mi alto

    Beep(1174, 250);    Beep(1046, 250);    Beep(784, 500);

    Beep(880, 250);    Beep(988, 250);    Beep(1046, 700);
}

// Funcion para reproducir musica MP3
void reproducirMusica(string archivo)
{
    mciSendString("stop musica", NULL, 0, NULL);
    mciSendString("close musica", NULL, 0, NULL);

    string comando = "open \"" + archivo + "\" type mpegvideo alias musica";
    mciSendString(comando.c_str(), NULL, 0, NULL);

    mciSendString("play musica", NULL, 0, NULL);
}

// Funcion para detener la musica MP3
void detenerMusica()
{
    // Detiene la musica
    mciSendString("stop musica", NULL, 0, NULL);

    // Cierra el archivo de musica
    mciSendString("close musica", NULL, 0, NULL);
}



void bienvenido()
{
    cout << "\n\t ,-----. ,--.                                ,--.  ,--." << endl;
    cout << "\t |  |) |_`--',---.,--,--,--.  ,--,---.,--,--,`--',-|  |,---." << endl;
    cout << "\t |  .-.  |--| .-. |      |  `'  | .-. |      |--' .-. | .-. | " << endl;
    cout << "\t |  '--' |  | '---|  ||  ||    || '---|  ||  |  ! `-' ' '-' ' " << endl;
    cout << "\t `------'`--'`----`--''--' `--'  `----`--''--`--'`---' `---' " << endl;
}

void caritafeliz(int x, int y)
{
    gotoxy(x, y);     cout << "     #######     ";
    gotoxy(x, y + 1); cout << "   ##       ##   ";
    gotoxy(x, y + 2); cout << "  #  O     O  #  ";
    gotoxy(x, y + 3); cout << " #             # ";
    gotoxy(x, y + 4); cout << " #    \\___/    # ";
    gotoxy(x, y + 5); cout << "  #           #  ";
    gotoxy(x, y + 6); cout << "   ##       ##   ";
    gotoxy(x, y + 7); cout << "      #####      ";

    gotoxy(x, y + 9); cout << "FELICITACIONES !!!!";
}

void snoopy()
{
    int mov = 50;

    for (int pos = 0; pos < mov; pos++)
    {
        system("cls");

        gotoxy(5 + pos, 5);  cout << "             .----.";
        gotoxy(5 + pos, 6);  cout << "          _.'__    `.";
        gotoxy(5 + pos, 7);  cout << "      .--(#)(##)---/#\\ ";
        gotoxy(5 + pos, 8);  cout << "    .' @          /###\\ ";
        gotoxy(5 + pos, 9);  cout << "    :         ,   ##### ";
        gotoxy(5 + pos, 10); cout << "     `-..__.-' _.-\\###/ ";
        gotoxy(5 + pos, 11); cout << "            `;_:    `-   ";
        gotoxy(5 + pos, 12); cout << "         .'oooooo'  ";
        gotoxy(5 + pos, 13); cout << "        /,  JOE  ,\\ ";
        gotoxy(5 + pos, 14); cout << "       `-._______.-'   ";
        gotoxy(5 + pos, 15); cout << "       //  COOL!  \\\\";
        gotoxy(5 + pos, 16); cout << "       ___`. | .'__  ";
        gotoxy(5 + pos, 17); cout << "      (______|______) ";

        Sleep(80); // Pequena pausa para ver la animacion
    }
}

// Funcion estrella roja con musica usando Beep()
void estrellabeep(int x, int y)
{
    color(12); // rojo claro

    gotoxy(x, y);      cout << "        *        ";
    gotoxy(x, y + 1);  cout << "       ***       ";
    gotoxy(x, y + 2);  cout << "      *****      ";
    gotoxy(x, y + 3);  cout << "  *************  ";
    gotoxy(x, y + 4);  cout << "    *********    ";
    gotoxy(x, y + 5);  cout << "     *******     ";
    gotoxy(x, y + 6);  cout << "    *********    ";
    gotoxy(x, y + 7);  cout << "   ****   ****   ";
    gotoxy(x, y + 8);  cout << "  ***       ***  ";

    color(7); // vuelve al color blanco normal

    gotoxy(x, y + 10);
    cout << "Estrella roja con sonido Beep";

    musicaCampeon(); // reproduce musica con Beep
}

// Funcion estrella verde con musica MP3
void estrellamp3(int x, int y)
{
    color(10); // verde

    gotoxy(x, y);      cout << "        *        ";
    gotoxy(x, y + 1);  cout << "       ***       ";
    gotoxy(x, y + 2);  cout << "      *****      ";
    gotoxy(x, y + 3);  cout << "  *************  ";
    gotoxy(x, y + 4);  cout << "    *********    ";
    gotoxy(x, y + 5);  cout << "     *******     ";
    gotoxy(x, y + 6);  cout << "    *********    ";
    gotoxy(x, y + 7);  cout << "   ****   ****   ";
    gotoxy(x, y + 8);  cout << "  ***       ***  ";

    color(7); // vuelve al color blanco normal

    gotoxy(x, y + 10);
    cout << "Estrella verde con musica MP3";

    reproducirMusica("happy.mp3"); // inicia la musica MP3

    gotoxy(x, y + 12);
    cout << "Presione una tecla para detener la musica...";
    getch();

    detenerMusica(); // detiene la musica MP3
}

void estrellaAzulTiritando(int x, int y)
{
    // Inicia la musica MP3
    reproducirMusica("shake.mp3");

    // La estrella va a aparecer y desaparecer 20 veces
    for (int i = 0; i < 20; i++)
    {
        // Cambiamos un poquito la posicion para que parezca que tiembla
        int movimiento;

        if (i % 2 == 0)
            movimiento = 1;
        else
            movimiento = -1;

        // Color azul
        color(9);

        // Dibujar estrella
        gotoxy(x + movimiento, y);      cout << "        *        ";
        gotoxy(x + movimiento, y + 1);  cout << "       ***       ";
        gotoxy(x + movimiento, y + 2);  cout << "      *****      ";
        gotoxy(x + movimiento, y + 3);  cout << "  *************  ";
        gotoxy(x + movimiento, y + 4);  cout << "    *********    ";
        gotoxy(x + movimiento, y + 5);  cout << "     *******     ";
        gotoxy(x + movimiento, y + 6);  cout << "    *********    ";
        gotoxy(x + movimiento, y + 7);  cout << "   ****   ****   ";
        gotoxy(x + movimiento, y + 8);  cout << "  ***       ***  ";

        color(7);

        Sleep(250); // tiempo visible

        // Borrar estrella para que parezca que se va
        gotoxy(x + movimiento, y);      cout << "                 ";
        gotoxy(x + movimiento, y + 1);  cout << "                 ";
        gotoxy(x + movimiento, y + 2);  cout << "                 ";
        gotoxy(x + movimiento, y + 3);  cout << "                 ";
        gotoxy(x + movimiento, y + 4);  cout << "                 ";
        gotoxy(x + movimiento, y + 5);  cout << "                 ";
        gotoxy(x + movimiento, y + 6);  cout << "                 ";
        gotoxy(x + movimiento, y + 7);  cout << "                 ";
        gotoxy(x + movimiento, y + 8);  cout << "                 ";

        Sleep(150); // tiempo invisible
    }

    // Detiene la musica al terminar el efecto
    detenerMusica();
}

int main()
{
    bienvenido();
    gotoxy(20, 20);    cout << "Presione una tecla para continuar...";    getch();

    system("cls");
    snoopy();
    gotoxy(20, 20);    cout << "Presione una tecla para continuar...";    getch();

    system("cls");
    caritafeliz(25, 5);
    gotoxy(20, 20);    cout << "Presione una tecla para continuar...";    getch();

    system("cls");
    estrellabeep(30, 5);    gotoxy(20, 20);    cout << "Presione una tecla para continuar...";
    getch();

	system("cls");
    estrellamp3(30, 5);
     gotoxy(20, 20);    cout << "Presione una tecla para continuar...";

    system("cls");
    estrellaAzulTiritando(30, 5);
    gotoxy(20, 22);    cout << "Fin del programa.";    getch();

    return 0;
}
