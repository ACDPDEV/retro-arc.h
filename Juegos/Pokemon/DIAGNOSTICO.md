# Diagnóstico técnico — Juego Pokémon

> Auditoría de solo lectura. Ruta: `Juegos/Pokemon`. Fecha: 2026-07-20.
> No se modificó código de juego; este documento es únicamente un informe de estado.

## Resumen general

El juego Pokémon es una batalla **PvP local por turnos para 2 jugadores** (no hay IA ni
mecánica de captura/exploración), construido en C++ header-only con una arquitectura clara y
razonablemente bien separada (MVC + patrón Command + Factory + Bridge + un *facade* de audio que
delega en el motor común `Common/Music`). La base de datos de especies, la matriz de efectividad
de tipos (18×18, verificada y correcta), las vistas interactivas de batalla y el sistema de sonido
(15/15 `.mp3` con disparador en Linux) están en buen estado. **Sin embargo, la rama está en mitad de
un refactor y no compila**: hay dos `#include` rotos (`Database/SpriteLookup.h` y
`Views/InstructionsView.h`, ambos inexistentes) que dependen del flujo de batalla y del menú de
instrucciones. A eso se suman varios bugs de lógica (conteo de rondas inflado, `RunCommand` con
condición invertida, la huida que muestra `VictoryView`, dos bugs de UI de entrada), abundante
código muerto de un módulo UI antiguo (`PokemonUI.h`) reemplazado por `BattleViews.h`, y defectos
de continuidad en la música de batalla (se reinicia cada turno). Caso aparte es la animación
`PokeballLaunch` (~452 KB): **no es un asset a eliminar sino una transición prevista aún sin
integrar** — debe reproducirse tras el título "FIGHT!" (pokébolas lanzadas) antes de mostrar los
Pokémon + interfaz; hoy solo vive dentro de una función demo con `while(true)`. El núcleo es sólido;
lo que falta es **cerrar el refactor, arreglar los includes, integrar la transición de inicio y
limpiar/depurar**.

---

## Estructura de carpetas

```
Juegos/Pokemon/
├── Pokemon.cpp / Pokemon.h        Punto de entrada + máquina de estados del menú
├── PokemonUI.h                    UI de batalla ANTIGUA (mayormente muerta)
├── PokeballLaunch_Left/Right.h    Assets de transición (~226 KB c/u) — SIN INTEGRAR
├── Bridge/        PokemonBridge.h            Puente estado global ↔ modelo OO
├── Commands/      Command, Attack, Switch, Run, Bag
├── Components/    TitleComponent.h
├── Controllers/   Game, Battle, Round, TurnController, PlayerController
├── Database/      PokemonDatabase, MockData, Effectiveness, State, Classes/
├── Enums/         GameOption, ChooseCommandOption
├── Factories/     PokemonFactory.h
├── Models/        Pokemon, Player, Move, Bag, Item, Potion, SuperPotion,
│                  FocusBand, Leftover, Effect, Enums/(PokemonType, EffectName)
├── Sound/         PokemonSound.h  (facade → Common/Music)
├── Sounds/        15 archivos .mp3
├── Views/         Title, Menu, Players, PokemonSelection, BattleViews,
│                  Mochila, Huida, Victory
├── PokemonMiniSprites/     8  (todos usados)
├── PokemonStaticSprites/   16 (8 Front usados, 8 Back huérfanos)
├── PokemonAnimatedSprites/ 16 (8 Front usados solo en Huida, 8 Back huérfanos)
└── Sprites/       Trainer1, Trainer2, Mochila (usados), PokeBall (huérfano)
```

---

## Tabla de archivos por rol y estado

