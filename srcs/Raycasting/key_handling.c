# include "../includes/game.h"


int	handle_input(int keycode, t_game *game)
{
	dprintf(2, "the key code %d\n",keycode);
	if (keycode == z)
		walk_forward(game);
	if (keycode == s)
		walk_backward(game);
	if (keycode == q)
		walk_left(game);
	if (keycode == d)
		walk_right(game);
	if (keycode == LEFT)
		retate_left(game);
	if (keycode == RIGHT)
		retate_right(game);
	if (keycode == ESC_KEY)
		exit(1);
	if (keycode == 80679312)
	{
		mlx_destroy_window(game->engine->mlx, game->engine->mlx_win);
		exit(0);
	}	
	return (0);
}