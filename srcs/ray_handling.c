#include "../includes/cub3d.h"

void put_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
}

// DDA line drawing algorithm
void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps;
    float x_inc, y_inc;
    float x = x0;
    float y = y0;

    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    x_inc = dx / (float)steps;
    y_inc = dy / (float)steps;

    for (int i = 0; i <= steps; i++)
    {
        put_pixel(mlx_ptr, win_ptr, round(x), round(y), color);
        x += x_inc;
        y += y_inc;
    }
}


double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * PI); // remainder = angle mod 2π 
    if (angle < 0) // handle negative values
        angle += 2 * PI;
    return angle;
}
void cast_rays(t_box *box)
{
   double  angle_between_rays;
   int ray_num;

    ray_num = 60;
    angle_between_rays = box->plyr->fov / ray_num;
    box->plyr->p_angle = normalize_angle(box->plyr->p_angle);
    box->ray->ray_angle = box->plyr->p_angle - (box->plyr->fov / 2); // start of the fov
    while (ray_num > 0)
    {
        box->ray->ray_angle = normalize_angle(box->ray->ray_angle);
        horizontal_intersection_check(box);
        vertical_intersection_check(box);
        if (get_closest_distance(box) == 'v')
        {
            box->ray->x_hit = box->ray->v_hit_x;
            box->ray->y_hit = box->ray->v_hit_y;
        }
        else
        {
            box->ray->x_hit = box->ray->h_hit_x;
            box->ray->y_hit = box->ray->h_hit_y;
        }
        draw_line(box->cub->mlx, box->cub->mlx_win ,box->plyr->p_x, box->plyr->p_y, box->ray->x_hit, box->ray->y_hit, RED);
        box->ray->ray_angle += angle_between_rays ;
        ray_num--;
    }
}
/*
void    calcule_dependencies(t_box *box)
{
    box->ray->plyr_to_pp = (box->ray->game_w / 2) / tan((box->plyr->fov / 2));
    box->ray->line_height =  TILESIZE / 
}
    */


