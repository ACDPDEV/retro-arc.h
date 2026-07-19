# Pokemon

> Namespace: `Pokemon` | Entry: `Juegos/Pokemon/Pokemon.cpp`

## Overview
Pokemon battle game with modern OOP architecture, Command Pattern, and comprehensive View-Model separation. Features a complete 2-player battle system with animated sprites, item system, and turn-based combat.

---

## Files

### Root Files

| File | Purpose |
|------|---------|
| `Pokemon.h` | Entry point declaration — calls `TitleView()` and `MenuView()` |
| `Pokemon.cpp` | Entry point implementation — includes all dependencies |
| `PokemonUI.h` | Battle UI functions (permanent graphics, options, animations) |
| `PokemonFunctions.h` | Utility functions (empty) |
| `PokemonMusic.h` | Music integration |
| `PokemonSounds.h` | Sound effects |
| `PokemonFigures.h` | Game figures/sprites for battle |
| `PokeballLaunch_Left.h` | Pokeball sprite left (23 animation frames) |
| `PokeballLaunch_Right.h` | Pokeball sprite right (23 animation frames) |

### Models/ (11 files)

| File | Purpose |
|------|---------|
| `Pokemon.h` | Pokemon class — name, type, HP, stats, moves |
| `Move.h` | Abstract move base class — name, damage, accuracy |
| `PhysicalMove.h` | Physical move type (uses `Move` constructor) |
| `SpecialMove.h` | Special move type (uses `Move` constructor) |
| `StatusMove.h` | Status move type (uses `Move` constructor) |
| `Bag.h` | Bag class — stores items, uses items on Pokemon |
| `Item.h` | Abstract item base class — name, virtual `use()` |
| `Potion.h` | Potion item — heals HP (configurable heal points) |
| `SuperPotion.h` | Super Potion item — inherits from `Potion` |
| `Antidote.h` | Antidote item — cures status conditions |
| `Player.h` | Player class — name, team, bag, active Pokemon |

### Game/ (3 files)

| File | Purpose |
|------|---------|
| `Game.h` | Game orchestration — main loop, team building, battle start |
| `Battle.h` | Battle system — manages rounds, checks win conditions |
| `Round.h` | Round management — player turns, command execution |

### Commands/ (5 files)

| File | Purpose |
|------|---------|
| `Command.h` | Abstract command base — virtual `Execute()` |
| `AttackCommand.h` | Attack action — executes a move |
| `BagCommand.h` | Use item action — applies item to active Pokemon |
| `RunCommand.h` | Run away action — attempts to flee battle |
| `SwitchPokemonCommand.h` | Switch Pokemon action — changes active Pokemon |

### Views/ (7 files)

| File | Purpose |
|------|---------|
| `TitleView.h` | Title screen — logo with gradient, sprites, prompt text |
| `MenuView.h` | Main menu — uses `TitleComponent` |
| `PlayersView.h` | Player names input — dual panels with styled inputs |
| `PokemonSelectionView.h` | Pokemon selection — 4x2 grid with navigation |
| `MochilaView.h` | Bag view — item list with descriptions |
| `HuidaView.h` | Run away screen — animated Psyduck escaping |
| `VictoryView.h` | Victory screen — title, winner sprite, confetti animation |

### Other Directories

| Directory | Files | Purpose |
|-----------|-------|---------|
| `Database/` | `MockData.h`, `State.h` | Mock Pokemon and item data (8 Pokemon, 4 items) + global game state |
| `Factories/` | `PokemonFactory.h` | Factory pattern for creating Pokemon instances |
| `Functions/` | `BuildTeam.h` | Team building logic (uses factory) |
| `Components/` | `TitleComponent.h` | Reusable title component with gradient |
| `Sprites/` | `Trainer1.h`, `Trainer2.h`, `Mochila.h` | Trainer and bag sprites |
| `PokemonStaticSprites/` | 16 files | Static front/back sprites for 8 Pokemon |
| `PokemonAnimatedSprites/` | 16 files | Animated front/back sprites for 8 Pokemon (10 frames each) |
| `PokemonMiniSprites/` | 8 files | Mini ANSI truecolor sprites for PokemonSelectionView (1 per Pokemon) |

