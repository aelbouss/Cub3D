/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:06:56 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 17:37:18 by aelbouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ESC_KEY 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_textures
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			identifiers_count;
	int			got_no;
	int			got_so;
	int			got_we;
	int			got_ea;
}				t_textures;

typedef struct s_colors
{
	int			floor;
	int			ceiling;
	int			color_count;
	int			got_floor;
	int			got_ceiling;
}				t_colors;

typedef struct s_player
{
	int			x;
	int			y;
	char		dir; // 'N', 'S', 'E', 'W'
}				t_player;

typedef struct s_game
{
	char		**map;
	int			map_started;
	int			map_height;
	t_textures	*tex;
	t_colors	*colors;
	t_player	*player;
}				t_game;

// parse_color
int				is_number(char *str);
int				ft_arrlen(char **arr);
void			validate_color_arr(char **arr, t_game *game, char *line,
					int fd);
int				parse_color(t_game *game, char *line, char *path, int fd);

// parse_map
void			init_struct(t_game *game);
void			store_map_line(t_game *game, char *line, int fd);
void			check_allowed_characters(t_game *game, int fd);
void			validate_map(t_game *game, int fd);
void			parse_map(t_game *game, int fd);

// check_file_extension
int				ft_strcmp(char *s1, char *s2);
void			check_file_extension(t_game *game, char *filename, int fd);

// check
int				is_empty_line(char *line);
int				is_identifier(char *line);
int				is_valid_map_char(char c);
int				is_map_line(char *line);

// utils
char			*clean_line(char *line);
char			**resize_map(t_game *game, char **map, int map_height, int fd);
void			find_player_pos(t_game *gamem, int fd);
void			exit_error(t_game *game, char *msg, int fd);

// utils2
int				get_identifier_index(char *line);
void			process_texture_data(t_game *game, char *line, char *path);
void			process_color_data(t_game *game, char *line, char *path,
					int fd);
void			parse_identifier(t_game *game, char *line, int fd);

// utils3
void			check_the_borders(t_game *game, int fd);
void			check_side_borders(t_game *game, int fd);

// check_path_textures
void			check_path_textures(t_game *game);

// free_game
void			free_array(char **array);
void			free_game(t_game *game);

// flood_fill
char			**dup_map(t_game *game);
void			flood_fill(char **map, t_game *game, t_player player, int fd);

#endif
