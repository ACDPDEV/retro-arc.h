#pragma once

#include <iostream>
#include <array>
#include "../../Common/Consts.h"
#include "../../Common/Graphics.h"
#include "../../Common/Terminal.h"
#include "../../Common/Aligned.h"
#include "../../Common/Font.h"
#include "../../Common/Sprite.h"
#include "../../Common/Utils.h"
#include "../../Common/Theme.h"
#include "PokeballLaunch_Left.h"
#include "PokeballLaunch_Right.h"
#include "Database/SpriteLookup.h"
#include "Sound/PokemonSound.h"
// PANTALLA: 200 x 50

namespace Pokemon
{
    void ShowPokemonSprites(int playerPokemonId, int opponentPokemonId);
    void BattleBeginningTitleView();
    void BattleIntroTransitionView(int playerActivePokemonId, int opponentActivePokemonId);

    const int Margin = 2, OptionsY = 38, BoxHeight = 3, BoxWidth = Common::WIDTH_SCREEN / 3, LifeWidth = 5,
              PokemonSpritewidth = 40, PokemonSpriteHeight = 20,
              InformationBox_1X = 3 * Margin + Common::WIDTH_SCREEN / 6 + PokemonSpritewidth/2,
              InformationBox_2X = -3 * Margin + Common::WIDTH_SCREEN / 2 - PokemonSpritewidth/2,
              InformationBox_1Y = OptionsY - Margin - PokemonSpriteHeight,
              InformationBox_2Y = Margin,
              PokemonSprite_1X = Common::WIDTH_SCREEN/3 - 3*PokemonSpritewidth/2 + 3*Margin,
              PokemonSprite_1Y = InformationBox_1Y,
              PokemonSprite_2X = 5*Common::WIDTH_SCREEN/6-PokemonSpritewidth/2,
              PokemonSprite_2Y = InformationBox_2Y,
              PokeballLaunch_1X = PokemonSprite_1X, PokeballLaunch_1Y = PokemonSprite_1Y,
              PokeballLaunch_2X = InformationBox_2X+BoxWidth + 5*Margin, PokeballLaunch_2Y = Margin;


    /// @brief Muestra la animacion de sprites de los Pokemon en batalla
    /// @param playerPokemonId ID del Pokemon del jugador en la BD (back sprite)
    /// @param opponentPokemonId ID del Pokemon oponente en la BD (front sprite)
    /// @details Recorre los 10 frames de animacion con 150ms de delay entre cada uno.
    ///          Usa SpriteLookup.h para obtener los sprites correctos por DB ID.
    void ShowPokemonSprites(int playerPokemonId, int opponentPokemonId){
        const SpriteSet& playerSprites = GetPokemonSprites(playerPokemonId);
        const SpriteSet& opponentSprites = GetPokemonSprites(opponentPokemonId);

        for (size_t i = 0; i < 10; i++)
        {
            Common::DrawSprite(PokemonSprite_1X, PokemonSprite_1Y, (*playerSprites.backFrames)[i]);
            Common::DrawSprite(PokemonSprite_2X, PokemonSprite_2Y, (*opponentSprites.frontFrames)[i]);
            if (i == 9){ continue; }
            Common::Sleep(150);
        }

    }

    void BattleBeginningTitleView(){
        PlayBattleBeginningSound();

        const std::array<std::string, 9> FightTitle = Common::ConcatFont({Common::FONT9_F,Common::FONT9_I,Common::FONT9_G,Common::FONT9_H,Common::FONT9_T, Common::FONT9_EXCLAMATION}, 2);
        std::vector<std::array<int, 3>> FightTitleColor = Common::Gradient(9, Common::DARK_RED, Common::YELLOW);

        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();
        for (int k = 0; k < 100; k++) {
            for (int i = 0; i < FightTitle.size(); i++) {
                Common::DrawText(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(FightTitle[i]), "center"), Common::AlignedY(0, Common::HEIGHT_SCREEN, 9, "center") + i, -1, -1, {FightTitle[i]}, {Common::BACKGROUND[0] + (FightTitleColor[i][0] - Common::BACKGROUND[0]) * k / 100, Common::BACKGROUND[1] + (FightTitleColor[i][1] - Common::BACKGROUND[1]) * k / 100, Common::BACKGROUND[2] + (FightTitleColor[i][2] - Common::BACKGROUND[2]) * k / 100}, Common::BACKGROUND);
             /*    Common::GoToXY(0, Common::HEIGHT_SCREEN + 1); */
            }
            std::cout.flush();
            Common::Sleep(400 / (k + 1));
        }
            Common::Sleep(400);
        for (int k = 100; k > 0; k--) {
            for (int i = 0; i < FightTitle.size(); i++) {
                Common::DrawText(Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(FightTitle[i]), "center"), Common::AlignedY(0, Common::HEIGHT_SCREEN, 9, "center") + i, -1, -1, {FightTitle[i]}, {Common::BACKGROUND[0] + (FightTitleColor[i][0] - Common::BACKGROUND[0]) * k / 100, Common::BACKGROUND[1] + (FightTitleColor[i][1] - Common::BACKGROUND[1]) * k / 100, Common::BACKGROUND[2] + (FightTitleColor[i][2] - Common::BACKGROUND[2]) * k / 100}, Common::BACKGROUND);
                /* Common::GoToXY(0, Common::HEIGHT_SCREEN + 1); */
            }
            std::cout.flush();
            Common::Sleep(400 / (k + 1));
        }
    }

    /// @brief Transicion de una sola pasada entre el titulo "FIGHT!" y la pantalla de batalla
    /// @param playerActivePokemonId ID (BD) del Pokemon activo del jugador
    /// @param opponentActivePokemonId ID (BD) del Pokemon activo del oponente
    /// @details Lanzamiento de pokebola (23 frames) -> aparicion de los Pokemon reales
    ///          (ShowPokemonSprites) -> retorna. No dibuja la pantalla de batalla final;
    ///          eso es responsabilidad de BattleViews::DrawBattleBackground (evita el
    ///          include circular PokemonUI.h <-> BattleViews.h). No hace `while(true)`.
    void BattleIntroTransitionView(int playerActivePokemonId, int opponentActivePokemonId){
        Common::EnableUTF8();
        Common::DrawBackground();
        Common::HideCursor();

        // Animacion pokeball lanzada
        for (size_t i = 0; i < 23; i++)
        {
            Common::DrawSprite(PokeballLaunch_1X-6*Margin, PokeballLaunch_1Y, Pokemon::PokeballLaunch_Left_ALL[i]);
            Common::DrawSprite(PokeballLaunch_2X-8*Margin, PokeballLaunch_2Y, Pokemon::PokeballLaunch_Right_ALL[i]);
            if (i == 22){ continue; }
            Common::Sleep(100);
        }

        Common::Clear();
        Common::DrawBackground();
        ShowPokemonSprites(playerActivePokemonId, opponentActivePokemonId);
    }

}
