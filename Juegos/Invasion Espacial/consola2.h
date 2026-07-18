// CONSOLA.H

#ifndef CONSOLA_H
#define CONSOLA_H

#include <iostream>
<<<<<<< HEAD
#include <sstream>
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
#include <windows.h>
#include <conio.h>
#include <string>
#include <ctime>

using namespace std;

//=========================================================
// CONSTANTES DE LA CONSOLA
//=========================================================
const int ANCHO_PANTALLA = 200;
const int ALTO_PANTALLA  = 60;

<<<<<<< HEAD
//=========================================================
// DOBLE BUFFER (evita el parpadeo durante el juego)
//=========================================================
// Idea: en vez de dibujar directamente sobre la pantalla que
// el usuario esta viendo, dibujamos todo el frame en un buffer
// "oculto" y recien al final lo mostramos de una sola vez con
// SetConsoleActiveScreenBuffer. Como el cambio es instantaneo,
// el ojo nunca ve un borrado a medias -> no hay parpadeo.

HANDLE bufferJuego[2];
int    indiceVisible     = 0;
bool   usandoDobleBuffer = false;

// CUADRO EN MEMORIA: durante el juego, en vez de mandar una
// llamada a Windows por cada linea de cada sprite (que es lo
// que dejaba una ventana chiquita para que el sistema repinte
// la consola a mitad de dibujar el frame -> esas lineas/pixeles
// sueltos que se ven), armamos el frame completo aca en RAM y
// recien en mostrarFrame() lo mandamos TODO junto en una unica
// llamada a la API.
CHAR_INFO cuadro[ANCHO_PANTALLA * ALTO_PANTALLA];
int  cursorX     = 0;
int  cursorY     = 0;
WORD colorActual = 15;

// Devuelve el handle sobre el que hay que escribir AHORA MISMO
HANDLE handleActivo()
{
    if(usandoDobleBuffer)
        return bufferJuego[1 - indiceVisible]; // el que esta oculto
    else
        return GetStdHandle(STD_OUTPUT_HANDLE); // consola normal (menus)
}

// Escribe un caracter en el cuadro en memoria, con limite de bordes
void escribirCelda(int x, int y, char c, WORD atributo)
{
    if(x < 0 || x >= ANCHO_PANTALLA || y < 0 || y >= ALTO_PANTALLA)
        return;

    int indice = y * ANCHO_PANTALLA + x;

    cuadro[indice].Char.AsciiChar = c;
    cuadro[indice].Attributes     = atributo;
}

// Crea los dos buffers y activa el modo doble buffer
void iniciarDobleBuffer()
{
    for(int i = 0; i < 2; i++)
    {
        bufferJuego[i] = CreateConsoleScreenBuffer(
            GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL);

        COORD tam;
        tam.X = ANCHO_PANTALLA;
        tam.Y = ALTO_PANTALLA;
        SetConsoleScreenBufferSize(bufferJuego[i], tam);

        SMALL_RECT ventana;
        ventana.Left   = 0;
        ventana.Top    = 0;
        ventana.Right  = ANCHO_PANTALLA - 1;
        ventana.Bottom = ALTO_PANTALLA - 1;
        SetConsoleWindowInfo(bufferJuego[i], TRUE, &ventana);

        CONSOLE_CURSOR_INFO cursor;
        cursor.dwSize   = 1;
        cursor.bVisible = FALSE;
        SetConsoleCursorInfo(bufferJuego[i], &cursor);
    }

    indiceVisible = 0;
    SetConsoleActiveScreenBuffer(bufferJuego[indiceVisible]);
    usandoDobleBuffer = true;
}

// Se llama UNA vez por vuelta del bucle del juego: muestra
// el frame recien dibujado y deja preparado el otro buffer
// para dibujar ahi el siguiente frame
void mostrarFrame()
{
    HANDLE oculto = bufferJuego[1 - indiceVisible];

    COORD tamBuffer      = { (SHORT)ANCHO_PANTALLA, (SHORT)ALTO_PANTALLA };
    COORD origenBuffer   = { 0, 0 };
    SMALL_RECT region    = { 0, 0, (SHORT)(ANCHO_PANTALLA - 1), (SHORT)(ALTO_PANTALLA - 1) };

    // UNA sola llamada para todo el frame (antes eran decenas/
    // cientos de llamadas chiquitas, una por cada linea de cada
    // sprite, y Windows a veces alcanzaba a repintar la ventana
    // a mitad de esa secuencia)
    WriteConsoleOutputA(oculto, cuadro, tamBuffer, origenBuffer, &region);

    indiceVisible = 1 - indiceVisible;
    SetConsoleActiveScreenBuffer(bufferJuego[indiceVisible]);
}

// Vuelve a la consola normal (para pantallas de game over, victoria, etc.)
void finalizarDobleBuffer()
{
    usandoDobleBuffer = false;
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
    CloseHandle(bufferJuego[0]);
    CloseHandle(bufferJuego[1]);
}

// Limpia TODO el buffer oculto de una sola vez (rapido, sin
// parpadeo). Hay que llamarla al principio de cada frame para
// que no queden "fantasmas" de dos frames atras al alternar
// entre los dos buffers.
void limpiarPantallaCompleta()
{
    if(usandoDobleBuffer)
    {
        for(int i = 0; i < ANCHO_PANTALLA * ALTO_PANTALLA; i++)
        {
            cuadro[i].Char.AsciiChar = ' ';
            cuadro[i].Attributes     = 15;
        }

        return;
    }

    HANDLE h = handleActivo();
    COORD  inicio = {0, 0};
    DWORD  escritos;
    DWORD  total = (DWORD)(ANCHO_PANTALLA * ALTO_PANTALLA);

    FillConsoleOutputCharacterA(h, ' ', total, inicio, &escritos);
    FillConsoleOutputAttribute(h, 15, total, inicio, &escritos);
}

