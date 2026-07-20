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
#include "BuscaminasUI.h"

namespace Buscaminas
{
    void PlayMinesweeper()
    {
        // ======================================================================
        // CONFIGURACIONES
        // ======================================================================
    
        int rows = 10;
        int cols = 10;
        int minesQuantity = 8;
        
        bool inGame = true;
    
        while (inGame)
        {
            int menuOption = Buscaminas::MainMenuView();

            switch (menuOption)
            {
                // OPCIÓN: JUGAR
                case 0:
                {
                    int levelOption = Buscaminas::LevelSelectView();
                    if (levelOption == -1) break; // Esc → back to main menu

                    rows = Buscaminas::SetRowsByLevel(levelOption);
                    cols = Buscaminas::SetColsByLevel(levelOption);
                    minesQuantity = Buscaminas::SetMinesQuantity(rows, cols, levelOption);

                    bool playAgain = false;
                    do {
                        playAgain = false;

                        int flagCount = Buscaminas::SetInitialFlagCount(minesQuantity);

                        std::vector<std::vector<int>> backgroundBoard = Buscaminas::CreateBackgroundBoard(rows, cols);
                        Buscaminas::PlaceMines(backgroundBoard, minesQuantity);
                        Buscaminas::CountAdjacentMines(backgroundBoard);

                        const std::array<int, 2> initialPosition = Buscaminas::GetInitialPosition(rows, cols);
                        int playerRow = initialPosition[0];
                        int playerCol = initialPosition[1];

                        std::vector<std::vector<int>> stateBoard = Buscaminas::CreatePageStateBoard(rows, cols);

                        // GameBoardView handles its own input loop
                        // Returns: -1=quit, 1=won, 2=lost
                        int boardResult = Buscaminas::GameBoardView(
                            stateBoard, backgroundBoard,
                            playerRow, playerCol,
                            flagCount, minesQuantity,
                            levelOption
                        );

                        if (boardResult == 1 || boardResult == 2) {
                            int goAction = Buscaminas::GameOverView(boardResult == 1);
                            if (goAction == 0) {
                                playAgain = true;
                            }
                        }
                        // boardResult == -1 → quit confirmed, go back to menu
                    } while (playAgain);

                    break;
                }

                // OPCIÓN: INSTRUCCIONES
                case 1:
                    Buscaminas::InstructionsView();
                    break;
                
                // OPCIÓN: CONFIGURACIONES
                case 2:
                    Buscaminas::ConfigView();
                    break;
                
                // OPCIÓN: VOLVER
                case 3:
                    inGame = false;
                    break;
                
                default:
                    break;
            }    
    
        }
        
    }
}
