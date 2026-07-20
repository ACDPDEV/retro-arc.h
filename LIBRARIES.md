# Common Libraries - retro-arc.h

## Overview
Librerías header-only para desarrollo de aplicaciones TUI (Terminal User Interface) cross-platform (Windows/Linux). Proveen desde primitivas de dibujo hasta componentes de UI interactivos.

---

## Core - Primitivas Fundamentales

### Terminal.h
**Propósito**: API unificada de terminal cross-platform.
**Dependencias**: `Consts.h`, `Windows/Terminal.h` o `Linux/Terminal.h` (según SO).

**Funciones principales**:
- `EnableTrueColor()` / `DisableTrueColor()` - Habilitar/deshabilitar colores 24-bit
- `EnableUTF8()` / `DisableUTF8()` - Soporte UTF-8
- `GoToXY(x, y)` - Posicionar cursor
- `Clear()` / `ClearConsoleLine(width)` - Limpiar pantalla/línea
- `Kbhit()` / `Getch()` - Lectura no-bloqueante de teclado
- `Sleep(ms)` - Pausa en milisegundos
- `GetConsoleWidth()` / `GetConsoleHeight()` - Dimensiones de terminal
- `SetCursorVisible(bool)` / `ShowCursor()` / `HideCursor()` - Control del cursor

**Úsalo cuando**: Necesites cualquier interacción directa con la terminal (posicionamiento, input raw, dimensiones, control de cursor).

---

### Color.h
**Propósito**: Utilidades de color True Color (24-bit RGB) para terminales ANSI.
**Dependencias**: Ninguna (solo std).

**Funciones y constantes**:
- `COLOR_DEFAULT` / `TRANSPARENT` (`{-1,-1,-1}`) - Centinela "no cambiar color"
- `Color(foreground, background)` - Genera secuencia de escape ANSI para colores
- `ResetColor()` - Resetea atributos de color
- `SetTerminalColor(fg, bg)` - Cambia color de toda la consola (limpia pantalla)
- `Gradient(steps, start, end)` - Genera vector de colores en degradado
- `isTransparent(color)` - Verifica si es transparencia

**Úsalo cuando**: Necesites aplicar colores RGB a texto o fondos. `TRANSPARENT` permite cambiar solo un canal (solo foreground o solo background).

---

### Utils.h
**Propósito**: Utilidades de manejo de strings UTF-8 con soporte ANSI escape.
**Dependencias**: Ninguna.

**Funciones principales**:
- `Length(str)` - Longitud visible de string (ignora secuencias ANSI y cuenta Unicode correctamente)
- `CutString(str, width)` - Corta string en líneas de ancho máximo
- `InvertString(str)` - Invierte un string
- `MaxString(strings)` - Retorna el string más largo de un vector
- `RepeatString(str, count)` - Repite un string N veces
- `ArrayToVector(arr)` - Convierte `std::array<string, 9>` a `std::vector<string>`

**Úsalo cuando**: Trabajes con strings que contengan caracteres Unicode o secuencias de color ANSI y necesites medir su longitud visible real.

---

### Aligned.h
**Propósito**: Cálculo de posiciones para alineación de elementos UI.
**Dependencias**: `Utils.h` (para `Length()`).

**Funciones**:
- `AlignedX(x, width, childWidth, alignment)` - Calcula posición X con alineación ("center", "right", "left")
- `AlignedY(y, height, childHeight, alignment)` - Calcula posición Y con alineación ("center", "bottom", "top")
- `RelativeX(x, childX)` / `RelativeY(y, childY)` - Posiciones relativas

**Úsalo cuando**: Necesites centrar, alinear a la derecha, o posicionar elementos dentro de un contenedor padre.

---

## Graphics - Dibujo en Terminal

### Graphics.h
**Propósito**: Funciones de dibujo TUI de alto nivel para cuadros y formas.
**Dependencias**: `Terminal.h`, `UnicodeGlyphs.h`, `Theme.h`, `Color.h`, `Utils.h`, `Aligned.h`, `Consts.h`.

**Funciones principales**:
- `DrawRawBox(x, y, w, h, borders..., corners...)` - Cuadro con bordes personalizados
- `DrawBox(x, y, w, h, borders[4], corners[4])` - Cuadro con estilos predefinidos (índices 0-6)
- `DrawRawHorizontalLine(x, y, len, left, center, right)` - Línea horizontal
- `DrawRawVerticalLine(x, y, len, top, center, bottom)` - Línea vertical
- `DrawFillRectangle(x, y, w, h, fill, fg, bg)` - Rectángulo relleno con color
- `DrawText(x, y, w, h, text, fg, bg)` - Texto multilinea con wrap automático
- `DrawBackground()` - Fondo completo con color de tema
- `PrintPrimaryBox(...)` - Cuadro con borde sólido y texto centrado