//---------------------------------------------------------
// IMPRIMIR (reemplaza a "cout <<" en el juego para que el
// texto se escriba siempre en el buffer correcto)
//---------------------------------------------------------
template <typename T>
void imprimir(const T& valor)
{
    ostringstream oss;
    oss << valor;
    string texto = oss.str();

    if(usandoDobleBuffer)
    {
        for(size_t i = 0; i < texto.size(); i++)
            escribirCelda(cursorX + (int)i, cursorY, texto[i], colorActual);

        cursorX += (int)texto.size();

        return;
    }

    DWORD escritos;
    WriteConsoleA(handleActivo(), texto.c_str(), (DWORD)texto.length(), &escritos, NULL);
}

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
//---------------------------------------------------------
// COLOR
//---------------------------------------------------------
void color(int c)
{
<<<<<<< HEAD
    if(usandoDobleBuffer)
    {
        colorActual = (WORD)c;
        return;
    }

    SetConsoleTextAttribute(handleActivo(), c);
=======
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
}

//---------------------------------------------------------
// GOTOXY
//---------------------------------------------------------
void gotoxy(int x, int y)
{
<<<<<<< HEAD
    if(usandoDobleBuffer)
    {
        cursorX = x;
        cursorY = y;
        return;
    }

    HANDLE hCon = handleActivo();
=======
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    COORD pos;

    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(hCon, pos);
}

//---------------------------------------------------------
// CONFIGURAR PANTALLA
//---------------------------------------------------------
void configurarPantalla()
{
    system("mode con: cols=200 lines=60");
    system("title INVASION ESPACIAL");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize;
    bufferSize.X = 200;
    bufferSize.Y = 60;

    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT ventana;
    ventana.Left = 0;
    ventana.Top = 0;
    ventana.Right = 199;
    ventana.Bottom = 59;

    SetConsoleWindowInfo(hConsole, TRUE, &ventana);

    CONSOLE_CURSOR_INFO cursor;

    cursor.dwSize = 1;
    cursor.bVisible = FALSE;

    SetConsoleCursorInfo(hConsole, &cursor);
}

//---------------------------------------------------------
// OCULTAR CURSOR
//---------------------------------------------------------
void ocultarCursor()
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cci;

    cci.dwSize = 100;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon,&cci);
}

//---------------------------------------------------------
// MOSTRAR CURSOR
//---------------------------------------------------------
void mostrarCursor()
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cci;

    cci.dwSize = 100;
    cci.bVisible = TRUE;

    SetConsoleCursorInfo(hCon,&cci);
}

//---------------------------------------------------------
// LIMPIAR UNA ZONA
//---------------------------------------------------------
void limpiarZona(int x,int y,int ancho,int alto)
{
    for(int i=0;i<alto;i++)
    {
        gotoxy(x,y+i);

        for(int j=0;j<ancho;j++)
            cout<<" ";
    }
}

//---------------------------------------------------------
// ESCRIBIR TEXTO CON EFECTO
//---------------------------------------------------------
void escribirTexto(int x,int y,string texto,int velocidad)
{
    gotoxy(x,y);

    for(int i=0;i<texto.length();i++)
    {
        cout<<texto[i];
        Beep(1200,3);
        Sleep(velocidad);
    }
}

//---------------------------------------------------------
// BARRA DE CARGA
//---------------------------------------------------------
void barraCarga(int x,int y)
{
    gotoxy(x,y);
    cout<<"[";

    for(int i=0;i<30;i++)
        cout<<" ";

    cout<<"]";

    for(int i=0;i<30;i++)
    {
        gotoxy(x+1+i,y);

        color(10);

        cout<<(char)219;

        gotoxy(x+35,y);

        color(15);

        cout<<(i+1)*100/30<<" %";

        Beep(900,5);

        Sleep(45);
    }
}
//=========================================================
// FONDO ESPACIAL ANIMADO
//=========================================================
void fondoEspacialAnimado()
{
    static bool creado = false;

    const int CANTIDAD_ESTRELLAS = 60;

    static int x[CANTIDAD_ESTRELLAS];
    static int y[CANTIDAD_ESTRELLAS];
    static bool brillo[CANTIDAD_ESTRELLAS];


    //=====================================================
    // CREAR ESTRELLAS SOLO UNA VEZ
    //=====================================================

    if(!creado)
    {
        srand(time(NULL));

        for(int i = 0; i < CANTIDAD_ESTRELLAS; i++)
        {
            x[i] = rand() % ANCHO_PANTALLA;
            y[i] = rand() % ALTO_PANTALLA;

            brillo[i] = rand()%2;
        }

        creado = true;
    }


    //=====================================================
    // ACTUALIZAR BRILLO
    //=====================================================

    for(int i = 0; i < CANTIDAD_ESTRELLAS; i++)
    {

        gotoxy(x[i], y[i]);


        if(brillo[i])
        {
            color(15);
            cout<<"*";
        }
        else
        {
            color(8);
            cout<<".";
        }


        // Cambia aleatoriamente el brillo

        if(rand()%5 == 0)
        {
            brillo[i] = !brillo[i];
        }
    }


    color(15);
}

#endif
