/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaanane <ridamaanane@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:02:34 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/09 23:35:24 by rmaanane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	premature_cleaner(t_game *game)
{
	if (game->map)
		free_array(game->map);
	if (game->colors)
		free(game->colors);
	if (game->tex)
		free(game->tex);
	if (game->player)
		free(game->player);
	if (game->player_pos)
		free(game->player_pos);
	if (game->engine)
		free(game->engine);
	if (game)
		free(game);
}

void	check_path_textures(t_game *game)
{
	char	*paths[4];

	int (i), (fd);
	paths[0] = game->tex->no;
	paths[1] = game->tex->so;
	paths[2] = game->tex->we;
	paths[3] = game->tex->ea;
	i = 0;
	while (i < 4)
	{
		if (!paths[i])
			exit_error(game, "Error\nMissing texture", -1);
		if (ft_strlen(paths[i]) < 4)
			exit_error(game, "Error\nInvalid texture path", -1);
		if (ft_strcmp((paths[i] + ft_strlen(paths[i])) - 4, ".xpm") != 0)
			exit_error(game, "Error\nInvalid texture extension", -1);
		fd = open(paths[i], O_RDONLY);
		if (fd == -1)
			exit_error(game, "Error\nTexture file not found or unreadable", -1);
		close(fd);
		i++;
	}
}
