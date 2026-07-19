# MainMenu

> Namespace: `MainMenu` | Entry: `MainMenu/MainMenu.h`

## Overview

Main menu system: presentation, authentication, game selection. Orchestrates all games.

---

## Files

| Folder/File | Purpose |
|-------------|---------|
| `MainMenu.h` | Entry point, orchestrates views and authentication flow |
| `Views/PresentationView.h` | Initial presentation screen with animated title |
| `Views/PasswordView.h` | Password input screen with hidden/visible mode |
| `Views/MainMenuView.h` | Game selection menu |
| `Views/WrongPasswordView.h` | Error feedback after max failed attempts |
| `Commands/Auth.h` | Authentication logic (password validation) |
| `Components/TitleComponent.h` | Title rendering with gradient colors |
| `Database/Options.h` | Menu option constants |
| `Database/Labels.h` | UI label strings |
| `Database/Env.h` | Environment config (password, attempts, state) |
| `Sprites/ArcadeLeft.h` | Left arcade cabinet ANSI truecolor sprite |
| `Sprites/ArcadeRight.h` | Right arcade cabinet ANSI truecolor sprite |

---

## Architecture

```
PresentationView → PasswordView → Auth Check → MainMenuView → Game Selection → Launch Game
```

### Flow Details

1. **PresentationView** — Renders the animated "RETRORCH." title with gradient colors and arcade sprites
2. **PasswordView** — Prompts user for password (up to `MAX_ATTEMPTS` retries)
3. **Auth Check** — `isValidPassword()` compares `INPUT` against `CLAVE`
4. **MainMenuView** — Shows game selection menu using `SelectComponent`
5. **WrongPasswordView** — Displayed if all attempts are exhausted

---

## Dependencies

| Utility | File | Usage |
|---------|------|-------|
| `Consts.h` | `Common/Consts.h` | Constants (`WIDTH_SCREEN`, `HEIGHT_SCREEN`) |
| `Aligned.h` | `Common/Aligned.h` | Alignment (`AlignedX`, `AlignedY`) |
| `Graphics.h` | `Common/Graphics.h` | Drawing (`DrawBackground`, `DrawText`, `DrawSprite`, `GoToEnd`) |
| `Font.h` | `Common/Font.h` | Title font (`FONT9_*` glyphs, `ConcatFont`) |
| `Color.h` | `Common/Color.h` | Colors (`Gradient`) |
| `Utils.h` | `Common/Utils.h` | Utilities (`Sleep`, `EnableUTF8`, `Clear`, `HideCursor`, `Length`, `MaxString`) |
| `Theme.h` | `Common/Theme.h` | Theme colors (`BACKGROUND`, `FOREGROUND_DARK`, `SELECTION_BACKGROUND`, `ACCENT`) |
| `Sprite.h` | `Common/Sprite.h` | Sprite rendering (`DrawSprite`) |
| `Input.h` | `Common/Input.h` | User input |
| `SelectComponent.h` | `Common/Components/SelectComponent.h` | Selection menu component |
| `InputComponent.h` | `Common/Components/InputComponent.h` | Password input component |
| `TransitionComponent.h` | `Common/Components/TransitionComponent.h` | Screen transitions |

---

## Key Functions

### `MainMenu/MainMenu.h`

```cpp
/// @brief Entry point — orchestrates the full presentation → auth → menu flow
inline void MainMenu();
```

Runs `PresentationView()`, then loops up to `MAX_ATTEMPTS` times through `PasswordView()`. On success, shows success message with countdown and launches `MainMenuView()`. On failure, shows `WrongPasswordView()`.

---

### `Views/PresentationView.h`

```cpp
/// @brief Renders the animated "RETRORCH." title with gradient colors and arcade sprites
inline void PresentationView();
```

Clears screen, hides cursor, draws background with left/right arcade sprites, then animates the title characters with a yellow-to-red gradient over 100 frames.

---

### `Views/PasswordView.h`

```cpp
/// @brief Renders the password input screen with label and message
inline void PasswordView();
```

Draws background, title component, and a text box or input component depending on `BLOCKED` state and `HIDDEN_PASSWORD` setting. When `BLOCKED` is true, uses `TextBoxComponent` (read-only display); otherwise uses `InputComponent` (interactive).

---

### `Views/MainMenuView.h`

```cpp
/// @brief Renders the game selection menu using SelectComponent
inline void MainMenuView();
```

Draws background, title, and a `SelectComponent` centered on screen with the available game options. The selected option is stored in `OPTION`.

---

### `Views/WrongPasswordView.h`

