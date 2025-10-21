#include "../../include/cub3d.h"
#include "../../include/raycasting.h"
#include "../../include/rendering.h"

void	draw_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		dst = game->render_addr + (y * game->render_line_length + x * (game->render_bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

t_texture	*get_texture(t_game *game, int texture_id)
{
	if (texture_id == 0)
		return &game->no_texture;
	else if (texture_id == 1)
		return &game->so_texture;
	else if (texture_id == 2)
		return &game->we_texture;
	else if (texture_id == 3)
		return &game->ea_texture;
	else
		return NULL;
}

int	get_texture_pixel(t_texture *texture, int tex_x, int tex_y)
{
	char	*dst;

	dst = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8));
	return *(unsigned int*)dst;
}
