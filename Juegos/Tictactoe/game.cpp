#include "game.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <iostream>
using namespace std;

const int TOTAL_PREGUNTAS = 30;

//MODO FUTBOL PREGUNTAS Y OPCIONES+++++++++++++++++++++++++++++++++++++++
string preguntas[TOTAL_PREGUNTAS] = {

"¿Quien gano el Mundial 2022?",
"¿Quien gano el Mundial 2018?",
"¿Cuantos Mundiales tiene Brasil?",
"¿En que pais se jugo el Mundial 2014?",
"¿Quien fue el maximo goleador del Mundial 2022?",
"¿Que seleccion gano el Mundial 2010?",
"¿Quien marco el gol de la final del Mundial 2010?",
"¿Que pais organizo el Mundial 2018?",
"¿Que seleccion gano la Copa America 2021?",
"¿Quien gano la Eurocopa 2024?",

"¿Cuantas Champions League tiene el FC Barcelona?",
"¿Que club gano la Champions League 2024?",
"¿Que club tiene mas Champions League?",
"¿Quien anoto el gol de la victoria en la final de Champions 2024?",
"¿Que equipo elimino al Barcelona en semifinales de Champions 2010?",
"¿Quien fue el maximo goleador historico de la Champions antes de Cristiano?",
"¿Que dorsal uso Messi en el PSG?",
"¿Que dorsal usa Cristiano Ronaldo con Portugal?",
"¿Quien gano el Balon de Oro 2010?",
"¿Quien gano el Balon de Oro 2023?",

"¿Que pais gano la primera Copa del Mundo?",
"¿Cual es el apodo de la seleccion brasilena?",
"¿Quien es el maximo goleador historico del Mundial?",
"¿Que jugador levanto la Copa del Mundo para Argentina en 2022?",
"¿Que pais gano la Eurocopa 2016?",
"¿Que club ficho primero a Cristiano Ronaldo tras salir del Sporting?",
"¿Quien es conocido como O Rei?",
"¿Que seleccion elimino a Brasil en cuartos del Mundial 2022?",
"¿Que jugador marco un triplete en la final del Mundial 2022?",
"¿Que club gano la primera Champions League?"

};

string opcionA[TOTAL_PREGUNTAS] = {

"Francia",
"Croacia",
"4",
"Sudafrica",
"Lionel Messi",

"Holanda",
"David Villa",
"Qatar",
"Brasil",
"Inglaterra",

"4",
"Borussia Dortmund",
"Milan",
"Vinicius Jr.",
"Inter de Milan",

"Raul",
"10",
"7",
"Andres Iniesta",
"Erling Haaland",

"Argentina",
"La Roja",
"Ronaldo Nazario",
"Di Maria",
"Francia",

"Real Madrid",
"Garrincha",
"Croacia",
"Messi",
"Milan"

};

string opcionB[TOTAL_PREGUNTAS] = {

"Argentina",
"Francia",
"5",
"Brasil",
"Julian Alvarez",

"Alemania",
"Andres Iniesta",
"Rusia",
"Argentina",
"España",

"5",
"Manchester City",
"Liverpool",
"Rodrygo",
"Chelsea",

"Messi",
"30",
"9",
"Xavi",
"Lionel Messi",

"Uruguay",
"La Canarinha",
"Miroslav Klose",
"Messi",
"Alemania",

"Manchester United",
"Ronaldo",
"Argentina",
"Julian Álvarez",
"Barcelona"

};

string opcionC[TOTAL_PREGUNTAS] = {

"Brasil",
"Belgica",
"6",
"Rusia",
"Kylian Mbappe",

"Brasil",
"Fernando Torres",
"Alemania",
"Chile",
"Francia",

"6",
"Real Madrid",
"Barcelona",
"Jude Bellingham",
"Arsenal",

"Shevchenko",
"19",
"10",
"Lionel Messi",
"Kylian Mbappe",

"Brasil",
"La Albiceleste",
"Pele",
"Otamendi",
"Portugal",

"Juventus",
"Pele",
"Francia",
"Kylian Mbappé",
"Benfica"

};

