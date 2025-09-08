# Cub3D – Human-Readable Subject (v1.0)

## Table of Contents

- [1. Introduction](#1-introduction)
- [2. Project Goals](#2-project-goals)
- [3. General Rules](#3-general-rules)
- [4. Mandatory Part](#4-mandatory-part)
- [5. Bonus Part](#5-bonus-part)
- [6. Example Scenes](#6-example-scenes)
- [7. Submission & Peer Evaluation](#7-submission--peer-evaluation)

---

## 1. Introduction

Cub3D is inspired by Wolfenstein 3D, the first "First Person Shooter" (FPS) developed in 1992 by ID Software. This project will teach you ray-casting, a technique for rendering 3D scenes from a 2D map. Your goal: create a dynamic first-person view inside a maze, where you must find your way out.

---

## 2. Project Goals

- Practice rigor, C programming, and basic algorithms.
- Learn to use C for graphical design: windows, colors, events, shapes.
- Apply math practically (without needing deep theory).
- Use online resources and documentation.
- **Strongly recommended:** Test the original Wolfenstein 3D game before starting: [Wolfenstein 3D Online](http://users.atw.hu/wolf3d/)

---

## 3. General Rules

- **Language:** C only.
- **Coding Style:** Must follow 42 Norme, including bonus files.
- **Stability:** No unexpected crashes (segfault, bus error, double free, etc.).
- **Memory:** No leaks allowed.
- **Makefile:** Must include `all`, `clean`, `fclean`, `re`, `bonus`. Use strict flags: `-Wall -Wextra -Werror`.
- **Bonus:** Must be in separate `_bonus.c/h` files and built with a `bonus` Makefile rule.
- **Libft:** If used, copy into a `libft/` folder with its own Makefile.
- **Testing:** Strongly recommended to create your own test programs.
- **Submission:** Only code on the assigned git repo is evaluated.
- **Automated Correction:** If Deepthought fails, evaluation stops.

---

## 4. Mandatory Part

### Program Name

- `cub3D`

### Required Files

- All source and header files, Makefile.

### Arguments

- The program takes a single `.cub` map file as its first argument.

### Allowed Functions

- Standard: `open`, `close`, `read`, `write`, `printf`, `malloc`, `free`, `perror`, `strerror`, `exit`
- Math library (`-lm`)
- All MinilibX functions
- Libft (if used)

### What You Must Do

- Render a "realistic" 3D first-person view inside a maze using ray-casting.
- Use MinilibX for all graphics.
- **Window management:** Must handle minimization, focus changes, etc.
- **Wall textures:** Different textures for north, south, east, and west walls.
- **Floor/Ceiling:** Different colors for each.
- **Controls:**
  - Arrow keys: rotate camera left/right
  - W, A, S, D: move player
  - ESC: closes the window and exits cleanly
  - Clicking the window’s red cross: closes and exits cleanly
- **Scene file:** The `.cub` file describes the map and resources.

#### Map Rules

- Only these chars: `0` (empty), `1` (wall), `N/S/E/W` (player start + orientation)
- Map must be closed by walls, or error.
- Map is always the last part of the file; other elements can be in any order.
- Map can include spaces (to be handled by your parser).
- Each element starts with an identifier:
  - `NO` / `SO` / `WE` / `EA`: texture paths
  - `F`: floor color (R,G,B)
  - `C`: ceiling color (R,G,B)
- Example minimal map:
  ```
  NO ./path_to_the_north_texture
  SO ./path_to_the_south_texture
  WE ./path_to_the_west_texture
  EA ./path_to_the_east_texture
  F 220,100,0
  C 225,30,0
  111111
  100101
  101001
  1100N1
  111111
  ```
- Any config error must print `Error\n` + a clear message, then exit.

---

## 5. Bonus Part

**Only evaluated if the mandatory part is 100% perfect.**

Possible bonuses:

- Wall collision
- Minimap
- Doors (open/close)
- Sprite animations
- Mouse to rotate view

**You may:**

- Use extra functions/symbols in bonus files (with justification).
- Modify the scene file format for bonuses.

---

## 6. Example Scenes

- Screenshots of Wolfenstein 3D and sample Cub3D outputs.
- Examples of bonus features: minimap, HUD, animated sprites, weapons, etc.

---

## 7. Submission & Peer Evaluation

- Submit only via your assigned git repo.
- Double-check folder and file names for conformity.
- Only submitted code is graded.

---

## Quick Checklist

- [ ] C only, 42 Norme
- [ ] No leaks, no crashes
- [ ] Handles all window events and inputs
- [ ] Different wall textures and floor/ceiling colors
- [ ] Parses `.cub` file correctly, with robust error handling
- [ ] Clean exit on ESC and window close
- [ ] Bonus only if everything else is perfect

---
