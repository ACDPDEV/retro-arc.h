# Invasión Espacial

> Namespace: `InvasionEspacial` | Entry: `Juegos/Invasion Espacial/main.cpp`

## Overview

Space invaders game with double-buffering, multiple enemy types, and boss battles. Windows-only legacy implementation using Win32 Console API.

---

## Files

| File | Purpose |
|------|---------|
| `consola2.h` | Console abstraction with double-buffering, screen utilities |
| `figuras.h` | All game sprites/figures (player, enemies, bullets, UI) |
| `movimientos.h` | Movement logic for player and enemies |
| `disparos.h` | Shooting mechanics for player and enemies |
| `colisiones.h` | Collision detection between all entities |
| `juego.h` | Main game loop, state management, HUD |
| `pantallas.h` | Screen rendering (menus, transitions, game over) |
| `main.cpp` | Entry point (currently integrated with PROC1 main) |

---

## Architecture

### Double-Buffering System

The game uses a custom double-buffering system to prevent flicker:

1. Two console screen buffers are created (`bufferJuego[0]`, `bufferJuego[1]`)
2. Drawing operations write to a hidden buffer via `CHAR_INFO cuadro[]`
3. `mostrarFrame()` swaps the visible buffer atomically using `WriteConsoleOutputA`
4. Each frame: clear → update → draw → swap

### Entity-Based Design

```
Entities:
├── Player (xJugador, yJugador)
├── Meteors (xMeteorito1/2/3, yMeteorito1/2/3)
├── UFOs (xOvni1/2, yOvni1/2)
├── Boss (xJefe, yJefe)
└── Projectiles (xBalaJugador, xBalaOvni1/2, xLaser1/2)
```

### Screen Management

The game has multiple screens that transition via `pantallas.h`:
- Presentation (animated title + loading bar)
- Access code screen (password: "1234")
- Welcome screen (animated ship arrival)
- Main menu (4 options)
- Game loop
- Game Over / Victory

---

## Dependencies

| Utility | File | Usage |
|---------|------|-------|
| None | - | This game doesn't use Common library |

All functions are self-contained within the `Juegos/Invasion Espacial/` directory.

---

## Constants

### Screen (`consola2.h`)

| Constant | Value | Description |
|----------|-------|-------------|
| `ANCHO_PANTALLA` | 200 | Console width (columns) |
| `ALTO_PANTALLA` | 60 | Console height (rows) |

### Game Configuration (`juego.h`)

| Constant | Value | Description |
|----------|-------|-------------|
| `VIDAS_INICIALES` | 5 | Starting lives |
| `PUNTOS_METEORITO` | 10 | Points per meteor |
| `PUNTOS_OVNI1` | 20 | Points per UFO type 1 |
| `PUNTOS_OVNI2` | 40 | Points per UFO type 2 |
| `PUNTOS_JEFE` | 100 | Points for boss kill |
| `DURACION_EXPLOSION` | 8 | Frames explosion lasts |
| `DURACION_INVULNERABILIDAD` | 20 | Frames of invincibility after hit |
| `VIDA_INICIAL_JEFE` | 5 | Boss HP |

### Movement (`movimientos.h`)

| Constant | Value | Description |
|----------|-------|-------------|
| `VELOCIDAD_JUGADOR` | 6 | Columns moved per keypress |

### Collision (`colisiones.h`)

| Constant | Value | Description |
|----------|-------|-------------|
| `ANCHO_JUGADOR` | 40 | Player hitbox width |
| `ALTO_JUGADOR` | 17 | Player hitbox height |
| `ANCHO_METEORITO1` | 14 | Meteor type 1 hitbox width |
| `ALTO_METEORITO1` | 10 | Meteor type 1 hitbox height |
| `ANCHO_METEORITO2` | 19 | Meteor type 2 hitbox width |
| `ALTO_METEORITO2` | 11 | Meteor type 2 hitbox height |
| `ANCHO_METEORITO3` | 23 | Meteor type 3 hitbox width |
| `ALTO_METEORITO3` | 13 | Meteor type 3 hitbox height |
| `ANCHO_OVNI1` | 27 | UFO type 1 hitbox width |
| `ALTO_OVNI1` | 10 | UFO type 1 hitbox height |
| `ANCHO_OVNI2` | 44 | UFO type 2 hitbox width |
| `ALTO_OVNI2` | 14 | UFO type 2 hitbox height |
| `ANCHO_JEFE` | 51 | Boss hitbox width |
| `ALTO_JEFE` | 19 | Boss hitbox height |
| `MARGEN_PRECISION` | 4 | Collision tolerance (pixels) |

