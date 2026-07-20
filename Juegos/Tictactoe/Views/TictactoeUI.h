#pragma once

// 1. Librerías estándar
#include <array>
#include <iostream>
#include <string>
#include <vector>

// 2. Librerías propias (jerarquía + orden alfabético)
#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/SelectPrimaryBox.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/UnicodeGlyphs.h"

namespace Common { void DrawBottomBar(); }

namespace Tictactoe
{
    // === Layout Constants ===

    /// @brief Ancho de cada celda en caracteres
    const int CELL_W = 7;
    /// @brief Alto de cada celda en líneas
    const int CELL_H = 4;
    /// @brief Ancho visual total del tablero (3*7 + 4 bordes)
    const int BOARD_W = 25;
    /// @brief Alto visual total del tablero (1 top + 12 celdas + 2 separadores + 1 bottom)
    const int BOARD_H = 16;

    /// @brief Coordenada X centrada del tablero (25 chars)
    inline int BoardX() {
        return Common::AlignedX(0, Common::WIDTH_SCREEN, BOARD_W, "center");
    }

    /// @brief Coordenada Y centrada del tablero (16 líneas)
    inline int BoardY() {
        return Common::AlignedY(0, Common::HEIGHT_SCREEN, BOARD_H, "center");
    }

    /// @brief Coordenada X del panel de quiz (derecha del tablero)
    inline int QuizX() {
        return BoardX() + BOARD_W + 2;
    }

    /// @brief Coordenada Y del panel de quiz (alineado con el tablero)
    inline int QuizY() {
        return BoardY();
    }

    const int QuizW = 42, QuizH = 14;

    // === Internal cell index helpers ===

    /// @brief Mapea cursorPos (0-8) a fila interna del tablero (2,6,10)
    inline int cellRow(int cursorPos) {
        const int rows[3] = {2, 6, 10};
        return rows[cursorPos / 3];
    }

    /// @brief Mapea cursorPos (0-8) a columna interna del tablero (2,6,10)
    inline int cellCol(int cursorPos) {
        const int cols[3] = {2, 6, 10};
        return cols[cursorPos % 3];
    }

    // === Helper ===

