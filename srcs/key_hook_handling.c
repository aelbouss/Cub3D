#include  "../includes/cub3d.h"



int	walk_forward(t_box *box)
{
	double	px;
	double	py;

	px = box->plyr->p_x + cos(box->plyr->p_angle) * PLYRSPEED;
	py = box->plyr->p_y + sin(box->plyr->p_angle) * PLYRSPEED;
	if (has_wall(box, px, py))
		return (1);
	box->plyr->p_x += cos(box->plyr->p_angle) * PLYRSPEED;
	box->plyr->p_y += sin(box->plyr->p_angle) * PLYRSPEED;
	draw_2d_world(box);
	draw_player(box);
	cast_rays(box);
	return (0);
}

int	walk_backward(t_box *box)
{
	double	px;
	double	py;

	px = box->plyr->p_x - cos(box->plyr->p_angle) * PLYRSPEED;
	py = box->plyr->p_y - sin(box->plyr->p_angle) * PLYRSPEED;
	if (has_wall(box, px, py))
		return (1);
	box->plyr->p_x -= cos(box->plyr->p_angle) * PLYRSPEED;
	box->plyr->p_y -= sin(box->plyr->p_angle) * PLYRSPEED;
	draw_2d_world(box);
	draw_player(box);
	cast_rays(box);
	return (0);
}



int	walk_left(t_box *box)
{
	double	px;
	double	py;

	px = box->plyr->p_x + cos(box->plyr->p_angle) * PLYRSPEED;
	py = box->plyr->p_y - sin(box->plyr->p_angle) * PLYRSPEED;
	if (has_wall(box, px, py))
		return (1);
	box->plyr->p_x += sin(box->plyr->p_angle) * PLYRSPEED;
	box->plyr->p_y -= cos(box->plyr->p_angle) * PLYRSPEED;
	draw_2d_world(box);
	draw_player(box);
	cast_rays(box);
	return (0);
}

int	walk_right(t_box *box)
{
	double	px;
	double	py;

	px = box->plyr->p_x - cos(box->plyr->p_angle) * PLYRSPEED;
	py = box->plyr->p_y + sin(box->plyr->p_angle) * PLYRSPEED;
	if (has_wall(box, px, py))
		return (1);
	box->plyr->p_x -= sin(box->plyr->p_angle) * PLYRSPEED;
	box->plyr->p_y += cos(box->plyr->p_angle) * PLYRSPEED;
	draw_2d_world(box);
	draw_player(box);
	cast_rays(box);
	return (0);
}

int	retate_right(t_box *box)
{
	box->plyr->p_angle += 0.1;
	box->plyr->p_angle = normalize_angle(box->plyr->p_angle);
    draw_2d_world(box);
    draw_player(box);
	cast_rays(box);
	return (0);
}

int	retate_left(t_box *box)
{
	box->plyr->p_angle -= 0.1;
	box->plyr->p_angle = normalize_angle(box->plyr->p_angle);
   	draw_2d_world(box);
   	draw_player(box);
	cast_rays(box);
	return (0);
}
