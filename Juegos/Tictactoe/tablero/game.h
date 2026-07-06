#include <windows.h>
#include <stdio.h>
#include <conio.h>

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
void pintarmarco(){ //Mostrar límites del escenario
//lineas horizontales
for(int i=2;i<78;i++){
	gotoxy(i,3); printf("%c", 205);
	gotoxy(i,23); printf("%c", 205); 
}
//Lineas verticales
for(int v=4;v<23;v++){
	gotoxy(2,v); printf("%c", 186);
	gotoxy(77,v); printf("%c", 186);	  
}	
//esquinas
	gotoxy(2,3); printf("%c", 201);
	gotoxy(2,23); printf("%c", 200); 	
	gotoxy(77,3); printf("%c", 187);
	gotoxy(77,23); printf("%c", 188); 
	
}
void pausa(int x){
	Sleep(x);
}




