# Git Workflow

## Ramas

```
main                 ← protegida, siempre deployable
  ├── feature/*      ← 1 rama por tarea (horas–2 días)
  ├── fix/*          ← hotfixes urgentes
  └── release/vX.Y   ← solo si freeze/QA prolongado
```

**Nombres:** `feature/login-oauth`, `fix/login-loop` (kebab-case, 2–4 palabras).

---

## Flujo Diario

```bash
# 0. INICIO
git prechange                    # main limpio + actualizado

# 1. CREAR RAMA
git create feature/login-oauth

# 2. PRIMER COMMIT + PUBLICAR PR
git publish "feat(auth): add Google OAuth callback"

# Con descripción (opcional)
git publish \
  "feat(auth): add Google OAuth callback" \
  "Implementa el callback de OAuth.
Agrega validaciones.
Añade pruebas."

# 3. CONTINUAR DESARROLLO
git fresh                        # rebase sobre origin/main

# Nuevos commits para la misma PR
git upload "fix(auth): handle expired tokens"

# Con descripción (opcional)
git upload \
  "fix(auth): handle expired tokens" \
  "Corrige la validación de tokens expirados.
Añade pruebas."

# 4. REVIEW (SLA 4h) — GitHub
#   Arreglos → git fixup + git pushf

# 5. MERGE (CI verde + 1 approve) — GitHub
#   "Squash and merge" + "Delete branch"

# 6. LIMPIEZA
git cleanup

# 7. SIGUIENTE
git prechange
```

> **La PR solo se crea una vez** mediante `git publish`.
> Los commits posteriores se envían con `git upload`, actualizando automáticamente la PR existente.

---

## Reglas Clave

| Regla | Por qué |
|--------|----------|
| 1 PR = 1 tarea, ≤2 días | Evita merge hell |
| `git fresh` antes de publicar cambios | Resuelves conflictos antes del review |
| Commits `feat:`, `fix:`, `refactor:` | Historial limpio y changelog automático |
| Review cruzado (no el autor) | Bus factor ↑ |
| Squash Merge | Un commit limpio por funcionalidad |
| Rama se borra al mergear | Mantiene el repositorio limpio |

---

## Commits Convencionales

```
feat(auth): add Google OAuth callback
fix(login): prevent infinite redirect loop
refactor(auth): extract token validation
docs(api): update auth endpoints
test(auth): add OAuth integration tests
```

---

## Setup (una vez por persona)

```bash
# Linux / macOS / Git Bash (Windows)
git config --global include.path "$(pwd)/.gitconfig"

# PowerShell (Windows)
git config --global include.path "$(Get-Location)\.gitconfig"

# CMD (Windows)
git config --global include.path "%cd%\.gitconfig"
```

> **Nota:** Usa una ruta absoluta para que los aliases funcionen desde cualquier directorio del repositorio.

### Aliases disponibles

| Alias | Descripción |
|--------|-------------|
| `git prechange` | Cambia a `main` y la actualiza |
| `git fresh` | Rebase de la rama actual sobre `origin/main` |
| `git cleanup` | Actualiza `main` y elimina ramas locales ya mergeadas |
| `git create <rama>` | Crea una rama y cambia a ella |
| `git publish <título> [descripción]` | Add + Commit + Push + Crea la PR |
| `git upload <título> [descripción]` | Add + Commit + Push |
| `git fixup <commit>` | Crea un commit `--fixup` |
| `git pushf` | `push --force-with-lease` |
| `git lg` | Log compacto con grafo |

---

## Protección de `main`

- Require Pull Request
- Require 1 approval
- Require CI pass
- Require linear history
- Enable Squash Merge
- Delete branch on merge
- Block force pushes

---

## Hotfix

```bash
git prechange
git create fix/critical-bug

git publish \
  "fix(core): resolve critical crash" \
  "Corrige un acceso inválido a memoria."

# PR urgente → Merge → Tag v1.2.1
```

---

## Stacked PRs (si B depende de A)

```bash
git create feature/auth-base
# ...

git create feature/oauth-ui
# PR B con base: feature/auth-base

# Merge: A → main
git fresh

# Merge: B → main
```
