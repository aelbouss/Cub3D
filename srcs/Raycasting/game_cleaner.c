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
}