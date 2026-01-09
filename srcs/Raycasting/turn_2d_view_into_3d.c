/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_2d_view_into_3d.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:07:13 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 16:07:14 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	load_texture(t_game *game, t_img *tex, char *path)
{
	tex->image = mlx_xpm_file_to_image(game->engine->mlx, path, &tex->width,
			&tex->height);
	if (!tex->image)
	{
		ft_putstr_fd("Error\nTexture load failed\n", 2);
		clean_game(game);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->image, &tex->bpp, &tex->line_len,
			&tex->endian);
}

int	allocate_textures(t_game *game)
{
	load_texture(game, &game->tex->north, game->tex->no);
	load_texture(game, &game->tex->south, game->tex->so);
	load_texture(game, &game->tex->west, game->tex->we);
	load_texture(game, &game->tex->east, game->tex->ea);
	return (0);
}
