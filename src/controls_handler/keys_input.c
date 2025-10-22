/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   keys_input.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kclaudan <kclaudan@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/10/10 20:16:47 by kclaudan		  #+#	#+#			 */
/*   Updated: 2025/10/21 21:35:13 by kclaudan		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../include/controls.h"
#include "../../include/rendering.h"
#include "../../include/cub3d.h"

// This function updates the key state when a key is pressed.
// ESC key returns FALSE to exit the program.
// Other keys update the corresponding state in game->keys.
int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
	{
		exit_game(game,"Endgame\n");
	}
	if (keycode == XK_w)
		game->keys.w_pressed = 1;
	if (keycode == XK_a)
		game->keys.a_pressed = 1;
	if (keycode == XK_s)
		game->keys.s_pressed = 1;
	if (keycode == XK_d)
		game->keys.d_pressed = 1;
	if (keycode == XK_Left)
		game->keys.left_pressed = 1;
	if (keycode == XK_Right)
		game->keys.right_pressed = 1;
	return (TRUE);
}

// This function updates the key state when a key is released.
int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->keys.w_pressed = 0;
	if (keycode == XK_a)
		game->keys.a_pressed = 0;
	if (keycode == XK_s)
		game->keys.s_pressed = 0;
	if (keycode == XK_d)
		game->keys.d_pressed = 0;
	if (keycode == XK_Left)
		game->keys.left_pressed = 0;
	if (keycode == XK_Right)
		game->keys.right_pressed = 0;
	return (TRUE);
}

// This function process the value of the kame->keys whether they are pressed to move in consequence.
int process_keys(void *param)
{
	t_game *game = (t_game *)param;

	if (game->keys.w_pressed)
		move_forward(game);
	if (game->keys.s_pressed)
		move_backward(game);
	if (game->keys.a_pressed)
		strafe_left(game);
	if (game->keys.d_pressed)
		strafe_right(game);
	if (game->keys.left_pressed)
		rotate_left(game);
	if (game->keys.right_pressed)
		rotate_right(game);
	rendering_frame(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);
	return (0);
}
