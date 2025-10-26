#include "../includes/cub3d.h"

void cast_rays(t_box *box)
{
   double  angle_between_rays;
   int ray_num;
    double snx;
    double sny;
    double lnx;
    double lny;
    double  boundary_s;
    double  boundary_l;

    ray_num = 60;
    draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                box->plyr->p_x, box->plyr->p_y,
                box->plyr->pdx, box->plyr->pdy,
                50, BLUE);
    angle_between_rays = box->plyr->fov / ray_num;  
    boundary_s = box->plyr->p_angle - (box->plyr->fov  / 2);
    snx = cos(boundary_s);
    sny = sin(boundary_s);
    boundary_l = box->plyr->p_angle + (box->plyr->fov   / 2);
    lnx = cos(boundary_l);
    lny = sin(boundary_l);
    draw_player_direction(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x, box->plyr->p_y, snx, sny, 50 ,   RED);
    draw_player_direction(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x, box->plyr->p_y, lnx, lny, 50 ,   RED);
    while (boundary_s < boundary_l)
    {
        snx = cos(boundary_s) * 10 ;
        sny = sin(boundary_s) * 10 ;
        draw_player_direction(box->cub->mlx, box->cub->mlx_win, box->plyr->p_x, box->plyr->p_y, snx, sny, 50 ,   RED);
        boundary_s += angle_between_rays ;
    }
}















