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

// prototypes section
size_t	ft_strlen(char *str);
int		loking_for_newline(const char *str);
char	*elicit_line(char *str);
char	*get_next_line(int fd);
char	*copy_remaining(char *str, int i);
char	*get_remaining(char *str);
char	**read_map(char *file);

// initerfaces

typedef	struct s_cub
{
	char	**map;
	void	*mlx;
	void	*mlx_win;
}	t_cub;

typedef	struct s_sprites
{
	void	*player;
	void	*wall;
	void	*collectible;
	void	*exit;

}t_sprites;

# endif