#include "../../include/cub3d.h"
#include "../../include/raycasting.h"
#include "../../include/rendering.h"

void	init_texture(t_game *game, t_texture **texture, int *tex_x)
{
	*texture = get_texture(game, game->ray.texture_id);
	if (!*texture)
		return;

	*tex_x = (int)(game->ray.wall_x * (double)(*texture)->width);
	if (game->ray.side == 0 && game->ray.dir_x > 0)
		*tex_x = (*texture)->width - *tex_x - 1;
	else if (game->ray.side == 1 && game->ray.dir_y < 0)
		*tex_x = (*texture)->width - *tex_x - 1;
}

void	draw_wall_column(t_game *game, int x, int draw_start, int draw_end)
{
	t_texture *texture;

	int tex_x;
	init_texture(game, &texture, &tex_x);

	double step = 1.0 * texture->height / (draw_end - draw_start);
	double tex_pos = 0;

	int y;

	y = draw_start;
	while (y <= draw_end)
	{
		int tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;

		int color = get_texture_pixel(texture, tex_x, tex_y);

		draw_pixel(game, x, y, color);
		y++;
	}
}

void	rendering_frame(t_game *game)
{
	t_ray	ray;
	int x;

	x = 0;

	while (x < SCREEN_WIDTH)
	{
		init_ray(&ray, game, x);
		cast_ray(&ray, game);

		int line_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
		int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;

		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		draw_wall_column(game, x, draw_start, draw_end);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);
}
