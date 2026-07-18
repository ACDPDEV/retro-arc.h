#ifndef PANTALLAS_H
#define PANTALLAS_H

#include <iostream>
#include <windows.h>
#include <conio.h>

#include "consola2.h"
<<<<<<< HEAD
#include "figuras.h"
=======
#include "figuritas.h"
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

using namespace std;
//=========================================================
// FUNCIONES DEL JUEGO
//=========================================================

void ejecutarJuego(string usuario);
//=========================================================
// PROTOTIPOS DE PANTALLAS
//=========================================================

void presentacion();

bool clave();
void bienvenida();
void claveIncorrecta();

void menu();

void instrucciones();
void creditos();
<<<<<<< HEAD
void despedida(string usuario);
=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

void gameOver();
void victoria();
//=========================================================
// PRESENTACIÓN
//=========================================================

void presentacion()
{
    system("cls");

    // Fondo de estrellas
    fondoEspacialAnimado();


    // Logo del juego
    dibujarTitulo();


    color(11);

    escribirTexto(62,28,
    "CARGANDO SISTEMA ESPACIAL...",35);


    Sleep(500);


    //=====================================================
    // BARRA DE CARGA
    //=====================================================

    gotoxy(65,32);
    color(15);
    cout<<"[                    ]";


    for(int i=0;i<=20;i++)
    {
        gotoxy(66+i,32);

        color(10);

<<<<<<< HEAD
        cout<<"|";
=======
        cout<<"¦";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

        gotoxy(70,34);

        color(15);

        cout<<i*5<<"%";

        Beep(800,20);

        Sleep(100);
    }


    //=====================================================
    // SISTEMA LISTO
    //=====================================================

    color(10);

    escribirTexto(75,37,
    "SISTEMA ONLINE",40);


    Beep(1000,200);


    Sleep(1000);
}

//=========================================================
// SEGURIDAD - CLAVE DE ACCESO
//=========================================================

bool clave()
{
    string codigo;

<<<<<<< HEAD
    const int MAX_INTENTOS = 3;

    for(int intento = 1; intento <= MAX_INTENTOS; intento++)
    {
        system("cls");

        color(11);

        gotoxy(55,8);
        cout<<"==========================================";

        gotoxy(65,10);
        cout<<"CENTRO DE DEFENSA ESPACIAL";

        gotoxy(55,12);
        cout<<"==========================================";


        color(15);

        gotoxy(65,17);
        cout<<"INGRESE CLAVE DE ACCESO:";


        color(14);

        gotoxy(65,18);
        cout<<"Intento "<<intento<<" de "<<MAX_INTENTOS;


        color(15);

        gotoxy(65,20);
        cout<<"> ";

        getline(cin,codigo);


        if(codigo=="1234")
        {
            return true;
        }


        if(intento < MAX_INTENTOS)
        {
            color(12);

            gotoxy(65,23);
            cout<<"CLAVE INCORRECTA. INTENTELO DE NUEVO.";

            Beep(300,200);

            Sleep(1400);
        }
    }

    return false;
=======
    system("cls");

    color(11);

    gotoxy(55,8);
    cout<<"==========================================";

    gotoxy(65,10);
    cout<<"CENTRO DE DEFENSA ESPACIAL";

    gotoxy(55,12);
    cout<<"==========================================";


    color(15);

    gotoxy(65,17);
    cout<<"INGRESE CLAVE DE ACCESO:";


    gotoxy(65,19);
    cout<<"> ";

    getline(cin,codigo);


    if(codigo=="ATAQUE ESPACIAL")
    {
        return true;
    }
    else
    {
        return false;
    }
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
}
//=========================================================
// SOLICITAR NOMBRE DE USUARIO
//=========================================================

string solicitarUsuario()
{
    string usuario;


    system("cls");


    color(11);

    gotoxy(55,8);
    cout<<"==========================================";

    gotoxy(65,10);
    cout<<"IDENTIFICACION DEL COMANDANTE";

    gotoxy(55,12);
    cout<<"==========================================";


    color(15);

    gotoxy(65,16);
    cout<<"Ingrese nombre de usuario:";


    gotoxy(65,18);
    cout<<"> ";

    getline(cin,usuario);


    if(usuario=="")
    {
        usuario="COMANDANTE";
    }


    return usuario;
}
//=========================================================
// ACCESO CORRECTO
//=========================================================

