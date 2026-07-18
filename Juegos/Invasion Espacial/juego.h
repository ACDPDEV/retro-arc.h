#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "consola2.h"
<<<<<<< HEAD
#include "figuras.h"
=======
#include "figuritas.h"
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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
<<<<<<< HEAD
    return rand() % (ANCHO_PANTALLA - ANCHO_METEORITO3 - 2) + 1;
=======
    return rand() % (ANCHO_PANTALLA - ANCHO_METEORITO - 2) + 1;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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

<<<<<<< HEAD
const int VIDAS_INICIALES = 5;
=======
const int VIDAS_INICIALES = 3;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


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

<<<<<<< HEAD
bool explotandoMeteorito1 = false;
int  contadorExplosion1 = 0;

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

int xMeteorito2;
int yMeteorito2;

<<<<<<< HEAD
bool explotandoMeteorito2 = false;
int  contadorExplosion2 = 0;

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

int xMeteorito3;
int yMeteorito3;

<<<<<<< HEAD
bool explotandoMeteorito3 = false;
int  contadorExplosion3 = 0;

// Cuantos frames dura la animacion de la explosion
const int DURACION_EXPLOSION = 8;

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


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
<<<<<<< HEAD
// VIDA DEL JEFE FINAL
//=========================================================

const int VIDA_INICIAL_JEFE = 5;

int vidaJefe = VIDA_INICIAL_JEFE;

//=========================================================
// INVULNERABILIDAD TEMPORAL DEL JUGADOR
//=========================================================
// Al recibir un golpe, el jugador queda unos frames sin poder
// recibir daÃ±o de nuevo, para que un mismo choque no le quite
// varias vidas de una sola vez.

bool invulnerable = false;

int contadorInvulnerable = 0;

const int DURACION_INVULNERABILIDAD = 20;

//=========================================================
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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

<<<<<<< HEAD
    explotandoMeteorito1 = false;

    contadorExplosion1 = 0;

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    xMeteorito2 = posicionAleatoriaMeteorito();

    yMeteorito2 = -20;

<<<<<<< HEAD
    explotandoMeteorito2 = false;

    contadorExplosion2 = 0;

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    xMeteorito3 = posicionAleatoriaMeteorito();

    yMeteorito3 = -35;

<<<<<<< HEAD
    explotandoMeteorito3 = false;

    contadorExplosion3 = 0;

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


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



<<<<<<< HEAD
    // JEFE FINAL - VIDA

    vidaJefe = VIDA_INICIAL_JEFE;

    // INVULNERABILIDAD

    invulnerable = false;

    contadorInvulnerable = 0;

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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

<<<<<<< HEAD
    imprimir("+");


    for(int i=1;i<ANCHO_PANTALLA-1;i++)
        imprimir("-");


    imprimir("+");
=======
    cout<<"+";


    for(int i=1;i<ANCHO_PANTALLA-1;i++)
        cout<<"-";


    cout<<"+";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08



    // BORDES LATERALES

    gotoxy(0,1);

<<<<<<< HEAD
    imprimir("|");
=======
    cout<<"¦";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


    gotoxy(ANCHO_PANTALLA-1,1);

<<<<<<< HEAD
    imprimir("|");
=======
    cout<<"¦";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08



    // BORDE INFERIOR

    gotoxy(0,2);

<<<<<<< HEAD
    imprimir("+"); 


    for(int i=1;i<ANCHO_PANTALLA-1;i++)
        imprimir("-");


    imprimir("+");
=======
    cout<<"+"; 


    for(int i=1;i<ANCHO_PANTALLA-1;i++)
        cout<<"-";


    cout<<"+";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08



    color(15);



    // VIDAS

    gotoxy(3,1);

<<<<<<< HEAD
    imprimir("VIDAS:");
=======
    cout<<"VIDAS:";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


    if(vidas>=1)
        dibujarVida(14,0);


    if(vidas>=2)
