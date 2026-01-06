#include  "../includes/game.h"


// Helper to load one texture and get its data
void load_texture(t_game *game, t_img *tex, char *path)
{
    tex->image = mlx_xpm_file_to_image(game->engine->mlx, path, &tex->width, &tex->height);
    if (!tex->image)
        exit_error(game, "Error\nTexture load failed", 1);
    
    // THIS IS THE CRITICAL MISSING STEP:
    tex->addr = mlx_get_data_addr(tex->image, &tex->bpp, &tex->line_len, &tex->endian);
}

// Updated allocate_textures
int allocate_textures(t_game *game)
{
    load_texture(game, &game->tex->north, game->tex->no);
    load_texture(game, &game->tex->south, game->tex->so);
    load_texture(game, &game->tex->west,  game->tex->we);
    load_texture(game, &game->tex->east,  game->tex->ea);
    return (0);
}