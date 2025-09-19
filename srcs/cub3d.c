#include "../includes/cub3d.h"


char	**read_map(char *file)
{
	int		fd;
	int		cnt;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cnt = 0;
	while (get_next_line(fd))
		cnt++;
	close(fd);
	map = malloc(sizeof (char *) * (cnt + 1));
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	cnt = 0;
	while (1)
	{
		map[cnt++] = get_next_line(fd);
		if (!map[cnt - 1])
			break ;
	}
	map[cnt] = NULL;
	return (map);
}

int	main(int ac, char **av)
{
	t_cub	*game;
	int		i;


	if (ac != 2)
		return (perror("invalig args\n"), 1);
	game = malloc(sizeof(t_cub));
	if (!game)
		return (perror("bad allocation"),  1);
	game->map =  read_map(av[1]);
	if (!game->map)
		return (perror("Bad Allocation") , 1);
	i = 0;
	while (game->map[i])
	{
		puts(game->map[i]);
		i++;
	}
	
	return (0);
}