# Buscaminas

> Namespace: `Minesweeper` | Entry: `Juegos/Buscaminas/Buscaminas.cpp`

## Overview

Minesweeper game with service layer architecture. Partially migrated to Common utilities. Uses a dual-board system: a **background board** (mines and adjacent counts) and a **state board** (cell visibility states).

**Cell state values:**

| Value | Meaning |
|-------|---------|
| `-2` | Flagged (has flag) |
| `-1` | Hidden (hidden) |
| `0` | Safe (revealed, no adjacent mines) |
| `1–8` | Adjacent (revealed, N adjacent mines) |
| `9` | Mine |

**Board values (background):**

| Value | Meaning |
|-------|---------|
| `0` | Safe cell |
| `1–8` | Adjacent mine count |
| `9` | Mine |

---

## Files

| File | Purpose |
|------|---------|
| `Buscaminas.h` | Main header with `PlayMinesweeper()` entry point |
| `Buscaminas.cpp` | Legacy `main()` with direct `conio.h` usage |
| `BuscaminasFunctions.h` / `.cpp` | Utility functions (input, validation, board helpers) |
| `BuscaminasService.h` | Service layer — game logic, state management, commands |
| `BuscaminasDatabase.h` | Database layer — board creation, mine placement |

---

## Architecture

Service-layer pattern separating concerns:

```
┌─────────────────────────────────────────────────┐
│  Main (Buscaminas.h / Buscaminas.cpp)           │
│  Entry point, menu loop, game loop               │
└─────────────┬───────────────────────────────────┘
              │
┌─────────────▼───────────────────────────────────┐
│  Service (BuscaminasService.h)                   │
│  Game logic, state validation, commands           │
│  • RevealCommand, FlagCommand, MoveCommand        │
│  • Win/loss detection, key identification         │
└─────────────┬───────────────────────────────────┘
              │
┌─────────────▼───────────────────────────────────┐
│  Database (BuscaminasDatabase.h)                 │
│  Board generation, mine placement, adjacent count │
│  • CreateBackgroundBoard, PlaceMines              │
│  • CountAdjacentMines                             │
└─────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────┐
│  Functions (BuscaminasFunctions.h/.cpp)          │
│  Utility helpers — input handling, validation     │
│  (Legacy, duplicates some Service logic)          │
└─────────────────────────────────────────────────┘
```

---

## Dependencies

| Utility | File | Usage |
|---------|------|-------|
| `Variables.h` | `Common/Variables.h` | Global state (`key`, `feedbackMessage`) |
| `Input.h` | `Common/Input.h` | `ReadConsoleChar()` |
| `Navigation.h` | `Common/Navigation.h` | `IsNavigationKey()`, `SetOption()`, `PrintFeedBackMessage()`, arrow key checks |
| `Output.h` | `Common/Output.h` | `PrintFeedBackMessage()` |
| `Consts.h` | `Common/Consts.h` | Key constants (`KEY_R`, `KEY_B`, `KEY_ESCAPE`, etc.) |

---

## Key Functions

### `Buscaminas.h`

```cpp
namespace Minesweeper {
    void PlayMinesweeper();
}
```

Main game entry point. Runs the menu loop (JUGAR / CRÉDITOS / VOLVER / CONFIGURACIONES) and the game loop. Delegates to Service and Database layers.

---

### `Buscaminas.cpp`

```cpp
// Global
string feedbackMessage = "";

// Entry point
int main();
```

Legacy implementation using `conio.h` directly. Contains its own `GetUserKey()`, `SetOption()`, `CanExcecuteOption()` functions. Moves with WASD keys instead of arrow keys. **Marked for migration to Common utilities.**

---

### `BuscaminasFunctions.h` / `.cpp`

**Database functions:**

```cpp
vector<vector<int>> CreateBackgroundBoard(int rows, int cols);
void PlaceMines(vector<vector<int>>& board, int minesQuantity);
void CountAdjacentMines(vector<vector<int>>& board);
```

**Input / Logic functions:**

```cpp
int  GetUserKey(string& feedbackMessage);
int  SetOption(int& option, int minOption, int maxOption, int userKey);
bool CanExcecuteOption(int userKey);
bool BuscaminasIsValidOption(int option, vector<int>& validOptions);
int  SetMinesQuantity(int rows, int cols, int levelOption);
int  SetRowsByLevel(int levelOption);
int  SetColsByLevel(int levelOption);
vector<vector<int>> CreatePageStateBoard(int rows, int cols);
array<int, 2> GetInitialPosition(int rows, int cols);
void ExecuteAction(vector<vector<int>>& stateBoard, int r, int c, int action, string& feedbackMessage);
bool IsWonGameState();  // TODO: not yet defined
```

