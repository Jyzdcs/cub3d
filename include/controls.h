#ifndef CONTROLS_H
# define CONTROLS_H

# include "cub3d.h"
# include <X11/X.h>
# include <X11/keysym.h>

int	handle_key_press(int keycode, t_game *game);
int	handle_key_release(int keycode, t_game *game);

#endif
