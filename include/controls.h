#ifndef CONTROLS_H
#define CONTROLS_H

#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include "cub3d.h"

// macOS keycodes (for MinilibX OpenGL on macOS)
// #define KEY_ESC 53
// #define KEY_W 13
// #define KEY_A 0
// #define KEY_S 1
// #define KEY_D 2
// #define KEY_LEFT 123
// #define KEY_RIGHT 124
// #define KEY_UP 126
// #define KEY_DOWN 125

int handle_key_press(int keycode, t_game *game);
int handle_key_release(int keycode, t_game *game);
int there_is_no_wall(t_map *map, double x, double y);
void move_forward(t_game *game);
void move_backward(t_game *game);
void strafe_left(t_game *game);
void strafe_right(t_game *game);
void rotate_left(t_game *game);
void rotate_right(t_game *game);
void rotate_player(t_game *game, double angle);
void rotate_left(t_game *game);
void rotate_right(t_game *game);
int process_keys(void *param);

#endif
