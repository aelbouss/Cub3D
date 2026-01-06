/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbouss <aelbouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:06:56 by rmaanane          #+#    #+#             */
/*   Updated: 2026/01/03 20:53:06 by aelbouss         ###   ########.fr       */
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
# include <math.h>

# define ESC_KEY 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363

# define s 115
# define z 119
# define q 97
# define d 100
# define TILESIZE 64
# define PLAYERSPEED 3
# define WALL_H 64
# define PI 3.141592653589793
# define RED 0xFF0000
# define YEL 0xd3e90f
# define BLUE 0X0000FF

# define SCREEN_H 720
# define SCREEN_W 1248




typedef struct s_img 
{
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
	void	*image;
} t_img;

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


	t_img		north;
	t_img		south;
	t_img		east;
	t_img		west;

	int			floor;
	int			ceiling;
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
	double			x;
	double			y;
	char			dir; // 'N', 'S', 'E', 'W'
	double			p_angle;
	double			fov;
	int				move_up;
	int				move_down;
	int				move_left;
	int				move_right;
	int				rotate_left;
	int				rotate_right;
	
}				t_player;

typedef	struct s_raycasting
{
	void	*mlx;
	void	*mlx_win;
	int		map_h;
	int		map_w;
	double	ray_angle;
    double	h_hit_x;
	double	h_hit_y;
	double	v_hit_x;
	double	v_hit_y;
	double	x_step;
	double	y_step;
	double	next_x;
	double	next_y;
	double	near_x;
	double	near_y;
	double	dist_proj_plane;
	double	wall_height;
	double	corrected_dist;
	double	final_dist;
	int     cur_x;
	int		wall_bottom_p;
	int		wall_top_p;
	t_img	world_3d;
	
}		t_raycasting;

typedef struct s_game
{
	char		**map;
	int			map_started;
	int			map_height;
	int			map_width;
	t_textures	*tex;
	t_colors	*colors;
	t_player	*player;
	t_raycasting	*engine;
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
void 			flood_fill(char **map, t_game *game, int x, int y, int fd);

// raycasting prototypes

t_game			*build_base();
void			destroy_game1(t_game *game);

void			destroy_game2(t_game *game);
void			initialize_game_utils(t_game *game);

void			generate_2d_world(t_game *game);
void			setup_engine(t_game *game);

int				allocate_textures(t_game *game);
void			set_player_angle(t_game *game);

double			normalize_angle(double angle);
int				has_wall(double x , double y , t_game *game);

void			put_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color);
void			draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color);

void			horizontal_intersection_check(t_game *game);
void			vertical_intersection_check(t_game *game);

 double			get_distance(double p1x, double p1y , double p2x, double p2y);
char			get_closest_distance(t_game *game);

void			cast_rays(t_game *game);
int				handle_input(t_game *game);

void			walk_forward(t_game *game);
void			walk_backward(t_game *game);

void			walk_left(t_game *game);
void			walk_right(t_game *game);

void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

void			draw_player (t_game *game);
char			get_closest_distance(t_game *game);

void 			draw_vertical_line(t_game *game, int x, int start_y, int end_y, int color);
void			put_pixel_to_buffer(char *buffer, int size_line, int bpp, int x, int y, int color);
// void			cast_3d_walls(t_game *game);
int				is_released(int keycode, t_game *game);
int				is_pressed(int keycode, t_game *game);

void			draw_textured_wall(t_game *game);
void			cast_3d_walls(t_game *game);
unsigned int    get_pixel_color(t_img *tex, int x, int y);


void load_texture(t_game *game, t_img *tex, char *path);

void    allocate_img(t_game *game, t_img *img);
void    draw_celling(t_game *game, t_img *img, int x , int y, int color);
void	calculate_wall_dependencies(t_game *game);


#endif