void bienvenida(string usuario)
{
    system("cls");


    color(10);

    escribirTexto(
        65,
<<<<<<< HEAD
        6,
=======
        15,
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
        "ACCESO AUTORIZADO",
        40);


<<<<<<< HEAD
    color(11);

    gotoxy(55,9);
=======

    color(11);


    gotoxy(55,18);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    cout<<"BIENVENIDO COMANDANTE "<<usuario;


<<<<<<< HEAD
    // FIGURA ANIMADA: la nave llega volando hasta el centro

    int xNave;
    int yNave = 15;

    for(xNave = 20; xNave <= 80; xNave += 4)
    {
        if(xNave > 20)
            borrarJugador(xNave - 4, yNave);

        dibujarJugador(xNave, yNave);

        Sleep(25);
    }


    color(15);

    gotoxy(55,40);
    cout<<"Preparando sistemas de combate...";

=======
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    Beep(1000,200);


    Sleep(1500);
}
//=========================================================
// CLAVE INCORRECTA
//=========================================================

void claveIncorrecta()
{
    system("cls");

    color(12);

<<<<<<< HEAD
    gotoxy(40,13);
    cout<<"+--------------------------------------------------------------+";

    gotoxy(40,14);
    cout<<"|                                                                |";

    gotoxy(40,15);
    cout<<"|   ACCESO DENEGADO                                             |";

    gotoxy(40,16);
    cout<<"|                                                                |";

    gotoxy(40,17);
    cout<<"|   Intento 3 veces ingresar con una clave incorrecta.          |";

    gotoxy(40,18);
    cout<<"|   Comuniquese con el administrador.                          |";

    gotoxy(40,19);
    cout<<"|                                                                |";

    gotoxy(40,20);
    cout<<"+--------------------------------------------------------------+";


    Beep(400,300);
    Beep(250,400);

    Sleep(2500);
=======
    escribirTexto(65,15,
    "ACCESO DENEGADO",40);


    color(14);

    escribirTexto(55,18,
    "CLAVE INCORRECTA",40);


    Beep(400,300);

    Sleep(1500);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
}
//=========================================================
// MENÚ
//=========================================================

void menu(string usuario)
{
    int opcion;


    do
    {
        system("cls");


        color(11);

        gotoxy(55,5);
        cout<<"==========================================";

        gotoxy(62,7);
        cout<<"INVASORES ESPACIALES";

        gotoxy(55,9);
        cout<<"==========================================";


        color(15);

        gotoxy(70,13);
        cout<<"1. INICIAR MISION";


        gotoxy(70,15);
        cout<<"2. INSTRUCCIONES";


        gotoxy(70,17);
        cout<<"3. CREDITOS";


        gotoxy(70,19);
        cout<<"4. SALIR";


        color(10);

        gotoxy(65,23);
        cout<<"Seleccione una opcion: ";

        cin>>opcion;
<<<<<<< HEAD

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            opcion = -1;
        }
        else
        {
            cin.ignore();
        }
=======
        cin.ignore();
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08



        switch(opcion)
        {

			case 1:
			
			    color(10);
			
			    gotoxy(65,27);
			    cout<<"INICIANDO MISION...";
			
			
			    Sleep(1000);
			
			
			    ejecutarJuego(usuario);
			
			
			    break;



            case 2:

                instrucciones();

                break;



            case 3:

                creditos();

                break;



            case 4:

<<<<<<< HEAD
                despedida(usuario);
=======
                color(12);

                gotoxy(65,27);
                cout<<"CERRANDO SISTEMA...";

                Sleep(1000);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

                break;



            default:

                color(12);

                gotoxy(65,27);
                cout<<"OPCION INVALIDA";

                Sleep(1000);

        }


    }while(opcion!=4);

}


//=========================================================
// OPCIONES DEL MENÚ
//=========================================================

//=========================================================
// INSTRUCCIONES
//=========================================================

