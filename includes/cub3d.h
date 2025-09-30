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
	void	*player;
	void	*wall;
	void	*floor;

}	t_img;

typedef	struct s_box
{
	t_game	*cub;
	t_img	*img;
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
int		draw_sprites(t_box *box);
void	extract_map_width_hight(t_box *box);

# endif