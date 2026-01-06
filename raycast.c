/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:02:34 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	check_path_textures(t_game *game)
{
	char	*paths[4];
	int		i;
	int		len;
	int		fd;

	paths[0] = game->tex->no;
	paths[1] = game->tex->so;
	paths[2] = game->tex->we;
	paths[3] = game->tex->ea;
	i = 0;
	while (i < 4)
	{
		if (!paths[i])
			exit_error(game, "Error\nMissing texture", fd);
		if (ft_strlen(paths[i]) < 4)
			exit_error(game, "Error\nInvalid texture path", fd);
		len = ft_strlen(paths[i]);
		if (len < 4 || ft_strcmp((paths[i] + len) - 4, ".xpm") != 0)
			exit_error(game, "Error\nInvalid texture extension", fd);
		fd = open(paths[i], O_RDONLY);
		if (fd == -1)
			exit_error(game, "Error\nTexture file not found or unreadable", fd);
		close(fd);
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_extension.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:01:15 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	check_file_extension(t_game *game, char *filename, int fd)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
		exit_error(game, "Error\nInvalid file extension. Must be .cub", fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:02:34 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	check_path_textures(t_game *game)
{
	char	*paths[4];
	int		i;
	int		len;
	int		fd;

	paths[0] = game->tex->no;
	paths[1] = game->tex->so;
	paths[2] = game->tex->we;
	paths[3] = game->tex->ea;
	i = 0;
	while (i < 4)
	{
		if (!paths[i])
			exit_error(game, "Error\nMissing texture", fd);
		if (ft_strlen(paths[i]) < 4)
			exit_error(game, "Error\nInvalid texture path", fd);
		len = ft_strlen(paths[i]);
		if (len < 4 || ft_strcmp((paths[i] + len) - 4, ".xpm") != 0)
			exit_error(game, "Error\nInvalid texture extension", fd);
		fd = open(paths[i], O_RDONLY);
		if (fd == -1)
			exit_error(game, "Error\nTexture file not found or unreadable", fd);
		close(fd);
		i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:02:46 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	is_identifier(char *line)
{
	if (!line)
		return (0);
	while (*line == ' ')
		line++;
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	if (!ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "WE ", 3))
		return (1);
	if (!ft_strncmp(line, "EA ", 3))
		return (1);
	if (!ft_strncmp(line, "F ", 2))
		return (1);
	if (!ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W')
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
		{
			i++;
			continue ;
		}
		if (!is_valid_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 01:02:27 by string            #+#    #+#             */
/*   Updated: 2026/01/04 01:30:29 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

char	**dup_map(t_game *game)
{
	char	**dest;
	int		i;

	dest = malloc(sizeof(char *) * (game->map_height + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < game->map_height)
	{
		dest[i] = ft_strdup(game->map[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
void flood_fill(char **map, t_game *game, int x, int y, int fd)
{
    if (y < 0 || y >= game->map_height || x < 0 || x >= (int)ft_strlen(map[y]))
    {
        free_array(map);
        exit_error(game, "Error\nMap is open", fd);
    }
    if (map[y][x] == '1' || map[y][x] == 'F')
        return ;
    if (map[y][x] == ' ')
    {
        free_array(map);
        exit_error(game, "Error\nMap is open", fd);
    }
    map[y][x] = 'F';
    flood_fill(map, game, x + 1, y, fd);
    flood_fill(map, game, x - 1, y, fd);
    flood_fill(map, game, x, y + 1, fd);
    flood_fill(map, game, x, y - 1, fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:03:51 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_game(t_game *game)
{
	int	i;

	if (game->tex->no)
		free(game->tex->no);
	if (game->tex->so)
		free(game->tex->so);
	if (game->tex->we)
		free(game->tex->we);
	if (game->tex->ea)
		free(game->tex->ea);
	if (game->map)
	{
		i = 0;
		while (i < game->map_height && game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
		game->map = NULL;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:04:18 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0); // empty string is not a number
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

void	validate_color_arr(char **arr, t_game *game, char *line, int fd)
{
	int	i;

	i = 0;
	if (!arr || ft_arrlen(arr) != 3)
	{
		free_array(arr);
		free(line);
		exit_error(game, "Error\nInvalid color format", fd);
	}
	while (i < 3)
	{
		if (!is_number(arr[i]))
		{
			free_array(arr);
			free(line);
			exit_error(game, "Error\nInvalid color", fd);
		}
		i++;
	}
}

int	parse_color(t_game *game, char *line, char *path, int fd)
{
	char	**arr;
	char	*clean;
	int		r;
	int		g;
	int		b;

	clean = clean_line(path);
	arr = ft_split(clean, ',');
	free(clean);
	validate_color_arr(arr, game, line, fd);
	r = ft_atoi(arr[0]);
	g = ft_atoi(arr[1]);
	b = ft_atoi(arr[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_array(arr);
		free(line);
		exit_error(game, "Error\nColor out of range", fd);
	}
	free_array(arr);
	return ((r << 16) | (g << 8) | b);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:35:50 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/04 01:38:45 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	check_allowed_characters(t_game *game, int fd)
{
	int (i), (j);
	i = 0;
	if (!game->map)
		exit_error(game, "Error\nEmpty Map", fd);
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_map_char(game->map[i][j]) && game->map[i][j] != '\n')
				exit_error(game, "Error\nInvalid character in map", fd);
			j++;
		}
		i++;
	}
}

void	store_map_line(t_game *game, char *line, int fd)
{
	char	*cleaned_line;

	game->map_started = 1;
	cleaned_line = clean_line(line);
	game->map = resize_map(game, game->map, game->map_height, fd);
	// add the space for new line
	game->map[game->map_height] = cleaned_line;
	// game->map_height(index)
	game->map_height++;
}

void	init_struct(t_game *game)
{
	game->map = NULL;
	game->tex->identifiers_count = 0;
	game->colors->color_count = 0;
	game->tex->got_no = 0;
	game->tex->got_so = 0;
	game->tex->got_we = 0;
	game->tex->got_ea = 0;
	game->colors->got_floor = 0;
	game->colors->got_ceiling = 0;
	game->map_started = 0;
}

void	validate_map(t_game *game, int fd)
{
	if (game->tex->identifiers_count != 4 || game->colors->color_count != 2)
		exit_error(game, "Error\nInvalid number of identifiers", fd);
	check_path_textures(game);
	check_allowed_characters(game, fd);
	check_the_borders(game, fd);
	check_side_borders(game, fd);
	find_player_pos(game, fd);
}

void	parse_map(t_game *game, int fd)
{
	char	*line;

	init_struct(game);
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line) && !game->map_started)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_empty_line(line) && game->map_started)
			(free(line), exit_error(game, "Error\nVoid after map start", fd));
		if (!game->map_started && is_identifier(line))
			parse_identifier(game, line, fd);
		else if (is_map_line(line))
			store_map_line(game, line, fd);
		else
			(free(line), exit_error(game, "Error\nInvalid line", fd));
		free(line);
		line = get_next_line(fd);
	}
	validate_map(game, fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:05:30 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/04 15:57:01 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

char	*clean_line(char *line)
{
	int		i;
	char	*new;

	new = malloc(ft_strlen(line) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**resize_map(t_game *game, char **map, int map_height, int fd)
		// make space for the new line + NULL
{
	char	**tmp;
	// 1 new line (We reserved the line) + 1 NULL
	tmp = realloc(map, sizeof(char *) * (map_height + 2));
	if (!tmp)
		exit_error(game, "Error\nMemory allocation failed", fd);
	tmp[map_height + 1] = NULL;
		// tmp[map_height] → this is where we store the new line so+ 1 for the NULL
	return (tmp);
}

void	find_player_pos(t_game *game, int fd)
{
	int (i), (j), (player_found);
	player_found = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				if (player_found)
					exit_error(game, "Error\nMultiple players!", fd);
				game->player->x = (double)j * TILESIZE + (TILESIZE / 2.0) ;
				game->player->y = (double)i * TILESIZE + (TILESIZE / 2.0) ;
				game->player->dir = game->map[i][j];
				player_found = 1;
			}
			j++;
		}
		i++;
	}
	if (!player_found)
		exit_error(game, "Error\nNo player found!", fd);
}

void	exit_error(t_game *game, char *msg, int fd)
{
	char	*tmp;

	ft_putendl_fd(msg, 2);
	free_game(game);
	tmp = get_next_line(fd);	
	while (tmp) // clean rest of the file
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	exit(1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:08:59 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	get_identifier_index(char *line)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (2);
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

void	process_texture_data(t_game *game, char *line, char *path)
{
	if (!ft_strncmp(line, "NO", 2) && !game->tex->got_no)
	{
		game->tex->identifiers_count++;
		game->tex->got_no++;
		game->tex->no = clean_line(path);
	}
	else if (!ft_strncmp(line, "SO", 2) && !game->tex->got_so)
	{
		game->tex->identifiers_count++;
		game->tex->got_so++;
		game->tex->so = clean_line(path);
	}
	else if (!ft_strncmp(line, "WE", 2) && !game->tex->got_we)
	{
		game->tex->identifiers_count++;
		game->tex->got_we++;
		game->tex->we = clean_line(path);
	}
	else if (!ft_strncmp(line, "EA", 2) && !game->tex->got_ea)
	{
		game->tex->identifiers_count++;
		game->tex->got_ea++;
		game->tex->ea = clean_line(path);
	}
}

void	process_color_data(t_game *game, char *line, char *path, int fd)
{
	if (!ft_strncmp(line, "F", 1) && !game->colors->got_floor)
	{
		game->colors->color_count++;
		game->colors->got_floor++;
		game->colors->floor = parse_color(game, line, path, fd);
	}
	else if (!ft_strncmp(line, "C", 1) && !game->colors->got_ceiling)
	{
		game->colors->color_count++;
		game->colors->got_ceiling++;
		game->colors->ceiling = parse_color(game, line, path, fd);
	}
}

void	parse_identifier(t_game *game, char *line, int fd)
{
	int		i;
	char	*path;

	while (*line == ' ')
		line++;
	i = get_identifier_index(line);
	while (line[i] == ' ')
		i++;
	path = line + i;
	process_texture_data(game, line, path);
	process_color_data(game, line, path, fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:09:10 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:47 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	check_the_borders(t_game *game, int fd)
{
	int	j;

	// Check top row
	j = 0;
	while (game->map[0][j])
	{
		if (game->map[0][j] != '1')
			exit_error(game, "Error\nInvalid top border in map", fd);
		j++;
	}
	// Check bottom row
	j = 0;
	while (game->map[game->map_height - 1][j])
	{
		if (game->map[game->map_height - 1][j] != '1')
			exit_error(game, "Error\nInvalid bottom border in map", fd);
		j++;
	}
}

void	check_side_borders(t_game *game, int fd)
{
	int	i;
	int	last_index;

	i = 1;                           // skip first row
	while (i < game->map_height - 1) // skip last row
	{
		last_index = ft_strlen(game->map[i]) - 1;
		if (game->map[i][0] != '1' || game->map[i][last_index] != '1')
			exit_error(game, "Error\nInvalid side borders in map", fd);
		i++;
	}
}
# include "../includes/game.h"

t_game	*build_base()
{
	t_game	*game;

	game = malloc(1 * sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Bad Allocation", STDERR_FILENO) , NULL);
	game->colors = malloc(1 * sizeof(t_colors));
	if (!game->colors)
	return (free(game),ft_putstr_fd("Bad Allocation", STDERR_FILENO), NULL);
	game->tex = malloc(1 * sizeof(t_textures));
	if (!game->tex)
		return (free(game->colors), free(game), NULL);
	game->player = malloc(1 * sizeof(t_player));
	if (!game->player)
		return (free(game->colors), free(game->tex) ,free(game)
			,ft_putstr_fd("Bad Allocation", STDERR_FILENO), NULL);
	game->engine = malloc(1 * sizeof(t_raycasting));
	if (!game->engine)
	{
		free(game->colors);
		free(game->player);
		free(game->tex);
		return (free(game), ft_putstr_fd("Bad Allocation",2), NULL);
	}
	return (game);
}

void	destroy_game(t_game *game) // will free all the allocations
{
		free (game->tex);
		game->tex = NULL;
		free (game->player);
		game->player = NULL;
		free (game->colors);
		game->colors = NULL;
		free (game->engine);
		game->engine = NULL;
		free (game);
		game = NULL;
}

void	initialize_game_utils(t_game *game)
{
	game->map = NULL;
    game->map_height = 0;
    game->map_started = 0;
    game->tex->no = NULL;
    game->tex->so = NULL;
    game->tex->we = NULL;
    game->tex->ea = NULL;
    game->colors->floor = -1;
    game->colors->ceiling = -1;
	game->player->move_up = 0;
	game->player->move_down = 0;
	game->player->move_left = 0;
	game->player->move_right = 0;
	game->player->rotate_left = 0;
	game->player->rotate_right = 0;	
	
}

void	setup_engine(t_game *game)
{
	game->engine->mlx = mlx_init();
	if (!game->engine->mlx)
		return (destroy_game(game),ft_putstr_fd("unable connecting to the server", 2));
	game->engine->map_h = game->map_height * TILESIZE;
	game->engine->map_w = ft_strlen(game->map[0]) * TILESIZE;
	game->player->fov = 60 * (PI / 180);
	game->engine->dist_proj_plane = (game->engine->map_w / 2) / tan(game->player->fov / 2.0);
	game->engine->mlx_win = mlx_new_window(game->engine->mlx, game->engine->map_w , game->engine->map_h , "cub3d");
	if (!game->engine->mlx_win)
		return (destroy_game2(game),ft_putstr_fd("unable to open mlx window", 2));
	set_player_angle(game);
	allocate_textures(game);

}
# include "../includes/game.h"



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

// void cast_rays(t_game *game)
// {
//    double  angle_between_rays;
//    int ray_num;

//     ray_num = 60;
//     angle_between_rays = game->player->fov / ray_num;
//     game->player->p_angle = normalize_angle(game->player->p_angle);
//     game->engine->ray_angle = game->player->p_angle - (game->player->fov / 2); // start of the fov
//     while (ray_num > 0)
//     {
//         game->engine->ray_angle = normalize_angle(game->engine->ray_angle);
//         horizontal_intersection_check(game);
//         vertical_intersection_check(game);
//         if (get_closest_distance(game) == 'v')
//             draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->v_hit_x, game->engine->v_hit_y, RED);
//         else
//             draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->h_hit_x, game->engine->h_hit_y, RED);
//         game->engine->ray_angle += angle_between_rays ;
//         game->engine->h_hit_x = 0;
//         game->engine->h_hit_y = 0;
//         game->engine->v_hit_x = 0;
//         game->engine->v_hit_y = 0;
//         ray_num--;
//     }
// }


void draw_vertical_line(t_game *game, int x, int y0, int y1, int color)
{
    for (int y = y0; y <= y1; y++)
    {
        put_pixel(game->engine->mlx, game->engine->mlx_win, x, y, color);
    }
}

void cast_3d_walls(t_game *game)
{
    int win_w = game->engine->map_w;
    int win_h = game->engine->map_h;
    int ray_num = win_w; // One ray per screen column for proper rendering
    double angle_between_rays = game->player->fov / (double)ray_num;
    double ray_angle_start = game->player->p_angle - (game->player->fov / 2.0);

    // Create image buffer
    void *img = mlx_new_image(game->engine->mlx, win_w, win_h);
    int bpp, size_line, endian;
    char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

    // Helper to set pixel in buffer
    #define PUT_IMG_PIXEL(x, y, color) \
        if ((x) >= 0 && (x) < win_w && (y) >= 0 && (y) < win_h) { \
            int offset = (y) * size_line + (x) * (bpp / 8); \
            *(unsigned int *)(data + offset) = (color); \
        }

    for (int x = 0; x < win_w; x++)
    {
        double ray_angle = normalize_angle(ray_angle_start + x * angle_between_rays);
        game->engine->ray_angle = ray_angle;

        horizontal_intersection_check(game);
        vertical_intersection_check(game);

        double dist;
        if (get_closest_distance(game) == 'v')
            dist = hypot(game->engine->v_hit_x - game->player->x, game->engine->v_hit_y - game->player->y);
        else
            dist = hypot(game->engine->h_hit_x - game->player->x, game->engine->h_hit_y - game->player->y);
        // Remove fish-eye effect
        double corrected_dist = dist * cos(ray_angle - game->player->p_angle);

        if (corrected_dist < 0.0001)
            corrected_dist = 0.0001;

        int wall_height = (int)((TILESIZE / corrected_dist) * game->engine->dist_proj_plane);

        if (wall_height > win_h * 2)
            wall_height = win_h * 2;

        int wall_top_pixel = (win_h / 2) - (wall_height / 2);
        if (wall_top_pixel < 0)
            wall_top_pixel = 0;

        int wall_bottom_pixel = (win_h / 2) + (wall_height / 2);
        if (wall_bottom_pixel >= win_h)
            wall_bottom_pixel = win_h - 1;

        // Draw ceiling
        for (int y = 0; y < wall_top_pixel; y++)
            PUT_IMG_PIXEL(x, y, 0x222222);

        // Draw wall
        for (int y = wall_top_pixel; y <= wall_bottom_pixel; y++)
            PUT_IMG_PIXEL(x, y, BLUE);

        // Draw floor
        for (int y = wall_bottom_pixel + 1; y < win_h; y++)
            PUT_IMG_PIXEL(x, y, 0x444444);
    }

    // Display the image buffer to the window
    mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, img, 0, 0);

    // Destroy image to avoid memory leaks
    mlx_destroy_image(game->engine->mlx, img);

    #undef PUT_IMG_PIXEL
}

# include "../includes/game.h"


void	destroy_game1(t_game *game) // will free all the allocations
{
		free (game->tex);
		game->tex = NULL;
		free (game->player);
		game->player = NULL;
		free (game->colors);
		game->colors = NULL;
		free (game->engine);
		game->engine = NULL;
		free (game);
		game = NULL;
}

void	destroy_game2(t_game *game)
{
		free (game->tex);
		game->tex = NULL;
		free (game->player);
		game->player = NULL;
		free (game->colors);
		game->colors = NULL;
		free(game->engine->mlx);
		game->engine->mlx = NULL;
		free (game->engine);
		game->engine = NULL;
		free (game);
		game = NULL;
}

void	destroy_game3(t_game *game)
{
		free(game->tex->no);
		free(game->tex->ea);
		free (game->tex);
		game->tex = NULL;
		free (game->player);
		game->player = NULL;
		free (game->colors);
		game->colors = NULL;
		free(game->engine->mlx);
		game->engine->mlx = NULL;
		free (game->engine);
		game->engine = NULL;
		free (game);
		game = NULL;
}# include  "../includes/game.h"



void horizontal_intersection_check(t_game *game)
{
    double rayangle;

    rayangle = normalize_angle(game->engine->ray_angle);
    if (rayangle > 0 && rayangle < PI) // looking down
        game->engine->near_y = floor(game->player->y / TILESIZE) * TILESIZE + TILESIZE;
    else // looking up
        game->engine->near_y = floor(game->player->y / TILESIZE) * TILESIZE - 1; // small offset for top-left corner
    game->engine->near_x = game->player->x + (game->engine->near_y - game->player->y ) / tan(rayangle);
    if (rayangle > 0 && rayangle < PI) // looking down
        game->engine->y_step = TILESIZE;
    else
        game->engine->y_step = -TILESIZE;
    game->engine->x_step = game->engine->y_step / tan(rayangle);
    game->engine->next_x = game->engine->near_x;
    game->engine->near_y = game->engine->near_y;
    while (game->engine->next_x >= 0 && game->engine->next_x <= game->engine->map_w &&
           game->engine->near_y >= 0 && game->engine->near_y <= game->engine->map_h &&
           !has_wall(game->engine->next_x, game->engine->near_y, game))
    {
        game->engine->next_x += game->engine->x_step;
        game->engine->near_y += game->engine->y_step;
    }
    game->engine->h_hit_x = game->engine->next_x;
    game->engine->h_hit_y = game->engine->near_y;
}

void vertical_intersection_check(t_game *game)
{
    double rayangle;

    rayangle = normalize_angle(game->engine->ray_angle);
    if (rayangle < 1.5 * PI && rayangle > 0.5 * PI) // looking left
        game->engine->near_x = floor(game->player->x / TILESIZE) * TILESIZE - 1; // offset for top-left corner
    else // looking right
        game->engine->near_x = floor(game->player->x / TILESIZE) * TILESIZE + TILESIZE;
    game->engine->near_y = game->player->y + (game->engine->near_x - game->player->x) * tan(rayangle);
    if (rayangle < 1.5 * PI && rayangle > 0.5 * PI) // looking left
       game->engine->x_step = -TILESIZE;
    else
       game->engine->x_step = TILESIZE;
    game->engine->y_step = game->engine->x_step * tan(rayangle);
    game->engine->next_x = game->engine->near_x;
    game->engine->next_y = game->engine->near_y;
    while (game->engine->next_x >= 0 && game->engine->next_x <= game->engine->map_w &&
           game->engine->next_y >= 0 && game->engine->next_y <= game->engine->map_h &&
           !has_wall(game->engine->next_x, game->engine->next_y, game))
    {
        game->engine->next_x += game->engine->x_step;
        game->engine->next_y += game->engine->y_step;
    }
    game->engine->v_hit_x = game->engine->next_x;
    game->engine->v_hit_y = game->engine->next_y;
}

// void cast_rays(t_game *game)
// {
//    double  angle_between_rays;
//    int ray_num;

//     ray_num = 60;
//     angle_between_rays = game->player->fov / ray_num;
//     game->player->p_angle = normalize_angle(game->player->p_angle);
//     game->engine->ray_angle = game->player->p_angle - (game->player->fov / 2); // start of the fov
//     while (ray_num > 0)
//     {
//         game->engine->ray_angle = normalize_angle(game->engine->ray_angle);
//         horizontal_intersection_check(game);
//         vertical_intersection_check(game);
//         if (get_closest_distance(game) == 'v')
//             draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->v_hit_x, game->engine->v_hit_y, RED);
//         else
//             draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->h_hit_x, game->engine->h_hit_y, RED);
//         game->engine->ray_angle += angle_between_rays ;
//         game->engine->h_hit_x = 0;
//         game->engine->h_hit_y = 0;
//         game->engine->v_hit_x = 0;
//         game->engine->v_hit_y = 0;
//         ray_num--;
//     }
// }

double  get_distance(double p1x, double p1y , double p2x, double p2y)
{
    double  fd;
    double  sd;

    fd = p1x - p2x ;
    sd = p1y - p2y ;
    return(sqrt(fd * fd + sd * sd));
}
char    get_closest_distance(t_game *game)
{
    double  v_distance;
    double  h_distance;

    v_distance = get_distance(game->player->x, game->player->y, game->engine->v_hit_x, game->engine->v_hit_y);
    h_distance = get_distance(game->player->x, game->player->y, game->engine->h_hit_x, game->engine->h_hit_y);
    if (v_distance <= h_distance)
    {
        game->engine->final_dist = v_distance;
        return ('v');
    }
    game->engine->final_dist = h_distance;
    return ('h');
}# include "../includes/game.h"


int	is_pressed(int keycode, t_game *game)
{
	if (keycode == z)
		game->player->move_up = 1;
	else if (keycode == s)
		game->player->move_down = 1;
	else if (keycode == q)
		game->player->move_left = 1;
	else if (keycode == d)
		game->player->move_right = 1;
	else if (keycode == LEFT)
		game->player->rotate_left = 1;
	else if (keycode == RIGHT)
		game->player->rotate_right = 1;
	else if (keycode == ESC_KEY)
		exit(1);
	else if (keycode == 80679312)
	{
		mlx_destroy_window(game->engine->mlx, game->engine->mlx_win);
		exit(0);
	}
	return (0);
}

int	is_released(int keycode, t_game *game)
{
	if (keycode == z)
		game->player->move_up = 0;
	else if (keycode == s)
		game->player->move_down = 0;
	else if (keycode == q)
		game->player->move_left = 0;
	else if (keycode == d)
		game->player->move_right = 0;
	else if (keycode == LEFT)
		game->player->rotate_left = 0;
	else if (keycode == RIGHT)
		game->player->rotate_right = 0;
	return (0);
}

// This function should be called every frame for smooth input handling
int	handle_input(t_game *game)
{

	if (game->player->rotate_left == 1)
        rotate_left(game);
    if (game->player->rotate_right == 1)
        rotate_right(game);
    if (game->player->move_up == 1)
        walk_forward(game);
    if (game->player->move_down == 1)
        walk_backward(game);
    if (game->player->move_left == 1)
        walk_left(game);
    if (game->player->move_right == 1)
        walk_right(game);
    cast_3d_walls(game);
	return (0);
}
# include "../includes/game.h"

void	set_player_angle(t_game *game)
{
	int	h;
	int	w;

	if (game->player->dir == 'S')
		game->player->p_angle = PI / 2 ;
	if (game->player->dir == 'N')
		game->player->p_angle = 3 * PI / 2;
	if (game->player->dir == 'E')
		game->player->p_angle = 0;
	if (game->player->dir == 'W')
		game->player->p_angle = PI;
	h = 0;
	while (game->map[h])
	{
		w = 0;
		while (game->map[h][w])
		{
			if (game->map[h][w] == 'S' || game->map[h][w] == 'N' || game->map[h][w] == 'E' || game->map[h][w] == 'W')
			{
				game->map[h][w] = '0';
				return ;
			}
			w++;
		}
		h++;
	}
}

int	has_wall(double x , double y , t_game *game)
{
	if (game ->map[(int)y / TILESIZE][(int)x / TILESIZE] == '1')
		return (1);
	return (0);
}


void	walk_forward(t_game *game)
{
	double	px;
	double	py;

	px = game->player->x + cos(game->player->p_angle) * PLAYERSPEED;
	py = game->player->y + sin(game->player->p_angle) * PLAYERSPEED;

	if (!has_wall(px, game->player->y, game))
		game->player->x = px;
	if (!has_wall(game->player->y, px, game))
		game->player->y = py;
}

void	walk_backward(t_game *game)
{
	double	px;
	double	py;

	px = game->player->x - cos(game->player->p_angle) * PLAYERSPEED;
	py = game->player->y - sin(game->player->p_angle) * PLAYERSPEED;

	if (!has_wall(px, game->player->y, game))
		game->player->x = px;
	if (!has_wall(game->player->y, px, game))
		game->player->y = py;
}

void	walk_left(t_game *game)
{
	double	px;
	double	py;

	px = game->player->x + sin(game->player->p_angle) * PLAYERSPEED;
	py = game->player->y - cos(game->player->p_angle) * PLAYERSPEED;

	if (!has_wall(px, game->player->y, game))
		game->player->x = px;
	if (!has_wall(game->player->y, px, game))
		game->player->y = py;
}

void	walk_right(t_game *game)
{
	double	px;
	double	py;

	// Move perpendicular to the player's angle (right/strafe)
	px = game->player->x - sin(game->player->p_angle) * PLAYERSPEED;
	py = game->player->y + cos(game->player->p_angle) * PLAYERSPEED;

	if (!has_wall(px, game->player->y, game))
		game->player->x = px;
	if (!has_wall(game->player->y, px, game))
		game->player->y = py;
}

double normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	rotate_left(t_game *game)
{
	game->player->p_angle -= 0.1;
	game->player->p_angle = normalize_angle(game->player->p_angle);
}

void	rotate_right(t_game *game)
{
	game->player->p_angle += 0.1;
	game->player->p_angle = normalize_angle(game->player->p_angle);
}

void	draw_player (t_game *game)
{
	int	y;
	int	x;

	y = 0;

	while (y < 10 )
	{
		x = 0; 
		while (x < 10)
		{
			mlx_pixel_put(game->engine->mlx, game->engine->mlx_win, game->player->x + x, game->player->y + y, RED);
			x++;
		}
		y++;
	}
}#include  "../includes/game.h"

int	allocate_textures(t_game *game)
{
	int	height;
	int	width;

	game->tex->wold2d = mlx_new_image(game->engine->mlx, game->engine->map_w, game->engine->map_h);
	if (!game->tex->wold2d)
		return (ft_putstr_fd("Bad image" , 2), 1);
	game->tex->south = mlx_xpm_file_to_image(game->engine->mlx, game->tex->so , &height, &width);
	if (!game->tex->south)
		return (ft_putstr_fd("Bad image" , 2), 1);
	game->tex->north = mlx_xpm_file_to_image(game->engine->mlx, game->tex->no, &height, &width);
	if (!game->tex->north)
		return (ft_putstr_fd("Bad image" , 2), 1);
	game->tex->east = mlx_xpm_file_to_image(game->engine->mlx, game->tex->ea, &height, &width);
	if (!game->tex->east)
		return (ft_putstr_fd("Bad image" , 2), 1);
	game->tex->west = mlx_xpm_file_to_image(game->engine->mlx, game->tex->we, &height, &width);
	if (!game->tex->we)
		return (ft_putstr_fd("Bad image" , 2), 1);
	return (0);
}

void	generate_2d_world(t_game *game)
{
	int h;
	int	w;

	h = 0;
	while (game->map[h])
	{
		w = 0;
		while (game->map[h][w])
		{
			if (game->map[h][w] == '1')
				mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, game->tex->west, w * TILESIZE , h * TILESIZE);
			if (game->map[h][w] == '0')
				mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, game->tex->north, w * TILESIZE , h * TILESIZE);
			if (game->map[h][w] == 'N' || game->map[h][w] == 'S' || game->map[h][w] == 'E' || game->map[h][w] == 'W')
				mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, game->tex->east, w * TILESIZE , h * TILESIZE);
			w++;
		}
		h++;
	}
}

