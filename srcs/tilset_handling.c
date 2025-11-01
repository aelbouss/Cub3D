#include "../includes/cub3d.h"


// Draw a pixel at (x, y)
void put_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
}

// Draw a ray from (sx, sy) at angle (radians) up to max_distance
void draw_ray_angle(void *mlx_ptr, void *win_ptr, double sx, double sy, double angle, double max_distance, int color)
{
    double hx = sx + cos(angle) * max_distance;
    double hy = sy + sin(angle) * max_distance;
    double dx = hx - sx;
    double dy = hy - sy;
    double steps = fmax(fabs(dx), fabs(dy));
    double x_inc = dx / steps;
    double y_inc = dy / steps;
    double x = sx;
    double y = sy;
    int i;

    for (i = 0; i <= (int)steps; i++)
    {
        put_pixel(mlx_ptr, win_ptr, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}

