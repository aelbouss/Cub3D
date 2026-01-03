/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:09:10 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 17:33:06 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	check_the_borders(t_game *game, int fd)
{
	int	j;

	// Check top row
	j = 0;
	while (game->map[0][j])
	{
		if (game->map[0][j] != '1')
			exit_error(game, "Error\nInvalid top border in map", fd);
		j++;
	}
	// Check bottom row
	j = 0;
	while (game->map[game->map_height - 1][j])
	{
		if (game->map[game->map_height - 1][j] != '1')
			exit_error(game, "Error\nInvalid bottom border in map", fd);
		j++;
	}
}

void	check_side_borders(t_game *game, int fd)
{
	int	i;
	int	last_index;

	i = 1;                           // skip first row
	while (i < game->map_height - 1) // skip last row
	{
		last_index = ft_strlen(game->map[i]) - 1;
		if (game->map[i][0] != '1' || game->map[i][last_index] != '1')
			exit_error(game, "Error\nInvalid side borders in map", fd);
		i++;
	}
}
