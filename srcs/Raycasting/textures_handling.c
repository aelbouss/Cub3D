/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:52:37 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 16:12:59 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

unsigned int	get_pixel_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

t_img	*select_texture(t_game *game, char side)
{
	if (side == 'v')
	{
		if (game->engine->ray_angle > PI / 2 && game->engine->ray_angle < 3 * PI
			/ 2)
			return (&game->tex->west);
		else
			return (&game->tex->east);
	}
	else
	{
		if (game->engine->ray_angle > PI && game->engine->ray_angle < 2 * PI)
			return (&game->tex->south);
		else
			return (&game->tex->north);
	}
	return (NULL);
}

void	allocate_img(t_game *game, t_img *img)
{
	img->image = mlx_new_image(game->engine->mlx, game->engine->map_w,
			game->engine->map_h);
	if (!img->image)
	{
		ft_putstr_fd("Error\n Image Allocation Failed\n", 2);
		clean_game(game);
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->image, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
	{
		ft_putstr_fd("Error\n Failed to get image data\n", 2);
		mlx_destroy_image(game->engine->mlx, img->image);
		clean_game(game);
		exit(1);
	}
}

void	draw_wall_texture(t_game *game, t_img *buffer, int x)
{
	t_img	*tex;
	int		y;
	double	step;
	double	texpos;

	tex = get_texture_info(game, &game->engine->texx);
	step = 1.0 * tex->height / game->engine->wall_height;
	texpos = (game->engine->wall_top_p - ((SCREEN_H / 2)
				- ((int)game->engine->wall_height / 2))) * step;
	y = game->engine->wall_top_p;
	while (y <= game->engine->wall_bottom_p)
	{
		game->engine->texy = (int)texpos;
		if (game->engine->texy >= tex->height)
			game->engine->texy = tex->height - 1;
		if (game->engine->texy < 0)
			game->engine->texy = 0;
		texpos += step;
		put_pixel_to_img(buffer, x, y, get_pixel_color(tex, game->engine->texx,
				game->engine->texy));
		y++;
	}
}
