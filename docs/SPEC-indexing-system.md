# Specification: Project Indexing System

**Version**: 2.0
**Date**: 2026-07-19
**Status**: Draft
**Scope**: Tier 1 indexing for AI agent navigation and project documentation

---

## 1. Project Index Manifest (INDEX.md)

### 1.1 Structure

The `INDEX.md` file provides a complete machine-readable manifest of the project. Format: Markdown with structured sections.

```markdown
# PROC1 Project Index

> Auto-generated manifest. Do not edit manually — use `scripts/gen-index.sh`.

**Last Updated**: {ISO-8601 timestamp}
**File Count**: {N} (.h + .cpp only, excludes binaries/scripts)
**Namespace Count**: {M}
**Excluded**: .atl/, .git/, build/, *.o, *.ogg, *.mp3, *.bat

---

## Directory Tree

```
PROC1/
├── Common/
│   ├── Components/
│   │   └── {6 files: BottomBar, InputComponent, LifeBar, SelectComponent, SelectPrimaryBox, TransitionComponent}
│   ├── Linux/
│   │   └── {3 files: Keys, Music, Terminal}
│   ├── Windows/
│   │   └── {3 files: Keys, Music, Terminal}
│   └── {12 .h files + 2 .md docs}
├── Juegos/
│   ├── BatallaNaval/
│   ├── Buscaminas/
│   ├── Invasion Espacial/
│   ├── Pokemon/
│   └── Tictactoe/
├── MainMenu/
│   ├── Commands/
│   ├── Components/
│   ├── Database/
│   ├── Sprites/
│   └── Views/
├── Tests/
└── main.cpp
```

---

## Module Index

### Common
**Namespace**: `Common`
**Purpose**: Shared utilities for graphics, input, output, terminal, navigation
**Platform Variants**: Linux/, Windows/ (each contains Keys.h, Music.h, Terminal.h)
**Dependencies**: Standard C++ libraries only
**Components/**: BottomBar.h, InputComponent.h, LifeBar.h, SelectComponent.h, SelectPrimaryBox.h, TransitionComponent.h

| File | Purpose | Key Functions | Key Variables | Depends On |
|------|---------|---------------|---------------|------------|
| Aligned.h | Text alignment utilities | AlignLeft, AlignRight, AlignCenter | — | — |
| Color.h | Color definitions and ANSI codes | GetColorCode, ApplyColor | COLOR_* constants | Terminal.h |
| Consts.h | Project-wide constants | — | WIDTH_SCREEN, HEIGHT_SCREEN, MAX_FEEDBACK_MESSAGE_LENGTH | — |
| Font.h | Font loading and rendering | LoadFont, DrawText | DEFAULT_FONT | Terminal.h |
| Graphics.h | Drawing primitives | DrawBox, DrawLine, DrawSprite | — | Color.h, Terminal.h |
| Input.h | Keyboard/mouse input handling | GetKey, GetMousePosition | — | Terminal.h |
| Music.h | Sound/music playback | PlaySound, StopMusic | — | — |
| Navigation.h | Menu navigation system | NavigateMenu, HandleSelection | — | Input.h |
| Output.h | Text output helpers | PrintAt, ClearScreen | — | Terminal.h |
| Sprite.h | Sprite loading and display | LoadSprite, RenderSprite | — | Graphics.h |
| Terminal.h | Terminal mode management (facade) | GoToEnd | — | Linux/ or Windows/ |
| Theme.h | Color themes | ApplyTheme, GetTheme | THEME_* constants | Color.h |
| UnicodeGlyphs.h | Unicode character maps | GetGlyph, RenderGlyph | GLYPH_* constants | — |
| Utils.h | General utilities | Clamp, Random, Timer | — | — |
| Variables.h | Global variable declarations | — | key, character, feedbackMessage, playerName | — |

### Juegos/BatallaNaval
**Namespace**: `BatallaNaval`
**Purpose**: Battleship game implementation
**Dependencies**: Common

| File | Purpose | Key Functions | Key Variables | Depends On |
|------|---------|---------------|---------------|------------|
| b_n_4.cpp | Main game logic | InitGame, PlaceShips, FireShot | board[][], ships[] | Common/Graphics.h |

### Juegos/Buscaminas
**Namespace**: `Buscaminas`
**Purpose**: Minesweeper game implementation
**Dependencies**: Common

| File | Purpose | Key Functions | Key Variables | Depends On |
|------|---------|---------------|---------------|------------|
| Buscaminas.h | Game header | — | — | Common/*.h |
| Buscaminas.cpp | Main game logic | InitBoard, RevealCell, CheckWin | minefield[][], revealed[][] | BuscaminasFunctions.h |
| BuscaminasDatabase.h | Data persistence | LoadGame, SaveGame | — | — |
| BuscaminasFunctions.h | Utility functions | CountMines, IsValidCell | — | — |
| BuscaminasFunctions.cpp | Function implementations | — | — | BuscaminasFunctions.h |
| BuscaminasService.h | Game services | NewGame, GetStatus | — | — |

### Juegos/Invasion Espacial
**Namespace**: `InvasionEspacial`
**Purpose**: Space Invaders game implementation
**Dependencies**: Common

| File | Purpose | Key Functions | Key Variables | Depends On |
|------|---------|---------------|---------------|------------|
| colisiones.h | Collision detection | CheckCollision | — | — |
| consola2.h | Console utilities | InitConsole | — | Common/Terminal.h |
| disparos.h | Shooting mechanics | FireBullet, UpdateBullets | bullets[] | — |
| figuras.h | Shape definitions | DrawAlien, DrawPlayer | — | Common/Graphics.h |
| juego.h | Game loop | RunGame, UpdateEntities | score, lives | — |
| juego version 4.cpp | Main implementation | — | — | juego.h |
| main.cpp | Entry point | main() | — | juego.h |
| movimientos.h | Movement logic | MovePlayer, MoveAliens | — | — |
| pantallas.h | Screen management | ShowMenu, ShowGameOver | — | Common/Output.h |

### Juegos/Pokemon
**Namespace**: `Pokemon`
**Purpose**: Pokemon-style RPG battle game
**Dependencies**: Common
**Note**: Largest module (~30 files). Split into sub-chunks for Engram.

| Subdir/File | Purpose | Key Functions | Key Variables | Depends On |
|-------------|---------|---------------|---------------|------------|
| Pokemon.cpp | Main game entry | InitGame, RunBattle | — | Common/*.h |
| Pokemon.h | Game header | — | — | — |
| Commands/AttackCommand.h | Attack action | ExecuteAttack | — | Models/Pokemon.h |
| Commands/BagCommand.h | Bag access | OpenBag, UseItem | — | Models/Bag.h |
| Commands/Command.h | Command interface | Execute | — | — |
| Commands/RunCommand.h | Run action | AttemptRun | — | — |
| Commands/SwitchPokemonCommand.h | Switch active Pokemon | SwitchTo | — | Models/Player.h |
| Components/TitleComponent.h | Title display | RenderTitle | — | Common/Graphics.h |
| Database/MockData.h | Test data | GetMockPlayer | — | Models/*.h |
| Factories/PokemonFactory.h | Pokemon creation | CreatePokemon | — | Models/Pokemon.h |
| Functions/BuildTeam.h | Team building | BuildStarterTeam | — | Models/*.h |
| Game/Battle.h | Battle system | StartBattle, ProcessTurn | — | Models/*.h |
| Game/Game.h | Game manager | InitGame, RunGameLoop | — | — |
| Game/Round.h | Round logic | ExecuteRound | — | Battle.h |
| Models/Antidote.h | Status cure item | Use | — | Item.h |
| Models/Bag.h | Inventory | AddItem, RemoveItem, GetItems | items[] | Item.h |
| Models/Item.h | Base item | Use | — | — |
| Models/Move.h | Base move | Use | — | — |
| Models/PhysicalMove.h | Physical attack | Use | — | Move.h |
| Models/Player.h | Player state | AddPokemon, GetActivePokemon | team[] | Pokemon.h |
| Models/Pokemon.h | Pokemon entity | TakeDamage, UseMove | hp, level, moves[] | Move.h |
| Models/Potion.h | Healing item | Use | — | Item.h |
| Models/SpecialMove.h | Special attack | Use | — | Move.h |
| Models/StatusMove.h | Status effect move | Use | — | Move.h |
| Models/SuperPotion.h | Strong healing item | Use | — | Item.h |
| PokemonAnimatedSprites/* | Animated sprite data (*.h) | — | — | — |
| PokemonStaticSprites/* | Static sprite data (*.h) | — | — | — |
| PokemonFigures.h | ASCII art figures | DrawPikachu, DrawSquirtle | — | — |
| PokemonFunctions.h | Utility functions | CalculateDamage | — | — |
| PokemonMusic.h | Music definitions | PlayBattleMusic | — | Common/Music.h |
| PokemonSounds.h | Sound effects | PlayCry | — | Common/Music.h |
| PokemonUI.h | UI rendering | DrawBattleUI | — | Common/Graphics.h |
| PokeballLaunch_Left.h | Animation sprite | — | — | — |
| PokeballLaunch_Right.h | Animation sprite | — | — | — |
| Sprites/*.h | Character sprites (Mochila, Trainer1, Trainer2) | — | — | — |
| Views/HuidaView.h | Run attempt screen | Render | — | Common/Output.h |
| Views/MenuView.h | Main menu | Render | — | Common/Navigation.h |
| Views/MochilaView.h | Bag screen | Render | — | Models/Bag.h |
| Views/PlayersView.h | Player selection | Render | — | Models/Player.h |
| Views/PokemonSelectionView.h | Pokemon selection | Render | — | Models/Pokemon.h |
| Views/TitleView.h | Title screen | Render | — | Common/Output.h |
| Views/VictoryView.h | Victory screen | Render | — | Common/Output.h |

### Juegos/Tictactoe
**Namespace**: `Tictactoe`
**Purpose**: Tic Tac Toe game implementation
**Dependencies**: Common

| File | Purpose | Key Functions | Key Variables | Depends On |
|------|---------|---------------|---------------|------------|
| console.h | Console utilities | InitConsole | — | Common/Terminal.h |
| console.cpp | Console implementation | — | — | console.h |
| game.h | Game logic header | — | — | — |
| game.cpp | Game implementation | MakeMove, CheckWinner, ResetBoard | board[3][3] | Common/Graphics.h |
| main.cpp | Entry point | main() | — | game.h |

### MainMenu
**Namespace**: `MainMenu`
**Purpose**: Application main menu and navigation
**Dependencies**: Common

| File | Purpose | Key Functions | Key Variables | Depends On |
|------|---------|---------------|---------------|------------|
| MainMenu.h | Menu header | — | — | Common/*.h |
| Commands/Auth.h | Authentication | Login, ValidatePassword | — | Database/Env.h |
| Components/TitleComponent.h | Title display | RenderTitle | — | Common/Graphics.h |
| Database/Env.h | Environment config | GetEnv | — | — |
| Database/Labels.h | UI labels | GetLabel | LABEL_* constants | — |
| Database/Options.h | Menu options | GetOptions | OPTION_* constants | — |
| Sprites/ArcadeLeft.h | Left arcade sprite | — | — | Common/Sprite.h |
| Sprites/ArcadeRight.h | Right arcade sprite | — | — | Common/Sprite.h |
| Views/MainMenuView.h | Main menu | Render | — | Common/Navigation.h |
| Views/PasswordView.h | Password input | Render, HandleInput | — | Common/Input.h |
| Views/PresentationView.h | Splash screen | Render | — | Common/Output.h |
| Views/WrongPasswordView.h | Error screen | Render | — | Common/Output.h |

### Tests
**Namespace**: `Tests`
**Purpose**: Manual compilation tests (no test framework)
**Dependencies**: Common, individual modules

| File | Purpose | What It Tests | Depends On |
|------|---------|---------------|------------|
| ColorTest.cpp | Color system | ANSI color codes | Common/Color.h |
| ComponentTest.cpp | UI components | Component rendering | Common/Components/ |
| FontTest.cpp | Font system | Font loading/rendering | Common/Font.h |
| GraphicsTest.cpp | Graphics primitives | Drawing functions | Common/Graphics.h |
| InputTest.cpp | Input handling | Keyboard/mouse capture | Common/Input.h |
| MainMenuTest.cpp | Main menu | Menu navigation | MainMenu/*.h |
| MenuViewTest.h | Menu view tests | View rendering | MainMenu/Views/ |
| MinesweeperTest.h | Buscaminas | Game logic | Juegos/Buscaminas/*.h |
| MusicTest.cpp | Music/sound | Audio playback | Common/Music.h |
| PokemonTest.cpp | Pokemon game | Game mechanics | Juegos/Pokemon/*.h |
| PokemonViewTest.cpp | Pokemon views | View rendering | Juegos/Pokemon/Views/*.h |
| TestingGradients.cpp | Gradient rendering | Color gradients | Common/Color.h |
| TestingGraphics/ | Graphics tests subdirectory | Box drawing, etc. | Common/Graphics.h |
| arceus.h | Pokemon sprite data | — | — |
| rayquaza.h | Pokemon sprite data | — | — |

**Non-indexable files** (excluded from manifest):
- `audio.ogg`, `Sound.mp3` — binary audio assets
- `*.o` — compiled object files
- `*.bat` — Windows scripts

---

## 2. Engram Index Configuration

### 2.1 Topic Key Structure

```
architecture/project-index              # Root index metadata
architecture/project-index/common       # Common/ module (full)
architecture/project-index/batallanaval # BatallaNaval/ module
architecture/project-index/buscaminas   # Buscaminas/ module
architecture/project-index/invasion     # InvasionEspacial/ module
architecture/project-index/pokemon      # Pokemon/ module (largest)
architecture/project-index/tictactoe    # Tictactoe/ module
architecture/project-index/mainmenu     # MainMenu/ module
architecture/project-index/tests        # Tests/ module
```

### 2.2 Chunking Strategy

Each chunk targets ≤2KB for optimal search. Pokemon is split further due to size.

| Chunk | Content | Approx Size | Priority |
|-------|---------|-------------|----------|
| `project-index` | Root: directory tree, module summary table, last updated | ~1KB | MUST |
| `project-index/common` | Common/ full file manifest with functions/variables | ~2KB | MUST |
| `project-index/pokemon` | Pokemon/ all subdirs (Models, Commands, Game, Views) | ~2KB | MUST |
| `project-index/mainmenu` | MainMenu/ full manifest with all subdirs | ~1.5KB | MUST |
| `project-index/batallanaval` | BatallaNaval/ (1 file) | ~0.3KB | SHOULD |
| `project-index/buscaminas` | Buscaminas/ (6 files) | ~0.8KB | SHOULD |
| `project-index/invasion` | InvasionEspacial/ (9 files) | ~1KB | SHOULD |
| `project-index/tictactoe` | Tictactoe/ (5 files) | ~0.6KB | SHOULD |
| `project-index/tests` | Tests/ manifest with test coverage mapping | ~1KB | SHOULD |

**Split rule**: If any single module exceeds 1.5KB, split by subdirectory (e.g., Pokemon gets sub-chunks for Models/, Commands/, Game/, Views/).

### 2.3 Search Patterns

| Query Pattern | mem_search Example | Expected Result |
|---------------|--------------------|-----------------|
| Project structure overview | `mem_search(query="project index directory structure")` | Root chunk |
| Find where a function lives | `mem_search(query="DrawBox function definition")` | Common chunk |
| Module dependencies | `mem_search(query="Pokemon depends on Common")` | Root or Pokemon chunk |
| Specific game logic | `mem_search(query="Battle ProcessTurn Pokemon")` | Pokemon chunk |
| UI/navigation help | `mem_search(query="Navigation menu system")` | Common or MainMenu chunk |
| Which file to edit | `mem_search(query="file containing InitBoard function")` | Relevant module chunk |
| Test coverage | `mem_search(query="test for Pokemon game")` | Tests chunk |
| New module scaffolding | `mem_search(query="game module structure Buscaminas")` | Buscaminas chunk (reference) |

**Query tips**:
- Include module name + function name for precision
- Use natural language for intent ("how to draw boxes" → Common/Graphics.h)
- Avoid single-word queries (too broad)
- Avoid full file paths (semantic search works better with concepts)

### 2.4 Update Mechanism

| Trigger | Action | Responsible |
|---------|--------|-------------|
| SDD archive phase | Validate INDEX.md matches code, regenerate if stale | `sdd-archive` skill |
| Manual file addition | Run `scripts/gen-index.sh --module <name>` | Developer or agent |
| New game/module added | Regenerate full index | Agent |
| Functions renamed | Regenerate affected module chunk | Agent |
| Session start | Agent reads INDEX.md or searches Engram | Agent |
| Binary files added | Log exclusion, do not add to manifest | Agent |

---

## 3. Maintenance Workflow

### 3.1 SDD Archive Validation

During the `sdd-archive` phase, the archive skill MUST:

1. Read current `INDEX.md`
2. Count `.h` and `.cpp` files in project (excluding `.git/`, `.atl/`, `build/`)
3. Compare against `File Count` in INDEX.md header
4. If mismatch > 0 files: flag INDEX.md as **STALE**
5. If stale: regenerate via `scripts/gen-index.sh`
6. Update Engram topics with new content

**Validation Rule**: INDEX.md is fresh if `File Count` matches actual count ± 2 (tolerance for INDEX.md itself, scripts, and non-code assets).

### 3.2 Generation Script (`scripts/gen-index.sh`)

**Purpose**: Auto-generate INDEX.md from filesystem.

**Inputs**:
- `--root <dir>` — Project root (default: `.`)
- `--output <file>` — Output file (default: `INDEX.md`)
- `--module <name>` — Regenerate single module only (optional)
- `--force` — Overwrite without confirmation
- `--dry-run` — Print diff without writing

**Logic**:
```
1. Find all .h and .cpp files (exclude .git/, .atl/, build/)
2. For each file:
   a. Skip binary/non-indexable (audio, .o, .bat)
   b. Parse namespace declaration: grep "namespace {name}"
   c. Parse function declarations: grep "inline.*(" | "void.*(" | "int.*("
   d. Parse variable declarations: grep "inline.*=" | "const.*="
   e. Parse #include directives
