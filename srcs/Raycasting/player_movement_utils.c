/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:02:39 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 16:05:12 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	set_player_angle(t_game *game)
{
	if (game->player->dir == 'S')
		game->player->p_angle = PI / 2;
	if (game->player->dir == 'N')
		game->player->p_angle = 3 * PI / 2;
	if (game->player->dir == 'E')
		game->player->p_angle = 0;
	if (game->player->dir == 'W')
		game->player->p_angle = PI;
}

int	has_wall(double x, double y, t_game *game)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (1);
	map_x = floor(x / TILESIZE);
	map_y = floor(y / TILESIZE);
	if (map_y >= game->map_height)
		return (1);
	if (map_x >= (int)ft_strlen(game->map[map_y]))
		return (1);
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	rotate_left(t_game *game)
{
	game->player->p_angle -= 0.01;
	game->player->p_angle = normalize_angle(game->player->p_angle);
}

void	rotate_right(t_game *game)
{
	game->player->p_angle += 0.01;
	game->player->p_angle = normalize_angle(game->player->p_angle);
}
