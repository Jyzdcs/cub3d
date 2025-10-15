#ifndef CONTROLS_H
# define CONTROLS_H

# include <X11/keysym.h>
# include <X11/X.h>
# include "cub3d.h"

int	handle_key_press(int keycode, t_game *game);
int	handle_key_release(int keycode, t_game *game);
int	there_is_no_wall(t_map *map, double x, double y);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);


#endif
