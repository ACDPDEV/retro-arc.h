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
#include "../../Common/Utils.h"
#include "../../Common/Components/BottomBar.h"
#include "../../Common/Theme.h"
#include "../../Common/UnicodeGlyphs.h"

// PANTALLA: 200 x 50

namespace Pokemon
{
    const int Margin = 2, OptionsY = 38, BoxHeight = 3, LifeWidth = 5;
    int InformationBox_1Y = OptionsY - 3 * BoxHeight,
        InformationBox_2Y = Margin, BoxWitdh = Common::WIDTH_SCREEN / 3;
    std::string Attack = "Impactrueno", AttackType = "Electrico"; 

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
    
    void PermanentBattleGraphicsView(int SpriteWidth, std::string Pokemon1, std::string Pokemon2){
        int InformationBox_1X = 3 * Margin + Common::WIDTH_SCREEN / 6 + SpriteWidth / 2,
            InformationBox_2X = -3 * Margin + Common::WIDTH_SCREEN / 2 - SpriteWidth / 2;
        Common::DrawBackground();

        // Informacion pokemon y figuras
            // Cajas principales
                // Caja de informacion 1
        Common::PrintPrimaryBox(InformationBox_1X, InformationBox_1Y, BoxWitdh - Margin, 2 * BoxHeight - 1, {""}, Common::FOREGROUND_DARK, Common::ORANGE, Common::CREAM);
                // Caja de informacion 2
        Common::PrintPrimaryBox(InformationBox_2X, InformationBox_2Y, BoxWitdh - Margin, 2 * BoxHeight - 1, {""}, Common::FOREGROUND_DARK, Common::ORANGE, Common::CREAM);

            // Cajas de vidas
                // Caja de vida 1
        Common::DrawLifeBar(InformationBox_1X + 2 * Margin, InformationBox_1Y + Margin, BoxWitdh/2 - 2 * Margin, Common::RED, Common::YELLOW, Common::GRAY);
        Common::DrawLifeBar(InformationBox_1X + 2 * Margin+BoxWitdh/2 - 2 * Margin, InformationBox_1Y + Margin, BoxWitdh/2 - 3 * Margin, Common::YELLOW, Common::LIGHT_GREEN, Common::GRAY);
                // Caja de vida 2
        Common::DrawLifeBar(InformationBox_2X + 2 * Margin, InformationBox_2Y + Margin, BoxWitdh/2 - 2 * Margin, Common::RED, Common::YELLOW, Common::GRAY);
        Common::DrawLifeBar(InformationBox_2X + 2 * Margin+BoxWitdh/2 - 2 * Margin, InformationBox_2Y + Margin, BoxWitdh/2 - 3 * Margin, Common::YELLOW, Common::LIGHT_GREEN, Common::GRAY);

            // Nombres
        Common::GoToXY(InformationBox_1X + 2 * Margin, InformationBox_1Y + Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << Pokemon1;

        Common::GoToXY(InformationBox_2X + 2 * Margin, InformationBox_2Y + Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << Pokemon2;

            // Vida
        Common::GoToXY(Common::AlignedX(InformationBox_1X + 2 * Margin, BoxWitdh - 5 * Margin, LifeWidth, "center"), InformationBox_1Y + 3 * Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << "50/50";

        Common::GoToXY(Common::AlignedX(InformationBox_2X + 2 * Margin, BoxWitdh - 5 * Margin, LifeWidth, "center"), InformationBox_2Y + 3 * Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << "50/50";

            //Ronda
    }

    void BattleOptionsView(int SpriteWidth, std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon)
    {   
        int InformationBox_1X = 3 * Margin + Common::WIDTH_SCREEN / 6 + SpriteWidth / 2,
        InformationBox_2X = -3 * Margin + Common::WIDTH_SCREEN / 2 - SpriteWidth / 2;
        PermanentBattleGraphicsView(SpriteWidth, Pokemon1, Pokemon2);
        
        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, BoxWitdh - Margin, 2 * BoxHeight, {"Que hara", CurrentPokemon + "?"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
        // opciones
        Common::PrintPrimaryBox(2 * Margin + BoxWitdh, OptionsY, BoxWitdh - 2 * Margin, BoxHeight, {"LUCHAR"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::ORANGE);
        Common::PrintPrimaryBox(2 * Margin + BoxWitdh, OptionsY + Margin + BoxHeight, BoxWitdh - 2 * Margin, BoxHeight, {"POKEMON"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::LIGHT_BLUE);
        Common::PrintPrimaryBox(Margin + 2 * BoxWitdh + 1, OptionsY, BoxWitdh - 2 * Margin, BoxHeight, {"MOCHILA"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(Margin + 2 * BoxWitdh + 1, OptionsY + Margin + BoxHeight, BoxWitdh - 2 * Margin, BoxHeight, {"HUIDA"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::LIGHT_GREEN);
        
        // Barra inferior
        Common::DrawBottomBar();
    }
    
    
    ///@brief BATALLA POKEMON / OPCIONES
    void BattleOptionsFightView(int SpriteWidth, std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon){
        int InformationBox_1X = 3 * Margin + Common::WIDTH_SCREEN / 6 + SpriteWidth / 2,
            InformationBox_2X = -3 * Margin + Common::WIDTH_SCREEN / 2 - SpriteWidth / 2;
        PermanentBattleGraphicsView(SpriteWidth, Pokemon1, Pokemon2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, BoxWitdh - Margin, 2 * BoxHeight, {"Ataque tipo", AttackType}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
       
        // Ataques
        Common::PrintPrimaryBox(2 * Margin + BoxWitdh, OptionsY, BoxWitdh - 2 * Margin, BoxHeight, {"IMPACTRUENO"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(2 * Margin + BoxWitdh, OptionsY + Margin + BoxHeight, BoxWitdh - 2 * Margin, BoxHeight, {"HIDROBOMBA"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(Margin + 2 * BoxWitdh + 1, OptionsY, BoxWitdh - 2 * Margin, BoxHeight, {"CABEZAZO ZEN"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);
        Common::PrintPrimaryBox(Margin + 2 * BoxWitdh + 1, OptionsY + Margin + BoxHeight, BoxWitdh - 2 * Margin, BoxHeight, {"ARANYAZO"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::GRAY);

        // Barra inferior
        Common::DrawBottomBar();
    }


    void BattleOptionsFightAttackedView(int SpriteWidth, std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon){
        int InformationBox_1X = 3 * Margin + Common::WIDTH_SCREEN / 6 + SpriteWidth / 2,
            InformationBox_2X = -3 * Margin + Common::WIDTH_SCREEN / 2 - SpriteWidth / 2;
        PermanentBattleGraphicsView(SpriteWidth, Pokemon1, Pokemon2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {Pokemon1 + " ha usado " + Attack + "!"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
       

        // Barra inferior
        Common::DrawBottomBar();
    }

    void BattleOptionsFightEffectivenessView(int SpriteWidth, std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon){
        int InformationBox_1X = 3 * Margin + Common::WIDTH_SCREEN / 6 + SpriteWidth / 2,
            InformationBox_2X = -3 * Margin + Common::WIDTH_SCREEN / 2 - SpriteWidth / 2;
        PermanentBattleGraphicsView(SpriteWidth, Pokemon1, Pokemon2);

        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {"Fue un golpe critico!"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
       

        // Barra inferior
        Common::DrawBottomBar();
    }

    void BattleOptionsFightFaintedView(int SpriteWidth, std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon){
        int InformationBox_1X = 3 * Margin + Common::WIDTH_SCREEN / 6 + SpriteWidth / 2,
            InformationBox_2X = -3 * Margin + Common::WIDTH_SCREEN / 2 - SpriteWidth / 2;
        PermanentBattleGraphicsView(SpriteWidth, Pokemon1, Pokemon2);
        
        // Comentarios
        Common::PrintPrimaryBox(Margin, OptionsY + 1, Common::WIDTH_SCREEN-2*Margin, 2 * BoxHeight, {"El " + Pokemon1 + " de $USER1 se ha desmayado!" }, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
       

        // Barra inferior
        Common::DrawBottomBar();
    }

}