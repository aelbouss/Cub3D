/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:52:45 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 16:04:27 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	move_with_collision(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;
	double	padding_x;
	double	padding_y;

	new_x = game->player->x + move_x;
	if (move_x > 0)
		padding_x = CLIP;
	else
		padding_x = -CLIP;
	if (!has_wall(new_x + padding_x, game->player->y, game))
		game->player->x = new_x;
	new_y = game->player->y + move_y;
	if (move_y > 0)
		padding_y = CLIP;
	else
		padding_y = -CLIP;
	if (!has_wall(game->player->x, new_y + padding_y, game))
		game->player->y = new_y;
}

void	walk_forward(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = cos(game->player->p_angle) * PLAYERSPEED;
	move_y = sin(game->player->p_angle) * PLAYERSPEED;
	move_with_collision(game, move_x, move_y);
}

void	walk_backward(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = -cos(game->player->p_angle) * PLAYERSPEED;
	move_y = -sin(game->player->p_angle) * PLAYERSPEED;
	move_with_collision(game, move_x, move_y);
}

void	walk_left(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = sin(game->player->p_angle) * PLAYERSPEED;
	move_y = -cos(game->player->p_angle) * PLAYERSPEED;
	move_with_collision(game, move_x, move_y);
}

void	walk_right(t_game *game)
{
	double	move_x;
	double	move_y;

	move_x = -sin(game->player->p_angle) * PLAYERSPEED;
	move_y = cos(game->player->p_angle) * PLAYERSPEED;
	move_with_collision(game, move_x, move_y);
}