3. Build directory tree representation
4. Group files by namespace/directory
5. Generate markdown tables per module
6. Calculate statistics (file count, namespace count)
7. Write INDEX.md with ISO-8601 timestamp
```

**Output Format**: Valid INDEX.md per Section 1.1.

**Error Handling**:
- If a file cannot be read: skip and log warning to stderr
- If namespace detection fails: use parent directory name as fallback
- If output file exists and no `--force`: prompt confirmation (non-interactive = skip)
- If `--module` specified but unknown: list valid module names and exit

### 3.3 Manual Update Process

When to update manually:
- Adding a new game module under `Juegos/`
- Adding new Common utility header
- Major refactoring that changes file purposes
- After merging a feature branch

Process:
```bash
# Full regeneration
scripts/gen-index.sh

# Single module regeneration
scripts/gen-index.sh --module pokemon

# Preview changes without writing
scripts/gen-index.sh --dry-run
```

### 3.4 Staleness Detection

**Signals INDEX.md is stale**:
1. `File Count` doesn't match `find . \( -name "*.h" -o -name "*.cpp" \) | grep -v ".git" | grep -v ".atl" | grep -v "build" | wc -l`
2. New `.h`/`.cpp` files exist not listed in manifest
3. Deleted files still appear in manifest
4. `Last Updated` is > 7 days old AND git log shows commits since then
5. Namespace declarations changed but manifest doesn't reflect it

**Agent Detection Protocol** (on session start):
```bash
# Quick staleness check — run once, cache result
ACTUAL=$(find . \( -name "*.h" -o -name "*.cpp" \) \
  | grep -v ".git" | grep -v ".atl" | grep -v "build" | wc -l)
