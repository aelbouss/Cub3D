#include  "../includes/game.h"



int	walk_forward(t_game *game)
{
	double	px;
	double	py;

	px = game->player->x + cos(game->player->p_angle) * PLAYERSPEED;
	py = game->player->y + sin(game->player->p_angle) * PLAYERSPEED;
	if (has_wall(px, py, game))
		return (1);
	game->player->x += cos(game->player->p_angle) * PLAYERSPEED;
	game->player->y += sin(game->player->p_angle) * PLAYERSPEED;
	generate_2d_world(game);
	cast_rays(game);
	return (0);
}

int	walk_backward(t_game *game)
{
	double	px;
	double	py;

	px = game->player->x - cos(game->player->p_angle) * PLAYERSPEED;
	py = game->player->y - sin(game->player->p_angle) * PLAYERSPEED;
	if (has_wall(px, py, game))
		return (1);
	game->player->x -= cos(game->player->p_angle) * PLAYERSPEED;
	game->player->y -= sin(game->player->p_angle) * PLAYERSPEED;
	generate_2d_world(game);
	cast_rays(game);
	return (0);
}



int	walk_left(t_game *game)
{
	double	px;
	double	py;

	px = game->player->x + cos(game->player->p_angle) * PLAYERSPEED;
	py = game->player->y - sin(game->player->p_angle) * PLAYERSPEED;
	if (has_wall(px, py, game))
		return (1);
	game->player->x += sin(game->player->p_angle) * PLAYERSPEED;
	game->player->y -= cos(game->player->p_angle) * PLAYERSPEED;
	generate_2d_world(game);
	cast_rays(game);
	return (0);
}

int	walk_right(t_game *game)
{
	double	px;
	double	py;

	px = game->player->x - cos(game->player->p_angle) * PLAYERSPEED;
	py = game->player->y + sin(game->player->p_angle) * PLAYERSPEED;
	if (has_wall(px, py, game))
		return (1);
	game->player->x -= sin(game->player->p_angle) * PLAYERSPEED;
	game->player->y += cos(game->player->p_angle) * PLAYERSPEED;
	generate_2d_world(game);
	cast_rays(game);
	return (0);
}

int	retate_right(t_game *game)
{
	game->player->p_angle += 0.1;
	game->player->p_angle = normalize_angle(game->player->p_angle);
    generate_2d_world(game);
	cast_rays(game);
	return (0);
}

int	retate_left(t_game *game)
{
	game->player->p_angle -= 0.1;
	game->player->p_angle = normalize_angle(game->player->p_angle);
    generate_2d_world(game);
	cast_rays(game);
	return (0);
}
