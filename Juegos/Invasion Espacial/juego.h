#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "consola2.h"
#include "figuritas.h"
#include "movimientos.h"
#include "disparos.h"
#include "colisiones.h"

using namespace std;
//=========================================================
// FUNCIONES DE PANTALLAS
//=========================================================

void victoria(string usuario, int puntaje);

void gameOver(string usuario, int puntaje);


//=========================================================
// FUNCIONES AUXILIARES
//=========================================================

int posicionAleatoriaMeteorito()
{
    return rand() % (ANCHO_PANTALLA - ANCHO_METEORITO - 2) + 1;
}


int posicionAleatoriaOvni1()
{
    return rand() % (ANCHO_PANTALLA - ANCHO_OVNI1 - 2) + 1;
}


int posicionAleatoriaOvni2()
{
    return rand() % (ANCHO_PANTALLA - ANCHO_OVNI2 - 2) + 1;
}


int posicionAleatoriaJefe()
{
    return rand() % (ANCHO_PANTALLA - ANCHO_JEFE - 2) + 1;
}

//=========================================================
// CONFIGURACIÓN DEL JUEGO
//=========================================================

const int VIDAS_INICIALES = 3;


const int PUNTOS_METEORITO = 10;
const int PUNTOS_OVNI1 = 20;
const int PUNTOS_OVNI2 = 40;
const int PUNTOS_JEFE = 100;


//=========================================================
// JUGADOR
//=========================================================

int xJugador = 80;
int yJugador = 42;

//=========================================================
// ESTADÍSTICAS
//=========================================================

int vidas = VIDAS_INICIALES;

int puntos = 0;

int nivel = 1;


//=========================================================
// METEORITOS
//=========================================================

int xMeteorito1;
int yMeteorito1;


int xMeteorito2;
int yMeteorito2;


int xMeteorito3;
int yMeteorito3;



//=========================================================
// OVNIS
//=========================================================

int xOvni1;
int yOvni1;


int xOvni2;
int yOvni2;



// DIRECCIONES

int direccionOvni1 = 1;

int direccionOvni2 = 1;


//=========================================================
// JEFE FINAL
//=========================================================

int xJefe;

int yJefe;


int direccionJefe = 1;



//=========================================================
// DISPARO DEL JUGADOR
//=========================================================

int xBalaJugador;

int yBalaJugador;

bool disparandoJugador = false;



//=========================================================
// DISPAROS OVNI
//=========================================================

int xBalaOvni1;

int yBalaOvni1;

bool disparandoOvni1 = false;



int xBalaOvni2;

int yBalaOvni2;

bool disparandoOvni2 = false;



//=========================================================
// LASER DEL JEFE
//=========================================================

int xLaser1;

int yLaser1;


int xLaser2;

int yLaser2;


bool disparandoJefe = false;



//=========================================================
// ESTADO DEL JUEGO
//=========================================================

bool juegoTerminado = false;

bool juegoVictoria = false;



//=========================================================
// INICIALIZAR JUEGO
//=========================================================

void inicializarJuego()
{

    srand(time(NULL));


    // JUGADOR

    xJugador = 80;

    yJugador = 42;



    // ESTADÍSTICAS

    vidas = VIDAS_INICIALES;

    puntos = 0;

    nivel = 1;



    // METEORITOS

    xMeteorito1 = posicionAleatoriaMeteorito();

    yMeteorito1 = -5;


    xMeteorito2 = posicionAleatoriaMeteorito();

    yMeteorito2 = -20;


    xMeteorito3 = posicionAleatoriaMeteorito();

    yMeteorito3 = -35;



    // OVNI 1

    xOvni1 = posicionAleatoriaOvni1();

    yOvni1 = -40;

    // OVNI 2

    xOvni2 = posicionAleatoriaOvni2();

    yOvni2 = -70;

    // JEFE

    xJefe = posicionAleatoriaJefe();

    yJefe = -120;

    // DISPARO JUGADOR

    disparandoJugador = false;

    xBalaJugador = 0;

    yBalaJugador = 0;

    // DISPAROS OVNI

    disparandoOvni1 = false;

    xBalaOvni1 = 0;

    yBalaOvni1 = 0;

    disparandoOvni2 = false;

    xBalaOvni2 = 0;

    yBalaOvni2 = 0;

    // LASER JEFE

    disparandoJefe = false;

    xLaser1 = 0;

    yLaser1 = 0;


    xLaser2 = 0;

    yLaser2 = 0;



    // ESTADOS

    juegoTerminado = false;

    juegoVictoria = false;

}
//=========================================================
// MOSTRAR HUD
//=========================================================