INDEXED=$(grep -c "^|" INDEX.md | head -1)  # Count table rows
DIFF=$((ACTUAL - INDEXED))
if [ "$DIFF" -gt 2 ] || [ "$DIFF" -lt -2 ]; then
  echo "STALE: INDEX.md has $INDEXED entries, project has $ACTUAL files"
  echo "Run: scripts/gen-index.sh"
fi
```

### 3.5 Rollback

If index generation produces incorrect output:
1. Check git: `git diff INDEX.md` to review changes
2. If bad: `git checkout -- INDEX.md` to restore previous version
3. If script bug: fix script, re-run with `--dry-run` first
4. Log the issue in Engram for future reference

---

## 4. AI Agent Integration

### 4.1 Session Start Protocol

Every agent session MUST execute this sequence:

```
STEP 1: mem_current_project
        → Confirms project identity

STEP 2: mem_search(query="project index directory structure", limit=1)
        → Retrieves root INDEX.md chunk from Engram

STEP 3: Read INDEX.md directly (if exists)
        → Verify freshness via staleness check (Section 3.4)
        → If stale: warn user, suggest regeneration

STEP 4: mem_search(query="{current task keywords}", limit=3)
        → Retrieves relevant module chunks

STEP 5: If task involves specific module:
        Read that module's section from INDEX.md
        → Avoids loading full index into context
