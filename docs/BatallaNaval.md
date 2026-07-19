# Batalla Naval

> Namespace: `BatallaNaval` | Entry: `Juegos/BatallaNaval/b_n_4.cpp`

## Overview

Simple battleship game implemented in legacy C++ style. Does not use Common utilities.

Single-file procedural implementation (no namespaces, no OOP). Contains all game logic,
board representation, ship placement, shot handling, and display in one translation unit.

---

## Files

| File | Purpose |
|------|---------|
| `b_n_4.cpp` | Main game file with all logic |

---

## Architecture

Legacy procedural style — no namespaces, no OOP. Single file contains:

- **Board representation**: 10×10 `int` grid (`tablero[10][10]`)
- **Ship placement**: Hardcoded positions (horizontal + vertical, both size 5)
- **Shot logic**: Coordinate input, validation, hit/miss detection
- **Display functions**: Board rendering via `dibujarTablero()`

### Board Cell Values

| Value | Meaning | Display |
|-------|---------|---------|
| `0` | Empty water | `~` |
| `1` | Ship segment | `B` |
| `2` | Miss (shot at water) | `o` |
| `3` | Hit (shot at ship) | `X` |

### Ship Configuration

| Ship | Start Position | Size | Direction |
|------|---------------|------|-----------|
| Ship 1 | Row 3, Col 6 | 5 | Horizontal (→) |
| Ship 2 | Row 4, Col 5 | 5 | Vertical (↓) |

---

## Dependencies

| Utility | File | Usage |
|---------|------|-------|
| None | — | This game doesn't use Common library |

Uses only `<iostream>` from the C++ standard library.

---

## Key Functions

### `dibujarTablero`

```cpp
void dibujarTablero(int tablero[filas][columnas]);
```

Renders the 10×10 game board to the console. Iterates through every cell and prints
the corresponding symbol based on the cell's state (water, ship, miss, hit).

**Parameters:**
- `tablero` — 10×10 integer grid representing the game board

**Display logic per cell:**
| Cell Value | Output | Meaning |
|------------|--------|---------|
| `0` | `~   ` | Empty water |
| `1` | `B   ` | Ship |
| `2` | `o   ` | Miss |
| `3` | `X   ` | Hit |

---

## Data Flow

```
User Input → Validate Coordinates → Check Hit/Miss → Update Board → Redraw
```

### Detailed Flow

1. **Initialize** — 10×10 grid filled with `0` (water)
2. **Place ships** — Two size-5 ships placed at hardcoded positions
3. **Draw initial board** — Call `dibujarTablero()`
4. **Game loop** — Repeat until all ships sunk:
   - Prompt for row (0–9) with validation loop
   - Prompt for column (0–9) with validation loop
   - Check cell state:
     - `0` (water) → set to `2` (miss), print "Agua."
     - `1` (ship) → set to `3` (hit), increment hit counter, print "Impacto!"
     - else → print "Ya se disparó aquí."
   - Redraw board
5. **Victory** — Print win message when loop exits

---

## Platform Notes

- Uses `cin`/`cout` for I/O
- Cross-platform (no platform-specific code)
- Legacy style (not using Common's terminal abstraction)
- Uses `using namespace std;` (legacy convention)
- Global constants for board dimensions (`filas = 10`, `columnas = 10`)

---

## Known Issues

The variable `aciertosTotales` is initialized to `0`, making the game loop condition
`aciertosActuales < aciertosTotales` immediately false (0 < 0). The game loop never
executes, and the player sees the victory message on start without playing.

---

## See Also

- [Common Library](../CommonDOCS.md)
- [MainMenu](MainMenu.md)
