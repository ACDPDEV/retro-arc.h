#include <iostream>
#include <vector>
#include <conio.h>
#include "Common/Variables.h"
#include "Common/Navigation.h"
#include "Common/Input.h"
#include "Common/Consts.h"

using namespace std;

int main() {
    // =========================================
    // INICIO DE SESION
    // =========================================
    
    /**
     * 
     * PANTALLA DE INICIO DE SESION
     * (EL CURSOR SE MOVERÁ EN LA LÓGICA)
     * 
     */

    const int MAX_PASSWORD_LENGTH = 15;  // MODIFICAR SEGÚN VISTA    ==============================
    const int cursorInitialRow = 4;   // MODIFICAR SEGÚN VISTA    ==============================
    const int cursorInitialCol = 5;   // MODIFICAR SEGÚN VISTA    ==============================
    string password = "";
    string passwordInView = "";
    
    ::feedbackMessage = "";
    ::rowFeedbackMessage = cursorInitialRow + 4;   // MODIFICAR SEGÚN VISTA    ==============================
    ::colFeedbackMessage = cursorInitialCol + 0;     // MODIFICAR SEGÚN VISTA    ==============================

    
    int countAttempts = 0;

    while (countAttempts < ::MAX_ATTEMPTS)
    {
        do
        {
            GoToXY(cursorInitialCol, cursorInitialRow);
            ClearConsoleLine(MAX_PASSWORD_LENGTH);
            GoToXY(cursorInitialCol, cursorInitialRow);
            cout << passwordInView;
            ::key = ReadConsoleChar();
            if(IsAlphaNumChar(::key))
            {
                if(passwordInView.length() <= MAX_PASSWORD_LENGTH)
                {
                    ::character = CastKeyToString(::key);
                    password += ::character;
                    passwordInView += "*";
                }
            }
            else if(::key == KEY_BACKSPACE)
            {
                if(passwordInView.length() > 0)
                {
                    password.pop_back();
                    passwordInView.pop_back();
                }
            }
            
        } while (::key != ::KEY_ENTER);

        ++countAttempts;

        if(password == ::CLAVE)
        {
            GoToXY(::colFeedbackMessage, ::rowFeedbackMessage);
            ClearConsoleLine(::MAX_FEEDBACK_MESSAGE_LENGTH);
            ::feedbackMessage = "";
            break;
        }
        else
        {
            int difference = ::MAX_ATTEMPTS - countAttempts;
            string remainingAttempts = to_string(difference);
            ::feedbackMessage = "Te quedan " + remainingAttempts + " intentos";

            // MOSTRAR EL MENSAJE DE ADVERTENCIA
            GoToXY(::colFeedbackMessage, ::rowFeedbackMessage);
            ClearConsoleLine(::MAX_FEEDBACK_MESSAGE_LENGTH);
            GoToXY(::colFeedbackMessage, ::rowFeedbackMessage);
            cout << ::feedbackMessage;
            if(countAttempts == MAX_ATTEMPTS)
            {
                /**
                 * 
                 * 
                 * TODO Pantalla de cierre de programa por contraseña errónea
                 * 
                 * 
                 */

                exit(1);
            }
        }
    }
    
    // =========================================
    // PANTALLA DE CARGA
    // =========================================

    /**
     * 
     * TODO
     * LA PANTALLA DE CARGA DEBE TENER UN CONTEO DE TIEMPO (CREO xD)
     * 
     */

    bool isRunning = true;

    while(isRunning)
    {

        // =========================================
        // MENU PRINCIPAL
        // =========================================
    
        const string menu_options[] = {
            "POKEMON", 
            "BUSCAMINAS", 
            "BATALLA NAVAL", 
            "TIC-TAC-TOE", 
            "BATALLA NAVAL", 
            "CRÉDITOS", 
            "SALIR", 
            "CONFIG"
        };
    
        const int menu_minOpt = 0;
        const int menu_maxOpt = menu_options->size();
        int menu_option = menu_minOpt;
    
        do{
            /**
             * 
             * 
             * 
             * 
             * TODO 
             * PANTALLA DE MENU DE OPCIONES RESALTANDO LA OPCIÓN SELECCIONADA
             * 
             * 
             * 
             * 
             */
    
            ::key = ReadConsoleChar();
    
            if(IsNavigationKey(::key))
            {
                SetOption(menu_option, menu_minOpt, menu_maxOpt, ::key);
            }
            else if(::key != KEY_ENTER && ::key != KEY_SPACE)
            {
                GoToXY(::colFeedbackMessage, ::rowFeedbackMessage);
                ClearConsoleLine(::MAX_FEEDBACK_MESSAGE_LENGTH);
                GoToXY(::colFeedbackMessage, ::rowFeedbackMessage);
                feedbackMessage = "Presiona las flechas y selecciona con ENTER o ESPACIO";
            }
        }while(::key != KEY_ENTER && ::key != KEY_SPACE);
    
        // SWITCH HACIA LA OPCION
        switch(menu_option)
        {
    
            // POKEMON
            case 0:
                break;
    
            // BUSCAMINAS
            case 1:
                break;
    
            // BATALLA NAVAL
            case 2:
                break;
    
            // TIC-TAC-TOE
            case 3:
                break;
    
            // SPACE INVADERS
            case 4:
                break;
    
            // =========================================
            // CRÉDITOS
            // =========================================
            case 5:
                /**
                 * 
                 * TODO
                 * MOSTRAR PANTALLA DE CRÉDITOS DEBE CONTENER :
                 * MENSAJE "Presione 'Q' para regresar"
                 * Universidad
                 * Curso
                 * Docente
                 * Autores
                 * Año
                 * 
                 * 
                 */

                do{
                    ::key = ReadConsoleChar();
                }while(::key != ::KEY_Q && ::key != ::KEY_Q_LOWER);
                break;
    
            // =========================================
            // SALIR
            // =========================================
            case 6:

                /**
                 * 
                 * 
                 * TODO
                 * PANTALLA DE CIERRE DE PROGRAMA POR OPCIÓN "SALIR"
                 * 
                 * 
                 * 
                 */
                isRunning = false;
                break;
    
            // =========================================
            // CONFIGURACIONES
            // =========================================
            
            // Configurar nombre de jugador
            case 7:

                break;
        }
    }

}
