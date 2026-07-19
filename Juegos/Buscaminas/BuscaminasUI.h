#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "../../Common/Color.h"
#include "../../Common/Consts.h"
#include "../../Common/Components/BottomBar.h"
#include "../../Common/Graphics.h"
#include "../../Common/Terminal.h"
#include "../../Common/Aligned.h"
#include "../../Common/Variables.h"
#include "../../Common/Font.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"
#include "../../Common/Utils.h"
#include "../../Common/Navigation.h"
#include "../../Common/Input.h"
#include "BuscaminasService.h"

bool ExitConfirmView();


namespace Buscaminas
{
    const int Margin = 2;
    const int OptionsY = 38;
    const int BoxHeight = 3;
    const int BoxWidth = Common::WIDTH_SCREEN / 3;
    const int CellWidth = 2;
    const int HUD_Y = 2;

    /// @brief Colors for revealed number cells 1-8
    const std::array<std::array<int, 3>, 8> NUMBER_COLORS = {{
        Common::BLUE,             // 1
        Common::LIGHT_GREEN,       // 2
        Common::RED,               // 3
        Common::DARK_RED,          // 4
        {128, 0, 128},            // 5 — purple (not in Theme.h)
        Common::LIGHT_BLUE,        // 6
        Common::FOREGROUND_DARK,   // 7
        Common::GRAY               // 8
    }};