```

**Context budget**: Never load more than 2 modules into context at once. Prefer reading a single module section from INDEX.md over loading the full file.

### 4.2 Module-Specific Work

**Scoping Rule**: Always narrow context to the relevant module.

| Task Type | Search Query | Files to Read |
|-----------|--------------|---------------|
| Fix bug in Pokemon battle | `query="Pokemon Battle ProcessTurn"` | `Juegos/Pokemon/Game/Battle.h` |
| Add new Common utility | `query="Common utilities functions"` | `Common/Utils.h` |
| Modify MainMenu navigation | `query="MainMenu navigation views"` | `MainMenu/Views/*.h` |
| Add new game module | `query="game module structure Buscaminas"` | Reference existing game structure |
| Work on tests | `query="Tests Pokemon test"` | `Tests/PokemonTest.cpp` |
| Modify Common Components | `query="Common Components UI"` | `Common/Components/*.h` |

### 4.3 Onboarding Flow

New contributors (human or agent) follow this sequence:

1. **Read README.md** — project overview and goals
2. **Read AGENTS.md** — constraints and rules (MANDATORY — no enums, no templates, no classes, no nullptr)
3. **Read docs/Common.md** — Common utilities documentation (Spanish)
4. **Read INDEX.md** — complete file manifest and relationships
5. **Search Engram** — check for past decisions on similar work
6. **Identify target module** — use INDEX.md to find relevant files
7. **Read module files** — understand current implementation

### 4.4 Search Optimization

**Effective Queries**:
- Include module name: "Pokemon Battle" not just "battle"
- Include function names: "DrawBox Graphics" not just "draw"
- Include file types: ".h files Common" for header listing
- Use natural language: "how does navigation work" → searches Navigation.h

**Avoid**:
- Single-word queries (too broad for semantic search)
- Quoting entire file paths (too specific — semantic search works on concepts)
- Searching for implementation details (read the file instead)

---

## 5. Success Criteria

### 5.1 Functional Requirements

| ID | Requirement | Priority |
|----|-------------|----------|
| FR-01 | INDEX.md MUST list every `.h` and `.cpp` file in project | MUST |
| FR-02 | Each file entry MUST include: path, purpose, key functions/variables | MUST |
| FR-03 | Directory tree MUST reflect actual filesystem structure | MUST |
| FR-04 | Module tables MUST document dependencies on Common/ | MUST |
| FR-05 | Engram chunks MUST be searchable via mem_search | MUST |
| FR-06 | `scripts/gen-index.sh` MUST auto-generate INDEX.md | MUST |
| FR-07 | Binary/non-code files MUST be excluded from manifest | MUST |
| FR-08 | SDD archive phase MUST validate INDEX.md freshness | SHOULD |
| FR-09 | Staleness detection MUST warn when index is outdated | SHOULD |
| FR-10 | Generation script MUST support `--dry-run` and `--module` flags | SHOULD |

### 5.2 Quality Requirements

| ID | Requirement | Metric |
|----|-------------|--------|
| QR-01 | Accuracy | 100% of `.h`/`.cpp` files listed match actual filesystem |
| QR-02 | Completeness | All public functions/variables documented per file |
| QR-03 | Freshness | INDEX.md updated within 7 days of any file change |
| QR-04 | Consistency | All entries follow identical table schema |
| QR-05 | Readability | Human-readable Markdown, no syntax errors |
| QR-06 | Machine-readable | Tables parseable by agents, consistent column count |
| QR-07 | Size budget | Engram chunks ≤ 2KB each |

### 5.3 Performance Requirements

| ID | Requirement | Target |
|----|-------------|--------|
| PR-01 | Engram search latency | < 2 seconds for any query |
| PR-02 | INDEX.md generation time | < 10 seconds for full regeneration |
| PR-03 | Staleness check time | < 3 seconds |
| PR-04 | Engram chunk size | ≤ 2KB per chunk |
| PR-05 | Session start context load | < 5 seconds total (2-3 mem_search calls) |

### 5.4 Usability Requirements

| ID | Requirement | Description |
|----|-------------|-------------|
| UR-01 | Self-documenting | INDEX.md readable without external docs |
| UR-02 | Low friction | `scripts/gen-index.sh` runs without configuration |
| UR-03 | Agent-friendly | Search patterns work with natural language queries |
| UR-04 | Human-friendly | Developers can manually edit if needed |
| UR-05 | Progressive detail | Root → Module → File granularity |

---

## Appendix A: Example File Entry

```markdown
| Pokemon/Game/Battle.h | Battle system: turn processing, damage calculation | StartBattle, ProcessTurn, CalculateDamage | activePokemon, turnCount | Models/Pokemon.h, Models/Move.h |
```

**Parsed Fields**:
- **Path**: `Pokemon/Game/Battle.h`
- **Purpose**: Battle system: turn processing, damage calculation
- **Key Functions**: StartBattle, ProcessTurn, CalculateDamage
- **Key Variables**: activePokemon, turnCount
- **Dependencies**: Models/Pokemon.h, Models/Move.h

---

## Appendix B: Engram Chunk Example

**Topic**: `architecture/project-index/pokemon`

```markdown
# Pokemon Module Index

Namespace: Pokemon | Dependencies: Common | Files: ~30

## Commands/
- AttackCommand.h: ExecuteAttack(player, move, target)
- BagCommand.h: OpenBag(player), UseItem(player, item)
- Command.h: Execute(context) — interface
- RunCommand.h: AttemptRun(player, enemy)
- SwitchPokemonCommand.h: SwitchTo(player, index)

## Game/
- Battle.h: StartBattle(p1, p2), ProcessTurn(turn), CalculateDamage(move, def)
- Game.h: InitGame(), RunGameLoop(), HandleInput()
- Round.h: ExecuteRound(battle, actions)

## Models/
- Pokemon.h: TakeDamage(amount), UseMove(move), GetStats()
- Player.h: AddPokemon(pkmn), GetActivePokemon(), GetTeam()
- Move.h: Use(user, target) — base
- Bag.h: AddItem(item), RemoveItem(id), GetItems()
- Item.h, Potion.h, SuperPotion.h, Antidote.h — items

## Views/
- BattleView.h: Render(battle state)
- MenuView.h: Render(options), HandleSelection()
- PokemonSelectionView.h: Render(team), SelectPokemon(index)
- VictoryView.h, HuidaView.h, MochilaView.h, PlayersView.h, TitleView.h
```

---

**END SPECIFICATION**
