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

void cast_rays(t_box *box)
{
    int number_rays = 50;
    double fov_rad = box->plyr->fov;
    double angle_between_rays = fov_rad / number_rays;
    double rayangle = box->plyr->p_angle - (fov_rad / 2.0);
    int i;

    for (i = 0; i < number_rays; i++)
    {
        // Calculate ray direction
        double ray_dir_x = cos(rayangle);
        double ray_dir_y = sin(rayangle);
        
        // Start from player position
        double ray_x = box->plyr->p_x;
        double ray_y = box->plyr->p_y;
        
        // Cast ray until hitting a wall (you need to implement wall detection)
        double step = 1.0 ;// Step size for ray marching
        int max_distance = 1000;  // Maximum ray distance
        int hit_wall = 0;
        
        for (int dist = 0; dist < max_distance && !hit_wall; dist++)
        {
            ray_x += ray_dir_x * step;
            ray_y += ray_dir_y * step;
            
            // Check if ray hit a wall (you need your map checking function here)
            // Example: if (is_wall(box->map, (int)(ray_x / TILE_SIZE), (int)(ray_y / TILE_SIZE)))
            //     hit_wall = 1;
        }
        
        // Draw the complete ray from player to wall
        draw_player_direction(box->cub->mlx, box->cub->mlx_win,
            box->plyr->p_x, box->plyr->p_y,
            ray_x, ray_y,
            30, RED);
       
        rayangle += angle_between_rays;
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