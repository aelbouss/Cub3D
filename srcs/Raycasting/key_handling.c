/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:00:37 by aelbouss          #+#    #+#             */
/*   Updated: 2026/01/09 16:22:12 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	is_pressed(int keycode, t_game *game)
{
	if (keycode == W)
		game->player->move_up = 1;
	else if (keycode == S)
		game->player->move_down = 1;
	else if (keycode == A)
		game->player->move_left = 1;
	else if (keycode == D)
		game->player->move_right = 1;
	else if (keycode == LEFT)
		game->player->rotate_left = 1;
	else if (keycode == RIGHT)
		game->player->rotate_right = 1;
	else if (keycode == ESC_KEY)
	{
		clean_game(game);
		exit(0);
	}
	return (0);
}

int	is_released(int keycode, t_game *game)
{
	if (keycode == W)
		game->player->move_up = 0;
	else if (keycode == S)
		game->player->move_down = 0;
	else if (keycode == A)
		game->player->move_left = 0;
	else if (keycode == D)
		game->player->move_right = 0;
	else if (keycode == LEFT)
		game->player->rotate_left = 0;
	else if (keycode == RIGHT)
		game->player->rotate_right = 0;
	return (0);
}

int	handle_input(t_game *game)
{
	if (game->player->rotate_left == 1)
		rotate_left(game);
	if (game->player->rotate_right == 1)
		rotate_right(game);
	if (game->player->move_up == 1)
		walk_forward(game);
	if (game->player->move_down == 1)
		walk_backward(game);
	if (game->player->move_left == 1)
		walk_left(game);
	if (game->player->move_right == 1)
		walk_right(game);
	cast_3d_walls(game);
	return (0);
}
