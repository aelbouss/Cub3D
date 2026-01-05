# include "../includes/game.h"

void	set_player_angle(t_game *game)
{
	int	h;
	int	w;

	if (game->player->dir == 'S')
		game->player->p_angle = PI / 2 ;
	if (game->player->dir == 'N')
		game->player->p_angle = 3 * PI / 2;
	if (game->player->dir == 'E')
		game->player->p_angle = 0;
	if (game->player->dir == 'W')
		game->player->p_angle = PI;
	h = 0;
	while (game->map[h])
	{
		w = 0;
		while (game->map[h][w])
		{
			if (game->map[h][w] == 'S' || game->map[h][w] == 'N' || game->map[h][w] == 'E' || game->map[h][w] == 'W')
			{
				game->map[h][w] = '0';
				return ;
			}
			w++;
		}
		h++;
	}
	dprintf(2, "=>>>>>>>>>>>><<<<  the  player  angle  is  : %lf\n",game->player->p_angle );
}

int	has_wall(double x , double y , t_game *game)
{
	if (game ->map[(int)y / TILESIZE][(int)x / TILESIZE] == '1')
		return (1);
	return (0);
}


void	walk_forward(t_game *game)
{
	double	px;
	double	py;

	px =  game->player->x + cos(game->player->p_angle) * PLAYERSPEED;
	py =  game->player->y + sin(game->player->p_angle) * PLAYERSPEED;

	if (has_wall(px, py, game))
		return ;
	game->player->x += cos(game->player->p_angle) * PLAYERSPEED;
	game->player->y += sin(game->player->p_angle) * PLAYERSPEED;
	generate_2d_world(game);
	//draw_player(game);
	cast_rays(game);
}

void	walk_backward(t_game *game)
{
	double	px;
	double	py;

	px =  game->player->x - cos(game->player->p_angle) * PLAYERSPEED;
	py =  game->player->y - sin(game->player->p_angle) * PLAYERSPEED;

	if (has_wall(px, py, game) == 1)
		return ;
	game->player->x -= cos(game->player->p_angle) * PLAYERSPEED;
	game->player->y -= sin(game->player->p_angle) * PLAYERSPEED;
	generate_2d_world(game);
	//draw_player(game);
	cast_rays(game);
}

void	walk_left(t_game *game)
{
	double	px;
	double	py;

	px =  game->player->x + cos(game->player->p_angle) * PLAYERSPEED;
	py =  game->player->y - sin(game->player->p_angle) * PLAYERSPEED;

	if (has_wall(px, py , game))
		return ;
	game->player->x += sin(game->player->p_angle) * PLAYERSPEED;
	game->player->y -= cos(game->player->p_angle) * PLAYERSPEED;
	generate_2d_world(game);
	//draw_player(game);
	cast_rays(game);
}

void	walk_right(t_game *game)
{
	double	px;
	double	py;

	
	px =  game->player->x - cos(game->player->p_angle) * PLAYERSPEED;
	py =  game->player->y + sin(game->player->p_angle) * PLAYERSPEED;

	if (has_wall(px, py, game))
		return ;
	game->player->x -= sin(game->player->p_angle) * PLAYERSPEED;
	game->player->y += cos(game->player->p_angle) * PLAYERSPEED;
	generate_2d_world(game);
	//draw_player(game);
	cast_rays(game);
}
double normalize_angle(double angle)
{
    // Use fmod to wrap the angle around 2*PI
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return (angle);
}

void	retate_left(t_game *game)
{

	game->player->p_angle -= 0.1;
	game->player ->p_angle = normalize_angle(game->player->p_angle);
	generate_2d_world(game);
	//draw_player(game);
	cast_rays(game);
}

void	retate_right(t_game *game)
{
	game->player->p_angle += 0.1;
	game->player ->p_angle = normalize_angle(game->player->p_angle);
	generate_2d_world(game);
	//draw_player(game);
	cast_rays(game);
}

void	draw_player (t_game *game)
{
	int	y;
	int	x;

	y = 0;

	while (y < 10 )
	{
		x = 0; 
		while (x < 10)
		{
			mlx_pixel_put(game->engine->mlx, game->engine->mlx_win, game->player->x + x, game->player->y + y, RED);
			x++;
		}
		y++;
	}
}