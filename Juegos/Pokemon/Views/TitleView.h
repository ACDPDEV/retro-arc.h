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

        // Texto (Presione una tecla para empezar) - 4-line font
        const std::array<std::string, 4> promptFont = Common::ConcatFont({
            Common::FONT4_p, Common::FONT4_r, Common::FONT4_e, Common::FONT4_s,
            Common::FONT4_i, Common::FONT4_o, Common::FONT4_n, Common::FONT4_a,
            Common::FONT4_blank,
            Common::FONT4_u, Common::FONT4_n, Common::FONT4_a,
            Common::FONT4_blank,
            Common::FONT4_t, Common::FONT4_e, Common::FONT4_c, Common::FONT4_l, Common::FONT4_a,
            Common::FONT4_blank,
            Common::FONT4_p, Common::FONT4_a, Common::FONT4_r, Common::FONT4_a,
            Common::FONT4_blank,
            Common::FONT4_e, Common::FONT4_m, Common::FONT4_p, Common::FONT4_e, Common::FONT4_z, Common::FONT4_a, Common::FONT4_r
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
