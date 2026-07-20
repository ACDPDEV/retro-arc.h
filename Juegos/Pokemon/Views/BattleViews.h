#pragma once

#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Components/SelectPrimaryBox.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Input.h"
#include "../../../Common/Navigation.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Utils.h"
#include "../../../Common/Variables.h"

#include "../Enums/ChooseCommandOption.h"
#include "../Models/Player.h"
#include "../Models/Pokemon.h"
#include "../Models/Move.h"
#include "../Models/Bag.h"
#include "../Models/Item.h"
#include "../PokemonUI.h"
#include "../Sound/PokemonSound.h"
#include "../Sprites/Mochila.h"
#include "../Database/State.h"

namespace Pokemon {

    // ============================================================
    // Helper: PokemonType to display string
    // ============================================================
    inline std::string PokemonTypeToString(PokemonGame::PokemonType type) {
        switch (type) {
            case PokemonGame::PokemonType::ACERO:      return "Acero";
            case PokemonGame::PokemonType::AGUA:       return "Agua";
            case PokemonGame::PokemonType::BICHO:      return "Bicho";
            case PokemonGame::PokemonType::DRAGON:     return "Dragon";
            case PokemonGame::PokemonType::ELECTRICO:  return "Electrico";
            case PokemonGame::PokemonType::FANTASMA:   return "Fantasma";
            case PokemonGame::PokemonType::FUEGO:      return "Fuego";
            case PokemonGame::PokemonType::HADA:       return "Hada";
            case PokemonGame::PokemonType::HIELO:      return "Hielo";
            case PokemonGame::PokemonType::LUCHA:      return "Lucha";
            case PokemonGame::PokemonType::NORMAL:     return "Normal";
            case PokemonGame::PokemonType::PLANTA:     return "Planta";
            case PokemonGame::PokemonType::PSIQUICO:   return "Psiquico";
            case PokemonGame::PokemonType::ROCA:       return "Roca";
            case PokemonGame::PokemonType::SINIESTRO:  return "Siniestro";
            case PokemonGame::PokemonType::TIERRA:     return "Tierra";
            case PokemonGame::PokemonType::VENENO:     return "Veneno";
            case PokemonGame::PokemonType::VOLADOR:    return "Volador";
            default:                                   return "???";
        }
    }

    // ============================================================
    // Helper: Item class name to display string (no RTTI available)
    // ============================================================
    inline std::string GetItemDisplayName(int itemId) {
        switch (itemId) {
            case 1: return "Banda Focus";
            case 2: return "Restos";
            case 3: return "Pocion";
            case 4: return "Super Pocion";
            default: return "Item Desconocido";
        }
    }

    inline std::string GetItemDescription(int itemId) {
        switch (itemId) {
            case 1: return "Protege del desmayo una vez por batalla.";
            case 2: return "Restaura 5% de PS max. al final de cada turno.";
            case 3: return "Restaura 20 PS de un Pokemon.";
            case 4: return "Restaura 50 PS de un Pokemon.";
            default: return "Sin descripcion.";
        }
    }

    // ============================================================
    // Layout constants (matching PokemonUI.h coordinate system)
    // ============================================================
    constexpr int BattleMargin = 2;
    constexpr int BattleBoxWidth = Common::WIDTH_SCREEN / 3;
    constexpr int BattleBoxHeight = 3;

    // Info boxes for pokemon sprites
    constexpr int BattleInfoBox1X = 3 * BattleMargin + Common::WIDTH_SCREEN / 6 + 20;
    constexpr int BattleInfoBox2X = -3 * BattleMargin + Common::WIDTH_SCREEN / 2 - 20;
    constexpr int BattleInfoBox1Y = 28;
    constexpr int BattleInfoBox2Y = BattleMargin;
    constexpr int BattleOptionsY = 38;

    // ============================================================
    // Helper: Calculate offset of first non-empty row in a sprite
    // ============================================================
    inline int GetSpriteContentOffset(const std::vector<std::string>& sprite) {
        for (int i = 0; i < static_cast<int>(sprite.size()); i++) {
            // Check if row has actual content (more than just background color + spaces)
            std::string row = sprite[i];
            // Count non-space, non-escape characters
            bool hasContent = false;
            bool inEscape = false;
            for (char c : row) {
                if (c == '\033') { inEscape = true; continue; }
                if (inEscape) { if (c == 'm') inEscape = false; continue; }
                if (c != ' ') { hasContent = true; break; }
            }
            if (hasContent) return i;
        }
        return 0; // fallback: no offset
    }

