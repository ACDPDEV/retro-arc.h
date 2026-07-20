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
#include "../Database/State.h"
#include "../PokemonAnimatedSprites/BulbasaurFront.h"
#include "../PokemonAnimatedSprites/CharmanderFront.h"
#include "../PokemonAnimatedSprites/SquirtleFront.h"
#include "../PokemonAnimatedSprites/PikachuFront.h"
#include "../PokemonAnimatedSprites/PsyduckFront.h"
#include "../PokemonAnimatedSprites/EeveeFront.h"
#include "../PokemonAnimatedSprites/RockruffFront.h"
#include "../PokemonAnimatedSprites/ChikoritaFront.h"

namespace Pokemon {

    /// @brief Pantalla de animacion de huida con sprite dinamico desplazandose de izquierda a derecha
    /// @details Muestra un sprite animado del Pokemon que huye, un cuadro de mensaje con FONT4,
    ///          y el contador de rondas. La animacion completa antes de retornar.
    ///          Lee los valores de los globals: currentPokemonName, playerNames[currentSelectionPlayer], currentRound.
    inline void HuidaView() {
        Common::DrawBackground();

        // Array de sprites animados de Pokemon (ordenado por spriteIndex)
        const std::vector<std::vector<std::string>>* pokemonAnimated[] = {
            &BulbasaurFront_ALL, &CharmanderFront_ALL, &SquirtleFront_ALL,
            &PikachuFront_ALL, &PsyduckFront_ALL, &EeveeFront_ALL,
            &RockruffFront_ALL, &ChikoritaFront_ALL
        };

        // Leer indice del Pokemon actual desde el estado
        int pokemonIdx = selectedCurrentPokemonId[currentSelectionPlayer];
        const auto& frames = *pokemonAnimated[pokemonIdx];
        int frameCount = frames.size();

        // Contador de rondas (posicion x=150, y=2)
        std::string roundText = "Rondas jugadas: " + std::to_string(currentRound);
        Common::DrawText(150, 2, -1, -1, {roundText}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // Barra inferior
        Common::DrawBottomBar();

        Common::GoToEnd();

        // Cuadro inferior con mensaje en FONT4 (arriba de DrawBottomBar, y ≈ 44)
        std::string msg = "EL " + currentPokemonName + " DE " + playerNames[currentSelectionPlayer] + " HA HUIDO";
        auto glyphs = Common::Font4String(msg);
        auto line = Common::ConcatFont(glyphs, 1);
        // Convertir array<string,4> a vector<string> para PrintPrimaryBox
        std::vector<std::string> lineVec(line.begin(), line.end());
        Common::PrintPrimaryBox(20, 44, 160, 6, lineVec,
            Common::FOREGROUND_LIGHT, Common::GRAY, Common::SELECTION_BACKGROUND);

        // Animacion de sprite desplazandose de izquierda a derecha
        const int startX = 0;
        const int endX = 160;
        const int step = 8;
        const int spriteY = 28;
        const int frameDelay = 80; // ms por frame

        for (int x = startX; x <= endX; x += step) {
            // Determinar frame actual (ciclico)
            int frameIndex = (x / step) % frameCount;

            // Limpiar posicion anterior (redibujar fondo)
            if (x > startX) {
                int prevX = x - step;
                // Redibujar fondo en la posicion anterior del sprite
                // Usar dimensiones dinamicas del sprite
                int spriteWidth = Common::Length(frames[0][0]);
                Common::DrawFillRectangle(
                    prevX, spriteY, spriteWidth, frames[0].size(),
                    Common::EMPTY_BLOCK,
                    Common::FOREGROUND_LIGHT, Common::BACKGROUND
                );
            }

            // Dibujar sprite en posicion actual
            Common::DrawSprite(x, spriteY, frames[frameIndex]);

            Common::Sleep(frameDelay);
        }

        // Pausa al final de la animacion
        Common::Sleep(500);
    }

} // namespace Pokemon
