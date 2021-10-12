# so_long
This project is a small 2D Bomberman game using minilibx, a graffic library used at 42. It uses textures, sprites and tiles.

## Description
* The player’s goal is to collect all collectibles present on the map then escape with minimal movement.
* At every move the current number of movements is displayed on the window.
* Ennemy patrols cause the player to lose in case of contact.

## Commands
* QWERTY
Up    = W
Down  = S
Left  = A
Right = D

* AZERTY
Up    = Z
Down  = S
Left  = Q
Right = D

* Quit
ESC

## Map
* The program taked as a first argument a map description file with the .ber extension.
* The map must be composed of only 5 possible characters:
0 for an empty space
1 for a wall
C for a collectible
E for map exit
P for the player’s starting position

This is a simple valid map:
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111

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