| Archivo | Rol | Estado | Problemas detectados |
|---|---|---|---|
| **Pokemon.cpp** | TU de compilación (solo includes) | Inerte | Sin definiciones ni `main`; toda la lógica vive en headers inline |
| **Pokemon.h** | Entrada + FSM de menú + flujo puente | ⚠️ Parcial | `#include Views/InstructionsView.h` **roto** (l.4, invocado l.73); Config es stub (l.76 "proximamente"); determinación de ganador frágil (asume `maxPokemon==1`, empate→P1); la huida acaba mostrando `VictoryView` en vez de `HuidaView` (l.47-68) |
| **PokemonUI.h** | UI de batalla antigua + animación de inicio | 🔴 Roto/parcial | `#include Database/SpriteLookup.h` **roto** (l.19) → `GetPokemonSprites`/`SpriteSet` indefinidos; 7 funciones huérfanas reemplazadas por `BattleViews.h`; **rescatable**: `BattleBeginningTitleView` (l.120, en uso) y la animación de pokébola (l.156-162) que debe convertirse en transición de una pasada (hoy atrapada en `BattleBeginningAnimationView`, l.150-175, con datos hardcodeados y `while(true)` final) |
| **Bridge/PokemonBridge.h** | Estado global ↔ modelo | ⚠️ Parcial | `CreateGameFromState()` descarta el resultado de `BuildPlayers()` y devuelve un `Game` vacío ("Phase 3" sin terminar); `mockToDbId` hardcodeado |
| **Controllers/Game.h** | Fachada/orquestador | ✅ Completo | Includes muertos (`GameOption`, `PlayerController`); `maxPokemon=1` invalida el cambio de Pokémon |
| **Controllers/Battle.h** | Bucle de rondas + fin de combate | ⚠️ Parcial | **Bug conteo de rondas**: doble `++countRounds` (l.36 y l.50) → off-by-one; `NextRound()`/`Finish()` declaradas sin implementar; `IsFinished()` duplica `EvaluateBattle()` y no se usa |
| **Controllers/Round.h** | Ronda: recolección + ejecución de comandos | ⚠️ Parcial | TODO l.191 (sin feedback si el comando no ejecuta); si un comando falla `CanExecute` se aborta la ronda de AMBOS; sin orden por velocidad (P1 siempre primero); desreferencia comando sin null-check; IDs mágicos de curación (3/4) |
| **Controllers/TurnController.h** | Fábrica de comandos por turno | ✅ Completo | `case RUN` inalcanzable (Round resuelve huida inline); `QUIT`→`default nullptr` sin manejo aguas arriba |
| **Controllers/PlayerController.h** | Init de jugador (bag/equipo) | ⚠️ Parcial | **CORRECCIÓN (hallada durante implementación de la Fase 4 del batch de estabilización, ver `openspec/changes/pokemon-stabilization/`)**: la fila original decía "clase entera desconectada del flujo puente" — es **falso**, verificado por grep. `PokemonBridge::BuildPlayers()` (que `Pokemon.h` llama en cada batalla real) usa `FillBag`/`SetInitialActivePokemon` sin condición, y `BuildTeam` como fallback. Solo el TODO de `BuildTeam` (l.49, `ShowPokemonMenu()` inexistente, `pokemonId` hardcodeado a 0) sigue siendo un gap real, pero acotado a esa rama de fallback, no a la clase entera |
| **Commands/Command.h** | Interfaz base Command | ✅ Completo | — |
| **Commands/AttackCommand.h** | Ataque con efectividad | ✅ Completo | Sin null-check de Pokémon activo; sin STAB/aleatoriedad/precisión (posiblemente intencional) |
| **Commands/SwitchPokemonCommand.h** | Cambio de Pokémon | ✅ Completo | Irrelevante mientras `maxPokemon==1` |
| **Commands/RunCommand.h** | Huida | 🔴 Roto + muerto | **Lógica invertida** (l.20): `isAlive = IsFainted()` → un Pokémon vivo no podría huir; además nunca se instancia (Round hace la huida inline) |
| **Commands/BagCommand.h** | Uso de ítem | ✅ Completo | Sin null-check de Pokémon activo |
| **Models/Pokemon.h** | Entidad + daño/curación/efectos | ⚠️ Parcial | TODO l.142 (VENENO sin implementar; solo LEFTOVER activo); `IsFainted()` compara `double == 0`; typo `CalulateDamageReduction`; FOCUS_BAND por flag, no por Effect |
| **Models/Player.h** | Jugador (equipo, activo, bolsa) | ✅ Completo | `CanPlay()` desreferencia `activePokemon` sin null-check (l.121); `canUseFocusBand` seteado pero nunca leído |
| **Models/Move.h** | Movimiento | ⚠️ Parcial | Constructor por defecto deja miembros **sin inicializar** (basura, l.43-46); include muerto de `Effectiveness.h` |
| **Models/Effect.h / Enums/EffectName.h** | Efectos de estado | ⚠️ Parcial | Solo 2 valores (FOCUS_BAND, LEFTOVER); no existe VENENO pese al TODO; FOCUS_BAND nunca se instancia como Effect |
| **Models/{Potion,SuperPotion,FocusBand,Leftover,Item,Bag}.h** | Ítems | ✅ Completo | `SuperPotion` es subclase vacía (redundante); `Leftover.countActiveLeftovers` sin usar |
| **Database/Effectiveness.h** | Matriz de tipos 18×18 | ✅ Completo | Verificada por muestreo, correcta; sin `#pragma once` (estilo) |
| **Database/PokemonDatabase.h vs MockData.h** | Datos de especies / display | ⚠️ Inconsistente | HP/atributos **no coinciden** entre ambas (dos fuentes de verdad); `MockData` lista ítems "Antidoto"/"Revivir" sin clase que los implemente |
| **Database/State.h** | Estado global de partida (`inline`) | ✅ Completo | Globales mutables (acoplamiento fuerte); `pokemonPlayers` redundante |
| **Factories/PokemonFactory.h** | Fábrica de Pokémon | ✅ Completo | — |
| **Enums/GameOption.h** | Opciones de menú | 💀 Muerto | Enum completo sin usar en ninguna parte |
| **Enums/ChooseCommandOption.h** | Comandos de batalla | ✅ Completo | Rama `QUIT` no manejada aguas arriba |
| **Views/TitleView.h** | Pantalla de título | ✅ Completo | — |
| **Views/MenuView.h** | Menú genérico | 💀 Huérfano | Definido, nunca invocado |
| **Views/PlayersView.h** | Entrada de nombres | ⚠️ Bug | **Salto de turno**: los dos `InputComponent` (l.150 y l.153) van consecutivos sin drenar stdin; un byte ENTER extra (auto-repetición al mantener la tecla, o *typeahead*) del campo de P1 lo lee el campo de P2 y lo cierra al instante con nombre vacío. Causa raíz: no hay `tcflush`/limpieza de buffer entre lecturas bloqueantes (`InitTerminalRawMode` solo limpia `ICANON\|ECHO`) |
| **Views/PokemonSelectionView.h** | Selección 2×2 con mini-sprites | ⚠️ Riesgo | Mismo patrón de carryover: se invoca 2× desde `Pokemon.h:33/36` (P1 y P2) sin flush de stdin entre medias → un ENTER arrastrado puede saltar la selección de P2 (l.309 `IsActionKey`) |
| **Views/BattleViews.h** | Sistema de batalla ACTIVO | ⚠️ No compila | Funcionalmente completo, pero arrastra `PokemonUI.h`→`SpriteLookup.h` roto; menú ofrece "SONIDO" en vez de "POKEMON" |
| **Views/MochilaView.h** | Pantalla de mochila | 💀 Huérfano | Incluido pero nunca invocado (batalla usa `BagMenuView`) |
| **Views/HuidaView.h** | Animación de huida | ✅ Completo | Único consumidor de `PokemonAnimatedSprites` (solo `*Front`); índice sin verificación de rango. Nota: su mensaje (l.61) **ya** usa el formato correcto `"EL [pokemon] DE [jugador] HA HUIDO"` → referencia para arreglar VictoryView |
| **Views/VictoryView.h** | Pantalla de victoria | ⚠️ Bug | **Mensaje incompleto** (l.117 y l.221, duplicado): dice `"¡El " + winnerName + " ha ganado la batalla!"` (nombre del jugador) cuando debería ser `"¡El [pokemon] de [jugador] ha ganado la batalla!"`. El Pokémon ya es derivable con `MOCK_POKEMON[pokemonIndex].name` (mismo `pokemonIndex` que la l.55 usa para el sprite) — no hace falta dato nuevo del modelo. Además: duplicación masiva (redibuja título+gradiente+sprite en cada frame de confeti) |
| **Components/TitleComponent.h** | Logo/entrada de nombre | ✅ Completo | Copia innecesaria de `title` por valor |
| **Sound/PokemonSound.h** | Facade de audio → `Common/Music` | ⚠️ Parcial | `ResumeBattleMusic()` código muerto; toggle SONIDO duplicado (inline en Round vs facade); sin `srand()` para ataque genérico |