    /// @brief Imprime texto centrado en X
    inline void PrintCentered(int y, const std::string& text, std::array<int,3> fg, std::array<int,3> bg) {
        int x = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(text), "center");
        Common::GoToXY(x, y);
        std::cout << Common::Color(fg, bg) << text;
    }

    // === Tablero con celdas por DrawFillRectangle ===

    /// @brief Dibuja el tablero 3x3 celda por celda con cursor highlight
    inline void DrawBoard(char tablero[13][13], int cursorPos) {
        const int bx = BoardX();
        const int by = BoardY();
        const int cellRows[3] = {2, 6, 10};
        const int cellCols[3] = {2, 6, 10};

        // ┌───────────────────────┐
        Common::GoToXY(bx, by - 1);
        std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::TOP_LEFT_CORNER;
        for (int i = 0; i < BOARD_W - 2; i++) std::cout << Common::HORIZONTAL_BORDER;
        std::cout << Common::TOP_RIGHT_CORNER;

        // 3 bloques × 4 sub-rows
        for (int block = 0; block < 3; block++) {
            for (int sub = 0; sub < CELL_H; sub++) {
                int rowY = by + block * (CELL_H + 1) + sub;
                bool isContentRow = (sub == 2);

                // Left border
                Common::GoToXY(bx, rowY);
                std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::VERTICAL_BORDER;

                for (int c = 0; c < 3; c++) {
                    int cellIdx = block * 3 + c;
                    int cellX = bx + 1 + c * (CELL_W + 1);
                    int cellY = rowY;

                    int internalRow = cellRows[block];
                    int internalCol = cellCols[c];
                    char ch = tablero[internalRow][internalCol];

                    bool isCursor = (cellIdx == cursorPos);

                    std::array<int,3> bgColor;
                    std::array<int,3> textColor = Common::FOREGROUND_DARK;
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

                    // Cell separator
                    if (c < 2) {
                        Common::GoToXY(cellX + CELL_W, cellY);
                        std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << Common::VERTICAL_BORDER;
                    }
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

        std::cout.flush();
    }

    // === HUD ===

    /// @brief HUD sobre el tablero: turno, posición del cursor y modo
    inline void DrawHUD(char piece, int cursorPos, bool isFootball) {
        int row = cursorPos / 3 + 1;
        int col = cursorPos % 3 + 1;
        std::string mode = isFootball ? "Futbol" : "Original";

        std::string prefix = "\u2500 Turno de ";
        std::string suffix = " \u2500 Pos: (" + std::to_string(row) + "," + std::to_string(col) + ") | " + mode;
        std::string fullText = prefix + piece + suffix;

        std::array<int,3> pieceColor = (piece == 'X') ? Common::RED : Common::BLUE;
        int textX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(fullText), "center");
        int y = BoardY() - 2;

        Common::GoToXY(textX, y);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << prefix;
        std::cout << Common::Color(pieceColor, Common::BACKGROUND) << piece;
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << suffix;
        std::cout.flush();
    }

    // === Bottom bar ===

    /// @brief Bottom bar con hints del juego (sin texto adicional superpuesto)
    inline void DrawBottomBarWithText(const std::string& text) {
        Common::keysHelper = {{"\u2190 \u2192 \u2191 \u2193", "Mover"}, {"ENTER", "Colocar"}, {"Q", "Salir"}};
        Common::DrawBottomBar();
        std::cout.flush();
    }

    // === Transición ===

    /// @brief Pantalla de transición "Preparate..."
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

    // === Menú principal ===

    /// @brief Pantalla integrada: título FONT9 + grid 2x2
    inline int DrawMenuScreen() {
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        Common::keysHelper = {
            {"\u2190 \u2192 \u2191 \u2193", "Navegar"},
            {"ENTER", "Seleccionar"}
        };

        // Título FONT9
        std::array<std::string, 9> titulo = Common::ConcatFont({
            Common::FONT9_T, Common::FONT9_I, Common::FONT9_C,
            Common::FONT9_BLANK,
            Common::FONT9_T, Common::FONT9_A, Common::FONT9_C,
            Common::FONT9_BLANK,
            Common::FONT9_T, Common::FONT9_O, Common::FONT9_E
        }, 2);

        std::vector<std::array<int, 3>> colores = Common::Gradient(9, Common::DARK_RED, Common::ACCENT);

        for (int k = 0; k < 6; k++) {
            for (int i = 0; i < static_cast<int>(titulo.size()); i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(titulo[i]), "center"),
                    3 + i, -1, -1, {titulo[i]},
                    {
                        Common::BACKGROUND[0] + (colores[i][0] - Common::BACKGROUND[0]) * (k + 1) / 6,
                        Common::BACKGROUND[1] + (colores[i][1] - Common::BACKGROUND[1]) * (k + 1) / 6,
                        Common::BACKGROUND[2] + (colores[i][2] - Common::BACKGROUND[2]) * (k + 1) / 6
                    },
                    Common::BACKGROUND);
            }
            std::cout.flush();
            Common::Sleep(50);
        }

        // Grid 2×2
        const int gridY = 16;
        const int slotW = 25;
        const int slotH = 3;

        std::array<std::string, 4> opciones = {"Original", "Futbol", "Instrucciones", "Salir"};
        int seleccion = 0;

        Common::SelectPrimaryBox2D(
            Common::AlignedX(0, Common::WIDTH_SCREEN, slotW * 2 + 4, "center"),
            gridY, opciones, seleccion,
            Common::GRAY, Common::SELECTION_BACKGROUND,
            Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT,
            slotW, slotH
        );

        Common::DrawBottomBar();
        std::cout.flush();
        return seleccion;
    }

    // === Instrucciones ===

    /// @brief Pantalla de instrucciones con FONT4 y colores del juego
    inline void DrawInstructions(bool isFootball) {
        Common::Clear();
        Common::DrawBackground();

        // Título FONT4
        std::string tituloStr = isFootball ? "tic tac toe futbol" : "tic tac toe";
        std::vector<std::array<std::string, 4>> tg = Common::Font4String(tituloStr);
        std::array<std::string, 4> titulo = Common::ConcatFont(tg, 1);
        int tw = Common::Length(titulo[0]);
        int tx = Common::AlignedX(0, Common::WIDTH_SCREEN, tw, "center");
        for (int i = 0; i < 4; i++)
            Common::DrawText(tx, 2 + i, -1, -1, {titulo[i]}, Common::ACCENT, Common::BACKGROUND);

        // Subtítulo
        std::vector<std::array<std::string, 4>> sg = Common::Font4String("instrucciones");
        std::array<std::string, 4> sub = Common::ConcatFont(sg, 1);
        int sw = Common::Length(sub[0]);
        int sx = Common::AlignedX(0, Common::WIDTH_SCREEN, sw, "center");
        for (int i = 0; i < 4; i++)
            Common::DrawText(sx, 8 + i, -1, -1, {sub[i]}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        const int cx = Common::AlignedX(0, Common::WIDTH_SCREEN, 50, "center");

        if (isFootball) {
            auto line = [&](int y, const std::string& t) {
                Common::GoToXY(cx, y);
                std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << t;
            };
            line(14, "1. Cada jugador debe responder una pregunta de futbol.");
            line(15, "2. Si responde correctamente puede colocar su ficha.");
            line(16, "3. Si responde mal pierde su turno.");
            line(17, "4. Forma una linea de 3 fichas para ganar.");

            Common::GoToXY(cx, 19);
            std::cout << Common::Color(Common::ACCENT, Common::BACKGROUND) << "Categorias:";

            auto cat = [&](int y, const std::string& c) {
                Common::GoToXY(cx + 2, y);
                std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << "- "
                          << Common::Color(Common::LIGHT_GREEN, Common::BACKGROUND) << c;
            };
            cat(21, "Mundiales");
            cat(22, "Champions League");
            cat(23, "Balon de Oro");
            cat(24, "Futbol internacional");
        } else {
            auto line = [&](int y, const std::string& t) {
                Common::GoToXY(cx, y);
                std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << t;
            };
            line(14, "1. El jugador X comienza la partida.");
            line(15, "2. Use flechas para moverse y Enter para colocar.");
            line(16, "3. No puede elegir una casilla ocupada.");
            line(17, "4. Gana quien forme una linea de 3 fichas.");

            Common::GoToXY(cx, 19);
            std::cout << Common::Color(Common::ACCENT, Common::BACKGROUND) << "Distribucion de las casillas:";

            const int gx = Common::AlignedX(0, Common::WIDTH_SCREEN, 11, "center");
            for (int r = 0; r < 3; r++) {
                Common::GoToXY(gx, 21 + r * 2);
                for (int c = 0; c < 3; c++) {
                    char num = '1' + r * 3 + c;
                    std::cout << Common::Color(Common::GRAY, Common::BACKGROUND);
                    if (c > 0) std::cout << "|";
                    std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND) << " " << num << " ";
                }
                if (r < 2) {
                    Common::GoToXY(gx, 22 + r * 2);
                    std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << "--+---+--";
                }
            }
        }

        // Prompt centrado
        std::string promptText = "Presiona una tecla...";
        int promptLen = Common::Length(promptText);
        int promptX = Common::AlignedX(0, Common::WIDTH_SCREEN, promptLen, "center");
        int promptY = 28;
        Common::GoToXY(promptX, promptY);
        std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << promptText;

        Common::keysHelper = {{"", " Continuar"}};
        Common::DrawBottomBar();
        std::cout.flush();
        Common::Getch();
        Common::Clear();
    }

    // === Panel de quiz ===

    inline void DrawQuizPanel() {
        Common::PrintPrimaryBox(QuizX(), QuizY(), QuizW, QuizH,
            {"QUIZ FUTBOLERO"},
            Common::ACCENT, Common::GRAY, Common::SELECTION_BACKGROUND);
        Common::DrawBottomBar();
    }

    inline void ClearQuizPanel() {
        Common::DrawFillRectangle(
            QuizX() + 1, QuizY() + 1,
            QuizW - 2, QuizH - 2,
            Common::FULL_BLOCK,
            Common::SELECTION_BACKGROUND, Common::BACKGROUND);
        std::cout.flush();
    }

    // === Turno ===

    inline void DrawCorrectAnswer() {
        Common::GoToXY(QuizX() + 2, QuizY() + 13);
        std::cout << Common::Color(Common::LIGHT_GREEN, Common::SELECTION_BACKGROUND) << "\u2714 Correcto!";
        std::cout.flush();
    }

    inline void DrawSelectCellPrompt() {
        Common::GoToXY(QuizX() + 2, QuizY() + 15);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND)
                  << "Enter para colocar";
        std::cout.flush();
    }

    // === Resultado y victoria ===

    inline void DrawResult() {
        int ry = BoardY() + 3 * (CELL_H + 1);  // below bottom border
        std::string text;
        std::array<int,3> color;
        if (ganar('X')) {
            text = " \u2500 \u2715 Gana X \u2715 \u2500 ";
            color = Common::RED;
        } else if (ganar('O')) {
            text = " \u2500 \u25CB Gana O \u25CB \u2500 ";
            color = Common::BLUE;
        } else {
            text = " \u2500 Empate \u2500 ";
            color = Common::FOREGROUND_LIGHT;
        }
        int textLen = Common::Length(text);
        Common::GoToXY(Common::AlignedX(0, Common::WIDTH_SCREEN, textLen, "center"), ry);
        std::cout << Common::Color(color, Common::BACKGROUND) << text;
        std::cout.flush();
        Common::DrawBottomBar();
    }

    /// @brief Pantalla de victoria completa
    inline void DrawVictoryScreen() {
        Common::Clear();
        Common::DrawBackground();

        // Título FONT9 "WINNER"
        std::array<std::string, 9> winTitle = Common::ConcatFont({
            Common::FONT9_W, Common::FONT9_I, Common::FONT9_N, Common::FONT9_N,
            Common::FONT9_E, Common::FONT9_R
        }, 2);

        std::vector<std::array<int,3>> winColors = Common::Gradient(9, Common::DARK_RED, Common::ACCENT);

        // Fade in
        for (int k = 0; k < 8; k++) {
            for (int i = 0; i < static_cast<int>(winTitle.size()); i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(winTitle[i]), "center"),
                    5 + i, -1, -1, {winTitle[i]},
                    {
                        Common::BACKGROUND[0] + (winColors[i][0] - Common::BACKGROUND[0]) * (k+1) / 8,
                        Common::BACKGROUND[1] + (winColors[i][1] - Common::BACKGROUND[1]) * (k+1) / 8,
                        Common::BACKGROUND[2] + (winColors[i][2] - Common::BACKGROUND[2]) * (k+1) / 8
                    },
                    Common::BACKGROUND);
            }
            std::cout.flush();
            Common::Sleep(60);
        }
        Common::Sleep(400);

        // Fade out
        for (int k = 8; k > 0; k--) {
            for (int i = 0; i < static_cast<int>(winTitle.size()); i++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(winTitle[i]), "center"),
                    5 + i, -1, -1, {winTitle[i]},
                    {
                        Common::BACKGROUND[0] + (winColors[i][0] - Common::BACKGROUND[0]) * k / 8,
                        Common::BACKGROUND[1] + (winColors[i][1] - Common::BACKGROUND[1]) * k / 8,
                        Common::BACKGROUND[2] + (winColors[i][2] - Common::BACKGROUND[2]) * k / 8
                    },
                    Common::BACKGROUND);
            }
            std::cout.flush();
            Common::Sleep(60);
        }

        Common::Clear();
        Common::DrawBackground();

        // Ganador con FONT4 — centrado arriba
        std::string winStr = ganar('X') ? "gana jugador x" : (ganar('O') ? "gana jugador o" : "empate");
        std::vector<std::array<std::string,4>> wg = Common::Font4String(winStr);
        std::array<std::string,4> winText = Common::ConcatFont(wg, 1);
        int ww = Common::Length(winText[0]);
        int wx = Common::AlignedX(0, Common::WIDTH_SCREEN, ww, "center");
        int winY = Common::AlignedY(0, Common::HEIGHT_SCREEN, 4, "center") - 3;

        std::array<int,3> winColor = ganar('X') ? Common::RED :
                                     (ganar('O') ? Common::BLUE : Common::FOREGROUND_LIGHT);

        for (int i = 0; i < 4; i++)
            Common::DrawText(wx, winY + i, -1, -1, {winText[i]}, winColor, Common::BACKGROUND);

        // Prompt centrado abajo del texto ganador
        std::string promptText = "Presiona una tecla...";
        int promptLen = Common::Length(promptText);
        int promptX = Common::AlignedX(0, Common::WIDTH_SCREEN, promptLen, "center");
        int promptY = winY + 6;
        Common::GoToXY(promptX, promptY);
        std::cout << Common::Color(Common::GRAY, Common::BACKGROUND) << promptText;

        Common::DrawBottomBar();
        std::cout.flush();
        Common::Getch();
    }

    // === Jugar de nuevo ===

    inline void DrawPlayAgainPrompt() {
        int ry = BoardY() + 3 * (CELL_H + 1) + 1;
        const int x = Common::AlignedX(0, Common::WIDTH_SCREEN, 36, "center");
        Common::GoToXY(x, ry);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::BACKGROUND)
                  << "\u2500\u2500\u2500 \u00BFJugar de nuevo? (S/N) \u2500\u2500\u2500";
        std::cout.flush();
        Common::DrawBottomBar();
    }
}
