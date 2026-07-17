#pragma once

#include <array>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Sprite.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Utils.h"
#include "../PokemonStaticSprites/CharmanderFront.h"
#include "../PokemonStaticSprites/PikachuFront.h"

namespace Pokemon {

    /// @brief Renderiza la pantalla de titulo de Pokemon: logo, sprites y texto de prompt
    /// @details Vista puramente visual — el llamador maneja el input despues de que retorne
    inline void TitleView() {
        Common::DrawBackground();

        // Logo "POKEMON" con ConcatFont (FONT_P-FONT_N) - 9-line font
        const std::array<std::string, 9> logo = Common::ConcatFont({
            Common::FONT_P, Common::FONT_O, Common::FONT_K,
            Common::FONT_E, Common::FONT_M, Common::FONT_O, Common::FONT_N
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

        // Texto (Presione una tecla para empezar) - 4-line font
        const std::array<std::string, 4> promptFont = Common::ConcatFont({
            Common::FONT_p, Common::FONT_r, Common::FONT_e, Common::FONT_s,
            Common::FONT_i, Common::FONT_o, Common::FONT_n, Common::FONT_a,
            Common::FONT_blank,
            Common::FONT_u, Common::FONT_n, Common::FONT_a,
            Common::FONT_blank,
            Common::FONT_t, Common::FONT_e, Common::FONT_c, Common::FONT_l, Common::FONT_a,
            Common::FONT_blank,
            Common::FONT_p, Common::FONT_a, Common::FONT_r, Common::FONT_a,
            Common::FONT_blank,
            Common::FONT_e, Common::FONT_m, Common::FONT_p, Common::FONT_e, Common::FONT_z, Common::FONT_a, Common::FONT_r
        }, 1);

        const int promptX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(promptFont[0]), "center");
        Common::DrawText(
            promptX, 36, -1, -1,
            {promptFont[0], promptFont[1], promptFont[2], promptFont[3]},
            Common::FOREGROUND_LIGHT, Common::BACKGROUND
        );

        // Barra inferior
        Common::DrawBottomBar();

        Common::GoToEnd();
    }

} // namespace Pokemon
