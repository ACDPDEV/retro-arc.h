#include "game.h"
#include <stdio.h>
using namespace std;

char tablero[11][11];
void agregar_marco(){
	for(int i=0;i<11;i++)
		tablero[i][3]= 186;
	for(int i=0;i<11;i++)
		tablero[i][7]= 186;
	for(int i=0;i<11;i++)
		tablero[3][i]= 205;
	for(int i=0;i<11;i++)
		tablero[7][i]= 205;
		
	tablero[3][3]=206;
	tablero[3][7]=206;
	tablero[7][3]=206;
	tablero[7][7]=206;
}
int main(){
	agregar_marco();
	for(int i=0;i<11;i++){
		for(int j=0;j<11;j++){
		gotoxy(j+18, i+3);
		printf("%c",tablero[i][j]);
		printf("\n");}
	}
	  
	
	return 0;
}