**Úsalo cuando**: Dibujes interfaces TUI con cuadros, rectángulos de color, o texto posicionado.

---

### UnicodeGlyphs.h
**Propósito**: Constantes de caracteres Unicode para bordes, esquinas, bloques y glifos especiales.
**Dependencias**: Ninguna.

**Constantes clave**:
- `BORDERS[7][4]` - Estilos de borde: vacío, punteado fino, punteado, simple, grueso, doble, cuadrantes
- `CORNERS[6][4]` - Estilos de esquina: vacío, simple, grueso, doble, redondeado, cuadrantes
- `FULL_BLOCK`, `UPPER_HALF_BLOCK`, `LOWER_HALF_BLOCK`, `EMPTY_BLOCK` - Bloques de relleno
- `QUADRANTS[6]` - Caracteres de cuadrantes para pixel-art
- `BOX DRAWING` - Líneas de dibujo de cajas

**Úsalo cuando**: Necesites caracteres Unicode para interfaces TUI (bordes de cuadros, bloques de relleno, pixel-art).

---

### Sprite.h
**Propósito**: Renderizado de sprites ASCII/UTF-8 con soporte de animación.
**Dependencias**: `Color.h`, `Graphics.h`, `Terminal.h`, `UnicodeGlyphs.h`.

**Funciones**:
- `DrawSprite(x, y, sprite)` - Dibuja un sprite (vector de strings) en posición específica
- `DrawAnimatedSprite(x, y, sprites, gapTime, iterations)` - Anima secuencia de frames con delay

**Úsalo cuando**: Tengas sprites pre-renderizados (strings con saltos de línea) que quieras mostrar o animar.

---

### Font.h
**Propósito**: Fuentes ASCII art para letras A-Z (mayúsculas), a-z (minúsculas), 0-9 y símbolos.
**Dependencias**: Ninguna.

**Contenido**:
- `FONT_A` a `FONT_Z` - Letras mayúsculas (9 líneas de alto)
- `FONT_a` a `FONT_z` - Letras minúsculas (4 líneas de alto)
- `FONT_0` a `FONT_9` - Números (4 líneas de alto)
- `FONT_BLANK`, `FONT_DOT`, `FONT_EXCLAMATION` - Caracteres especiales
- `ConcatFont(fontChars, separator)` - Concatena múltiples caracteres con separador

**Úsalo cuando**: Necesites texto grande estilo "banner" o "marquee" en terminal.

---

## Input - Entrada de Usuario

### Input.h
**Propósito**: Parsing y validación de entrada de usuario, lectura de teclado.
**Dependencias**: `Terminal.h` (para `Kbhit`, `Getch`), `Consts.h`.

**Funciones de parsing**:
- `Validate(input, type)` - Valida si entrada coincide con tipo ("int", "float", "string", "char", "bool")
- `ParseInt(str)` / `ParseIntStrict(str)` - Conversión a entero (con/sin validación estricta)
- `ParseFloat(str)` - Conversión a float
- `ParseChar(str)` / `ParseBool(str)` - Conversión a char/bool

**Funciones de entrada**:
- `Input()` - Lee palabra desde stdin (bloqueante)
- `TryInput(line)` - Intenta leer línea de forma no-bloqueante (con backspace/eco)
- `ReadConsoleChar()` - Lee tecla presionada (retorna vector de bytes, soporta Unicode/teclas especiales)
- `ReadConsoleChar(validRanges)` - Lee tecla con validación de rangos permitidos
- `CastKeyToString(byteChar)` - Convierte bytes de tecla a string imprimible
- `IsAlphaNumChar(byteChar)` - Verifica si es alfanumérico
- `IsValidChar(ranges, char)` / `IsValidChar(validChars, char)` - Validación de caracteres

**Úsalo cuando**: Necesites leer entrada del usuario con validación, o manejar teclas especiales/flechas.

---

### Keys.h (Windows/Linux)
**Propósito**: Constantes de códigos de teclas por plataforma.
**Dependencias**: Ninguna (seleccionado por `#ifdef _WIN32` en `Consts.h`).

**Constantes**:
- `KEY_ENTER`, `KEY_SPACE`, `KEY_BACKSPACE`, `KEY_ESCAPE` - Teclas de acción
- `KEY_ARROW_TOP/LEFT/BOTTOM/RIGHT` + variantes `_2` - Flechas de navegación
- `KEY_A` a `KEY_Z`, `KEY_A_LOWER` a `KEY_Z_LOWER` - Letras
- `KEY_A_ACCENT_CAPS/LOWER` a `KEY_U_ACCENT_CAPS/LOWER` - Vocales con acento
- `KEY_ENYE_CAPS/LOWER` - Ñ/ñ
- `KEY_0` a `KEY_9` - Números
- `NAVIGATION_KEYS` - Vector de todas las teclas de navegación
- `ACTION_KEYS` - Vector de teclas de acción (Enter, Space)
- `ALPHA_NUM_CHARS` - Vector de todos los caracteres alfanuméricos