Assets (no leídos en detalle; auditados por referencia):

| Asset | Estado | Detalle |
|---|---|---|
| `PokeballLaunch_Left/Right.h` (~452 KB) | 🟡 Válido, sin integrar | 23 frames por lado (`*_ALL[i]`). Referidos en `PokemonUI.h:156-162` pero solo dentro de la demo con `while(true)` → hoy no se ejecutan. **Uso previsto**: transición "FIGHT!" → pokébolas lanzadas → Pokémon. NO eliminar (ver plan de transición) |
| `Sprites/PokeBall.h` | 💀 Huérfano | Ni incluido ni referenciado |
| `PokemonStaticSprites/*Back.h` (8) | 💀 Huérfanos | Sin referencias |
| `PokemonAnimatedSprites/*Back.h` (8) | 💀 Huérfanos | Se consumían vía el `SpriteLookup.h` ausente |
| `PokemonAnimatedSprites/*Front.h` (8) | ✅ Usados | Solo en `HuidaView` |
| `PokemonStaticSprites/*Front.h`, `MiniSprites`, `Trainer1/2`, `Mochila` | ✅ Usados | — |
| `Sounds/*.mp3` (15) | ✅ Usados | 15/15 con disparador en Linux |

---

## Elementos faltantes / mejoras (priorizados)

