/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:08:59 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
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

void	process_texture_data(t_game *game, char *line, char *path)
{
	if (!ft_strncmp(line, "NO", 2) && !game->tex->got_no)
	{
		game->tex->identifiers_count++;
		game->tex->got_no++;
		game->tex->no = clean_line(path);
	}
	else if (!ft_strncmp(line, "SO", 2) && !game->tex->got_so)
	{
		game->tex->identifiers_count++;
		game->tex->got_so++;
		game->tex->so = clean_line(path);
	}
	else if (!ft_strncmp(line, "WE", 2) && !game->tex->got_we)
	{
		game->tex->identifiers_count++;
		game->tex->got_we++;
		game->tex->we = clean_line(path);
	}
	else if (!ft_strncmp(line, "EA", 2) && !game->tex->got_ea)
	{
		game->tex->identifiers_count++;
		game->tex->got_ea++;
		game->tex->ea = clean_line(path);
	}
}

void	process_color_data(t_game *game, char *line, char *path, int fd)
{
	if (!ft_strncmp(line, "F", 1) && !game->colors->got_floor)
	{
		game->colors->color_count++;
		game->colors->got_floor++;
		game->colors->floor = parse_color(game, line, path, fd);
	}
	else if (!ft_strncmp(line, "C", 1) && !game->colors->got_ceiling)
	{
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
	process_texture_data(game, line, path);
	process_color_data(game, line, path, fd);
}
