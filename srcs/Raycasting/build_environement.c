# include "../includes/game.h"

t_game	*build_base()
{
	t_game	*game;

	game = malloc(1 * sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Bad Allocation", STDERR_FILENO) , NULL);
	game->colors = malloc(1 * sizeof(t_colors));
	if (!game->colors)
	return (free(game),ft_putstr_fd("Bad Allocation", STDERR_FILENO), NULL);
	game->tex = malloc(1 * sizeof(t_textures));
	if (!game->tex)
		return (free(game->colors), free(game), NULL);
	game->player = malloc(1 * sizeof(t_player));
	if (!game->player)
		return (free(game->colors), free(game->tex) ,free(game)
			,ft_putstr_fd("Bad Allocation", STDERR_FILENO), NULL);
	game->engine = malloc(1 * sizeof(t_raycasting));
	if (!game->engine)
	{
		free(game->colors);
		free(game->player);
		free(game->tex);
		return (free(game), ft_putstr_fd("Bad Allocation",2), NULL);
	}
	return (game);
}

void	destroy_game(t_game *game) // will free all the allocations
{
		free (game->tex);
		game->tex = NULL;
		free (game->player);
		game->player = NULL;
		free (game->colors);
		game->colors = NULL;
		free (game->engine);
		game->engine = NULL;
		free (game);
		game = NULL;
}

void	initialize_game_utils(t_game *game)
{
    game->map_height = 0;
    game->map_started = 0;
    game->tex->no = NULL;
    game->tex->so = NULL;
    game->tex->we = NULL;
    game->tex->ea = NULL;
    game->colors->floor = -1;
    game->colors->ceiling = -1;
	game->player->move_up = 0;
	game->player->move_down = 0;
	game->player->move_left = 0;
	game->player->move_right = 0;
	game->player->rotate_left = 0;
	game->player->rotate_right = 0;
}

void	setup_engine(t_game *game)
{
	game->engine->mlx = mlx_init();
	if (!game->engine->mlx)
		return (destroy_game(game),ft_putstr_fd("unable connecting to the server", 2));
	game->engine->map_h = game->map_height * TILESIZE;
	game->engine->map_w = ft_strlen(game->map[0]) * TILESIZE;
	game->player->fov = 60 * (PI / 180);
	game->engine->dist_proj_plane = (game->engine->map_w / 2) / tan(game->player->fov / 2.0);
	game->engine->mlx_win = mlx_new_window(game->engine->mlx, game->engine->map_w , game->engine->map_h , "cub3d");
	if (!game->engine->mlx_win)
		return (destroy_game2(game),ft_putstr_fd("unable to open mlx window", 2));
	set_player_angle(game);
	allocate_textures(game);

}
