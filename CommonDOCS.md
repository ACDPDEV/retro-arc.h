# Common Library — Mapeo de Funciones

La biblioteca `Common/` es el núcleo cross-platform (Windows/Linux) del proyecto retro-arc.h, bajo el namespace `Common`. Abstrae diferencias de SO (terminal, teclado, audio) y provee constantes, utilidades de entrada, dibujo TUI, componentes de UI y renderizado de sprites ASCII/Unicode. Todos los headers son header-only (`inline`).

---

## Table of Contents

- [1. Constantes y Estado Global](#1-constantes-y-estado-global)
- [2. Keycodes (Platform-Specific)](#2-keycodes-platform-specific)
- [3. Terminal Cross-Platform](#3-terminal-cross-platform)
- [4. Color](#4-color)
- [5. Theme](#5-theme)
- [6. UnicodeGlyphs](#6-unicodeglyphs)
- [7. Font (ASCII Art)](#7-font-ascii-art)
- [8. Utils (String)](#8-utils-string)
- [9. Aligned (Layout)](#9-aligned-layout)
- [10. Input](#10-input)
- [11. Graphics (TUI Drawing)](#11-graphics-tui-drawing)
- [12. Sprites / Animation](#12-sprites--animation)
- [13. Navigation](#13-navigation)
- [14. Audio](#14-audio)
- [15. Output](#15-output)
- [16. Components UI](#16-components-ui)
- [Quick Reference](#quick-reference)
- [Cross-References](#cross-references)
- [Diagrama de Dependencias](#diagrama-de-dependencias)

---

## Quick Reference

Alphabetical index of all functions:

| Function | File | Purpose |
|----------|------|---------|
| `AlignedX` | `Aligned.h` | Calculate X alignment (left/center/right) |
| `AlignedY` | `Aligned.h` | Calculate Y alignment (top/center/bottom) |
| `ArrayToVector` | `Utils.h` | Convert `array<string,9>` to `vector<string>` |
| `CastKeyToString` | `Input.h` | Convert key bytes to printable string |
| `Clear` | `Terminal.h` | Clear entire screen |
| `ClearConsoleLine` | `Terminal.h` | Clear a line by printing spaces |
| `Color` | `Color.h` | Generate ANSI RGB color sequence |
| `ConcatFont` | `Font.h` | Concatenate ASCII art glyphs horizontally (9 or 4 lines) |
| `CutString` | `Utils.h` | Split string into fixed-width segments |
| `DisableTrueColor` | `Terminal.h` | Disable ANSI True Color support |
| `DisableUTF8` | `Terminal.h` | Disable UTF-8 support |
| `DrawAnimatedSprite` | `Sprite.h` | Animate a sequence of sprite frames |
| `DrawBackground` | `Graphics.h` | Fill screen with base background color |
| `DrawBottomBar` | `Components/BottomBar.h` | Draw status bar at screen bottom |
| `DrawBox` | `Graphics.h` | Draw box with predefined border styles |
| `DrawFillRectangle` | `Graphics.h` | Draw filled rectangle with color |
| `DrawLifeBar` | `Components/LifeBar.h` | Draw health bar with gradient |
| `DrawRawBox` | `Graphics.h` | Draw box with custom border characters |
| `DrawRawHorizontalLine` | `Graphics.h` | Draw horizontal line with custom endpoints |
| `DrawRawVerticalLine` | `Graphics.h` | Draw vertical line with custom endpoints |
| `DrawSprite` | `Sprite.h` | Draw a static ASCII sprite |
| `DrawText` | `Graphics.h` | Draw multiline text with color and word wrap |
| `EnableTrueColor` | `Terminal.h` | Enable ANSI True Color (VT100) |
| `EnableUTF8` | `Terminal.h` | Enable UTF-8 encoding support |
| `GetConsoleHeight` | `Terminal.h` | Get terminal height in rows |
| `GetConsoleSize` | `Terminal.h` | Get terminal size as `{width, height}` |
| `GetConsoleWidth` | `Terminal.h` | Get terminal width in columns |
| `Getch` | `Terminal.h` | Read one keypress without blocking |
| `GoToEnd` | `Terminal.h` | Move cursor below the virtual canvas |
| `GoToXY` | `Terminal.h` | Position cursor at absolute coordinates |
| `Gradient` | `Color.h` | Generate color gradient between two RGB values |
| `HideCursor` | `Terminal.h` | Hide the terminal cursor |
| `InitTerminalRawMode` | `Terminal.h` | Enable raw mode for key-by-key reading |
| `Input` | `Input.h` | Read a word from stdin |
| `InputComponent` | `Components/InputComponent.h` | Interactive text input component |
| `InvertString` | `Utils.h` | Reverse a string (ASCII only) |
| `isTransparent` | `Color.h` | Check if a color is `COLOR_DEFAULT` (transparent) |
| `IsActionKey` | `Navigation.h` | Check if key is Enter or Space |
| `IsAlphaNumChar` | `Input.h` | Check if key is alphanumeric |
| `IsAnsiEnabled` | `Terminal.h` | Check if True Color is supported |
| `IsKeyArrowBottom` | `Navigation.h` | Check if key is down arrow |
| `IsKeyArrowLeft` | `Navigation.h` | Check if key is left arrow |
| `IsKeyArrowRight` | `Navigation.h` | Check if key is right arrow |
| `IsKeyArrowTop` | `Navigation.h` | Check if key is up arrow |
| `IsNavigationKey` | `Navigation.h` | Check if key is any arrow key |
| `IsValidChar` | `Input.h` | Validate character against ranges or exact list |
| `KillAudioProcess` | `Music.h` | Kill child audio process (Linux) |
| `Kbhit` | `Terminal.h` | Check if a keypress is available |
| `Length` | `Utils.h` | Get visible width of string (ignoring ANSI/UTF-8) |
| `MaxString` | `Utils.h` | Find longest string in a vector |
| `ParseBool` | `Input.h` | Parse string to bool (`"true"`/`"false"`/`"1"`/`"0"`) |
| `ParseChar` | `Input.h` | Extract first character from string |
| `ParseFloat` | `Input.h` | Parse string to float |
| `ParseInt` | `Input.h` | Parse string to int |
| `ParseIntStrict` | `Input.h` | Parse string to int (strict validation) |
| `PauseAudio` | `Music.h` | Pause audio playback |
| `PlayAudio` | `Music.h` | Play audio file |
| `PlayAudioLoop` | `Music.h` | Play audio file in infinite loop |
| `PrintFeedBackMessage` | `Output.h` | Print user feedback message |
| `PrintPrimaryBox` | `Graphics.h` | Draw decorative box with centered text |
| `ReadConsoleChar` | `Input.h` | Read validated keypress (single byte or multibyte) |
| `RelativeX` | `Aligned.h` | Calculate relative X offset |
| `RelativeY` | `Aligned.h` | Calculate relative Y offset |
| `RepeatString` | `Utils.h` | Repeat string N times |
| `ResetColor` | `Color.h` | Reset terminal colors to default |
| `RestoreTerminalMode` | `Terminal.h` | Restore terminal to original state (Linux) |
| `ResumeAudio` | `Music.h` | Resume paused audio |
| `SelectComponent` | `Components/SelectComponent.h` | Interactive selection menu component |
| `SetCursorVisible` | `Terminal.h` | Show or hide terminal cursor |
| `SetOption` | `Navigation.h` | Update selection index with cyclic navigation |
| `SetTerminalColor` | `Color.h` | Set entire terminal foreground/background color |
| `ShowCursor` | `Terminal.h` | Show the terminal cursor |
| `Sleep` | `Terminal.h` | Sleep current thread for N milliseconds |
| `StaticSelectComponent` | `Components/SelectComponent.h` | Render-only selection menu |
| `StopAudio` | `Music.h` | Stop and close audio |
| `TextBoxComponent` | `Components/InputComponent.h` | Render-only text input box |
| `TransitionComponent` | `Components/TransitionComponent.h` | Screen transition animation |
| `TryInput` | `Input.h` | Non-blocking line input with backspace handling |
| `Validate` | `Input.h` | Validate input string against a type |

---

## 1. Constantes y Estado Global

### `Common/Consts.h`

| Trigger (¿Cuándo usar?) | Símbolo | Tipo | Valor | Descripción |
|---|---|---|---|---|
| Definir el ancho virtual del canvas | `WIDTH_SCREEN` | `const int` | `200` | Ancho de pantalla en caracteres. Usado por `DrawBackground()` y `TransitionComponent` como límite horizontal. |
| Definir el alto virtual del canvas | `HEIGHT_SCREEN` | `const int` | `50` | Alto de pantalla en filas. Usado por `DrawBackground()`, `GoToEnd()` y `TransitionComponent`. |
| Limitar longitud de mensajes | `MAX_FEEDBACK_MESSAGE_LENGTH` | `const int` | `80` | Cantidad máxima de caracteres para `ClearConsoleLine` al limpiar la barra de feedback. |

### `Common/Variables.h`

| Trigger (¿Cuándo usar?) | Símbolo | Tipo | Valor por defecto | Descripción |
|---|---|---|---|---|
| Almacenar la última tecla presionada | `key` | `inline std::vector<int>` | `{}` | Vector de bytes de la tecla leída (1-3 bytes según plataforma). Se actualiza con `ReadConsoleChar()`. |
| Almacenar el carácter convertido | `character` | `inline std::string` | `""` | Último carácter impreso, generado por `CastKeyToString()`. |
| Mostrar mensajes de estado al usuario | `feedbackMessage` | `inline std::string` | `""` | Texto que se imprime en la posición de feedback. |
| Fila donde se imprime el feedback | `rowFeedbackMessage` | `inline int` | `0` | Coordenada Y de la línea de feedback. |
| Columna donde se imprime el feedback | `colFeedbackMessage` | `inline int` | `0` | Coordenada X de la línea de feedback. |
| Nombre del jugador activo | `playerName` | `inline std::string` | `"Player 1"` | Nombre del jugador, usado por pantallas de input y selección. |

---

## 2. Keycodes (Platform-Specific)

### `Common/Windows/Keys.h` y `Common/Linux/Keys.h`

> **Diferencia de plataforma**: Windows usa secuencias de 2 bytes para teclas especiales (prefijo `0` o `224`). Linux usa secuencias ANSI de 3 bytes (prefijo `27` = ESC).

#### Teclas de Acción

| Trigger (¿Cuándo usar?) | Constante | Windows | Linux | Descripción |
|---|---|---|---|---|
| Confirmar selección / enviar input | `KEY_ENTER` | `{13}` | `{10}` | Enter/Return. Código distinto por SO. |
| Seleccionar opción alternativa | `KEY_SPACE` | `{32}` | `{32}` | Espacio. Código idéntico en ambas plataformas. |
| Borrar último carácter | `KEY_BACKSPACE` | `{8}` | `{127}` | Backspace. Linux usa DEL (127) como código estándar. |
| Cancelar / salir | `KEY_ESCAPE` | `{27}` | `{27}` | Escape. Código idéntico en ambas plataformas. |

#### Teclas de Navegación (Flechas)

| Trigger (¿Cuándo usar?) | Constante | Windows | Linux (ANSI) | Linux (App Mode) |
|---|---|---|---|---|
| Mover selección hacia arriba | `KEY_ARROW_TOP` | `{224, 72}` | `{27, 91, 65}` | `{27, 79, 65}` |
| Mover selección hacia abajo | `KEY_ARROW_BOTTOM` | `{224, 80}` | `{27, 91, 66}` | `{27, 79, 66}` |
| Mover selección hacia la izquierda | `KEY_ARROW_LEFT` | `{224, 75}` | `{27, 91, 68}` | `{27, 79, 68}` |
| Mover selección hacia la derecha | `KEY_ARROW_RIGHT` | `{224, 77}` | `{27, 91, 67}` | `{27, 79, 67}` |

> Las variantes `_2` (ej. `KEY_ARROW_TOP_2`) cubren terminales en "application mode" (DECCKM/smkx).

#### Teclas Alfanuméricas

| Trigger (¿Cuándo usar?) | Constante | Ejemplo | Descripción |
|---|---|---|---|
| Detectar letra mayúscula específica | `KEY_A` .. `KEY_Z` | `{65}` .. `{90}` | Código ASCII estándar. |
| Detectar letra minúscula específica | `KEY_A_LOWER` .. `KEY_Z_LOWER` | `{97}` .. `{122}` | Código ASCII estándar. |
| Detectar Ñ mayúscula | `KEY_ENYE_CAPS` | `{195, 145}` | Secuencia UTF-8 (2 bytes). |
| Detectar ñ minúscula | `KEY_ENYE_LOWER` | `{195, 177}` | Secuencia UTF-8 (2 bytes). |
| Detectar vocal acentuada mayúscula | `KEY_A_ACCENT_CAPS` .. `KEY_U_ACCENT_CAPS` | `{195, 129}` .. `{195, 154}` | Á, É, Í, Ó, Ú — UTF-8 (2 bytes). |
| Detectar vocal acentuada minúscula | `KEY_A_ACCENT_LOWER` .. `KEY_U_ACCENT_LOWER` | `{195, 161}` .. `{195, 186}` | á, é, í, ó, ú — UTF-8 (2 bytes). |
| Detectar dígito específico | `KEY_0` .. `KEY_9` | `{48}` .. `{57}` | Código ASCII estándar. |

#### Colecciones

| Trigger (¿Cuándo usar?) | Constante | Tipo | Contenido |
|---|---|---|---|
| Verificar si es tecla de acción (Enter/Space) | `ACTION_KEYS` | `vector<vector<int>>` | `KEY_ENTER`, `KEY_SPACE` |
| Verificar si es tecla de navegación (flechas) | `NAVIGATION_KEYS` | `vector<vector<int>>` | 8 variantes: 4 primarias + 4 `_2` |
| Verificar si es carácter alfanumérico válido | `ALPHA_NUM_CHARS` | `vector<vector<int>>` | 62 letras + 10 dígitos + ñ/Ñ + vocales acentuadas |

---

## 3. Terminal Cross-Platform

### `Common/Terminal.h` (Fachada)

La fachada incluye la implementación específica por SO y define la función de utilidad `GoToEnd()`.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Posicionar cursor al final de la pantalla virtual | `GoToEnd` | `inline void GoToEnd()` | Ninguno | `void` | Mueve el cursor a `(0, HEIGHT_SCREEN + 1)`, justo debajo del área de dibujo. |

### `Common/Windows/Terminal.h`

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Poner terminal en modo raw (lectura tecla por tecla) | `InitTerminalRawMode` | `inline void InitTerminalRawMode()` | Ninguno | `void` | Declarada pero vacía en Windows (conio.h ya provee `_kbhit`/`_getch`). |
| Habilitar colores True Color ANSI (VT100) | `EnableTrueColor` | `inline void EnableTrueColor()` | Ninguno | `void` | Activa `ENABLE_VIRTUAL_TERMINAL_PROCESSING` en la consola Win32. |
| Deshabilitar colores True Color | `DisableTrueColor` | `inline void DisableTrueColor()` | Ninguno | `void` | Desactiva `ENABLE_VIRTUAL_TERMINAL_PROCESSING`. |
| Verificar si ANSI está habilitado | `IsAnsiEnabled` | `inline bool IsAnsiEnabled()` | Ninguno | `bool` | `true` si `ENABLE_VIRTUAL_TERMINAL_PROCESSING` está activo. |
| Habilitar soporte UTF-8 | `EnableUTF8` | `inline void EnableUTF8()` | Ninguno | `void` | Configura páginas de código a `CP_UTF8` (65001) para entrada y salida. |
| Deshabilitar soporte UTF-8 | `DisableUTF8` | `inline void DisableUTF8()` | Ninguno | `void` | Restaura páginas de código a `CP_ACP` (ANSI). |
| Controlar visibilidad del cursor | `SetCursorVisible` | `inline void SetCursorVisible(bool visible)` | `visible` (`bool`): `true` para mostrar, `false` para ocultar | `void` | Modifica `CONSOLE_CURSOR_INFO.bVisible`. |
| Mostrar el cursor | `ShowCursor` | `inline void ShowCursor()` | Ninguno | `void` | Equivalente a `SetCursorVisible(true)`. |
| Ocultar el cursor | `HideCursor` | `inline void HideCursor()` | Ninguno | `void` | Equivalente a `SetCursorVisible(false)`. |
| Posicionar cursor en coordenadas absolutas | `GoToXY` | `inline void GoToXY(int x, int y)` | `x` (`int`): columna (0-indexed), `y` (`int`): fila (0-indexed) | `void` | Usa `SetConsoleCursorPosition` de Win32. |
| Limpiar pantalla completa | `Clear` | `inline void Clear()` | Ninguno | `void` | Ejecuta `system("cls")` y reposiciona cursor en `(0,0)`. |
| Obtener ancho de la consola | `GetConsoleWidth` | `inline int GetConsoleWidth()` | Ninguno | `int` | Ancho en columnas del buffer de consola visible. |
| Obtener alto de la consola | `GetConsoleHeight` | `inline int GetConsoleHeight()` | Ninguno | `int` | Alto en filas del buffer de consola visible. |
| Obtener tamaño de la consola | `GetConsoleSize` | `inline std::array<int, 2> GetConsoleSize()` | Ninguno | `array<int,2>` | `{width, height}`. |
| Verificar si hay tecla en el buffer | `Kbhit` | `inline bool Kbhit()` | Ninguno | `bool` | Wraps `_kbhit()` de conio.h. |
| Leer una tecla sin bloqueo | `Getch` | `inline char Getch()` | Ninguno | `char` | Wraps `_getch()` de conio.h. Devuelve el byte presionado. |
| Dormir el hilo actual | `Sleep` | `inline void Sleep(int ms)` | `ms` (`int`): milisegundos | `void` | Wraps `::Sleep()` de Win32 (synchapi.h). |
| Limpiar una línea de la consola | `ClearConsoleLine` | `inline void ClearConsoleLine(int lineLength)` | `lineLength` (`int`): número de espacios a imprimir | `void` | Imprime `lineLength` espacios en blanco. **Nota**: la implementación actual tiene un bug de loops anidados que produce más espacios de los esperados (ver Notas de Bugs al final). |

### `Common/Linux/Terminal.h`

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Poner terminal en modo raw (lectura tecla por tecla) | `InitTerminalRawMode` | `inline void InitTerminalRawMode()` | Ninguno | `void` | Configura termios (ICANON/ECHO off, VMIN=1/VTIME=0). Registra `atexit(RestoreTerminalMode)` y handler de SIGINT. Llamar una sola vez al inicio de `main()`. |
| Restaurar terminal al estado original | `RestoreTerminalMode` | `inline void RestoreTerminalMode()` | Ninguno | `void` | Restaura termios original guardado en `g_oldTermios`. Se llama automáticamente via `atexit`. |
| Habilitar colores True Color | `EnableTrueColor` | `inline void EnableTrueColor()` | Ninguno | `void` | No-op en Linux (ANSI es intrínseco al terminal). Existe por compatibilidad de interfaz. |
| Deshabilitar colores True Color | `DisableTrueColor` | `inline void DisableTrueColor()` | Ninguno | `void` | No-op en Linux. Por compatibilidad de interfaz. |
| Verificar soporte de color True Color | `IsAnsiEnabled` | `inline bool IsAnsiEnabled()` | Ninguno | `bool` | `true` si `COLORTERM=truecolor/24bit`, o si `TERM` está definido y no es `"dumb"`. |
| Habilitar soporte UTF-8 | `EnableUTF8` | `inline void EnableUTF8()` | Ninguno | `void` | Ejecuta `setlocale(LC_ALL, "en_US.UTF-8")`. |
| Deshabilitar soporte UTF-8 | `DisableUTF8` | `inline void DisableUTF8()` | Ninguno | `void` | Ejecuta `setlocale(LC_ALL, "C")`. |
| Controlar visibilidad del cursor | `SetCursorVisible` | `inline void SetCursorVisible(bool visible)` | `visible` (`bool`) | `void` | Emite secuencias ANSI `\x1b[?25h` (mostrar) o `\x1b[?25l` (ocultar). |
| Mostrar el cursor | `ShowCursor` | `inline void ShowCursor()` | Ninguno | `void` | Equivalente a `SetCursorVisible(true)`. |
| Ocultar el cursor | `HideCursor` | `inline void HideCursor()` | Ninguno | `void` | Equivalente a `SetCursorVisible(false)`. |
| Posicionar cursor en coordenadas absolutas | `GoToXY` | `inline void GoToXY(int x, int y)` | `x` (`int`): columna (0-indexed), `y` (`int`): fila (0-indexed) | `void` | Emite ANSI `\x1b[{y+1};{x+1}H`. Convierte de 0-indexed a 1-indexed internamente. |
| Limpiar pantalla completa | `Clear` | `inline void Clear()` | Ninguno | `void` | Emite `\x1b[2J\x1b[3J` (limpia pantalla + scrollback) y reposiciona cursor. Más eficiente que `system("clear")`. |
| Obtener ancho del terminal | `GetConsoleWidth` | `inline int GetConsoleWidth()` | Ninguno | `int` | Usa `ioctl(TIOCGWINSZ)` para leer `ws_col`. |
| Obtener alto del terminal | `GetConsoleHeight` | `inline int GetConsoleHeight()` | Ninguno | `int` | Usa `ioctl(TIOCGWINSZ)` para leer `ws_row`. |
| Obtener tamaño del terminal | `GetConsoleSize` | `inline std::array<int, 2> GetConsoleSize()` | Ninguno | `array<int,2>` | `{width, height}`. |
| Verificar si hay tecla en el buffer | `Kbhit` | `inline bool Kbhit()` | Ninguno | `bool` | Usa `select()` con timeout cero para no bloquear. Requiere `InitTerminalRawMode()`. |
| Leer una tecla sin bloqueo | `Getch` | `inline int Getch()` | Ninguno | `int` | Lee un byte con `read()`. Devuelve `int` (no `char`) para evitar sign-extension en bytes UTF-8 (>= 128). |
| Dormir el hilo actual | `Sleep` | `inline void Sleep(int ms)` | `ms` (`int`): milisegundos | `void` | Usa `usleep(ms * 1000)`. |

> **Nota**: En Linux, `Kbhit()` y `Getch()` requieren que `InitTerminalRawMode()` se haya llamado antes. La inicialización se registra una sola vez en `main()`.

---

## 4. Color

### `Common/Color.h`

| Trigger (¿Cuándo usar?) | Función/Símbolo | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Representar "no cambiar este color" | `COLOR_DEFAULT` | `const std::array<int, 3>` | — | `{ -1, -1, -1 }` | Valor centinela de transparencia. Se usa como foreground o background para indicar que ese canal no se debe modificar. |
| Verificar si un color es transparente | `isTransparent` | `inline bool isTransparent(const std::array<int, 3>& color)` | `color` (`array<int,3>`): color a evaluar | `bool` | `true` si los tres componentes son `-1`. |
| Generar secuencia ANSI de color RGB | `Color` | `inline std::string Color(std::array<int, 3> foreground, std::array<int, 3> background)` | `foreground` (`array<int,3>`): color de texto RGB o `COLOR_DEFAULT`, `background` (`array<int,3>`): color de fondo RGB o `COLOR_DEFAULT` | `string` | Secuencia ANSI `\033[38;2;R;G;Bm` y/o `\033[48;2;R;G;Bm`. Si el color es transparente, se omite esa parte. |
| Resetear todos los colores de la terminal | `ResetColor` | `inline std::string ResetColor()` | Ninguno | `string` | Secuencia ANSI `\033[0m` que restaura colores por defecto. |
| Cambiar color de fondo/texto de toda la consola | `SetTerminalColor` | `inline void SetTerminalColor(std::array<int, 3> foreground, std::array<int, 3> background)` | `foreground` (`array<int,3>`), `background` (`array<int,3>`) | `void` | Aplica color + limpia pantalla + reposicia cursor. Útil para "flash" de color global. |
| Generar degradado de colores | `Gradient` | `inline std::vector<std::array<int, 3>> Gradient(int steps, std::array<int, 3> start, std::array<int, 3> end)` | `steps` (`int`): cantidad de pasos, `start` (`array<int,3>`): color inicial, `end` (`array<int,3>`): color final | `vector<array<int,3>>` | Vector de `steps` colores con interpolación lineal entre `start` y `end`. Usado por `DrawLifeBar` y `TransitionComponent`. |

---

## 5. Theme

### `Common/Theme.h`

Paleta de colores inspirada en [Matte Black Theme](https://omarchytheme.com/themes/matte-black/) de Omarchy. Todos son `const std::array<int, 3>` con valores RGB (0-255).

| Trigger (¿Cuándo usar?) | Constante | Valor RGB | Descripción |
|---|---|---|---|
| Fondo base de la aplicación | `BACKGROUND` | `{31, 34, 38}` | Gris oscuro azulado (#333a40). Color predominante del canvas. |
| Texto principal (claro) | `FOREGROUND_LIGHT` | `{255, 255, 255}` | Blanco puro. Texto sobre fondo oscuro. |
| Texto principal (oscuro) | `FOREGROUND_DARK` | `{0, 0, 0}` | Negro. Texto sobre fondo claro o selección. |
| Color de acento / highlight | `ACCENT` | `{230, 142, 13}` | Naranja dorado (#e68e0d). Resaltar elementos seleccionados. |
| Color del cursor | `CURSOR` | `{234, 234, 234}` | Gris claro (#eaeaea). |
| Fondo de selección | `SELECTION_BACKGROUND` | `{51, 54, 54}` | Gris intermedio (#515151). Fondo de cajas de input y menús. |
| Texto de selección | `SELECTION_FOREGROUND` | `{190, 190, 190}` | Gris claro (#bebebe). Texto sobre `SELECTION_BACKGROUND`. |
| Verde suave | `SOFT_GREEN` | `{178, 242, 187}` | Verde pastel. BARRAS DE VIDA alto. |
| Verde claro | `LIGHT_GREEN` | `{105, 219, 124}` | Verde vivo. BARRAS DE VIDA medio-alto. |
| Gris | `GRAY` | `{206, 212, 218}` | Gris neutro. Texto secundario. |
| Azul claro | `LIGHT_BLUE` | `{153, 233, 242}` | Cian. BARRAS DE VIDA medio. |
| Azul | `BLUE` | `{25, 113, 194}` | Azul saturado. BARRAS DE VIDA bajo, BottomBar. |
| Naranja | `ORANGE` | `{255, 193, 7}` | Amarillo/naranja. BARRAS DE VIDA crítico. |
| Rojo suave | `SOFT_RED` | `{255, 201, 201}` | Rosa claro. |
| Crema | `CREAM` | `{254, 236, 152}` | Amarillo crema. |
| Rojo | `RED` | `{239, 75, 70}` | Rojo saturado. BARRAS DE VIDA muy bajo. |
| Rojo oscuro | `DARK_RED` | `{182, 54, 59}` | Rojo profundo. BARRAS DE VIDA mínimo. |
| Amarillo | `YELLOW` | `{255, 202, 2}` | Amarillo brillante. |

---

## 6. UnicodeGlyphs

### `Common/UnicodeGlyphs.h`

Glifos Unicode para el graficador TUI. Requiere `EnableUTF8()`. **Importante**: el archivo debe guardarse como UTF-8; en MSVC usar flag `/utf-8`.

#### Bloques de Relleno

| Trigger (¿Cuándo usar?) | Constante | Tipo | Descripción |
|---|---|---|---|
| Barras de progreso / sparklines por columna | `VERTICAL_EIGHTH_BLOCKS` | `array<string, 9>` | 9 niveles: `" "` (0/8) → `▁▂▃▄▅▆▇█` (8/8). Índice = fracción de llenado. |
| Espacio vacío | `EMPTY_BLOCK` | `string` | `" "` — relleno por defecto. |
| Mitad superior de celda | `UPPER_HALF_BLOCK` | `string` | `"▀"` — usado para bordes de cajas y mitad superior de cuadrantes. |
| Mitad inferior de celda | `LOWER_HALF_BLOCK` | `string` | `"▄"` — usado para bordes de cajas y mitad inferior de cuadrantes. |
| Bloque completo de celda | `FULL_BLOCK` | `string` | `"█"` — relleno sólido, usado por `DrawFillRectangle`, `DrawLifeBar`. |
| Mitad izquierda de celda | `LEFT_HALF_BLOCK` | `string` | `"▌"` |
| Mitad derecha de celda | `RIGHT_HALF_BLOCK` | `string` | `"▐"` |
| Niveles de sombreado | `SHADING` | `array<string, 4>` | `░`(25%), `▒`(50%), `▓`(75%), `█`(100%). Mapas de calor, histogramas. |
| Cuadrantes (2x2 por celda) | `QUADRANTS` | `array<string, 16>` | 16 combinaciones bitmask: `[0]` vacío → `[15]`█ completo. Ejemplo: `QUADRANTS[0b0110]` = `▞` diagonal. |

#### Caracteres de Borde (Box Drawing)

| Trigger (¿Cuándo usar?) | Constante | Glyph | Descripción |
|---|---|---|---|
| Borde horizontal simple | `HORIZONTAL_BORDER` | `─` | Línea horizontal fina. |
| Borde vertical simple | `VERTICAL_BORDER` | `│` | Línea vertical fina. |
| Esquina sup-izq simple | `TOP_LEFT_CORNER` | `┌` | |
| Esquina sup-der simple | `TOP_RIGHT_CORNER` | `┐` | |
| Esquina inf-izq simple | `BOTTOM_LEFT_CORNER` | `└` | |
| Esquina inf-der simple | `BOTTOM_RIGHT_CORNER` | `┘` | |
| T izquierda simple | `LEFT_TEE` | `├` | |
| T derecha simple | `RIGHT_TEE` | `┤` | |
| T arriba simple | `TOP_TEE` | `┬` | |
| T abajo simple | `BOTTOM_TEE` | `┴` | |
| Cruz simple | `CROSS` | `┼` | |
| Borde horizontal doble | `DOUBLE_HORIZONTAL_BORDER` | `═` | |
| Borde vertical doble | `DOUBLE_VERTICAL_BORDER` | `║` | |
| Esquina sup-izq doble | `DOUBLE_TOP_LEFT_CORNER` | `╔` | |
| Esquina sup-der doble | `DOUBLE_TOP_RIGHT_CORNER` | `╗` | |
| Esquina inf-izq doble | `DOUBLE_BOTTOM_LEFT_CORNER` | `╚` | |
| Esquina inf-der doble | `DOUBLE_BOTTOM_RIGHT_CORNER` | `╝` | |
| T izquierda doble | `DOUBLE_LEFT_TEE` | `╠` | |
| T derecha doble | `DOUBLE_RIGHT_TEE` | `╣` | |
| T arriba doble | `DOUBLE_TOP_TEE` | `╦` | |
| T abajo doble | `DOUBLE_BOTTOM_TEE` | `╩` | |
| Cruz doble | `DOUBLE_CROSS` | `╬` | |
| Esquina sup-izq redondeada | `ROUNDED_TOP_LEFT_CORNER` | `╭` | |
| Esquina sup-der redondeada | `ROUNDED_TOP_RIGHT_CORNER` | `╮` | |
| Esquina inf-izq redondeada | `ROUNDED_BOTTOM_LEFT_CORNER` | `╰` | |
| Esquina inf-der redondeada | `ROUNDED_BOTTOM_RIGHT_CORNER` | `╯` | |
| Borde horizontal grueso (heavy) | `HEAVY_HORIZONTAL_BORDER` | `━` | |
| Borde vertical grueso (heavy) | `HEAVY_VERTICAL_BORDER` | `┃` | |
| Esquina sup-izq heavy | `HEAVY_TOP_LEFT_CORNER` | `┏` | |
| Esquina sup-der heavy | `HEAVY_TOP_RIGHT_CORNER` | `┓` | |
| Esquina inf-izq heavy | `HEAVY_BOTTOM_LEFT_CORNER` | `┗` | |
| Esquina inf-der heavy | `HEAVY_BOTTOM_RIGHT_CORNER` | `┛` | |
| T izquierda heavy | `HEAVY_LEFT_TEE` | `┣` | |
| T derecha heavy | `HEAVY_RIGHT_TEE` | `┫` | |
| T arriba heavy | `HEAVY_TOP_TEE` | `┳` | |
| T abajo heavy | `HEAVY_BOTTOM_TEE` | `┻` | |
| Cruz heavy | `HEAVY_CROSS` | `╋` | |
| Línea horizontal punteada fina | `THIN_DOTTED_HORIZONTAL` | `┄` | |
| Línea vertical punteada fina | `THIN_DOTTED_VERTICAL` | `┆` | |
| Línea horizontal punteada | `DOTTED_HORIZONTAL` | `┈` | |
| Línea vertical punteada | `DOTTED_VERTICAL` | `┊` | |
| Cruz de ejes (vertical resaltada) | `AXIS_CROSS` | `╂` | Marcar eje y=0 en gráficos. |

#### Catálogos Indexados

| Trigger (¿Cuándo usar?) | Constante | Tipo | Descripción |
|---|---|---|---|
| Obtener borde por estilo en `DrawBox` | `BORDERS` | `array<array<string,4>, 7>` | `[estilo][orientación]` — 7 estilos × 4 (top, right, bottom, left). Índices: 0=vacío, 1=punteado fino, 2=punteado, 3=simple, 4=heavy, 5=doble, 6=cuadrantes. |
| Obtener esquina por estilo en `DrawBox` | `CORNERS` | `array<array<string,4>, 6>` | `[estilo][esquina]` — 6 estilos × 4 (TL, TR, BR, BL). Índices: 0=vacío, 1=simple, 2=heavy, 3=doble, 4=redondeado, 5=cuadrantes. |

---

## 7. Font (ASCII Art)

### `Common/Font.h`

Fuentes de estilo ASCII art en dos tamaños. Cada glyph es un array de strings: 9 líneas para mayúsculas, 4 líneas para minúsculas/números.

#### Fuente Grande (9 líneas) — Mayúsculas y Símbolos

| Trigger (¿Cuándo usar?) | Constante | Tipo | Descripción |
|---|---|---|---|
| Renderizar letra 'A' grande | `FONT_A` | `array<string, 9>` | ASCII art de bloque para A. |
| Renderizar letra 'B' grande | `FONT_B` | `array<string, 9>` | ASCII art de bloque para B. |
| Renderizar letra 'C' grande | `FONT_C` | `array<string, 9>` | ASCII art de bloque para C. |
| Renderizar letra 'D' grande | `FONT_D` | `array<string, 9>` | ASCII art de bloque para D. |
| Renderizar letra 'E' grande | `FONT_E` | `array<string, 9>` | ASCII art de bloque para E. |
| Renderizar letra 'F' grande | `FONT_F` | `array<string, 9>` | ASCII art de bloque para F. |
| Renderizar letra 'G' grande | `FONT_G` | `array<string, 9>` | ASCII art de bloque para G. |
| Renderizar letra 'H' grande | `FONT_H` | `array<string, 9>` | ASCII art de bloque para H. |
| Renderizar letra 'I' grande | `FONT_I` | `array<string, 9>` | ASCII art de bloque para I. |
| Renderizar letra 'J' grande | `FONT_J` | `array<string, 9>` | ASCII art de bloque para J. |
| Renderizar letra 'K' grande | `FONT_K` | `array<string, 9>` | ASCII art de bloque para K. |
| Renderizar letra 'L' grande | `FONT_L` | `array<string, 9>` | ASCII art de bloque para L. |
| Renderizar letra 'M' grande | `FONT_M` | `array<string, 9>` | ASCII art de bloque para M. |
| Renderizar letra 'N' grande | `FONT_N` | `array<string, 9>` | ASCII art de bloque para N. |
| Renderizar letra 'O' grande | `FONT_O` | `array<string, 9>` | ASCII art de bloque para O. |
| Renderizar letra 'P' grande | `FONT_P` | `array<string, 9>` | ASCII art de bloque para P. |
| Renderizar letra 'Q' grande | `FONT_Q` | `array<string, 9>` | ASCII art de bloque para Q. |
| Renderizar letra 'R' grande | `FONT_R` | `array<string, 9>` | ASCII art de bloque para R. |
| Renderizar letra 'S' grande | `FONT_S` | `array<string, 9>` | ASCII art de bloque para S. |
| Renderizar letra 'T' grande | `FONT_T` | `array<string, 9>` | ASCII art de bloque para T. |
| Renderizar letra 'U' grande | `FONT_U` | `array<string, 9>` | ASCII art de bloque para U. |
| Renderizar letra 'V' grande | `FONT_V` | `array<string, 9>` | ASCII art de bloque para V. |
| Renderizar letra 'W' grande | `FONT_W` | `array<string, 9>` | ASCII art de bloque para W. |
| Renderizar letra 'X' grande | `FONT_X` | `array<string, 9>` | ASCII art de bloque para X. |
| Renderizar letra 'Y' grande | `FONT_Y` | `array<string, 9>` | ASCII art de bloque para Y. |
| Renderizar letra 'Z' grande | `FONT_Z` | `array<string, 9>` | ASCII art de bloque para Z. |
| Espacio en blanco grande | `FONT_BLANK` | `array<string, 9>` | 9 líneas de 3 espacios. Separador entre letras. |
| Punto grande | `FONT_DOT` | `array<string, 9>` | Dos bloques sólidos en la última línea. |
| Signo de exclamación grande | `FONT_EXCLAMATION` | `array<string, 9>` | ASCII art de bloque para `!`. |

#### Fuente Pequeña (4 líneas) — Minúsculas, Números y Símbolos

| Trigger (¿Cuándo usar?) | Constante | Tipo | Descripción |
|---|---|---|---|
| Renderizar letra 'a' pequeña | `FONT_a` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'b' pequeña | `FONT_b` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'c' pequeña | `FONT_c` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'd' pequeña | `FONT_d` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'e' pequeña | `FONT_e` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'f' pequeña | `FONT_f` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'g' pequeña | `FONT_g` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'h' pequeña | `FONT_h` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'i' pequeña | `FONT_i` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'j' pequeña | `FONT_j` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'k' pequeña | `FONT_k` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'l' pequeña | `FONT_l` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'm' pequeña | `FONT_m` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'n' pequeña | `FONT_n` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'o' pequeña | `FONT_o` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'p' pequeña | `FONT_p` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'q' pequeña | `FONT_q` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'r' pequeña | `FONT_r` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 's' pequeña | `FONT_s` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 't' pequeña | `FONT_t` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'u' pequeña | `FONT_u` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'v' pequeña | `FONT_v` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'w' pequeña | `FONT_w` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'x' pequeña | `FONT_x` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'y' pequeña | `FONT_y` | `array<string, 4>` | Minúscula compacta. |
| Renderizar letra 'z' pequeña | `FONT_z` | `array<string, 4>` | Minúscula compacta. |
| Espacio en blanco pequeño | `FONT_blank` | `array<string, 4>` | 4 líneas de 2 espacios. Separador. |
| Renderizar dígito '0' | `FONT_0` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '1' | `FONT_1` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '2' | `FONT_2` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '3' | `FONT_3` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '4' | `FONT_4` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '5' | `FONT_5` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '6' | `FONT_6` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '7' | `FONT_7` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '8' | `FONT_8` | `array<string, 4>` | Número compacto. |
| Renderizar dígito '9' | `FONT_9` | `array<string, 4>` | Número compacto. |

#### Funciones de Composición

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Concatenar glyphs grandes horizontalmente | `ConcatFont` (9 líneas) | `inline std::array<std::string, 9> ConcatFont(std::vector<std::array<std::string, 9>> fontChar, int separator)` | `fontChar` (`vector<array<string,9>>`): glyphs a concatenar, `separator` (`int`): espacios entre cada glyph | `array<string,9>` | Une múltiples glyphs de fuente grande en una sola línea de texto multilínea. Cada fila se concatena horizontalmente con `separator` espacios de separación. |
| Concatenar glyphs pequeños horizontalmente | `ConcatFont` (4 líneas) | `inline std::array<std::string, 4> ConcatFont(std::vector<std::array<std::string, 4>> fontChar, int separator)` | `fontChar` (`vector<array<string,4>>`): glyphs a concatenar, `separator` (`int`): espacios entre cada glyph | `array<string,4>` | Igual que la versión de 9 líneas pero para fuente pequeña (4 líneas). |

---

## 8. Utils (String)

### `Common/Utils.h`

Utilidades de manipulación de strings, con soporte para caracteres multibyte (UTF-8) y secuencias de escape ANSI.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Obtener largo visible de un string | `Length` | `int Length(const std::string& str)` | `str` (`string`): string a medir | `int` | Cuenta caracteres visibles ignorando secuencias ANSI (`\033[...`) y saltando bytes de caracteres multibyte UTF-8. Devuelve el ancho real en columnas. |
| Dividir string en segmentos de ancho fijo | `CutString` | `std::vector<std::string> CutString(const std::string& str, size_t width)` | `str` (`string`): texto a dividir, `width` (`size_t`): ancho máximo por segmento | `vector<string>` | Divide el string en trozos de `width` caracteres visibles. Usado por `DrawText` para ajustar texto a un ancho dado. |
| Invertir un string | `InvertString` | `std::string InvertString(std::string str)` | `str` (`string`): texto a invertir | `string` | Devuelve el string con los bytes en orden inverso. **Nota**: no respeta caracteres multibyte — usar solo con ASCII puro. |
| Encontrar el string más largo de un vector | `MaxString` | `std::string MaxString(std::vector<std::string> strings)` | `strings` (`vector<string>`): lista de strings | `string` | Devuelve el string con mayor `Length()` (ancho visible). Usado por componentes de UI para calcular anchos de cajas. |
| Repetir un string N veces | `RepeatString` | `std::string RepeatString(std::string str, int count)` | `str` (`string`): texto a repetir, `count` (`int`): cantidad de repeticiones | `string` | Concatena `str` consigo mismo `count` veces. |
| Convertir array de 9 strings a vector | `ArrayToVector` | `std::vector<std::string> ArrayToVector(std::array<std::string, 9> arr)` | `arr` (`array<string,9>`): array estático de 9 strings (fuente grande) | `vector<string>` | Convierte el formato de `FONT_X` (array estático) a `vector<string>` para usar con `DrawText` y `ConcatFont`. |

---

## 9. Aligned (Layout)

### `Common/Aligned.h`

Funciones de posicionamiento relativo para alinear elementos dentro de un área contenedora.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Calcular posición X con alineación horizontal | `AlignedX` | `inline int AlignedX(int x, int width, int childWidth, std::string alignment)` | `x` (`int`): origen X del contenedor, `width` (`int`): ancho del contenedor, `childWidth` (`int`): ancho del elemento hijo, `alignment` (`string`): `"center"`, `"right"` o `"left"` | `int` | Posición X del hijo dentro del contenedor según la alineación. `"left"` = origen, `"center"` = centrado, `"right"` = alineado a la derecha. |
| Calcular posición Y con alineación vertical | `AlignedY` | `inline int AlignedY(int y, int height, int childHeight, std::string alignment)` | `y` (`int`): origen Y del contenedor, `height` (`int`): alto del contenedor, `childHeight` (`int`): alto del elemento hijo, `alignment` (`string`): `"center"`, `"bottom"` o `"top"` | `int` | Posición Y del hijo dentro del contenedor según la alineación. `"top"` = origen, `"center"` = centrado, `"bottom"` = alineado abajo. |
| Calcular posición X relativa | `RelativeX` | `inline int RelativeX(int x, int ChildX)` | `x` (`int`): posición base X, `ChildX` (`int`): offset relativo | `int` | Retorna `x + ChildX`. Desplazamiento horizontal desde un punto base. |
| Calcular posición Y relativa | `RelativeY` | `inline int RelativeY(int y, int ChildY)` | `y` (`int`): posición base Y, `ChildY` (`int`): offset relativo | `int` | Retorna `y + ChildY`. Desplazamiento vertical desde un punto base. |

---

## 10. Input

### `Common/Input.h`

Utilidades de entrada de usuario y parsing de tipos. Depende de `Terminal.h` para `Kbhit`/`Getch`.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Validar si una entrada coincide con un tipo | `Validate` | `inline bool Validate(std::string input, std::string type)` | `input` (`string`): texto a validar, `type` (`string`): `"int"`, `"float"`, `"string"`, `"char"` o `"bool"` | `bool` | `true` si el primer carácter de `input` es compatible con el tipo. Validación básica: int = dígito, float = dígito o '.', char = alfabético, string = siempre true. |
| Convertir string a int | `ParseInt` | `inline int ParseInt(std::string str)` | `str` (`string`): texto a convertir | `int` | Wraps `std::stoi()`. Lanza excepción si no es válido. |
| Convertir string a int con validación estricta | `ParseIntStrict` | `inline int ParseIntStrict(std::string str)` | `str` (`string`): solo dígitos, opcionalmente signo `+`/`-` | `int` | A diferencia de `ParseInt()`, rechaza `"1.5"`, `"1,000"`, `"1e3"`, `"1E3"`, `"10."`. Lanza `invalid_argument`. |
| Convertir string a float | `ParseFloat` | `inline float ParseFloat(std::string str)` | `str` (`string`): texto a convertir | `float` | Wraps `std::stof()`. Lanza excepción si no es válido. |
| Extraer primer carácter | `ParseChar` | `inline char ParseChar(std::string str)` | `str` (`string`): texto del cual extraer | `char` | Retorna `str[0]`. No valida si el string está vacío. |
| Convertir string a bool | `ParseBool` | `inline bool ParseBool(std::string str)` | `str` (`string`): `"true"`, `"false"`, `"1"` o `"0"` | `bool` | `true` para `"true"`/`"1"`, `false` para `"false"`/`"0"`. Lanza `invalid_argument` para otros valores. |
| Leer una palabra desde stdin | `Input` | `inline std::string Input()` | Ninguno | `string` | Usa `std::cin >> line`. Lee hasta espacio o salto de línea. |
| Leer línea completa de forma no bloqueante | `TryInput` | `inline bool TryInput(std::string& line)` | `line` (`string&`): referencia donde se deposita la línea completada | `bool` | `true` si se presionó Enter (línea lista), `false` si no hay entrada. Maneja backspace y eco en pantalla. Usar en bucle para input interactivo. |
| Validar carácter de 1 byte por rango | `IsValidChar` (rango) | `inline bool IsValidChar(std::vector<std::tuple<int, int>>& validCharRanges, int character)` | `validCharRanges` (`vector<tuple<int,int>>`): rangos `[min, max]` permitidos, `character` (`int`): código del carácter a validar | `bool` | `true` si `character` está dentro de al menos uno de los rangos (inclusivo). |
| Validar carácter multibyte por lista exacta | `IsValidChar` (lista) | `inline bool IsValidChar(std::vector<std::vector<int>>& validChars, std::vector<int>& character)` | `validChars` (`vector<vector<int>>`): lista de secuencias de bytes válidas, `character` (`vector<int>`): bytes del carácter a validar | `bool` | `true` si `character` coincide exactamente con alguna entrada de `validChars`. Usado con `ALPHA_NUM_CHARS` y `ACTION_KEYS`. |
| Leer tecla validada por rango (1 byte) | `ReadConsoleChar` (rango) | `inline int ReadConsoleChar(std::vector<std::tuple<int, int>>& validCharRanges)` | `validCharRanges` (`vector<tuple<int,int>>`): rangos permitidos | `int` | Lee con `Getch()`, salta byte de prefijo UTF-8 si aplica, valida contra rangos. Devuelve código del carácter o `-1` si no es válido. |
| Leer tecla completa (multibyte) | `ReadConsoleChar` (sin args) | `inline std::vector<int> ReadConsoleChar()` | Ninguno | `vector<int>` | Lee la secuencia completa de bytes de una tecla. Maneja: Windows (0/224 + scancode), Linux (ESC + secuencia ANSI), UTF-8 (2/3/4 bytes). Devuelve vector de bytes. |
| Convertir bytes de tecla a string imprimible | `CastKeyToString` | `inline std::string CastKeyToString(const std::vector<int>& byteChar)` | `byteChar` (`vector<int>`): secuencia de bytes | `string` | Convierte cada byte a `char` y los concatena. |
| Verificar si un carácter es alfanumérico | `IsAlphaNumChar` | `inline bool IsAlphaNumChar(std::vector<int>& byteChar)` | `byteChar` (`vector<int>`): bytes del carácter | `bool` | `true` si coincide con alguna entrada de `ALPHA_NUM_CHARS` (letras, dígitos, ñ, vocales acentuadas). |

---

## 11. Graphics (TUI Drawing)

### `Common/Graphics.h`

Funciones de dibujo TUI de alto nivel para cuadros, líneas, rectángulos y texto en terminal.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Dibujar cuadro con bordes personalizados | `DrawRawBox` | `inline void DrawRawBox(int x, int y, int width, int height, std::string topBorder, std::string rightBorder, std::string bottomBorder, std::string leftBorder, std::string topLeftCorner, std::string topRightCorner, std::string BottomRightCorner, std::string BottomLeftCorner)` | `x`, `y` (`int`): esquina sup-izq, `width`, `height` (`int`): dimensiones interiores, `topBorder`, `rightBorder`, `bottomBorder`, `leftBorder` (`string`): caracteres de borde por lado, `topLeftCorner`, `topRightCorner`, `BottomRightCorner`, `BottomLeftCorner` (`string`): caracteres de esquina | `void` | Dibuja un rectángulo con bordes y esquinas de texto arbitrario. No valida límites de pantalla. |
| Dibujar cuadro con estilos predefinidos | `DrawBox` | `inline void DrawBox(int x, int y, int width, int height, std::array<unsigned, 4> borders, std::array<unsigned, 4> corners)` | `x`, `y` (`int`): posición, `width`, `height` (`int`): dimensiones, `borders` (`array<unsigned,4>`): índices de estilo para `[top, right, bottom, left]` en `BORDERS[]` (0-6), `corners` (`array<unsigned,4>`): índices de estilo para `[TL, TR, BR, BL]` en `CORNERS[]` (0-5) | `void` | Resuelve strings desde `BORDERS` y `CORNERS` y delega en `DrawRawBox`. Estilos: 0=vacío, 1=punteado fino, 2=punteado, 3=simple, 4=heavy, 5=doble, 6=cuadrantes. |
| Dibujar línea horizontal | `DrawRawHorizontalLine` | `inline void DrawRawHorizontalLine(int x, int y, int length, std::string left, std::string center, std::string right)` | `x`, `y` (`int`): posición, `length` (`int`): longitud total, `left` (`string`): extremo izquierdo, `center` (`string`): relleno central, `right` (`string`): extremo derecho | `void` | Construye la línea completa y la imprime en una sola llamada a `cout`. |
| Dibujar línea vertical | `DrawRawVerticalLine` | `inline void DrawRawVerticalLine(int x, int y, int length, std::string top, std::string center, std::string bottom)` | `x`, `y` (`int`): posición, `length` (`int`): longitud total, `top` (`string`): extremo superior, `center` (`string`): relleno central, `bottom` (`string`): extremo inferior | `void` | Imprime carácter a carácter moviendo el cursor con `GoToXY()`. |
| Dibujar rectángulo relleno con color | `DrawFillRectangle` | `inline void DrawFillRectangle(int x, int y, int width, int height, std::string fill, std::array<int, 3> foreground, std::array<int, 3> background)` | `x`, `y` (`int`): posición, `width`, `height` (`int`): dimensiones, `fill` (`string`): carácter de relleno (ej: `"█"`, `"░"`, `" "`), `foreground` (`array<int,3>`): color de texto o `COLOR_DEFAULT`, `background` (`array<int,3>`): color de fondo o `COLOR_DEFAULT` | `void` | Imprime línea por línea con `GoToXY()`. Aplica color ANSI via `Color()`. |
| Dibujar texto multilínea con color | `DrawText` | `inline void DrawText(int x, int y, int width, int height, std::vector<std::string> text, std::array<int, 3> foreground, std::array<int, 3> background)` | `x`, `y` (`int`): posición, `width` (`int`): ancho máximo (-1 = sin límite), `height` (`int`): alto máximo (-1 = sin límite), `text` (`vector<string>`): líneas de texto, `foreground`, `background` (`array<int,3>`): colores | `void` | Renderiza texto línea por línea. Si una línea excede `width`, la divide con `CutString`. |
| Dibujar fondo de pantalla completo | `DrawBackground` | `inline void DrawBackground()` | Ninguno | `void` | Llena toda la pantalla (`WIDTH_SCREEN × HEIGHT_SCREEN`) con `EMPTY_BLOCK`, foreground negro y background `BACKGROUND`. Equivale a pintar el canvas base. |
| Dibujar caja primaria con texto centrado | `PrintPrimaryBox` | `inline void PrintPrimaryBox(int x, int y, int width, int height, std::vector<std::string> text, std::array<int, 3> textColor, std::array<int, 3> borderColor, std::array<int, 3> fillColor)` | `x`, `y` (`int`): posición, `width`, `height` (`int`): dimensiones, `text` (`vector<string>`): líneas de texto interior, `textColor` (`array<int,3>`), `borderColor` (`array<int,3>`), `fillColor` (`array<int,3>`) | `void` | Dibuja una caja decorativa con borde superior (`LOWER_HALF_BLOCK`), borde inferior (`UPPER_HALF_BLOCK`), bordes laterales (`FULL_BLOCK`), relleno de color, y texto centrado horizontal y verticalmente. |

---

## 12. Sprites / Animation

### `Common/Sprite.h`

Renderizado simple de sprites ASCII/UTF-8 en terminal.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Dibujar un sprite estático | `DrawSprite` | `inline void DrawSprite(int x, int y, const std::vector<std::string>& sprite)` | `x`, `y` (`int`): posición de la esquina superior izquierda, `sprite` (`vector<string>`): frame completo con saltos de línea internos | `void` | Imprime cada línea del sprite en la posición correspondiente usando `DrawText`. No posiciona el cursor antes — usar `GoToXY` si se necesita una posición específica. |
| Animar una secuencia de sprites | `DrawAnimatedSprite` | `inline void DrawAnimatedSprite(int x, int y, const std::vector<std::vector<std::string>>& sprites, int gapTime, int iterations)` | `x`, `y` (`int`): posición, `sprites` (`vector<vector<string>>`): vector de frames, `gapTime` (`int`): delay entre frames en ms, `iterations` (`int`): cantidad de repeticiones de toda la secuencia | `void` | Reproduce la secuencia de frames `iterations` veces, con `gapTime` milisegundos entre cada frame. No hace `Sleep()` después del último frame. No limpia frames anteriores. |

---

## 13. Navigation

### `Common/Navigation.h`

Funciones de detección de teclas de navegación y manejo de selección cíclica.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Detectar tecla flecha arriba | `IsKeyArrowTop` | `inline bool IsKeyArrowTop(std::vector<int>& userKey)` | `userKey` (`vector<int>&`): bytes de la tecla | `bool` | `true` si coincide con `KEY_ARROW_TOP` o `KEY_ARROW_TOP_2`. |
| Detectar tecla flecha abajo | `IsKeyArrowBottom` | `inline bool IsKeyArrowBottom(std::vector<int>& userKey)` | `userKey` (`vector<int>&`): bytes de la tecla | `bool` | `true` si coincide con `KEY_ARROW_BOTTOM` o `KEY_ARROW_BOTTOM_2`. |
| Detectar tecla flecha izquierda | `IsKeyArrowLeft` | `inline bool IsKeyArrowLeft(std::vector<int>& userKey)` | `userKey` (`vector<int>&`): bytes de la tecla | `bool` | `true` si coincide con `KEY_ARROW_LEFT` o `KEY_ARROW_LEFT_2`. |
| Detectar tecla flecha derecha | `IsKeyArrowRight` | `inline bool IsKeyArrowRight(std::vector<int>& userKey)` | `userKey` (`vector<int>&`): bytes de la tecla | `bool` | `true` si coincide con `KEY_ARROW_RIGHT` o `KEY_ARROW_RIGHT_2`. |
| Actualizar opción seleccionada con navegación cíclica | `SetOption` | `inline void SetOption(int& option, const int& minOption, const int& maxOption, std::vector<int>& userKey)` | `option` (`int&`): índice actual (se modifica), `minOption` (`const int&`): valor mínimo, `maxOption` (`const int&`): valor máximo, `userKey` (`vector<int>&`): bytes de la tecla | `void` | Flecha arriba/izquierda decrementa (con wrap: `minOption → maxOption`). Flecha abajo/derecha incrementa (con wrap: `maxOption → minOption`). Comportamiento de orbe/bucle. |
| Verificar si es tecla de acción (Enter/Space) | `IsActionKey` | `inline bool IsActionKey(std::vector<int>& byteChar)` | `byteChar` (`vector<int>&`): bytes de la tecla | `bool` | `true` si coincide con alguna entrada de `ACTION_KEYS`. |
| Verificar si es tecla de navegación (flechas) | `IsNavigationKey` | `inline bool IsNavigationKey(std::vector<int>& byteChar)` | `byteChar` (`vector<int>&`): bytes de la tecla | `bool` | `true` si coincide con alguna entrada de `NAVIGATION_KEYS`. |

---

## 14. Audio

### `Common/Music.h` (Fachada)

Incluye `Windows/Music.h` o `Linux/Music.h` según `_WIN32`. API unificada: una sola instancia de audio a la vez.

### `Common/Windows/Music.h`

Backend: MCI (Media Control Interface) de Win32. Alias interno: `"audio"`.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Reproducir archivo de audio | `PlayAudio` | `inline void PlayAudio(const std::string& file)` | `file` (`string`): ruta al archivo MP3/WAV | `void` | Detiene reproducción anterior, abre el archivo con MCI y reproduce. No bloquea (background). |
| Reproducir audio en bucle infinito | `PlayAudioLoop` | `inline void PlayAudioLoop(const std::string& file)` | `file` (`string`): ruta al archivo MP3/WAV | `void` | Igual que `PlayAudio` pero con flag `"repeat"`. Detener con `StopAudio()`. |
| Detener y cerrar audio | `StopAudio` | `inline void StopAudio()` | Ninguno | `void` | Detiene y cierra el alias `"audio"`. Seguro llamar sin audio activo. |
| Pausar audio (mantener posición) | `PauseAudio` | `inline void PauseAudio()` | Ninguno | `void` | Pausa la reproducción. Reanudar con `ResumeAudio()`. |
| Reanudar audio desde pausa | `ResumeAudio` | `inline void ResumeAudio()` | Ninguno | `void` | Solo funciona si se llamó `PauseAudio()` antes. |

### `Common/Linux/Music.h`

Backend: `ffplay` (ffmpeg) como proceso hijo. Control por PID global.

| Trigger (¿Cuándo usar?) | Función/Símbolo | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| PID del proceso de audio actual | `g_audioPid` | `inline pid_t g_audioPid` | — | `pid_t` | `0` = ninguno activo. Se actualiza internamente por `PlayAudio`/`PlayAudioLoop`. |
| Detener proceso hijo de audio | `KillAudioProcess` | `inline void KillAudioProcess()` | Ninguno | `void` | Función auxiliar interna. Envía `SIGTERM`, espera con `waitpid`, resetea `g_audioPid` a 0. |
| Reproducir archivo de audio | `PlayAudio` | `inline void PlayAudio(const std::string& file)` | `file` (`string`): ruta al archivo MP3/WAV | `void` | `fork()` + `execlp("ffplay", "-nodisp", "-autoexit", ...)`. Requiere ffmpeg instalado. |
| Reproducir audio en bucle infinito | `PlayAudioLoop` | `inline void PlayAudioLoop(const std::string& file)` | `file` (`string`): ruta al archivo MP3/WAV | `void` | Igual que `PlayAudio` pero con `-loop 0`. |
| Detener y cerrar audio | `StopAudio` | `inline void StopAudio()` | Ninguno | `void` | Llama a `KillAudioProcess()`. |
| Pausar audio (mantener posición) | `PauseAudio` | `inline void PauseAudio()` | Ninguno | `void` | Envía `SIGSTOP` al proceso hijo (lo congela). |
| Reanudar audio desde pausa | `ResumeAudio` | `inline void ResumeAudio()` | Ninguno | `void` | Envía `SIGCONT` al proceso hijo. |

---

## 15. Output

### `Common/Output.h`

Funciones de salida de mensajes de estado al usuario.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Mostrar mensaje de feedback al usuario | `PrintFeedBackMessage` | `void PrintFeedBackMessage()` | Ninguno (usa variables globales `feedbackMessage`, `rowFeedbackMessage`, `colFeedbackMessage`) | `void` | Limpia la línea de feedback (usando `MAX_FEEDBACK_MESSAGE_LENGTH`), reposiciona cursor y imprime `feedbackMessage`. **Nota**: incluye directamente `Windows/Terminal.h` (ver Notas de Bugs). |

---

## 16. Components UI

### `Common/Components/InputComponent.h`

Componentes de entrada de texto.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Renderizar caja de texto (sin interacción) | `TextBoxComponent` | `inline void TextBoxComponent(int x, int y, int width, int height, std::string &input, std::string label = "", std::string message = "", std::string replaceChar = "")` | `x`, `y` (`int`): posición, `width`, `height` (`int`): dimensiones, `input` (`string&`): texto actual (se renderiza), `label` (`string`): etiqueta encima de la caja, `message` (`string`): mensaje debajo de la caja, `replaceChar` (`string`): carácter de enmascaramiento (ej: `"*"` para contraseñas) | `void` | Dibuja caja de input con fondo `SELECTION_BACKGROUND`, label centrado arriba, mensaje abajo, cursor visual con `QUADRANTS[5]`. |
| Componente de input interactivo completo | `InputComponent` | `inline void InputComponent(int x, int y, int width, int height, std::string& input, std::string label = "", std::string message = "", std::string replaceChar = "")` | Mismos que `TextBoxComponent` | `void` | Loop bloqueante: renderiza `TextBoxComponent`, lee teclas con `ReadConsoleChar()`. Enter confirma, Backspace borra, alfanuméricos se agregan. Actualiza `input` por referencia. |

### `Common/Components/SelectComponent.h`

Componentes de selección de opciones.

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Renderizar menú de selección (sin interacción) | `StaticSelectComponent` | `inline void StaticSelectComponent(int x, int y, std::array<int, 3> backgroundColor, std::array<int, 3> selectedColor, std::vector<std::string> &options, int selectedOption, std::array<std::string,2> selectedPadding = {"", ""}, std::array<int, 2> verticalPadding = {0, 0}, int innerGap = 0)` | `x`, `y` (`int`): posición, `backgroundColor` (`array<int,3>`): fondo de opciones no seleccionadas, `selectedColor` (`array<int,3>`): fondo de opción seleccionada, `options` (`vector<string>&`): textos de las opciones, `selectedOption` (`int`): índice de la opción seleccionada, `selectedPadding` (`array<string,2>`): padding izquierdo/derecho de la opción seleccionada, `verticalPadding` (`array<int,2>`): padding superior/inferior del bloque, `innerGap` (`int`): espacio entre opciones | `void` | Dibuja lista de opciones con fondo `SELECTION_BACKGROUND`. La opción seleccionada se resalta con `selectedColor` y foreground negro. |
| Componente de selección interactivo completo | `SelectComponent` | `inline void SelectComponent(int x, int y, std::array<int, 3> backgroundColor, std::array<int, 3> selectedColor, std::vector<std::string> options, int &selectedOption, std::array<std::string,2> selectedPadding = {"", ""}, std::array<int, 2> verticalPadding = {0, 0}, int innerGap = 0)` | Mismos que `StaticSelectComponent` (options por valor, selectedOption por referencia) | `void` | Loop bloqueante: renderiza `StaticSelectComponent`, navega con flechas arriba/abajo (wrap cíclico), confirma con Enter. Actualiza `selectedOption` por referencia. |

### `Common/Components/LifeBar.h`

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Dibujar barra de vida con degradado | `DrawLifeBar` | `void DrawLifeBar(int x, int y, int gradientLength, std::array<int, 3> initColor, std::array<int, 3> endColor, std::array<int, 3> background)` | `x`, `y` (`int`): posición inicial, `gradientLength` (`int`): ancho de la barra en caracteres, `initColor` (`array<int,3>`): color del extremo izquierdo (ej: verde), `endColor` (`array<int,3>`): color del extremo derecho (ej: rojo), `background` (`array<int,3>`): color de fondo (no utilizado en implementación actual) | `void` | Genera un degradado de `gradientLength` colores con `Gradient()` y dibuja cada celda como un `FULL_BLOCK` de color. Barra horizontal que va de verde (vida alta) a rojo (vida baja). |

### `Common/Components/BottomBar.h`

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Dibujar barra inferior de estado | `DrawBottomBar` | `void DrawBottomBar()` | Ninguno | `void` | Dibuja un rectángulo de 3 filas de alto en la parte inferior de la pantalla (`HEIGHT_SCREEN - 3`), color `BLUE`, que cubre todo el ancho (`WIDTH_SCREEN`). |

### `Common/Components/TransitionComponent.h`

| Trigger (¿Cuándo usar?) | Función | Firma | Parámetros | Devuelve | Descripción |
|---|---|---|---|---|---|
| Ejecutar transición visual de pantalla | `TransitionComponent` | `inline void TransitionComponent()` | Ninguno | `void` | Animación de transición: genera un degradado rojo→amarillo que se desplaza horizontalmente de izquierda a derecha con ruido aleatorio pixel a pixel. Oculta cursor, ejecuta la animación, y reposiciona cursor al final. Duración proporcional a `WIDTH_SCREEN`. |

---

## Cross-References

Which games use which Common utilities:

| Utility | Used By |
|---------|---------|
| `Aligned.h` | [Pokemon](docs/Pokemon.md), [MainMenu](docs/MainMenu.md) |
| `Color.h` | [Pokemon](docs/Pokemon.md), [MainMenu](docs/MainMenu.md) |
| `Components/BottomBar.h` | [Pokemon](docs/Pokemon.md) |
| `Components/InputComponent.h` | [Pokemon](docs/Pokemon.md), [MainMenu](docs/MainMenu.md) |
| `Components/LifeBar.h` | [Pokemon](docs/Pokemon.md) |
| `Components/SelectComponent.h` | [MainMenu](docs/MainMenu.md) |
| `Components/TransitionComponent.h` | [MainMenu](docs/MainMenu.md) |
| `Consts.h` | [Pokemon](docs/Pokemon.md), [Buscaminas](docs/Buscaminas.md), [MainMenu](docs/MainMenu.md), [InvasionEspacial](docs/InvasionEspacial.md) |
| `Font.h` | [Pokemon](docs/Pokemon.md), [MainMenu](docs/MainMenu.md) |
| `Graphics.h` | [Pokemon](docs/Pokemon.md), [MainMenu](docs/MainMenu.md) |
| `Input.h` | [Pokemon](docs/Pokemon.md), [Buscaminas](docs/Buscaminas.md), [MainMenu](docs/MainMenu.md), [InvasionEspacial](docs/InvasionEspacial.md) |
| `Music.h` | _(Tests only — no game uses directly)_ |
| `Navigation.h` | [Pokemon](docs/Pokemon.md), [Buscaminas](docs/Buscaminas.md), [InvasionEspacial](docs/InvasionEspacial.md) |
| `Output.h` | [Buscaminas](docs/Buscaminas.md) |
| `Sprite.h` | [Pokemon](docs/Pokemon.md), [MainMenu](docs/MainMenu.md) |
| `Terminal.h` | [Pokemon](docs/Pokemon.md) |
| `Theme.h` | [Pokemon](docs/Pokemon.md), [MainMenu](docs/MainMenu.md) |
| `UnicodeGlyphs.h` | [Pokemon](docs/Pokemon.md) |
| `Utils.h` | [Pokemon](docs/Pokemon.md), [MainMenu](docs/MainMenu.md) |
| `Variables.h` | [Pokemon](docs/Pokemon.md), [Buscaminas](docs/Buscaminas.md), [InvasionEspacial](docs/InvasionEspacial.md) |

> **Notes**:
> - [BatallaNaval](docs/BatallaNaval.md) and [Tictactoe](docs/Tictactoe.md) do not use Common utilities — they have their own platform abstractions.
> - `Music.h` is included only by test files; no game currently uses it at runtime.

---

## Diagrama de Dependencias

```
                           ┌─────────────────┐
                           │   Consts.h       │
                           │ (WIDTH/HEIGHT)   │
                           └────────┬────────┘
                                    │
         ┌──────────────────────────┼──────────────────────────┐
         ▼                          ▼                          ▼
   ┌──────────┐             ┌──────────────┐          ┌──────────────┐
   │ Keys.h   │◄──────►     │  Terminal.h  │          │  Variables.h │
   │ (OS-spec)│    incl.    │ (OS-spec)    │          │ (global)     │
   └────┬─────┘             └──────┬───────┘          └──────┬───────┘
        │                          │                         │
        ▼                          ▼                         ▼
   ┌──────────┐             ┌──────────────┐          ┌──────────────┐
   │ Input.h  │             │  Graphics.h  │          │  Output.h    │
   │ Nav.h    │◄──────►     │  Color.h     │◄──────►  │              │
   └────┬─────┘   usa       │  Sprite.h    │          └──────────────┘
        │                   │  Theme.h     │
        │                   │  Aligned.h   │
        │                   │  Utils.h     │
        │                   └──────┬───────┘
        │                          │
        ▼                          ▼
   ┌────────────────────────────────────────────┐
   │          Components/                        │
   │  InputComponent  SelectComponent            │
   │  LifeBar  BottomBar  TransitionComponent    │
   └────────────────────────────────────────────┘
```

### Flujo de dependencias detallado

```
Consts.h
  ├── include → Windows/Keys.h  (si _WIN32)
  ├── include → Linux/Keys.h    (si no _WIN32)
  │
Terminal.h  (fachada)
  ├── include → Windows/Terminal.h  (si _WIN32)
  ├── include → Linux/Terminal.h    (si no _WIN32)
  └── define  → GoToEnd()
  │
Music.h  (fachada)
  ├── include → Windows/Music.h  (si _WIN32)
  └── include → Linux/Music.h    (si no _WIN32)
  │
Color.h       ← (independiente)
Theme.h       ← (independiente)
UnicodeGlyphs.h ← (independiente)
Font.h        ← (independiente)
Utils.h       ← (independiente)
Aligned.h     ← include Utils.h
  │
Input.h       ← include Terminal.h, Consts.h
Navigation.h  ← include Consts.h
  │
Graphics.h    ← include Consts.h, Terminal.h, Theme.h,
                UnicodeGlyphs.h, Color.h, Utils.h, Aligned.h
  │
Sprite.h      ← include Color.h, Graphics.h, Terminal.h,
                UnicodeGlyphs.h
  │
Output.h      ← include Consts.h, Variables.h, Windows/Terminal.h
  │
Components/
  ├── InputComponent.h   ← Graphics.h, Aligned.h, Theme.h,
  │                         Consts.h, Variables.h, Input.h
  ├── SelectComponent.h  ← Input.h, Color.h, Graphics.h,
  │                         Utils.h, Variables.h
  ├── LifeBar.h          ← Color.h, Graphics.h, Terminal.h,
  │                         Theme.h, UnicodeGlyphs.h
  ├── BottomBar.h        ← Color.h, Graphics.h, Terminal.h,
  │                         Theme.h, UnicodeGlyphs.h
  └── TransitionComponent.h ← Consts.h, Theme.h, Graphics.h,
                               UnicodeGlyphs.h, Color.h, Terminal.h
```