### 🔴 P0 — Bloqueantes de compilación (la rama no compila)
1. **`Database/SpriteLookup.h` inexistente** — incluido en `PokemonUI.h:19`; provee `GetPokemonSprites()`/`SpriteSet`, usados también en `BattleViews.h:178`. Rompe todo el flujo de batalla.
2. **`Views/InstructionsView.h` inexistente en Pokemon** — incluido en `Pokemon.h:4` e invocado en l.73 (solo existe en Tictactoe/Buscaminas).
3. **`Components/MenuOptions.h` inexistente** (hallado en verificación de compilación, no capturado en la auditoría original) — incluido en `Views/TitleView.h:18` (camino activo) y `Views/MenuView.h:13` (huérfano); ambos esperan de ahí `OPTIONS` (vector de labels) y `OPTION` (índice `int` seleccionado). Nunca existió en el historial de git. Bloquea la compilación igual que los dos anteriores.

### 🟠 P1 — Bugs funcionales
3. **`RunCommand::CanExecute` invertido** (`RunCommand.h:20`): `isAlive = IsFainted()`. (Mitigado hoy solo porque la clase está muerta.)
4. **Huida muestra `VictoryView` en vez de `HuidaView`** (`Pokemon.h:47-68`): la lógica de `winner` deja `HuidaView()` inalcanzable.
5. **Conteo de rondas inflado** (`Battle.h:36`+`:50`): doble incremento → off-by-one propagado a `WriteBackState`.
6. **Música de batalla se reinicia cada turno** (`StartBattleMusic` en `BattleMenuView`, invocada por ronda y jugador): `BattleContinuation.mp3` nunca progresa; el toggle SONIDO se auto-resetea al siguiente menú.
7. **`Move()` por defecto deja miembros sin inicializar** (`Move.h:43-46`); riesgo de basura si se instancia sin args.
8. **Ausencia de null-checks de `GetActivePokemon()`** en `AttackCommand`, `BagCommand`, `TurnController`, `Player::CanPlay`, `Round` (desreferencia de comando).
9. **Salto de turno al ingresar nombres** (`PlayersView.h:150-153`): sin flush de stdin entre los dos `InputComponent` consecutivos, un byte ENTER arrastrado del campo de P1 cierra el de P2 con nombre vacío. Mismo patrón de carryover en las dos llamadas a `PokemonSelectionView` (`Pokemon.h:33/36`). Arreglo (dirección): drenar stdin (`tcflush`/consumir `Kbhit` pendientes) al entrar a cada lectura bloqueante, o ignorar un ENTER inmediato sin actividad previa del campo.
10. **Mensaje de victoria sin el Pokémon** (`VictoryView.h:117` y `:221`): muestra el nombre del jugador en vez de `"¡El [pokemon] de [jugador] ha ganado la batalla!"`. El Pokémon se obtiene de `MOCK_POKEMON[pokemonIndex].name` (índice ya calculado en l.55); corregir en las **dos** ocurrencias (está duplicado). `HuidaView.h:61` ya lo hace bien; no hay pantalla de derrota separada (derrota = victoria del rival, misma vista).

