# OOP_Project

# Space Adventure Game

Welcome to **Space Adventure Game**, a thrilling space shooter where you battle waves of pirate ships, collect resources, and survive in the depths of space!

---

## Table of Contents
- [Game Features](#game-features)
- [How to Play](#how-to-play)
- [Setup](#setup)
- [Code Overview](#code-overview)

---

## Game Features

- **Dynamic Gameplay**:
  - Face waves of pirate ships with increasing difficulty.
  - Collect resources from a trading planet to replenish health and ammo.

- **Engaging Mechanics**:
  - Shoot enemies with your laser cannon.
  - Manage your health and ammo to survive as long as possible.

- **Beautiful Visuals**:
  - Scrollable space background.
  - Smooth animations and interactive UI elements like health bars.

- **Audio Effects**:
  - Background music and sound effects for shooting, explosions, collisions, and pickups.

---

## How to Play

### Controls:
- **Arrow Keys**: Move your ship (Up, Down, Left, Right).
- **Spacebar**: Shoot bullets to destroy enemies.

### Objectives:
1. **Survive Waves**: Avoid enemy ships and bullets.
2. **Eliminate Enemies**: Earn points by defeating pirate ships.
3. **Use the Planet Base**: Collect resources to restore health and ammo.

### Game Over:
- If your health reaches zero, the game will end. Press `R` to restart or `Esc` to exit.

---

## Setup

### Requirements:
1. **C++ Compiler** with support for C++11 or later.
2. [SFML Library](https://www.sfml-dev.org/) (Graphics, Audio, and Window modules).

### Instructions:
1. Clone this repository or download the source code.
2. Install the SFML library:
   ```bash
   sudo apt-get install libsfml-dev
g++ -std=c++11 Game.cpp -o SpaceAdventure -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./SpaceAdventure

## Code Overview

## Key Components:
Game: Manages the game loop, updates, rendering, and events.
Universe: Handles the background scrolling.
Ship: Represents the player-controlled ship.
PirateShip: Represents enemy ships.
PlanetBase: Acts as a resource point for health and ammo.
Bullet: Represents projectiles fired by the player and enemies.
Highlights:
Health and Ammo UI:
Health bar dynamically adjusts color and size based on player health.
Wave System:
Waves increase in difficulty, spawning more ships with each interval.
Audio Integration:
Background music and sound effects are loaded and played during gameplay.
Attribution

## Libraries:
SFML (Simple and Fast Multimedia Library) for graphics, audio, and input handling.
