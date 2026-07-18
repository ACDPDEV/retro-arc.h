#include "console.h"

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
