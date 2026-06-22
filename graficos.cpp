#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <synchapi.h>
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

// ------------------------------------------------------------------------
// FUNCIONES BASE
// ------------------------------------------------------------------------
void color(int c);
void gotoxy(int x, int y);
void reproducirMusica(string archivo);
void detenerMusica();
void activar_truecolor();
string repeat_pixel(int numero, char simbolo);
void dibujarTitulo();

// ------------------------------------------------------------------------
// EJEMPLOS DE LA PROFESORA
// ------------------------------------------------------------------------
void musicaCampeon();
void bienvenido();
void snoopy();
void caritafeliz(int x, int y);
void estrellabeep(int x, int y);
void estrellamp3(int x, int y);
void estrellaAzulTiritando(int x, int y);

// ------------------------------------------------------------------------
// NUESTROS DIBUJOS
// ------------------------------------------------------------------------
void titulo();
void victoria();
void cohete();
void ovni();
void buque(int x, int y);
void avion(int x, int y);
void tictactoe_menu(int x, int y);
void jugador(int x, int y);
void eevee(int x, int y);
void pikachu(int x, int y);

int main() {
    // 1. Activamos los colores ANSI TrueColor para dibujos como Pikachu y Eevee
    activar_truecolor();

    int opcion;

    do {
        system("cls"); // Limpia la pantalla en cada retorno al menú

        // Encabezado decorativo usando tu propia función de título
        color(11); // Color Celeste
        dibujarTitulo();

        color(14); // Color Amarillo para el recuadro del menú
        cout << "\n====================================================================" << endl;
        color(15); // Blanco
        cout << "                    MENU PRINCIPAL - TRABAJO DE GRAFICOS            " << endl;
        color(14);
        cout << "====================================================================" << endl;
        color(7);  // Blanco normal para las opciones

        cout << " 1.  Mostrar Titulo Principal (Estatico)" << endl;
        cout << " 2.  Efecto de Victoria (Musica MP3 + Animacion Confeti)" << endl;
        cout << " 3.  Animacion del Cohete (Interactivo - Dispara con ESPACIO)" << endl;
        cout << " 4.  Formacion OVNI (Movimiento - Salir con ESC)" << endl;
        cout << " 5.  Dibujo de Buque de Guerra (Estatico)" << endl;
        cout << " 6.  Dibujo de Avion F15 (Estatico)" << endl;
        cout << " 7.  Menu Tic Tac Toe (ASCII Art)" << endl;
        cout << " 8.  Personaje Jugador (ASCII Art)" << endl;
        cout << " 9.  Dibujo de Eevee (Braille Art)" << endl;
        cout << " 10. Dibujo de Pikachu (True Color ANSI)" << endl;

        color(11); // Celeste para los ejemplos de la profesora
        cout << " ------------------------------------------------------------------" << endl;
        cout << " 11. [Ejemplo Profe] Snoopy en Movimiento" << endl;
        cout << " 12. [Ejemplo Profe] Carita Feliz" << endl;
        cout << " 13. [Ejemplo Profe] Estrella con Sonido Beep" << endl;
        cout << " 14. [Ejemplo Profe] Estrella con Musica MP3" << endl;
        cout << " 15. [Ejemplo Profe] Estrella Azul Tiritando" << endl;

        color(12); // Rojo para la opción de salida
        cout << " ------------------------------------------------------------------" << endl;
        cout << " 0.  SALIR DEL PROGRAMA" << endl;
        color(14);
        cout << "====================================================================" << endl;
        color(15);
        cout << " Seleccione una opcion [0-15]: ";
        cin >> opcion;

        // Ejecución de la opción seleccionada
        system("cls"); // Limpiamos pantalla antes de dibujar
        switch(opcion) {
            case 1:
                titulo();
                break;
            case 2:
                victoria();
                break;
            case 3:
                cohete();
                break;
            case 4:
                ovni();
                break;
            case 5:
                color(11);
                buque(5, 5);
                break;
            case 6:
                color(14);
                avion(5, 5);
                break;
            case 7:
                color(13);
                tictactoe_menu(5, 2);
                break;
            case 8:
                jugador(5, 2);
                break;
            case 9:
                color(14);
                eevee(5, 2);
                break;
            case 10:
                pikachu(5, 2);
                break;
            case 11:
                snoopy();
                break;
            case 12:
                color(14);
                caritafeliz(25, 5);
                break;
            case 13:
                estrellabeep(30, 5);
                break;
            case 14:
                estrellamp3(30, 5);
                break;
            case 15:
                estrellaAzulTiritando(30, 5);
                break;
            case 0:
                color(10);
                cout << "\n\n\t¡Gracias por usar nuestro programa de graficos!\n\tSaliendo con exito...\n\n" << endl;
                break;
            default:
                color(12);
                cout << "\n\n\tOpcion no valida. Por favor, intente de nuevo.\n" << endl;
        }
        if(opcion != 0) {
            color(7); // Restaurar blanco
            cout << "\n\n\n Presione cualquier tecla para regresar al Menu Principal...";
            getch();
        }

    } while(opcion != 0);

    return 0;
}

