# cub3D

A 3D first-person perspective maze explorer built in C using 42's **MiniLibX** library. The project uses raycasting principles inspired by the classic 1992 game *Wolfenstein 3D* to render a dynamic 3D world from a flat 2D grid map in real time.

---

## Overview

**cub3D** is the major graphics milestone in the 42 curriculum. It transitions from simple 2D tile blitting to mathematical 3D rendering.

Key technical aspects include:

* Parsing `.cub` scene files (textures, ceiling/floor colors, and grid layout).
* Implementing the **DDA (Digital Differential Analysis)** raycasting algorithm.
* Converting ray collision distances into vertically scaled wall slices.
* Calculating exact texture coordinates to map `.xpm` images onto 3D surfaces.
* Managing player orientation vectors, camera planes, and smooth movement.

---

## How the Raycaster Works

The rendering engine does not use hardware 3D pipelines (like modern OpenGL or Vulkan). Every column of pixels on your screen is calculated manually:

1. **Camera Setup:** The player has a position vector $(x, y)$, a direction vector, and a camera plane perpendicular to the direction that defines the field of view (FOV).
2. **Casting Rays:** For every vertical column of the window (e.g., width = 1024 pixels, so 1024 individual rays), a ray is projected outward into the 2D grid.
3. **DDA Algorithm:** The ray steps through grid cells one by one until it hits a wall (`1`). DDA avoids sampling empty space and guarantees the exact wall intersection point.
4. **Distance & Fisheye Correction:** Euclidean distance makes flat walls look curved at the screen edges. Projecting the distance perpendicular to the camera plane eliminates the fisheye distortion.
5. **Wall Height Calculation:** Using the perpendicular wall distance, the screen calculates how tall the wall slice should appear. Closer walls appear taller; further walls appear shorter.
6. **Texture Mapping:** The engine determines whether the ray hit a North, South, East, or West face, calculates the exact horizontal offset on the wall ($wallX$), and samples the corresponding vertical stripe of pixels from the `.xpm` texture buffer to draw to the screen.

---

## Controls

| Key | Action |
| --- | --- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` (Left Arrow) | Rotate camera left |
| `→` (Right Arrow) | Rotate camera right |
| `ESC` | Exit game cleanly |
| Window `Close` (`X`) | Exit application |

---

## Scene Configuration (`.cub`)

Scene descriptions are defined in `.cub` files. The file contains texture paths, RGB color values, and a closed map layout:

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111111111
1000000000001
1011000001101
100000N000001
1111111111111

```

* **Textures:** North (`NO`), South (`SO`), West (`WE`), East (`EA`) image paths.
* **Colors:** Floor (`F`) and Ceiling (`C`) formatted as standard R,G,B values between 0 and 255.
* **Map Characters:**
* `0` : Empty walkable space
* `1` : Wall
* `N`, `S`, `E`, `W` : Player starting position and initial orientation


* **Validation:** The map must be completely closed and enclosed by walls (`1`), even when spaces exist around the perimeter.

---

## Prerequisites & MiniLibX Setup

### 1. System Dependencies

**Linux (Debian / Ubuntu / Kali):**

```bash
sudo apt update
sudo apt install -y gcc make libx11-dev libxext-dev libbsd-dev

```

**macOS:**

```bash
xcode-select --install

```

---

### 2. Installing MiniLibX

Clone and compile the MiniLibX library inside the project directory:

**Linux (X11 Version):**

```bash
git clone https://github.com/42Paris/minilibx-linux.git mlx
cd mlx
make
cd ..

```

**macOS (OpenGL / AppKit Version):**

```bash
git clone https://github.com/42Paris/minilibx_opengl.git mlx
cd mlx
make
cd ..

```

---

## Build & Execution

### 1. Compile

```bash
git clone https://github.com/your-username/cub3D.git
cd cub3D
make

```

### 2. Run

```bash
./cub3D maps/valid/simple.cub

```

### 3. Cleanup Rules

* `make clean` removes compiled object files (`.o`).
* `make fclean` removes object files and the `cub3D` binary.
* `make re` recompiles the entire project from scratch.

---