### 🟡 P2 — Refactor incompleto / lógica pendiente
11. **`PokemonBridge::CreateGameFromState` no integra jugadores** en `Game` ("Phase 3" sin cerrar).
12. **Sin IA para el jugador 2/rival**: ambos lados son control manual por las mismas vistas.
13. **TODOs abiertos**: efectos de estado (VENENO, `Pokemon.h:142`), menú de selección de equipo (`PlayerController.h:49`, `ShowPokemonMenu()` inexistente), feedback "comando no ejecutable" (`Round.h:191`).
14. **Sin orden por velocidad** en la ronda (P1 siempre primero); IDs mágicos de ítems de curación (3/4).
15. **Inconsistencia de datos** `PokemonDatabase.h` vs `MockData.h` (HP distintos); ítems "Antidoto"/"Revivir" sin clase de modelo.

### 🟢 P3 — Sonido: mejoras y huecos
16. **Windows: todos los SFX son no-op** (`PlayAudioOverlay` es stub) → solo música, cero efectos.
17. **SFX bloqueantes en Linux** (`PlayAudioOverlay` usa `waitpid`) → micro-congelamientos al atacar/curar.
18. **Faltan SFX**: navegación de menús (mover cursor), confirmación en el menú principal/Title, cambio de Pokémon, BGM durante la selección de Pokémon (silencio), sonido de captura/pokébola.
19. `ResumeBattleMusic()` muerto; toggle SONIDO duplicado; sin `srand()` para el ataque genérico aleatorio.

### 🔵 P4 — Limpieza / deuda técnica
20. **Assets huérfanos reales**: `Sprites/PokeBall.h` + 16 sprites `*Back.h` sin referencias. **Nota: `PokeballLaunch_*` NO es huérfano** — es transición pendiente de integrar (ver sección siguiente), no eliminar.
21. **`PokemonUI.h`**: rescatar `BattleBeginningTitleView` + la animación de pokébola (para la transición); eliminar las 7 funciones huérfanas reemplazadas por `BattleViews.h`.
22. **Vistas/enums huérfanos**: `MenuView`, `MochilaView`, enum `GameOption`, `RunCommand`, `Battle::NextRound/Finish/IsFinished`.
23. Redibujado por frame en `VictoryView`; `SuperPotion` redundante; includes muertos varios; typo `CalulateDamageReduction`.

