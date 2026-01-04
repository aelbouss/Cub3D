# include  "../includes/game.h"



void horizontal_intersection_check(t_game *box)
{
    double rayangle;

    rayangle = normalize_angle(box->ray->ray_angle);
    if (rayangle > 0 && rayangle < PI) // looking down
        box->ray->near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE + TILESIZE;
    else // looking up
        box->ray->near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE - 1; // small offset for top-left corner
    box->ray->near_x = box->plyr->p_x + (box->ray->near_y - box->plyr->p_y) / tan(rayangle);
    if (rayangle > 0 && rayangle < PI) // looking down
        box->ray->y_step = TILESIZE;
    else
        box->ray->y_step = -TILESIZE;
    box->ray->x_step = box->ray->y_step / tan(rayangle);
    box->ray->next_x = box->ray->near_x;
    box->ray->near_y = box->ray->near_y;
    while (box->ray->next_x >= 0 && box->ray->next_x <= box->ray->game_w &&
           box->ray->near_y >= 0 && box->ray->near_y <= box->ray->game_h &&
           !has_wall(box, box->ray->next_x, box->ray->near_y))
    {
        box->ray->next_x += box->ray->x_step;
        box->ray->near_y += box->ray->y_step;
    }
    box->ray->h_hit_x = box->ray->next_x;
    box->ray->h_hit_y = box->ray->near_y;
}

void vertical_intersection_check(t_game *box)
{
    double rayangle;

    rayangle = normalize_angle(box->ray->ray_angle);
    if (rayangle < 1.5 * PI && rayangle > 0.5 * PI) // looking left
        box->ray->near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE - 1; // offset for top-left corner
    else // looking right
        box->ray->near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE + TILESIZE;
    box->ray->near_y = box->plyr->p_y + (box->ray->near_x - box->plyr->p_x) * tan(rayangle);
    if (rayangle < 1.5 * PI && rayangle > 0.5 * PI) // looking left
        box->ray->x_step = -TILESIZE;
    else
        box->ray->x_step = TILESIZE;
    box->ray->y_step = box->ray->x_step * tan(rayangle);
    box->ray->next_x = box->ray->near_x;
    box->ray->next_y = box->ray->near_y;
    while (box->ray->next_x >= 0 && box->ray->next_x <= box->ray->game_w &&
           box->ray->next_y >= 0 && box->ray->next_y <= box->ray->game_h &&
           !has_wall(box, box->ray->next_x, box->ray->next_y))
    {
        box->ray->next_x += box->ray->x_step;
        box->ray->next_y += box->ray->y_step;
    }
    box->ray->v_hit_x = box->ray->next_x;
    box->ray->v_hit_y = box->ray->next_y;
}

double  get_distance(double p1x, double p1y , double p2x, double p2y)
{
    double  fd;
    double  sd;

    fd = p1x - p2x ;
    sd = p1y - p2y ;
    return(sqrt(fd * fd + sd * sd));
}
char    get_closest_distance(t_game *box)
{
    double  v_distance;
    double  h_distance;

    v_distance = get_distance(box->plyr->p_x, box->plyr->p_y, box->ray->v_hit_x, box->ray->v_hit_y);
    h_distance = get_distance(box->plyr->p_x, box->plyr->p_y, box->ray->h_hit_x, box->ray->h_hit_y);
    if (v_distance <= h_distance)
        return ('v');
    return ('h');
}