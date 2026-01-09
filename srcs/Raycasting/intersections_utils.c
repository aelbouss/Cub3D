/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:57:37 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 16:00:11 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

char	get_closest_distance(t_game *game)
{
	double	v_distance;
	double	h_distance;

	v_distance = get_distance(game->player->x, game->player->y,
			game->engine->v_hit_x, game->engine->v_hit_y);
	h_distance = get_distance(game->player->x, game->player->y,
			game->engine->h_hit_x, game->engine->h_hit_y);
	if (v_distance <= h_distance)
	{
		game->engine->final_dist = v_distance;
		return ('v');
	}
	game->engine->final_dist = h_distance;
	return ('h');
}