---

## Key Functions

### consola2.h — Console & Double-Buffer

```cpp
/// @brief Returns the active console handle (double-buffered or standard)
/// @return HANDLE to current console buffer
HANDLE handleActivo();

/// @brief Writes a character to the in-memory frame buffer with bounds checking
/// @param x Column position
/// @param y Row position
/// @param c Character to write
/// @param atributo Windows console color attribute
void escribirCelda(int x, int y, char c, WORD atributo);

/// @brief Creates two console buffers and enables double-buffering mode
void iniciarDobleBuffer();

/// @brief Swaps visible buffer and commits the hidden buffer to screen
void mostrarFrame();

/// @brief Disables double-buffering and returns to standard console
void finalizarDobleBuffer();

/// @brief Clears the entire hidden buffer (or standard console if not double-buffered)
void limpiarPantallaCompleta();

/// @brief Generic print function that replaces cout << for double-buffer compatibility
/// @param valor Value to print (converted to string via ostringstream)
template <typename T>
void imprimir(const T& valor);

/// @brief Sets the current text color attribute
/// @param c Color code (0-15, Windows console attributes)
void color(int c);

/// @brief Moves cursor to position (sets cursorX/cursorY in double-buffer, or calls Win32 API)
/// @param x Column position
/// @param y Row position
void gotoxy(int x, int y);

/// @brief Configures console window size (200x60), title, and hides cursor
void configurarPantalla();

/// @brief Hides the console cursor
void ocultarCursor();

/// @brief Shows the console cursor
void mostrarCursor();

/// @brief Clears a rectangular zone of the console
/// @param x Left column
/// @param y Top row
/// @param ancho Width
/// @param alto Height
void limpiarZona(int x, int y, int ancho, int alto);

/// @brief Writes text character by character with sound effect and delay
/// @param x Column position
/// @param y Row position
/// @param texto Text to write
/// @param velocidad Delay between characters (ms)
void escribirTexto(int x, int y, string texto, int velocidad);

/// @brief Draws a loading bar with percentage display
/// @param x Column position
/// @param y Row position
void barraCarga(int x, int y);

/// @brief Renders animated starfield background (created once, updated each call)
void fondoEspacialAnimado();
```

### figuras.h — Sprites & Figures

