![Logo](Assets/Logo.png)

# PROC1 — Retro-arc.h

Colección de juegos retro en **TUI (Terminal User Interface)** con núcleo cross-platform. Un proyecto académico que demuestra cómo crear experiencias de juego completas directamente en la terminal, con soporte para Linux y Windows.

---

## Juegos incluidos

| Juego | Descripción |
|-------|-------------|
| **Batalla Naval** | El clásico juego de estrategia por turnos contra la computadora |
| **Buscaminas** | El icónico juego de lógica con campos de minas |
| **Invasión Espacial** | Shoot 'em up con estética retro en la terminal |
| **Pokémon** | RPG por turnos inspirado en la franquicia |
| **Tic Tac Toe** | El eterno tres en raya |

Todos los juegos se ejecutan desde un **menú principal** que permite navegar entre ellos de forma cómoda.

---

## Características

- **Cross-platform**: funciona en Linux y Windows sin modificar código
- **Renderizado en terminal**: gráficos, colores y sprites usando caracteres Unicode
- **Sin dependencias externas**: solo librería estándar de C++ y utilidades propias
- **Navegación por teclado**: interfaz completa con flechas, Enter y Escape
- **Sistema de temas**: personalización visual del entorno de juego

---

## Requisitos

- Compilador C++ compatible con C++11 o superior (g++, clang++, MSVC)
- Terminal con soporte para caracteres Unicode (la mayoría de terminales modernas lo soportan)
- Linux o Windows

---

## Compilación y ejecución

```bash
# Compilar
g++ -std=c++11 -o proc1 main.cpp

# Ejecutar
./proc1
```

El juego principal se ejecuta desde la raíz del proyecto. Cada juego también puede compilarse de forma independiente desde su carpeta en `Juegos/`.

---

## Estructura del proyecto

```
PROC1/
├── Common/              # Biblioteca cross-platform de utilidades
│   ├── Graphics.h       #   Renderizado gráfico en terminal
│   ├── Input.h          #   Manejo de entrada del usuario
│   ├── Output.h         #   Salida y renderizado
│   ├── Color.h          #   Sistema de colores
│   ├── Sprite.h         #   Carga y renderizado de sprites
│   ├── Music.h          #   Efectos de sonido
│   ├── Terminal.h       #   Detección de plataforma
│   ├── Components/      #   Componentes UI reutilizables
│   ├── Linux/           #   Implementación específica Linux
│   └── Windows/         #   Implementación específica Windows
├── Juegos/              # Los 5 juegos del proyecto
│   ├── BatallaNaval/
│   ├── Buscaminas/
│   ├── Invasion Espacial/
│   ├── Pokemon/
│   └── Tictactoe/
├── MainMenu/            # Menú principal con navegación
├── Tests/               # Pruebas unitarias
├── docs/                # Documentación detallada
├── Assets/              # Sprites, logo y recursos
├── main.cpp             # Punto de entrada
└── CommonDOCS.md        # Referencia completa de la biblioteca Common
```

---

## Documentación

- [CommonDOCS.md](CommonDOCS.md) — Referencia completa de la biblioteca Common
- [docs/MainMenu.md](docs/MainMenu.md) — Documentación del menú principal
- [docs/BatallaNaval.md](docs/BatallaNaval.md) — Batalla Naval
- [docs/Buscaminas.md](docs/Buscaminas.md) — Buscaminas
- [docs/InvasionEspacial.md](docs/InvasionEspacial.md) — Invasión Espacial
- [docs/Pokemon.md](docs/Pokemon.md) — Pokémon
- [docs/Tictactoe.md](docs/Tictactoe.md) — Tic Tac Toe

---

## Licencia

Proyecto académico — Universidad Nacional de Trujillo.
