# Tests

> Directory: `Tests/`

## Overview
Test files for Common utilities, game modules, and MainMenu.

---

## Test Files

| File | Tests | Dependencies |
|------|-------|-------------|
| `ColorTest.cpp` | `Common/Color.h` RGB colors and gradients | |
| `ComponentTest.cpp` | UI components | |
| `FontTest.cpp` | `Common/Font.h` fonts and ConcatFont | |
| `GraphicsTest.cpp` | `Common/Graphics.h` drawing functions | |
| `InputTest.cpp` | `Common/Input.h` input parsing | |
| `MusicTest.cpp` | `Common/Music.h` audio playback | |
| `PokemonTest.cpp` | Pokemon module | |
| `PokemonViewTest.cpp` | Pokemon views | |
| `MainMenuTest.cpp` | MainMenu module | |
| `MenuViewTest.h` | Menu view test (header-only) | |
| `MinesweeperTest.h` | Minesweeper board test (header-only) | |
| `TestingGradients.cpp` | Color gradients | |
| `test_simple.cpp` | Simple compilation test | |
| `test_titleview_compilation.cpp` | TitleView compilation | |
| `test_pokemon_interfaces.cpp` | Pokemon interfaces | |

---

## Test Data

| File | Purpose |
|------|---------|
| `arceus.h` | Pokemon test sprite |
| `rayquaza.h` | Pokemon test sprite |
| `audio.ogg` | Audio test file |
| `Sound.mp3` | Audio test file |

---

## Running Tests

```bash
# Compile and run a test
g++ -std=c++17 -I../Common Tests/ColorTest.cpp -o test_color
./test_color
```

---

## Notes

- Tests are manual compilation (no test framework)
- Each test file is standalone
- Some tests are header-only (`.h` files included in other tests)