```cpp
/// @brief Draws the player spaceship at position (x, y)
/// @param x Column position
/// @param y Row position
void dibujarJugador(int x, int y);

/// @brief Erases the player spaceship (draws spaces over 23 rows)
/// @param x Column position
/// @param y Row position
void borrarJugador(int x, int y);

/// @brief Draws meteor type 1 (small, 10 rows)
/// @param x Column position
/// @param y Row position
void dibujarMeteorito1(int x, int y);

/// @brief Erases meteor type 1
void borrarMeteorito1(int x, int y);

/// @brief Draws meteor type 2 (medium, 11 rows)
/// @param x Column position
/// @param y Row position
void dibujarMeteorito2(int x, int y);

/// @brief Erases meteor type 2
void borrarMeteorito2(int x, int y);

/// @brief Draws meteor type 3 (large, 13 rows)
/// @param x Column position
/// @param y Row position
void dibujarMeteorito3(int x, int y);

/// @brief Erases meteor type 3
void borrarMeteorito3(int x, int y);

/// @brief Draws UFO type 1 (10 rows, red)
/// @param x Column position
/// @param y Row position
void dibujarOvni1(int x, int y);

/// @brief Erases UFO type 1
void borrarOvni1(int x, int y);

/// @brief Draws UFO type 2 (14 rows, red)
/// @param x Column position
/// @param y Row position
void dibujarOvni2(int x, int y);

/// @brief Erases UFO type 2
void borrarOvni2(int x, int y);

/// @brief Draws the final boss (mothership, 19 rows, magenta)
/// @param x Column position
/// @param y Row position
void dibujarJefeFinal(int x, int y);

/// @brief Erases the final boss
void borrarJefeFinal(int x, int y);

/// @brief Draws player bullet (3 rows, cyan)
/// @param x Column position
/// @param y Row position
void dibujarBalaJugador(int x, int y);

/// @brief Erases player bullet
void borrarBalaJugador(int x, int y);

/// @brief Draws UFO bullet (3 rows, red)
/// @param x Column position
/// @param y Row position
void dibujarBalaOvni(int x, int y);

/// @brief Erases UFO bullet
void borrarBalaOvni(int x, int y);

/// @brief Draws boss laser (5 rows, yellow)
/// @param x Column position
/// @param y Row position
void dibujarLaserJefe(int x, int y);

/// @brief Erases boss laser
void borrarLaserJefe(int x, int y);

/// @brief Draws explosion animation frame 1 (5 rows, yellow)
/// @param x Column position
/// @param y Row position
void dibujarExplosion1(int x, int y);

/// @brief Erases explosion 1
void borrarExplosion1(int x, int y);

/// @brief Draws explosion animation frame 2 (5 rows, red)
/// @param x Column position
/// @param y Row position
void dibujarExplosion2(int x, int y);

/// @brief Erases explosion 2
void borrarExplosion2(int x, int y);

/// @brief Draws explosion animation frame 3 (5 rows, gray)
/// @param x Column position
/// @param y Row position
void dibujarExplosion3(int x, int y);

/// @brief Erases explosion 3
void borrarExplosion3(int x, int y);

/// @brief Draws a heart (life icon, 5 rows, red)
/// @param x Column position
/// @param y Row position
void dibujarVida(int x, int y);

/// @brief Erases heart icon
void borrarVida(int x, int y);

/// @brief Draws a broken heart (5 rows, red)
/// @param x Column position
/// @param y Row position
void dibujarVidaRota(int x, int y);

/// @brief Erases broken heart
void borrarVidaRota(int x, int y);

/// @brief Draws the victory trophy (20 rows, gold)
/// @param x Column position
/// @param y Row position
void dibujarCopa(int x, int y);

/// @brief Erases victory trophy
void borrarCopa(int x, int y);

/// @brief Draws the animated game title "INVASION ESPACIAL" with sound
void dibujarTitulo();

/// @brief Displays game over screen with score
/// @param usuario Player username
/// @param puntaje Final score
void gameOver(string usuario, int puntaje);

/// @brief Displays victory screen with score
/// @param usuario Player username
/// @param puntaje Final score
void victoria(string usuario, int puntaje);
```

### movimientos.h — Movement

