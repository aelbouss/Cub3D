#include "../includes/cub3d.h"



void draw_player_direction(void *mlx_ptr, void *win_ptr, 
                           int player_x, int player_y, 
                           double dir_x, double dir_y, 
                           int length, int color)
{
    int x_end = player_x + (int)(dir_x * length);
    int y_end = player_y + (int)(dir_y * length);

    int dx = abs(x_end - player_x);
    int dy = abs(y_end - player_y);
    int sx = player_x < x_end ? 1 : -1;
    int sy = player_y < y_end ? 1 : -1;
    int err = dx - dy;

    int x0 = player_x;
    int y0 = player_y;

    while (1) {
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);
        if (x0 == x_end && y0 == y_end)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

