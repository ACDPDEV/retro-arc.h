// CONSOLA.H

#ifndef CONSOLA_H
#define CONSOLA_H

#include <iostream>
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

//---------------------------------------------------------
// COLOR
//---------------------------------------------------------
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//---------------------------------------------------------
// GOTOXY
//---------------------------------------------------------
void gotoxy(int x, int y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

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
