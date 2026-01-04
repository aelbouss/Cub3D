/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:01:15 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	check_file_extension(t_game *game, char *filename, int fd)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
		exit_error(game, "Error\nInvalid file extension. Must be .cub", fd);
}
