#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "../Common/Terminal.h"

namespace RetroArcTest
{
    void PrintMenuTest(std::vector<std::string> options, int currentOption)
    {
        for (int i = 0; i < options.size(); i++)
        {
            Common::GoToXY(25, i+1);
            if(currentOption == i)
            {
                std::cout << " > ";
            }
            else
            {
                std::cout << "   ";
            }
            std::cout << options[i] << std::endl;
        }
    
    }
}
