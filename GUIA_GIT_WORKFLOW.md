# Git Workflow 

## Ramas

```
main                 ← protegida, siempre deployable
  ├── feature/*      ← 1 rama por tarea (horas–2 días)
  ├── fix/*          ← hotfixes urgentes
  └── release/vX.Y   ← solo si freeze/QA prolongado
```

**Nombres:** `feature/login-oauth`, `fix/login-loop` (kebab-case, 2-4 palabras).

---

## Flujo Diario

```bash
# 0. INICIO
git prechange                    # main limpio + actualizado

# 1. CREAR RAMA
git checkout -b feature/login-oauth

# 2. TRABAJO (commits convencionales)
git add -A && git commit -m "feat(auth): add Google OAuth callback"

# 3. ANTES DE PUSH
git fresh                        # rebase sobre origin/main

# 4. PUSH + PR
git push -u origin HEAD
# → Abrir PR en GitHub, asignar 1 reviewer

# 5. REVIEW (SLA 4h) — **en GitHub**
#   Arreglos → git fixup + git pushf

# 6. MERGE (CI verde + 1 approve) — **botón en GitHub**
#   "Squash and merge" + "Delete branch"

# 7. LIMPIEZA
git cleanup                      # main actualizado, ramas locales borradas

# 8. SIGUIENTE → git prechange
```

> **Reviews y merges se hacen en GitHub** por simplicidad: UI nativa, notificaciones, historial de review, squash merge automático, branch deletion automático.

---

## Reglas Clave

| Regla | Por qué |
|-------|---------|
| 1 PR = 1 tarea, ≤2 días | Evita merge hell |
| `git fresh` antes de push | Conflictos los resuelves tú |
| Commits `feat:`, `fix:`, `refactor:` | Historial limpio, changelog auto |
| Review cruzado (no el autor) | Bus factor ↑ |
| Rama se borra al mergear | Config: "Delete branch on merge" = ON |

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

> **Nota**: Usa ruta absoluta para que el alias `git prechange` funcione desde cualquier directorio dentro del repo.

**Aliases disponibles:** `prechange`, `fresh`, `cleanup`, `fixup`, `pushf`, `lg`

---

## Protección `main` (GitHub/GitLab)

- Require PR + 1 approval
- Require CI pass
- Require linear history (squash merge)
- Delete branch on merge
- Block force pushes

---

## Hotfix

```bash
git prechange
git checkout -b fix/critical-bug
# ... fix mínimo ...
git fresh && git push -u origin HEAD
# PR urgente → merge → tag v1.2.1
```

---

## Stacked PRs (si B depende de A)

```bash
git checkout feature/auth-base
git checkout -b feature/oauth-ui
# PR B con base: feature/auth-base
# Merge orden: A → main, luego B rebase → merge
```
