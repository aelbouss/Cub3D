#include  "../includes/game.h"


void load_texture(t_game *game, t_img *tex, char *path)
{
    tex->image = mlx_xpm_file_to_image(game->engine->mlx, path, &tex->width, &tex->height);
    if (!tex->image)
    {
        ft_putstr_fd("Error\nTexture load failed\n", 2);
        clean_game(game);
		exit(1);
    }
    tex->addr = mlx_get_data_addr(tex->image, &tex->bpp, &tex->line_len, &tex->endian);
}

void    allocate_img(t_game *game, t_img *img)
{
    img->image =  mlx_new_image(game->engine->mlx, game->engine->map_w, game->engine->map_h);
    if (!img->image)
    {
        ft_putstr_fd("Error\n Image Allocation Failed\n", 2);
        clean_game(game);
		exit(1);   
    }
    img->addr = mlx_get_data_addr(img->image, &img->bpp, &img->line_len, &img->endian);
    if (!img->addr)
    {
        ft_putstr_fd("Error\n Failed to get image data\n", 2);
        mlx_destroy_image(game->engine->mlx, img->image);
        clean_game(game);
		exit(1);  
    }
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
