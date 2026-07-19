#ifndef GAME_H
#define GAME_H

#include "console.h"
const int TAM = 11;
extern char tablero[TAM][TAM];

void inicializarJuego();
void mostrarResultado();
void jugarOriginal();
bool jugarNuevamente();

void mostrarPanelQuiz();
void dibujarPanelQuiz();
void limpiarPanelQuiz();
//MODO FUTBOL
void jugarFutbol();
void turnoFutbolX();
void turnoFutbolO();
bool preguntaFutbol();
void victoriaFutbol();
//++++++++++++++
void intro();

void menuPrincipal();

void agregar_marco();
void pintarmarco();
void mostrar_tablero();
void llenar_tablero_con_espacios();
void agregarNumeros();
void turnoX();
void turnoO();

void agregarFicha(char pos, char ficha);
bool celdaVacia(char tecla);

bool ganar(char ficha);
bool tableroLleno();

void mostrar_Instrucciones();
void mostrar_InstruccionesFutbol();

void despedida();
#endif
