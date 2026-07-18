#pragma once

#include "Consts.h"
#include "Variables.h"
#include "Windows/Terminal.h"
#include <iostream>
#include <string>

namespace Common
{
    void PrintFeedBackMessage()
    {
        GoToXY(Common::colFeedbackMessage, Common::rowFeedbackMessage);
        ClearConsoleLine(Common::MAX_FEEDBACK_MESSAGE_LENGTH);
        GoToXY(Common::colFeedbackMessage, Common::rowFeedbackMessage);
        std::cout << Common::feedbackMessage;
    }
}