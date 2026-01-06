# include "../includes/game.h"



void put_pixel(void *mlx_ptr, void *win_ptr, int x, int y, int color)
{
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
}

// DDA line drawing algorithm
void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps;
    float x_inc, y_inc;
    float x = x0;
    float y = y0;

    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    x_inc = dx / (float)steps;
    y_inc = dy / (float)steps;

    for (int i = 0; i <= steps; i++)
    {
        put_pixel(mlx_ptr, win_ptr, round(x), round(y), color);
        x += x_inc;
        y += y_inc;
    }
}

// void cast_rays(t_game *game)
// {
//    double  angle_between_rays;
//    int ray_num;

//     ray_num = 60;
//     angle_between_rays = game->player->fov / ray_num;
//     game->player->p_angle = normalize_angle(game->player->p_angle);
//     game->engine->ray_angle = game->player->p_angle - (game->player->fov / 2); // start of the fov
//     while (ray_num > 0)
//     {
//         game->engine->ray_angle = normalize_angle(game->engine->ray_angle);
//         horizontal_intersection_check(game);
//         vertical_intersection_check(game);
//         if (get_closest_distance(game) == 'v')
//             draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->v_hit_x, game->engine->v_hit_y, RED);
//         else
//             draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->h_hit_x, game->engine->h_hit_y, RED);
//         game->engine->ray_angle += angle_between_rays ;
//         game->engine->h_hit_x = 0;
//         game->engine->h_hit_y = 0;
//         game->engine->v_hit_x = 0;
//         game->engine->v_hit_y = 0;
//         ray_num--;
//     }
// }


void draw_vertical_line(t_game *game, int x, int y0, int y1, int color)
{
    for (int y = y0; y <= y1; y++)
    {
        put_pixel(game->engine->mlx, game->engine->mlx_win, x, y, color);
    }
}
unsigned int get_pixel_color(t_img *tex, int x, int y)
{
    char *dst;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0); // Safety check
    dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return (*(unsigned int *)dst);
}

// void cast_3d_walls(t_game *game)
// {
//     int win_w = game->engine->map_w;
//     int win_h = game->engine->map_h;
//     int ray_num = win_w; // One ray per screen column for proper rendering
//     double angle_between_rays = game->player->fov / (double)ray_num;
//     double ray_angle_start = game->player->p_angle - (game->player->fov / 2.0);

//     // Create image buffer
//     void *img = mlx_new_image(game->engine->mlx, win_w, win_h);
//     int bpp, size_line, endian;
//     char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

//     // Helper to set pixel in buffer
//     #define PUT_IMG_PIXEL(x, y, color) 
//         if ((x) >= 0 && (x) < win_w && (y) >= 0 && (y) < win_h) { 
//             int offset = (y) * size_line + (x) * (bpp / 8); 
//             *(unsigned int *)(data + offset) = (color); 
//         }

//     for (int x = 0; x < win_w; x++)
//     {
//         double ray_angle = normalize_angle(ray_angle_start + x * angle_between_rays);
//         game->engine->ray_angle = ray_angle;

//         horizontal_intersection_check(game);
//         vertical_intersection_check(game);

//         double dist;
//         if (get_closest_distance(game) == 'v')
//             dist = hypot(game->engine->v_hit_x - game->player->x, game->engine->v_hit_y - game->player->y);
//         else
//             dist = hypot(game->engine->h_hit_x - game->player->x, game->engine->h_hit_y - game->player->y);
//         // Remove fish-eye effect
//         double corrected_dist = dist * cos(ray_angle - game->player->p_angle);

//         if (corrected_dist < 0.0001)
//             corrected_dist = 0.0001;

//         int wall_height = (int)((TILESIZE / corrected_dist) * game->engine->dist_proj_plane);

//         if (wall_height > win_h * 2)
//             wall_height = win_h * 2;

//         int wall_top_pixel = (win_h / 2) - (wall_height / 2);
//         if (wall_top_pixel < 0)
//             wall_top_pixel = 0;

//         int wall_bottom_pixel = (win_h / 2) + (wall_height / 2);
//         if (wall_bottom_pixel >= win_h)
//             wall_bottom_pixel = win_h - 1;

//         // Draw ceiling
//         for (int y = 0; y < wall_top_pixel; y++)
//             PUT_IMG_PIXEL(x, y, 0x222222);

//         // Draw wall
//         for (int y = wall_top_pixel; y <= wall_bottom_pixel; y++)
//             PUT_IMG_PIXEL(x, y, BLUE);

//         // Draw floor
//         for (int y = wall_bottom_pixel + 1; y < win_h; y++)
//             PUT_IMG_PIXEL(x, y, 0x444444);
    
    
// // Helper to get color from a texture at (x, y)


// // Inside cast_3d_walls loop...
// // After calculating corrected_dist, wall_height, etc.

//     // 1. Determine which texture to use
//     t_img *current_tex;
//     // double ray_angle = normalize_angle(game->engine->ray_angle);
//     char side = get_closest_distance(game); // 'v' or 'h'

//     if (side == 'v')
//     {
//         // If ray is looking Left (PI/2 to 3PI/2), we hit East face
//         if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2)
//             current_tex = &game->tex->east;
//         else
//             current_tex = &game->tex->west;
//     }
//     else
//     {
//         // If ray is looking Up (PI to 2PI), we hit South face
//         if (ray_angle > PI && ray_angle < 2 * PI)
//             current_tex = &game->tex->south;
//         else
//             current_tex = &game->tex->north;
//     }

//     // 2. Calculate Hit Position (wallX)
//     // This is the specific decimal coordinate (0.0 to 1.0) where the wall was hit
//     double wallX;
//     if (side == 'v')
//         wallX = game->engine->v_hit_y / TILESIZE;
//     else
//         wallX = game->engine->h_hit_x / TILESIZE;
    
