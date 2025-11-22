#include "../includes/cub3d.h"

void get_player_direction(double p_angle)
{
    // Normalize angle to 0 ~ 2*PI
    while (p_angle < 0)
        p_angle += 2 * PI;
    while (p_angle >= 2 * PI)
        p_angle -= 2 * PI;

    if ((p_angle >= 7*PI/4) || (p_angle < PI/4))
        printf("Moving Right\n");
    else if (p_angle >= PI/4 && p_angle < 3*PI/4)
        printf("Moving Up\n");
    else if (p_angle >= 3*PI/4 && p_angle < 5*PI/4)
        printf("Moving Left\n");
    else
        printf("Moving Down\n");
}

/*void    horizontal_intersection_check(t_box *box , char dir)
{
    double  next_y;
    double  next_x;
    double  near_x;
    double  near_y;

    if (dir == 'u')
        near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE - 1;
    if (dir == 'd')
        near_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE + TILESIZE ;
    near_x =  (near_y - box->plyr->p_y) / tan(box->ray->ray_angle) + box->plyr->p_x ;

    next_y = near_y ;
    next_x = near_x ;

    while (next_y >= 0 && next_y <= box->ray->game_h && next_x >= 0 && next_x <= box->ray->game_w)
    {
        if (has_wall(box, next_x, next_y) == 1)
        {
            box->ray->h_hit_x = next_x;
            box->ray->h_hit_y = next_y;
            return ;
        }
        if (dir == 'u')
            next_y -= TILESIZE ;
        if (dir  == 'd')
            next_y += TILESIZE ;
        next_x = next_y / tan(box->ray->ray_angle); 
    }
}

void    vertical_intersection_check(t_box *box, char dir)
{
    double  next_y;
    double  next_x;
    double  near_x;
    double  near_y;

    if (dir  == 'r')
        near_x = floor(box->plyr->p_x / TILESIZE) * TILESIZE +TILESIZE ;
    if (dir == 'l')
        near_x = floor(box->plyr->p_x / TILESIZE) - 1 ;
    near_y = box->plyr->p_y + (box->plyr->p_x - near_x) * tan(box->ray->ray_angle);

    next_y = near_y ;
    next_x = near_x ;

     while (next_y >= 0 && next_y <= box->ray->game_h && next_x >= 0 && next_x <= box->ray->game_w)
     {
        if (has_wall(box, next_x, next_y) == 1)
        {
            box->ray->v_hit_x = next_x;
            box->ray->v_hit_x = next_y;
            return ;
        }
        if (dir == 'r')
            next_x += TILESIZE ;
        if (dir == 'l')
            next_x -= TILESIZE ;
        next_y = near_x  * tan(box->ray->ray_angle);
     }
}*/

