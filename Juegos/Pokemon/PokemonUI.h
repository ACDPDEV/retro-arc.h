#pragma once

#include <iostream>
#include <array>
#include "../../Common/Color.h"
#include "../../Common/Consts.h"
#include "../../Common/Components/LifeBar.h"
#include "../../Common/Graphics.h"
#include "../../Common/Terminal.h"
#include "../../Common/Aligned.h"
#include "../../Common/Font.h"
#include "../../Common/Sprite.h"
#include "../../Common/Utils.h"
#include "../../Common/Components/BottomBar.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"
#include "PokeballLaunch_Left.h"
#include "PokeballLaunch_Right.h"
#include "Database/SpriteLookup.h"
// PANTALLA: 200 x 50

namespace Pokemon
{
    void ShowPokemonSprites(int playerPokemonId, int opponentPokemonId);
    void PermanentBattleGraphicsView(std::string Pokemon1, std::string Pokemon2, int playerPokemonId, int opponentPokemonId, int hp1, int maxHp1, int hp2, int maxHp2);
    void BattleBeginningTitleView();
    void BattleBeginningAnimationView();
    void BattleOptionsView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, int hp1, int maxHp1, int hp2, int maxHp2);
    void BattleOptionsFightView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, std::string move1, std::string move2, std::string move3, std::string move4, std::string attackType, int hp1, int maxHp1, int hp2, int maxHp2);
    void BattleOptionsFightAttackedView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, std::string attackName, int hp1, int maxHp1, int hp2, int maxHp2);
    void BattleOptionsFightEffectivenessView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, int hp1, int maxHp1, int hp2, int maxHp2);
    void BattleOptionsFightFaintedView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, std::string playerName, int hp1, int maxHp1, int hp2, int maxHp2);

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

        /// @brief Vista permanente de batalla con sprites, info boxes y barras de vida
    /// @param Pokemon1 Nombre del primer Pokemon (jugador)
    /// @param Pokemon2 Nombre del segundo Pokemon (oponente)
    /// @param playerPokemonId ID del Pokemon del jugador en la BD
    /// @param opponentPokemonId ID del Pokemon oponente en la BD
    /// @param hp1 PS actuales del primer Pokemon
    /// @param maxHp1 PS maximos del primer Pokemon
    /// @param hp2 PS actuales del segundo Pokemon
    /// @param maxHp2 PS maximos del segundo Pokemon
    /// @details Limpia la pantalla, dibuja el fondo, los sprites (frame 0),
    ///          las cajas de informacion y las barras de vida.
    void PermanentBattleGraphicsView(std::string Pokemon1, std::string Pokemon2, int playerPokemonId, int opponentPokemonId, int hp1, int maxHp1, int hp2, int maxHp2){
        Common::Clear();
        Common::DrawBackground();

        // Dibujar sprites (frame 0, sin animacion)
        const SpriteSet& playerSprites = GetPokemonSprites(playerPokemonId);
        const SpriteSet& opponentSprites = GetPokemonSprites(opponentPokemonId);
        Common::DrawSprite(PokemonSprite_1X, PokemonSprite_1Y, (*playerSprites.backFrames)[0]);
        Common::DrawSprite(PokemonSprite_2X, PokemonSprite_2Y, (*opponentSprites.frontFrames)[0]);

        // Informacion pokemon y figuras
            // Cajas principales
                // Caja de informacion 1
        Common::PrintPrimaryBox(InformationBox_1X, InformationBox_1Y, BoxWidth - Margin, 2 * BoxHeight - 1, {""}, Common::FOREGROUND_DARK, Common::ORANGE, Common::CREAM);
                // Caja de informacion 2
        Common::PrintPrimaryBox(InformationBox_2X, InformationBox_2Y, BoxWidth - Margin, 2 * BoxHeight - 1, {""}, Common::FOREGROUND_DARK, Common::ORANGE, Common::CREAM);

            // Cajas de vidas
                // Caja de vida 1
        Common::DrawLifeBar(InformationBox_1X + 2 * Margin, InformationBox_1Y + Margin, BoxWidth/2 - 2 * Margin, Common::RED, Common::YELLOW, Common::GRAY);
        Common::DrawLifeBar(InformationBox_1X + 2 * Margin+BoxWidth/2 - 2 * Margin, InformationBox_1Y + Margin, BoxWidth/2 - 3 * Margin, Common::YELLOW, Common::LIGHT_GREEN, Common::GRAY);
                // Caja de vida 2
        Common::DrawLifeBar(InformationBox_2X + 2 * Margin, InformationBox_2Y + Margin, BoxWidth/2 - 2 * Margin, Common::RED, Common::YELLOW, Common::GRAY);
        Common::DrawLifeBar(InformationBox_2X + 2 * Margin+BoxWidth/2 - 2 * Margin, InformationBox_2Y + Margin, BoxWidth/2 - 3 * Margin, Common::YELLOW, Common::LIGHT_GREEN, Common::GRAY);

            // Nombres
        Common::GoToXY(InformationBox_1X + 2 * Margin, InformationBox_1Y + Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << Pokemon1;

        Common::GoToXY(InformationBox_2X + 2 * Margin, InformationBox_2Y + Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << Pokemon2;

            // Vida
        Common::GoToXY(Common::AlignedX(InformationBox_1X + 2 * Margin, BoxWidth - 5 * Margin, LifeWidth, "center"), InformationBox_1Y + 3 * Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << std::to_string(hp1) + "/" + std::to_string(maxHp1);

        Common::GoToXY(Common::AlignedX(InformationBox_2X + 2 * Margin, BoxWidth - 5 * Margin, LifeWidth, "center"), InformationBox_2Y + 3 * Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << std::to_string(hp2) + "/" + std::to_string(maxHp2);
            //Ronda
    }

    void BattleBeginningTitleView(){
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

    // DEMO FUNCTION — hardcoded values for testing. Not used in gameplay.
    void BattleBeginningAnimationView(){
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
        ShowPokemonSprites(1, 4);

        Common::Sleep(300);
        PermanentBattleGraphicsView("PSYDUCK", "ROCKRUFF", 1, 4, 50, 50, 45, 45);
        Common::Sleep(300);
        BattleOptionsView("PSYDUCK", "ROCKRUFF", "PSYDUCK", 1, 4, 50, 50, 45, 45);
        while (true)
        {
            ShowPokemonSprites(1, 4);
        }
    }


    /// @brief Vista de opciones de batalla principal
    /// @param Pokemon1 Nombre del primer Pokemon
    /// @param Pokemon2 Nombre del segundo Pokemon
    /// @param CurrentPokemon Nombre del Pokemon actual
    /// @param playerPokemonId ID del Pokemon del jugador en la BD
    /// @param opponentPokemonId ID del Pokemon oponente en la BD
    /// @param hp1 PS actuales del primer Pokemon
    /// @param maxHp1 PS maximos del primer Pokemon
    /// @param hp2 PS actuales del segundo Pokemon
    /// @param maxHp2 PS maximos del segundo Pokemon
    void BattleOptionsView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, int hp1, int maxHp1, int hp2, int maxHp2)
    {
        PermanentBattleGraphicsView(Pokemon1, Pokemon2, playerPokemonId, opponentPokemonId, hp1, maxHp1, hp2, maxHp2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, BoxWidth - Margin, 2 * BoxHeight, {"Que hara", CurrentPokemon + "?"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
        // opciones
        Common::PrintPrimaryBox(2 * Margin + BoxWidth, OptionsY, BoxWidth - 2 * Margin, BoxHeight, {"LUCHAR"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::ORANGE);
        Common::PrintPrimaryBox(2 * Margin + BoxWidth, OptionsY + Margin + BoxHeight, BoxWidth - 2 * Margin, BoxHeight, {"POKEMON"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::LIGHT_BLUE);
        Common::PrintPrimaryBox(Margin + 2 * BoxWidth + 1, OptionsY, BoxWidth - 2 * Margin, BoxHeight, {"MOCHILA"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(Margin + 2 * BoxWidth + 1, OptionsY + Margin + BoxHeight, BoxWidth - 2 * Margin, BoxHeight, {"HUIDA"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::LIGHT_GREEN);

        // Barra inferior
        Common::DrawBottomBar();
    }


    /// @brief BATALLA POKEMON / OPCIONES DE ATAQUE
    /// @param Pokemon1 Nombre del primer Pokemon
    /// @param Pokemon2 Nombre del segundo Pokemon
    /// @param CurrentPokemon Nombre del Pokemon actual que ataca
    /// @param playerPokemonId ID del Pokemon del jugador en la BD
    /// @param opponentPokemonId ID del Pokemon oponente en la BD
    /// @param move1 Nombre del primer movimiento
    /// @param move2 Nombre del segundo movimiento
    /// @param move3 Nombre del tercer movimiento
    /// @param move4 Nombre del cuarto movimiento
    /// @param attackType Tipo de ataque del Pokemon actual
    /// @param hp1 PS actuales del primer Pokemon
    /// @param maxHp1 PS maximos del primer Pokemon
    /// @param hp2 PS actuales del segundo Pokemon
    /// @param maxHp2 PS maximos del segundo Pokemon
    void BattleOptionsFightView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, std::string move1, std::string move2, std::string move3, std::string move4, std::string attackType, int hp1, int maxHp1, int hp2, int maxHp2){
        PermanentBattleGraphicsView(Pokemon1, Pokemon2, playerPokemonId, opponentPokemonId, hp1, maxHp1, hp2, maxHp2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, BoxWidth - Margin, 2 * BoxHeight, {"Ataque tipo", attackType}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);

        // Ataques
        Common::PrintPrimaryBox(2 * Margin + BoxWidth, OptionsY, BoxWidth - 2 * Margin, BoxHeight, {move1}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(2 * Margin + BoxWidth, OptionsY + Margin + BoxHeight, BoxWidth - 2 * Margin, BoxHeight, {move2}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(Margin + 2 * BoxWidth + 1, OptionsY, BoxWidth - 2 * Margin, BoxHeight, {move3}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(Margin + 2 * BoxWidth + 1, OptionsY + Margin + BoxHeight, BoxWidth - 2 * Margin, BoxHeight, {move4}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);

        // Barra inferior
        Common::DrawBottomBar();
    }


    /// @brief Vista de ataque realizado
    /// @param Pokemon1 Nombre del Pokemon que ataca
    /// @param Pokemon2 Nombre del Pokemon que recibe el ataque
    /// @param CurrentPokemon Nombre del Pokemon actual
    /// @param playerPokemonId ID del Pokemon del jugador en la BD
    /// @param opponentPokemonId ID del Pokemon oponente en la BD
    /// @param attackName Nombre del ataque utilizado
    /// @param hp1 PS actuales del primer Pokemon
    /// @param maxHp1 PS maximos del primer Pokemon
    /// @param hp2 PS actuales del segundo Pokemon
    /// @param maxHp2 PS maximos del segundo Pokemon
    void BattleOptionsFightAttackedView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, std::string attackName, int hp1, int maxHp1, int hp2, int maxHp2){
        PermanentBattleGraphicsView(Pokemon1, Pokemon2, playerPokemonId, opponentPokemonId, hp1, maxHp1, hp2, maxHp2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {Pokemon1 + " ha usado " + attackName + "!"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);


        // Barra inferior
        Common::DrawBottomBar();
    }

    /// @brief Vista de efectividad del ataque
    /// @param Pokemon1 Nombre del primer Pokemon
    /// @param Pokemon2 Nombre del segundo Pokemon
    /// @param CurrentPokemon Nombre del Pokemon actual
    /// @param playerPokemonId ID del Pokemon del jugador en la BD
    /// @param opponentPokemonId ID del Pokemon oponente en la BD
    /// @param hp1 PS actuales del primer Pokemon
    /// @param maxHp1 PS maximos del primer Pokemon
    /// @param hp2 PS actuales del segundo Pokemon
    /// @param maxHp2 PS maximos del segundo Pokemon
    void BattleOptionsFightEffectivenessView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, int hp1, int maxHp1, int hp2, int maxHp2){
        PermanentBattleGraphicsView(Pokemon1, Pokemon2, playerPokemonId, opponentPokemonId, hp1, maxHp1, hp2, maxHp2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {"Fue un golpe critico!"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);


        // Barra inferior
        Common::DrawBottomBar();
    }

    /// @brief Vista de Pokemon desmayado
    /// @param Pokemon1 Nombre del Pokemon desmayado
    /// @param Pokemon2 Nombre del otro Pokemon
    /// @param CurrentPokemon Nombre del Pokemon actual
    /// @param playerPokemonId ID del Pokemon del jugador en la BD
    /// @param opponentPokemonId ID del Pokemon oponente en la BD
    /// @param playerName Nombre del jugador dueño del Pokemon desmayado
    /// @param hp1 PS actuales del primer Pokemon
    /// @param maxHp1 PS maximos del primer Pokemon
    /// @param hp2 PS actuales del segundo Pokemon
    /// @param maxHp2 PS maximos del segundo Pokemon
    void BattleOptionsFightFaintedView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon, int playerPokemonId, int opponentPokemonId, std::string playerName, int hp1, int maxHp1, int hp2, int maxHp2){
        PermanentBattleGraphicsView(Pokemon1, Pokemon2, playerPokemonId, opponentPokemonId, hp1, maxHp1, hp2, maxHp2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {"El " + Pokemon1 + " de " + playerName + " se ha desmayado!" }, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);


        // Barra inferior
        Common::DrawBottomBar();
    }

}
