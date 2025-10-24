#include "../../include/controls.h"

int	there_is_no_wall(t_map *map, double x, double y)
{
	if (map->map[(int)(y - HITBOX_SIZE)][(int)(x - HITBOX_SIZE)] == '1')
		return (TRUE);
	if (map->map[(int)(y - HITBOX_SIZE)][(int)(x + HITBOX_SIZE)] == '1')
		return (TRUE);
	if (map->map[(int)(y + HITBOX_SIZE)][(int)(x + HITBOX_SIZE)] == '1')
		return (TRUE);
	if (map->map[(int)(y + HITBOX_SIZE)][(int)(x - HITBOX_SIZE)] == '1')
		return (TRUE);
	return (FALSE);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.speed * game->player.dir_x;
	new_y = game->player.y + game->player.speed * game->player.dir_y;
	if (there_is_no_wall(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (there_is_no_wall(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.speed * game->player.dir_x;
	new_y = game->player.y - game->player.speed * game->player.dir_y;
	if (there_is_no_wall(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (there_is_no_wall(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.speed * game->player.dir_y;
	new_y = game->player.y - game->player.speed * game->player.dir_x;
	if (there_is_no_wall(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (there_is_no_wall(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}

void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.speed * game->player.dir_y;
	new_y = game->player.y + game->player.speed * game->player.dir_x;
	if (there_is_no_wall(&game->map, new_x, game->player.y))
		game->player.x = new_x;
	if (there_is_no_wall(&game->map, game->player.x, new_y))
		game->player.y = new_y;
}
