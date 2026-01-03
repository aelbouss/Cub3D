/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:03:51 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 17:33:27 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_game(t_game *game)
{
	int	i;

	if (game->tex->no)
		free(game->tex->no);
	if (game->tex->so)
		free(game->tex->so);
	if (game->tex->we)
		free(game->tex->we);
	if (game->tex->ea)
		free(game->tex->ea);
	if (game->map)
	{
		i = 0;
		while (i < game->map_height && game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}
