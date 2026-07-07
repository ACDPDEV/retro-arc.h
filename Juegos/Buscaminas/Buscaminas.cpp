#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include "../../Common/Variables.h"
#include "../../Common/Input.h"
#include "../../Common/Navigation.h"
#include "../../Common/Output.h"
#include "Buscaminas.h"
#include "BuscaminasFunctions.h"

using namespace std;

int PlayBuscaminas()
{
    // ======================================================================
    // CONFIGURACIONES
    // ======================================================================

    int rows = 10;
    int cols = 10;
    int minesQuantity = 8;
    
    const string gameOptions[] = 
    {
        "JUGAR",
        "CRÉDITOS",
        "VOLVER AL MENÚ",
        "CONFIGURACIONES"  
    };

    const int minGameOption = 0;
    const int maxGameOption = gameOptions->size() - 1;
    int gameOption = minGameOption;

    bool inGame = true;
    string playerName = "Player 1";  // TODO ----------- REFERENCIAR A VARIABLE GLOBAL


    while (inGame)
    {
        ::feedbackMessage = "";
        
        do
        {
            /**
             * 
             * TODO
             * MOSTRAR PANTALLA CON LAS OPCIONES Y TÍTULO. DEBE INCLUIR LA VARIABLE feebbackMessage
             * 
             * 
             */

            ::key = ReadConsoleChar();
            if(IsNavigationKey(::key))
            {
                ::feedbackMessage = "";
                PrintFeedBackMessage();
                SetOption(gameOption, minGameOption, maxGameOption, ::key);
            }
            else if( ! IsActionKey(::key))
            {
                ::feedbackMessage = "Presiona las flechas y selecciona con ENTER o ESPACIO";
                PrintFeedBackMessage();
            }
        } while (!IsActionKey(::key));
        

        switch (gameOption)
        {
            // OPCIÓN: JUGAR
            case 0:
            {
                
                const string levels[] =
                {
                    "FÁCIL",
                    "INTERMEDIO",
                    "DIFÍCIL"
                };
                // SELECCIONAR NIVEL

                const int minLevelOption = 0;
                const int maxLevelOption = levels->size() - 1;
                int levelOption = minLevelOption;
                
                do{
                    /**
                     * TODO
                     * 
                     * PANTALLA PARA SELECCIONAR NIVEL
                     * 
                     * 
                     */
                    ::key = ReadConsoleChar();
                    if(IsNavigationKey(::key))
                    {
                        ::feedbackMessage = "";
                        PrintFeedBackMessage();
                        SetOption(levelOption, minLevelOption, maxLevelOption, ::key);
                    }
                    else if( ! IsActionKey(::key))
                    {
                        ::feedbackMessage = "Presiona las flechas y selecciona con ENTER o ESPACIO";
                        PrintFeedBackMessage();
                    }
                }
                while(! IsActionKey(::key));

                rows = SetRowsByLevel(levelOption);
                cols = SetColsByLevel(levelOption);
                minesQuantity = SetMinesQuantity(rows, cols, levelOption);
                int flagCount = SetInitialFlagCount(minesQuantity);

                vector<vector<int>> backgroundBoard = CreateBackgroundBoard(rows, cols);
                PlaceMines(backgroundBoard, minesQuantity);
                CountAdjacentMines(backgroundBoard);

                const array<int, 2> initialPosition = GetInitialPosition(rows, cols);
                int playerRow = initialPosition[0];
                int playerCol = initialPosition[1];

                vector<vector<int>> playerStateBoard = CreatePageStateBoard(rows, cols);
                char actionKey;
                bool gameOver = false;
                bool wonGame = false;

                ::feedbackMessage = "Moverse: Flechas | Revelar: (R) | Bandera: (B) | Salir: (Q)";
                /**
                 * 
                 * 
                 * TODO:
                 * MOSTRAR IU SIN PARÁMETROS
                 * 
                 * 
                 */

                while (!gameOver)
                {
                    /**
                     * 
                     * TODO:
                     * MOSTRAR SECCIONES DE UI CON PARÁMETROS
                     * TABLERO,
                     * FEEDBACK MESSAGGE,
                     * BANDERAS,
                     * POSICION ACTUAL DEL JUGADOR (ROW, COL)
                     * 
                     */

                    // 2. Pedir la acción
                    ::key = ReadConsoleChar();

                    if(IsMoveKey(::key))
                    {
                        MoveCommand(playerRow, playerCol, rows, cols, ::key);
                    }
                    else if(IsRevealKey(::key))
                    {
                        RevealCommand(backgroundBoard, playerStateBoard, playerRow, playerCol, ::feedbackMessage);
                        if(MineIsRevealed(backgroundBoard, playerRow, playerCol, ::feedbackMessage))
                        {
                            gameOver = true;
                        }
                        else if(IsWonGameState(playerStateBoard, minesQuantity))
                        {
                            /**
                             * TODO: VALIDAR SI CUMPLE CON LA CONDICIÓN PARA GANAR
                             */
                            wonGame = true;
                            gameOver = true;
                        }
                    }
                    else if(IsFlagKey(::key))
                    {
                        FlagCommand(flagCount, playerStateBoard, playerRow, playerCol, ::feedbackMessage);
                    }
                    else if(IsExitMatchKey(::key))
                    {
                        const string messageBoxOptions[]
                        {
                            "SÍ",
                            "NO"
                        };
                        const int minMessageBoxOption = 0;
                        const int maxMessageBoxOption = messageBoxOptions->size() - 1;
                        int mbOption = minMessageBoxOption;
                        
                        do{
                            /**
                             * 
                             * TODO:
                             * MESSAGE BOX PARA CONFIRMAR SALIDA
                             * "¿Quieres abandonar la partida?"
                             * "SI"  "NO"
                             * 
                             */
                            ::key = ReadConsoleChar();
                            if(IsNavigationKey(::key))
                            {
                                SetOption(mbOption, minMessageBoxOption, maxMessageBoxOption, ::key);
                            }
                            
                        }while( ! IsActionKey(::key));
                        
                        if(messageBoxOptions[mbOption] == "SÍ")
                        {
                            gameOver = true;
                        }
                    }
                    else
                    {
                        /**
                         * 
                         * TODO:
                         * GESTIONAR TECLA EQUIVOCADA
                         * 
                         */
                    }

                    
                }

                if(! IsExitMatchKey(::key))
                {
                    // TODO mostrar la pantalla de victoria o resultado

                }
                break;
            }

            
            // OPCIÓN: CRÉDITOS
            case 1:
            // TODO: CRÉDITOS DE BUSCAMINAS
            break;
            
            // OPCIÓN: SALIR
            case 2:
            inGame = false;
            break;
            
            // OPCIÓN: CONFIGURACIONES
            case 3:
                // TODO: CONFIGURAR NOMBRE DEL JUGADOR
                break;
            
            default:
                break;
        }    

    }
    

    return 0;
}