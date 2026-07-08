#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "../Common/Terminal.h"

namespace RetroArcTest
{
    void PrintMinesweeperBoardTest(std::vector<std::vector<int>> board, int playerRow, int playerCol)
    {
        std::string c;
        int num;
        for (int i = 0; i < board.size(); i++)
        {
            Common::GoToXY(12, i+3);
            for (int j = 0; j < board[0].size(); j++)
            {
                num = board[i][j];
                if(num == -1)
                    c = "-";
                else if(num == 0)
                    c = " ";
                else if(num == -2)
                    c = "B";
                else if(num == 9)
                    c = "@";
                else if(0 < num && num < 9)
                    c = std::to_string(num);

                if(playerRow == i && playerCol == j)
                {
                    std::cout << "[";

                }
                else
                {
                    std::cout << " ";
                }
                
                std::cout << c;

                if(playerRow == i && playerCol == j)
                    std::cout << "]";
                else
                    std::cout << " ";
            }
        }
    
    }
}