    // ============================================================
    // Helper: Draw the permanent battle background (sprites + info)
    // ============================================================
    inline void DrawBattleBackground(PokemonGame::Player& playerOne, PokemonGame::Player& playerTwo, bool flipPerspective = false) {
        Common::Clear();
        Common::DrawBackground();

        // Get active pokemon data
        PokemonGame::Pokemon* poke1 = playerOne.GetActivePokemon();
        PokemonGame::Pokemon* poke2 = playerTwo.GetActivePokemon();
        std::string name1 = poke1 ? poke1->GetName() : "???";
        std::string name2 = poke2 ? poke2->GetName() : "???";
        int dbId1 = ::Pokemon::battleActivePokemonId1;
        int dbId2 = ::Pokemon::battleActivePokemonId2;
        int hp1 = poke1 ? static_cast<int>(poke1->GetCurrentHp()) : 0;
        int maxHp1 = poke1 ? static_cast<int>(poke1->GetMaxHp()) : 0;
        int hp2 = poke2 ? static_cast<int>(poke2->GetCurrentHp()) : 0;
        int maxHp2 = poke2 ? static_cast<int>(poke2->GetMaxHp()) : 0;

        // Flip perspective for player 2's turn
        int leftDbId = flipPerspective ? dbId2 : dbId1;
        int rightDbId = flipPerspective ? dbId1 : dbId2;
        std::string leftName = flipPerspective ? name2 : name1;
        std::string rightName = flipPerspective ? name1 : name2;
        int leftHp = flipPerspective ? hp2 : hp1;
        int leftMaxHp = flipPerspective ? maxHp2 : maxHp1;
        int rightHp = flipPerspective ? hp1 : hp2;
        int rightMaxHp = flipPerspective ? maxHp1 : maxHp2;

        // Draw info boxes FIRST (behind sprites)
        Common::PrintPrimaryBox(InformationBox_1X, InformationBox_1Y, BoxWidth - Margin, 2 * BoxHeight - 1,
            {""}, Common::FOREGROUND_DARK, Common::ORANGE, Common::CREAM);
        Common::PrintPrimaryBox(InformationBox_2X, InformationBox_2Y, BoxWidth - Margin, 2 * BoxHeight - 1,
            {""}, Common::FOREGROUND_DARK, Common::ORANGE, Common::CREAM);

        // Draw life bars (proportional to HP) — full width of info box minus padding
        int barWidth = BoxWidth - 4 * Margin;
        int filled1 = (leftMaxHp > 0) ? static_cast<int>(barWidth * leftHp / leftMaxHp) : 0;
        int filled2 = (rightMaxHp > 0) ? static_cast<int>(barWidth * rightHp / rightMaxHp) : 0;
        // Left life bar
        Common::DrawLifeBar(InformationBox_1X + 2 * Margin, InformationBox_1Y + Margin, filled1, Common::RED, Common::YELLOW, Common::GRAY);
        Common::DrawFillRectangle(InformationBox_1X + 2 * Margin + filled1, InformationBox_1Y + Margin, barWidth - filled1, 1, Common::FULL_BLOCK, Common::GRAY, Common::COLOR_DEFAULT);
        // Right life bar
        Common::DrawLifeBar(InformationBox_2X + 2 * Margin, InformationBox_2Y + Margin, filled2, Common::RED, Common::YELLOW, Common::GRAY);
        Common::DrawFillRectangle(InformationBox_2X + 2 * Margin + filled2, InformationBox_2Y + Margin, barWidth - filled2, 1, Common::FULL_BLOCK, Common::GRAY, Common::COLOR_DEFAULT);

        // Pokemon names
        Common::GoToXY(InformationBox_1X + 2 * Margin, InformationBox_1Y + Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << leftName;

        Common::GoToXY(InformationBox_2X + 2 * Margin, InformationBox_2Y + Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << rightName;

        // HP text
        Common::GoToXY(Common::AlignedX(InformationBox_1X + 2 * Margin, BoxWidth - 5 * Margin, LifeWidth, "center"), InformationBox_1Y + 3 * Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << std::to_string(leftHp) + "/" + std::to_string(leftMaxHp);

        Common::GoToXY(Common::AlignedX(InformationBox_2X + 2 * Margin, BoxWidth - 5 * Margin, LifeWidth, "center"), InformationBox_2Y + 3 * Margin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << std::to_string(rightHp) + "/" + std::to_string(rightMaxHp);

        // Draw sprites LAST (on top of everything) — offset for empty rows at top
        const SpriteSet& leftSprites = GetPokemonSprites(leftDbId);
        const SpriteSet& rightSprites = GetPokemonSprites(rightDbId);
        const auto& leftFrame = (*leftSprites.backFrames)[0];
        const auto& rightFrame = (*rightSprites.frontFrames)[0];
        int leftOffset = GetSpriteContentOffset(leftFrame);
        int rightOffset = GetSpriteContentOffset(rightFrame);
        Common::DrawSprite(PokemonSprite_1X, PokemonSprite_1Y - leftOffset, leftFrame);
        Common::DrawSprite(PokemonSprite_2X, PokemonSprite_2Y - rightOffset, rightFrame);
    }

    // ============================================================
    // Helper: Draw the permanent battle background (single player)
    // ============================================================
    inline void DrawSingleBattleBackground(PokemonGame::Player& player) {
        Common::Clear();
        Common::DrawBackground();

        std::string name = player.GetActivePokemon() ? player.GetActivePokemon()->GetName() : "???";

        // Info box
        Common::PrintPrimaryBox(BattleInfoBox1X, BattleInfoBox1Y, BattleBoxWidth - BattleMargin, 2 * BattleBoxHeight - 1,
            {""}, Common::FOREGROUND_DARK, Common::ORANGE, Common::CREAM);

        // Pokemon name
        Common::GoToXY(BattleInfoBox1X + 2 * BattleMargin, BattleInfoBox1Y + BattleMargin / 2);
        std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << name;

        // HP display
        if (player.GetActivePokemon()) {
            std::string hp = std::to_string(static_cast<int>(player.GetActivePokemon()->GetCurrentHp())) + "/" +
                             std::to_string(static_cast<int>(player.GetActivePokemon()->GetMaxHp()));
            Common::GoToXY(Common::AlignedX(BattleInfoBox1X + 2 * BattleMargin, BattleBoxWidth - 5 * BattleMargin, 10, "center"),
                          BattleInfoBox1Y + 3 * BattleMargin / 2);
            std::cout << Common::Color(Common::FOREGROUND_DARK, Common::COLOR_DEFAULT) << hp;
        }
    }

    // ============================================================
    // Task 2.1: BattleMenuView — Main battle command selection (2x2 grid)
    // ============================================================
    /// @brief Interactive main battle menu — returns chosen command option
    /// @details Displays FIGHT/BAG/SONIDO/RUN options in a 2x2 grid layout.
    ///          Shows the active Pokemon name, sprites, and life bars (via PokemonUI).
    ///          User navigates with arrow keys, confirms with ENTER.
    /// @param playerOne Current player's data (reads active Pokemon name)
    /// @param playerTwo Opponent player's data (reads active Pokemon name)
    /// @return Selected ChooseCommandOption (FIGHT, BAG, SONIDO, or RUN)
    inline PokemonGame::ChooseCommandOption BattleMenuView(PokemonGame::Player& playerOne, PokemonGame::Player& playerTwo, bool flipPerspective = false) {
        // Battle music is started once per battle in Battle::Start(), not per menu draw
        // (see Controllers/Battle.h) — do not call StartBattleMusic() here.

        // Draw battle background with sprites, life bars, and names
        DrawBattleBackground(playerOne, playerTwo, flipPerspective);

        // Get active pokemon name for the prompt
        std::string pokeName = playerOne.GetActivePokemon() ? playerOne.GetActivePokemon()->GetName() : "???";

        // Prompt box: "Turno de {player} — {pokemon}?"
        Common::PrintPrimaryBox(BattleMargin, BattleOptionsY + 1, BattleBoxWidth - BattleMargin, 2 * BattleBoxHeight,
            {"Turno de " + playerOne.GetName(), pokeName + "?"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);

        // Menu options in 2x2 grid: [0]=FIGHT [1]=BAG [2]=SONIDO [3]=RUN
        std::vector<std::string> options = {"LUCHAR", "MOCHILA", "SONIDO", "HUIDA"};
        std::vector<PokemonGame::ChooseCommandOption> commands = {
            PokemonGame::ChooseCommandOption::FIGHT,
            PokemonGame::ChooseCommandOption::BAG,
            PokemonGame::ChooseCommandOption::SONIDO,
            PokemonGame::ChooseCommandOption::RUN
        };

        int selectedOption = 0; // 0-3: 0=LUCHAR, 1=MOCHILA, 2=POKEMON, 3=HUIDA

        // 2x2 grid layout positions
        const int menuX = 2 * BattleMargin + BattleBoxWidth;
        const int menuY = BattleOptionsY;
        const int slotWidth = BattleBoxWidth - 2 * BattleMargin;
        const int slotHeight = BattleBoxHeight;
        const int gapX = BattleMargin;
        const int gapY = BattleMargin;

        // Bottom bar hints
        Common::keysHelper.clear();
        Common::keysHelper.push_back({"↑↓←→", "Navegar"});
        Common::keysHelper.push_back({"ENTER", "Seleccionar"});
        Common::DrawBottomBar();

        while (true) {
            // Draw 2x2 grid
            for (int i = 0; i < 4; i++) {
                int col = i % 2;      // 0, 1, 0, 1
                int row = i / 2;      // 0, 0, 1, 1
                int x = menuX + col * (slotWidth + gapX);
                int y = menuY + row * (slotHeight + gapY);
                std::array<int, 3> bgColor = (i == selectedOption) ? Common::ORANGE : Common::FOREGROUND_DARK;
                std::array<int, 3> txtColor = (i == selectedOption) ? Common::FOREGROUND_DARK : Common::FOREGROUND_LIGHT;
                Common::PrintPrimaryBox(x, y, slotWidth, slotHeight, {options[i]},
                    txtColor, Common::FOREGROUND_DARK, bgColor);
            }

            Common::key = Common::ReadConsoleChar();

            if (Common::IsActionKey(Common::key)) {
                PlayButtonPressSound();
                return commands[selectedOption];
            } else if (Common::IsKeyArrowTop(Common::key)) {
                // Move up: row 1 → row 0
                if (selectedOption >= 2) selectedOption -= 2;
            } else if (Common::IsKeyArrowBottom(Common::key)) {
                // Move down: row 0 → row 1
                if (selectedOption < 2) selectedOption += 2;
            } else if (Common::IsKeyArrowLeft(Common::key)) {
                // Move left: col 1 → col 0
                if (selectedOption % 2 == 1) selectedOption -= 1;
            } else if (Common::IsKeyArrowRight(Common::key)) {
                // Move right: col 0 → col 1
                if (selectedOption % 2 == 0 && selectedOption < 3) selectedOption += 1;
            }

            // Redraw prompt
            Common::PrintPrimaryBox(BattleMargin, BattleOptionsY + 1, BattleBoxWidth - BattleMargin, 2 * BattleBoxHeight,
                {"Turno de " + playerOne.GetName(), pokeName + "?"}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);

            Common::DrawBottomBar();
        }
    }

    // ============================================================
    // Task 2.2: FightMenuView — Move selection sub-menu (2x2 grid)
    // ============================================================
    /// @brief Interactive fight sub-menu — returns selected move ID
    /// @details Displays battle background (sprites + HP) then available moves
    ///          in a 2x2 grid. User selects a move or cancels with ESC.
    /// @param playerOne Current player's data (reads active Pokemon's moves)
    /// @param playerTwo Opponent player's data (for battle background)
    /// @return Move ID (1-indexed) or -1 if cancelled
    inline int FightMenuView(PokemonGame::Player& playerOne, PokemonGame::Player& playerTwo, bool flipPerspective = false) {
        // Draw battle background with sprites, life bars, names
        DrawBattleBackground(playerOne, playerTwo, flipPerspective);

        PokemonGame::Pokemon* activePoke = playerOne.GetActivePokemon();
        if (!activePoke) return -1;

        std::string pokeName = activePoke->GetName();
        std::vector<PokemonGame::Move*> moves = activePoke->GetMoves();

        // Build option strings: "MOVE_NAME (Type)" — max 4 moves
        std::vector<std::string> options;
        std::vector<int> moveIds;
        for (PokemonGame::Move* move : moves) {
            if (move && move->HasName()) {
                std::string label = move->GetName() + " (" + PokemonTypeToString(move->GetType()) + ")";
                options.push_back(label);
                moveIds.push_back(move->GetId());
            }
        }

        // Handle no moves available
        if (options.empty()) {
            Common::PrintPrimaryBox(BattleMargin, BattleOptionsY + 1, Common::WIDTH_SCREEN - 2 * BattleMargin, 2 * BattleBoxHeight,
                {pokeName + " no tiene movimientos disponibles."}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
            Common::DrawBottomBar();
            Common::Sleep(1500);
            return -1;
        }

        // Info box: player name + attack type
        std::string typeStr = PokemonTypeToString(activePoke->GetType());
        Common::PrintPrimaryBox(BattleMargin, BattleOptionsY + 1, BattleBoxWidth - BattleMargin, 2 * BattleBoxHeight,
            {playerOne.GetName(), "Ataque tipo " + typeStr}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);

        int selectedOption = 0;
        const int menuX = 2 * BattleMargin + BattleBoxWidth;
        const int menuY = BattleOptionsY;
        const int slotWidth = BattleBoxWidth - 2 * BattleMargin;
        const int slotHeight = BattleBoxHeight;

        // Bottom bar hints
        Common::keysHelper.clear();
        Common::keysHelper.push_back({"←→↑↓", "Navegar"});
        Common::keysHelper.push_back({"ENTER", "Atacar"});
        Common::keysHelper.push_back({"ESC", "Volver"});
        Common::DrawBottomBar();

        while (true) {
            // Draw 2x2 grid (max 4 moves)
            for (int i = 0; i < static_cast<int>(options.size()) && i < 4; i++) {
                int row = i / 2;
                int col = i % 2;
                int x = menuX + col * (slotWidth + BattleMargin);
                int y = menuY + row * (slotHeight + BattleMargin);
                std::array<int, 3> bgColor = (i == selectedOption) ? Common::ORANGE : Common::FOREGROUND_DARK;
                std::array<int, 3> txtColor = (i == selectedOption) ? Common::FOREGROUND_DARK : Common::FOREGROUND_LIGHT;
                Common::PrintPrimaryBox(x, y, slotWidth, slotHeight, {options[i]},
                    txtColor, Common::FOREGROUND_DARK, bgColor);
            }

            Common::key = Common::ReadConsoleChar();

            if (Common::IsActionKey(Common::key)) {
                PlayAttackSound();
                return moveIds[selectedOption];
            } else if (Common::IsKeyArrowTop(Common::key)) {
                if (selectedOption >= 2) selectedOption -= 2;
            } else if (Common::IsKeyArrowBottom(Common::key)) {
                if (selectedOption < 2 && selectedOption + 2 < static_cast<int>(options.size())) selectedOption += 2;
            } else if (Common::IsKeyArrowLeft(Common::key)) {
                if (selectedOption % 2 == 1) selectedOption -= 1;
            } else if (Common::IsKeyArrowRight(Common::key)) {
                if (selectedOption % 2 == 0 && selectedOption + 1 < static_cast<int>(options.size())) selectedOption += 1;
            } else if (Common::key == Common::KEY_ESCAPE) {
                return -1;
            }

            // Redraw info box
            Common::PrintPrimaryBox(BattleMargin, BattleOptionsY + 1, BattleBoxWidth - BattleMargin, 2 * BattleBoxHeight,
                {playerOne.GetName(), "Ataque tipo " + typeStr}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);

            Common::DrawBottomBar();
        }
    }

    // ============================================================
    // Task 2.3: BagMenuView — Item selection sub-menu
    // ============================================================
    /// @brief Interactive bag sub-menu — returns selected item ID
    /// @details Displays battle background (sprites + HP) then items from the player's bag.
    ///          Shows "Mochila vacia" if bag is empty.
    /// @param playerOne Current player's data (reads bag contents)
    /// @param playerTwo Opponent player's data (for battle background)
    /// @return Item ID or -1 if cancelled or bag empty
    inline int BagMenuView(PokemonGame::Player& playerOne, PokemonGame::Player& playerTwo, bool flipPerspective = false) {
        // Draw battle background with sprites, life bars, names
        Common::DrawBackground();

        // Player name indicator
        Common::GoToXY(BattleMargin, 1);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << playerOne.GetName();

        // Draw Mochila sprite (above the battle info boxes, not overlapping)
        Common::DrawSprite(15, 2, Mochila);

        PokemonGame::Bag& bag = playerOne.GetBag();

        // Collect items from the bag using known IDs from FillBag
        std::vector<std::string> options;
        std::vector<int> itemIds;

        for (int id = 1; id <= 4; id++) {
            if (bag.HasItemWithId(id)) {
                options.push_back(GetItemDisplayName(id));
                itemIds.push_back(id);
            }
        }

        // Handle empty bag
        if (options.empty()) {
            Common::PrintPrimaryBox(BattleMargin, BattleOptionsY + 1, Common::WIDTH_SCREEN - 2 * BattleMargin, 2 * BattleBoxHeight,
                {"Mochila vacia", "No hay items disponibles."}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);

            Common::keysHelper.clear();
            Common::keysHelper.push_back({"ENTER", "Volver"});
            Common::DrawBottomBar();

            while (true) {
                Common::key = Common::ReadConsoleChar();
                if (Common::IsActionKey(Common::key) || Common::key == Common::KEY_ESCAPE) {
                    break;
                }
            }
            return -1;
        }

        int selectedOption = 0;
        // Position items to the right of the Mochila sprite
        const int bagY = 15;
        const int menuX = Common::AlignedX(0, Common::WIDTH_SCREEN, 50, "center");
        const int slotWidth = 50;
        const int slotHeight = 3;

        // Bottom bar hints
        Common::keysHelper.clear();
        Common::keysHelper.push_back({"↑↓", "Navegar"});
        Common::keysHelper.push_back({"ENTER", "Usar"});
        Common::keysHelper.push_back({"ESC", "Volver"});
        Common::DrawBottomBar();

        while (true) {
            Common::StaticSelectPrimaryBox1D(
                menuX, bagY,
                options, selectedOption,
                Common::FOREGROUND_DARK, Common::FOREGROUND_DARK,
                Common::ORANGE, Common::FOREGROUND_LIGHT,
                slotWidth, slotHeight
            );

            // Description box
            int descWidth = Common::WIDTH_SCREEN - 8;
            int descHeight = 4;
            int descX = Common::AlignedX(0, Common::WIDTH_SCREEN, descWidth, "center");
            int descY = Common::AlignedY(0, Common::HEIGHT_SCREEN, descHeight, "bottom") - 5;
            Common::PrintPrimaryBox(descX, descY, descWidth, descHeight,
                {GetItemDescription(itemIds[selectedOption])},
                Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);

            Common::key = Common::ReadConsoleChar();

            if (Common::IsActionKey(Common::key)) {
                return itemIds[selectedOption];
            } else if (Common::IsKeyArrowTop(Common::key)) {
                selectedOption = (selectedOption - 1 + options.size()) % options.size();
            } else if (Common::IsKeyArrowBottom(Common::key)) {
                selectedOption = (selectedOption + 1) % options.size();
            } else if (Common::key == Common::KEY_ESCAPE) {
                return -1;
            }

            Common::DrawBottomBar();
        }
    }

    // ============================================================
    // Task 2.4: PokemonMenuView — Team switch selection
    // ============================================================
    /// @brief Interactive team display — returns Pokemon ID to switch to
    /// @details Shows all Pokemon in the player's team with name, HP, and status.
    ///          Fainted Pokemon are grayed out and unselectable.
    ///          Current active Pokemon is also unselectable.
    /// @param player Current player's data (reads team)
    /// @return Pokemon ID to switch to, or -1 if cancelled
    inline int PokemonMenuView(PokemonGame::Player& player) {
        Common::DrawBackground();

        // Player name indicator
        Common::GoToXY(BattleMargin, 1);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << player.GetName();

        auto team = player.GetTeam();
        PokemonGame::Pokemon* activePoke = player.GetActivePokemon();

        // Build option strings and track selectable indices
        std::vector<std::string> options;
        std::vector<int> pokemonIds;
        std::vector<bool> selectable;

        for (const auto& pokePtr : team) {
            if (!pokePtr) continue;

            PokemonGame::Pokemon* poke = pokePtr.get();
            std::string name = poke->GetName();
            std::string status = "";
            bool isFainted = poke->IsFainted();
            bool isActive = (activePoke && poke->GetId() == activePoke->GetId());

            if (isFainted) {
                status = " (desmayado)";
            } else if (isActive) {
                status = " (activo)";
            }

            std::string hpStr = std::to_string(static_cast<int>(poke->GetCurrentHp())) + "/" +
                                std::to_string(static_cast<int>(poke->GetMaxHp())) + " HP";

            std::string label = name + " " + hpStr + status;
            options.push_back(label);
            pokemonIds.push_back(poke->GetId());
            // Can select if not fainted and not currently active
            selectable.push_back(!isFainted && !isActive);
        }

        // Handle empty team
        if (options.empty()) {
            Common::PrintPrimaryBox(BattleMargin, BattleOptionsY + 1, Common::WIDTH_SCREEN - 2 * BattleMargin, 2 * BattleBoxHeight,
                {"No hay Pokemon disponibles."}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
            Common::DrawBottomBar();
            Common::Sleep(1500);
            return -1;
        }

        // Check if any selectable Pokemon exist
        bool hasSelectable = false;
        for (bool sel : selectable) {
            if (sel) { hasSelectable = true; break; }
        }
        if (!hasSelectable) {
            Common::PrintPrimaryBox(BattleMargin, BattleOptionsY + 1, Common::WIDTH_SCREEN - 2 * BattleMargin, 2 * BattleBoxHeight,
                {"No hay Pokemon disponibles para cambiar."}, Common::FOREGROUND_DARK, Common::FOREGROUND_DARK, Common::FOREGROUND_LIGHT);
            Common::DrawBottomBar();
            Common::Sleep(1500);
            return -1;
        }

        int selectedOption = 0;
        // Find first selectable option
        for (int i = 0; i < static_cast<int>(selectable.size()); i++) {
            if (selectable[i]) {
                selectedOption = i;
                break;
            }
        }

        const int menuX = 2 * BattleMargin + BattleBoxWidth;
        const int menuY = BattleOptionsY;
        const int slotWidth = BattleBoxWidth - 2 * BattleMargin;
        const int slotHeight = BattleBoxHeight;

        // Bottom bar hints
        Common::keysHelper.clear();
        Common::keysHelper.push_back({"↑↓", "Navegar"});
        Common::keysHelper.push_back({"ENTER", "Cambiar"});
        Common::keysHelper.push_back({"ESC", "Volver"});
        Common::keysHelper.push_back({"*", "desmayado = no selectable"});
        Common::DrawBottomBar();

        while (true) {
            // Draw menu
            Common::StaticSelectPrimaryBox1D(
                menuX, menuY,
                options, selectedOption,
                Common::FOREGROUND_DARK, Common::FOREGROUND_DARK,
                Common::ORANGE, Common::FOREGROUND_LIGHT,
                slotWidth, slotHeight
            );

            Common::key = Common::ReadConsoleChar();

            if (Common::IsActionKey(Common::key)) {
                // Check if selected Pokemon is selectable
                if (selectable[selectedOption]) {
                    return pokemonIds[selectedOption];
                }
                // If not selectable, just ignore (stay on current position)
            } else if (Common::IsKeyArrowTop(Common::key)) {
                // Find next selectable option upward
                int next = selectedOption;
                for (int i = 0; i < static_cast<int>(options.size()); i++) {
                    next = (next - 1 + options.size()) % options.size();
                    if (selectable[next]) {
                        selectedOption = next;
                        break;
                    }
                }
            } else if (Common::IsKeyArrowBottom(Common::key)) {
                // Find next selectable option downward
                int next = selectedOption;
                for (int i = 0; i < static_cast<int>(options.size()); i++) {
                    next = (next + 1) % options.size();
                    if (selectable[next]) {
                        selectedOption = next;
                        break;
                    }
                }
            } else if (Common::key == Common::KEY_ESCAPE) {
                return -1;
            }

            Common::DrawBottomBar();
        }
    }

    // ============================================================
    // Task 2.5: RunConfirmationView — Flee confirmation dialog
    // ============================================================
    /// @brief Confirmation dialog for flee attempt
    /// @details Shows "Seguro que quieres huir?" with SI/NO options.
    ///          Returns true if confirmed, false if cancelled.
    /// @return true if player confirms flee, false otherwise
    inline bool RunConfirmationView() {
        Common::DrawBackground();

        // Dialog box centered on screen
        const int dialogWidth = 60;
        const int dialogHeight = 12;
        const int dialogX = Common::AlignedX(0, Common::WIDTH_SCREEN, dialogWidth, "center");
        const int dialogY = Common::AlignedY(0, Common::HEIGHT_SCREEN, dialogHeight, "center");

        // Message
        Common::PrintPrimaryBox(dialogX, dialogY, dialogWidth, dialogHeight,
            {"Seguro que quieres", "huir de la batalla?"},
            Common::FOREGROUND_DARK, Common::ORANGE, Common::CREAM);

        // SI / NO buttons
        std::vector<std::string> options = {"SI", "NO"};
        int selectedOption = 1; // Default to NO (safer)

        const int buttonWidth = 15;
        const int buttonY = dialogY + dialogHeight + 2;
        const int button1X = dialogX + dialogWidth / 2 - buttonWidth - 2;
        const int button2X = dialogX + dialogWidth / 2 + 2;

        // Bottom bar hints
        Common::keysHelper.clear();
        Common::keysHelper.push_back({"← →", "Navegar"});
        Common::keysHelper.push_back({"ENTER", "Confirmar"});
        Common::DrawBottomBar();

        while (true) {
            // Draw buttons
            std::array<int, 3> siBg = (selectedOption == 0) ? Common::ORANGE : Common::FOREGROUND_DARK;
            std::array<int, 3> noBg = (selectedOption == 1) ? Common::ORANGE : Common::FOREGROUND_DARK;
            std::array<int, 3> siTxt = (selectedOption == 0) ? Common::FOREGROUND_DARK : Common::FOREGROUND_LIGHT;
            std::array<int, 3> noTxt = (selectedOption == 1) ? Common::FOREGROUND_DARK : Common::FOREGROUND_LIGHT;

            Common::PrintPrimaryBox(button1X, buttonY, buttonWidth, BattleBoxHeight,
                {"SI"}, siTxt, Common::ORANGE, siBg);
            Common::PrintPrimaryBox(button2X, buttonY, buttonWidth, BattleBoxHeight,
                {"NO"}, noTxt, Common::ORANGE, noBg);

            Common::key = Common::ReadConsoleChar();

            if (Common::IsActionKey(Common::key)) {
                return (selectedOption == 0); // true if SI selected
            } else if (Common::IsKeyArrowLeft(Common::key) || Common::IsKeyArrowRight(Common::key)) {
                selectedOption = 1 - selectedOption; // Toggle between 0 and 1
            } else if (Common::key == Common::KEY_ESCAPE) {
                return false; // ESC = cancel = NO
            }

            Common::DrawBottomBar();
        }
    }

    // ============================================================
    // Task 2.6: AttackResultView — Attack result display
    // ============================================================
    /// @brief Displays attack result message with effectiveness
    /// @details Shows "{player}: {attacker} ha usado {attack}!" then damage and effectiveness.
    ///          Brief pause before returning.
    /// @param playerName Name of the player performing the attack
    /// @param attacker Name of the attacking Pokemon
    /// @param attackName Name of the attack used
    /// @param defender Name of the defending Pokemon
    /// @param damage Damage dealt (for display)
    /// @param effectiveness Effectiveness message (e.g., "Es muy efectivo!", "No es muy efectivo...")
    inline void AttackResultView(
        const std::string& playerName,
        const std::string& attacker,
        const std::string& attackName,
        const std::string& defender,
        int damage,
        const std::string& effectiveness
    ) {
        Common::DrawBackground();

        // Main attack message with player name
        std::string attackMsg = playerName + ": " + attacker + " ha usado " + attackName + "!";
        int msgWidth = Common::Length(attackMsg) + 8;
        if (msgWidth < 40) msgWidth = 40;
        int msgX = Common::AlignedX(0, Common::WIDTH_SCREEN, msgWidth, "center");
        int msgY = Common::AlignedY(0, Common::HEIGHT_SCREEN, 8, "center") - 2;

        Common::PrintPrimaryBox(msgX, msgY, msgWidth, 8,
            {attackMsg},
            Common::FOREGROUND_LIGHT, Common::ORANGE, Common::SELECTION_BACKGROUND);

        // Damage message — 2 rows below the centered attack text
        std::string dmgMsg = "-" + std::to_string(damage) + " PS";
        int dmgX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(dmgMsg) + 4, "center");
        Common::DrawText(dmgX, msgY + 5, -1, -1,
            {dmgMsg}, Common::RED, Common::SELECTION_BACKGROUND);

        // Effectiveness line (if not empty) — 2 rows below damage text
        if (!effectiveness.empty()) {
            int effX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(effectiveness) + 4, "center");
            std::array<int, 3> effColor = Common::FOREGROUND_LIGHT;
            if (effectiveness.find("muy efectivo") != std::string::npos) {
                effColor = Common::LIGHT_GREEN;
            } else if (effectiveness.find("no es muy") != std::string::npos) {
                effColor = Common::ORANGE;
            } else if (effectiveness.find("poco") != std::string::npos) {
                effColor = Common::DARK_RED;
            }
            Common::DrawText(effX, msgY + 7, -1, -1,
                {effectiveness}, effColor, Common::SELECTION_BACKGROUND);
        }

        // Bottom bar
        Common::keysHelper.clear();
        Common::keysHelper.push_back({"ENTER", "Continuar"});
        Common::DrawBottomBar();

        // Wait for key press
        while (true) {
            Common::key = Common::ReadConsoleChar();
            if (Common::IsActionKey(Common::key) || Common::key == Common::KEY_ESCAPE) {
                break;
            }
        }
    }

    // ============================================================
    // Task 2.7: RunResultView — Flee result display
    // ============================================================
    /// @brief Displays flee result message announcing the winner
    /// @details Shows "{runner} ha huido de la batalla! {winner} es el ganador!"
    ///          Visual style matches AttackResultView (centered box).
    /// @param runnerName Name of the player who fled
    /// @param winnerName Name of the winning player
    inline void RunResultView(const std::string& runnerName, const std::string& winnerName) {
        Common::DrawBackground();

        std::string msg1 = runnerName + " ha huido";
        std::string msg2 = "de la batalla!";
        std::string msg3 = winnerName + " es el ganador!";

        int msgWidth = Common::Length(msg3) + 8;
        if (msgWidth < 40) msgWidth = 40;
        int msgX = Common::AlignedX(0, Common::WIDTH_SCREEN, msgWidth, "center");
        int msgY = Common::AlignedY(0, Common::HEIGHT_SCREEN, 10, "center") - 2;

        Common::PrintPrimaryBox(msgX, msgY, msgWidth, 10,
            {msg1, msg2, "", msg3},
            Common::FOREGROUND_LIGHT, Common::ORANGE, Common::SELECTION_BACKGROUND);

        // Bottom bar
        Common::keysHelper.clear();
        Common::keysHelper.push_back({"ENTER", "Continuar"});
        Common::DrawBottomBar();

        // Wait for key press
        while (true) {
            Common::key = Common::ReadConsoleChar();
            if (Common::IsActionKey(Common::key) || Common::key == Common::KEY_ESCAPE) {
                break;
            }
        }
    }

} // namespace Pokemon
