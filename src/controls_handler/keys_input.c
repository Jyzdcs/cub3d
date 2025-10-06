#include "../../include/controls.h"
#include "../../include/cub3d.h"

// These 4 functions are used for tests only, in order to TDD correctly.
// These are stub functions.
// They need to be uncommented to run the tests.

// static int	handle_key_w_s_movement(int keycode, t_game *game)
// {
// 	(void)keycode;
// 	(void)game;
// 	return (TRUE);
// }
// static int	handle_key_a_d_movement(int keycode, t_game *game)
// {
// 	(void)keycode;
// 	(void)game;
// 	return (TRUE);
// }
// static int	handle_key_left_right_rotation(int keycode, t_game *game)
// {
// 	(void)keycode;
// 	(void)game;
// 	return (TRUE);
// }
// static int	launch_rendering_function(t_game *game)
// {
// 	(void)game;
// 	return (TRUE);
// }

// This function only take the information from the key pressed and is used to handle the key pressed
// In casee of Esc key pressed, this will either return false or launch the exit function for the program.
// In case of Left or Right key pressed, this will trigger the rotation of the camera.
// If a key is pressed, we move the position of the player and then we render the view of the new position.
int	handle_key_press(int keycode, t_game *game)
{
	int key_is_pressed;

	key_is_pressed = FALSE;
	if (keycode == XK_Escape)
		return (FALSE);
	if (keycode == XK_W)
		key_is_pressed = handle_key_w_s_movement(keycode, game);
	if (keycode == XK_A)
		key_is_pressed = handle_key_a_d_movement(keycode, game);
	if (keycode == XK_S)
		key_is_pressed = handle_key_w_s_movement(keycode, game);
	if (keycode == XK_D)
		key_is_pressed = handle_key_a_d_movement(keycode, game);
	if (keycode == XK_Left)
		key_is_pressed = handle_key_left_right_rotation(keycode, game);
	if (keycode == XK_Right)
		key_is_pressed = handle_key_left_right_rotation(keycode, game);
	if (key_is_pressed)
		launch_rendering_function(game);
	return (TRUE);
}
