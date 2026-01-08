# include "../includes/game.h"


void	destroy_game1(t_game *game)
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

void	clean_textures_paths(t_game *game)
{
	if (game->tex->so)
	{
		free(game->tex->so);
		game->tex->so = NULL;	
	}
	if (game->tex->no)
	{
		free(game->tex->no);
		game->tex->no = NULL;
	}
	if (game->tex->we)
	{
		free(game->tex->we);
		game->tex->we = NULL;
	}
	if (game->tex->ea)
	{
		free(game->tex->ea);
		game->tex->ea = NULL ;
	}
}

void	free_textures(t_game *game)
{
	free(game->tex->no);
	free(game->tex->so);
	free(game->tex->we);
	free(game->tex->ea);

	if (game->tex->north.image)
		mlx_destroy_image(game->engine->mlx, game->tex->north.image);

	if (game->tex->south.image)
		mlx_destroy_image(game->engine->mlx, game->tex->south.image);
	if (game->tex->east.image)
		mlx_destroy_image(game->engine->mlx, game->tex->east.image);

	if (game->tex->west.image)
		mlx_destroy_image (game->engine->mlx, game->tex->west.image);
}


void	free_map(char **m)
{
	int	y;

	y = 0;
	if (!m)
		return ;
	while (m[y])
	{
		if (m[y])
		{
			free (m[y]);
			m[y] = NULL;
		}
		y++;
	}
	free(m);
	m = NULL;
	
}
void	clean_game(t_game *game)
{
	free_map(game->map);
	free_textures(game);
	if (game->engine->mlx_win)
		mlx_destroy_window(game->engine->mlx, game->engine->mlx_win);
	mlx_destroy_display(game->engine->mlx);
	free(game->engine->mlx);
	free(game->tex);
	free(game->colors);
	free(game->player);
	free(game->engine);
	free(game);

}