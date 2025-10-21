#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"

void	draw_pixel(t_game *game, int x, int y, int color);
t_texture	*get_texture(t_game *game, int texture_id);
void	draw_wall_column(t_game *game, int x, int draw_start, int draw_end);
void	rendering_frame(t_game *game);
void	render_floor_and_ceiling(t_game *game);
int		get_texture_pixel(t_texture *texture, int tex_x, int tex_y);
void	init_texture(t_game *game, t_texture **texture, int *tex_x);

#endif