<<<<<<< HEAD
        dibujarVida(24,0);


    if(vidas>=3)
        dibujarVida(34,0);


    if(vidas>=4)
        dibujarVida(44,0);


    if(vidas>=5)
        dibujarVida(54,0);
=======
        dibujarVida(26,0);


    if(vidas>=3)
        dibujarVida(38,0);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08



    // PUNTAJE

    gotoxy(80,1);

<<<<<<< HEAD
    imprimir("PUNTOS: "); imprimir(puntos);
=======
    cout<<"PUNTOS: "<<puntos;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08



    // NIVEL

    gotoxy(155,1);

<<<<<<< HEAD
    imprimir("NIVEL: "); imprimir(nivel);
=======
    cout<<"NIVEL: "<<nivel;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

}



//=========================================================
// VERIFICAR COLISIONES
//=========================================================

void verificarColisiones()
{


    // BALA - METEORITO 1

<<<<<<< HEAD
    if(disparandoJugador &&
       !explotandoMeteorito1 &&
       colisionBalaMeteorito1(
=======
    if(colisionBalaMeteorito1(
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
        xBalaJugador,
        yBalaJugador,
        xMeteorito1,
        yMeteorito1))
    {

        puntos += PUNTOS_METEORITO;


        disparandoJugador=false;


<<<<<<< HEAD
        explotandoMeteorito1 = true;

        contadorExplosion1 = DURACION_EXPLOSION;

        Beep(1200, 60); // Explosion (meteorito chico: sonido agudo y corto)
=======
        borrarMeteorito1(
            xMeteorito1,
            yMeteorito1);



        xMeteorito1 =
        posicionAleatoriaMeteorito();


        yMeteorito1=-10;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    }




    // BALA - METEORITO 2


<<<<<<< HEAD
    if(disparandoJugador &&
       !explotandoMeteorito2 &&
       colisionBalaMeteorito2(
=======
    if(colisionBalaMeteorito2(
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
        xBalaJugador,
        yBalaJugador,
        xMeteorito2,
        yMeteorito2))
    {


        puntos += PUNTOS_METEORITO;


        disparandoJugador=false;


<<<<<<< HEAD
        explotandoMeteorito2 = true;

        contadorExplosion2 = DURACION_EXPLOSION;

        Beep(700, 90); // Explosion (meteorito mediano)
=======

        borrarMeteorito2(
            xMeteorito2,
            yMeteorito2);



        xMeteorito2 =
        posicionAleatoriaMeteorito();


        yMeteorito2=-20;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    }




    // BALA - METEORITO 3


<<<<<<< HEAD
    if(disparandoJugador &&
       !explotandoMeteorito3 &&
       colisionBalaMeteorito3(
=======
    if(colisionBalaMeteorito3(
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
        xBalaJugador,
        yBalaJugador,
        xMeteorito3,
        yMeteorito3))
    {


        puntos += PUNTOS_METEORITO;


        disparandoJugador=false;


<<<<<<< HEAD
        explotandoMeteorito3 = true;

        contadorExplosion3 = DURACION_EXPLOSION;

        Beep(350, 130); // Explosion (meteorito gigante: sonido grave y mas largo)

    }



    // BALA - OVNI 1

    if(nivel>=2 &&
       disparandoJugador &&
       colisionBalaOvni1(
        xBalaJugador,
        yBalaJugador,
        xOvni1,
        yOvni1))
    {
        puntos += PUNTOS_OVNI1;

        disparandoJugador = false;

        yOvni1 = -40;
        xOvni1 = posicionAleatoriaOvni1();

        Beep(900, 100); // Explosion ovni 1
    }



    // BALA - OVNI 2

    if(nivel>=3 &&
       disparandoJugador &&
       colisionBalaOvni2(
        xBalaJugador,
        yBalaJugador,
        xOvni2,
        yOvni2))
    {
        puntos += PUNTOS_OVNI2;

        disparandoJugador = false;

        yOvni2 = -70;
        xOvni2 = posicionAleatoriaOvni2();

        Beep(600, 130); // Explosion ovni 2
    }



    // BALA - JEFE FINAL

    if(nivel>=4 &&
       disparandoJugador &&
       colisionBalaJefeFinal(
        xBalaJugador,
        yBalaJugador,
        xJefe,
        yJefe))
    {
        puntos += PUNTOS_JEFE;

        disparandoJugador = false;

        vidaJefe--;

        if(vidaJefe <= 0)
        {
            juegoVictoria = true;
            Beep(250, 400); // Explosion final del jefe (grave y larga)
        }
        else
        {
            Beep(1000, 50); // Impacto en el jefe (todavia sigue con vida)
        }
    }



    //=====================================================
    // DAÃ‘O AL JUGADOR (con invulnerabilidad temporal)
    //=====================================================

    if(!invulnerable)
    {
        bool golpeado = false;

        // JUGADOR - METEORITO 1
        if(!explotandoMeteorito1 &&
           colisionJugadorMeteorito1(xJugador, yJugador, xMeteorito1, yMeteorito1))
        {
            golpeado = true;

            explotandoMeteorito1 = true;
            contadorExplosion1 = DURACION_EXPLOSION;
        }

        // JUGADOR - METEORITO 2
        if(!explotandoMeteorito2 &&
           colisionJugadorMeteorito2(xJugador, yJugador, xMeteorito2, yMeteorito2))
        {
            golpeado = true;

            explotandoMeteorito2 = true;
            contadorExplosion2 = DURACION_EXPLOSION;
        }

        // JUGADOR - METEORITO 3
        if(!explotandoMeteorito3 &&
           colisionJugadorMeteorito3(xJugador, yJugador, xMeteorito3, yMeteorito3))
        {
            golpeado = true;

            explotandoMeteorito3 = true;
            contadorExplosion3 = DURACION_EXPLOSION;
        }

        // JUGADOR - OVNI 1
        if(nivel>=2 &&
           colisionJugadorOvni1(xJugador, yJugador, xOvni1, yOvni1))
        {
            golpeado = true;

            yOvni1 = -40;
            xOvni1 = posicionAleatoriaOvni1();
        }

        // JUGADOR - OVNI 2
        if(nivel>=3 &&
           colisionJugadorOvni2(xJugador, yJugador, xOvni2, yOvni2))
        {
            golpeado = true;

            yOvni2 = -70;
            xOvni2 = posicionAleatoriaOvni2();
        }

        // JUGADOR - BALA OVNI 1
        if(disparandoOvni1 &&
           colisionJugadorBalaOvni(xJugador, yJugador, xBalaOvni1, yBalaOvni1))
        {
            golpeado = true;

            disparandoOvni1 = false;
        }

        // JUGADOR - BALA OVNI 2
        if(disparandoOvni2 &&
           colisionJugadorBalaOvni(xJugador, yJugador, xBalaOvni2, yBalaOvni2))
        {
            golpeado = true;

            disparandoOvni2 = false;
        }

        // JUGADOR - LASER DEL JEFE (ambos rayos)
        if(disparandoJefe &&
           (colisionJugadorLaserJefe(xJugador, yJugador, xLaser1, yLaser1) ||
            colisionJugadorLaserJefe(xJugador, yJugador, xLaser2, yLaser2)))
        {
            golpeado = true;

            disparandoJefe = false;
        }

        if(golpeado)
        {
            vidas--;

            invulnerable = true;
            contadorInvulnerable = DURACION_INVULNERABILIDAD;

            Beep(200, 200); // Alarma: la nave del jugador recibio un golpe
        }
    }
}



//=========================================================
// ACTUALIZAR EXPLOSIONES
//=========================================================
// Dibuja la animacion de explosion mientras dura, y cuando
// termina hace reaparecer al meteorito arriba de la pantalla.

void actualizarExplosiones()
{
    if(explotandoMeteorito1)
    {
        dibujarExplosion1(xMeteorito1 + 3, yMeteorito1 + 2);

        contadorExplosion1--;

        if(contadorExplosion1 <= 0)
        {
            explotandoMeteorito1 = false;

            xMeteorito1 = posicionAleatoriaMeteorito();

            yMeteorito1 = -10;
        }
    }

    if(explotandoMeteorito2)
    {
        dibujarExplosion2(xMeteorito2 + 6, yMeteorito2 + 3);

        contadorExplosion2--;

        if(contadorExplosion2 <= 0)
        {
            explotandoMeteorito2 = false;

            xMeteorito2 = posicionAleatoriaMeteorito();

            yMeteorito2 = -20;
        }
    }

    if(explotandoMeteorito3)
    {
        dibujarExplosion3(xMeteorito3 + 8, yMeteorito3 + 4);

        contadorExplosion3--;

        if(contadorExplosion3 <= 0)
        {
            explotandoMeteorito3 = false;

            xMeteorito3 = posicionAleatoriaMeteorito();

            yMeteorito3 = -30;
        }
    }
=======

        borrarMeteorito3(
            xMeteorito3,
            yMeteorito3);



        xMeteorito3 =
        posicionAleatoriaMeteorito();


        yMeteorito3=-30;

    }

>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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
<<<<<<< HEAD
        yJugador,
        xBalaJugador,
        yBalaJugador,
        disparandoJugador);
=======
        yJugador);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08



    // METEORITOS

<<<<<<< HEAD
    bool escapoMeteorito1 = false;
    bool escapoMeteorito2 = false;
    bool escapoMeteorito3 = false;

    if(!explotandoMeteorito1)
        moverMeteorito1(
            xMeteorito1,
            yMeteorito1,
            escapoMeteorito1);



    if(!explotandoMeteorito2)
        moverMeteorito2(
            xMeteorito2,
            yMeteorito2,
            escapoMeteorito2);



    if(!explotandoMeteorito3)
        moverMeteorito3(
            xMeteorito3,
            yMeteorito3,
            escapoMeteorito3);

    // Si un meteorito llego abajo sin ser destruido, se pierde
    // una vida (antes esto no pasaba nunca).
    if(escapoMeteorito1 || escapoMeteorito2 || escapoMeteorito3)
        vidas--;
=======
    moverMeteorito1(
        xMeteorito1,
        yMeteorito1);



    moverMeteorito2(
        xMeteorito2,
        yMeteorito2);



    moverMeteorito3(
        xMeteorito3,
        yMeteorito3);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08




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

<<<<<<< HEAD
        moverBalaOvni1(
            xBalaOvni1,
            yBalaOvni1,
            disparandoOvni1);

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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

<<<<<<< HEAD
        moverBalaOvni2(
            xBalaOvni2,
            yBalaOvni2,
            disparandoOvni2);

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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

<<<<<<< HEAD
    	moverLaserJefe(
        xLaser1,
        yLaser1,
        xLaser2,
        yLaser2,
        disparandoJefe);

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
	}
    // BALA JUGADOR

    moverBalaJugador(
        xBalaJugador,
        yBalaJugador,
        disparandoJugador);

<<<<<<< HEAD
    // INVULNERABILIDAD TEMPORAL DEL JUGADOR

    if(invulnerable)
    {
        contadorInvulnerable--;

        if(contadorInvulnerable <= 0)
            invulnerable = false;
    }

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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

<<<<<<< HEAD
    iniciarDobleBuffer();

    // CICLO PRINCIPAL
    while(vidas>0 && !juegoVictoria)
    {
        limpiarPantallaCompleta();

=======
    // CICLO PRINCIPAL
    while(vidas>0 && !juegoVictoria)
    {
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
        actualizarJuego();

        verificarColisiones();

<<<<<<< HEAD
        actualizarExplosiones();

        actualizarNivel();

        dibujarJuego();

        mostrarFrame();
=======
        actualizarNivel();

        //dibujarJuego();
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

        Sleep(40);
    }

<<<<<<< HEAD
    finalizarDobleBuffer();

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
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
