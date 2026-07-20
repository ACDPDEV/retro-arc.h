#pragma once

#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/UnicodeGlyphs.h"
#include "../../../Common/Variables.h"
#include "../BuscaminasService.h"
#include "../BuscaminasUI.h"

// Forward declaration — ExitConfirmView is defined in ExitConfirmView.h
namespace Buscaminas
{
    bool ExitConfirmView();
}

namespace Buscaminas
{
    /// @brief Draws the HUD bar with flag count, cursor position, and mines remaining
    /// @param flagCount Current number of flags placed
    /// @param playerRow Current cursor row
    /// @param playerCol Current cursor column
    /// @param minesRemaining Total mines count
    inline void DrawHUD(int flagCount, int playerRow, int playerCol, int minesRemaining)
    {
        std::string hudText = "🚩 " + std::to_string(flagCount)
            + "  📍 (" + std::to_string(playerRow) + "," + std::to_string(playerCol) + ")"
            + "  💣 " + std::to_string(minesRemaining) + " restantes";
        Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(hudText), "center"), HUD_Y);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << hudText;
    }

    /// @brief Draws a single cell on the board with cursor highlight
    /// @param cellX X position of the cell
    /// @param cellY Y position of the cell
    /// @param state The cell state (-2=flagged, -1=hidden, 0=safe, 1-8=number)
    /// @param isCursor Whether the cursor is on this cell
    inline void DrawCell(int cellX, int cellY, int state, bool isCursor)
    {
        if (state == -2) { // Flagged
            if (isCursor) {
                Common::DrawFillRectangle(cellX, cellY, CELL_WIDTH, 1, Common::EMPTY_BLOCK, Common::ORANGE, Common::FOREGROUND_DARK);
                Common::GoToXY(cellX, cellY);
                std::cout << Common::Color(Common::ORANGE, Common::FOREGROUND_DARK) << "⛳";
            } else {
                Common::DrawFillRectangle(cellX, cellY, CELL_WIDTH, 1, Common::EMPTY_BLOCK, Common::FOREGROUND_DARK, Common::SELECTION_BACKGROUND);
                Common::GoToXY(cellX, cellY);
                std::cout << Common::Color(Common::ORANGE, Common::SELECTION_BACKGROUND) << "⛳";
            }
        } else if (state == -1) { // Hidden
            if (isCursor) {
                Common::DrawFillRectangle(cellX, cellY, CELL_WIDTH, 1, Common::SHADING[0], Common::FOREGROUND_LIGHT, Common::FOREGROUND_DARK);
            } else {
                Common::DrawFillRectangle(cellX, cellY, CELL_WIDTH, 1, Common::SHADING[0], Common::SELECTION_FOREGROUND, Common::SELECTION_BACKGROUND);
            }
        } else if (state == 0) { // Safe (empty)
            if (isCursor) {
                Common::DrawFillRectangle(cellX, cellY, CELL_WIDTH, 1, Common::EMPTY_BLOCK, Common::FOREGROUND_DARK, Common::CURSOR);
            } else {
                Common::DrawFillRectangle(cellX, cellY, CELL_WIDTH, 1, Common::EMPTY_BLOCK, Common::BACKGROUND, Common::BACKGROUND);
            }
        } else if (1 <= state && state <= 8) { // Number
            const auto& numColor = NUMBER_COLORS[state - 1];
            const std::string numStr = std::to_string(state) + " ";
            if (isCursor) {
                Common::DrawFillRectangle(cellX, cellY, CELL_WIDTH, 1, Common::EMPTY_BLOCK, numColor, Common::CURSOR);
                Common::GoToXY(cellX, cellY);
                std::cout << Common::Color(numColor, Common::CURSOR) << numStr;
            } else {
                Common::DrawFillRectangle(cellX, cellY, CELL_WIDTH, 1, Common::EMPTY_BLOCK, numColor, Common::BACKGROUND);
                Common::GoToXY(cellX, cellY);
                std::cout << Common::Color(numColor, Common::BACKGROUND) << numStr;
            }
        }
    }

    /// @brief Draws the game board with snapshot-diff partial redraw
    /// @param stateBoard The visible cell states
    /// @param backgroundBoard The board with mines and numbers (unused, kept for interface)
    /// @param prevBoard Previous state snapshot (in/out: modified each frame)
    /// @param playerRow Current cursor row
    /// @param playerCol Current cursor column
    /// @param oldRow Previous cursor row (for clearing old highlight)
    /// @param oldCol Previous cursor column (for clearing old highlight)
    /// @param forceFullRedraw If true, redraws every cell
    inline void DrawBoard(
        const std::vector<std::vector<int>>& stateBoard,
        const std::vector<std::vector<int>>& /*backgroundBoard*/,
        std::vector<std::vector<int>>& prevBoard,
        int playerRow,
        int playerCol,
        int oldRow,
        int oldCol,
        bool forceFullRedraw)
    {
        const int rows = stateBoard.size();
        const int cols = stateBoard[0].size();
        const int boardX = BoardX(cols);
        const int boardY = BoardY(rows);

        if (forceFullRedraw) {
            // Full redraw: draw every cell
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    const int state = stateBoard[row][col];
                    const bool isCursor = (row == playerRow && col == playerCol);
                    const int cellX = boardX + col * CELL_WIDTH;
                    const int cellY = boardY + row;
                    DrawCell(cellX, cellY, state, isCursor);
                }
            }
        } else {
            // Partial redraw: only changed cells and cursor positions
            // Redraw old cursor position (remove highlight)
            if (oldRow >= 0 && oldRow < rows && oldCol >= 0 && oldCol < cols) {
                if (!(oldRow == playerRow && oldCol == playerCol)) {
                    const int cellX = boardX + oldCol * CELL_WIDTH;
                    const int cellY = boardY + oldRow;
                    DrawCell(cellX, cellY, stateBoard[oldRow][oldCol], false);
                }
            }

            // Redraw new cursor position (add highlight)
            const int cursorX = boardX + playerCol * CELL_WIDTH;
            const int cursorY = boardY + playerRow;
            DrawCell(cursorX, cursorY, stateBoard[playerRow][playerCol], true);

            // Redraw cells whose state changed
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    if (stateBoard[row][col] != prevBoard[row][col]) {
                        const bool isCursor = (row == playerRow && col == playerCol);
                        const int cellX = boardX + col * CELL_WIDTH;
                        const int cellY = boardY + row;
                        DrawCell(cellX, cellY, stateBoard[row][col], isCursor);
                    }
                }
            }
        }

        // Update prevBoard snapshot
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                prevBoard[row][col] = stateBoard[row][col];
            }
        }

        std::cout.flush();
    }

    /// @brief Updates feedback message with auto-clear after N frames
    /// @param feedback The feedback message string (modified to clear after 3 frames)
    /// @param frameCounter Frame counter (reset on each new message)
    inline void UpdateFeedback(std::string& feedback, int& frameCounter)
    {
        if (!feedback.empty()) {
            frameCounter++;
            if (frameCounter > 3) {
                feedback = "";
                frameCounter = 0;
            }
        }
    }

    /// @brief Main game board view with cursor, HUD, partial redraw, and input loop
    /// @param stateBoard  The visible cell states
    /// @param backgroundBoard The board with mines and numbers
    /// @param playerRow  Cursor row (modified by movement)
    /// @param playerCol  Cursor column (modified by movement)
    /// @param flagCount  Remaining flags (modified by FlagCommand)
    /// @param minesRemaining Total mines count
    /// @param difficulty 0=Easy, 1=Intermediate, 2=Hard
    /// @return -1=quit, 1=won, 2=lost
    inline int GameBoardView(
        std::vector<std::vector<int>>& stateBoard,
        const std::vector<std::vector<int>>& backgroundBoard,
        int& playerRow,
        int& playerCol,
        int& flagCount,
        int minesRemaining,
        int /*difficulty*/)
    {
        const int rows = stateBoard.size();
        const int cols = stateBoard[0].size();

        // Create prevBoard snapshot for partial redraw
        std::vector<std::vector<int>> prevBoard(rows, std::vector<int>(cols, -1));

        // Previous cursor position for partial redraw
        int oldRow = playerRow;
        int oldCol = playerCol;

        // Feedback message and frame counter
        std::string feedback = "";
        int feedbackCounter = 0;

        // First frame: full setup
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        // Draw HUD
        DrawHUD(flagCount, playerRow, playerCol, minesRemaining);

        // Full redraw on first frame
        DrawBoard(stateBoard, backgroundBoard, prevBoard, playerRow, playerCol, oldRow, oldCol, true);

        // Bottom bar
        Common::keysHelper = {
            {"\u2190 \u2192 \u2191 \u2193", "Mover"},
            {"R", "Revelar"},
            {"F", "Bandera"},
            {"Q", "Abandonar"}
        };
        Common::DrawBottomBar();
        std::cout.flush();

        while (true) {
            Common::key = Common::ReadConsoleChar();

            // Save old cursor position
            oldRow = playerRow;
            oldCol = playerCol;

            // Movement (arrows)
            if (Buscaminas::IsMoveKey(Common::key)) {
                Buscaminas::MoveCommand(playerRow, playerCol, rows, cols, Common::key);
            }
            // Reveal (R/r)
            else if (Common::key == Common::KEY_R || Common::key == Common::KEY_R_LOWER) {
                std::string fb;
                Buscaminas::RevealCommand(backgroundBoard, stateBoard, playerRow, playerCol, fb);
                if (!fb.empty()) {
                    feedback = fb;
                    feedbackCounter = 0;
                }
                if (Buscaminas::MineIsRevealed(backgroundBoard, playerRow, playerCol, fb)) {
                    return 2; // lost
                }
                if (Buscaminas::IsWonGameState(stateBoard, minesRemaining)) {
                    return 1; // won
                }
            }
            // Flag (F/f)
            else if (Common::key == Common::KEY_F || Common::key == Common::KEY_F_LOWER) {
                std::string fb;
                Buscaminas::FlagCommand(flagCount, stateBoard, playerRow, playerCol, fb);
                if (!fb.empty()) {
                    feedback = fb;
                    feedbackCounter = 0;
                }
            }
            // Quit (Q/q or Esc → confirm exit)
            else if (Common::key == Common::KEY_Q || Common::key == Common::KEY_Q_LOWER || Common::key == Common::KEY_ESCAPE) {
                if (ExitConfirmView()) {
                    return -1; // confirmed quit
                }
                // Redraw board after cancel
                Common::DrawBackground();
                DrawBoard(stateBoard, backgroundBoard, prevBoard, playerRow, playerCol, oldRow, oldCol, true);
                DrawHUD(flagCount, playerRow, playerCol, minesRemaining);
                Common::DrawBottomBar();
                std::cout.flush();
                continue;
            }

            // Update feedback counter
            if (!feedback.empty()) {
                feedbackCounter++;
                if (feedbackCounter > 3) {
                    feedback = "";
                    feedbackCounter = 0;
                }
            }

            // Partial redraw: draw background only over affected areas
            // Draw HUD each frame (flag count may change)
            DrawHUD(flagCount, playerRow, playerCol, minesRemaining);

            // Partial board redraw
            DrawBoard(stateBoard, backgroundBoard, prevBoard, playerRow, playerCol, oldRow, oldCol, false);

            // Draw feedback message
            if (!feedback.empty()) {
                Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(feedback), "center"), HUD_Y + 2);
                std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << feedback;
            } else {
                // Clear feedback line
                const std::string clearLine(Common::WIDTH_SCREEN, ' ');
                Common::GoToXY(0, HUD_Y + 2);
                std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << clearLine;
            }

            std::cout.flush();
        }
    }

} // namespace Buscaminas
