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

void cast_rays(t_game *game)
{
   double  angle_between_rays;
   int ray_num;

    ray_num = 60;
    angle_between_rays = game->player->fov / ray_num;
    game->player->p_angle = normalize_angle(game->player->p_angle);
    game->engine->ray_angle = game->player->p_angle - (game->player->fov / 2); // start of the fov
    while (ray_num > 0)
    {
        game->engine->ray_angle = normalize_angle(game->engine->ray_angle);
        horizontal_intersection_check(game);
        vertical_intersection_check(game);
        if (get_closest_distance(game) == 'v')
            draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->v_hit_x, game->engine->v_hit_y, RED);
        else
            draw_line(game->engine->mlx, game->engine->mlx_win ,game->player->x, game->player->y, game->engine->h_hit_x, game->engine->h_hit_y, RED);
        game->engine->ray_angle += angle_between_rays ;
        game->engine->h_hit_x = 0;
        game->engine->h_hit_y = 0;
        game->engine->v_hit_x = 0;
        game->engine->v_hit_y = 0;
        ray_num--;
    }
}

void draw_vertical_line(t_game *game, int x, int y0, int y1, int color)
{
    for (int y = y0; y <= y1; y++)
    {
        put_pixel(game->engine->mlx, game->engine->mlx_win, x, y, color);
    }
}

void cast_3d_walls(t_game *game)
{
    int win_w = game->engine->map_w;
    int win_h = game->engine->map_h;
    int ray_num = win_w; // One ray per screen column for proper rendering
    double angle_between_rays = game->player->fov / (double)ray_num;
    double ray_angle_start = game->player->p_angle - (game->player->fov / 2.0);

    // Create image buffer
    void *img = mlx_new_image(game->engine->mlx, win_w, win_h);
    int bpp, size_line, endian;
    char *data = mlx_get_data_addr(img, &bpp, &size_line, &endian);

    // Helper to set pixel in buffer
    #define PUT_IMG_PIXEL(x, y, color) \
        if ((x) >= 0 && (x) < win_w && (y) >= 0 && (y) < win_h) { \
            int offset = (y) * size_line + (x) * (bpp / 8); \
            *(unsigned int *)(data + offset) = (color); \
        }

    for (int x = 0; x < win_w; x++)
    {
        double ray_angle = normalize_angle(ray_angle_start + x * angle_between_rays);
        game->engine->ray_angle = ray_angle;

        horizontal_intersection_check(game);
        vertical_intersection_check(game);

        double dist;
        if (get_closest_distance(game) == 'v')
            dist = hypot(game->engine->v_hit_x - game->player->x, game->engine->v_hit_y - game->player->y);
        else
            dist = hypot(game->engine->h_hit_x - game->player->x, game->engine->h_hit_y - game->player->y);

        // Remove fish-eye effect
        double corrected_dist = dist * cos(ray_angle - game->player->p_angle);

        if (corrected_dist < 0.0001)
            corrected_dist = 0.0001;

        int wall_height = (int)((TILESIZE / corrected_dist) * game->engine->dist_proj_plane);

        if (wall_height > win_h * 2)
            wall_height = win_h * 2;

        int wall_top_pixel = (win_h / 2) - (wall_height / 2);
        if (wall_top_pixel < 0)
            wall_top_pixel = 0;

        int wall_bottom_pixel = (win_h / 2) + (wall_height / 2);
        if (wall_bottom_pixel >= win_h)
            wall_bottom_pixel = win_h - 1;

        // Draw ceiling
        for (int y = 0; y < wall_top_pixel; y++)
            PUT_IMG_PIXEL(x, y, 0x222222);

        // Draw wall
        for (int y = wall_top_pixel; y <= wall_bottom_pixel; y++)
            PUT_IMG_PIXEL(x, y, BLUE);

        // Draw floor
        for (int y = wall_bottom_pixel + 1; y < win_h; y++)
            PUT_IMG_PIXEL(x, y, 0x444444);
    }

    // Display the image buffer to the window
    mlx_put_image_to_window(game->engine->mlx, game->engine->mlx_win, img, 0, 0);

    // Destroy image to avoid memory leaks
    mlx_destroy_image(game->engine->mlx, img);

    #undef PUT_IMG_PIXEL
}


