/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 01:02:27 by string            #+#    #+#             */
/*   Updated: 2026/01/03 17:33:22 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

char	**dup_map(t_game *game)
{
	char	**dest;
	int		i;

	dest = malloc(sizeof(char *) * (game->map_height + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		dest[i] = ft_strdup(game->map[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	flood_fill(char **map, t_game *game, t_player player, int fd)
{
	if (player.y < 0 || player.y >= game->map_height || player.x < 0
		|| player.x >= ft_strlen(map[player.y]))
	{
		free_array(map);
		exit_error(game, "Error\nMap is open", fd);
	}
	if (map[player.y][player.x] == '1' || map[player.y][player.x] == 'F')
		return ;
	if (map[player.y][player.x] == ' ')
	{
		free_array(map);
		exit_error(game, "Error\nMap is open", fd);
	}
	map[player.y][player.x] = 'F';
	flood_fill(map, game, (t_player){player.x + 1, player.y, player.dir}, fd);
	flood_fill(map, game, (t_player){player.x - 1, player.y, player.dir}, fd);
	flood_fill(map, game, (t_player){player.x, player.y + 1, player.dir}, fd);
	flood_fill(map, game, (t_player){player.x, player.y - 1, player.dir}, fd);
}