```cpp
/// @brief Handles player input (arrows + space) and updates position
/// @param x Player X position (reference, modified)
/// @param y Player Y position
/// @param xBala Bullet X position (reference)
/// @param yBala Bullet Y position (reference)
/// @param disparando Shooting state (reference)
void moverJugador(int &x, int y, int &xBala, int &yBala, bool &disparando);

/// @brief Moves meteor type 1 downward (1 row every 3 frames)
/// @param x Meteor X position (reference, modified)
/// @param y Meteor Y position (reference, modified)
/// @param escapo Set to true if meteor escaped bottom
void moverMeteorito1(int &x, int &y, bool &escapo);

/// @brief Moves meteor type 2 downward (1 row every 2 frames)
/// @param x Meteor X position (reference, modified)
/// @param y Meteor Y position (reference, modified)
/// @param escapo Set to true if meteor escaped bottom
void moverMeteorito2(int &x, int &y, bool &escapo);

/// @brief Moves meteor type 3 downward (1 row every 2 frames)
/// @param x Meteor X position (reference, modified)
/// @param y Meteor Y position (reference, modified)
/// @param escapo Set to true if meteor escaped bottom
void moverMeteorito3(int &x, int &y, bool &escapo);

/// @brief Moves UFO type 1 with horizontal bouncing and slow descent
/// @param x UFO X position (reference, modified)
/// @param y UFO Y position (reference, modified)
/// @param direccion Horizontal direction (1=right, -1=left, reference)
void moverOvni1(int &x, int &y, int &direccion);

/// @brief Moves UFO type 2 with horizontal bouncing and slower descent
/// @param x UFO X position (reference, modified)
/// @param y UFO Y position (reference, modified)
/// @param direccion Horizontal direction (reference)
void moverOvni2(int &x, int &y, int &direccion);

/// @brief Moves boss horizontally with bouncing (no vertical movement)
/// @param x Boss X position (reference, modified)
/// @param y Boss Y position
/// @param direccion Horizontal direction (reference)
void moverJefe(int &x, int &y, int &direccion);
```

### disparos.h — Shooting

```cpp
/// @brief Fires a bullet from the player's position
/// @param xJugador Player X position
/// @param yJugador Player Y position
/// @param xBala Bullet X position (reference, set to player center)
/// @param yBala Bullet Y position (reference, set to player Y)
/// @param disparando Shooting state (reference, set to true)
void dispararJugador(int xJugador, int yJugador,
                     int &xBala, int &yBala,
                     bool &disparando);

/// @brief Moves player bullet upward (2 rows/frame), deactivates at top
/// @param x Bullet X position (reference)
/// @param y Bullet Y position (reference, modified)
/// @param disparando Shooting state (reference, set false when off-screen)
void moverBalaJugador(int &x, int &y, bool &disparando);

/// @brief Fires UFO type 1 bullet (random chance: 1/120 per frame)
/// @param xOvni UFO X position
/// @param yOvni UFO Y position
/// @param xBala Bullet X position (reference)
/// @param yBala Bullet Y position (reference)
/// @param disparando Shooting state (reference)
void dispararOvni1(int xOvni, int yOvni,
                   int &xBala, int &yBala,
                   bool &disparando);

/// @brief Moves UFO type 1 bullet downward (1 row/frame)
/// @param x Bullet X position (reference)
/// @param y Bullet Y position (reference)
/// @param disparando Shooting state (reference)
void moverBalaOvni1(int &x, int &y, bool &disparando);

/// @brief Fires UFO type 2 bullet (random chance: 1/70 per frame, more frequent)
/// @param xOvni UFO X position
/// @param yOvni UFO Y position
/// @param xBala Bullet X position (reference)
/// @param yBala Bullet Y position (reference)
/// @param disparando Shooting state (reference)
void dispararOvni2(int xOvni, int yOvni,
                   int &xBala, int &yBala,
                   bool &disparando);

/// @brief Moves UFO type 2 bullet downward (2 rows/frame, faster)
/// @param x Bullet X position (reference)
/// @param y Bullet Y position (reference)
/// @param disparando Shooting state (reference)
void moverBalaOvni2(int &x, int &y, bool &disparando);

/// @brief Fires boss dual lasers (random chance: 1/50 per frame)
/// @param xJefe Boss X position
/// @param yJefe Boss Y position
/// @param xLaser1 Left laser X position (reference)
/// @param yLaser1 Left laser Y position (reference)
/// @param xLaser2 Right laser X position (reference)
/// @param yLaser2 Right laser Y position (reference)
/// @param disparando Shooting state (reference)
void dispararJefeFinal(int xJefe, int yJefe,
                       int &xLaser1, int &yLaser1,
                       int &xLaser2, int &yLaser2,
                       bool &disparando);

/// @brief Moves both boss lasers downward (2 rows/frame)
/// @param xLaser1 Left laser X position (reference)
/// @param yLaser1 Left laser Y position (reference)
/// @param xLaser2 Right laser X position (reference)
/// @param yLaser2 Right laser Y position (reference)
/// @param disparando Shooting state (reference)
void moverLaserJefe(int &xLaser1, int &yLaser1,
                    int &xLaser2, int &yLaser2,
                    bool &disparando);
```

