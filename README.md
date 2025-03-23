[На русском 🇷🇺](README_RUS.md)

# Game of Life

A classic implementation of Conway's Game of Life — a cellular automaton simulation that follows simple rules to create complex patterns.

## Features
- Supports interactive controls: start, pause, reset the simulation.
- Six predefined patterns: still lifes, oscillators, spaceships, guns.

## How to Run
```sh
./bin/game_of_life < initial_fields/101.txt
```

## Controls
- `1, 2, 3, 4` – speed
- `SPACE` – pause
- `Q` – quit the game

## Rules
1. Any live cell with two or three live neighbors survives.
2. Any dead cell with exactly three live neighbors becomes a live cell.
3. All other live cells die in the next generation. Similarly, all other dead cells stay dead.

## License

This project is licensed under the Apache License, Version 2.0. See the LICENSE file for details.
