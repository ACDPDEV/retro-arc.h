#pragma once

#include <array>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/LifeBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Sprite.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/UnicodeGlyphs.h"
#include "../../../Common/Utils.h"
#include "../Database/MockData.h"
#include "../Database/State.h"
#include "../PokemonMiniSprites/BulbasaurMini.h"
#include "../PokemonMiniSprites/CharmanderMini.h"
#include "../PokemonMiniSprites/ChikoritaMini.h"
#include "../PokemonMiniSprites/EeveeMini.h"
#include "../PokemonMiniSprites/PikachuMini.h"
#include "../PokemonMiniSprites/PsyduckMini.h"
#include "../PokemonMiniSprites/RockruffMini.h"
#include "../PokemonMiniSprites/SquirtleMini.h"

namespace Pokemon {

    /// @brief Pantalla de seleccion de Pokemon con cuadricula 2x2 y paginacion
    /// @details Muestra 4 Pokemon por pagina en una cuadricula interactiva. El usuario navega con flechas y confirma con ENTER.
    ///          LEFT/RIGHT en los bordes cambia de pagina. La seleccion se persiste en Pokemon::selectedCurrentPokemonId[currentSelectionPlayer] via State.h
    inline void PokemonSelectionView() {
        Common::DrawBackground();
        int selectedPokemon = Pokemon::selectedCurrentPokemonId[Pokemon::currentSelectionPlayer];

        // Titulo "SELECCIONA" con FONT4 (4-line font, lowercase glyphs)
        const std::array<std::string, 4> title = Common::ConcatFont({
            Common::FONT4_s, Common::FONT4_e, Common::FONT4_l, Common::FONT4_e,
            Common::FONT4_c, Common::FONT4_c, Common::FONT4_i, Common::FONT4_o,
            Common::FONT4_n, Common::FONT4_a
        }, 1);

        // Centrar titulo horizontalmente
        const int titleX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[0]), "center");

        // Renderizar titulo linea por linea con color naranja
        for (int i = 0; i < 4; i++) {
            Common::DrawText(
                titleX, 2 + i, -1, -1,
                {title[i]}, Common::ORANGE, Common::BACKGROUND
            );
        }

        // Configuracion de la cuadricula 2x2
        const int gridY = 16;
        const int cellHeight = 10;
        const int cols = 2;
        const int rows = 2;
        const int cellGapX = 4;
        const int cellGapY = 2;
        const int perPage = cols * rows; // 4 Pokemon por pagina
        const int totalPages = (POKEMON_COUNT + perPage - 1) / perPage; // 2 paginas
        int page = selectedPokemon / perPage;

        // cellWidth se calcula dinamicamente segun el nombre mas ancho de la pagina
        int cellWidth = 55;

        // Array de mini sprites de Pokemon (ordenado por spriteIndex)
        const std::vector<std::string>* pokemonMiniSprites[] = {
            &BulbasaurMini, &CharmanderMini, &SquirtleMini, &PikachuMini,
            &PsyduckMini, &EeveeMini, &RockruffMini, &ChikoritaMini
        };

        // Funcion para obtener el indice global de un Pokemon en la pagina actual
        auto getPageIndex = [&](int col, int row) -> int {
            return page * perPage + row * cols + col;
        };

        // Calcular ancho de celda adaptativo segun el nombre mas ancho de la pagina
        auto computeCellWidth = [&]() -> int {
            int maxWidth = 0;
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    int idx = getPageIndex(col, row);
                    if (idx >= POKEMON_COUNT) continue;
                    std::vector<std::array<std::string, 4>> glyphs = Common::Font4String(MOCK_POKEMON[idx].name);
                    std::array<std::string, 4> assembled = Common::ConcatFont(glyphs, 1);
                    int w = Common::Length(assembled[0]);
                    if (w > maxWidth) maxWidth = w;
                }
            }
            // Ancho = nombre + area de sprite (16) + margen minimo
            int computed = maxWidth + 24;
            if (computed < 55) computed = 55;
            return computed;
        };

        // Dibujar celda de Pokemon
        auto drawCell = [&](int col, int row, int index, bool isSelected, int gridX) {
            if (index >= POKEMON_COUNT) return;

            const int cellX = gridX + col * (cellWidth + cellGapX);
            const int cellY = gridY + row * (cellHeight + cellGapY);

            // Borde de celda: naranja si esta seleccionada, gris si no
            std::array<int, 3> borderColor = isSelected ? Common::ORANGE : Common::GRAY;

            // Celda con PrintPrimaryBox
            Common::PrintPrimaryBox(
                cellX, cellY, cellWidth, cellHeight,
                {},
                Common::COLOR_DEFAULT,
                borderColor,
                Common::SELECTION_BACKGROUND
            );

            // Nombre de Pokemon con FONT4 (separator=1 para interletrado)
            std::vector<std::array<std::string, 4>> nameGlyphs = Common::Font4String(MOCK_POKEMON[index].name);
            std::array<std::string, 4> fontName = Common::ConcatFont(nameGlyphs, 1);
            int nameWidth = Common::Length(fontName[0]);

            // Alinear nombre a la izquierda con padding fijo
            int nameOffsetX = 3;
            for (int i = 0; i < 4; i++) {
                Common::DrawText(cellX + nameOffsetX, cellY + 1 + i, -1, -1,
                    {fontName[i]}, Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);
            }

            // Sprite de Pokemon alineado a la derecha, centrado verticalmente
            Common::DrawSprite(cellX + cellWidth - 18, cellY + (cellHeight - 7) / 2, *pokemonMiniSprites[index]);

            // Barra de vida y texto HP
            int hp = MOCK_POKEMON[index].hp;
            int maxHp = MOCK_POKEMON[index].maxHp;
            float hpRatio = static_cast<float>(hp) / static_cast<float>(maxHp);

            // Colores de barra: rojo -> amarillo -> verde claro
            std::array<int, 3> barStart, barEnd;
            if (hpRatio > 0.5f) {
                barStart = Common::YELLOW;
                barEnd = Common::LIGHT_GREEN;
            } else if (hpRatio > 0.2f) {
                barStart = Common::RED;
                barEnd = Common::YELLOW;
            } else {
                barStart = Common::DARK_RED;
                barEnd = Common::RED;
            }

            // Texto HP para calcular ancho total
            std::string hpText = std::to_string(hp) + "/" + std::to_string(maxHp) + " HP";
            int hpTextWidth = Common::Length(hpText);
            int barWidth = 18;
            int hpTotalWidth = barWidth + 1 + hpTextWidth;

            // Alinear barra + texto a la izquierda con padding fijo
            int hpOffsetX = 3;
            Common::DrawLifeBar(cellX + hpOffsetX, cellY + 6, barWidth, barStart, barEnd, Common::SELECTION_BACKGROUND);
            Common::DrawText(cellX + hpOffsetX + barWidth + 1, cellY + 6, -1, -1,
                {hpText}, Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);
        };

        // Funcion para redibujar toda la pantalla
        auto redrawAll = [&]() {
            Common::DrawBackground();

            // Titulo
            for (int i = 0; i < 4; i++) {
                Common::DrawText(
                    titleX, 2 + i, -1, -1,
                    {title[i]}, Common::ORANGE, Common::BACKGROUND
                );
            }

            // Player name box with FONT4 — adaptive width based on name
            // Convert playerName to FONT4 glyphs first to compute adaptive width
            std::vector<std::array<std::string, 4>> playerNameGlyphs = Common::Font4String(Pokemon::playerNames[Pokemon::currentSelectionPlayer]);
            std::array<std::string, 4> fontPlayerName = Common::ConcatFont(playerNameGlyphs, 1);
            int playerNameWidth = Common::Length(fontPlayerName[0]);

            // Adaptive box width: name + 8 padding (4 each side), minimum 30
            const int namePadding = 8;
            int nameBoxWidth = playerNameWidth + namePadding;
            if (nameBoxWidth < 30) nameBoxWidth = 30;
            const int nameBoxHeight = 6;
            const int nameBoxX = Common::AlignedX(0, Common::WIDTH_SCREEN, nameBoxWidth, "center");
            const int nameBoxY = 8;

            // Draw player name box
            Common::PrintPrimaryBox(
                nameBoxX, nameBoxY, nameBoxWidth, nameBoxHeight,
                {},
                Common::FOREGROUND_DARK,
                Common::ORANGE,
                Common::SELECTION_BACKGROUND
            );

            // Draw name centered in box
            int nameRenderX = Common::AlignedX(nameBoxX, nameBoxWidth, Common::Length(fontPlayerName[0]), "center");
            for (int i = 0; i < 4; i++) {
                Common::DrawText(nameRenderX, nameBoxY + 1 + i, -1, -1,
                    {fontPlayerName[i]}, Common::ORANGE, Common::SELECTION_BACKGROUND);
            }

            // Calcular ancho adaptativo de celda y centrar cuadricula
            cellWidth = computeCellWidth();
            const int totalGridWidth = cols * cellWidth + (cols - 1) * cellGapX;
            const int gridX = (Common::WIDTH_SCREEN - totalGridWidth) / 2;

            // Celdas de Pokemon
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    int index = getPageIndex(col, row);
                    bool isSelected = (index == selectedPokemon);
                    drawCell(col, row, index, isSelected, gridX);
                }
            }

            // Indicador de pagina con FONT4 (FONT_ digitos + slash)
            int pageNum = page + 1;
            std::vector<std::array<std::string, 4>> pageGlyphs;
            if (pageNum >= 10) {
                pageGlyphs.push_back(Common::Font4Digit(pageNum / 10));
            }
            pageGlyphs.push_back(Common::Font4Digit(pageNum % 10));
            pageGlyphs.push_back(Common::FONT4_slash);
            if (totalPages >= 10) {
                pageGlyphs.push_back(Common::Font4Digit(totalPages / 10));
            }
            pageGlyphs.push_back(Common::Font4Digit(totalPages % 10));
            std::array<std::string, 4> pageFont = Common::ConcatFont(pageGlyphs, 1);
            const int pageFontWidth = Common::Length(pageFont[0]);
            const int pageX = (Common::WIDTH_SCREEN - pageFontWidth) / 2;
            const int pageY = 40;
            for (int i = 0; i < 4; i++) {
                Common::DrawText(pageX, pageY + i, -1, -1,
                    {pageFont[i]}, Common::GRAY, Common::BACKGROUND);
            }

            // BottomBar con entradas de navegacion
            Common::keysHelper.clear();
            Common::keysHelper.push_back({"← → ↑ ↓", "Navegar"});
            Common::keysHelper.push_back({"ENTER", "Seleccionar"});
            Common::DrawBottomBar();

            Common::GoToEnd();
        };

        // Dibujar pantalla inicial
        redrawAll();

        // Loop de navegacion
        while (true) {
            Common::key = Common::ReadConsoleChar();

            if (Common::IsKeyArrowTop(Common::key)) {
                // Mover arriba: wrap dentro de la pagina
                int localRow = (selectedPokemon / cols) % rows;
                if (localRow > 0) {
                    selectedPokemon -= cols;
                } else {
                    selectedPokemon += cols; // wrap a fila inferior
                }
            } else if (Common::IsKeyArrowBottom(Common::key)) {
                // Mover abajo: wrap dentro de la pagina
                int localRow = (selectedPokemon / cols) % rows;
                if (localRow < rows - 1) {
                    selectedPokemon += cols;
                } else {
                    selectedPokemon -= cols; // wrap a fila superior
                }
            } else if (Common::IsKeyArrowLeft(Common::key)) {
                int localCol = selectedPokemon % cols;
                if (localCol > 0) {
                    // Mover columna izquierda dentro de la pagina
                    selectedPokemon--;
                } else {
                    // En borde izquierdo: cambiar a pagina anterior, col=0
                    if (page > 0) {
                        page--;
                        selectedPokemon = page * perPage;
                        redrawAll();
                        continue;
                    }
                }
            } else if (Common::IsKeyArrowRight(Common::key)) {
                int localCol = selectedPokemon % cols;
                if (localCol < cols - 1) {
                    // Mover columna derecha dentro de la pagina
                    selectedPokemon++;
                } else {
                    // En borde derecho: cambiar a pagina siguiente, col=0
                    if (page < totalPages - 1) {
                        page++;
                        selectedPokemon = page * perPage;
                        if (selectedPokemon >= POKEMON_COUNT) {
                            selectedPokemon = POKEMON_COUNT - 1;
                        }
                        redrawAll();
                        continue;
                    }
                }
            } else if (Common::IsActionKey(Common::key)) {
                // Confirmar seleccion y persistir
                Pokemon::selectedCurrentPokemonId[Pokemon::currentSelectionPlayer] = selectedPokemon;
                break;
            }

            // Redibujar solo las celdas (optimizado, sin redraw completo)
            cellWidth = computeCellWidth();
            const int totalGridWidth = cols * cellWidth + (cols - 1) * cellGapX;
            const int gridX = (Common::WIDTH_SCREEN - totalGridWidth) / 2;
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    int index = getPageIndex(col, row);
                    bool isSelected = (index == selectedPokemon);
                    drawCell(col, row, index, isSelected, gridX);
                }
            }

            Common::GoToEnd();
        }
    }

} // namespace Pokemon
