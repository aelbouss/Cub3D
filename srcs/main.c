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
	generate_2d_world(game);
	mlx_loop(game->engine->mlx);
	return (0);
}