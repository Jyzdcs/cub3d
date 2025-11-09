/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:49:17 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/09 11:49:17 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/raycasting.h"
#include "../../include/rendering.h"

void	init_texture(t_game *game, t_texture **texture, int *tex_x)
{
	*texture = get_texture(game, game->ray.texture_id);
	if (!*texture)
		return ;
	*tex_x = (int)(game->ray.wall_x * (double)(*texture)->width);
	if (*tex_x < 0)
		*tex_x = 0;
	if (*tex_x >= (*texture)->width)
		*tex_x = (*texture)->width - 1;
}

void	init_wall_column(t_wall_column *wall, t_texture *texture,
		t_render_frame *frame)
{
	wall->step = 1.0 * texture->height / frame->line_height;
	wall->draw_start = frame->draw_start;
	wall->draw_end = frame->draw_end;
	wall->tex_pos = (frame->draw_start - (-frame->line_height / 2
				+ SCREEN_HEIGHT / 2)) * wall->step;
	wall->tex_y = 0;
	wall->color = 0;
	wall->y = frame->draw_start;
}

void	draw_wall_column(t_game *game, int x, t_render_frame *frame)
{
	t_wall_column	wall;
	t_texture		*texture;

	init_texture(game, &texture, &wall.tex_x);
	init_wall_column(&wall, texture, frame);
	while (wall.y <= frame->draw_end)
	{
		wall.tex_y = (int)wall.tex_pos;
		if (wall.tex_y < 0)
			wall.tex_y = 0;
		if (wall.tex_y >= texture->height)
			wall.tex_y = texture->height - 1;
		wall.tex_pos += wall.step;
		wall.color = get_texture_pixel(texture, wall.tex_x, wall.tex_y);
		draw_pixel(game, x, wall.y, wall.color);
		wall.y++;
	}
}

void	init_frame(t_render_frame *frame, t_ray *ray)
{
	frame->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	frame->draw_start = -frame->line_height / 2 + SCREEN_HEIGHT / 2;
	frame->draw_end = frame->line_height / 2 + SCREEN_HEIGHT / 2;
	if (frame->draw_start < 0)
		frame->draw_start = 0;
	if (frame->draw_end >= SCREEN_HEIGHT)
		frame->draw_end = SCREEN_HEIGHT - 1;
}

void	rendering_frame(t_game *game)
{
	t_ray			ray;
	t_render_frame	frame;
	int				x;

	render_floor_and_ceiling(game);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray(&ray, game, x);
		cast_ray(&ray, game);
		game->ray = ray;
		init_frame(&frame, &ray);
		draw_wall_column(game, x, &frame);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);
}
