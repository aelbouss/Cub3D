# ifndef CUB3D_H
# define CUB3D_H

// headers
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
#include  <math.h>
# include <mlx.h>


//macros  section
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

// initerfaces

// macros section 

# define TILESIZE 64
# define PLYRSIZE 5
# define PLYRSPEED 10
# define POV	60
# define RES 4
# define RED 0xFF0000
# define YEL 0xd3e90f
# define BLUE 0X0000FF
# define PI  3.141592653589793
# define WF 119 
# define WB 115
# define WL 97
# define WR 100
# define RL 65361
# define RR 65363
# define RES 4

typedef	struct s_game
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
	int		map_h;
	int		map_w;
}	t_game;

typedef	struct s_img
{
	int	bpp;
	int	size_line;
	int	endian;
	char	*img_data;
	void	*wold2d;
}	t_img;

typedef	struct s_player
{
	double	p_x;
	double	p_y;
	double	pdx;
	double	pdy;
	double	p_angle ;
	double	walking_dir;
	double	turn_dir;
	double	angle_ret;
	double	fov;
	int pos;
	int	dir;

}	t_player;

typedef	struct s_raycasting
{
	int	fov;
	int	rays_num;
	double	ray_angle;
	double	game_w;
	double	game_h;
	double	h_hit_x;
	double	h_hit_y;
	double	v_hit_x;
	double	v_hit_y;

}	t_raycasting;

typedef	struct s_box
{
	t_game	*cub;
	t_img	*img;
	t_player	*plyr;
	t_raycasting	*ray;
}	t_box;




// prototypes section
size_t	ft_strlen(char *str);
int	loking_for_newline(const char *str);
char	*elicit_line(char *str);
char	*get_next_line(int fd);
char	*copy_remaining(char *str, int i);
char	*get_remaining(char *str);
char	**read_map(char *file);
t_box	*setup_environement(char *mapfile);
int	build_dependencies(t_box *box);
int	allocate_sprites(t_box *box);
void	extract_map_width_hight(t_box *box);
void	draw_player (t_box *box);
void	put_pixel_to_image(char *img_data, int x, int y, int color, int bpp, int size_line);
void	fill_2d_world(t_box *box);
int	push_pixels_to_image(t_box *box, void *image, int color, int y, int x);
int	draw_2d_world(t_box *box);
int	key_handler (int keycode, t_box *box);
void draw_player_direction(void *mlx_ptr, void *win_ptr, 
                           int player_x, int player_y, 
                           double dir_x, double dir_y, 
                           int length, int color);
void	adjust_player_direction(t_box *box, int keycode);

int	walk_forward(t_box *box);
int	walk_backward(t_box *box);
int	walk_left(t_box *box);
int	walk_right(t_box *box);
int	retate_right(t_box *box);
int	retate_left(t_box *box);
double	adjust_angle(double angle);
char    grap_direction(t_box *box);
int		has_wall(t_box *box, double x , double y);
void    draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color);
void    horizontal_intersection_check(t_box *box , char dir);
void    vertical_intersection_check(t_box *box, char dir);
int cast_ray_simple(t_box *box,
                    double start_x, double start_y,
                    double dx, double dy,
                    double *hit_x, double *hit_y);
char lowest_distance(double p_x, double p_y, 
                     double h_hit_x, double h_hit_y, 
                     double v_hit_x, double v_hit_y);
void draw_line_mlx(void *mlx_ptr, void *win_ptr,
                   double x0, double y0,
                   double hit_x, double hit_y,
                   double dir_x, double dir_y,
                   int color);
void cast_rays(t_box *box);
# endif