//# include "../includes/cub3d.h"
# include "../includes/game.h"

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
		destroy_game1(game);
        perror("Error opening file");
        return 1;
    }
	initialize_game_utils(game);
	parse_map(game, fd);
	setup_engine(game);
	// generate_2d_world(game);
	// cast_rays(game);
	// Key press event (key down)
	cast_3d_walls(game);
	mlx_hook(game->engine->mlx_win, 2, 1L << 0, is_pressed, game);
	mlx_hook(game->engine->mlx_win, 3, 1L << 1, is_released, game);
	mlx_loop_hook(game->engine->mlx, handle_input, game);
	

	mlx_loop(game->engine->mlx);
	return (0);
}