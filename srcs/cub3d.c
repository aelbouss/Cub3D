#include "../includes/cub3d.h"


int	main(int ac, char **av)
{
	t_box	*box;

	if (ac != 2)
		return (perror("Error : Invalid Arguments\n"), 1);
	box = setup_environement(av[1]);
	if (!box)
		return (1);
	if (build_dependencies(box) != 0)
		return (1);
	draw_sprites(box);
	mlx_loop(box->cub->mlx);
	return (0);
}