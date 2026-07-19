# AGENTS.md — Reglas del Proyecto PROC1

> Instrucciones para AI agents que trabajan en este proyecto.
> Lee `CommonDOCS.md` antes de tocar código.

---

## 1. Dependencias

- **SIEMPRE** usar las utilidades de `Common/` y leer `CommonDOCS.md` antes de tocar código.
- **NO** usar librerías externas. Solo:
  - Librerías estándar de C++ (`<array>`, `<vector>`, `<string>`, etc.)
  - Utilidades propias del proyecto (`Common/*.h`)
  - `array`, `vector`, `string` de las librerías estándar

## 2. Niveles de Complejidad Permitidos

### Tipos
- Tipos estándar de C++ + `string` + `vector` + `array`
- Utilidades del proyecto (`Common/*.h`)

### Paradigmas — PROHIBIDOS
- **NO** usar enums
- **NO** usar tipos genéricos (templates)
- **NO** usar objetos (clases con métodos)
- **NO** usar `nullptr`
- **NO** usar funcionalidades avanzadas de C++

### Punteros
- Usar la **mínima cantidad** de punteros
- Solo cuando es estrictamente necesario:
  - Modificar valores fuera del scope
  - Operaciones críticas donde crear una copia es demasiado costoso

### Control de Flujo
- Bucles: `for`, `while`, `do while`
- Switch
- Condicionales: `if`, `else`, `if else`

## 3. Estructura de Headers

Orden estricto en cada archivo `.h`:

```cpp
#pragma once

// 1. Librerías estándar
#include <array>
#include <string>
#include <vector>

// 2. Librerías propias (jerarquía + orden alfabético)
#include "Common/Utils.h"
#include "Common/Variables.h"

// (salto de línea entre cada grupo)
```

**Reglas:**
- `#pragma once` siempre primero
- `#include` de librerías estándar
- Salto de línea
- `#include` de librerías propias (orden jerárquico y alfabético)
- **NO** usar `use namespace ...;` en módulos

## 4. Namespaces Permitidos

| Namespace | Uso |
|-----------|-----|
| `Common` | Utilidades compartidas |
| `MainMenu` | Menú principal |
| `BatallaNaval` | Juego Batalla Naval |
| `Buscaminas` | Juego Buscaminas |
| `InvasionEspacial` | Juego Invasión Espacial |
| `Pokemon` | Juego Pokémon |
| `Tictactoe` | Juego Tic Tac Toe |

> Los namespaces de juegos coinciden con el nombre de su carpeta en `Juegos/`.

## 5. Estructura de Funciones

### Declaración (en el header)

```cpp
/// @brief Descripción breve de la función
/// @param arg1 Descripción del parámetro 1
/// @param arg2 Descripción del parámetro 2
/// @return Descripción del valor de retorno
inline type NameFunction(
    type arg1,
    type arg2,
    ...
);
```

### Definición (en el `.cpp` o después del header)

```cpp
inline type NameFunction(
    type arg1,
    type arg2,
    ...
) {
    ...
}
```

### Llamadas a funciones

```cpp
NameFunction(
    arg1,
    arg2,
    ...
);
```

**Reglas:**
- Declarar funciones **después del header** antes de definirlas
- Documentar **cada función** con `///` (Doxygen)
- Formato multi-línea para funciones con varios parámetros

## 6. Variables y Constantes

```cpp
// Constantes globales
const type CONST_NAME = valor;

// Variables globales
inline type variableName = valor;
```

## 7. Estructura del Proyecto

```
PROC1/
├── Common/           # Utilidades compartidas
│   ├── Aligned.h
│   ├── Color.h
│   ├── Components/   # Componentes reutilizables
│   ├── Consts.h
│   ├── Font.h
│   ├── Graphics.h
│   ├── Input.h
│   ├── Linux/        # Implementación Linux
│   ├── Music.h
│   ├── Navigation.h
│   ├── Output.h
│   ├── Sprite.h
│   ├── Terminal.h
│   ├── Theme.h
│   ├── UnicodeGlyphs.h
│   ├── Utils.h
│   ├── Variables.h
│   └── Windows/      # Implementación Windows
├── Juegos/           # Juegos del proyecto
│   ├── BatallaNaval/
│   ├── Buscaminas/
│   ├── Invasion Espacial/
│   ├── Pokemon/
│   └── Tictactoe/
├── MainMenu/         # Menú principal
│   ├── Commands/
│   ├── Components/
│   ├── Database/
│   ├── MainMenu.h
│   ├── Sprites/
│   └── Views/
├── Tests/            # Pruebas
├── docs/              ← NUEVO: Documentación del proyecto
├── CommonDOCS.md     # Documentación de Common
├── AGENTS.md
└── README.md
```

## 8. Subdivisión de Responsabilidades

Cada módulo/juego se organiza por carpetas:

| Carpeta | Responsabilidad |
|---------|----------------|
| `Models/` | Modelos de datos, estructuras |
| `Commands/` | Comandos, acciones del usuario |
| `Components/` | Componentes reutilizables |
| `Views/` | Vistas, renderizado |
| `Database/` | Persistencia de datos |
| `Sprites/` | Sprites (si aplica) |
| `Sounds/` | Sonidos (si aplica) |

## 9. Sistema de Documentación

### Archivos de Documentación
| Archivo | Propósito | Cuándo Leer |
|---------|-----------|-------------|
| `CommonDOCS.md` | Referencia de la biblioteca Common | Antes de usar cualquier utilidad de Common/ |
| `docs/{Game}.md` | Documentación específica del juego | Antes de modificar un juego |
| `docs/MainMenu.md` | Documentación del menú principal | Antes de modificar MainMenu/ |
| `docs/Tests.md` | Infraestructura de pruebas | Antes de agregar/modificar pruebas |

### Reglas de Documentación
- **SIEMPRE** leer el `.md` relevante antes de modificar un módulo
- **SIEMPRE** actualizar la documentación al agregar/cambiar funciones
- **SIEMPRE** incluir `@param` y `@return` en comentarios Doxygen
- La documentación de funciones en `.md` DEBE coincidir con la firma real del código
- Las referencias cruzadas DEBEN usar rutas relativas: `[texto](ruta/relativa.md)`

### Para Agentes de IA
- Comenzar con `AGENTS.md` (este archivo) para reglas de codificación
- Leer `CommonDOCS.md` para utilidades disponibles
- Leer `.md` específico del módulo para contexto antes de cambios
- Usar la sección de Referencia Rápida para búsqueda rápida de funciones
- Verificar Referencias Cruzadas para entender relaciones entre módulos

---

> **Importante**: Antes de implementar cualquier función o módulo, revisa `CommonDOCS.md` para entender las utilidades disponibles.
