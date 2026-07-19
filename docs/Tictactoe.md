# Tic Tac Toe

> Namespace: `Tictactoe` | Entry: `Juegos/Tictactoe/main.cpp`

## Overview
Tic Tac Toe game with two modes: original and football variant. Windows-only legacy implementation.

## Files
| File | Purpose |
|------|---------|
| `console.h` / `console.cpp` | Console I/O utilities (gotoxy, color, pause) |
| `game.h` / `game.cpp` | Game logic and UI |
| `main.cpp` | Entry point with main menu |
| `Makefile.win` | Windows build file |
| `TicTacToeFutbol.dev` / `.layout` | Dev-C++ project and layout files |

## Architecture
- Console module handles Win32 API interactions (cursor positioning, color, hiding cursor)
- Game module contains all game logic, UI rendering, and quiz system for football mode
- Main entry point provides a loop-based menu for mode selection

### Game Modes
- **Original**: Standard Tic Tac Toe — two players alternate placing X and O
- **Football**: Players answer football trivia questions to earn the right to place a piece; wrong answer loses the turn

## Dependencies
| Utility | File | Usage |
|---------|------|-------|
| None | - | This game does not use the Common library |

> Note: This is a standalone legacy module. It uses `<windows.h>`, `<conio.h>`, and `<stdio.h>` directly.

## Key Functions

### console.h / console.cpp
| Function | Signature | Description |
|----------|-----------|-------------|
| `gotoxy` | `void gotoxy(int x, int y)` | Positions the console cursor at coordinates (x, y) |
| `OcultarCursor` | `void OcultarCursor()` | Hides the console cursor |
| `color` | `void color(int color)` | Sets the console text color |
| `pausa` | `void pausa(int tiempo)` | Pauses execution for `tiempo` milliseconds via `Sleep()` |

### game.h / game.cpp
| Function | Signature | Description |
|----------|-----------|-------------|
| `menuPrincipal` | `void menuPrincipal()` | Displays the main menu (Original / Football / Exit) |
| `inicializarJuego` | `void inicializarJuego()` | Initializes the board with spaces, borders, and numbers, then renders it |
| `jugarOriginal` | `void jugarOriginal()` | Runs a full original mode game loop (instructions → game → result → exit) |
| `jugarFutbol` | `void jugarFutbol()` | Runs a full football mode game loop (instructions → quiz-based game → result) |
| `mostrar_Instrucciones` | `void mostrar_Instrucciones()` | Shows original mode instructions |
| `mostrar_InstruccionesFutbol` | `void mostrar_InstruccionesFutbol()` | Shows football mode instructions |
| `mostrar_tablero` | `void mostrar_tablero()` | Renders the 11×11 board array to the console with colored pieces |
| `turnoX` | `void turnoX()` | Handles player X's turn (input → validate → place → render) |
| `turnoO` | `void turnoO()` | Handles player O's turn |
| `turnoFutbolX` | `void turnoFutbolX()` | Handles player X's turn in football mode (quiz → place) |
| `turnoFutbolO` | `void turnoFutbolO()` | Handles player O's turn in football mode |
| `mostrarResultado` | `void mostrarResultado()` | Displays win/loss/draw result for original mode |
| `ganar` | `bool ganar(char ficha)` | Checks if the given piece (`'X'` or `'O'`) has won |
| `tableroLleno` | `bool tableroLleno()` | Returns true if all 9 cells are occupied (draw) |
| `agregarFicha` | `void agregarFicha(char pos, char ficha)` | Places a piece on the board at position `'1'`–`'9'` |
| `celdaVacia` | `bool celdaVacia(char tecla)` | Validates that a cell position is unoccupied |
| `jugarNuevamente` | `bool jugarNuevamente()` | Prompts user to play again (S/N) |
| `preguntaFutbol` | `bool preguntaFutbol()` | Randomly selects a quiz question, shows options, returns true if answered correctly |
| `victoriaFutbol` | `void victoriaFutbol()` | Displays the football mode victory screen |
| `despedida` | `void despedida()` | Shows farewell message and waits for keypress |

### Board Helpers
| Function | Signature | Description |
|----------|-----------|-------------|
| `agregar_marco` | `void agregar_marco()` | Populates the board array with border characters (186, 205, 206) |
| `pintarmarco` | `void pintarmarco()` | Draws the outer frame on screen using box-drawing characters |
| `llenar_tablero_con_espacios` | `void llenar_tablero_con_espacios()` | Fills the board array with spaces (ASCII 32) |
| `agregarNumeros` | `void agregarNumeros()` | Places cell numbers `'1'`–`'9'` at their grid positions |
| `mostrarPanelQuiz` | `void mostrarPanelQuiz()` | Displays the quiz panel title |
| `dibujarPanelQuiz` | `void dibujarPanelQuiz()` | Draws the quiz panel border and title |
| `limpiarPanelQuiz` | `void limpiarPanelQuiz()` | Clears the quiz panel interior and redraws its border |

## Data Flow
```
Main Menu → Mode Selection → Game Loop → Input → Update Board → Check Win → Display
                  │
          ┌───────┴───────┐
          ▼               ▼
    Original Mode    Football Mode
    (direct play)    (quiz → play)
```

## Global State
| Variable | Type | Scope | Description |
|----------|------|-------|-------------|
| `tablero` | `char[11][11]` | `main.cpp` (extern in `game.h`) | The game board array |
| `preguntas` | `string[30]` | `game.cpp` | Football trivia questions |
| `opcionA–D` | `string[30]` each | `game.cpp` | Quiz answer options |
| `respuestaCorrecta` | `char[30]` | `game.cpp` | Correct answer key (`'A'`–`'D'`) |
| `usada` | `bool[30]` | `game.cpp` | Tracks which questions have been used |
| `preguntasUsadas` | `int` | `game.cpp` | Counter of questions used in current game |

## Platform Notes
- **Windows-only**: Uses `<windows.h>` and `<conio.h>`
- Not cross-platform
- Win32 Console API for cursor positioning (`SetConsoleCursorPosition`), color (`SetConsoleTextAttribute`), and cursor visibility (`SetConsoleCursorInfo`)
- Uses `Sleep()` for pausing
- Uses `getch()` from `<conio.h>` for unbuffered input
- Box-drawing characters use CP437 codes (186, 201, 205, etc.)

## See Also
- [Common Library](../CommonDOCS.md)
- [MainMenu](MainMenu.md)
