/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:08:59 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/08 00:39:37 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	get_identifier_index(char *line)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (2);
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

void process_textures_we_and_ea(t_game *game, char *line, char *path, int fd)
{
	if (!ft_strncmp(line, "WE", 2))
	{
		if (game->tex->got_we)
		{
			free(line);
			exit_error(game, "Error\nDuplicate WE identifier", fd);
		}
		game->tex->identifiers_count++;
		game->tex->got_we++;
		game->tex->we = clean_line(path);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		if (game->tex->got_ea)
		{
			free(line);
			exit_error(game, "Error\nDuplicate EA identifier", fd);
		}
		game->tex->identifiers_count++;
		game->tex->got_ea++;
		game->tex->ea = clean_line(path);
	}
}

void	process_texture_data(t_game *game, char *line, char *path, int fd)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		if (game->tex->got_no)
		{
			free(line);
			exit_error(game, "Error\nDuplicate NO identifier", fd);
		}
		game->tex->identifiers_count++;
		game->tex->got_no++;
		game->tex->no = clean_line(path);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		if (game->tex->got_so)
		{
			free(line);
			exit_error(game, "Error\nDuplicate SO identifier", fd);
		}
		game->tex->identifiers_count++;
		game->tex->got_so++;
		game->tex->so = clean_line(path);
	}
	process_textures_we_and_ea(game, line, path, fd);
}


void	process_color_data(t_game *game, char *line, char *path, int fd)
{
	if (!ft_strncmp(line, "F", 1))
	{
		if (game->colors->got_floor)
		{
			free(line);
			exit_error(game, "Error\nDuplicate F identifier", fd);
		}
		game->colors->color_count++;
		game->colors->got_floor++;
		game->colors->floor = parse_color(game, line, path, fd);
	}
	else if (!ft_strncmp(line, "C", 1))
	{
		if (game->colors->got_ceiling)
		{
			free(line);
			exit_error(game, "Error\nDuplicate C identifier", fd);
		}
		game->colors->color_count++;
		game->colors->got_ceiling++;
		game->colors->ceiling = parse_color(game, line, path, fd);
	}
}

void	parse_identifier(t_game *game, char *line, int fd)
{
	int		i;
	char	*path;

	while (*line == ' ')
		line++;
	i = get_identifier_index(line);
	while (line[i] == ' ')
		i++;
	path = line + i;
	process_texture_data(game, line, path, fd);
	process_color_data(game, line, path, fd);
}
