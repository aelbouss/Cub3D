# include "../includes/game.h"


unsigned int get_pixel_color(t_img *tex, int x, int y)
{
    char *dst;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0);
    dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return (*(unsigned int *)dst);
}

void calculate_wall_dependencies(t_game *game)
{
    double dist;

    // 1. Get raw distance (Same as before)
    if (get_closest_distance(game) == 'v')
        dist = game->engine->final_dist;
    else
        dist = game->engine->final_dist;

    // 2. Fix Fish-Eye (Same as before)
    game->engine->corrected_dist = dist * cos(game->engine->ray_angle - game->player->p_angle);
    if (game->engine->corrected_dist < 0.0001) 
        game->engine->corrected_dist = 0.0001;

    // 3. Calculate Height
    game->engine->wall_height = (TILESIZE / game->engine->corrected_dist) * game->engine->dist_proj_plane;

    // 4. Calculate Draw Start/End using SCREEN_H
    //    We center the wall on the window, not the map.
    game->engine->wall_top_p = (SCREEN_H / 2) - (game->engine->wall_height / 2);
    if (game->engine->wall_top_p < 0) 
        game->engine->wall_top_p = 0;

    game->engine->wall_bottom_p = (SCREEN_H / 2) + (game->engine->wall_height / 2);
    if (game->engine->wall_bottom_p >= SCREEN_H) 
        game->engine->wall_bottom_p = SCREEN_H - 1;
}

t_img   *select_texture(t_game *game , char side)
{
       if (side == 'v')
    {
        // Check if looking Left (West)
        if (game->engine->ray_angle > PI / 2 && game->engine->ray_angle < 3 * PI / 2) // either left or  right (west or east)
            return (&game->tex->west);
        else
            return (&game->tex->east);
    }
    else
    {
        // Check if looking Up (South facing wall) vs Down (North facing wall)
        if (game->engine->ray_angle > PI && game->engine->ray_angle < 2 * PI) // check north or south (up down)
            return(&game->tex->south);
        else
            return (&game->tex->north);
    }
    return (NULL) ;
}

t_img *get_texture_info(t_game *game, int *texX)
{
    t_img   *tex;
    double  wallX;
    char    side;

    tex = NULL ;
    side = get_closest_distance(game);
    tex = select_texture(game, side);
    // 2. Calculate Wall X (where exactly we hit the wall)
    if (side == 'v')
        wallX = game->engine->v_hit_y / TILESIZE;
    else
        wallX = game->engine->h_hit_x / TILESIZE;
    wallX -= floor(wallX); 
    // 3. Calculate Texture X
    *texX = (int)(wallX * (double)tex->width);

    // 4. Flip texture if necessary
    if ((side == 'v' && game->engine->ray_angle > PI / 2 && game->engine->ray_angle < 3 * PI / 2) ||
        (side == 'h' && !(game->engine->ray_angle > PI && game->engine->ray_angle < 2 * PI)))
        *texX = tex->width - *texX - 1;
    return (tex);
}

void    put_pixel_to_img(t_img *img, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= img->width || y < 0 || y >= img->height)
        return ;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

void draw_wall_texture(t_game *game, t_img *buffer, int x)
{
    t_img   *tex;
    int     texX;
    int     y;
    double  step;
    double  texPos;

    tex = get_texture_info(game, &texX);
    step = 1.0 * tex->height / game->engine->wall_height;
    
    // Calculate initial texture position using SCREEN_H
    texPos = (game->engine->wall_top_p - ((SCREEN_H / 2) 
            - ((int)game->engine->wall_height / 2))) * step;

    y = game->engine->wall_top_p;
    while (y <= game->engine->wall_bottom_p)
    {
        int texY = (int)texPos;
        // Safe modulo/clamping
        if (texY >= tex->height) 
            texY = tex->height - 1;
        if (texY < 0) 
            texY = 0;
            
        texPos += step;
        put_pixel_to_img(buffer, x, y, get_pixel_color(tex, texX, texY));
        y++;
    }
}

void draw_column(t_game *game, t_img *buffer, int x)
{
    int y;

    // 1. Draw Ceiling
    y = 0;
    while (y < game->engine->wall_top_p)
    {
        put_pixel_to_img(buffer, x, y, game->colors->ceiling);
        y++;
    }

    // 2. Draw Wall
    draw_wall_texture(game, buffer, x);

    // 3. Draw Floor (Loop until SCREEN_H)
    y = game->engine->wall_bottom_p + 1;
    while (y < SCREEN_H)
    {
        put_pixel_to_img(buffer, x, y, game->colors->floor);
        y++;
    }
}

void cast_3d_walls(t_game *game)
{
    t_img   buffer;
    int     x;

    // 1. Init Buffer with SCREEN Dimensions
    buffer.img_ptr = mlx_new_image(game->engine->mlx, SCREEN_W, SCREEN_H);
    buffer.addr = mlx_get_data_addr(buffer.img_ptr, &buffer.bpp, &buffer.line_len, &buffer.endian);
    buffer.width = SCREEN_W;
    buffer.height = SCREEN_H;

    x = 0;
    // 2. Loop until SCREEN_W
    while (x < SCREEN_W)
    {
        // 3. Calculate Angle based on SCREEN_W
        double ray_start = game->player->p_angle - (game->player->fov / 2.0);
        
        // This step is crucial: It spreads your FOV across the WINDOW width
        double step = game->player->fov / (double)SCREEN_W; 
        
        game->engine->ray_angle = normalize_angle(ray_start + x * step);

        // 4. Cast Ray (These still use the map for collision, which is correct)
        horizontal_intersection_check(game);
        vertical_intersection_check(game);

        // 5. Calculate Physics
        calculate_wall_dependencies(game);

        // 6. Draw
        draw_column(game, &buffer, x);

        x++;
    }
    
    mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, buffer.img_ptr, 0, 0);
    mlx_destroy_image(game->engine->mlx, buffer.img_ptr);
}
