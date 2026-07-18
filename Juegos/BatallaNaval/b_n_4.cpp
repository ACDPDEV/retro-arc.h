// Fase 4: Refactorización y el Bucle del Juego (Game Loop)

#include <iostream>
using namespace std;

const int filas = 10, columnas = 10;

void dibujarTablero(int tablero[filas][columnas]);
int main()
{

    int tablero[filas][columnas];
    int filaInicioHor = 3;
    int columnaInicioHor = 6;
    int tamanoHor = 5;
    int filaInicioVert = 4;
    int columnaInicioVert = 5;
    int tamanoVert = 5;
    int aciertosActuales =0;
    int aciertosTotales = 0;
    int filaDisparo;
    int columnaDisparo;

    for (int i = 0; i < filas; ++i)
    {                                                           // construyendo tablero en la memoria
        for (int j = 0; j < columnas; ++j)
        {
            tablero[i][j] = 0;
        }
    }
    // asigno barcos en memoria

    if (columnaInicioHor + tamanoHor <= 10)
    {                                                            // delimitando tamaño del barco a limites del tablero (en horizontal)
        for (int i = 0; i < tamanoHor; ++i)
        {                                                           // asignando barco horizontal, el barco "inicia" en la fila 4 y la columna 5

            tablero[filaInicioHor][columnaInicioHor + i] = 1;
        }
    }
    else
    {
        cout << "Limites de tablero excedidos.\n\n";                        // cuando el barco se "sale" del tablero
    }

    for (int i = 0; i < tamanoVert; ++i)
    {                                                                   // asignando barco vertical; el barco "inicia" en la fila 5 y la columna 6
        tablero[filaInicioVert + i][columnaInicioVert] = 1;
    }

    dibujarTablero(tablero);

    while (aciertosActuales<aciertosTotales)
    {
        cout << "Ingrese una fila de diparo (0-9): ";                       // disparando en cierto numero de fila (incluye validacion)
        cin >> filaDisparo;
        cout << "\n";
        ;
        while (filaDisparo > 9 || filaDisparo < 0)
        {
            cout << "Ingrese una fila entre 0 y 9: ";
            cin >> filaDisparo;
            cout << "\n";
        }

        cout << "Ingrese una columna de diparo (0-9): ";                        // disparando en cierto numero de columna (incluye validacion)
        cin >> columnaDisparo;
        cout << "\n";
        while (columnaDisparo > 9 || columnaDisparo < 0)
        {
            cout << "Ingrese una columna entre 0 y 9: ";
            cin >> columnaDisparo;
            cout << "\n";
        }

        if (tablero[filaDisparo][columnaDisparo] == 0)
        {                                                                       // si no hay impacto
            tablero[filaDisparo][columnaDisparo] = 2;
            cout << "Agua.\n";
        }
        else if (tablero[filaDisparo][columnaDisparo] == 1)
        {                                                                       // si hay impacto
            tablero[filaDisparo][columnaDisparo] = 3;
            aciertosActuales++;
            cout << "Impacto! \n";
        }
        else
        {
            cout << "Ya se disparo aquí.\n";
        }
        dibujarTablero(tablero);
    }

    cout<<"Victoria, haz destruido la flota enemiga.";

    return 0;
}

void dibujarTablero(int tablero[filas][columnas])       //CONVERTIDO EN FUNCION, DIBUJO DE TABLERO
{ // IMPRESION DE TABLERO
    for (int i = 0; i < filas; ++i)
    {                                                   // visualizacion del tablero(mar)             //TODO ESTO DEBERIA SER UNA FUNCION
        for (int j = 0; j < columnas; ++j)
        {
            if (tablero[i][j] == 0)
            {                                           
                cout << "~   ";
            }
            else if (tablero[i][j] == 1)
            { // visualizacion de los barcos
                cout << "B   ";
            }
            else if (tablero[i][j] == 2)
            { // condicion de fallo
                cout << "o   ";
            }
            else if (tablero[i][j] == 3)
            { // condicion de impacto
                cout << "X   ";
            }
        }
        cout << endl;
    }
}
