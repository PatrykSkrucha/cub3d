# cub3d

> The scene parser and map validator for a **raycasting game engine** inspired by early first-person shooters, written in C.

![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)
![MLX42](https://img.shields.io/badge/graphics-MLX42-555555?style=flat)

## About

cub3d reads a `.cub` scene file describing the textures, colours and map of a 3D maze and makes sure
it is valid before anything gets rendered. This repository contains that parsing and validation layer.
The MLX42 graphics library is included for the rendering part.

## What gets checked

- the file has the `.cub` extension and can be opened
- the four wall textures `NO`, `SO`, `WE`, `EA` are each given once
- floor `F` and ceiling `C` colours are valid `R,G,B` values (0–255)
- the map uses only `0` (floor), `1` (wall), spaces and exactly one player (`N`, `S`, `E` or `W`)
- the map is **closed**: rows and columns are scanned so no floor tile touches the outside

Any problem ends the program with `Error` and a short explanation.

## Scene file example

```
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png

F 76,76,76
C 99,99,99

111111
100001
1000N1
111111
```

## Build & run

Requires `cc` and `make`.

```bash
make
./cub3d maps/1.cub
```

A valid map exits silently. The [`maps/`](maps) folder and [`maps/not_valid/`](maps/not_valid) hold example scenes, including broken ones (open walls, bad colours, two players) for testing the error handling.

---

<sub>Part of the <a href="https://www.codam.nl/">Codam</a> (42 network) curriculum.</sub>
