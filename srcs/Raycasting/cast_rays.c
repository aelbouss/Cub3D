/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:32:04 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 15:48:26 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	calculate_wall_dependencies(t_game *game)
{
	double	dist;

	if (get_closest_distance(game) == 'v')
		dist = game->engine->final_dist;
	else
		dist = game->engine->final_dist;
	game->engine->corrected_dist = dist * cos(game->engine->ray_angle
			- game->player->p_angle);
	if (game->engine->corrected_dist < 0.0001)
		game->engine->corrected_dist = 0.0001;
	game->engine->wall_height = (TILESIZE / game->engine->corrected_dist)
		* game->engine->dist_proj_plane;
	game->engine->wall_top_p = (SCREEN_H / 2) - (game->engine->wall_height / 2);
	if (game->engine->wall_top_p < 0)
		game->engine->wall_top_p = 0;
	game->engine->wall_bottom_p = (SCREEN_H / 2) + (game->engine->wall_height
			/ 2);
	if (game->engine->wall_bottom_p >= SCREEN_H)
		game->engine->wall_bottom_p = SCREEN_H - 1;
}

void	cast_3d_walls(t_game *game)
{
	t_img	buffer;
	int		x;
	double	ray_start;
	double	step;

	buffer.img_ptr = mlx_new_image(game->engine->mlx, SCREEN_W, SCREEN_H);
	buffer.addr = mlx_get_data_addr(buffer.img_ptr, &buffer.bpp,
			&buffer.line_len, &buffer.endian);
	buffer.width = SCREEN_W;
	buffer.height = SCREEN_H;
	x = 0;
	while (x < SCREEN_W)
	{
		ray_start = game->player->p_angle - (game->player->fov / 2.0);
		step = game->player->fov / (double)SCREEN_W;
		game->engine->ray_angle = normalize_angle(ray_start + x * step);
		horizontal_intersection_check(game);
		vertical_intersection_check(game);
		calculate_wall_dependencies(game);
		draw_column(game, &buffer, x);
		x++;
	}
	mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win,
		buffer.img_ptr, 0, 0);
	mlx_destroy_image(game->engine->mlx, buffer.img_ptr);
}