---

## Plan de transición de inicio de batalla (PokeballLaunch)

> Corrección: `PokeballLaunch_Left/Right.h` **no es código muerto a eliminar**. Es la animación de
> transición prevista entre el título "FIGHT!" y la aparición de los Pokémon + interfaz de batalla.
> Solo falta integrarla como estado de una pasada.

### Qué hace hoy `BattleBeginningAnimationView` (PokemonUI.h:150-175) y por qué no se integró

La función es un **prototipo/demo** que ya contiene la secuencia deseada, pero inutilizable tal cual:

1. `EnableUTF8` + `DrawBackground` + `HideCursor`.
2. **Lanzamiento de pokébola** (l.156-162): bucle único de 23 frames dibujando
   `PokeballLaunch_Left_ALL[i]` y `PokeballLaunch_Right_ALL[i]` con 100 ms/frame, en las posiciones
   `PokeballLaunch_1X/1Y` y `PokeballLaunch_2X/2Y` (consts l.45-46). **Esto es lo que hay que rescatar.**
3. `Clear` + `DrawBackground`.
4. **Aparición de los Pokémon**: `ShowPokemonSprites(1, 4)` (l.165) — 10 frames animados.
5. `PermanentBattleGraphicsView("PSYDUCK","ROCKRUFF",1,4,50,50,45,45)` (l.168) — escena estática.
6. `BattleOptionsView(...)` (l.170) — menú.
7. **`while (true) { ShowPokemonSprites(1,4); }`** (l.171-174) — bucle infinito final.

Por qué quedó fuera del flujo activo:
- **Valores hardcodeados** (IDs `1`/`4`, nombres `"PSYDUCK"/"ROCKRUFF"`, HP `50/50`,`45/45`): es una
  demo, no está cableada a los jugadores/Pokémon reales.
- **Depende del include roto** `SpriteLookup.h` vía `ShowPokemonSprites`/`PermanentBattleGraphicsView`
  (`GetPokemonSprites`) → hoy ni siquiera compila (es el P0 nº1).
- **No retorna** (`while(true)` final): inservible como transición dentro de un flujo lineal.
- El flujo real se **reimplementó en `BattleViews.h`** (`DrawBattleBackground`) y `Pokemon.h` va directo
  a `game.Start(...)`, saltándose por completo `PokemonUI.h`. La animación quedó huérfana en el refactor.

### Punto exacto de inserción (fin de "FIGHT!" → inicio de `BattleViews.h`)

En `Pokemon.h`, `case 0`:

```
l.40  BattleBeginningTitleView();   // título "FIGHT!" (termina aquí)
l.41  Common::Sleep(500);
      ─────────────  ← AQUÍ va la transición de pokébola  ─────────────
l.43  PokemonGame::Game game;
l.44  game.Start(players.first, players.second);   // entra a Round → BattleViews (interfaz real)
```

La transición se inserta **entre la l.41 y la l.43**: después de que el título "FIGHT!" termina y
antes de construir/arrancar el `Game` (que es quien dibuja la interfaz de batalla vía
`BattleViews::DrawBattleBackground`).

### Estructura propuesta: estado de una sola pasada (sin loop infinito)

Nueva función de una pasada, p. ej. `BattleIntroTransitionView(playerOne, playerTwo)` (o una
`BattleBeginningAnimationView` saneada), llamada en el hueco anterior. Secuencia lineal que **retorna**:

1. **Título "FIGHT!"** — ya lo hace `BattleBeginningTitleView()` (l.40); la transición empieza justo después.
2. **Pokébolas lanzadas** — el bucle de 23 frames (paso 2 de arriba) **una sola vez**, terminando en el
   último frame. Sin `while`.
