/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:34:57 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 15:48:22 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

t_img	*get_texture_info(t_game *game, int *texx)
{
	t_img	*tex;
	double	wallx;
	char	side;

	tex = NULL;
	side = get_closest_distance(game);
	tex = select_texture(game, side);
	if (side == 'v')
		wallx = game->engine->v_hit_y / TILESIZE;
	else
		wallx = game->engine->h_hit_x / TILESIZE;
	wallx -= floor(wallx);
	*texx = (int)(wallx * (double)tex->width);
	if ((side == 'v' && game->engine->ray_angle > PI / 2
			&& game->engine->ray_angle < 3 * PI / 2) || (side == 'h'
			&& !(game->engine->ray_angle > PI && game->engine->ray_angle < 2
				* PI)))
		*texx = tex->width - *texx - 1;
	return (tex);
}

void	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_column(t_game *game, t_img *buffer, int x)
{
	int	y;

	y = 0;
	while (y < game->engine->wall_top_p)
	{
		put_pixel_to_img(buffer, x, y, game->colors->ceiling);
		y++;
	}
	draw_wall_texture(game, buffer, x);
	y = game->engine->wall_bottom_p + 1;
	while (y < SCREEN_H)
	{
		put_pixel_to_img(buffer, x, y, game->colors->floor);
		y++;
	}
}
