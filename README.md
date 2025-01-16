# so_long

This project is a small 2D Bomberman-style game created using **minilibx**, a graphics library used at 42. The game features textures, sprites, and tile-based design.

https://user-images.githubusercontent.com/65622360/137594197-e525784d-8baf-49d2-9584-9888fe649215.mov

---

## Description

In this game, the player’s goal is to:
- **Collect all bombs** (collectibles) scattered across the map.
- **Escape through the revealed pipe** (exit) with the fewest possible moves.

### Features:
- The **current movement count** updates dynamically on the game window.
- **Enemy patrols**: Coming into contact with an enemy results in game over.
- **Collectibles** include:
  - <img src="/screenshots/item-speed.png" /> **Speed**: Increases the player’s movement speed.
  - <img src="/screenshots/item-bomb.png" /> **Bomb**: Allows the player to place an additional bomb.
  - <img src="/screenshots/item-fire.png" /> **Fire**: Boosts the power of the player’s bombs.

---

## Commands

### Run the Game
```bash
make
./bomberman [map]       # Example: ./bomberman maps/map_large.ber
```

### Controls

#### QWERTY Keyboards:
- **Up**: W  
- **Down**: S  
- **Left**: A  
- **Right**: D  

#### AZERTY Keyboards:
- **Up**: Z  
- **Down**: S  
- **Left**: Q  
- **Right**: D  

#### Additional Commands:
- **Set Bomb**: B  
- **Quit Game**: ESC  

---

## Map

The game requires a valid **.ber** map file as input. The map consists of the following 6 characters:

| Character | Meaning                   | Icon                           |
|-----------|---------------------------|---------------------------------|
| `0`       | Empty space               | <img src="/screenshots/empty-space.png" /> |
| `1`       | Wall                      | <img src="/screenshots/wall.png" />        |
| `C`       | Collectibles              |                                 |
| `E`       | Map exit                  | <img src="/screenshots/exit.png" />        |
| `P`       | Player's starting position| <img src="/screenshots/player.png" />      |
| `M`       | Enemy's starting position | <img src="/screenshots/ennemy.png" />      |

### Example of a Valid Map:
```plaintext
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

### Map Requirements:
- Must be **surrounded by walls** (`1`).
- Must contain at least:
  - **One exit** (`E`).
  - **One collectible** (`C`).
  - **One starting position** (`P`).
- Must be **rectangular**.

---

## Screenshots

<p align="center">
  <img src="/screenshots/screen_1.png" width="50%" />
</p>

<p align="center">
  <img src="/screenshots/screen_2.png" width="50%" />
</p>
