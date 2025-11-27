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
        return ('l');
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
    char    dir;

    near_y = 0;
    dir = get_player_direction(box->ray->ray_angle);
    if (dir == 'u')
        near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE - 0.0001;
    if (dir == 'd')
        near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE + TILESIZE;
    
    near_x = box->plyr->p_x + (near_y - box->plyr->p_y) / tan(box->ray->ray_angle);
    if (dir == 'd')
        y_step = TILESIZE;
    if (dir == 'u')
        y_step = -TILESIZE;
    x_step = y_step / tan(box->ray->ray_angle);
    if (dir == 'r' && x_step < 0)
        x_step *= -1 ;
    if (dir == 'l' && x_step > 0)
        x_step *= -1 ;
    next_x = near_x;
    next_y = near_y;
    while (next_y >= 0 && next_y <= box->ray->game_h && next_x >= 0 && next_x <= box->ray->game_w)
    {
        if (has_wall(box, next_x, next_y))
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
    char    dir;

    dir  = get_player_direction(box->ray->ray_angle);    
    if (dir == 'r')
        near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE + TILESIZE ;
    else
        near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE - 0.0001;
    
    if (dir == 'r')
        x_step = TILESIZE;
    else
        x_step = -TILESIZE;
    near_y = box->plyr->p_y + (near_x - box->plyr->p_x) * tan(box->ray->ray_angle);
    y_step = x_step * tan(box->ray->ray_angle);
    next_y = near_y ;
    next_x = near_x ;
    while (next_y >= 0 && next_y <= box->ray->game_h && next_x >= 0 && next_x <= box->ray->game_w)
    {
        if (has_wall(box, next_x, next_y))
        {
            box->ray->v_hit_x = next_x;
            box->ray->v_hit_y = next_y;
            return ;
        }
        next_x += x_step;
        next_y += y_step;
    }
}



/*void horizontal_intersection_check(t_box *box)
{
    double ray = box->ray->ray_angle;
    double near_x, near_y;
    double x_step, y_step;

    int ray_up   = (ray > PI);
    int ray_down = !ray_up;
    int ray_right = (ray < 0.5*PI || ray > 1.5*PI);
    int ray_left  = !ray_right;

    (void)ray_left;
    (void)ray_down;
    // --- 1. Find nearest horizontal gridline ---
    if (ray_up)
        near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE - 0.0001;
    else
        near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE + TILESIZE;

    // --- 2. Find corresponding near_x ---
    near_x = box->plyr->p_x + (near_y - box->plyr->p_y) / tan(ray);

    // --- 3. Step sizes ---
    y_step = ray_up ? -TILESIZE : TILESIZE;
    x_step = y_step / tan(ray);

    // --- 4. Loop ---
    double next_x = near_x;
    double next_y = near_y;

    while (next_x >= 0 && next_x <= box->ray->game_w &&
           next_y >= 0 && next_y <= box->ray->game_h)
    {
        if (has_wall(box, next_x, next_y))
        {
            box->ray->h_hit_x = next_x;
            box->ray->h_hit_y = next_y;
            return;
        }
        next_x += x_step;
        next_y += y_step;
    }
}*/

/*void vertical_intersection_check(t_box *box)
{
    double ray = box->ray->ray_angle;
    double near_x, near_y;
    double x_step, y_step;

    int ray_up   = (ray > PI);
    int ray_down = !ray_up;
    int ray_right = (ray < 0.5*PI || ray > 1.5*PI);
    int ray_left  = !ray_right;

    
    (void)ray_left;
    (void)ray_down;
    // --- 1. Find nearest vertical gridline ---
    if (ray_right)
        near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE + TILESIZE;
    else
        near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE - 0.0001;

    // --- 2. Find corresponding near_y ---
    near_y = box->plyr->p_y + (near_x - box->plyr->p_x) * tan(ray);

    // --- 3. Step sizes ---
    x_step = ray_right ? TILESIZE : -TILESIZE;
    y_step = x_step * tan(ray);

    // --- 4. Loop ---
    double next_x = near_x;
    double next_y = near_y;

    while (next_x >= 0 && next_x <= box->ray->game_w &&
           next_y >= 0 && next_y <= box->ray->game_h)
    {
        if (has_wall(box, next_x, next_y))
        {
            box->ray->v_hit_x = next_x;
            box->ray->v_hit_y = next_y;
            return;
        }
        next_x += x_step;
        next_y += y_step;
    }

}*/


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
