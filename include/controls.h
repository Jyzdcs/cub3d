#ifndef CONTROLS_H
# define CONTROLS_H

# include <X11/keysym.h>
# include <X11/X.h>
# include "cub3d.h"

int	handle_key_press(int keycode, t_game *game);
int	handle_key_release(int keycode, t_game *game);

#endif