**View functions:**

```cpp
void DisplayBoard(const vector<vector<int>>& board);
```

> **Note**: This file uses `conio.h` and `getch()` directly. Functions here duplicate logic from `BuscaminasService.h` — part of the legacy code being migrated.

---

### `BuscaminasService.h`

All functions live inside `namespace Minesweeper`.

**Configuration functions:**

```cpp
int SetMinesQuantity(int rows, int cols, int levelOption);
int SetInitialFlagCount(int minesQuantity);
int SetRowsByLevel(int levelOption);
int SetColsByLevel(int levelOption);
```

**Board initialization:**

```cpp
vector<vector<int>> CreatePageStateBoard(int rows, int cols);
array<int, 2>       GetInitialPosition(int rows, int cols);
```

**State value accessors:**

```cpp
int  GetStateValueSafe();      // returns 0
int  GetStateValueFlagged();   // returns -2
int  GetStateValueHidden();    // returns -1
bool StateValueIsHidden(int stateValue);
bool StateValueIsFlagged(int stateValue);
bool StateValueIsRevealed(int stateValue);
```

**Background value accessors:**

```cpp
int  GetBackGroundValueSafe();       // returns 0
bool BackgroundValueIsSafe(int backgroundValue);
bool BackGroundValueIsAdjacent(int backgroundValue);
```

**Game commands:**

```cpp
void RevealSafeRegionCommand(
    vector<vector<int>> backgroundBoard,
    vector<vector<int>>& stateBoard,
    int playerRow, int playerCol,
    string& feedbackMessage
);

void RevealCommand(
    vector<vector<int>> backgroundBoard,
    vector<vector<int>>& stateBoard,
    int row, int col,
    string& feedbackMessage
);

bool MineIsRevealed(vector<vector<int>> backgroundBoard, int row, int col, string& feedbackMessage);

void MoveCommand(int& playerRow, int& playerCol, int rows, int cols, vector<int>& key);

void FlagCommand(
    int& flagCount,
    vector<vector<int>>& stateBoard,
    int row, int col,
    string& feedbackMessage
);

bool IsWonGameState(vector<vector<int>>& stateBoard, int minesQuantity);
```

**Key identification helpers:**

```cpp
bool IsMoveKey(vector<int>& key);
bool IsRevealKey(vector<int>& key);
bool IsFlagKey(vector<int>& key);
bool IsExitMatchKey(vector<int>& key);
```

---

### `BuscaminasDatabase.h`

All functions live inside `namespace Minesweeper`.

```cpp
vector<vector<int>> CreateBackgroundBoard(int rows, int cols);
void PlaceMines(vector<vector<int>>& board, int minesQuantity);
void CountAdjacentMines(vector<vector<int>>& board);
```

---

## Data Flow

```
User Input
    │
    ▼
Service Layer (key identification, command dispatch)
    │
    ├──► Database: board creation, mine placement
    │
    ├──► State Update: modify stateBoard cells
    │
    └──► Display: render stateBoard with cursor position
```

**Game loop:**

1. Display current state board
2. Read user input (arrow keys / R / B / Q)
3. Service identifies key type → dispatches command
4. Command modifies state board or position
5. Check win/loss conditions
6. Repeat

---

## Platform Notes

- **Partially cross-platform**: Uses Common library (`Navigation.h`, `Input.h`, `Output.h`) for arrow key handling
- **Legacy code** in `Buscaminas.cpp` and `BuscaminasFunctions.cpp` uses `conio.h` and `getch()` directly — Windows-only
- `BuscaminasService.h` uses Common utilities and is cross-platform
- `BuscaminasDatabase.h` is pure C++ with no platform dependencies

---

## Migration Status

| Component | Status |
|-----------|--------|
| Database layer | ✅ Migrated (`BuscaminasDatabase.h`) |
| Service layer | ✅ Migrated (`BuscaminasService.h`) |
| Functions layer | ⚠️ Legacy — duplicates Service logic |
| Main entry point | ⚠️ Partial — `PlayMinesweeper()` uses Common; `main()` uses `conio.h` |

---

## Levels

| Level | Rows | Cols | Mine Density |
|-------|------|------|--------------|
| Easy (`0`) | 9 | 9 | 5.0% |
| Medium (`1`) | 16 | 16 | 8.2% |
| Hard (`2`) | 16 | 30 | 12.5% |

---

## See Also

- [Common Library](../CommonDOCS.md)
- [MainMenu](MainMenu.md)
- [BatallaNaval](BatallaNaval.md)
- [Tictactoe](Tictactoe.md)
