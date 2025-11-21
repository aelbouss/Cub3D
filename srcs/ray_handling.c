#include "../includes/cub3d.h"



char    lowest_distance(double x1, double y1, double x2, double y2)
{
    double dx = fabs(x2 - x1);
    double dy = fabs(y2 - y1);

    if (dx < dy)
        return 's';
    else
        return 'f';
}

void cast_rays(t_box *box, char dir)
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
        // the  snx , sny are the  vector  direction coordinates
        snx = cos(box->ray->ray_angle) * PLYRSPEED ;
        sny = sin(box->ray->ray_angle) * PLYRSPEED ;
        horizontal_intersection_check(box, dir);
        vertical_intersection_check(box, dir);
        if (lowest_distance(box->ray->h_hit_x, box->ray->h_hit_y, box->ray->v_hit_x, box->ray->v_hit_y) == 's')
               draw_line_mlx(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x, box->plyr->p_y, box->ray->v_hit_x, box->ray->v_hit_y , snx, sny , RED);
        else
             draw_line_mlx(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x, box->plyr->p_y, box->ray->h_hit_x, box->ray->h_hit_y , snx, sny , RED);
                 //cast_ray_simple(box, box->plyr->p_x, box->plyr->p_y, snx, sny, box->ray->h_hit_x , &box->ray->h_hit_y);
       // draw_player_direction(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x, box->plyr->p_y, snx, sny, 20 , RED);
        box->ray->ray_angle += angle_between_rays ;
    }
}




