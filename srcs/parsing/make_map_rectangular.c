# include "../includes/game.h"

int get_max_line_len(t_game *game)
{
    int i;
    int len;
    int max_len;

    i = 0;
    max_len = 0;

    while (i < game->map_height)
    {
        len = ft_strlen(game->map[i]);
        if (len > max_len)
            max_len = len;
        i++;
    }
    return (max_len);
}

void make_map_rectangular(t_game *game)
{
    int (i) , (j);
    char	*new_line;
    int  max_len;

    max_len = get_max_line_len(game);   
    game->engine->map_w = max_len * TILESIZE;
    i = 0;
    while (i < game->map_height)
    {
        int len = ft_strlen(game->map[i]);
        if (len < max_len)
        {
            new_line = malloc(sizeof(char) * (max_len + 1));
            if (!new_line)
                exit_error(game, "Error\nMalloc failed", 2);
            ft_strlcpy(new_line, game->map[i], len + 1);
            j = len;
            while (j < max_len)
                new_line[j++] = ' ';
            new_line[max_len] = '\0';
            free(game->map[i]);
            game->map[i] = new_line;
        }
        i++;
    }
}