```cpp
/// @brief Displays the lockout message after max failed password attempts
inline void WrongPasswordView();
```

Shows a centered message: "Intentó 3 veces ingresar con una clave incorrecta. Comuníquese con el administrador."

---

### `Commands/Auth.h`

```cpp
/// @brief Verifies if the current input matches the stored password
/// @return true if INPUT equals CLAVE, false otherwise
inline bool isValidPassword();
```

Simple comparison of `INPUT` against `CLAVE`.

---

### `Components/TitleComponent.h`

```cpp
/// @brief Calculates the X position for a title character line
/// @param title Array of title font strings
/// @param i Index of the line to calculate
/// @return Horizontal position centered on screen
inline int calculateTitleX(
    std::array<std::string, 9> title,
    int i
);

/// @brief Calculates the Y position for a title character line
/// @param title Array of title font strings
/// @param i Index of the line to calculate
/// @return Vertical position relative to screen
inline int calculateTitleY(
    std::array<std::string, 9> title,
    int i
);

/// @brief Renders the "RETRORCH." title with gradient colors
inline void TitleComponent();
```

Renders each of the 9 title font characters vertically with a yellow-to-red gradient.

---

### `Database/Options.h`

```cpp
/// @brief Current selected option index (mutable)
inline int OPTION = 0;

/// @brief Available menu options
const std::vector<std::string> OPTIONS = {
    "Pokemon",
    "Buscaminas",
    "Batalla Naval",
    "Tic Tac Toe",
    "Invasores Espaciales",
    "Creditos"
};
```

---

### `Database/Labels.h`

```cpp
/// @brief Prompt label for password input
const std::string INPUT_LABEL = "Ingrese su contraseña:";

/// @brief Message shown on wrong password
const std::string WRONG_PASSWORD_MESSAGE = "Clave incorrecta. Intente de nuevo.";

/// @brief Message shown on successful authentication
const std::string AUTH_SUCCESS_MESSAGE = "Clave correcta.";
```

---

### `Database/Env.h`

```cpp
/// @brief The correct password
const std::string CLAVE = "1234";

/// @brief Current user input (mutable)
inline std::string INPUT = "";

/// @brief Current displayed message (mutable)
inline std::string MESSAGE = "";

/// @brief Label for input component
const std::string LABEL = INPUT_LABEL;

/// @brief Maximum number of password attempts
const int MAX_ATTEMPTS = 3;

/// @brief Maximum password input length
const int MAX_PASSWORD_LEN = 24;

/// @brief Whether input is blocked (read-only mode, mutable)
inline bool BLOCKED = false;

/// @brief Whether password is hidden with mask characters (mutable)
inline bool HIDDEN_PASSWORD = true;

/// @brief Character used to mask hidden password input
const std::string HIDDEN_CHAR = "*";
```

---

### `Sprites/ArcadeLeft.h`

```cpp
/// @brief Left arcade cabinet ANSI truecolor sprite (precomputed, zero runtime cost)
inline const std::vector<std::string> ArcadeLeft = { ... };
```

---

### `Sprites/ArcadeRight.h`

```cpp
/// @brief Right arcade cabinet ANSI truecolor sprite (precomputed, zero runtime cost)
inline const std::vector<std::string> ArcadeRight = { ... };
```

---

## Data Flow

```
PresentationView
    ↓
PasswordView (loop up to MAX_ATTEMPTS)
    ↓
isValidPassword() → INPUT == CLAVE
    ├─ true  → Show success message (1s countdown)
    │         → TransitionComponent
    │         → MainMenuView
    │         → User selects option → Launch Game
    └─ false → WrongPasswordView (lockout)
```

---

## Game Options

| Index | Option | Game |
|-------|--------|------|
| 0 | `Pokemon` | Pokemon battle game |
| 1 | `Buscaminas` | Minesweeper |
| 2 | `Batalla Naval` | Battleship |
| 3 | `Tic Tac Toe` | Tic Tac Toe |
| 4 | `Invasores Espaciales` | Space invaders |
| 5 | `Creditos` | Credits screen |

---

## Platform Notes

- Cross-platform (uses Common library abstractions)
- ANSI truecolor sprites for terminal rendering
- UTF-8 enabled at startup via `Common::EnableUTF8()`

---

## See Also

- [Common Library](../CommonDOCS.md)
- [Pokemon](Pokemon.md)
- [Buscaminas](Buscaminas.md)
- [Batalla Naval](BatallaNaval.md)
- [Tic Tac Toe](Tictactoe.md)
- [Invasión Espacial](InvasionEspacial.md)