    /// @brief Helper: draws bottom bar with centered text
    inline void DrawBottomBarWithText(const std::string& text)
    {
        Common::DrawBottomBar();
        Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(text), "center"), Common::HEIGHT_SCREEN - 2);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BLUE) << text;
        std::cout.flush();
    }

    /// @brief Helper: draws a selection box with highlight
    inline void DrawOptionBox(int x, int y, int width, int height, const std::string& text, const std::array<int, 3>& fillColor, bool selected)
    {
        if (selected) {
            Common::PrintPrimaryBox(x, y, width, height, {text}, Common::FOREGROUND_LIGHT, Common::CURSOR, fillColor);
        } else {
            Common::PrintPrimaryBox(x, y, width, height, {text}, Common::FOREGROUND_DARK, fillColor, fillColor);
        }
    }

    // ─────────────────────────────────────────────────────────────────────────
    // VIEW 1: MainMenu
    // ─────────────────────────────────────────────────────────────────────────
    /// @brief Main menu — title + 4 options in 2×2 grid
    /// @return 0=Jugar, 1=Créditos, 2=Config, 3=Volver
    inline int MainMenuView()
    {
        const std::vector<std::string> options = {"JUGAR", "CRÉDITOS", "CONFIGURACIONES", "VOLVER"};
        const std::vector<std::array<int, 3>> optionColors = {
            Common::ORANGE, Common::GRAY, Common::LIGHT_BLUE, Common::LIGHT_GREEN
        };
        int option = 0;
        const int minOption = 0;
        const int maxOption = options.size() - 1;

        // Font title: "BUSCAMINAS"
        const auto titleFont = Common::ConcatFont(
            {Common::FONT_B, Common::FONT_U, Common::FONT_S, Common::FONT_C,
             Common::FONT_A, Common::FONT_M, Common::FONT_I, Common::FONT_N,
             Common::FONT_A, Common::FONT_S}, 2);
        const auto titleGradient = Common::Gradient(9, Common::YELLOW, Common::ORANGE);

        // Grid positions
        const int gridTotalWidth = 2 * BoxWidth + Margin;
        const int gridX = (Common::WIDTH_SCREEN - gridTotalWidth) / 2;
        const int gridY = 22;

        do {
            Common::EnableUTF8();
            Common::Clear();
            Common::DrawBackground();
            Common::HideCursor();

            // Draw title
            for (int i = 0; i < 9; i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(titleFont[i]), "center"),
                    HUD_Y + 2 + i, -1, -1,
                    {titleFont[i]},
                    titleGradient[i], Common::BACKGROUND
                );
            }

            // Draw option boxes (2×2 grid)
            for (int i = 0; i < 4; i++) {
                int boxX = (i % 2 == 0) ? gridX : gridX + BoxWidth + Margin;
                int boxY = (i / 2 == 0) ? gridY : gridY + BoxHeight + Margin;
                DrawOptionBox(boxX, boxY, BoxWidth, BoxHeight, options[i], optionColors[i], i == option);
            }

            DrawBottomBarWithText("Usa flechas para navegar, Enter para seleccionar");

            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                Common::SetOption(option, minOption, maxOption, Common::key);
            }

        } while (!Common::IsActionKey(Common::key));

        return option;
    }

    // ─────────────────────────────────────────────────────────────────────────
    // VIEW 2: LevelSelect
    // ─────────────────────────────────────────────────────────────────────────
    /// @brief Difficulty selection screen
    /// @return 0=Easy, 1=Intermediate, 2=Hard, -1=Back (Esc)
    inline int LevelSelectView()
    {
        const std::vector<std::string> levels = {"FÁCIL", "INTERMEDIO", "DIFÍCIL"};
        const std::vector<std::string> levelDescs = {"9x9 — ~4 minas", "16x16 — ~21 minas", "16x30 — ~60 minas"};
        const std::vector<std::array<int, 3>> levelColors = {
            Common::LIGHT_GREEN, Common::ORANGE, Common::RED
        };
        int option = 0;
        const int minOption = 0;
        const int maxOption = levels.size() - 1;

        do {
            Common::EnableUTF8();
            Common::Clear();
            Common::DrawBackground();
            Common::HideCursor();

            // Title
            const std::string title = "SELECCIONA DIFICULTAD";
            Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title), "center"), HUD_Y + 4);
            std::cout << Common::Color(Common::YELLOW, Common::BACKGROUND) << title;

            const int boxWidth = 40;
            const int boxX = (Common::WIDTH_SCREEN - boxWidth) / 2;
            const int boxStartY = 12;
            const int boxGap = BoxHeight + Margin;

            for (int i = 0; i < 3; i++) {
                int y = boxStartY + i * boxGap;
                std::string boxText = levels[i] + "  " + levelDescs[i];
                DrawOptionBox(boxX, y, boxWidth, BoxHeight, boxText, levelColors[i], i == option);
            }

            DrawBottomBarWithText("Enter para seleccionar, Esc para volver");

            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                Common::SetOption(option, minOption, maxOption, Common::key);
            } else if (Common::key == Common::KEY_ESCAPE) {
                return -1;
            }

        } while (!Common::IsActionKey(Common::key));

        return option;
    }

    // ─────────────────────────────────────────────────────────────────────────
    // VIEW 3: GameBoard
    // ─────────────────────────────────────────────────────────────────────────
    /// @brief Main game board view with cursor, HUD, and input loop
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
        int difficulty)
    {
        const int rows = stateBoard.size();
        const int cols = stateBoard[0].size();

        // Board centered horizontally
        const int boardWidth = cols * CellWidth;
        const int boardX = (Common::WIDTH_SCREEN - boardWidth) / 2;
        const int boardY = HUD_Y + 3;

        while (true) {
            Common::EnableUTF8();
            Common::Clear();
            Common::DrawBackground();
            Common::HideCursor();

            // ── HUD ──
            std::string hudText = "🚩 " + std::to_string(flagCount)
                + "  📍 (" + std::to_string(playerRow) + "," + std::to_string(playerCol) + ")"
                + "  💣 " + std::to_string(minesRemaining) + " restantes";
            Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(hudText), "center"), HUD_Y);
            std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << hudText;

            // ── Board grid ──
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    const int cellX = boardX + col * CellWidth;
                    const int cellY = boardY + row;
                    const bool isCursor = (row == playerRow && col == playerCol);
                    const int state = stateBoard[row][col];

                    if (state == -2) { // Flagged
                        if (isCursor) {
                            Common::DrawFillRectangle(cellX, cellY, CellWidth, 1, Common::EMPTY_BLOCK, Common::ORANGE, Common::FOREGROUND_DARK);
                            Common::GoToXY(cellX, cellY);
                            std::cout << Common::Color(Common::ORANGE, Common::FOREGROUND_DARK) << "⛳";
                        } else {
                            Common::DrawFillRectangle(cellX, cellY, CellWidth, 1, Common::EMPTY_BLOCK, Common::FOREGROUND_DARK, Common::SELECTION_BACKGROUND);
                            Common::GoToXY(cellX, cellY);
                            std::cout << Common::Color(Common::ORANGE, Common::SELECTION_BACKGROUND) << "⛳";
                        }
                    } else if (state == -1) { // Hidden
                        if (isCursor) {
                            Common::DrawFillRectangle(cellX, cellY, CellWidth, 1, Common::SHADING[0], Common::FOREGROUND_LIGHT, Common::FOREGROUND_DARK);
                        } else {
                            Common::DrawFillRectangle(cellX, cellY, CellWidth, 1, Common::SHADING[0], Common::SELECTION_FOREGROUND, Common::SELECTION_BACKGROUND);
                        }
                    } else if (state == 0) { // Safe (empty)
                        if (isCursor) {
                            Common::DrawFillRectangle(cellX, cellY, CellWidth, 1, Common::EMPTY_BLOCK, Common::FOREGROUND_DARK, Common::CURSOR);
                        } else {
                            Common::DrawFillRectangle(cellX, cellY, CellWidth, 1, Common::EMPTY_BLOCK, Common::BACKGROUND, Common::BACKGROUND);
                        }
                    } else if (1 <= state && state <= 8) { // Number
                        const auto& numColor = NUMBER_COLORS[state - 1];
                        const std::string numStr = std::to_string(state) + " ";
                        if (isCursor) {
                            Common::DrawFillRectangle(cellX, cellY, CellWidth, 1, Common::EMPTY_BLOCK, numColor, Common::CURSOR);
                            Common::GoToXY(cellX, cellY);
                            std::cout << Common::Color(numColor, Common::CURSOR) << numStr;
                        } else {
                            Common::DrawFillRectangle(cellX, cellY, CellWidth, 1, Common::EMPTY_BLOCK, numColor, Common::BACKGROUND);
                            Common::GoToXY(cellX, cellY);
                            std::cout << Common::Color(numColor, Common::BACKGROUND) << numStr;
                        }
                    }
                }
            }

            DrawBottomBarWithText("Flechas=mover  R=revelar  F=bandera  Q=abandonar");

            Common::key = Common::ReadConsoleChar();

            // Movement (arrows)
            if (Minesweeper::IsMoveKey(Common::key)) {
                Minesweeper::MoveCommand(playerRow, playerCol, rows, cols, Common::key);
            }
            // Reveal (R/r)
            else if (Common::key == Common::KEY_R || Common::key == Common::KEY_R_LOWER) {
                std::string fb;
                Minesweeper::RevealCommand(backgroundBoard, stateBoard, playerRow, playerCol, fb);
                if (Minesweeper::MineIsRevealed(backgroundBoard, playerRow, playerCol, fb)) {
                    return 2; // lost
                }
                if (Minesweeper::IsWonGameState(stateBoard, minesRemaining)) {
                    return 1; // won
                }
            }
            // Flag (F/f)
            else if (Common::key == Common::KEY_F || Common::key == Common::KEY_F_LOWER) {
                std::string fb;
                Minesweeper::FlagCommand(flagCount, stateBoard, playerRow, playerCol, fb);
            }
            // Quit (Q/q or Esc → confirm exit)
            else if (Common::key == Common::KEY_Q || Common::key == Common::KEY_Q_LOWER || Common::key == Common::KEY_ESCAPE) {
                if (ExitConfirmView()) {
                    return -1; // confirmed quit
                }
                // else: cancelled → continue game (loop redraws board)
            }
        }
    }

    // ─────────────────────────────────────────────────────────────────────────
    // VIEW 4: ExitConfirm
    // ─────────────────────────────────────────────────────────────────────────
    /// @brief Confirmation dialog when quitting a game
    /// @return true=confirm exit, false=cancel
    inline bool ExitConfirmView()
    {
        const int boxWidth = 40;
        const int boxHeight = 5;
        const int boxX = (Common::WIDTH_SCREEN - boxWidth) / 2;
        const int boxY = (Common::HEIGHT_SCREEN - boxHeight) / 2;

        int option = 1; // default: NO
        const int minOption = 0;
        const int maxOption = 1;

        do {
            Common::EnableUTF8();
            Common::DrawBackground();
            Common::HideCursor();

            // Message box
            Common::PrintPrimaryBox(boxX, boxY, boxWidth, boxHeight,
                {"¿Quieres abandonar", "la partida?"},
                Common::FOREGROUND_LIGHT, Common::GRAY, Common::SELECTION_BACKGROUND);

            // Options: SÍ and NO
            const int optY = boxY + boxHeight + Margin;
            const int optWidth = 12;
            const int optSpacing = 4;
            const int totalOptWidth = 2 * optWidth + optSpacing;
            const int optStartX = (Common::WIDTH_SCREEN - totalOptWidth) / 2;

            DrawOptionBox(optStartX, optY, optWidth, BoxHeight, "SÍ", Common::RED, option == 0);
            DrawOptionBox(optStartX + optWidth + optSpacing, optY, optWidth, BoxHeight, "NO", Common::LIGHT_GREEN, option == 1);

            DrawBottomBarWithText("Enter para confirmar");

            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                Common::SetOption(option, minOption, maxOption, Common::key);
            } else if (Common::key == Common::KEY_ESCAPE) {
                return false;
            }
        } while (!Common::IsActionKey(Common::key));

        return (option == 0); // true if SÍ selected
    }

    // ─────────────────────────────────────────────────────────────────────────
    // VIEW 5: GameOver
    // ─────────────────────────────────────────────────────────────────────────
    /// @brief Result screen after winning or losing
    /// @param won true if victory, false if defeat
    /// @return 0=play again, 1=back to menu
    inline int GameOverView(bool won)
    {
        int selectedOption = 0;
        const int minOption = 0;
        const int maxOption = 1;

        Common::EnableUTF8();

        if (won) {
            // Victory: "VICTORIA" in Font.h with YELLOW → ORANGE gradient
            const auto victoryFont = Common::ConcatFont(
                {Common::FONT_V, Common::FONT_I, Common::FONT_C, Common::FONT_T,
                 Common::FONT_O, Common::FONT_R, Common::FONT_I, Common::FONT_A}, 2);
            const auto gradient = Common::Gradient(9, Common::YELLOW, Common::ORANGE);

            // Background flash
            for (int flash = 0; flash < 3; flash++) {
                Common::DrawFillRectangle(0, 0, Common::WIDTH_SCREEN, Common::HEIGHT_SCREEN,
                    Common::EMPTY_BLOCK, Common::FOREGROUND_LIGHT,
                    (flash % 2 == 0) ? Common::YELLOW : Common::BACKGROUND);
                Common::Sleep(150);
            }
            Common::DrawBackground();

            // Draw title
            for (int i = 0; i < 9; i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(victoryFont[i]), "center"),
                    HUD_Y + 3 + i, -1, -1,
                    {victoryFont[i]},
                    gradient[i], Common::BACKGROUND
                );
            }
        } else {
            // Defeat: "DERROTA" in Font.h with RED → DARK_RED gradient
            const auto defeatFont = Common::ConcatFont(
                {Common::FONT_D, Common::FONT_E, Common::FONT_R, Common::FONT_R,
                 Common::FONT_O, Common::FONT_T, Common::FONT_A}, 2);
            const auto gradient = Common::Gradient(9, Common::RED, Common::DARK_RED);

            Common::DrawBackground();

            for (int i = 0; i < 9; i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(defeatFont[i]), "center"),
                    HUD_Y + 3 + i, -1, -1,
                    {defeatFont[i]},
                    gradient[i], Common::BACKGROUND
                );
            }
        }

        // Options
        const std::vector<std::string> options = {"JUGAR DE NUEVO", "VOLVER AL MENÚ"};
        const std::vector<std::array<int, 3>> optColors = {Common::ORANGE, Common::GRAY};
        const int boxWidth = 30;
        const int boxX = (Common::WIDTH_SCREEN - boxWidth) / 2;
        const int boxStartY = 24;
        const int boxGap = BoxHeight + Margin;

        do {
            // Redraw options (they change with selection)
            for (int i = 0; i < 2; i++) {
                DrawOptionBox(boxX, boxStartY + i * boxGap, boxWidth, BoxHeight, options[i], optColors[i], i == selectedOption);
            }

            DrawBottomBarWithText("Enter para seleccionar");

            Common::key = Common::ReadConsoleChar();
            if (Common::IsNavigationKey(Common::key)) {
                Common::SetOption(selectedOption, minOption, maxOption, Common::key);
            }
        } while (!Common::IsActionKey(Common::key));

        return selectedOption; // 0=play again, 1=menu
    }

    // ─────────────────────────────────────────────────────────────────────────
    // VIEW 6: Credits
    // ─────────────────────────────────────────────────────────────────────────
    /// @brief Credits screen
    inline void CreditsView()
    {
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        const std::string title = "CRÉDITOS";
        Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title), "center"), HUD_Y + 4);
        std::cout << Common::Color(Common::YELLOW, Common::BACKGROUND) << title;

        const int textY = 12;
        const std::vector<std::string> credits = {
           
        };

        for (size_t i = 0; i < credits.size(); i++) {
            Common::GoToXY(
                Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(credits[i]), "center"),
                textY + static_cast<int>(i)
            );
            std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << credits[i];
        }

        DrawBottomBarWithText("Presiona Q para volver");

        // Wait for Q
        do {
            Common::key = Common::ReadConsoleChar();
        } while (Common::key != Common::KEY_Q && Common::key != Common::KEY_Q_LOWER && Common::key != Common::KEY_ESCAPE);
    }

    // ─────────────────────────────────────────────────────────────────────────
    // VIEW 7: Config
    // ─────────────────────────────────────────────────────────────────────────
    /// @brief Configuration screen with player name input
    inline void ConfigView()
    {
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        const std::string title = "CONFIGURACIONES";
        Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title), "center"), HUD_Y + 4);
        std::cout << Common::Color(Common::YELLOW, Common::BACKGROUND) << title;

        // Label
        const std::string label = "Nombre del jugador:";
        const int labelX = 40;
        const int labelY = 12;
        Common::GoToXY(labelX, labelY);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << label;

        // Input field
        const int inputWidth = 30;
        const int inputX = labelX + Common::Length(label) + 2;
        const int inputY = labelY;
        std::string input = Common::playerName;

        DrawBottomBarWithText("Enter para guardar, Esc para volver");

        while (true) {
            // Draw input box
            Common::DrawFillRectangle(
                inputX, inputY,
                inputWidth, 1,
                Common::EMPTY_BLOCK,
                Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND
            );

            // Draw input text
            Common::GoToXY(inputX, inputY);
            std::string displayInput = input;
            if (displayInput.size() > static_cast<size_t>(inputWidth)) {
                displayInput = displayInput.substr(0, inputWidth);
            }
            std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << displayInput
                      << Common::ResetColor();
            std::cout.flush();

            Common::key = Common::ReadConsoleChar();

            if (Common::key == Common::KEY_ENTER) {
                Common::playerName = input;
                return;
            } else if (Common::key == Common::KEY_ESCAPE) {
                return;
            } else if (Common::key == Common::KEY_BACKSPACE) {
                if (!input.empty()) {
                    input.pop_back();
                }
            } else if (input.size() < static_cast<size_t>(inputWidth) && Common::IsAlphaNumChar(Common::key)) {
                for (char c : Common::CastKeyToString(Common::key)) {
                    input.push_back(c);
                }
            }
        }
    }

} // namespace Buscaminas
