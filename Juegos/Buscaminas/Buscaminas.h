#pragma once 
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include "../../Common/Variables.h"
#include "../../Common/Input.h"
#include "../../Common/Navigation.h"
#include "../../Common/Output.h"
#include "BuscaminasDatabase.h"
#include "BuscaminasService.h"

namespace Minesweeper
{
    void PlayMinesweeper()
    {
        // ======================================================================
        // CONFIGURACIONES
        // ======================================================================
    
        int rows = 10;
        int cols = 10;
        int minesQuantity = 8;
        
        const std::string gameOptions[] = 
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
        std::string playerName = "Player 1";  // TODO ----------- REFERENCIAR A VARIABLE GLOBAL
    
    
        while (inGame)
        {
            Common::feedbackMessage = "";
            
            do
            {
                /**
                 * 
                 * TODO
                 * MOSTRAR PANTALLA CON LAS OPCIONES Y TÍTULO. DEBE INCLUIR LA VARIABLE feebbackMessage
                 * 
                 * 
                 */
    
                Common::key = Common::ReadConsoleChar();
                if(Common::IsNavigationKey(Common::key))
                {
                    Common::feedbackMessage = "";
                    Common::PrintFeedBackMessage();
                    Common::SetOption(gameOption, minGameOption, maxGameOption, Common::key);
                }
                else if( ! Common::IsActionKey(Common::key))
                {
                    Common::feedbackMessage = "Presiona las flechas y selecciona con ENTER o ESPACIO";
                    Common::PrintFeedBackMessage();
                }
            } while (!Common::IsActionKey(Common::key));
            
    
            switch (gameOption)
            {
                // OPCIÓN: JUGAR
                case 0:
                {
                    
                    const std::string levels[] =
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
                        Common::key = Common::ReadConsoleChar();
                        if(Common::IsNavigationKey(Common::key))
                        {
                            Common::feedbackMessage = "";
                            Common::PrintFeedBackMessage();
                            Common::SetOption(levelOption, minLevelOption, maxLevelOption, Common::key);
                        }
                        else if( ! Common::IsActionKey(Common::key))
                        {
                            Common::feedbackMessage = "Presiona las flechas y selecciona con ENTER o ESPACIO";
                            Common::PrintFeedBackMessage();
                        }
                    }
                    while(! Common::IsActionKey(Common::key));
    
                    rows = Minesweeper::SetRowsByLevel(levelOption);
                    cols = Minesweeper::SetColsByLevel(levelOption);
                    minesQuantity = Minesweeper::SetMinesQuantity(rows, cols, levelOption);
                    int flagCount = Minesweeper::SetInitialFlagCount(minesQuantity);
    
                    std::vector<std::vector<int>> backgroundBoard = Minesweeper::CreateBackgroundBoard(rows, cols);
                    Minesweeper::PlaceMines(backgroundBoard, minesQuantity);
                    Minesweeper::CountAdjacentMines(backgroundBoard);
    
                    const std::array<int, 2> initialPosition = Minesweeper::GetInitialPosition(rows, cols);
                    int playerRow = initialPosition[0];
                    int playerCol = initialPosition[1];
    
                    std::vector<std::vector<int>> stateBoard = Minesweeper::CreatePageStateBoard(rows, cols);
                    bool gameOver = false;
                    bool wonGame = false;
    
                    Common::feedbackMessage = "Moverse: Flechas | Revelar: (R) | Bandera: (B) | Salir: (Q)";
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
                        Common::key = Common::ReadConsoleChar();
    
                        if(Minesweeper::IsMoveKey(Common::key))
                        {
                            Minesweeper::MoveCommand(playerRow, playerCol, rows, cols, Common::key);
                        }
                        else if(Minesweeper::IsRevealKey(Common::key))
                        {
                            Minesweeper::RevealCommand(backgroundBoard, stateBoard, playerRow, playerCol, Common::feedbackMessage);
                            if(Minesweeper::MineIsRevealed(backgroundBoard, playerRow, playerCol, Common::feedbackMessage))
                            {
                                gameOver = true;
                            }
                            else if(Minesweeper::IsWonGameState(stateBoard, minesQuantity))
                            {
                                /**
                                 * TODO: VALIDAR SI CUMPLE CON LA CONDICIÓN PARA GANAR
                                 */
                                wonGame = true;
                                gameOver = true;
                            }
                        }
                        else if(Minesweeper::IsFlagKey(Common::key))
                        {
                            Minesweeper::FlagCommand(flagCount, stateBoard, playerRow, playerCol, Common::feedbackMessage);
                        }
                        else if(Minesweeper::IsExitMatchKey(Common::key))
                        {
                            const std::string messageBoxOptions[]
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
                                Common::key = Common::ReadConsoleChar();
                                if(Common::IsNavigationKey(Common::key))
                                {
                                    Common::SetOption(mbOption, minMessageBoxOption, maxMessageBoxOption, Common::key);
                                }
                                
                            }while( ! Common::IsActionKey(Common::key));
                            
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
    
                    if(! Minesweeper::IsExitMatchKey(Common::key))
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
        
    }
}