//# include "../includes/cub3d.h"
# include "../includes/parsing.h"


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
	return (game);
}

void	destroy_game(t_game *game)
{
		free (game->tex);
		game->tex = NULL;
		free (game->player);
		game->player = NULL;
		free (game->colors);
		game->colors = NULL;
		free (game);
		game = NULL;
}

void	initialize_game_utils(t_game *game)
{
	game->map = NULL;
    game->map_height = 0;
    game->map_started = 0;
    game->tex->no = NULL;
    game->tex->so = NULL;
    game->tex->we = NULL;
    game->tex->ea = NULL;
    game->colors->floor = -1;
    game->colors->ceiling = -1;
}

int	main(int ac, char **av)
{
	t_game	*game;
	int	fd;


	if (ac != 2)
    {
        printf("Usage: %s <map_file.cub>\n", av[0]);
        return 1;
    }
	game = build_base();
	fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
		destroy_game(game);
        perror("Error opening file");
        return 1;
    }
	initialize_game_utils(game);
	parse_map(game, fd);
	destroy_game(game);
	return (0);
}