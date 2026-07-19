#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "../../Common/Color.h"
#include "../../Common/Graphics.h"
#include "../../Common/Terminal.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"
#include "../../Common/Variables.h"
#include "../../Common/Utils.h"

namespace Common
{
    void DrawBottomBar()
    {
        const int barWidth = WIDTH_SCREEN;
        const int barHeight = 3;
        const int barY = HEIGHT_SCREEN - barHeight;
        const int barX = 0;
        const int PADDING = 3;

        Common::DrawFillRectangle(
            barX, barY,
            barWidth, barHeight,
            EMPTY_BLOCK,
            DARK_BLUE, DARK_BLUE
        );

        // Early exit if no entries
        if (keysHelper.empty()) return;

        // Rendering constants
        const int row2Y = barY + 1;  // middle row
        const int row3Y = barY + 2;  // bottom row
        const int maxEntryLen = 30;
        const int gapLen = 3;

        int currentCol = PADDING;
        int currentRow = row2Y;

        for (size_t i = 0; i < keysHelper.size(); ++i) {
            const auto& entry = keysHelper[i];
            const std::string& key = entry[0];
            const std::string& desc = entry[1];

            // Build display string
            std::string keyPart = "[" + key + "]";
            std::string descPart = " " + desc;
            std::string fullEntry = keyPart + descPart;

            // Truncate to maxEntryLen visible chars
            std::string truncated = TruncateVisible(fullEntry, maxEntryLen);
            int entryLen = Common::Length(truncated);

            // Check if fits on current row (respect right padding)
            if (currentCol + entryLen > barWidth - PADDING) {
                // Move to row 3
                currentRow = row3Y;
                currentCol = PADDING;
                // If row 3 also full, drop remaining entries
                if (currentRow > row3Y) break;
            }

            // Position cursor
            Common::GoToXY(barX + currentCol, currentRow);

            // Print key part in YELLOW color
            std::cout << Common::Color(YELLOW, DARK_BLUE) << keyPart;

            // Print description part in LIGHT_BLUE (cyan) color
            std::cout << Common::Color(LIGHT_BLUE, DARK_BLUE) << descPart;

            // Advance column
            currentCol += entryLen + gapLen;
        }

        std::cout << Common::ResetColor();
        std::cout.flush();
    }
}
