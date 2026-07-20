#pragma once

// 1. Librerías estándar
#include <array>
#include <iostream>
#include <string>
#include <vector>

// 2. Librerías propias (jerarquía + orden alfabético)
#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/UnicodeGlyphs.h"
#include "../../../Common/Variables.h"

#include "../TictactoeUI.h"

// Forward declaration — ExitConfirmView is defined in ExitConfirmView.h
namespace Tictactoe
{
    bool ExitConfirmView();
}

namespace Tictactoe
{
    // ── Board border/separator constants ──
    const int CELL_ROWS[3] = {2, 6, 10};
    const int CELL_COLS[3] = {2, 6, 10};

    /// @brief Draws a single cell on the board with cursor highlight
    /// @param tablero The 13x13 game board
    /// @param cellIdx Cell index 0-8
    /// @param cursorPos Current cursor position
    /// @param bx Board X origin
    /// @param by Board Y origin
    inline void DrawCell(char tablero[13][13], int cellIdx, int cursorPos, int bx, int by) {
        int block = cellIdx / 3;
        int col = cellIdx % 3;
        int internalRow = CELL_ROWS[block];
        int internalCol = CELL_COLS[col];
        char ch = tablero[internalRow][internalCol];
        bool isCursor = (cellIdx == cursorPos);

        for (int sub = 0; sub < CELL_H; sub++) {
            int cellX = bx + 1 + col * (CELL_W + 1);
            int cellY = by + block * (CELL_H + 1) + sub;
            bool isContentRow = (sub == 2);

            std::array<int, 3> bgColor;
            std::array<int, 3> textColor = Common::FOREGROUND_DARK;
            std::string text = "";
            bool hasContent = false;

            if (ch == 'X') {
                bgColor = isCursor ? Common::CURSOR : Common::RED;
                text = "\u2715";
                hasContent = true;
            } else if (ch == 'O') {
                bgColor = isCursor ? Common::CURSOR : Common::BLUE;
                text = "\u25CB";
                hasContent = true;
            } else if (ch >= '1' && ch <= '9') {
                bgColor = isCursor ? Common::CURSOR : Common::SELECTION_BACKGROUND;
                text = std::string(1, ch);
                textColor = isCursor ? Common::FOREGROUND_LIGHT : Common::GRAY;
                hasContent = true;
            } else {
                bgColor = Common::SELECTION_BACKGROUND;
            }

            // Fill cell background
            Common::DrawFillRectangle(cellX, cellY, CELL_W, 1, Common::EMPTY_BLOCK, bgColor, bgColor);

            // Render content on content sub-row
            if (isContentRow && hasContent) {
                Common::GoToXY(cellX + 3, cellY);
                std::cout << Common::Color(textColor, bgColor) << text;
            }

            // Vertical separator after cell (right border)
            if (col < 2) {
                int sepX = cellX + CELL_W;
                Common::GoToXY(sepX, cellY);
                std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::VERTICAL_BORDER;
            }
        }
    }

    /// @brief Draws the full board from scratch (borders, separators, all 9 cells)
    /// @param tablero The 13x13 game board
    /// @param cursorPos Current cursor position
    /// @param bx Board X origin
    /// @param by Board Y origin
    inline void DrawFullBoard(char tablero[13][13], int cursorPos, int bx, int by) {
        // ┌───────────────────────┐
        Common::GoToXY(bx, by - 1);
        std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::TOP_LEFT_CORNER;
        for (int i = 0; i < BOARD_W - 2; i++) std::cout << Common::HORIZONTAL_BORDER;
        std::cout << Common::TOP_RIGHT_CORNER;

        // 3 blocks × 4 sub-rows
        for (int block = 0; block < 3; block++) {
            for (int sub = 0; sub < CELL_H; sub++) {
                int rowY = by + block * (CELL_H + 1) + sub;

                // Left border
                Common::GoToXY(bx, rowY);
                std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::VERTICAL_BORDER;

                for (int c = 0; c < 3; c++) {
                    int cellIdx = block * 3 + c;
                    DrawCell(tablero, cellIdx, cursorPos, bx, by);
                }

                // Right border
                Common::GoToXY(bx + BOARD_W - 1, rowY);
                std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::VERTICAL_BORDER;
            }

            // Separator between blocks: ├───────┼───────┼───────┤
            if (block < 2) {
                int sepY = by + (block + 1) * (CELL_H + 1) - 1;
                Common::GoToXY(bx, sepY);
                std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::LEFT_TEE;
                for (int c = 0; c < 3; c++) {
                    for (int i = 0; i < CELL_W; i++) std::cout << Common::HORIZONTAL_BORDER;
                    if (c < 2) std::cout << Common::CROSS;
                }
                std::cout << Common::RIGHT_TEE;
            }
        }

        // └───────────────────────┘
        int bottomY = by + 3 * (CELL_H + 1) - 1;
        Common::GoToXY(bx, bottomY);
        std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::BOTTOM_LEFT_CORNER;
        for (int i = 0; i < BOARD_W - 2; i++) std::cout << Common::HORIZONTAL_BORDER;
        std::cout << Common::BOTTOM_RIGHT_CORNER;
    }

