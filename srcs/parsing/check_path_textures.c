/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:02:34 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 17:33:15 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

void	check_path_textures(t_game *game)
{
	char	*paths[4];
	int		i;
	int		len;
	int		fd;

	paths[0] = game->tex->no;
	paths[1] = game->tex->so;
	paths[2] = game->tex->we;
	paths[3] = game->tex->ea;
	i = 0;
	while (i < 4)
	{
		if (!paths[i])
			exit_error(game, "Error\nMissing texture", fd);
		if (ft_strlen(paths[i]) < 4)
			exit_error(game, "Error\nInvalid texture path", fd);
		len = ft_strlen(paths[i]);
		if (len < 4 || ft_strcmp((paths[i] + len) - 4, ".xpm") != 0)
			exit_error(game, "Error\nInvalid texture extension", fd);
		fd = open(paths[i], O_RDONLY);
		if (fd == -1)
			exit_error(game, "Error\nTexture file not found or unreadable", fd);
		close(fd);
		i++;
	}
}
