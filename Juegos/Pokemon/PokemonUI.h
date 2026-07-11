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
#include "PokeballLaunchRight.h"
#include "PokeballLaunchLeft.h"
#include "PokemonFigures.h"
// PANTALLA: 200 x 50

namespace Pokemon
{   
    void ShowPokemonSprites();
    void PermanentBattleGraphicsView(std::string Pokemon1, std::string Pokemon2);
    void BattleBeginningTitleView();
    void BattleBeginningAnimationView();
    void BattleOptionsView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon);
    void BattleOptionsFightView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon);
    void BattleOptionsFightAttackedView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon);
    void BattleOptionsFightEffectivenessView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon);

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
    std::string Attack = "Impactrueno", AttackType = "Electrico"; 

    void ShowPokemonSprites(){
        Common::DrawSprite(PokemonSprite_1X, PokemonSprite_1Y, Pokemon::PsyduckBack);
        Common::DrawSprite(PokemonSprite_2X, PokemonSprite_2Y,Pokemon::RockruffFront);
    }

        /// @brief No incluye DrawBackground()
    /// @param Pokemon1 
    /// @param Pokemon2 
    void PermanentBattleGraphicsView(std::string Pokemon1, std::string Pokemon2){
 
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
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << "50/50";

        Common::GoToXY(Common::AlignedX(InformationBox_2X + 2 * Margin, BoxWidth - 5 * Margin, LifeWidth, "center"), InformationBox_2Y + 3 * Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << "50/50";

            //Ronda
    }

    void BattleBeginningTitleView(){
        const std::array<std::string, 9> FightTitle = Common::ConcatFont({Common::FONT_F,Common::FONT_I,Common::FONT_G,Common::FONT_H,Common::FONT_T, Common::FONT_EXCLAMATION}, 2);
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
    
    void BattleBeginningAnimationView(){
        Common::EnableUTF8();
        Common::Clear();
        Common::DrawBackground();
        Common::HideCursor();

        // Animacion pokeball lanzada
        for (size_t i = 0; i < 10; i++)
        {
            Common::DrawSprite(PokeballLaunch_1X, PokeballLaunch_1Y, Pokemon::PokeballLaunchRight[i]);
            Common::DrawSprite(PokeballLaunch_2X, PokeballLaunch_2Y, Pokemon::PokeballLaunchLeft[i]);
            Common::Sleep(500);
        }
        Common::Clear();
        Common::DrawBackground();
        Common::Sleep(300);
        ShowPokemonSprites();
       
        PermanentBattleGraphicsView("PSYDUCK", "ROCKRUFF");
        BattleOptionsView("PSYDUCK", "ROCKRUFF", "PSYDUCK");
    }


    void BattleOptionsView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon)
    {   
        PermanentBattleGraphicsView(Pokemon1, Pokemon2);
        
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
    
    
    ///@brief BATALLA POKEMON / OPCIONES
    void BattleOptionsFightView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon){
        PermanentBattleGraphicsView(Pokemon1, Pokemon2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, BoxWidth - Margin, 2 * BoxHeight, {"Ataque tipo", AttackType}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
       
        // Ataques
        Common::PrintPrimaryBox(2 * Margin + BoxWidth, OptionsY, BoxWidth - 2 * Margin, BoxHeight, {"IMPACTRUENO"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(2 * Margin + BoxWidth, OptionsY + Margin + BoxHeight, BoxWidth - 2 * Margin, BoxHeight, {"HIDROBOMBA"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(Margin + 2 * BoxWidth + 1, OptionsY, BoxWidth - 2 * Margin, BoxHeight, {"CABEZAZO ZEN"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(Margin + 2 * BoxWidth + 1, OptionsY + Margin + BoxHeight, BoxWidth - 2 * Margin, BoxHeight, {"ARANYAZO"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);

        // Barra inferior
        Common::DrawBottomBar();
    }


    void BattleOptionsFightAttackedView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon){
        PermanentBattleGraphicsView(Pokemon1, Pokemon2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {Pokemon1 + " ha usado " + Attack + "!"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
       

        // Barra inferior
        Common::DrawBottomBar();
    }

    void BattleOptionsFightEffectivenessView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon){
        PermanentBattleGraphicsView(Pokemon1, Pokemon2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {"Fue un golpe critico!"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
       

        // Barra inferior
        Common::DrawBottomBar();
    }

    void BattleOptionsFightFaintedView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon){
        PermanentBattleGraphicsView(Pokemon1, Pokemon2);
        
        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {"El " + Pokemon1 + " de $USER1 se ha desmayado!" }, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
       

        // Barra inferior
        Common::DrawBottomBar();
    }

}