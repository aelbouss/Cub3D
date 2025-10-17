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





/*
void	cast_rays(t_box *box)
{
	double	rayangle;
	double	angle_between_rays;
	int	number_rays;
	int	i;			

	number_rays = (box->cub->map_w * TILESIZE) / RES;
	angle_between_rays = box->plyr->fov / number_rays;
	rayangle = box->plyr->p_angle - (box->plyr->fov / 2);
	i = 0;
	while (i < number_rays)
	{
		draw_player_direction(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x,
			box->plyr->p_y, box->plyr->p_x + cos(rayangle) * 30, box->plyr->p_y + sin(rayangle) * 30, 30, RED);
		rayangle += angle_between_rays;
		i++;
	}
}*/