//     wallX -= floor(wallX); // Keep only the decimal part

//     // 3. Calculate Texture X coordinate
//     int texX = (int)(wallX * (double)current_tex->width);

//     // Flip texture if necessary (so it doesn't look mirrored)
//     if ((side == 'v' && ray_angle > PI / 2 && ray_angle < 3 * PI / 2) ||
//         (side == 'h' && !(ray_angle > PI && ray_angle < 2 * PI)))
//     {
//         texX = current_tex->width - texX - 1;
//     }

//     // 4. Drawing Loop
//     double step = 1.0 * current_tex->height / wall_height;
//     double texPos = (wall_top_pixel - win_h / 2 + wall_height / 2) * step;

//     for (int y = wall_top_pixel; y <= wall_bottom_pixel; y++)
//     {
//         int texY = (int)texPos;
//         // Prevent texture overflow
//         if (texY >= current_tex->height) texY = current_tex->height - 1;
//         if (texY < 0) texY = 0;

//         texPos += step;

//         unsigned int color = get_pixel_color(current_tex, texX, texY);
        
//         // Use your macro or pixel put function
//         PUT_IMG_PIXEL(x, y, color); 
//     }

// }

//     // Display the image buffer to the window
//     mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, img, 0, 0);

//     // Destroy image to avoid memory leaks
//     mlx_destroy_image(game->engine->mlx, img);

//     #undef PUT_IMG_PIXEL
// }


void cast_3d_walls(t_game *game)
{
    int win_w = game->engine->map_w;
    int win_h = game->engine->map_h;
    
    // Create image buffer
    void *img = mlx_new_image(game->engine->mlx, win_w, win_h);
    int bpp, size_line, endian;
    char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

    // Helper macro to set pixel in buffer (faster than function call)
    #define PUT_IMG_PIXEL(x, y, color) \
        if ((x) >= 0 && (x) < win_w && (y) >= 0 && (y) < win_h) { \
            int offset = (y) * size_line + (x) * (bpp / 8); \
            *(unsigned int *)(data + offset) = (color); \
        }

    // Raycasting Loop
    for (int x = 0; x < win_w; x++)
    {
        // 1. Calculate Ray Angle
        double ray_angle_start = game->player->p_angle - (game->player->fov / 2.0);
        double angle_between_rays = game->player->fov / (double)win_w;
        double ray_angle = normalize_angle(ray_angle_start + x * angle_between_rays);
        
        game->engine->ray_angle = ray_angle;

        // 2. Run DDA
        horizontal_intersection_check(game);
        vertical_intersection_check(game);

        // 3. Calculate Wall Distances
        char side = get_closest_distance(game); // 'v' or 'h'
        double dist = game->engine->final_dist; // Assuming this was set by get_closest_distance

        // Remove fish-eye effect
        double corrected_dist = dist * cos(ray_angle - game->player->p_angle);
        if (corrected_dist < 0.0001) corrected_dist = 0.0001;

        // 4. Calculate Wall Height
        int wall_height = (int)((TILESIZE / corrected_dist) * game->engine->dist_proj_plane);
        
        int wall_top_pixel = (win_h / 2) - (wall_height / 2);
        if (wall_top_pixel < 0) wall_top_pixel = 0;

        int wall_bottom_pixel = (win_h / 2) + (wall_height / 2);
        if (wall_bottom_pixel >= win_h) wall_bottom_pixel = win_h - 1;

        // 5. DRAW CEILING (from 0 to wall_top)
        for (int y = 0; y < wall_top_pixel; y++)
            PUT_IMG_PIXEL(x, y, game->colors->ceiling);

        // 6. DRAW WALL (Textured)
        
        // A. Identify which texture to use
        t_img *current_tex;
        if (side == 'v')
        {
            if (ray_angle > PI / 2 && ray_angle < 3 * PI / 2) // Looking Left -> West Wall
                current_tex = &game->tex->west;
            else
                current_tex = &game->tex->east;
        }
        else
        {
            if (ray_angle > PI && ray_angle < 2 * PI) // Looking Up -> South Wall
                current_tex = &game->tex->south; // (North/South flip depends on your coordinate system)
            else
                current_tex = &game->tex->north;
        }

        // B. Calculate X coordinate on the texture
        double wallX;
        if (side == 'v')
            wallX = game->engine->v_hit_y / TILESIZE;
        else
            wallX = game->engine->h_hit_x / TILESIZE;
        wallX -= floor(wallX); 

        int texX = (int)(wallX * (double)current_tex->width);

        // Flip texture if necessary
        if ((side == 'v' && ray_angle > PI / 2 && ray_angle < 3 * PI / 2) ||
            (side == 'h' && !(ray_angle > PI && ray_angle < 2 * PI)))
            texX = current_tex->width - texX - 1;

        // C. Draw the vertical strip
        double step = 1.0 * current_tex->height / wall_height;
        double texPos = (wall_top_pixel - win_h / 2 + wall_height / 2) * step;

        for (int y = wall_top_pixel; y <= wall_bottom_pixel; y++)
        {
            int texY = (int)texPos;
            if (texY >= current_tex->height) texY = current_tex->height - 1;
            if (texY < 0) texY = 0;
            
            texPos += step;
            
            unsigned int color = get_pixel_color(current_tex, texX, texY);
            PUT_IMG_PIXEL(x, y, color);
        }

        // 7. DRAW FLOOR (from wall_bottom to screen height)
        for (int y = wall_bottom_pixel + 1; y < win_h; y++)
            PUT_IMG_PIXEL(x, y, game->colors->floor);
    }

    mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, img, 0, 0);
    mlx_destroy_image(game->engine->mlx, img);
    #undef PUT_IMG_PIXEL
}