    /// @brief Draws the game board with snapshot-diff partial redraw
    /// @param tablero The 13x13 game board
    /// @param cursorPos Current cursor position
    /// @param forceFullRedraw If true, redraws the entire board
    inline void DrawBoard(char tablero[13][13], int cursorPos, bool forceFullRedraw) {
        static bool initialized = false;
        static int prevContent[9] = {0};
        static int prevCursor[9] = {0};

        const int bx = BoardX();
        const int by = BoardY();

        if (forceFullRedraw || !initialized) {
            DrawFullBoard(tablero, cursorPos, bx, by);

            // Initialize snapshot
            for (int i = 0; i < 9; i++) {
                int row = CELL_ROWS[i / 3];
                int col = CELL_COLS[i % 3];
                prevContent[i] = static_cast<int>(tablero[row][col]);
                prevCursor[i] = (i == cursorPos) ? 1 : 0;
            }
            initialized = true;
        } else {
            // Partial redraw: only cells whose content or cursor state changed
            for (int i = 0; i < 9; i++) {
                int row = CELL_ROWS[i / 3];
                int col = CELL_COLS[i % 3];
                int currentContent = static_cast<int>(tablero[row][col]);
                int currentCursor = (i == cursorPos) ? 1 : 0;

                if (currentContent != prevContent[i] || currentCursor != prevCursor[i]) {
                    DrawCell(tablero, i, cursorPos, bx, by);
                    prevContent[i] = currentContent;
                    prevCursor[i] = currentCursor;
                }
            }
        }

        std::cout.flush();
    }

    /// @brief HUD over the board: turn piece, cursor position, game mode
    /// @param piece Current player piece ('X' or 'O')
    /// @param cursorPos Current cursor position 0-8
    /// @param isFootball Whether in football mode
    inline void DrawHUD(char piece, int cursorPos, bool isFootball) {
        int row = cursorPos / 3 + 1;
        int col = cursorPos % 3 + 1;
        std::string mode = isFootball ? "Futbol" : "Original";

        std::string prefix = "\u2500 Turno de ";
        std::string suffix = " \u2500 Pos: (" + std::to_string(row) + "," + std::to_string(col) + ") | " + mode;
        std::string fullText = prefix + piece + suffix;

        std::array<int, 3> pieceColor = (piece == 'X') ? Common::RED : Common::BLUE;
        int textX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(fullText), "center");
        int y = BoardY() - 2;

        Common::GoToXY(textX, y);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << prefix;
        std::cout << Common::Color(pieceColor, Common::BACKGROUND) << piece;
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << suffix;
        std::cout.flush();
    }

    /// @brief Bottom bar with game-specific hints
    /// @param text Custom hint text for the middle of the bar
    inline void DrawBottomBarWithText(const std::string& text) {
        Common::keysHelper = {{"\u2190 \u2192 \u2191 \u2193", "Mover"}, {"ENTER", "Colocar"}, {"Q", "Salir"}};
        Common::DrawBottomBar();
        std::cout.flush();
    }

    /// @brief Pre-game transition screen "preparate" with fade-in
    inline void DrawTransition() {
        Common::Clear();
        Common::DrawBackground();

        std::vector<std::array<std::string, 4>> glyphs = Common::Font4String("preparate");
        std::array<std::string, 4> texto = Common::ConcatFont(glyphs, 1);
        int textW = Common::Length(texto[0]);
        int tx = Common::AlignedX(0, Common::WIDTH_SCREEN, textW, "center");
        int ty = Common::AlignedY(0, Common::HEIGHT_SCREEN, 4, "center");

        for (int k = 0; k < 8; k++) {
            for (int i = 0; i < 4; i++) {
                Common::DrawText(tx, ty + i, -1, -1, {texto[i]},
                    {
                        Common::BACKGROUND[0] + (Common::FOREGROUND_LIGHT[0] - Common::BACKGROUND[0]) * (k + 1) / 8,
                        Common::BACKGROUND[1] + (Common::FOREGROUND_LIGHT[1] - Common::BACKGROUND[1]) * (k + 1) / 8,
                        Common::BACKGROUND[2] + (Common::FOREGROUND_LIGHT[2] - Common::BACKGROUND[2]) * (k + 1) / 8
                    },
                    Common::BACKGROUND);
            }
            std::cout.flush();
            Common::Sleep(80);
        }
        Common::Sleep(500);
    }

} // namespace Tictactoe
