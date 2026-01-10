/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:08:23 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/10 04:26:31 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//# include "../includes/cub3d.h"
#include "../includes/game.h"

int	cross_exit(t_game *game)
{
	clean_game(game);
	exit(0);
}

void	parsing(t_game *game, int fd, char **av)
{
	char	**map_dup;

	initialize_game_utils(game);
	check_file_extension(game, av[1], fd);
	init_struct(game);
	parse_map(game, fd);
	map_dup = dup_map(game);
	flood_fill(map_dup, game, *game->player_pos, fd);
	close(fd);
	free_array(map_dup);
}

void	raycasting(t_game *game)
{
	setup_engine(game);
	cast_3d_walls(game);
	mlx_hook(game->engine->mlx_win, 17, 0, cross_exit, game);
	mlx_hook(game->engine->mlx_win, 2, 1L << 0, is_pressed, game);
	mlx_hook(game->engine->mlx_win, 3, 1L << 1, is_released, game);
	mlx_loop_hook(game->engine->mlx, handle_input, game);
	mlx_loop(game->engine->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;
	int		fd;

	if (ac != 2)
	{
		printf("Usage: %s <map_file.cub>\n", av[0]);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	game = build_base();
	parsing(game, fd, av);
	raycasting(game);
}
