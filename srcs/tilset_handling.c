#include "../includes/cub3d.h"

int	allocate_sprites(t_box *box)
{
	int	h;
	int	w;

	h = TILESIZE;
	w = TILESIZE;
	box->img->wall = mlx_xpm_file_to_image(box->cub->mlx, "textures/wall64.xpm", &w, &h);
	if (!box->img->wall)
		return (1); // free all the  cotainer .
	box->img->floor = mlx_xpm_file_to_image(box->cub->mlx, "textures/floor.xpm", &w, &h);
	return (0);
}

int	draw_sprites(t_box *box)
{
	int	y;
	int	x;

	y = 0;
	while (y < box->cub->map_h)
	{
		x = 0;
		while (x < box->cub->map_w)
		{
			if (box->cub->map[y][x] == '1')
			{
				mlx_put_image_to_window(box->cub->mlx, box->cub->mlx_win, box->img->wall, x * TILESIZE, y * TILESIZE);
			}
			if (box->cub->map[y][x] == '0')
			{
				mlx_put_image_to_window(box->cub->mlx, box->cub->mlx_win, box->img->floor, x * TILESIZE, y * TILESIZE);
			}
			x++;
		}
		y++;
	}
	return (0);
}