### colisiones.h — Collision Detection

```cpp
/// @brief Checks bullet-meteor type 1 collision with precision margin
bool colisionBalaMeteorito1(int xBala, int yBala,
                            int xMeteorito, int yMeteorito);

/// @brief Checks bullet-meteor type 2 collision with precision margin
bool colisionBalaMeteorito2(int xBala, int yBala,
                            int xMeteorito, int yMeteorito);

/// @brief Checks bullet-meteor type 3 collision with precision margin
bool colisionBalaMeteorito3(int xBala, int yBala,
                            int xMeteorito, int yMeteorito);

/// @brief Checks bullet-UFO type 1 collision with precision margin
bool colisionBalaOvni1(int xBala, int yBala,
                       int xOvni, int yOvni);

/// @brief Checks bullet-UFO type 2 collision with precision margin
bool colisionBalaOvni2(int xBala, int yBala,
                       int xOvni, int yOvni);

/// @brief Checks bullet-boss collision with precision margin
bool colisionBalaJefeFinal(int xBala, int yBala,
                           int xJefe, int yJefe);

/// @brief Checks player-meteor type 1 collision (AABB)
bool colisionJugadorMeteorito1(int xJugador, int yJugador,
                               int xMeteorito, int yMeteorito);

/// @brief Checks player-meteor type 2 collision (AABB)
bool colisionJugadorMeteorito2(int xJugador, int yJugador,
                               int xMeteorito, int yMeteorito);

/// @brief Checks player-meteor type 3 collision (AABB)
bool colisionJugadorMeteorito3(int xJugador, int yJugador,
                               int xMeteorito, int yMeteorito);

/// @brief Checks player-UFO type 1 collision (AABB)
bool colisionJugadorOvni1(int xJugador, int yJugador,
                          int xOvni, int yOvni);

/// @brief Checks player-UFO type 2 collision (AABB)
bool colisionJugadorOvni2(int xJugador, int yJugador,
                          int xOvni, int yOvni);

/// @brief Checks player-UFO bullet collision (AABB)
bool colisionJugadorBalaOvni(int xJugador, int yJugador,
                             int xBala, int yBala);

/// @brief Checks player-boss laser collision (AABB)
bool colisionJugadorLaserJefe(int xJugador, int yJugador,
                              int xLaser, int yLaser);
```

### juego.h — Game Loop & State

```cpp
/// @brief Generates random X position for meteor spawn
int posicionAleatoriaMeteorito();

/// @brief Generates random X position for UFO type 1 spawn
int posicionAleatoriaOvni1();

/// @brief Generates random X position for UFO type 2 spawn
int posicionAleatoriaOvni2();

/// @brief Generates random X position for boss spawn
int posicionAleatoriaJefe();

/// @brief Initializes all game state variables (player, enemies, projectiles, scores)
void inicializarJuego();

/// @brief Draws the HUD (lives, score, level) with borders
void mostrarHUD();

/// @brief Checks all collisions and updates game state (damage, score, explosions)
void verificarColisions();

/// @brief Updates explosion animations and respawns destroyed enemies
void actualizarExplosiones();

/// @brief Updates game level based on score thresholds (100/250/500)
void actualizarNivel();

/// @brief Main update function: moves all entities, updates bullets, manages invulnerability
void actualizarJuego();

/// @brief Draws the current game frame (calls mostrarHUD)
void dibujarJuego();

/// @brief Executes the full game session: init → game loop → end screen
/// @param usuario Player username
void ejecutarJuego(string usuario);
```

### pantallas.h — Screen Management

