/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 01:02:27 by string            #+#    #+#             */
/*   Updated: 2026/01/04 01:30:29 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

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
void flood_fill(char **map, t_game *game, int x, int y, int fd)
{
    if (y < 0 || y >= game->map_height || x < 0 || x >= (int)ft_strlen(map[y]))
    {
        free_array(map);
        exit_error(game, "Error\nMap is open", fd);
    }
    if (map[y][x] == '1' || map[y][x] == 'F')
        return ;
    if (map[y][x] == ' ')
    {
        free_array(map);
        exit_error(game, "Error\nMap is open", fd);
    }
    map[y][x] = 'F';
    flood_fill(map, game, x + 1, y, fd);
    flood_fill(map, game, x - 1, y, fd);
    flood_fill(map, game, x, y + 1, fd);
    flood_fill(map, game, x, y - 1, fd);
}
