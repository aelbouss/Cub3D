# include "../includes/game.h"


int	is_pressed(int keycode, t_game *game)
{
	if (keycode == z)
		game->player->move_up = 1;
	else if (keycode == s)
		game->player->move_down = 1;
	else if (keycode == q)
		game->player->move_left = 1;
	else if (keycode == d)
		game->player->move_right = 1;
	else if (keycode == LEFT)
		game->player->rotate_left = 1;
	else if (keycode == RIGHT)
		game->player->rotate_right = 1;
	else if (keycode == ESC_KEY)
		exit(1);
	else if (keycode == 80679312)
	{
		mlx_destroy_window(game->engine->mlx, game->engine->mlx_win);
		exit(0);
	}
	return (0);
}

int	is_released(int keycode, t_game *game)
{
	if (keycode == z)
		game->player->move_up = 0;
	else if (keycode == s)
		game->player->move_down = 0;
	else if (keycode == q)
		game->player->move_left = 0;
	else if (keycode == d)
		game->player->move_right = 0;
	else if (keycode == LEFT)
		game->player->rotate_left = 0;
	else if (keycode == RIGHT)
		game->player->rotate_right = 0;
	return (0);
}

// This function should be called every frame for smooth input handling
int	handle_input(t_game *game)
{

	if (!game)
		dprintf(2, "Error: Game not initialized\n");
	if (game->player->move_up == 1)
		walk_forward(game);
	else if (game->player->move_down == 1)
		walk_backward(game);
	else if (game->player->move_left == 1)
		walk_left(game);
	else if (game->player->move_right == 1)
		walk_right(game);
	else if (game->player->rotate_left == 1)
		rotate_left(game);
	else if (game->player->rotate_right == 1)
		rotate_right(game);
	return (0);
}
