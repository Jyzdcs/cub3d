/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:13:45 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/24 17:46:40 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
#define RENDERING_H

#include "cub3d.h"

typedef struct s_map t_map;
typedef struct s_player t_player;
typedef struct s_game t_game;
typedef struct s_texture t_texture;

void draw_pixel(t_game *game, int x, int y, int color);
t_texture *get_texture(t_game *game, int texture_id);
void draw_wall_column(t_game *game, int x, int draw_start, int draw_end);
void rendering_frame(t_game *game);
void render_floor_and_ceiling(t_game *game);
int get_texture_pixel(t_texture *texture, int tex_x, int tex_y);
int rgb_to_int(char *rgb);

/* INITIALIZATION */
int init_game_walls_paths(t_game *game);
int init_game_textures(t_game *game);
int init_game_rgb(t_game *game);
int load_texture(t_game *game, t_texture *texture, char *path, char *texture_name);
#endif