// Funcion para cambiar el color del texto en consola
void color(int c) {
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
void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hcon, dwPos);
}

// Musica sencilla usando Beep()
// Cada Beep tiene una frecuencia y una duracion
void musicaCampeon() {
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
void reproducirMusica(string archivo) {
    mciSendString("stop musica", NULL, 0, NULL);
    mciSendString("close musica", NULL, 0, NULL);

    string comando = "open \"" + archivo + "\" type mpegvideo alias musica";
    mciSendString(comando.c_str(), NULL, 0, NULL);

    mciSendString("play musica", NULL, 0, NULL);
}

// Funcion para detener la musica MP3
void detenerMusica() {
    // Detiene la musica
    mciSendString("stop musica", NULL, 0, NULL);

    // Cierra el archivo de musica
    mciSendString("close musica", NULL, 0, NULL);
}

/// Activa colores ANSI truecolor en la consola de Windows y la página de
/// códigos CP437 (necesaria para que el byte 223 se vea como '▀').
/// Requiere Windows 10 build 1909+. Fuente: https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
void activar_truecolor() {
    SetConsoleOutputCP(437);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

string repeat_pixel(int numero, char simbolo = (char)223) {
    string result;
    for (int i = 0; i < numero; i++) {
        result += simbolo;
    }
    return result;
}

void bienvenido() {
    cout << "\n\t ,-----. ,--.                                ,--.  ,--." << endl;
    cout << "\t |  |) |_`--',---.,--,--,--.  ,--,---.,--,--,`--',-|  |,---." << endl;
    cout << "\t |  .-.  |--| .-. |      |  `'  | .-. |      |--' .-. | .-. | " << endl;
    cout << "\t |  '--' |  | '---|  ||  ||    || '---|  ||  |  ! `-' ' '-' ' " << endl;
    cout << "\t `------'`--'`----`--''--' `--'  `----`--''--`--'`---' `---' " << endl;
}

void caritafeliz(int x, int y) {
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

void snoopy() {
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
void estrellabeep(int x, int y) {
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
void estrellamp3(int x, int y) {
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

void estrellaAzulTiritando(int x, int y) {
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

// ------------------------------------------------------------------------
// NUESTROS DIBUJOS
// ------------------------------------------------------------------------
void dibujarTitulo() {
    int random = 1 + rand() % 10;
    color((random + 0) % 10); cout << "@@@@@@@  @@@@@@@    @@@@@  @@   @@ @@   @@ @@@@@@@ @@   @@  @@@@@  @@@@@@@ @@@@@@@ @@@@ @@   @@" << endl;
    color((random + 1) % 10); cout << "@@       @@    @@  @@   @@ @@@  @@ @@  @@  @@      @@@  @@ @@        @@    @@      @@@@ @@@  @@" << endl;
    color((random + 2) % 10); cout << "@@@@@    @@@@@@@  @@@@@@@@ @@@@ @@ @@@@@   @@@@@   @@@@ @@  @@@@@    @@    @@@@@    @@  @@@@ @@" << endl;
    color((random + 3) % 10); cout << "@@       @@  @@   @@    @@ @@ @@@@ @@  @@  @@      @@ @@@@     @@    @@    @@       @@  @@ @@@@" << endl;
    color((random + 4) % 10); cout << "@@       @@   @@  @@    @@ @@  @@@ @@   @@ @@      @@  @@@ @@  @@    @@    @@      @@@@ @@  @@@" << endl;
    color((random + 5) % 10); cout << "@@       @@    @@ @@    @@ @@   @@ @@   @@ @@@@@@@ @@   @@  @@@@@    @@    @@@@@@@ @@@@ @@   @@" << endl;
}
void titulo() {
    reproducirMusica("retro.mp3");
    for (int i = 1; i <= 10 ; i++) {
        system("cls");
        dibujarTitulo();
        Sleep(500);
    }
};


// Función para imprimir el título "VICTORIA"
void tituloVictoria(int x){
    gotoxy(x,7);  cout << R"(__/\\\________/\\\__/\\\\\\\\\\\________/\\\\\\\\\__/\\\\\\\\\\\\\\\_______/\\\\\_________/\\\\\\\\\______/\\\\\\\\\\\_____/\\\\\\\\\____  )";
    gotoxy(x,8);  cout << R"(  _\//\\\______/\\\______\/\\\_______/\\\/_________________\/\\\_________/\\\/__\///\\\__\/\\\_____\/\\\_______\/\\\______/\\\/////////\\\_ )";
    gotoxy(x,9);  cout << R"(   __\//\\\____/\\\_______\/\\\______/\\\___________________\/\\\________/\\\______\//\\\_\/\\\\\\\\\\\/________\/\\\_____\/\\\_______\/\\\_   )";
    gotoxy(x,10); cout << R"(    ___\//\\\__/\\\________\/\\\_____\/\\\___________________\/\\\_______\/\\\_______\/\\\_\/\\\//////\\\________\/\\\_____\/\\\\\\\\\\\\\\\_   )";
    gotoxy(x,11); cout << R"(     ____\//\\\/\\\_________\/\\\_____\//\\\__________________\/\\\_______\//\\\______/\\\__\/\\\____\//\\\_______\/\\\_____\/\\\/////////\\\_  )";
    gotoxy(x,12); cout << R"(      _____\//\\\\\__________\/\\\______\///\\\________________\/\\\________\///\\\__/\\\____\/\\\_____\//\\\______\/\\\_____\/\\\_______\/\\\_ )";
    gotoxy(x,13); cout << R"(       ______\//\\\________/\\\\\\\\\\\____\////\\\\\\\\\_______\/\\\__________\///\\\\\/_____\/\\\______\//\\\__/\\\\\\\\\\\_\/\\\_______\/\\\_ )";
    gotoxy(x,14); cout << R"(        _______\///________\///////////________\/////////________\///_____________\/////_______\///________\///__\///////////__\///________\///__)";
}
// Función para borrar el título con animación
void borrarTitulo(int posx, int posy,int largoTitulo, int altoTitulo){
    for (int i = 0; i < altoTitulo; i++)
    {
        for (int j = 0; j < largoTitulo; j++)
        {
            gotoxy(posx+j,posy+i); cout << " ";
            Sleep(2);
        }

    }
}
//Función para mostrar confeti
void mostrarConfeti(int x, int y, int largoTitulo, int altoTitulo, int duracionMs) {
    srand(time(NULL));
    char simbolos[] = { '*', '.', 'o', '+', 'x' };
    const int N = 10;      // partículas en pantalla a la vez
    int px[N], py[N];
    int margen = 4;        // franja arriba/abajo del título

    int repeticiones = duracionMs / 150;

    for (int i = 0; i < repeticiones; i++)
    {
        // borramos las partículas de la vuelta anterior
        if (i > 0) {
            for (int p = 0; p < N; p++) {
                gotoxy(px[p], py[p]);
                cout << " ";
            }
        }

        // elegimos un color random para este fotograma
        int colorRandom = rand() % 6;
        switch (colorRandom)
        {
            case 0: system("color 0A"); break; // verde
            case 1: system("color 0B"); break; // cian
            case 2: system("color 0C"); break; // rojo
            case 3: system("color 0D"); break; // magenta
            case 4: system("color 0E"); break; // amarillo
            case 5: system("color 0F"); break; // blanco
        }

        // dibujamos partículas nuevas en posiciones random
        for (int p = 0; p < N; p++)
        {
            //utilizamos un condicional compacto a ? b:c
            int fila = (rand() % 2 == 0) ? y - 1 - rand() % margen : y + altoTitulo + rand() % margen;
            int col = x + rand() % largoTitulo;

            px[p] = col;
            py[p] = fila;

            gotoxy(col, fila);
            cout << simbolos[rand() % 5];
        }

        Sleep(150);
    }

    // borramos las últimas partículas
    for (int p = 0; p < N; p++) {
        gotoxy(px[p], py[p]);
        cout << " ";
    }

    system("color 0F"); // dejamos la consola en blanco sobre negro al terminar
}
void victoria() {

    reproducirMusica("victoria.mp3");
    Sleep(3000); //esperamos 3 segundos para mostrar el título
    tituloVictoria(1); //imprimimos el título
    mostrarConfeti(1, 7, 145, 8, 4700);
    borrarTitulo(1, 7, 145, 8);
    Sleep(4000);
}

void dibujar_cohete(int x,int y) {
    color(12);

    gotoxy(x,y);      cout<<"            /\\";
    gotoxy(x,y+1);    cout<<"           /##\\";
    gotoxy(x,y+2);    cout<<"          /####\\";
    gotoxy(x,y+3);    cout<<"         /######\\";

    color(14);

    gotoxy(x,y+4);    cout<<"        |########|";
    gotoxy(x,y+5);    cout<<"        |########|";

    color(11);

    gotoxy(x,y+6);    cout<<"        |## OO ##|";
    gotoxy(x,y+7);    cout<<"        |# OOOO #|";
    gotoxy(x,y+8);    cout<<"        |## OO ##|";

    color(14);

    gotoxy(x,y+9);    cout<<"        |########|";
    gotoxy(x,y+10);   cout<<"        |########|";

    color(11);

    gotoxy(x,y+11);   cout<<"        |## OO ##|";

    color(9);

    gotoxy(x,y+12);   cout<<"       /|########|\\";
    gotoxy(x,y+13);   cout<<"      /_|########|_\\";
    gotoxy(x,y+14);   cout<<"     /__|########|__\\";

    color(14);

    gotoxy(x,y+15);   cout<<"        |########|";
    gotoxy(x,y+16);   cout<<"        |########|";

    color(8);

    gotoxy(x,y+17);   cout<<"       /    ||    \\";
    gotoxy(x,y+18);   cout<<"      /_____||_____\\";

    color(14);

    gotoxy(x+8,y+19); cout<<"   /\\/\\ ";

    color(12);

    gotoxy(x+7,y+20); cout<<"   /\\/\\/\\";
}
void disparoLaser(int x,int y) {
    Beep(1800,50);

    for(int i=y;i>0;i--)
    {
        color(11);

        gotoxy(x,i);
        cout<<"^";

        Sleep(20);

        gotoxy(x,i);
        cout<<" ";
    }
}
void cohete() {
    system("mode con: cols=120 lines=40");
    system("cls");

    int x = 1;
    int y = 10;
    int direccion = 1;

    while(true)
    {
        system("cls");

        dibujar_cohete(x,y);

        color(15);

        gotoxy(5,36);
        cout<<"ESPACIO = DISPARAR";

        gotoxy(5,37);
        cout<<"ESC = SALIR";

        if(kbhit())
        {
            char tecla = getch();
            if(tecla == 27)
            {
                break;
            }
            if(tecla == ' ')
            {
                disparoLaser(x+13,y-1);

                dibujar_cohete(x,y);
            }
        }
        x += direccion;

        if(x >= 85)
        {
            direccion = -1;
        }
        if(x <= 1)
        {
            direccion = 1;
        }
        Sleep(60);
    }

    system("cls");

    color(10);

    gotoxy(45,15);
    cout<<"GRACIAS";

    Beep(523,200);
    Beep(659,200);
    Beep(784,300);

    color(15);
}

void dibujar_ovni(int x,int y) {
    color(10);

    gotoxy(x,y); cout<<"      .------.";
    gotoxy(x,y+1); cout<<"    _.'  ||  `._";
    gotoxy(x,y+2); cout<<"  .'  _(_)(_)_  `.";
    gotoxy(x,y+3); cout<<"===================";
    gotoxy(x,y+4); cout<<"| (*) (*) (*) (*) |";
    gotoxy(x,y+5); cout<<" `._  ********* _.'";
    gotoxy(x,y+6); cout<<"    `---------`";
    gotoxy(x,y+7); cout<<"      / / \\ \\";

    color(15);
}

void borrarOvni(int x,int y) {
    for(int i=0;i<8;i++)
    {
        gotoxy(x,y+i);
        cout<<"                     ";
    }
}

void formacionOvnis(int x,int y) {

    dibujar_ovni(x+20,y);

    dibujar_ovni(x,y+10);

    dibujar_ovni(x+40,y+10);
}

void borrarFormacion(int x,int y) {
    borrarOvni(x+20,y);

    borrarOvni(x,y+10);

    borrarOvni(x+40,y+10);
}

void ovni() {
    system("mode con: cols=120 lines=40");

    int x = 1;
    int y = 2;
    int direccion = 1;

    // Mensaje de ayuda en pantalla
    gotoxy(5, 30);
    color(15);
    cout << "PRESIONE 'ESC' PARA SALIR DE LA ANIMACION Y VOLVER AL MENU";

    while(true)
    {
        formacionOvnis(x,y);
        Sleep(80);
        borrarFormacion(x,y);

        x += direccion;

        if(x >= 40) {
            direccion = -1;
        }
        if(x <= 1) {
            direccion = 1;
        }

        // NUEVA MEJORA: Detectar si el usuario presiona ESC para salir
        if(kbhit()) {
            char tecla = getch();
            if(tecla == 27) { // 27 es el código ASCII de la tecla ESC
                break;
            }
        }
    }
    system("cls");
}

void buque(int x, int y) {
    gotoxy(x, y + 0);  cout << "                                     |__";
    gotoxy(x, y + 1);  cout << "                                     |\\\\/";
    gotoxy(x, y + 2);  cout << "                                    ---";
    gotoxy(x, y + 3);  cout << "                                   |/ | [";
    gotoxy(x, y + 4);  cout << "                                 ! || | |||";
    gotoxy(x, y + 5);  cout << "                               _/|  _/|-++'";
    gotoxy(x, y + 6);  cout << "                         +   +--|    |--|--|_ |-";
    gotoxy(x, y + 7);  cout << "                      { /|__| [==o]  |--- |||__/";
    gotoxy(x, y + 8);  cout << "            [===o]|T|  +---------------___[}-_===_.'____                  /\\";
    gotoxy(x, y + 9);  cout << "                |  |____`-' ||___-{]_| _[}-  |     |_[___\\==--            \\/ _";
    gotoxy(x, y + 10); cout << " __..._____--==/___]_|__|_____________________________[___\\==--___,-----'.7";
    gotoxy(x, y + 11); cout << "|                                                               BB-61     /";
    gotoxy(x, y + 12); cout << " \\_______________________________________________________________________|";
};

void avion(int x, int y) {
    gotoxy(x, y + 0);  cout << "  ______";
    gotoxy(x, y + 1);  cout << "  L,.   ',";
    gotoxy(x, y + 2);  cout << "   \\\\     ',_";
    gotoxy(x, y + 3);  cout << "    \\\\  FAP  ',";
    gotoxy(x, y + 4);  cout << "     \\\\       ',";
    gotoxy(x, y + 5);  cout << "      \\\\    F15   ',";
    gotoxy(x, y + 6);  cout << "       \\\\___NAVY  ',_                            _..----.._";
    gotoxy(x, y + 7);  cout << "       [______        \"'==.I\\\\_____________..--\"<__\\\\_n@___4\\,_";
    gotoxy(x, y + 8);  cout << "     ,..-=T            __   ____________            \\/ \"'\" O<==\"\"-+.._";
    gotoxy(x, y + 9);  cout << "     I____|_____    }_>=========I>=**\"\"''==-------------==-   \" |   \"'-,___";
    gotoxy(x, y + 10); cout << "     [_____,.--'\"            _______        \"\"--=<\"\"-----=====+==--''\"\"";
    gotoxy(x, y + 11); cout << "     \"\"'-=+..,,__,-----,_____|      |      -=* |";
    gotoxy(x, y + 12); cout << "                    |__   /    |---,--'\"---+------+- '\"";
};

//inicio es lo que imprime el programa cuando seleccionas el jueg "tictactoe" en el menú de minijuegos

void tictactoe_menu(int x, int y) {
    gotoxy(x, y);cout      << "   ,-----. ,--. ,----.  ,-----.  ,----. ,----.  ,-----. ,---. ,---.,     ";
    gotoxy(x, y + 1);cout  << "   |_    _| |  | |  __| |_    _| |     | |  __| |_    _| |   | |  __|    ";
    gotoxy(x, y + 2);cout  << "     |  |   |  | | |      |  |   |  _  | | |      |  |   | ] | |.|_      ";
    gotoxy(x, y + 3);cout  << "     |  |   |  | | |      |  |   |  _  | | |      |  |   | ] | |  _|     ";
    gotoxy(x, y + 4);cout  << "     |  |   |  | | |__    |  |   |  _  | | |__    |  |   | ] | |.|__     ";
    gotoxy(x, y + 5);cout  << "     |  |   |  | |    |   |  |   | | | | |    |   |  |   |   | |    |    ";
    gotoxy(x, y + 6);cout  << "     `--'   `--' '----'   `--'   `-' `-' '----'   `--'   `---'  `---`    ";
    gotoxy(x, y + 7);cout  << "          _____       ";
    gotoxy(x, y + 8);cout  << "       .-(    )-.     ";
    gotoxy(x, y + 9);cout  << "      (  Hola...)     ";
    gotoxy(x, y + 10);cout << "      '--(   )--'     ";
    gotoxy(x, y + 11);cout << "          )(          ";
    gotoxy(x, y + 12);cout << "         / _          ";
    gotoxy(x, y + 13);cout << "     `_--/-/_ _       ";
    gotoxy(x, y + 14);cout << " ~\\/       /         ";
    gotoxy(x, y + 15);cout << "   |  . _ .   |--\\   ";
    gotoxy(x, y + 16);cout << "  _| # (    #  )      ";
    gotoxy(x, y + 17);cout << " / \\   _  # /        ";
    gotoxy(x, y + 18);cout << "     -_  _-~          ";
    gotoxy(x, y + 19);cout << "      -'--`-_         ";
    gotoxy(x, y + 20);cout << "     /     . |        ";
    gotoxy(x, y + 21);cout << "     |     |~|        ";
    gotoxy(x, y + 22);cout << "     |-----,,)        ";
    gotoxy(x, y + 23);cout << "     --------         ";
    gotoxy(x, y + 24);cout << "       |_|_|          ";
    gotoxy(x, y + 25);cout << "     _~__~__\\        ";
}
//jugador es el personaje del juego, que te observa mientras juegas y puede mostrar comentarios de la jugada

void jugador(int x, int y) {
	color(10);

    gotoxy(x, y);          cout << "                               o                          ";
    gotoxy(x, y + 1);      cout << "                             o$$      oo                  ";
    gotoxy(x, y + 2);      cout << "                 $o         o$ $     o$                   ";
    gotoxy(x, y + 3);      cout << "               $  $         $  $    o$    ooo             ";
    gotoxy(x, y + 4);      cout << "               $o '$       o'  $    $'   o$'''            ";
    gotoxy(x, y + 5);      cout << "               $'  'o     o$   $   o    o''               ";
    gotoxy(x, y + 6);      cout << "               $    $     $$   $   $   o''                ";
    gotoxy(x, y + 7);      cout << "               $$    $   $$'    $ $'  $'       oo '       ";
    gotoxy(x, y + 8);      cout << "       $   o   $$     oo'$      ' '   $o oooo'''   ooo    ";
    gotoxy(x, y + 9);      cout << "        $   'o $$      '  oo       oo  '''     oo'''      ";
    gotoxy(x, y + 10);     cout << "         $   '$$$       o'  '     '  '      o '           ";
    gotoxy(x, y + 11);     cout << "         $$                                 ''oooo        ";
    gotoxy(x, y + 12);     cout << " o        $                         ooo        ''''''oooo ";
    gotoxy(x, y + 13);     cout << "  'o      $           ooo   o    o'    ''                 ";
    gotoxy(x, y + 14);     cout << "o   'oo   '         o'       'o '        'o     oooo      ";
    gotoxy(x, y + 15);     cout << " 'o   ''          o'          $           ''              ";
    gotoxy(x, y + 16);     cout << "   'oo           o'           $$           $     $$$$''   ";
    gotoxy(x, y + 17);     cout << " oooo'           $         oo $  oo        $       '''    ";
    gotoxy(x, y + 18);     cout << " ooooo   ''      $        $'$ $ o'$$       $   ooooooo    ";
    gotoxy(x, y + 19);     cout << "'''  '$ '        $        '$' $ $$'        '   $$'''      ";
    gotoxy(x, y + 20);     cout << "   oo $          'o          o$ '         o    $$ooo      ";
    gotoxy(x, y + 21);     cout << " o$'''''          'o          'o         o     '''''$     ";
    gotoxy(x, y + 22);     cout << " $$                 ''ooooo$     o     o            $     ";
    gotoxy(x, y + 23);     cout << " '$                      $      $o'' '''             $    ";
    gotoxy(x, y + 24);     cout << "   'o    o                 o   o$'                 ''     ";
    gotoxy(x, y + 25);     cout << "     ''oo$o                 '''''             $ooo''      ";
    gotoxy(x, y + 26);     cout << "          'oo                               o$'           ";
    gotoxy(x, y + 27);     cout << "            'oo                           oo'             ";
    gotoxy(x, y + 28);     cout << "              ''oo        '''          oo'''              ";
    gotoxy(x, y + 29);     cout << "                 ''' oo            o  '''                 ";
    gotoxy(x, y + 30);     cout << "                      o'$' oooo ''                        ";
    gotoxy(x, y + 31);     cout << "                     o'   $''''' o                        ";
    gotoxy(x, y + 32);     cout << "                     $o   o$     $o                       ";
    gotoxy(x, y + 33);     cout << "                    o$ooo  $ooooo$                        ";
    gotoxy(x, y + 34);     cout << "                    $'     $       '                      ";
    gotoxy(x, y + 35);     cout << "                    $''''' $'''''$$                       ";
    gotoxy(x, y + 36);     cout << "                    'o$$' $$oooooo$o$                     ";
    gotoxy(x, y + 37);     cout << "                     o $  $        $                      ";
    gotoxy(x, y + 38);     cout << "                     $o$  $$''' '  $$                     ";
    gotoxy(x, y + 39);     cout << "                o    '    $    '''''$                     ";
    gotoxy(x, y + 40);     cout << "                $oo       $ooooooo  $                     ";
    gotoxy(x, y + 41);     cout << "                 $''  o  o'         '$                    ";
    gotoxy(x, y + 42);     cout << "                 $$''$$$$$$$$$$$$$o$$$                    ";
    gotoxy(x, y + 43);     cout << "                    o$$$$$$$$$$$$$$$$$  o                 ";
    gotoxy(x, y + 44);     cout << "                ooo$''$$$$$$''''''$$''''''''o             ";
    gotoxy(x, y + 45);     cout << "               $''$oooo$$$         $         $o           ";
    gotoxy(x, y + 46);     cout << "          '''''$o                 o        o'''           ";
    gotoxy(x, y + 47);     cout << "               ''$$oooooooooooooo''' ooo$$'''             ";
    gotoxy(x, y + 48);     cout << "                      ''''''''                            ";
}
void eevee(int x, int y) {
    gotoxy(x, y+0);  cout << "⠀⠀⠀⠀⠀⠀⣀⣠⣤⡔⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡴⣧";
    gotoxy(x, y+1);  cout << "⠀⠀⣀⣤⣶⣿⣿⣿⣿⣏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡾⠁⣼";
    gotoxy(x, y+2);  cout << "⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⢷⣆⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡟⠀⠀⣿";
    gotoxy(x, y+3);  cout << "⣾⣿⣿⣟⢛⣛⣛⣛⣋⠭⠥⠿⣿⣿⣷⣤⠀⠀⠀⢀⣀⣀⣠⣀⡀⢿⡇⠀⣸⡇";
    gotoxy(x, y+4);  cout << "⣿⣿⣿⠻⢧⠙⢯⡀⠈⠉⠙⠛⠳⢦⣝⢿⣷⢠⣾⣿⣿⣿⣿⣿⣯⣬⡥⢰⡟⠀";
    gotoxy(x, y+5);  cout << "⢹⣯⣛⠯⢿⣾⣷⣍⡳⣤⣀⠀⠀⠀⠉⠳⣍⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡃⠀⠀";
    gotoxy(x, y+6);  cout << "⠈⠹⣿⣿⣾⣿⣿⣿⣿⣷⣭⣛⠷⢦⣤⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀";
    gotoxy(x, y+7);  cout << "⠀⠀⠈⠛⠿⣿⣿⣿⣿⣿⢋⣵⡾⣣⣤⣦⢻⣿⣿⣿⣻⠻⣿⣿⣿⡏⠖⢻⠀⠀";
    gotoxy(x, y+8);  cout << "⠀⠀⠀⠀⠀⠀⠈⠉⠉⣱⣿⡟⠼⣻⣿⣿⢸⣿⣿⡇⡛⠀⣿⣿⣿⣧⡠⣸⡇⠀";
    gotoxy(x, y+9);  cout << "⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣷⢹⣿⣿⣿⣏⢿⣿⣷⣕⣧⣿⣿⣿⢿⣿⡿⠀⠀";
    gotoxy(x, y+10); cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⣠⢿⣿⡟⣿⣷⣭⣻⠿⢿⠿⠷⢞⣫⣵⠿⠀⠀";
    gotoxy(x, y+11); cout << "⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿⣿⡟⣎⢿⣧⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠀⠀⠀";
    gotoxy(x, y+12); cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⠁⠻⣷⡝⣩⣿⣿⣿⣿⣿⣿⣿⠿⠁⠀⠀⠀⠀";
    gotoxy(x, y+13); cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⠀⠀⠀⠀⣿⣿⣿⠉⠙⢻⢟⣿⡇⠀⠀⠀⠀⠀";
    gotoxy(x, y+14); cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⡀⠀⠸⣿⣿⡇⠀⠀⠀⠀⠀";
    gotoxy(x, y+15); cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⢿⡧⠀⠀⠈⠉⠀⠀⠀";
};
void pikachu(int x, int y) {
    const string FG1 = "\033[38;2;0;0;0m";
    const string FG2 = "\033[38;2;41;41;41m";
    const string FG3 = "\033[38;2;65;65;74m";
    const string FG4 = "\033[38;2;246;189;32m";
    const string FG5 = "\033[38;2;98;49;8m";
    const string FG6 = "\033[38;2;156;82;0m";
    const string FG7 = "\033[38;2;222;148;0m";
    const string FG8 = "\033[38;2;255;246;164m";
    const string FG9 = "\033[38;2;246;230;82m";
    const string FG10 = "\033[38;2;115;115;131m";
    const string FG11 = "\033[38;2;255;255;255m";
    const string FG12 = "\033[38;2;230;90;65m";
    const string FG13 = "\033[38;2;197;32;24m";

    const string BG1 = "\033[48;2;0;0;0m";
    const string BG2 = "\033[48;2;41;41;41m";
    const string BG3 = "\033[48;2;65;65;74m";
    const string BG4 = "\033[48;2;246;189;32m";
    const string BG5 = "\033[48;2;98;49;8m";
    const string BG6 = "\033[48;2;156;82;0m";
    const string BG7 = "\033[48;2;222;148;0m";
    const string BG8 = "\033[48;2;255;246;164m";
    const string BG9 = "\033[48;2;246;230;82m";
    const string BG10 = "\033[48;2;115;115;131m";
    const string BG11 = "\033[48;2;255;255;255m";
    const string BG12 = "\033[48;2;230;90;65m";
    const string BG13 = "\033[48;2;197;32;24m";

    gotoxy(x, y + 0); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 1); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 2); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 3); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 4); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 5); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 6); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 7); cout << FG1 << BG1 << repeat_pixel(19);    cout << FG2 << BG2 << repeat_pixel(1);    cout << FG1 << BG2 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(34);    cout << "\033[0m" << endl;
    gotoxy(x, y + 8); cout << FG1 << BG1 << repeat_pixel(19);    cout << FG2 << BG3 << repeat_pixel(1);    cout << FG2 << BG4 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(10);    cout << FG1 << BG2 << repeat_pixel(2);    cout << FG1 << BG1 << repeat_pixel(22);    cout << "\033[0m" << endl;
    gotoxy(x, y + 9); cout << FG1 << BG1 << repeat_pixel(19);    cout << FG4 << BG4 << repeat_pixel(2);    cout << FG5 << BG6 << repeat_pixel(1);    cout << FG1 << BG7 << repeat_pixel(1);    cout << FG1 << BG8 << repeat_pixel(2);    cout << FG1 << BG9 << repeat_pixel(1);    cout << FG1 << BG6 << repeat_pixel(1);    cout << FG1 << BG9 << repeat_pixel(1);    cout << FG6 << BG9 << repeat_pixel(1);    cout << FG4 << BG9 << repeat_pixel(1);    cout << FG9 << BG10 << repeat_pixel(1);    cout << FG3 << BG3 << repeat_pixel(2);    cout << FG3 << BG1 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(21);    cout << "\033[0m" << endl;
    gotoxy(x, y + 10); cout << FG1 << BG1 << repeat_pixel(19);    cout << FG4 << BG6 << repeat_pixel(1);    cout << FG4 << BG9 << repeat_pixel(1);    cout << FG7 << BG9 << repeat_pixel(1);    cout << FG8 << BG9 << repeat_pixel(3);    cout << FG9 << BG1 << repeat_pixel(1);    cout << FG9 << BG4 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(1);    cout << FG9 << BG7 << repeat_pixel(1);    cout << FG9 << BG1 << repeat_pixel(1);    cout << FG3 << BG1 << repeat_pixel(2);    cout << FG1 << BG1 << repeat_pixel(4);    cout << FG1 << BG9 << repeat_pixel(1);    cout << FG6 << BG9 << repeat_pixel(1);    cout << FG1 << BG6 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(16);    cout << "\033[0m" << endl;
    gotoxy(x, y + 11); cout << FG1 << BG1 << repeat_pixel(19);    cout << FG1 << BG2 << repeat_pixel(1);    cout << FG11 << BG6 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(4);    cout << FG1 << BG9 << repeat_pixel(1);    cout << FG2 << BG9 << repeat_pixel(1);    cout << FG9 << BG12 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(1);    cout << FG1 << BG5 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(3);    cout << FG1 << BG9 << repeat_pixel(1);    cout << FG7 << BG9 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(4);    cout << FG6 << BG6 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(15);    cout << "\033[0m" << endl;
    gotoxy(x, y + 12); cout << FG1 << BG1 << repeat_pixel(18);    cout << FG5 << BG5 << repeat_pixel(1);    cout << FG9 << BG4 << repeat_pixel(3);    cout << FG6 << BG4 << repeat_pixel(1);    cout << FG9 << BG4 << repeat_pixel(3);    cout << FG12 << BG13 << repeat_pixel(2);    cout << FG13 << BG13 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(3);    cout << FG6 << BG4 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(7);    cout << FG1 << BG1 << repeat_pixel(15);    cout << "\033[0m" << endl;
    gotoxy(x, y + 13); cout << FG1 << BG1 << repeat_pixel(19);    cout << FG4 << BG1 << repeat_pixel(1);    cout << FG4 << BG4 << repeat_pixel(9);    cout << FG1 << BG9 << repeat_pixel(1);    cout << FG6 << BG1 << repeat_pixel(1);    cout << FG4 << BG5 << repeat_pixel(1);    cout << FG4 << BG4 << repeat_pixel(3);    cout << FG9 << BG4 << repeat_pixel(1);    cout << FG9 << BG1 << repeat_pixel(2);    cout << FG1 << BG1 << repeat_pixel(17);    cout << "\033[0m" << endl;
    gotoxy(x, y + 14); cout << FG1 << BG1 << repeat_pixel(20);    cout << FG9 << BG9 << repeat_pixel(1);    cout << FG4 << BG9 << repeat_pixel(2);    cout << FG4 << BG4 << repeat_pixel(4);    cout << FG4 << BG9 << repeat_pixel(2);    cout << FG9 << BG9 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(2);    cout << FG4 << BG1 << repeat_pixel(1);    cout << FG4 << BG4 << repeat_pixel(1);    cout << FG1 << BG5 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(20);    cout << "\033[0m" << endl;
    gotoxy(x, y + 15); cout << FG1 << BG1 << repeat_pixel(19);    cout << FG9 << BG9 << repeat_pixel(2);    cout << FG7 << BG9 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(3);    cout << FG7 << BG9 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(2);    cout << FG9 << BG4 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(1);    cout << FG1 << BG5 << repeat_pixel(1);    cout << FG7 << BG7 << repeat_pixel(1);    cout << FG4 << BG4 << repeat_pixel(1);    cout << FG4 << BG5 << repeat_pixel(1);    cout << FG5 << BG1 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(19);    cout << "\033[0m" << endl;
    gotoxy(x, y + 16); cout << FG1 << BG1 << repeat_pixel(19);    cout << FG6 << BG9 << repeat_pixel(1);    cout << FG9 << BG6 << repeat_pixel(1);    cout << FG9 << BG7 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(2);    cout << FG6 << BG9 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(1);    cout << FG9 << BG6 << repeat_pixel(1);    cout << FG6 << BG9 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(1);    cout << FG9 << BG4 << repeat_pixel(1);    cout << FG1 << BG4 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(1);    cout << FG7 << BG1 << repeat_pixel(1);    cout << FG1 << BG6 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(21);    cout << "\033[0m" << endl;
    gotoxy(x, y + 17); cout << FG1 << BG1 << repeat_pixel(18);    cout << FG4 << BG4 << repeat_pixel(1);    cout << FG9 << BG9 << repeat_pixel(8);    cout << FG4 << BG9 << repeat_pixel(1);    cout << FG9 << BG4 << repeat_pixel(1);    cout << FG4 << BG4 << repeat_pixel(2);    cout << FG5 << BG4 << repeat_pixel(1);    cout << FG6 << BG1 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(22);    cout << "\033[0m" << endl;
    gotoxy(x, y + 18); cout << FG1 << BG1 << repeat_pixel(18);    cout << FG6 << BG1 << repeat_pixel(1);    cout << FG4 << BG1 << repeat_pixel(1);    cout << FG4 << BG4 << repeat_pixel(2);    cout << FG4 << BG7 << repeat_pixel(1);    cout << FG4 << BG1 << repeat_pixel(2);    cout << FG4 << BG5 << repeat_pixel(1);    cout << FG4 << BG4 << repeat_pixel(4);    cout << FG4 << BG1 << repeat_pixel(1);    cout << FG5 << BG1 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(23);    cout << "\033[0m" << endl;
    gotoxy(x, y + 19); cout << FG1 << BG1 << repeat_pixel(18);    cout << FG9 << BG1 << repeat_pixel(2);    cout << FG7 << BG5 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(6);    cout << FG5 << BG1 << repeat_pixel(1);    cout << FG4 << BG1 << repeat_pixel(1);    cout << FG4 << BG6 << repeat_pixel(1);    cout << FG1 << BG1 << repeat_pixel(25);    cout << "\033[0m" << endl;
    gotoxy(x, y + 20); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 21); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 22); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 23); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 24); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 25); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 26); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
    gotoxy(x, y + 27); cout << FG1 << BG1 << repeat_pixel(55);    cout << "\033[0m" << endl;
}
