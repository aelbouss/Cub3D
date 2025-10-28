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

// find  the  horizontal intersection 

char    grap_direction(t_box *box)
{
    if ((box->ray->rayagnle > 0) && (box->ray->rayagnle < PI)) // facing  down
        return ('d');
    if (!((box->ray->rayagnle > 0) && (box->ray->rayagnle < PI))) // facing up
        return ('u');
    if ((box->ray->rayagnle < (0.5 * PI)) && (box->ray->rayagnle > (1.5 * PI))) // facing right
        return ('r');
    if (!((box->ray->rayagnle < (0.5 * PI)) && (box->ray->rayagnle > (1.5 * PI)))) //ficing  left
        return ('l');
}


// need to complete the  horizontal intersection .
void    horizontal_intersection(t_box *box)
{
    // if the  player  lookin up
    if (grap_direction(box) == 'u')
        box->ray->nearset_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE -1;
    // if the  player  looking  down 
    if (grap_direction(box) == 'd')
        box->ray->nearest_y = floor(box->plyr->p_y / TILESIZE) * TILESIZE + TILESIZE;
    // the  nearest x 
    box->ray->nearest_x = ( box->ray->nearest_y - box->plyr->p_y) / tan(box->plyr->player-angle) + box->plyr->p_x ;
    box->ray->h_i_x = box->ray->nearest_x;
    box->ray->h_i_y = box->ray->nearest_y;
}














