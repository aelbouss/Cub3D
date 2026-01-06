# include  "../includes/game.h"



void horizontal_intersection_check(t_game *game)
{
    double rayangle;

    rayangle = normalize_angle(game->engine->ray_angle);
    if (rayangle > 0 && rayangle < PI) // looking down
        game->engine->near_y = floor(game->player->y / TILESIZE) * TILESIZE + TILESIZE;
    else // looking up
        game->engine->near_y = floor(game->player->y / TILESIZE) * TILESIZE - 0.001; // small offset for top-left corner
    game->engine->near_x = game->player->x + (game->engine->near_y - game->player->y ) / tan(rayangle);
    if (rayangle > 0 && rayangle < PI) // looking down
        game->engine->y_step = TILESIZE;
    else
        game->engine->y_step = -TILESIZE;
    game->engine->x_step = game->engine->y_step / tan(rayangle);
    game->engine->next_x = game->engine->near_x;
    game->engine->near_y = game->engine->near_y;
    while (game->engine->next_x >= 0 && game->engine->next_x <= game->engine->map_w &&
           game->engine->near_y >= 0 && game->engine->near_y <= game->engine->map_h &&
           !has_wall(game->engine->next_x, game->engine->near_y, game))
    {
        game->engine->next_x += game->engine->x_step;
        game->engine->near_y += game->engine->y_step;
    }
    game->engine->h_hit_x = game->engine->next_x;
    game->engine->h_hit_y = game->engine->near_y;
}

void vertical_intersection_check(t_game *game)
{
    double rayangle;

    rayangle = normalize_angle(game->engine->ray_angle);
    if (rayangle < 1.5 * PI && rayangle > 0.5 * PI) // looking left
        game->engine->near_x = floor(game->player->x / TILESIZE) * TILESIZE - 0.001; // offset for top-left corner
    else // looking right
        game->engine->near_x = floor(game->player->x / TILESIZE) * TILESIZE + TILESIZE;
    game->engine->near_y = game->player->y + (game->engine->near_x - game->player->x) * tan(rayangle);
    if (rayangle < 1.5 * PI && rayangle > 0.5 * PI) // looking left
       game->engine->x_step = -TILESIZE;
    else
       game->engine->x_step = TILESIZE;
    game->engine->y_step = game->engine->x_step * tan(rayangle);
    game->engine->next_x = game->engine->near_x;
    game->engine->next_y = game->engine->near_y;
    while (game->engine->next_x >= 0 && game->engine->next_x <= game->engine->map_w &&
           game->engine->next_y >= 0 && game->engine->next_y <= game->engine->map_h &&
           !has_wall(game->engine->next_x, game->engine->next_y, game))
    {
        game->engine->next_x += game->engine->x_step;
        game->engine->next_y += game->engine->y_step;
    }
    game->engine->v_hit_x = game->engine->next_x;
    game->engine->v_hit_y = game->engine->next_y;
}

// void cast_rays(t_game *game)
// {
//    double  angle_between_rays;
//    int ray_num;

//     ray_num = 60;
//     angle_between_rays = game->player->fov / ray_num;
//     game->player->p_angle = normalize_angle(game->player->p_angle);
//     game->engine->ray_angle = game->player->p_angle - (game->player->fov / 2); // start of the fov
//     while (ray_num > 0)
//     {
//         game->engine->ray_angle = normalize_angle(game->engine->ray_angle);
//         horizontal_intersection_check(game);
//         vertical_intersection_check(game);
//         if (get_closest_distance(game) == 'v')
//             draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->v_hit_x, game->engine->v_hit_y, RED);
//         else
//             draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->h_hit_x, game->engine->h_hit_y, RED);
//         game->engine->ray_angle += angle_between_rays ;
//         game->engine->h_hit_x = 0;
//         game->engine->h_hit_y = 0;
//         game->engine->v_hit_x = 0;
//         game->engine->v_hit_y = 0;
//         ray_num--;
//     }
// }

double  get_distance(double p1x, double p1y , double p2x, double p2y)
{
    double  fd;
    double  sd;

    fd = p1x - p2x ;
    sd = p1y - p2y ;
    return(sqrt(fd * fd + sd * sd));
}
char    get_closest_distance(t_game *game)
{
    double  v_distance;
    double  h_distance;

    v_distance = get_distance(game->player->x, game->player->y, game->engine->v_hit_x, game->engine->v_hit_y);
    h_distance = get_distance(game->player->x, game->player->y, game->engine->h_hit_x, game->engine->h_hit_y);
    if (v_distance <= h_distance)
    {
        game->engine->final_dist = v_distance;
        return ('v');
    }
    game->engine->final_dist = h_distance;
    return ('h');
}