void instrucciones()
{
    system("cls");

    color(11);

    gotoxy(55,5);
    cout<<"==========================================";

    gotoxy(68,7);
    cout<<"INSTRUCCIONES";

    gotoxy(55,9);
    cout<<"==========================================";


    color(15);


    gotoxy(60,12);
    cout<<"OBJETIVO:";

    gotoxy(60,14);
    cout<<"Defiende la galaxia de la invasion";

    gotoxy(60,15);
<<<<<<< HEAD
    cout<<"alienigena y meteoritos.";
=======
    cout<<"alienigena.";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


    gotoxy(60,18);
    cout<<"CONTROLES:";


    gotoxy(60,20);
<<<<<<< HEAD
    cout<<"Movimiento  :  FLECHAS IZQ/DER";
=======
    cout<<"Movimiento  :  A  D";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    gotoxy(60,21);
    cout<<"Disparo     :  ESPACIO";


    gotoxy(60,24);
    cout<<"Destruye enemigos y consigue";

    gotoxy(60,25);
    cout<<"la mayor puntuacion.";


    color(10);

    gotoxy(65,30);
    cout<<"Presione una tecla para volver";

    getch();
}


//=========================================================
// CREDITOS
//=========================================================

void creditos()
{
    system("cls");

    color(11);

    gotoxy(55,7);
    cout<<"==========================================";

    gotoxy(70,9);
    cout<<"CREDITOS";

    gotoxy(55,11);
    cout<<"==========================================";


    color(15);

    gotoxy(60,15);
    cout<<"INVASORES ESPACIALES";


    gotoxy(60,18);
    cout<<"Proyecto Final";

    gotoxy(60,20);
<<<<<<< HEAD
    cout<<"Algoritmos y programacion";


    gotoxy(60,23);
    cout<<"Desarrollado por: VASQUEZ CHAVEZ YAMILLET";
=======
    cout<<"Programacion I";


    gotoxy(60,23);
    cout<<"Desarrollado por:";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


    gotoxy(60,25);
    cout<<"Equipo de desarrollo";


    color(10);

    gotoxy(65,30);
    cout<<"Presione una tecla para volver";


    getch();
}


//=========================================================
// PANTALLAS DEL JUEGO
//=========================================================

<<<<<<< HEAD


//=========================================================
// DESPEDIDA
//=========================================================

void despedida(string usuario)
{
    system("cls");

    color(11);

    gotoxy(55,6);
    cout<<"==========================================";

    gotoxy(63,8);
    cout<<"MISION FINALIZADA";

    gotoxy(55,10);
    cout<<"==========================================";
=======
//=========================================================
// GAME OVER
//=========================================================

void gameOver(string usuario, int puntaje)
{
    system("cls");

    color(12);


    gotoxy(65,10);
    cout<<"==========================";


    gotoxy(72,12);
    cout<<"GAME OVER";


    gotoxy(65,14);
    cout<<"==========================";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08


    color(15);

<<<<<<< HEAD
    gotoxy(50,13);
    cout<<"Gracias por defender la galaxia, comandante "<<usuario<<".";


    // FIGURA ANIMADA: la nave se aleja del centro hasta salir de pantalla

    int xNave;
    int yNave = 18;

    for(xNave = 80; xNave >= 10; xNave -= 4)
    {
        if(xNave < 80)
            borrarJugador(xNave + 4, yNave);

        dibujarJugador(xNave, yNave);

        Sleep(25);
    }

    borrarJugador(xNave + 4, yNave);


    color(10);

    gotoxy(60,45);
    cout<<"Hasta la proxima mision, "<<usuario<<"...";


    Beep(700,150);
    Beep(500,150);
    Beep(300,300);
=======

    gotoxy(60,18);
    cout<<"La invasion ha terminado";


    gotoxy(60,20);
    cout<<"La Tierra necesita otra oportunidad";


    gotoxy(60,22);
    cout<<"COMANDANTE: "<<usuario;


    gotoxy(60,24);
    cout<<"PUNTAJE FINAL: "<<puntaje;


    Beep(400,300);

>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    Sleep(2000);
}

<<<<<<< HEAD
=======
//=========================================================
// VICTORIA
//=========================================================

void victoria(string usuario, int puntaje)
{
    system("cls");


    color(10);


    gotoxy(60,8);
    cout<<"================================";


    gotoxy(70,10);
    cout<<"VICTORIA";


    gotoxy(60,12);
    cout<<"================================";


    color(15);


    gotoxy(65,16);
    cout<<"MISION COMPLETADA";


    gotoxy(65,19);
    cout<<"PUNTAJE FINAL:";


    color(14);

    gotoxy(80,19);
    cout<<puntaje;


    color(10);


    gotoxy(55,24);
    cout<<"La galaxia esta a salvo";


    gotoxy(60,28);
    cout<<"Presione una tecla para continuar";


    Beep(1000,300);

    getch();
}

>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

#endif
