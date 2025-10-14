#include  "../includes/cub3d.h"



int	walk_forward(t_box *box)
{
	box->plyr->p_x += cos(box->plyr->p_angle) * 10;
	box->plyr->p_y += sin(box->plyr->p_angle) * 10;
	draw_2d_world(box);
	draw_player(box);
	/*draw_player_direction(box->cub->mlx, box->cub->mlx_win,
        	box->plyr->p_x, box->plyr->p_y,
                        box->plyr->pdx, box->plyr->pdy,
			50, BLUE);*/
	cast_rays(box);
	return (0);
}

int	walk_backward(t_box *box)
{
	box->plyr->p_x -= cos(box->plyr->p_angle) * 10;
	box->plyr->p_y -= sin(box->plyr->p_angle) * 10;
	draw_2d_world(box);
	draw_player(box);
	/*draw_player_direction(box->cub->mlx, box->cub->mlx_win,
		box->plyr->p_x, box->plyr->p_y,
		box->plyr->pdx, box->plyr->pdy,
		50, BLUE);*/
	cast_rays(box);
	return (0);
}



int	walk_left(t_box *box)
{
	box->plyr->p_x -= 10 ;
	draw_2d_world(box);
	draw_player(box);
	draw_player_direction(box->cub->mlx, box->cub->mlx_win,
		box->plyr->p_x, box->plyr->p_y,
		box->plyr->pdx, box->plyr->pdy,
		50, BLUE);
	cast_rays(box);
	return (0);
}

int	walk_right(t_box *box)
{
	box->plyr->p_x += 10 ;
	draw_2d_world(box);
	draw_player(box);
	draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                box->plyr->p_x, box->plyr->p_y,
                box->plyr->pdx, box->plyr->pdy,
                50, BLUE);
	cast_rays(box);
	return (0);
}

int	retate_right(t_box *box)
{
	box->plyr->p_angle += 0.3;
	if (box->plyr->p_angle > 2 * PI)
        	box->plyr->p_angle -= 2 * PI;
    // Update direction vector every time angle changes
    box->plyr->pdx = cos(box->plyr->p_angle) * 10;
    box->plyr->pdy = sin(box->plyr->p_angle) * 10;

    draw_2d_world(box);
    draw_player(box);
    draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE);
	cast_rays(box);
	return (0);
}

int	retate_left(t_box *box)
{
	 box->plyr->p_angle -= 0.3;
   	 if (box->plyr->p_angle < 0)
        box->plyr->p_angle += 2 * PI;

    // Update direction vector every time angle changes
    	box->plyr->pdx = cos(box->plyr->p_angle) * 10;
    	box->plyr->pdy = sin(box->plyr->p_angle) * 10;

   	 draw_2d_world(box);
   	 draw_player(box);
    	draw_player_direction(box->cub->mlx, box->cub->mlx_win,
                          box->plyr->p_x, box->plyr->p_y,
                          box->plyr->pdx, box->plyr->pdy,
                          50, BLUE); // longer line for visibility
	cast_rays(box);
	return (0);
}
