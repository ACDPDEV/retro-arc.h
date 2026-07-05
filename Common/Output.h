#pragma once

#include "Consts.h"
#include "Variables.h"
#include "Windows/Terminal.h"
#include <iostream>
#include <string>

using namespace std;

void PrintFeedBackMessage()
{
    GoToXY(::colFeedbackMessage, ::rowFeedbackMessage);
    ClearConsoleLine(::MAX_FEEDBACK_MESSAGE_LENGTH);
    GoToXY(::colFeedbackMessage, ::rowFeedbackMessage);
    cout << ::feedbackMessage;
}