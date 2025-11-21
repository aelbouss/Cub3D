#include "../includes/cub3d.h"

char	**read_map(char *file)
{
	int		fd;
	int		cnt;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cnt = 0;
	while (get_next_line(fd))
		cnt++;
	close(fd);
	map = malloc(sizeof (char *) * (cnt + 1));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cnt = 0;
	while (1)
	{
		map[cnt++] = get_next_line(fd);
		if (!map[cnt - 1])
			break ;
	}
	map[cnt] = NULL;
	return (map);
}


void	extract_map_width_hight(t_box *box)
{
	int	i;

	box->cub->map_w = ft_strlen(box->cub->map[0]) - 1;
	i = 0;
	while (box->cub->map[i])
		i++;
	box->cub->map_h = i;
	return;
}

t_box	*setup_environement(char *mapfile)
{
	t_box	*box;

	if (!mapfile)
		return (perror("Map file"), NULL);
	box = malloc(1 * sizeof(t_box));
	if (!box)
		return (perror("Error"), NULL);
	box->cub = malloc(1 * sizeof(t_game));
	if (!box->cub)
		return (free(box), perror("Error"), NULL);
	box->img = malloc(1 * sizeof(t_img));
	if (!box->img)
		return (free(box->cub), free(box), perror("Error"), NULL);
	box->cub->map = read_map(mapfile);
	if (!box->cub->map)
		return (NULL); // free container
	box->plyr = malloc(1 * sizeof(t_player));
	if (!box->plyr)
		return (NULL);
	box->ray = malloc(1 * sizeof(t_raycasting));
	if (!box->ray)
		return (NULL);
	extract_map_width_hight(box);
	return (box);
}

int	build_dependencies(t_box *box)
{
	box->cub->mlx = mlx_init();
	if (!box->cub->mlx)
		return (1); // free cub , free img , free  box .
	box->cub->mlx_win = mlx_new_window(box->cub->mlx, box->cub->map_w * TILESIZE,
			box->cub->map_h * TILESIZE, "cub3d");
	if (!box->cub->mlx_win)
		return (1); // free mlx , free cub  , free img , free core
	box->plyr->p_y = ((box->cub->map_h * TILESIZE) / 2);
	box->plyr->p_x = ((box->cub->map_w * TILESIZE) / 2);
	box->plyr->p_angle = 90 * (PI / 180);
	box->plyr->pdx = cos(box->plyr->p_angle);
	box->plyr->pdy = sin(box->plyr->p_angle);
	box->plyr->fov = 60 * (PI / 180);
	box->ray->game_h = (box->cub->map_h * TILESIZE);
	box->ray->game_w = (box->cub->map_w * TILESIZE);
	box->img->wold2d = mlx_new_image(box->cub->mlx, box->cub->map_w * TILESIZE, box->cub->map_h *TILESIZE);
	if (!box->img->wold2d)
		return (perror("Bad Image\n"), 1);
	box->img->img_data = mlx_get_data_addr(box->img->wold2d, &box->img->bpp, &box->img->size_line, &box->img->endian);
	return (0);
}


void	put_pixel_to_image(char *img_data, int x, int y, int color, int bpp, int size_line)
{
	char	*pixel_addr;
	int		offset;

	offset = (y * size_line) + (x * (bpp / 8));
	pixel_addr = img_data + offset;
	*(unsigned int *)pixel_addr = color;
}
int	push_pixels_to_image(t_box *box, void *image, int color, int y, int x)
{
	int	i;
	int	j;
	(void)image;
	i = y;
	while (i < y + 63)
	{
		j = x;
		while (j <  x + 63)
		{
			put_pixel_to_image(box->img->img_data, j, i, color, box->img->bpp, box->img->size_line);
			j++;
		}
		i++;
	}	
	return (0);
}

