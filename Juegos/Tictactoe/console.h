#ifndef CONSOLE_H
#define CONSOLE_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>

void gotoxy(int x, int y);
void OcultarCursor();
void color(int color);
void pausa(int tiempo);

#endif
