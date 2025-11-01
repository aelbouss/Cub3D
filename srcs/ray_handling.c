#include "../includes/cub3d.h"

void cast_rays(t_box *box)
{
   double  angle_between_rays;
   int ray_num;
    double snx;
    double sny;

    ray_num = 60;
    angle_between_rays = box->plyr->fov / ray_num;
    box->ray->ray_angle = box->plyr->p_angle - (box->plyr->fov  / 2); // start of the fov
    while (box->ray->ray_angle < box->plyr->p_angle + (box->plyr->fov  / 2))
    {
        horizontal_intersection(box);
        snx = cos(box->ray->ray_angle) * 10 ;
        sny = sin(box->ray->ray_angle) * 10 ;
       // draw_player_direction(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x, box->plyr->p_y, snx, sny, 50 ,   RED);
        draw_ray_angle(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x, box->plyr->p_y);
        box->ray->ray_angle += angle_between_rays ;
    }
}

//find  the  horizontal intersection 

char    grap_direction(t_box *box)
{
    if ((box->ray->ray_angle > 0) && (box->ray->ray_angle < PI)) // facing  down
        return ('d');
    if (!((box->ray->ray_angle > 0) && (box->ray->ray_angle < PI))) // facing up
        return ('u');
    if ((box->ray->ray_angle < (0.5 * PI)) && (box->ray->ray_angle > (1.5 * PI))) // facing right
        return ('r');
    if (!((box->ray->ray_angle < (0.5 * PI)) && (box->ray->ray_angle > (1.5 * PI)))) //ficing  left
        return ('l');
    return ('w');
}

int has_wall(t_box *box, double x , double y)
{
    if (box->cub->map[(int)(x / TILESIZE)][(int)(y / TILESIZE)] == '1')
        return (1);
    return (0);
}

// need to complete the  horizontal intersection .
void    horizontal_intersection(t_box *box)
{
    double  ya;
    double  xa;
    // if the  player  lookin up
    if (grap_direction(box) == 'u')
        box->ray->nearest_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE -1;
    // if the  player  looking  down 
    if (grap_direction(box) == 'd')
        box->ray->nearest_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE + TILESIZE;
    // the  nearest x 
    box->ray->nearest_x = ( box->ray->nearest_y - box->plyr->p_y) / tan(box->plyr->p_angle) + box->plyr->p_x ;
    box->ray->h_i_x = box->ray->nearest_x;
    box->ray->h_i_y = box->ray->nearest_y;
    
    ya = 0;
    xa = 0;

    if (grap_direction(box) == 'u')
        ya -= TILESIZE;
    if (grap_direction(box) == 'd')
        ya = TILESIZE;
    xa = ya / tan(box->ray->ray_angle);
    // ensure  that the  ray  will  always  stays in the  screen ;
    while (box->ray->h_i_x <= box->cub->map_w && box->ray->h_i_x >= 0 && box->ray->h_i_y <= box->cub->map_h && box->ray->h_i_y >= 0)
    {
        if (has_wall(box, box->ray->h_i_x ,  box->ray->h_i_y) == 1)
        {
            box->ray->wall_hit_x = box->ray->h_i_x ;
            box->ray->wall_hit_y = box->ray->h_i_y ;
            break ;
        }
        else
        {
            box->ray->h_i_y += ya;
            box->ray->h_i_x += xa;
        }
    }
}














