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

    const int MAX_PASSWORD_LENGTH = 15;  // MODIFICAR SEGÚN VISTA    ==============================
    const int cursorInitialRow = 4;   // MODIFICAR SEGÚN VISTA    ==============================
    const int cursorInitialCol = 5;   // MODIFICAR SEGÚN VISTA    ==============================
    string password = "";
    string passwordInView = "";
    
    string feedbackMessage = "";
    int rowFeedbackMessage = cursorInitialRow + 4;   // MODIFICAR SEGÚN VISTA    ==============================
    int colFeedbackMessage = cursorInitialCol + 0;     // MODIFICAR SEGÚN VISTA    ==============================

    vector<int> key;
    string character;
    
    int countAttempts = 0;

    while (countAttempts < ::MAX_ATTEMPTS)
    {
        do
        {
            GoToXY(cursorInitialCol, cursorInitialRow);
            ClearConsoleLine(MAX_PASSWORD_LENGTH);
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

        ++countAttempts;

        if(password == ::CLAVE)
        {
            GoToXY(colFeedbackMessage, rowFeedbackMessage);
            ClearConsoleLine(MAX_FEEDBACK_MESSAGE_LEGTH);
            feedbackMessage = "";
            break;
        }
        else
        {
            int difference = ::MAX_ATTEMPTS - countAttempts;
            string remainingAttempts = to_string(difference);
            feedbackMessage = "Te quedan " + remainingAttempts + " intentos";

            // MOSTRAR EL MENSAJE DE ADVERTENCIA
            GoToXY(colFeedbackMessage, rowFeedbackMessage);
            ClearConsoleLine(MAX_FEEDBACK_MESSAGE_LEGTH);
            GoToXY(colFeedbackMessage, rowFeedbackMessage);
            cout << feedbackMessage;
        }
    }
    
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
