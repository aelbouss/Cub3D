#include "../includes/cub3d.h"

void    horizontal_intersection_check(t_box *box )
{
    double  next_y;
    double  next_x;
    double  rayangle;

    rayangle = box->ray->ray_angle;
    if (!(rayangle > 0 && rayangle < PI)) // FAcin down
        box->ray->near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE - 1;
    else
        box->ray->near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE + TILESIZE; //facing up
    box->ray->near_x = box->plyr->p_x + (box->ray->near_y - box->plyr->p_y) / tan(rayangle);
    if (rayangle > 0 && rayangle < PI)
        box->ray->y_step = TILESIZE;
    else
        box->ray->y_step = -TILESIZE;
    box->ray->x_step = box->ray->y_step / tan(rayangle);
    next_x =  box->ray->near_x;
    next_y =  box->ray->near_y;
    while (next_y >= 0 && next_y <= box->ray->game_h && next_x >= 0 && next_x <= box->ray->game_w)
    {
        if (has_wall(box, next_x, next_y))
        {
            box->ray->h_hit_x = next_x;
            box->ray->h_hit_y = next_y;
            return ;
        }
        next_x += box->ray->x_step;
        next_y += box->ray->y_step;
    }
}

void    vertical_intersection_check(t_box *box)
{
    double  next_y;
    double  next_x;
    double  rayangle;

    rayangle = box->ray->ray_angle;   
    if (rayangle < 0.5 * PI || rayangle > 1.5 * PI) // facing right
        box->ray->near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE + TILESIZE ;
    else
        box->ray->near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE - 1;
    box->ray->near_y = box->plyr->p_y + (box->ray->near_x - box->plyr->p_x) * tan(rayangle);
    if (rayangle < 0.5 * PI || rayangle > 1.5 * PI) // facing right
        box->ray->x_step = TILESIZE;
    else
        box->ray->x_step = -TILESIZE;
    box->ray->y_step = box->ray->x_step * tan(rayangle);
    next_y = box->ray->near_y;
    next_x = box->ray->near_x;
    while (next_y >= 0 && next_y <= box->ray->game_h && next_x >= 0 && next_x <= box->ray->game_w)
    {
        if (has_wall(box, next_x, next_y))
        {
            box->ray->v_hit_x = next_x;
            box->ray->v_hit_y = next_y;
            return ;
        }
        next_x += box->ray->x_step;
        next_y += box->ray->y_step;
    }
}


double  get_distance(double p1x, double p1y , double p2x, double p2y)
{
    double  fd;
    double  sd;

    fd = p1x - p2x ;
    sd = p1y - p2y ;
    return(sqrt(fd * fd + sd * sd));
}

char    get_closest_distance(t_box *box)
{
    double  v_distance;
    double  h_distance;

    v_distance = get_distance(box->plyr->p_x, box->plyr->p_y, box->ray->v_hit_x, box->ray->v_hit_y);
    h_distance = get_distance(box->plyr->p_x, box->plyr->p_y, box->ray->h_hit_x, box->ray->h_hit_y);
    if (v_distance <= h_distance)
        return ('v');
    return ('h');
}