---

## Architecture

### Command Pattern
All player actions are encapsulated as Command objects:
```cpp
class Command {
public:
    virtual ~Command() = default;
    virtual void Execute(
        PokemonGame::Battle& battle,
        PokemonGame::Player& actor,
        PokemonGame::Player& opponent) = 0;
};
```

### Model-View Separation
- **Models/**: Pure data classes (`Pokemon`, `Player`, `Bag`, `Move`, `Item`)
- **Views/**: Display functions with no business logic (use Common library for rendering)
- **Commands/**: Bridge between user input and model updates

### Game Orchestration
```
Game::Start()
  └─> BuildTeam() × 2
  └─> Battle::Start()
        └─> Round::Play() × N
              └─> Player::ChooseCommand()
              └─> Command::Execute()
```

---

## Dependencies

| Utility | File | Usage |
|---------|------|-------|
| `Variables.h` | `Common/Variables.h` | Global state (`playerName`, `key`) |
| `Font.h` | `Common/Font.h` | Text rendering (FONT4, FONT9 fonts) |
| `Color.h` | `Common/Color.h` | Color constants and handling |
| `Graphics.h` | `Common/Graphics.h` | Drawing functions (`DrawText`, `DrawSprite`, `DrawFillRectangle`) |
| `Sprite.h` | `Common/Sprite.h` | Sprite rendering (`DrawSprite`) |
| `Terminal.h` | `Common/Terminal.h` | Terminal operations (`Clear`, `GoToXY`, `HideCursor`) |
| `Theme.h` | `Common/Theme.h` | Color theme constants |
| `Utils.h` | `Common/Utils.h` | Utility functions (`Length`, `AlignedX`, `AlignedY`) |
| `Aligned.h` | `Common/Aligned.h` | Alignment calculations |
| `Consts.h` | `Common/Consts.h` | Screen dimensions (`WIDTH_SCREEN`, `HEIGHT_SCREEN`) |
| `BottomBar.h` | `Common/Components/BottomBar.h` | Bottom bar component |
| `InputComponent.h` | `Common/Components/InputComponent.h` | Input component |
| `LifeBar.h` | `Common/Components/LifeBar.h` | Life bar rendering |
| `SelectPrimaryBox.h` | `Common/Components/SelectPrimaryBox.h` | Selection box component |
| `Input.h` | `Common/Input.h` | Input handling (`ReadConsoleChar`, `IsKeyArrowTop`) |
| `Navigation.h` | `Common/Navigation.h` | Navigation utilities |
| `Output.h` | `Common/Output.h` | Output utilities |
| `UnicodeGlyphs.h` | `Common/UnicodeGlyphs.h` | Unicode characters (`HORIZONTAL_BORDER`, `VERTICAL_BORDER`) |

---

## Key Functions

### Entry Point
```cpp
namespace Pokemon {
    inline void Pokemon() {
        TitleView();           // Show title screen
        MenuView();            // Show main menu
        PlayersView();         // Enter player names (writes to playerNames[])
        
        currentSelectionPlayer = 0;
        PokemonSelectionView(); // Player 1 selects Pokemon
        
        currentSelectionPlayer = 1;
        PokemonSelectionView(); // Player 2 selects Pokemon
        
        // Battle would go here
        HuidaView();           // Placeholder - shows run animation
    }
}
```

### Core Classes

#### Pokemon Class
```cpp
class Pokemon {
private:
    std::string name;
    PokemonType type;
    int maxHp, currentHp;
    int attack, defense, speed;
    std::vector<Move*> moves;
public:
    Pokemon(const std::string& name, PokemonType type, int hp, int attack, int defense, int speed);
    virtual ~Pokemon();
    void receiveDamage(int damage);
    bool isFainted() const;
    void addMove(Move* move);
    Move* getMove(int index);
    PokemonType getType() const;
};
```

#### Player Class
```cpp
class Player {
private:
    std::string name;
    std::vector<std::unique_ptr<Pokemon>> team;
    Pokemon* activePokemon;
    Bag bag;
public:
    Player(const std::string& name);
    std::string GetName();
    bool HasLost();
    void ClearTeam();
    int TeamSize() const;
    void AddPokemon(std::unique_ptr<Pokemon> pokemon);
    Pokemon* GetPokemon(size_t index);
    void SwitchPokemon(size_t index);
    Pokemon* GetActivePokemon();
    Bag& GetBag();
    std::unique_ptr<Command> ChooseCommand(Battle& battle);
};
```

#### Game Class
```cpp
class Game {
public:
    static inline int maxPokemon = 6;
    void Start();  // Main game loop
};
```

#### Battle Class
```cpp
class Battle {
private:
    Player& playerOne;
    Player& playerTwo;
    bool finished;
public:
    Battle(Player& playerOne, Player& playerTwo);
    void Start();           // Main battle loop
    void EvaluateBattle();  // Check win conditions
    bool IsFinished();
};
```

#### Round Class
```cpp
class Round {
private:
    Player& player1;
    Player& player2;
    Battle& battle;
    std::unique_ptr<Command> playerOneCommand;
    std::unique_ptr<Command> playerTwoCommand;
public:
    Round(Battle& battle, Player& player1, Player& player2);
    void Play();  // Execute both player turns
};
```

### View Functions

```cpp
// Title screen with logo, sprites, and prompt
inline void TitleView();

// Main menu
inline void MenuView();

// Player name input with styled panels — writes to playerNames[0] and playerNames[1]
inline void PlayersView();

// Pokemon selection grid (4x2) — reads currentSelectionPlayer, writes to selectedCurrentPokemonId[currentSelectionPlayer]
inline void PokemonSelectionView();

// Bag view with item descriptions
inline void MochilaView();

// Run away animation — reads currentPokemonName, playerNames[currentSelectionPlayer], currentRound
inline void HuidaView();

// Victory screen with confetti — reads winnerName, currentRound, selectedCurrentPokemonId[winnerIndex]
inline void VictoryView();
```

### Battle UI Functions (PokemonUI.h)
```cpp
void ShowPokemonSprites();
void PermanentBattleGraphicsView(std::string Pokemon1, std::string Pokemon2);
void BattleBeginningTitleView();      // "FIGHT!" animation
void BattleBeginningAnimationView();  // Pokeball launch + sprite reveal
void BattleOptionsView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon);
void BattleOptionsFightView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon);
void BattleOptionsFightAttackedView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon);
void BattleOptionsFightEffectivenessView(std::string Pokemon1, std::string Pokemon2, std::string CurrentPokemon);
```

---

## Data Flow

```
User Input → Command → Game → Battle → Round → Execute Command → Update Models → Refresh Views

Detailed:
1. TitleView() → MenuView() → PlayersView() (writes playerNames[])
2. PokemonSelectionView() × 2 (writes selectedCurrentPokemonId[])
3. Battle::Start()
4.   Round::Play()
5.     Player::ChooseCommand() → User selects action
6.     Command::Execute() → Updates Pokemon HP/status
7.     EvaluateBattle() → Check if battle is over
8. VictoryView() or HuidaView()
```

---

## Class Hierarchy

```
Command (abstract)
├── AttackCommand        — Executes a Move on opponent's Pokemon
├── BagCommand           — Uses an Item on actor's active Pokemon
├── RunCommand           — Attempts to flee battle
└── SwitchPokemonCommand — Changes actor's active Pokemon

Move (abstract)
├── PhysicalMove  — Physical attack (uses constructor inheritance)
├── SpecialMove   — Special attack (uses constructor inheritance)
└── StatusMove    — Status effect move (uses constructor inheritance)

Item (abstract)
├── Potion       — Heals HP (configurable amount)
│   └── SuperPotion — Heals more HP (inherits Potion)
└── Antidote     — Cures status conditions

PokemonType (enum class)
├── Normal, Fire, Water, Grass, Electric
├── Rock, Ice, Psychic, Ghost
```

---

## Database

### Global State (State.h)
```cpp
namespace Pokemon {
    inline std::string playerNames[2] = {"", ""};           // Player names
    inline int selectedCurrentPokemonId[2] = {0, 0};       // Selected Pokemon per player
    inline int currentSelectionPlayer = 0;                  // Current player selecting (0 or 1)
    inline int pokemonPlayers[2] = {0, 0};                  // Pokemon IDs per player
    inline std::string currentPokemonName = "";              // Current Pokemon name
    inline int currentRound = 0;                            // Current round number
    inline std::string winnerName = "";                     // Winner's name
}
```

### Mock Data
```cpp
const MockPokemon MOCK_POKEMON[8] = {
    {"Bulbasaur",  45, 45, 0},
    {"Charmander", 39, 39, 1},
    {"Squirtle",   44, 44, 2},
    {"Pikachu",    35, 35, 3},
    {"Psyduck",    50, 50, 4},
    {"Eevee",      55, 55, 5},
    {"Rockruff",   45, 45, 6},
    {"Chikorita",  45, 45, 7}
};

const MockItem BAG_ITEMS[4] = {
    {"Pocion",       "Restaura 20 PS de un Pokemon.", 3},
    {"Super Pocion", "Restaura 50 PS de un Pokemon.", 2},
    {"Antidoto",     "Cura un estado alterado de un Pokemon.", 1},
    {"Revivir",      "Revive a un Pokemon debilitado con la mitad de sus PS.", 0}
};
```

---

## Sprites

### Static Sprites (8 Pokemon)
Each Pokemon has front and back static sprites:
- Bulbasaur, Charmander, Squirtle, Pikachu
- Psyduck, Eevee, Rockruff, Chikorita

### Animated Sprites (8 Pokemon)
Each Pokemon has 10 animation frames (front and back):
- Used for battle animations and transitions

### Other Sprites
- `Trainer1.h`, `Trainer2.h` — Player trainer sprites
- `Mochila.h` — Bag/backpack sprite
- `PokeballLaunch_Left/Right.h` — 23-frame pokeball launch animation

### Mini Sprites (8 Pokemon)
Used in PokemonSelectionView for compact display:
- BulbasaurMini, CharmanderMini, SquirtleMini, PikachuMini
- PsyduckMini, EeveeMini, RockruffMini, ChikoritaMini
- ANSI truecolor precomputed sprites — zero runtime cost

---

## Platform Notes

- **Cross-platform**: Uses Common library for OS abstraction
- **Modern C++**: Classes, inheritance, smart pointers (`std::unique_ptr`), vectors
- **Header-only**: Most code in `.h` files (inline functions)
- **Terminal-based**: Renders to terminal using ANSI escape codes

---

## Key Design Patterns

1. **Command Pattern**: Encapsulates player actions as objects
2. **Factory Pattern**: `PokemonFactory::Create()` instantiates Pokemon
3. **Template Method**: `Move::execute()` pure virtual, implemented by subclasses
4. **Observer-like**: Views update based on model state

---

## Implementation Status

### Complete
- ✅ Title screen with animated logo
- ✅ Player name input with styled panels
- ✅ Pokemon selection grid
- ✅ Battle UI (options, attacks, effectiveness)
- ✅ Victory screen with confetti animation
- ✅ Run away animation (Psyduck)
- ✅ Mock data for Pokemon and items

### In Progress / TODO
- 🔲 `Player::HasLost()` — Not implemented
- 🔲 `Battle::IsFinished()` — Not implemented
- 🔲 `Player::ChooseCommand()` — UI integration pending
- 🔲 `PokemonFactory::Create()` — Switch cases commented out
- 🔲 `BuildTeam()` — Menu integration pending
- 🔲 Item quantity management in Bag

---

## See Also

- [Common Library](../CommonDOCS.md)
- [MainMenu](MainMenu.md)
