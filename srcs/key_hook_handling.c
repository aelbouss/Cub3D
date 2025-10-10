#include  "../includes/cub3d.h"

void	adjust_player_direction(t_box *box, int keycode)
{
	box->plyr->turn_dir = 0;
	box->plyr->walking_dir = 0;
	box->plyr->angle_ret = 0;
	if (keycode == 100) // right
		box->plyr->turn_dir = 1;
	if (keycode == 97) // left
		box->plyr->turn_dir = -1;
	if (keycode == 65362)
		box->plyr->walking_dir = 1;
	if (keycode == 65364)
		box->plyr->walking_dir = -1;
	box->plyr->angle_ret += box->plyr->turn_dir * 10;
	box->plyr->p_x += cos(box->plyr->angle_ret) * PLYRSIZE;
	box->plyr->p_y += sin(box->plyr->angle_ret) * PLYRSIZE;
}