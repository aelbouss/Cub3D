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
}

// int	has_wall(double x , double y , t_game *game)
// {
// 	if (game ->map[(int)y / TILESIZE][(int)x / TILESIZE] != '1')
// 		return (0);
// 	return (1);
// }


int has_wall(double x, double y, t_game *game)
{
    int map_x;
    int map_y;

    if (x < 0 || y < 0)
        return (1); // Consider outside the world as a wall

    map_x = floor(x / TILESIZE);
    map_y = floor(y / TILESIZE);

    // 1. Check strict bounds
    if (map_y >= game->map_height)
        return (1);
    // Since we padded the map, we can just check the first line's length
    // or keep it safe by checking strlen of the specific line
    if (map_x >= (int)ft_strlen(game->map[map_y]))
        return (1);

    // 2. Check for Wall ('1')
    if (game->map[map_y][map_x] == '1')
        return (1);
        
    // 3. (Optional) Treat spaces as walls to fix your "walking through" issue
    // if (game->map[map_y][map_x] == ' ')
    //     return (1);

    return (0);
}

#define CLIP 40 // Distance to keep from the wall

void move_with_collision(t_game *game, double move_x, double move_y)
{
    double new_x;
    double new_y;
    double padding_x;
    double padding_y;

    new_x = game->player->x + move_x;
    
    // 1. Determine padding for X without ternary operator
    if (move_x > 0)
        padding_x = CLIP;
    else
        padding_x = -CLIP;

    // 2. Try moving along X axis
    if (!has_wall(new_x + padding_x, game->player->y, game))
        game->player->x = new_x;

    new_y = game->player->y + move_y;

    // 3. Determine padding for Y without ternary operator
    if (move_y > 0)
        padding_y = CLIP;
    else
        padding_y = -CLIP;

    // 4. Try moving along Y axis (using potentially updated X)
    if (!has_wall(game->player->x, new_y + padding_y, game))
        game->player->y = new_y;
}
 

void walk_forward(t_game *game)
{
    double move_x;
    double move_y;

    move_x = cos(game->player->p_angle) * PLAYERSPEED;
    move_y = sin(game->player->p_angle) * PLAYERSPEED;

    move_with_collision(game, move_x, move_y);
}

void walk_backward(t_game *game)
{
    double move_x;
    double move_y;

    move_x = -cos(game->player->p_angle) * PLAYERSPEED;
    move_y = -sin(game->player->p_angle) * PLAYERSPEED;

    move_with_collision(game, move_x, move_y);
}

void walk_left(t_game *game)
{
    double move_x;
    double move_y;

    move_x = sin(game->player->p_angle) * PLAYERSPEED;
    move_y = -cos(game->player->p_angle) * PLAYERSPEED;

    move_with_collision(game, move_x, move_y);
}

void walk_right(t_game *game)
{
    double move_x;
    double move_y;

    move_x = -sin(game->player->p_angle) * PLAYERSPEED;
    move_y = cos(game->player->p_angle) * PLAYERSPEED;

    move_with_collision(game, move_x, move_y);
}

// void	walk_forward(t_game *game)
// {
// 	double	px;
// 	double	py;

// 	px = game->player->x + cos(game->player->p_angle) * PLAYERSPEED;
// 	py = game->player->y + sin(game->player->p_angle) * PLAYERSPEED;

// 	if (!has_wall(px, game->player->y, game))
// 		game->player->x = px;
// 	if (!has_wall(game->player->x, py, game))
// 		game->player->y = py;
// }

// void	walk_backward(t_game *game)
// {
// 	double	px;
// 	double	py;

// 	px = game->player->x - cos(game->player->p_angle) * PLAYERSPEED;
// 	py = game->player->y - sin(game->player->p_angle) * PLAYERSPEED;

// 	if (!has_wall(px, game->player->y, game))
// 		game->player->x = px;
// 	if (!has_wall(game->player->x, py, game))
// 		game->player->y = py;
// }

// void	walk_left(t_game *game)
// {
// 	double	px;
// 	double	py;

// 	px = game->player->x + sin(game->player->p_angle) * PLAYERSPEED;
// 	py = game->player->y - cos(game->player->p_angle) * PLAYERSPEED;

// 	if (!has_wall(px, game->player->y, game))
// 		game->player->x = px;
// 	if (!has_wall(game->player->x, py, game))
// 		game->player->y = py;
// }

// void	walk_right(t_game *game)
// {
// 	double	px;
// 	double	py;

// 	// Move perpendicular to the player's angle (right/strafe)
// 	px = game->player->x - sin(game->player->p_angle) * PLAYERSPEED;
// 	py = game->player->y + cos(game->player->p_angle) * PLAYERSPEED;

// 	if (!has_wall(px, game->player->y, game))
// 		game->player->x = px;
// 	if (!has_wall(game->player->x, py, game))
// 		game->player->y = py;
// }

double normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	rotate_left(t_game *game)
{
	game->player->p_angle -= 0.1;
	game->player->p_angle = normalize_angle(game->player->p_angle);
}

void	rotate_right(t_game *game)
{
	game->player->p_angle += 0.1;
	game->player->p_angle = normalize_angle(game->player->p_angle);
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