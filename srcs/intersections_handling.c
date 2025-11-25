#include "../includes/cub3d.h"

char    get_player_direction(double p_angle)
{
    // Normalize angle to 0 ~ 2*PI
    while (p_angle < 0)
        p_angle += 2 * PI;
    while (p_angle >= 2 * PI)
        p_angle -= 2 * PI;

    if ((p_angle >= 7 * PI / 4) || (p_angle < PI / 4))
        return ('r');
    else if (p_angle >= PI / 4 && p_angle < 3 * PI / 4)
        return ('u');
    else if (p_angle >= 3*PI/4 && p_angle < 5 * PI / 4)
        return ('l')
    else
        return ('d');
}

void    horizontal_intersection_check(t_box *box )
{

    double  next_y;
    double  next_x;
    double  near_x;
    double  near_y;
    double  x_step;
    double  y_step;

    if (get_player_direction(box->ray->ray_angle) == 'u')
        near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE;
    if (get_player_direction(box->ray->ray_angle) == 'd')
        near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE + TILESIZE;
    near_x = box->plyr->p_x + (near_y - box->plyr->p_y) / tan(box->ray->ray_angle);

    if (get_player_direction(box->ray->ray_angle) == 'd')
        y_step = TILESIZE;
    if (get_player_direction(box->ray->ray_angle) == 'u')
        y_step = -TILESIZE;
    x_step = y_step / tan(box->ray->ray_angle);
    if (get_player_direction && x_step > 0)
        x_step *= -1 ;
    if (get_player_direction() && x_step < 0)
        x_step *= -1 ;
    while (next_y >= 0 && next_y <= box->ray->game_h && next_x >= 0 && next_x <= box->ray->game_w)
    {
        if (has_wall(box, next_x, next_y) == 1)
        {
            box->ray->h_hit_x = next_x;
            box->ray->h_hit_y = next_y;
            return ;
        }
        next_y += y_step;
        next_x += x_step;
    }
}


void    vertical_intersection_check(t_box *box)
{
    double  next_y;
    double  next_x;
    double  near_x;
    double  near_y;
    double  x_step;
    double  y_step;

    if (get_player_direction(box->ray->ray_angle) == 'r')
        near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE + TILESIZE ;
    else
        near_x = floor(box->plyr->p_x / TILESIZE) + TILESIZE ;
    
    if (get_player_direction(box->ray->ray_angle) == 'r')
        x_step = TILESIZE;
    else
        x_step = -TILESIZE;
    near_y = box->plyr->p_y + (near_x - box->plyr->p_x) * tan(box->ray->ray_angle);
    y_step = x_step * tan(box->ray->ray_angle);
    next_y = near_y ;
    next_x = near_x ;
    while (next_y >= 0 && next_y <= box->ray->game_h && next_x >= 0 && next_x <= box->ray->game_w)
    {
        if (has_wall(box, next_x, next_y) == 1)
        {
            box->ray->v_hit_x = next_x;
            box->ray->v_hit_y = next_y;
            return ;
        }
        next_x += x_step;
        next_y += y_step;
    }
}