```cpp
/// @brief Displays animated title screen with loading bar
void presentacion();

/// @brief Access code screen (password: "1234", 3 attempts)
/// @return true if correct code entered, false otherwise
bool clave();

/// @brief Requests player username from input
/// @return Entered username or "COMANDANTE" if empty
string solicitarUsuario();

/// @brief Welcome screen with animated ship arrival
/// @param usuario Player username
void bienvenida(string usuario);

/// @brief Displays access denied message after 3 failed attempts
void claveIncorrecta();

/// @brief Main menu with 4 options (Play, Instructions, Credits, Exit)
/// @param usuario Player username
void menu(string usuario);

/// @brief Displays game instructions (controls, objective)
void instrucciones();

/// @brief Displays credits screen
void creditos();

/// @brief Goodbye screen with animated ship departure
/// @param usuario Player username
void despedida(string usuario);
```

---

## Data Flow

```
Game Loop (ejecutarJuego):
│
├── inicializarJuego()           ← Reset all state
├── iniciarDobleBuffer()         ← Create Win32 buffers
│
└── while (vidas > 0 && !juegoVictoria)
    │
    ├── limpiarPantallaCompleta()
    │
    ├── actualizarJuego()
    │   ├── moverJugador()        ← Input + position update
    │   ├── moverMeteorito1/2/3() ← Enemy descent
    │   ├── moverOvni1/2()        ← Enemy movement
    │   ├── dispararOvni1/2()     ← Enemy shooting
    │   ├── moverBalaOvni1/2()    ← Enemy bullet movement
    │   ├── moverJefe()           ← Boss movement
    │   ├── dispararJefeFinal()   ← Boss shooting
    │   ├── moverLaserJefe()      ← Boss laser movement
    │   └── moverBalaJugador()    ← Player bullet movement
    │
    ├── verificarColisiones()     ← All collision checks
    │   ├── Bullet vs Enemies     → Score + explosion trigger
    │   └── Player vs Enemies/Bullets → Life loss + invulnerability
    │
    ├── actualizarExplosiones()   ← Animation frames + respawn
    │
    ├── actualizarNivel()         ← Score → Level progression
    │   ├── Level 1: 0-99 pts    → Meteors only
    │   ├── Level 2: 100-249 pts → + UFO type 1
    │   ├── Level 3: 250-499 pts → + UFO type 2
    │   └── Level 4: 500+ pts    → + Boss
    │
    ├── dibujarJuego()            ← Render HUD
    │
    └── mostrarFrame()            ← Swap buffers (atomic)
```

---

## Platform Notes

- **Windows-only**: Uses Win32 Console API (`CreateConsoleScreenBuffer`, `WriteConsoleOutputA`, `SetConsoleCursorPosition`)
- **Double-buffering**: `HANDLE bufferJuego[2]` with `CHAR_INFO cuadro[]` for flicker-free rendering
- **Input**: Uses `<conio.h>` (`kbhit()`, `getch()`) for non-blocking keyboard input
- **Sound**: Uses `Beep(frequency, duration)` for sound effects
- **Console size**: Fixed at 200 columns × 60 rows
- **Not cross-platform**: Cannot compile on Linux/macOS without significant changes

---

## Level Progression

| Level | Score Threshold | Enemies Active |
|-------|-----------------|----------------|
| 1 | 0-99 | Meteors (3 types) |
| 2 | 100-249 | + UFO Type 1 |
| 3 | 250-499 | + UFO Type 2 |
| 4 | 500+ | + Final Boss (5 HP) |

---

## Entity Speeds

| Entity | Vertical Speed | Horizontal |
|--------|----------------|------------|
| Meteor 1 | 1 row / 3 frames | None |
| Meteor 2 | 1 row / 2 frames | None |
| Meteor 3 | 1 row / 2 frames | None |
| UFO 1 | 1 row / 2 frames | Bouncing |
| UFO 2 | 1 row / 3 frames | Bouncing |
| Boss | 0 | Bouncing |
| Player Bullet | 2 rows/frame up | None |
| UFO 1 Bullet | 1 row/frame down | None |
| UFO 2 Bullet | 2 rows/frame down | None |
| Boss Laser | 2 rows/frame down | None |

---

## See Also

- [Common Library](../CommonDOCS.md)
- [MainMenu](MainMenu.md)