string opcionD[TOTAL_PREGUNTAS] = {

"Alemania",
"Alemania",
"7",
"Qatar",
"Olivier Giroud",

"España",
"Xavi",
"Francia",
"Uruguay",
"Italia",

"7",
"Bayern Múnich",
"Real Madrid",
"Dani Carvajal",
"Manchester United",

"Benzema",
"7",
"17",
"Wesley Sneijder",
"Kevin De Bruyne",

"Italia",
"Los Galos",
"Messi",
"Dibu Martinez",
"España",

"Al-Nassr",
"Ronaldinho",
"Paises Bajos",
"Griezmann",
"Milan"

};

char respuestaCorrecta[TOTAL_PREGUNTAS] = {

'B',
'B',
'B',
'B',
'C',
'D',
'B',
'B',
'B',
'B',

'B',
'C',
'D',
'A',
'A',
'A',
'B',
'A',
'C',
'B',

'B',
'B',
'B',
'B',
'C',
'B',
'C',
'A',
'C',
'C'

};

//++++++++++++++++++++++++++++++++++++++++++++++++++++

void menuPrincipal(){

    system("cls");
    color(15);

    gotoxy(25,2);
    cout << "========================";

    gotoxy(28,3);
    cout << "TIC TAC TOE";

    gotoxy(25,4);
    cout << "========================";

    gotoxy(29,7);
    cout << "1. Original";

    gotoxy(29,9);
    cout << "2. Modo Futbol";

    gotoxy(29,11);
    cout << "3. Salir";

    gotoxy(22,14);
    cout << "Seleccione una opcion: ";
}
bool usada[TOTAL_PREGUNTAS];

int preguntasUsadas = 0;

