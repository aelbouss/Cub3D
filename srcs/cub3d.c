#include "../includes/cub3d.h"


void	draw_player (t_box *box)
{
	int	y;
	int	x;

	y = 0;

	while (y < 20)
	{
		x = 0; 
		while (x < 20)
		{
			mlx_pixel_put(box->cub->mlx, box->cub->mlx_win, ((box->plyr->p_x * 	TILESIZE) / 2) + x, ((box->plyr->p_y * TILESIZE) / 2) + y, RED);
			x++;
		}
		y++;
	}
}

int	key_handler (int keycode, t_box *box)
{
	if (keycode == 65362)
	{
		if (((box->plyr->p_y - 1) * TILESIZE) > (1 * TILESIZE))
		{
			box->plyr->p_y -= 1 ;
			draw_sprites(box);
			draw_player(box);
		}
	}
	if (keycode == 65364)
	{
		if (((box->plyr->p_y + 1) * TILESIZE) < (box->cub->map_h * TILESIZE))
		{
			box->plyr->p_y += 1 ;
			draw_sprites(box);
			draw_player(box);
		}
	}
	if (keycode == 65361)
	{
		if (((box->plyr->p_x - 1) * TILESIZE) > (1 * TILESIZE))
		{
			box->plyr->p_x -= 1 ;
			draw_sprites(box);
			draw_player(box);
		}
	}
	if (keycode == 65363)
	{
		if (((box->plyr->p_x + 1) * TILESIZE) < (box->cub->map_w * TILESIZE))
		{
			box->plyr->p_x += 1 ;
			draw_sprites(box);
			draw_player(box);
		}
	}

	return (0);
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
	draw_sprites(box);
	mlx_key_hook(box->cub->mlx_win, key_handler, box);
	draw_player(box);
	mlx_loop(box->cub->mlx);
	return (0);
}