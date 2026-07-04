#include <iostream>
#include <vector>
#include "common/Input.h"
#include "common/Consts.h"
#include <conio.h>

using namespace std;

int main() {
    cout << "Se ejecuta el programa" << endl;

    // =========================================
    // INICIO DE SESION
    // =========================================
    
    /**
     * 
     * CARGAR PANTALLA DE INICIO DE SESION
     * (EL CURSOR SE MOVERÁ EN LA LÓGICA)
     * 
     */

    const int MAX_PASSWORD_LENGTH = 15;
    const int cursorInitialRow = 4;
    const int cursorInitialCol = 5;
    string password = "";
    string passwordInView = "";

    vector<int> key;
    string character;
    

    do
    {
        GoToXY(cursorInitialCol, cursorInitialRow);
        cout <<  "                      ";
        GoToXY(cursorInitialCol, cursorInitialRow);
        cout << passwordInView;
        key = ReadConsoleChar();
        if(IsAlphaNumChar(key))
        {
            if(passwordInView.length() <= MAX_PASSWORD_LENGTH)
            {
                character = CastKeyToString(key);
                password += character;
                passwordInView += "*";
            }
        }
        else if(key == KEY_BACKSPACE)
        {
            if(passwordInView.length() > 0)
            {
                password.pop_back();
                passwordInView.pop_back();
            }
        }
        
    } while (key != ::KEY_ENTER);
    
    // PANTALLA DE CARGA

    // PANTALLA DE INICIO

    // SELECCIONAR OPCIÓN

    // SWITCH HACIA LA OPCION

    // =========================================
    // JUEGOS
    // =========================================
    /**
     * JUEGOS :
     * 0: POKEMON
     * 1: BUSCAMINAS
     * 2: BATALLA NAVAL
     * 3: TIC-TAC-TOE
     * 4: SPACE-INVADERS
     */
    
    // =========================================
    // CONFIGURACIONES
    // =========================================
    
    // Configurar nombre de jugador
    
    // =========================================
    // CRÉDITOS
    // =========================================
    /**
     * Universidad
     * Curso
     * Docente
     * Autores
     * Año
     */
    
    // =========================================
    // SALIR
    // =========================================

}
