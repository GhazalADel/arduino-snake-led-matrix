# Snake Game on Arduino — Microprocessors Final Project
**Amirkabir University of Technology | Fall 2023**

## Overview
Implementation of the classic Snake game on an Arduino Uno with an 8×8 LED matrix display, simulated in Proteus.

## Hardware
- Arduino Uno
- 8×8 LED Matrix (MATRIX-8X8-BLUE)
- MAX7219 Controller
- 4 Buttons (up / down / left / right)

## Gameplay
- Snake is controlled via 4 directional buttons
- Food spawns randomly on the 8×8 grid after being eaten
- Snake grows by one unit per food eaten
- Collision with walls or itself resets the game

## Implementation Notes
- Display uses multiplexing via an 8×8 boolean array; LED matrix rendering is decoupled from game logic
- Snake state updates on a timer interrupt (~0.5s tick)
- Written in C++ for Arduino

## Files
| File | Description |
|------|-------------|
| `another/another.ino` | Arduino sketch (game logic) |
| `snake_gmae.pdsprj` | Proteus simulation project |
| `build/` | Compiled hex & binaries |
