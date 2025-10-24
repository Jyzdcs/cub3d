#include "../../include/cub3d.h"
#include "../../include/raycasting.h"
#include "../../include/rendering.h"

void	init_texture(t_game *game, t_texture **texture, int *tex_x)
{
	*texture = get_texture(game, game->ray.texture_id);
	if (!*texture)
		return ;
	*tex_x = (int)(game->ray.wall_x * (double)(*texture)->width);
	if (game->ray.side == 0 && game->ray.dir_x > 0)
		*tex_x = (*texture)->width - *tex_x - 1;
	else if (game->ray.side == 1 && game->ray.dir_y < 0)
		*tex_x = (*texture)->width - *tex_x - 1;
}

void	init_wall_column(t_wall_column *wall, t_texture *texture,
				int draw_start, int draw_end)
{
	wall->step = 1.0 * texture->height
		/ (draw_end - draw_start);
	wall->draw_start = draw_start;
	wall->draw_end = draw_end;
	wall->tex_pos = 0;
	wall->tex_y = 0;
	wall->color = 0;
	wall->y = draw_start;
}

void	draw_wall_column(t_game *game, int x, int draw_start, int draw_end)
{
	t_wall_column	wall;
	t_texture		*texture;

	init_texture(game, &texture, &wall.tex_x);
	init_wall_column(&wall, texture, draw_start, draw_end);
	while (wall.y <= draw_end)
	{
		wall.tex_y = (int)wall.tex_pos & (texture->height - 1);
		wall.tex_pos += wall.step;
		wall.color = get_texture_pixel(texture, wall.tex_x, wall.tex_y);
		draw_pixel(game, x, wall.y, wall.color);
		wall.y++;
	}
}

void	clear_screen(t_game *game)
{
	ft_memset(game->render_addr, 0, SCREEN_HEIGHT * game->render_line_length);
}

void	rendering_frame(t_game *game)
{
	t_ray			ray;
	t_render_frame	frame;
	int				x;

	clear_screen(game);
	render_floor_and_ceiling(game);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(&ray, game, x);
		cast_ray(&ray, game);
		game->ray = ray;
		frame.line_height = (int)(SCREEN_HEIGHT / ray.perp_wall_dist);
		frame.draw_start = -frame.line_height / 2 + SCREEN_HEIGHT / 2;
		frame.draw_end = frame.line_height / 2 + SCREEN_HEIGHT / 2;
		if (frame.draw_start < 0)
			frame.draw_start = 0;
		if (frame.draw_end >= SCREEN_HEIGHT)
			frame.draw_end = SCREEN_HEIGHT - 1;
		draw_wall_column(game, x, frame.draw_start, frame.draw_end);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);
}
