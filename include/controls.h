/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:57:27 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/09 11:57:27 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# include "cub3d.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

// macOS keycodes (for MinilibX OpenGL on macOS)
// # define KEY_ESC 53
// # define KEY_W 13
// # define KEY_A 0
// # define KEY_S 1
// # define KEY_D 2
// # define KEY_LEFT 123
// # define KEY_RIGHT 124
// # define KEY_UP 126
// # define KEY_DOWN 125

int		handle_key_press(int keycode, t_game *game);
int		handle_key_release(int keycode, t_game *game);
int		there_is_no_wall(t_map *map, double x, double y);
int		process_keys(void *param);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	strafe_left(t_game *game);
void	strafe_right(t_game *game);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
void	rotate_player(t_game *game, double angle);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);

#endif