void mostrarHUD()
{

    color(11);


    // BORDE SUPERIOR

    gotoxy(0,0);

    cout<<"+";


    for(int i=1;i<ANCHO_PANTALLA-1;i++)
        cout<<"-";


    cout<<"+";



    // BORDES LATERALES

    gotoxy(0,1);

    cout<<"¦";


    gotoxy(ANCHO_PANTALLA-1,1);

    cout<<"¦";



    // BORDE INFERIOR

    gotoxy(0,2);

    cout<<"+"; 


    for(int i=1;i<ANCHO_PANTALLA-1;i++)
        cout<<"-";


    cout<<"+";



    color(15);



    // VIDAS

    gotoxy(3,1);

    cout<<"VIDAS:";


    if(vidas>=1)
        dibujarVida(14,0);


    if(vidas>=2)
        dibujarVida(26,0);


    if(vidas>=3)
        dibujarVida(38,0);



    // PUNTAJE

    gotoxy(80,1);

    cout<<"PUNTOS: "<<puntos;



    // NIVEL

    gotoxy(155,1);

    cout<<"NIVEL: "<<nivel;

}



//=========================================================
// VERIFICAR COLISIONES
//=========================================================

void verificarColisiones()
{


    // BALA - METEORITO 1

    if(colisionBalaMeteorito1(
        xBalaJugador,
        yBalaJugador,
        xMeteorito1,
        yMeteorito1))
    {

        puntos += PUNTOS_METEORITO;


        disparandoJugador=false;


        borrarMeteorito1(
            xMeteorito1,
            yMeteorito1);



        xMeteorito1 =
        posicionAleatoriaMeteorito();


        yMeteorito1=-10;

    }




    // BALA - METEORITO 2


    if(colisionBalaMeteorito2(
        xBalaJugador,
        yBalaJugador,
        xMeteorito2,
        yMeteorito2))
    {


        puntos += PUNTOS_METEORITO;


        disparandoJugador=false;



        borrarMeteorito2(
            xMeteorito2,
            yMeteorito2);



        xMeteorito2 =
        posicionAleatoriaMeteorito();


        yMeteorito2=-20;

    }




    // BALA - METEORITO 3


    if(colisionBalaMeteorito3(
        xBalaJugador,
        yBalaJugador,
        xMeteorito3,
        yMeteorito3))
    {


        puntos += PUNTOS_METEORITO;


        disparandoJugador=false;



        borrarMeteorito3(
            xMeteorito3,
            yMeteorito3);



        xMeteorito3 =
        posicionAleatoriaMeteorito();


        yMeteorito3=-30;

    }

}



//=========================================================
// ACTUALIZAR NIVEL
//=========================================================

void actualizarNivel()
{

    if(puntos>=500)
    {
        nivel=4;
    }

    else if(puntos>=250)
    {
        nivel=3;
    }

    else if(puntos>=100)
    {
        nivel=2;
    }

    else
    {
        nivel=1;
    }

}



//=========================================================
// ACTUALIZAR JUEGO
//=========================================================

void actualizarJuego()
{


    // MOVIMIENTO JUGADOR

    moverJugador(
        xJugador,
        yJugador);



    // METEORITOS

    moverMeteorito1(
        xMeteorito1,
        yMeteorito1);



    moverMeteorito2(
        xMeteorito2,
        yMeteorito2);



    moverMeteorito3(
        xMeteorito3,
        yMeteorito3);




    // OVNI 1

    if(nivel>=2)
    {

        moverOvni1(
            xOvni1,
            yOvni1,
            direccionOvni1);



        dispararOvni1(
            xOvni1,
            yOvni1,
            xBalaOvni1,
            yBalaOvni1,
            disparandoOvni1);

    }




    // OVNI 2

    if(nivel>=3)
    {

        moverOvni2(
            xOvni2,
            yOvni2,
            direccionOvni2);



        dispararOvni2(
            xOvni2,
            yOvni2,
            xBalaOvni2,
            yBalaOvni2,
            disparandoOvni2);

    }

	// JEFE FINAL

	if(nivel>=4)
	{

   	 	moverJefe(
        xJefe,
        yJefe,
        direccionJefe);


    	dispararJefeFinal(
        xJefe,
        yJefe,
        xLaser1,
        yLaser1,
        xLaser2,
        yLaser2,
        disparandoJefe);

	}
    // BALA JUGADOR

    moverBalaJugador(
        xBalaJugador,
        yBalaJugador,
        disparandoJugador);

}
//=========================================================
// DIBUJAR JUEGO
//=========================================================

void dibujarJuego()
{
    mostrarHUD();
}
//=========================================================
// EJECUTAR JUEGO
//=========================================================

void ejecutarJuego(string usuario)
{
    system("cls");
    inicializarJuego();

    // CICLO PRINCIPAL
    while(vidas>0 && !juegoVictoria)
    {
        actualizarJuego();

        verificarColisiones();

        actualizarNivel();

        //dibujarJuego();

        Sleep(40);
    }

    system("cls");

    // FINAL DEL JUEGO
    if(juegoVictoria)
    {
        victoria(
            usuario,
            puntos);
    }

    else
    {

        gameOver(
            usuario,
            puntos);

    }

}
#endif