//*********PARTE 1****** (inicialización del tablero)****************
void agregar_marco(){
	for(int i=0;i<11;i++){
		tablero[i][3]= 186;
		tablero[i][7]= 186;
		tablero[3][i]= 205;
		tablero[7][i]= 205;
	}
	tablero[3][3]=206;
	tablero[3][7]=206;
	tablero[7][3]=206;
	tablero[7][7]=206;
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

void mostrar_tablero(){
	for(int i=0;i<11;i++){
		for(int j=0;j<11;j++){
		gotoxy(j+18, i+3);
		if(tablero[i][j]=='X')
                color(12);      // Rojo
            else if(tablero[i][j]=='O')
                color(9);       // Azul
            else
                color(15);      // Blanco
		printf("%c",tablero[i][j]);
		}
	}
	color(15);   // Regresa al blanco
}

void llenar_tablero_con_espacios(){
	for(int i=0; i<11; i++){
		for(int j=0; j<11; j++)
			tablero[i][j]= 32;
	}
}

void agregarNumeros(){

    tablero[1][1]='1';
    tablero[1][5]='2';
    tablero[1][9]='3';

    tablero[5][1]='4';
    tablero[5][5]='5';
    tablero[5][9]='6';

    tablero[9][1]='7';
    tablero[9][5]='8';
    tablero[9][9]='9';
}
//****************** (inicialización)****************
void inicializarJuego(){


    llenar_tablero_con_espacios();

    agregar_marco();

    agregarNumeros();

    OcultarCursor();

    mostrar_tablero();
}



//*********PARTE 2**** (JUGADAS)*************************************
void agregarFicha(char pos, char ficha){

    if(pos=='1')
        tablero[1][1]=ficha;
    else if(pos=='2')
        tablero[1][5]=ficha;
    else if(pos=='3')
        tablero[1][9]=ficha;
    else if(pos=='4')
        tablero[5][1]=ficha;
    else if(pos=='5')
        tablero[5][5]=ficha;
    else if(pos=='6')
        tablero[5][9]=ficha;
    else if(pos=='7')
        tablero[9][1]=ficha;
    else if(pos=='8')
        tablero[9][5]=ficha;
    else if(pos=='9')
        tablero[9][9]=ficha;
}
bool celdaVacia(char tecla){

    if(tecla=='1'){
        if(tablero[1][1]=='1')
            return true;
        else
            return false;
    }

    else if(tecla=='2'){
        if(tablero[1][5]=='2')
            return true;
        else
            return false;
    }

    else if(tecla=='3'){
        if(tablero[1][9]=='3')
            return true;
        else
            return false;
    }

    else if(tecla=='4'){
        if(tablero[5][1]=='4')
            return true;
        else
            return false;
    }

    else if(tecla=='5'){
        if(tablero[5][5]=='5')
            return true;
        else
            return false;
    }

    else if(tecla=='6'){
        if(tablero[5][9]=='6')
            return true;
        else
            return false;
    }

    else if(tecla=='7'){
        if(tablero[9][1]=='7')
            return true;
        else
            return false;
    }

    else if(tecla=='8'){
        if(tablero[9][5]=='8')
            return true;
        else
            return false;
    }

    else if(tecla=='9'){
        if(tablero[9][9]=='9')
            return true;
        else
            return false;
    }

    return false;
}
//*********PARTE 3***** (VALIDACIONES)****************
bool ganar(char ficha){

    if(tablero[1][1]==ficha && tablero[1][5]==ficha && tablero[1][9]==ficha ||
       tablero[5][1]==ficha && tablero[5][5]==ficha && tablero[5][9]==ficha ||
       tablero[9][1]==ficha && tablero[9][5]==ficha && tablero[9][9]==ficha ||

       tablero[1][1]==ficha && tablero[5][1]==ficha && tablero[9][1]==ficha ||
       tablero[1][5]==ficha && tablero[5][5]==ficha && tablero[9][5]==ficha ||
       tablero[1][9]==ficha && tablero[5][9]==ficha && tablero[9][9]==ficha ||

       tablero[1][1]==ficha && tablero[5][5]==ficha && tablero[9][9]==ficha ||
       tablero[1][9]==ficha && tablero[5][5]==ficha && tablero[9][1]==ficha)
        return true;
    else
        return false;
}

bool tableroLleno(){
	if(tablero[1][1] != '1' && tablero[1][5] != '2' && tablero[1][9] != '3' &&
	 	tablero[5][1] != '4' && tablero[5][5] != '5' && tablero[5][9] != '6' &&			
	 	tablero[9][1] != '7' && tablero[9][5] != '8' && tablero[9][9] != '9')
	 return true;
	else 
		return false;
}

//*********PARTE 4**** (INTERFAZ)****************
void mostrar_Instrucciones(){

    system("cls");

    color(14);
    gotoxy(28,2); cout<<("TIC TAC TOE");
    color(15);

    gotoxy(1,4);  cout<<("INSTRUCCIONES:");
    gotoxy(1,6);  cout<<("1. El jugador X comienza la partida.");
    gotoxy(1,7);  cout<<("2. Presione un numero del 1 al 9 para jugar.");
    gotoxy(1,8);  cout<<("3. No puede elegir una casilla ocupada.");
    gotoxy(1,9);  cout<<("4. Gana quien forme una linea de 3 fichas.");

    gotoxy(1,11); cout<<("Distribucion de las casillas:");

    gotoxy(8,13); cout<<("1 | 2 | 3");
    gotoxy(8,14); cout<<("--+---+--");
    gotoxy(8,15); cout<<("4 | 5 | 6");
    gotoxy(8,16); cout<<("--+---+--");
    gotoxy(8,17); cout<<("7 | 8 | 9");

    gotoxy(1,20); cout<<("Presione cualquier tecla para comenzar...");
    getch();

    system("cls");
}
void mostrar_InstruccionesFutbol(){

    system("cls");

    color(14);

    gotoxy(28,2);
    cout<<"TIC TAC TOE FUTBOL";

    color(15);


    gotoxy(1,4);
    cout<<"INSTRUCCIONES MODO FUTBOL:";


    gotoxy(1,6);
    cout<<"1. Cada jugador debe responder una pregunta de futbol.";


    gotoxy(1,7);
    cout<<"2. Si responde correctamente puede colocar su ficha.";


    gotoxy(1,8);
    cout<<"3. Si responde mal pierde su turno.";


    gotoxy(1,9);
    cout<<"4. Forma una linea de 3 fichas para ganar.";


    gotoxy(1,11);
    cout<<"Categorias:";


    gotoxy(5,13);
    cout<<"- Mundiales";


    gotoxy(5,14);
    cout<<"- Champions League";


    gotoxy(5,15);
    cout<<"- Balon de Oro";


    gotoxy(5,16);
    cout<<"- Futbol internacional";


    gotoxy(1,20);
    cout<<"Presione cualquier tecla para comenzar...";


    getch();

    system("cls");
}
void turnoX(){

    char tecla;

    do{
        gotoxy(1,1);
        cout<<("Turno de X");
        tecla = getch();
    }while(!celdaVacia(tecla));

    agregarFicha(tecla, 'X');

    mostrar_tablero();
}
void turnoO(){

    char tecla;

    do{
        gotoxy(1,1);
        cout<<("Turno de O");
        tecla = getch();
    }while(!celdaVacia(tecla));

    agregarFicha(tecla, 'O');

    mostrar_tablero();
}
void mostrarResultado(){

    gotoxy(1,15);

    if(ganar('X')){
        color(12);
        cout<<("Gano X");
    }
    else if(ganar('O')){
        color(9);
        cout<<("Gano O");
    }
    else{
        color(15);
        cout<<("Empate");
    }

    color(15);
}

void victoriaFutbol(){

    system("cls");

    color(14);

    gotoxy(28,4);
    cout<<"==============================";

    gotoxy(35,5);
    cout<<"!! VICTORIAAA !!";

    gotoxy(28,6);
    cout<<"==============================";


    if(ganar('X')){

        color(12);

        gotoxy(35,9);
        cout<<"GANADOR: JUGADOR X";

    }
    else if(ganar('O')){

        color(9);

        gotoxy(35,9);
        cout<<"GANADOR: JUGADOR O";

    }
    else{

        color(15);

        gotoxy(38,9);
        cout<<"EMPATE";

    }


    color(15);

    gotoxy(32,13);
    cout<<"Gracias por jugar";

    gotoxy(32,15);
    cout<<"Presione una tecla...";

    getch();

}

void jugarOriginal(){
	 mostrar_Instrucciones();
    inicializarJuego();

    while(true){

        turnoX();

        if(ganar('X') || tableroLleno())
            break;

        turnoO();

        if(ganar('O') || tableroLleno())
            break;
    }

    mostrarResultado();

    despedida();
}
//Modo futbol
void mostrarPanelQuiz(){

    color(14);

    gotoxy(50,2);
    cout << "QUIZ FUTBOLERO";

    gotoxy(50,3);
    cout << "======================";

    color(15);
}


void jugarFutbol(){
	mostrar_InstruccionesFutbol();
    inicializarJuego();
    preguntasUsadas = 0;

	for(int i=0; i<TOTAL_PREGUNTAS; i++){
    usada[i] = false;
	}
	dibujarPanelQuiz();
    

    while(true){

        turnoFutbolX();

        if(ganar('X') || tableroLleno())
            break;

        turnoFutbolO();

        if(ganar('O') || tableroLleno())
            break;
    }

    victoriaFutbol();
}
  
void turnoFutbolX(){

    char tecla;

    gotoxy(1,1);
    cout << "Turno de X";

    if(!preguntaFutbol()){
        return;
    }

gotoxy(50,5);
color(10);
cout<<"Respuesta correcta";

gotoxy(50,7);
color(15);
cout<<"Seleccione una casilla (1-9)";

	agregar_marco();
	mostrar_tablero();	
    do{
        gotoxy(1,2);
        cout << "Elija una casilla: ";
        tecla = getch();
    }while(!celdaVacia(tecla));

    agregarFicha(tecla,'X');

    mostrar_tablero();
    limpiarPanelQuiz();
}

void turnoFutbolO(){

    char tecla;

    gotoxy(1,1);
    cout << "Turno de O";

    if(!preguntaFutbol()){
        return;
	}

gotoxy(50,5);
color(10);
cout<<"Respuesta correcta";

gotoxy(50,7);
color(15);
cout<<"Seleccione una casilla (1-9)";

    
	agregar_marco();
	mostrar_tablero();
    do{
        gotoxy(1,2);
        cout << "Elija una casilla: ";
        tecla = getch();
    }while(!celdaVacia(tecla));

    agregarFicha(tecla,'O');

    mostrar_tablero();
    limpiarPanelQuiz();
}

void despedida(){

    gotoxy(1,18);
    color(15);
    cout<<("Presione cualquier tecla para salir...");
    getch();

}

bool preguntaFutbol(){

    limpiarPanelQuiz();

    if(preguntasUsadas == TOTAL_PREGUNTAS){

    for(int j=0; j<TOTAL_PREGUNTAS; j++){
        usada[j] = false;
    	}

    	preguntasUsadas = 0;
	}

		int i;

do{
    i = rand() % TOTAL_PREGUNTAS;
}while(usada[i]);

usada[i] = true;
preguntasUsadas++;
    color(15);
    
    gotoxy(50,5);
if(preguntas[i].length() <= 38){
    cout << preguntas[i];
}
else{
    cout << preguntas[i].substr(0,38);
    gotoxy(50,6);
    cout << preguntas[i].substr(38);

}

    gotoxy(50,7);
    cout << "A) " << opcionA[i];

    gotoxy(50,8);
    cout << "B) " << opcionB[i];

    gotoxy(50,9);
    cout << "C) " << opcionC[i];

    gotoxy(50,10);
    cout << "D) " << opcionD[i];

    gotoxy(50,12);
    cout << "Respuesta: ";

    char respuesta = getch();

    respuesta = toupper(respuesta);

    cout << respuesta;

    if(respuesta == respuestaCorrecta[i]){

        gotoxy(50,14);
        color(10);
        cout << "¡Correcto!";

        getch();

        limpiarPanelQuiz();

        return true;
    }

    gotoxy(50,14);
    color(12);
    cout << "Incorrecto. Pierdes el turno.";

    getch();

    limpiarPanelQuiz();

    return false;
}


void dibujarPanelQuiz(){

    color(14);

    // Esquinas
 	gotoxy(48,2); printf("%c",201);
	gotoxy(90,2); printf("%c",187);

	gotoxy(48,14); printf("%c",200);
	gotoxy(90,14); printf("%c",188);

    // Líneas horizontales
    for(int i=49;i<90;i++){
    gotoxy(i,2); printf("%c",205);
    gotoxy(i,14); printf("%c",205);
}

    // Líneas verticales
    for(int i=3;i<14;i++){
    gotoxy(48,i); printf("%c",186);
    gotoxy(90,i); printf("%c",186);
}

    // Título
    color(15);
    gotoxy(60,3);
cout<<"QUIZ FUTBOLERO";
}
void limpiarPanelQuiz(){

    color(15);

    for(int i=4;i<14;i++){

        gotoxy(49,i);

        for(int j=0;j<40;j++){
            cout<<" ";
        }
    }

    dibujarPanelQuiz();
}
bool jugarNuevamente(){

    char opcion;


    gotoxy(25,20);
    cout<<"¿Desea jugar otra vez? (S/N): ";


    opcion=getch();

    opcion=toupper(opcion);


    if(opcion=='S')
        return true;

    else
        return false;

}