**Úsalo cuando**: Necesites comparar teclas presionadas con constantes nombradas.

---

### Navigation.h
**Propósito**: Utilidades de navegación en menús y opciones.
**Dependencias**: `Consts.h` (para constantes de teclas).

**Funciones**:
- `IsKeyArrowTop/Bottom/Left/Right(key)` - Verifica dirección de flecha (incluye variantes)
- `SetOption(option, min, max, key)` - Actualiza índice de opción con comportamiento circular (loop)
- `IsActionKey(byteChar)` - Verifica si es tecla de acción (Enter/Space)
- `IsNavigationKey(byteChar)` - Verifica si es tecla de navegación

**Úsalo cuando**: Implementes menús navegables con flechas y selección circular.

---

## Theme - Paleta de Colores

### Theme.h
**Propósito**: Paleta de colores "Matte Black" (inspirada en Omarchy).
**Dependencias**: Ninguna.

**Constantes de color**:
- `BACKGROUND` - Fondo base `{31, 34, 38}`
- `FOREGROUND_LIGHT` / `FOREGROUND_DARK` - Texto claro/oscuro
- `ACCENT` - Color de acento `{230, 142, 13}`
- `CURSOR` - Color del cursor
- `SELECTION_BACKGROUND` / `SELECTION_FOREGROUND` - Colores de selección
- Colores nombrados: `SOFT_GREEN`, `LIGHT_GREEN`, `GRAY`, `LIGHT_BLUE`, `BLUE`, `ORANGE`, `SOFT_RED`, `CREAM`, `RED`, `DARK_RED`, `YELLOW`

**Úsalo cuando**: Necesites colores consistentes para tu UI. Todos los componentes usan esta paleta por defecto.

---

## State - Estado Global

### Variables.h
**Propósito**: Variables globales del namespace Common.
**Dependencias**: Ninguna.

**Variables**:
- `key` - Vector de bytes de la última tecla presionada
- `character` - String del carácter actual
- `feedbackMessage` - Mensaje de feedback para mostrar
- `rowFeedbackMessage` / `colFeedbackMessage` - Posición del mensaje de feedback
- `playerName` - Nombre del jugador (default: "Player 1")

**Úsalo cuando**: Necesites acceder al estado compartido entre componentes.

---

### Consts.h
**Propósito**: Constantes de dimensiones y configuración del sistema.
**Dependencias**: `Windows/Keys.h` o `Linux/Keys.h` (según SO).

**Constantes**:
- `WIDTH_SCREEN = 200` - Ancho de pantalla en caracteres
- `HEIGHT_SCREEN = 50` - Alto de pantalla en líneas
- `MAX_FEEDBACK_MESSAGE_LENGTH = 80` - Largo máximo de mensajes de feedback

**Úsalo cuando**: Necesites las dimensiones del "viewport" o configuración base.

---

### Output.h
**Propósito**: Impresión de mensajes de feedback en posición fija.
**Dependencias**: `Consts.h`, `Variables.h`, `Windows/Terminal.h`.

**Funciones**:
- `PrintFeedBackMessage()` - Imprime `feedbackMessage` en la posición configurada, limpiando la línea previa

**Úsalo cuando**: Muestres mensajes de estado/error que se actualizan en una posición fija de pantalla.

---

## Components - Componentes UI Reutilizables

### Components/BottomBar.h
**Propósito**: Barra inferior de navegación/acciones.
**Dependencias**: `Color.h`, `Graphics.h`, `Terminal.h`, `Theme.h`, `UnicodeGlyphs.h`.

**Funciones**:
- `DrawBottomBar()` - Dibuja barra de 3 líneas de alto en la parte inferior de pantalla

**Úsalo cuando**: Necesites una barra de estado o navegación en la parte inferior.

---

### Components/InputComponent.h
**Propósito**: Componente de entrada de texto interactivo con cursor.
**Dependencias**: `Graphics.h`, `Aligned.h`, `Theme.h`, `Consts.h`, `Variables.h`, `Input.h`.

**Funciones**:
- `TextBoxComponent(...)` - Renderiza caja de texto con label, mensaje y cursor (sin input loop)
- `InputComponent(...)` - TextBox interactivo con loop de input (acepta caracteres, backspace, enter para confirmar)
  - Parámetros: posición, dimensiones, referencia al string de input, label, mensaje de ayuda, carácter de reemplazo (para passwords)

