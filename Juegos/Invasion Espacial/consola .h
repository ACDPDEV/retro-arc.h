#ifndef CONSOLA_H
#define CONSOLA_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;

//=========================================================
// POSICIONAR CURSOR
//=========================================================
void gotoxy(int x, int y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(hCon, pos);
}

//=========================================================
// CAMBIAR COLOR DEL TEXTO
//=========================================================
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//=========================================================
// CONFIGURAR LA CONSOLA
//=========================================================
void configurarPantalla()
{
    system("mode con: cols=200 lines=60");
    system("title INVASORES ESPACIALES");
}

//=========================================================
// LIMPIAR PANTALLA
//=========================================================
void limpiarPantalla()
{
    system("cls");
}

//=========================================================
// OCULTAR CURSOR
//=========================================================
void ocultarCursor()
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursor;

    cursor.dwSize = 100;
    cursor.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cursor);
}

//=========================================================
// MOSTRAR CURSOR
//=========================================================
void mostrarCursor()
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursor;

    cursor.dwSize = 100;
    cursor.bVisible = TRUE;

    SetConsoleCursorInfo(hCon, &cursor);
}

//=========================================================
// ESCRIBIR TEXTO CON EFECTO
//=========================================================
void escribirTexto(int x, int y, string texto, int velocidad)
{
    gotoxy(x, y);

    for(int i = 0; i < texto.length(); i++)
    {
        cout << texto[i];
        Sleep(velocidad);
    }
}

//=========================================================
// ESCRIBIR TEXTO CENTRADO
//=========================================================
void escribirTextoCentrado(int fila, string texto)
{
    int columna = (200 - texto.length()) / 2;

    gotoxy(columna, fila);

    cout << texto;
}

//=========================================================
// DIBUJAR UNA LÍNEA HORIZONTAL
//=========================================================
void lineaHorizontal(int x, int y, int longitud, char caracter)
{
    gotoxy(x, y);

    for(int i = 0; i < longitud; i++)
        cout << caracter;
}

//=========================================================
// DIBUJAR UNA LÍNEA VERTICAL
//=========================================================
void lineaVertical(int x, int y, int altura, char caracter)
{
    for(int i = 0; i < altura; i++)
    {
        gotoxy(x, y + i);
        cout << caracter;
    }
}

//=========================================================
// DIBUJAR UN MARCO
//=========================================================
void dibujarMarco(int x, int y, int ancho, int alto)
{
    lineaHorizontal(x, y, ancho, (char)205);
    lineaHorizontal(x, y + alto - 1, ancho, (char)205);

    lineaVertical(x, y, alto, (char)186);
    lineaVertical(x + ancho - 1, y, alto, (char)186);

    gotoxy(x, y);
    cout << (char)201;

    gotoxy(x + ancho - 1, y);
    cout << (char)187;

    gotoxy(x, y + alto - 1);
    cout << (char)200;

    gotoxy(x + ancho - 1, y + alto - 1);
    cout << (char)188;
}

#endif
