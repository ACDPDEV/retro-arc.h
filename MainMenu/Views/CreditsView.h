#pragma once

#include <string>
#include <vector>

#include "../../Common/Consts.h"
#include "../../Common/Aligned.h"
#include "../../Common/Graphics.h"
#include "../../Common/Font.h"
#include "../../Common/Color.h"
#include "../../Common/Utils.h"
#include "../../Common/Theme.h"
#include "../../Common/Input.h"
#include "../../Common/Sprite.h"
#include "../../Common/Components/BottomBar.h"
#include "../../Common/Variables.h"

namespace MainMenu {
    inline std::vector<std::array<std::string, 4>> StringToFont4(const std::string& str) {
        std::vector<std::array<std::string, 4>> glyphs;
        for (char c : str) {
            if (c >= 'A' && c <= 'Z') c = c + 32;
            switch (c) {
                case 'a': glyphs.push_back(Common::FONT4_a); break;
                case 'b': glyphs.push_back(Common::FONT4_b); break;
                case 'c': glyphs.push_back(Common::FONT4_c); break;
                case 'd': glyphs.push_back(Common::FONT4_d); break;
                case 'e': glyphs.push_back(Common::FONT4_e); break;
                case 'f': glyphs.push_back(Common::FONT4_f); break;
                case 'g': glyphs.push_back(Common::FONT4_g); break;
                case 'h': glyphs.push_back(Common::FONT4_h); break;
                case 'i': glyphs.push_back(Common::FONT4_i); break;
                case 'j': glyphs.push_back(Common::FONT4_j); break;
                case 'k': glyphs.push_back(Common::FONT4_k); break;
                case 'l': glyphs.push_back(Common::FONT4_l); break;
                case 'm': glyphs.push_back(Common::FONT4_m); break;
                case 'n': glyphs.push_back(Common::FONT4_n); break;
                case 'o': glyphs.push_back(Common::FONT4_o); break;
                case 'p': glyphs.push_back(Common::FONT4_p); break;
                case 'q': glyphs.push_back(Common::FONT4_q); break;
                case 'r': glyphs.push_back(Common::FONT4_r); break;
                case 's': glyphs.push_back(Common::FONT4_s); break;
                case 't': glyphs.push_back(Common::FONT4_t); break;
                case 'u': glyphs.push_back(Common::FONT4_u); break;
                case 'v': glyphs.push_back(Common::FONT4_v); break;
                case 'w': glyphs.push_back(Common::FONT4_w); break;
                case 'x': glyphs.push_back(Common::FONT4_x); break;
                case 'y': glyphs.push_back(Common::FONT4_y); break;
                case 'z': glyphs.push_back(Common::FONT4_z); break;
                case ' ': glyphs.push_back(Common::FONT4_blank); break;
                default: glyphs.push_back(Common::FONT4_blank); break;
            }
        }
        return glyphs;
    }

    inline void CreditsView() {
        Common::DrawBackground();

        const std::string title = "CREDITOS";
        std::vector<std::array<int, 3>> titleColor = Common::Gradient(1, {247, 208, 58}, {247, 27, 27});

        Common::DrawText(
            Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title), "center"),
            Common::AlignedY(0, Common::HEIGHT_SCREEN, 1, "center") - 8,
            -1, -1,
            {title},
            {titleColor[0]},
            Common::BACKGROUND
        );

        struct GameCredit {
            std::string game;
            std::vector<std::string> members;
        };

        std::vector<GameCredit> credits = {
            {"Pokemon", {"Diaz Pisfil Ahilton Cesar", "Gamboa Valderrama Renzo Gamboa"}},
            {"Buscaminas", {"Colona Cahuana Anilton Aldair"}},
            {"Invasores Espaciales", {"Vazquez Chavez Yamilet Yasuri"}},
            {"Tic Tac Toe", {"Terrornes Alfaro Alexander", "Calsin Yucra Edinson Victor"}}
        };

        int totalLines = credits.size() * 6;
        int startY = Common::AlignedY(0, Common::HEIGHT_SCREEN, totalLines, "center") - 4;

        for (size_t i = 0; i < credits.size(); i++) {
            auto fontGlyphs = StringToFont4(credits[i].game);
            auto fontArray = Common::ConcatFont(fontGlyphs, 1);
            int fontX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(fontArray[0]), "center");

            for (int line = 0; line < 4; line++) {
                Common::DrawText(
                    fontX, startY + i * 6 + line,
                    -1, -1,
                    {fontArray[line]},
                    Common::ORANGE,
                    Common::BACKGROUND
                );
            }

            for (size_t j = 0; j < credits[i].members.size(); j++) {
                Common::DrawText(
                    Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(credits[i].members[j]), "center"),
                    startY + i * 6 + 4 + j,
                    -1, -1,
                    {credits[i].members[j]},
                    Common::FOREGROUND_LIGHT,
                    Common::BACKGROUND
                );
            }
        }

        Common::keysHelper.clear();
        Common::keysHelper.push_back({"ENTER", "Volver"});
        Common::DrawBottomBar();

        Common::GoToEnd();
        Common::Getch();
        Common::keysHelper.clear();
    }
}
