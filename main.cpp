#include <iostream>
#include <vector>
#include "Juegos/Buscaminas/Buscaminas.h"
#include "Common/Variables.h"
#include "Common/Navigation.h"
#include "Common/Input.h"
#include "Common/Consts.h"
#include "Pokemon/Game/Game.h"
#include "Tests/MenuViewTest.h" // <<<<<<<<<<< BORRAR CUANDO YA NO SE ESTÉ USANDO RetroArcTest namespace <<<< BORRAR

int main() {
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif
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
    std::string password = "";
    std::string passwordInView = "";
    
    Common::feedbackMessage = "";
    Common::rowFeedbackMessage = cursorInitialRow + 4;   // MODIFICAR SEGÚN VISTA    ==============================
    Common::colFeedbackMessage = cursorInitialCol + 0;     // MODIFICAR SEGÚN VISTA    ==============================

    
    int countAttempts = 0;

    while (countAttempts < Common::MAX_ATTEMPTS)
    {
        do
        {
            Common::GoToXY(cursorInitialCol, cursorInitialRow);
            Common::ClearConsoleLine(MAX_PASSWORD_LENGTH);
            Common::GoToXY(cursorInitialCol, cursorInitialRow);
            std::cout << passwordInView;
            Common::key = Common::ReadConsoleChar();
            if(Common::IsAlphaNumChar(Common::key))
            {
                if(passwordInView.length() <= MAX_PASSWORD_LENGTH)
                {
                    Common::character = Common::CastKeyToString(Common::key);
                    password += Common::character;
                    passwordInView += "*";
                }
            }
            else if(Common::key == Common::KEY_BACKSPACE)
            {
                if(passwordInView.length() > 0)
                {
                    password.pop_back();
                    passwordInView.pop_back();
                }
            }
            
        } while (Common::key != Common::KEY_ENTER);

        ++countAttempts;

        if(password == Common::CLAVE)
        {
            Common::GoToXY(Common::colFeedbackMessage, Common::rowFeedbackMessage);
            Common::ClearConsoleLine(Common::MAX_FEEDBACK_MESSAGE_LENGTH);
            Common::feedbackMessage = "";
            break;
        }
        else
        {
            int difference = Common::MAX_ATTEMPTS - countAttempts;
            std::string remainingAttempts = std::to_string(difference);
            Common::feedbackMessage = "Te quedan " + remainingAttempts + " intentos";

            // MOSTRAR EL MENSAJE DE ADVERTENCIA
            Common::GoToXY(Common::colFeedbackMessage, Common::rowFeedbackMessage);
            Common::ClearConsoleLine(Common::MAX_FEEDBACK_MESSAGE_LENGTH);
            Common::GoToXY(Common::colFeedbackMessage, Common::rowFeedbackMessage);
            std::cout << Common::feedbackMessage;
            if(countAttempts == Common::MAX_ATTEMPTS)
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
    Common::HideCursor();
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
    
        const std::vector<std::string> menu_options = {
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
        const int menu_maxOpt = menu_options.size() - 1;
        int menu_option = menu_minOpt;
    
        do{
            RetroArcTest::PrintMenuTest(menu_options, menu_option);
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
    
            Common::key = Common::ReadConsoleChar();
    
            if(Common::IsNavigationKey(Common::key))
            {
                Common::SetOption(menu_option, menu_minOpt, menu_maxOpt, Common::key);
            }
            else if(Common::key != Common::KEY_ENTER && Common::key != Common::KEY_SPACE)
            {
                Common::GoToXY(Common::colFeedbackMessage, Common::rowFeedbackMessage);
                Common::ClearConsoleLine(Common::MAX_FEEDBACK_MESSAGE_LENGTH);
                Common::GoToXY(Common::colFeedbackMessage, Common::rowFeedbackMessage);
                Common::feedbackMessage = "Presiona las flechas y selecciona con ENTER o ESPACIO";
            }
        }while(Common::key != Common::KEY_ENTER && Common::key != Common::KEY_SPACE);
    
        // SWITCH HACIA LA OPCION
        switch(menu_option)
        {
    
            // POKEMON
            case 0:
                PokemonGame::Game game;
                game.start();
                break;
    
            // BUSCAMINAS
            case 1:
                Minesweeper::PlayMinesweeper();
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
                    Common::key = Common::ReadConsoleChar();
                }while(Common::key != Common::KEY_Q && Common::key != Common::KEY_Q_LOWER);
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
