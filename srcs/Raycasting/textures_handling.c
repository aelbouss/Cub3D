#include  "../includes/game.h"

int	allocate_textures(t_game *game)
{
	int	height;
	int	width;

	game->tex->wold2d = mlx_new_image(game->engine->mlx, game->engine->map_w, game->engine->map_h);
	if (!game->tex->wold2d)
		return (ft_putstr_fd("Bad image" , 2), 1);
	game->tex->south = mlx_xpm_file_to_image(game->engine->mlx, game->tex->so , &height, &width);
	if (!game->tex->south)
		return (ft_putstr_fd("Bad image" , 2), 1);
	game->tex->north = mlx_xpm_file_to_image(game->engine->mlx, game->tex->no, &height, &width);
	if (!game->tex->north)
		return (ft_putstr_fd("Bad image" , 2), 1);
	game->tex->east = mlx_xpm_file_to_image(game->engine->mlx, game->tex->ea, &height, &width);
	if (!game->tex->east)
		return (ft_putstr_fd("Bad image" , 2), 1);
	game->tex->west = mlx_xpm_file_to_image(game->engine->mlx, game->tex->we, &height, &width);
	if (!game->tex->we)
		return (ft_putstr_fd("Bad image" , 2), 1);
	return (0);
}

void	generate_2d_world(t_game *game)
{
	int h;
	int	w;

	h = 0;
	while (game->map[h])
	{
		w = 0;
		while (game->map[h][w])
		{
			if (game->map[h][w] == '1')
				mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, game->tex->west, w * TILESIZE , h * TILESIZE);
			if (game->map[h][w] == '0')
				mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, game->tex->north, w * TILESIZE , h * TILESIZE);
			if (game->map[h][w] == 'N' || game->map[h][w] == 'S' || game->map[h][w] == 'E' || game->map[h][w] == 'W')
				mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, game->tex->east, w * TILESIZE , h * TILESIZE);
			w++;
		}
		h++;
	}
}

