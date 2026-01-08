/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:05:30 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/07 22:19:15 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

char	*clean_line(char *line)
{
	int		i;
	char	*new;

	new = malloc(ft_strlen(line) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**resize_map(t_game *game, char **map, int map_height, int fd)
	// make space for the new line + NULL
{
	char	**tmp;
	// 1 new line (We reserved the line) + 1 NULL
	tmp = realloc(map, sizeof(char *) * (map_height + 2));
	if (!tmp)
		exit_error(game, "Error\nMemory allocation failed", fd);
	tmp[map_height + 1] = NULL;
		// tmp[map_height] → this is where we store the new line so+ 1 for the NULL
	return (tmp);
}



void	find_player_pos(t_game *game, int fd)
{
	int (i), (j), (player_found);
	player_found = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				if (player_found)
					exit_error(game, "Error\nMultiple players!", fd);
				game->player->x = (double)j * TILESIZE + (TILESIZE / 2.0) ;
				game->player->y = (double)i * TILESIZE + (TILESIZE / 2.0) ;
				game->player->pos_x = j;
				game->player->pos_y = i;
				game->player->dir = game->map[i][j];
				player_found = 1;
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		exit_error(game, "Error\nNo player found!", fd);
}

void	exit_error(t_game *game, char *msg, int fd)
{
	char	*tmp;

	ft_putendl_fd(msg, 2);
	tmp = get_next_line(fd);	
	while (tmp) // clean rest of the file
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	if (game->tex->no)
		free(game->tex->no);
	if (game->tex->so)
		free(game->tex->so);
	if (game->tex->we)
		free(game->tex->we);
	if (game->tex->ea)
		free(game->tex->ea);
	premature_cleaner(game, msg);
	// (void)game;
	close(fd);
	exit(1);
}