3. **Aparición de los Pokémon** — la animación de 10 frames (`ShowPokemonSprites`) **una vez**, pero con
   los **IDs reales** de los Pokémon activos (de `selectedCurrentPokemonId[0/1]` o de
   `players.first/second.GetActivePokemon()`), no `1`/`4` hardcodeados.
4. **Interfaz de batalla** — dibujar la escena permanente **una vez** con `BattleViews::DrawBattleBackground`
   (el renderer ACTIVO), no con `PermanentBattleGraphicsView` (obsoleto). Luego `return`.
5. Control vuelve a `Pokemon.h` → `game.Start(...)` corre el bucle real de batalla.

Detalles a cuidar:
- Alinear `PokeballLaunch_1X/1Y`/`_2X/2Y` con las posiciones donde `DrawBattleBackground` coloca a cada
  Pokémon, para que la pokébola "aterrice" donde aparece el Pokémon.
- La transición debe ser **no bloqueante respecto al input** (drenar stdin al terminar, para no arrastrar
  un ENTER al primer menú de batalla — mismo cuidado que el bug de salto de turno, P1 nº9).

### Qué rescatar de `PokemonUI.h` y qué descartar

**Rescatar:**
- `BattleBeginningTitleView` (l.120) — ya en uso.
- La animación de pokébola (bucle 23 frames, l.156-162) + los `#include` de `PokeballLaunch_Left/Right.h`
  + las consts de posición (l.45-46).
- El **concepto** de `ShowPokemonSprites` (10 frames, l.54-66) — adaptándolo a IDs reales y resolviendo su
  dependencia de `GetPokemonSprites`/`SpriteLookup.h` (P0 nº1: restaurar `SpriteLookup.h` o re-apuntar a
  los arrays de sprites que ya usa `BattleViews`).

**Descartar** (reemplazado por `BattleViews.h`):
- `PermanentBattleGraphicsView` → usar `DrawBattleBackground`.
- `BattleOptionsView` y todas las `BattleOptionsFight*View` (menús ya reimplementados).
- El cuerpo demo de `BattleBeginningAnimationView` (hardcodeos + `while(true)`).

Resultado: `PokemonUI.h` queda reducido a `BattleBeginningTitleView` + la nueva transición de una pasada.

---

## 3 próximos pasos sugeridos (por impacto)

1. **Restaurar la compilación (P0).** Recrear o reconectar `Database/SpriteLookup.h` (definir `SpriteSet` + `GetPokemonSprites()` a partir de los sprites existentes) y añadir/redirigir `Views/InstructionsView.h` en Pokemon. Sin esto, nada del flujo de batalla ni de instrucciones arranca. Es el desbloqueo que habilita todo lo demás.

2. **Cerrar el refactor de flujo y arreglar los bugs de partida (P1/P2).** Integrar `BuildPlayers()` en `Game` (`PokemonBridge` "Phase 3"), corregir la determinación de ganador/huida en `Pokemon.h` (que `HuidaView` sea alcanzable), el doble conteo de rondas, `RunCommand` invertido, el **salto de turno al ingresar nombres** (flush de stdin en `PlayersView`/`PokemonSelectionView`) y el **mensaje de victoria sin Pokémon** (`VictoryView`), y decidir si `RunCommand`/`PlayerController` se cablean o se eliminan. Deja el bucle de batalla coherente de principio a fin. Con la compilación ya restaurada (paso 1), **integrar la transición de pokébola** (ver sección anterior) en el hueco de `Pokemon.h:41-43`.

3. **Estabilizar el audio de batalla y rellenar huecos (P3).** Mover `StartBattleMusic()` fuera del render por-turno para que el loop de `BattleContinuation.mp3` no se reinicie, unificar el toggle SONIDO en la facade (eliminar `ResumeBattleMusic` muerto o usarlo), y decidir el soporte de SFX en Windows (hoy silencioso). Como extra de bajo coste: SFX de navegación/confirmación de menús y BGM en la selección de Pokémon. Alto impacto en percepción de calidad con riesgo bajo.