**Úsalo cuando**: Necesites campos de texto editables (nombres, contraseñas, búsqueda).

---

### Components/SelectComponent.h
**Propósito**: Menú de selección interactivo con navegación por flechas.
**Dependencias**: `Input.h`, `Color.h`, `Graphics.h`, `Utils.h`, `Variables.h`.

**Funciones**:
- `StaticSelectComponent(...)` - Renderiza menú sin interacción (solo dibuja)
- `SelectComponent(...)` - Menú interactivo con navegación Up/Down y confirmación con Enter
  - Soporta: padding personalizado, gap interior, colores de fondo/selección

**Úsalo cuando**: Necesites menús de opciones navegables (menú principal, configuración, selección de nivel).

---

### Components/LifeBar.h
**Propósito**: Barra de vida/progreso con degradado de color.
**Dependencias**: `Color.h`, `Graphics.h`, `Terminal.h`, `Theme.h`, `UnicodeGlyphs.h`.

**Funciones**:
- `DrawLifeBar(x, y, gradientLength, initColor, endColor, background)` - Dibuja barra horizontal con degradado

**Úsalo cuando**: Muestres barras de progreso, vida, o cualquier valor con representación visual gradual.

---

### Components/TransitionComponent.h
**Propósito**: Efecto de transición animada entre pantallas.
**Dependencias**: `Consts.h`, `Theme.h`, `Graphics.h`, `UnicodeGlyphs.h`, `Color.h`, `Terminal.h`.

**Funciones**:
- `TransitionComponent()` - Ejecuta animación de transición de izquierda a derecha con gradiente rojo-amarillo y ruido aleatorio

**Úsalo cuando**: Necesites una transición visual entre pantallas o estados del juego.

---

## Dependency Graph

```
Terminal.h ─┬─> Color.h ─┬─> Graphics.h ─┬─> Sprite.h
             │            │               │
             │            │               ├─> Components/BottomBar.h
             │            │               ├─> Components/InputComponent.h
             │            │               ├─> Components/LifeBar.h
             │            │               ├─> Components/TransitionComponent.h
             │            │               └─> Components/SelectComponent.h
             │            │
             │            └─> UnicodeGlyphs.h
             │
             ├─> Input.h ─┬─> Components/InputComponent.h
             │            └─> Components/SelectComponent.h
             │
             ├─> Navigation.h (usa Keys.h via Consts.h)
             │
             └─> Output.h (usa Variables.h)

Utils.h ──> Aligned.h ──> Graphics.h

Theme.h ──> Graphics.h, Components/*
Consts.h ──> Keys.h (Windows/Linux)
Variables.h ──> Output.h, Components/*
```

---

## Quick Reference - ¿Qué usar?

| Necesidad | Librería |
|-----------|----------|
| Posicionar cursor | `Terminal.h` → `GoToXY()` |
| Leer tecla del usuario | `Input.h` → `ReadConsoleChar()` |
| Comparar tecla con nombre | `Keys.h` (constantes `KEY_*`) |
| Navegar menú con flechas | `Navigation.h` → `SetOption()` |
| Dibujar cuadro/borde | `Graphics.h` → `DrawBox()` / `DrawRawBox()` |
| Rectángulo de color | `Graphics.h` → `DrawFillRectangle()` |
| Texto posicionado | `Graphics.h` → `DrawText()` |
| Medir longitud real de string | `Utils.h` → `Length()` |
| Campo de texto editable | `Components/InputComponent.h` → `InputComponent()` |
| Menú de opciones | `Components/SelectComponent.h` → `SelectComponent()` |
| Barra de vida/progreso | `Components/LifeBar.h` → `DrawLifeBar()` |
| Animar sprite | `Sprite.h` → `DrawAnimatedSprite()` |
| Texto grande ASCII art | `Font.h` + `ConcatFont()` |
| Aplicar color RGB | `Color.h` → `Color()` / `ResetColor()` |
| Transición entre pantallas | `Components/TransitionComponent.h` → `TransitionComponent()` |
| Fondo de tema | `Graphics.h` → `DrawBackground()` |
| Alinear elemento | `Aligned.h` → `AlignedX()` / `AlignedY()` |

---

## Platform Notes

- **Windows**: Usa Win32 Console API + `conio.h` para input (`Kbhit`/`Getch`).
- **Linux**: Usa POSIX termios (modo raw) + ANSI nativo. `InitTerminalRawMode()` se llama automáticamente al incluir `Terminal.h`.
- **UTF-8**: Ambas plataformas soportan caracteres Unicode de 1-4 bytes. `Length()` en `Utils.h` maneja correctamente la longitud visible.
- **True Color**: Requiere `EnableTrueColor()` una vez al inicio del programa.
