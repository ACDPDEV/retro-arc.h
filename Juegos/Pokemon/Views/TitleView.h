#pragma once

#include <array>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/SelectComponent.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Sprite.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Utils.h"
#include "../Components/MenuOptions.h"
#include "../PokemonStaticSprites/CharmanderFront.h"
#include "../PokemonStaticSprites/PikachuFront.h"

namespace Pokemon {

    /// @brief Renderiza la pantalla de titulo de Pokemon con logo, sprites y menu de opciones
    /// @return Indice de la opcion seleccionada por el usuario (0=Jugar, 1=Instrucciones, 2=Configuraciones, 3=Volver)
    inline int TitleView() {
        OPTION = 0;

        Common::DrawBackground();

        // Logo "POKEMON" con ConcatFont (FONT9_P-FONT9_N) - 9-line font
        const std::array<std::string, 9> logo = Common::ConcatFont({
            Common::FONT9_P, Common::FONT9_O, Common::FONT9_K,
            Common::FONT9_E, Common::FONT9_M, Common::FONT9_O, Common::FONT9_N
        }, 1);

        // Gradiente: amarillo → rojo para las 9 lineas del logo
        const std::vector<std::array<int, 3>> logoGradient = Common::Gradient(
            9, Common::YELLOW, Common::RED
        );

        // Centrar logo horizontalmente
        const int logoX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(logo[0]), "center");

        // Renderizar logo linea por linea con gradiente
        for (int i = 0; i < 9; i++) {
            Common::DrawText(
                logoX, 3 + i, -1, -1,
                {logo[i]}, logoGradient[i], Common::BACKGROUND
            );
        }

        // Sprites: Charmander a la izquierda, Pikachu a la derecha
        Common::DrawSprite(35, 14, CharmanderFront);
        Common::DrawSprite(125, 14, PikachuFront);

        // Menu de opciones con selector
        const int selectWidth = Common::Length(Common::MaxString(OPTIONS)) + 16;
        const int selectHeight = OPTIONS.size();
        const int selectX = Common::AlignedX(0, Common::WIDTH_SCREEN, selectWidth, "center");
        const int selectY = Common::AlignedY(0, Common::HEIGHT_SCREEN, selectHeight, "center");

        Common::SelectComponent(
            selectX, selectY,
            Common::SELECTION_BACKGROUND, Common::ACCENT,
            OPTIONS, OPTION,
            {" [>>>]  ", "        "},
            {1, 1}, 1
        );

        // Barra inferior
        Common::DrawBottomBar();

        Common::GoToEnd();

        return OPTION;
    }

} // namespace Pokemon
