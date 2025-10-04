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
	if (allocate_sprites(box) != 0)
		return (1);  // free all the container
	box->plyr->p_y = box->cub->map_h / 2;
	box->plyr->p_x = box->cub->map_w / 2;
	return (0);
}

