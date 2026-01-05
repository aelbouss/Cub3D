# include "../includes/game.h"



void put_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
}

// DDA line drawing algorithm
void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps;
    float x_inc, y_inc;
    float x = x0;
    float y = y0;

    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    x_inc = dx / (float)steps;
    y_inc = dy / (float)steps;

    for (int i = 0; i <= steps; i++)
    {
        put_pixel(mlx_ptr, win_ptr, round(x), round(y), color);
        x += x_inc;
        y += y_inc;
    }
}

void cast_rays(t_game *game)
{
   double  angle_between_rays;
   int ray_num;

    ray_num = 60;
    angle_between_rays = game->player->fov / ray_num;
    game->player->p_angle = normalize_angle(game->player->p_angle);
    game->engine->ray_angle = game->player->p_angle - (game->player->fov / 2); // start of the fov
    while (ray_num > 0)
    {
        game->engine->ray_angle = normalize_angle(game->engine->ray_angle);
        horizontal_intersection_check(game);
        vertical_intersection_check(game);
        if (get_closest_distance(game) == 'v')
            draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->v_hit_x, game->engine->v_hit_y, RED);
        else
            draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->h_hit_x, game->engine->h_hit_y, RED);
        game->engine->ray_angle += angle_between_rays ;
        game->engine->h_hit_x = 0;
        game->engine->h_hit_y = 0;
        game->engine->v_hit_x = 0;
        game->engine->v_hit_y = 0;
        ray_num--;
    }
}






