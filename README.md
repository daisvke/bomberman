# so_long
This project is a small 2D Bomberman game using minilibx, a graffic library used at 42. It uses textures, sprites and tiles.

## Description

https://user-images.githubusercontent.com/65622360/137594197-e525784d-8baf-49d2-9584-9888fe649215.mov


* The player’s goal is to collect all the collectible bombs present on the map, then to escape from the revealed pipe with minimal movement.
* At every move the current number of movements is displayed on the window.
* Ennemy patrols cause the player to lose in case of contact.
* Collectibles include :<br />
<img src="/screenshots/item-speed.png" /> Speed = allows the player to move faster<br />
<img src="/screenshots/item-bomb.png" /> Bomb = allows the player to set an additional bomb on the field<br />
<img src="/screenshots/item-fire.png" /> Fire = increases the power of the bombs set by the player

## Commands
* QWERTY<br />
Up = W<br />
Down = S<br />
Left = A<br />
Right = D<br />

* AZERTY<br />
Up = Z<br />
Down = S<br />
Left = Q<br />
Right = D<br />
* Set bomb = B<br />
* Quit = ESC

## Map
* The program taked as a first argument a map description file with the .ber extension.
* The map can be composed of only 6 possible characters:<br />
0 for an empty space <img src="/screenshots/empty-space.png" /><br />
1 for a wall <img src="/screenshots/wall.png" /><br />
C for a collectible<br />
E for map exit <img src="/screenshots/exit.png" /><br />
P for the player’s starting position <img src="/screenshots/player.png" /><br />
M for an ennemy's starting position <img src="/screenshots/ennemy.png" />

This is a simple valid map:
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

* The map must be closed/surrounded by walls, if not the program must returns an error.
* It must have at least one exit, one collectible, and one starting position.
* It must be rectangular.

## Screenshots
<p align="center">
  <img src="/screenshots/screen_1.png" width="50%" />
</p>

<p align="center">
  <img src="/screenshots/screen_2.png" width="50%" />
</p>
