/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_handing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:54:59 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 15:57:13 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	get_h_intersections(t_game *game)
{
	while (game->engine->next_x >= 0
		&& game->engine->next_x <= game->engine->map_w
		&& game->engine->near_y >= 0
		&& game->engine->near_y <= game->engine->map_h
		&& !has_wall(game->engine->next_x, game->engine->near_y, game))
	{
		game->engine->next_x += game->engine->x_step;
		game->engine->near_y += game->engine->y_step;
	}
	game->engine->h_hit_x = game->engine->next_x;
	game->engine->h_hit_y = game->engine->near_y;
}

void	horizontal_intersection_check(t_game *game)
{
	double	rayangle;

	rayangle = normalize_angle(game->engine->ray_angle);
	if (rayangle > 0 && rayangle < PI)
		game->engine->near_y = floor(game->player->y / TILESIZE) * TILESIZE
			+ TILESIZE;
	else
		game->engine->near_y = floor(game->player->y / TILESIZE) * TILESIZE
			- 0.001;
	game->engine->near_x = game->player->x + (game->engine->near_y
			- game->player->y) / tan(rayangle);
	if (rayangle > 0 && rayangle < PI)
		game->engine->y_step = TILESIZE;
	else
		game->engine->y_step = -TILESIZE;
	game->engine->x_step = game->engine->y_step / tan(rayangle);
	game->engine->next_x = game->engine->near_x;
	game->engine->near_y = game->engine->near_y;
	get_h_intersections(game);
}

void	get_v_intersections(t_game *game)
{
	while (game->engine->next_x >= 0
		&& game->engine->next_x <= game->engine->map_w
		&& game->engine->next_y >= 0
		&& game->engine->next_y <= game->engine->map_h
		&& !has_wall(game->engine->next_x, game->engine->next_y, game))
	{
		game->engine->next_x += game->engine->x_step;
		game->engine->next_y += game->engine->y_step;
	}
	game->engine->v_hit_x = game->engine->next_x;
	game->engine->v_hit_y = game->engine->next_y;
}

void	vertical_intersection_check(t_game *game)
{
	double	rayangle;

	rayangle = normalize_angle(game->engine->ray_angle);
	if (rayangle < 1.5 * PI && rayangle > 0.5 * PI)
		game->engine->near_x = floor(game->player->x / TILESIZE) * TILESIZE
			- 0.001;
	else
		game->engine->near_x = floor(game->player->x / TILESIZE) * TILESIZE
			+ TILESIZE;
	game->engine->near_y = game->player->y + (game->engine->near_x
			- game->player->x) * tan(rayangle);
	if (rayangle < 1.5 * PI && rayangle > 0.5 * PI)
		game->engine->x_step = -TILESIZE;
	else
		game->engine->x_step = TILESIZE;
	game->engine->y_step = game->engine->x_step * tan(rayangle);
	game->engine->next_x = game->engine->near_x;
	game->engine->next_y = game->engine->near_y;
	get_v_intersections(game);
}

double	get_distance(double p1x, double p1y, double p2x, double p2y)
{
	double	fd;
	double	sd;

	fd = p1x - p2x;
	sd = p1y - p2y;
	return (sqrt(fd * fd + sd * sd));
}
