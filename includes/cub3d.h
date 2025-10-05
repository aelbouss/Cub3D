# ifndef CUB3D_H
# define CUB3D_H

// headers
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <mlx.h>


//macros  section
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

// initerfaces

// macros section 

# define	TILESIZE 64
# define	POV	60
# define	RES 4
# define RED 0xFF0000

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
	int	p_x;
	int	p_y;
	int	fov;
	int pos;
	int	dir;
}	t_player;

typedef	struct s_box
{
	t_game	*cub;
	t_img	*img;
	t_player	*plyr;
}	t_box;

// prototypes section
size_t	ft_strlen(char *str);
int		loking_for_newline(const char *str);
char	*elicit_line(char *str);
char	*get_next_line(int fd);
char	*copy_remaining(char *str, int i);
char	*get_remaining(char *str);
char	**read_map(char *file);
t_box	*setup_environement(char *mapfile);
int		build_dependencies(t_box *box);
int		allocate_sprites(t_box *box);
void	extract_map_width_hight(t_box *box);
void	draw_player (t_box *box);
int	push_pixels_to_image(t_box *box, void *image, int color);
void	put_pixel_to_image(char *img_data, int x, int y, int color, int bpp, int size_line);
void	fill_2d_world(t_box *box);

# endif