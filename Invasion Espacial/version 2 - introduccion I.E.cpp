//=========================================================
//              INVASORES ESPACIALES
//          Proyecto Final - Programación I
//=========================================================

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

//=========================================================
// COLOR
//=========================================================
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//=========================================================
// GOToxy
//=========================================================
void gotoxy(int x, int y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCon, pos);
}

//=========================================================
// CONFIGURAR PANTALLA
//=========================================================
void configurarPantalla()
{
    system("mode con: cols=200 lines=60");
    system("title INVASORES ESPACIALES");
}

//=========================================================
// TEXTO CON EFECTO
//=========================================================
void escribirTexto(int x, int y, string texto, int vel)
{
    gotoxy(x, y);

    for(int i = 0; i < texto.length(); i++)
    {
        cout << texto[i];
        Beep(1200, 3);
        Sleep(vel);
    }
}

//=========================================================
// BARRA DE CARGA
//=========================================================
void barraCarga(int x, int y)
{
    gotoxy(x, y);
    cout << "[";

    for(int i = 0; i < 20; i++) cout << " ";

    cout << "]";

    for(int i = 0; i < 20; i++)
    {
        gotoxy(x + 1 + i, y);
        color(10);
        cout << (char)219;

        gotoxy(x + 25, y);
        color(15);
        cout << (i + 1) * 5 << "%";

        Beep(900, 5);
        Sleep(60);
    }
}

//=========================================================
// TITULO SISTEMA
//=========================================================
void mostrarTituloSistema()
{
    color(11);

    gotoxy(60, 3);
    cout << "========================================================";

    gotoxy(75, 5);
    cout << "SISTEMA DE DEFENSA ESPACIAL";

    gotoxy(60, 7);
    cout << "========================================================";
}

void mostrarAlertaGigante()
{
    system("cls");

    //==============================
    // MARCO SUPERIOR
    //==============================
    color(12);
    gotoxy(40,2);
    cout << "################################################################################";

    //==============================
    // TÍTULO ALERTA (MEJORADO)
    //==============================
    color(12);

    gotoxy(55,5);
    cout << "  ¦¦¦¦¦+ ¦¦+     ¦¦¦¦¦¦¦+¦¦¦¦¦¦+ ¦¦¦¦¦¦¦¦+ ¦¦¦¦¦+ ";

    gotoxy(55,6);
    cout << " ¦¦+--¦¦+¦¦¦     ¦¦+----+¦¦+--¦¦++--¦¦+--+¦¦+--¦¦+";

    gotoxy(55,7);
    cout << " ¦¦¦¦¦¦¦¦¦¦¦     ¦¦¦¦¦+  ¦¦¦¦¦¦++   ¦¦¦   ¦¦¦¦¦¦¦¦";

    gotoxy(55,8);
    cout << " ¦¦+--¦¦¦¦¦¦     ¦¦+--+  ¦¦+--¦¦+   ¦¦¦   ¦¦+--¦¦¦";

    gotoxy(55,9);
    cout << " ¦¦¦  ¦¦¦¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+¦¦¦  ¦¦¦   ¦¦¦   ¦¦¦  ¦¦¦";

    gotoxy(55,10);
    cout << " +-+  +-++------++------++-+  +-+   +-+   +-+  +-+";

    //==============================
    // SUBTÍTULO
    //==============================
    color(14);
    gotoxy(70,12);
    cout << "!!! ALERTA CRITICA DEL SISTEMA !!!";

    gotoxy(75,14);
    cout << "INVASION EXTRATERRESTRE";

    gotoxy(82,15);
    cout << "CONFIRMADA";

    //==============================
    // ICONOS LATERALES SIMPLIFICADOS
    //==============================
    color(12);

    gotoxy(45,13);
    cout << "   /\\  ";
    gotoxy(45,14);
    cout << "  /!!\\ ";
    gotoxy(45,15);
    cout << " /____\\";

    gotoxy(110,13);
    cout << "   /\\  ";
    gotoxy(110,14);
    cout << "  /!!\\ ";
    gotoxy(110,15);
    cout << " /____\\";

    //==============================
    // BARRA DE PROGRESO MÁS LIMPIA
    //==============================
    color(12);

    gotoxy(60,18);
    cout << "INICIANDO PROTOCOLO DE DEFENSA...";

    gotoxy(65,20);
    cout << "[";

    for(int i = 0; i < 30; i++) cout << " ";
    cout << "]";

    for(int i = 0; i < 30; i++)
    {
        gotoxy(66 + i, 20);
        cout << (char)219;
        Beep(900,20);
        Sleep(40);
    }

    //==============================
    // FINAL
    //==============================
    for(int i = 0; i < 5; i++)
    {
        Beep(1200,120);
        Beep(700,120);
    }

    color(14);
    gotoxy(70,23);
    cout << "PREPARESE PARA LA BATALLA...";

    Sleep(2000);
}
//=========================================================
// PANTALLA ALERTA
//=========================================================
void pantallaAlerta()
{
    system("cls");

    mostrarTituloSistema();

    color(15);
    escribirTexto(60, 12, "Inicializando protocolo de seguridad...", 20);
    barraCarga(60, 14);

    Sleep(500);
    system("cls");

    mostrarTituloSistema();

    escribirTexto(60, 12, "Escaneando el espacio...", 20);
    barraCarga(60, 14);

    Sleep(500);
    system("cls");

    mostrarTituloSistema();

    escribirTexto(60, 12, "Analizando senal desconocida...", 20);
    barraCarga(60, 14);

    Sleep(800);

    mostrarAlertaGigante();
}

//=========================================================
// MAIN
//=========================================================
int main()
{
    configurarPantalla();
    pantallaAlerta();

    getch();
    return 0;
}
