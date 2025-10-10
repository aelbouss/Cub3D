#include "../includes/cub3d.h"


void	draw_player (t_box *box)
{
	int	y;
	int	x;

	y = 0;

	while (y < PLYRSIZE)
	{
		x = 0; 
		while (x < PLYRSIZE)
		{
			mlx_pixel_put(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x + x, box->plyr->p_y + y, RED);
			x++;
		}
		y++;
	}
}

int	key_handler (int keycode, t_box *box)
{
	if (keycode == 65362)
	{
		if (loking_for_wall(box->plyr->p_x, (box->plyr->p_y - PLYRSIZE), box) != 1)
		{
			box->plyr->p_y -= PLYRSIZE ;
			draw_2d_world(box);
			draw_player(box);
			draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE);
		}
	}
	if (keycode == 65364)
	{
		if (loking_for_wall(box->plyr->p_x, (box->plyr->p_y + PLYRSIZE), box) != 1)
		{
			box->plyr->p_y += PLYRSIZE ;
			draw_2d_world(box);
			draw_player(box);
			draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE);
		}
	}
	if (keycode == 65361)
	{
		if (loking_for_wall((box->plyr->p_x - PLYRSIZE), box->plyr->p_y, box) != 1)
		{
			box->plyr->p_x -= PLYRSIZE ;
			draw_2d_world(box);
			draw_player(box);
			draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE);
		}
	}
	if (keycode == 65363)
	{
		if (loking_for_wall(box->plyr->p_x + PLYRSIZE, box->plyr->p_y, box) != 1)
		{
			box->plyr->p_x += PLYRSIZE ;
			draw_2d_world(box);
			draw_player(box);
			draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE);
		}
	}
	else if (keycode == 97) // A - rotate left
	{
   	 box->plyr->p_angle -= 0.1;
   	 if (box->plyr->p_angle < 0)
        box->plyr->p_angle += 2 * M_PI;

    // Update direction vector every time angle changes
    	box->plyr->pdx = cos(box->plyr->p_angle) * 10;
    	box->plyr->pdy = sin(box->plyr->p_angle) * 10;

   	 draw_2d_world(box);
   	 draw_player(box);
    	draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE); // longer line for visibility
}

else if (keycode == 100) // D - rotate right
{
    box->plyr->p_angle += 0.1;
    if (box->plyr->p_angle > 2 * M_PI)
        box->plyr->p_angle -= 2 * M_PI;

    // Update direction vector every time angle changes
    box->plyr->pdx = cos(box->plyr->p_angle) * 10;
    box->plyr->pdy = sin(box->plyr->p_angle) * 10;

    draw_2d_world(box);
    draw_player(box);
    draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE);
}

	return (0);
}


int	draw_2d_world(t_box *box)
{
	int	y;
	int	x;

	y = 0;
	while (box->cub->map[y])
	{
		x = 0;
		while (box->cub->map[y][x])
		{
			if (box->cub->map[y][x] == '1')
				push_pixels_to_image(box, box->img->wold2d, 0x565656, y * TILESIZE, x * TILESIZE);
			if (box->cub->map[y][x] == '0')
				push_pixels_to_image(box, box->img->wold2d, 0xFFFFFF, y * TILESIZE, x * TILESIZE);
				// draw white color ;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(box->cub->mlx, box->cub->mlx_win,box->img->wold2d , 0, 0);
	return (0);
}



int	loking_for_wall(int x, int y, t_box *box)
{
	if (box->cub->map[(int)(y / TILESIZE)][(int )(x / TILESIZE)] == '0')
		return (0);
	return (1);
}


int	main(int ac, char **av)
{
	t_box	*box;

	if (ac != 2)
		return (perror("Error : Invalid Arguments\n"), 1);
	box = setup_environement(av[1]);
	if (!box)
		return (1);
	if (build_dependencies(box) != 0)
		return (1);
	draw_2d_world(box);
	draw_player(box);
	draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE);
	mlx_key_hook(box->cub->mlx_win, key_handler, box);
	mlx_loop(box->cub->mlx);
	return (0);
}
 