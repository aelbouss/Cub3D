//# include "../includes/cub3d.h"
# include "../includes/game.h"

int    cross_exit(t_game *game)
{
    mlx_destroy_window(game->engine->mlx, game->engine->mlx_win);
	// need  to  free all resources
    ft_putendl_fd("X detected", 2);
    exit(0);
}

void	raycasting(t_game *game)
{
	setup_engine(game);
	cast_3d_walls(game);
	mlx_hook(game->engine->mlx_win, 17, 0, cross_exit, game); //17 “window close button clicked” → 0 no mask needed
	mlx_hook(game->engine->mlx_win, 2, 1L << 0, is_pressed, game);
	mlx_hook(game->engine->mlx_win, 3, 1L << 1, is_released, game);
	mlx_loop_hook(game->engine->mlx, handle_input, game);
	mlx_loop(game->engine->mlx);
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
	fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
	game = build_base();
	initialize_game_utils(game);
	parse_map(game, fd);
	raycasting(game);
	return (0);
}