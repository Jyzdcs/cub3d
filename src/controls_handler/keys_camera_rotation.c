#include "../../include/controls_handler.h"

void rotate_player(t_game *game, double angle)
{
	double old_dir_x;
	double old_plane_x;
	double cos_a = cos(angle);
	double sin_a = sin(angle);

	// Rotate direction
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos_a - game->player.dir_y * sin_a;
	game->player.dir_y = old_dir_x * sin_a + game->player.dir_y * cos_a;

	// Rotate plane
	old_plane_x = game->camera.plane_x;
	game->camera.plane_x = game->camera.plane_x * cos_a - game->camera.plane_y * sin_a;
	game->camera.plane_y = old_plane_x * sin_a + game->camera.plane_y * cos_a;
}

void rotate_left(t_game *game)
{
	rotate_player(game, game->player.rotation_speed);
}

void rotate_right(t_game *game)
{
	rotate_player(game, -game->player.rotation_speed);
}
