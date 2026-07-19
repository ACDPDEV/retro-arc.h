#include "console.h"
#include <windows.h>
#include <string>
#include <mmsystem.h>
#include <iostream>
#include <conio.h>

using namespace std;

const int ANCHO_PANTALLA = 200;
const int ALTO_PANTALLA = 60;

void gotoxy (int x, int y){ //para posicionar cursos
	HANDLE hConsole;
	COORD dwPos;
	
	dwPos.X=x;
	dwPos.Y=y;
	hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, dwPos);
}

void OcultarCursor(){
	CONSOLE_CURSOR_INFO cci ={100, FALSE};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void color(int color){
	static HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon, color|( 0 * 0x10 + 0x100));
}

void pausa(int x){
	Sleep(x);
}

void reproducirSonido(string archivo)
{
    mciSendString("stop sonido", NULL, 0, NULL);
    mciSendString("close sonido", NULL, 0, NULL);

    string comando = "open \"" + archivo + "\" type mpegvideo alias sonido";
    mciSendString(comando.c_str(), NULL, 0, NULL);

    mciSendString("play sonido", NULL, 0, NULL);
}

void detenerSonido()
{
    mciSendString("stop sonido", NULL, 0, NULL);
    mciSendString("close sonido", NULL, 0, NULL);
}
