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
	if (keycode == WF)
		walk_forward(box);
	if (keycode == WB)
		walk_backward(box);
	if (keycode == WL)
		walk_left(box);
	if (keycode == WR)
		walk_right(box);
	if (keycode == RL)
		retate_left(box);
	if (keycode == RR)
		retate_right(box);
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
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(box->cub->mlx, box->cub->mlx_win,box->img->wold2d , 0, 0);
	return (0);
}


int		has_wall(t_box *box, double x , double y)
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
	cast_rays(box);
	mlx_key_hook(box->cub->mlx_win, key_handler, box);
	mlx_hook(box->cub->mlx_win, 2, 1l<<0, key_handler, box);
	mlx_loop(box->cub->mlx);
	return (0);
}
 
// there is a bug when the player being inside the wall and you tray to move it out .
