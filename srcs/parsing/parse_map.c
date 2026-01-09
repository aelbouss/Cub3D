/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:35:50 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/09 02:30:16 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	check_allowed_characters(t_game *game, int fd)
{
	int (i), (j);
	i = 0;
	if (!game->map)
		exit_error(game, "Error\nEmpty Map", fd);
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_map_char(game->map[i][j]) && game->map[i][j] != '\n')
				exit_error(game, "Error\nInvalid character in map", fd);
			j++;
		}
		i++;
	}
}

void	store_map_line(t_game *game, char *line, int fd)
{
	char	*cleaned_line;

	game->map_started = 1;
	cleaned_line = clean_line(line);
	game->map = resize_map(game, game->map, game->map_height, fd);
	game->map[game->map_height] = cleaned_line;
	game->map_height++;
}

void	init_struct(t_game *game)
{
	game->map = NULL;
	game->tex->identifiers_count = 0;
	game->colors->color_count = 0;
	game->tex->got_no = 0;
	game->tex->got_so = 0;
	game->tex->got_we = 0;
	game->tex->got_ea = 0;
	game->colors->got_floor = 0;
	game->colors->got_ceiling = 0;
	game->map_started = 0;
	game->player_pos->player_found = 0;
}

void	validate_map(t_game *game, int fd)
{
	if (game->tex->identifiers_count != 4 || game->colors->color_count != 2)
		exit_error(game, "Error\nInvalid number of identifiers", fd);
	check_path_textures(game);
	check_allowed_characters(game, fd);
	check_the_borders(game, fd);
	check_side_borders(game, fd);
	find_player_pos(game, fd);
}

void	parse_map(t_game *game, int fd)
{
	char	*line;

	init_struct(game);
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line) && !game->map_started)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_empty_line(line) && game->map_started)
			(free(line), exit_error(game, "Error\nVoid after map start", fd));
		if (!game->map_started && is_identifier(line))
			parse_identifier(game, line, fd);
		else if (is_map_line(line))
			store_map_line(game, line, fd);
		else
			(free(line), exit_error(game, "Error\nInvalid line", fd));
		free(line);
		line = get_next_line(fd);
	}
	validate_map(game, fd);
	make_map_rectangular(game);
}
