/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:13:45 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/03 00:14:01 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "cub3d.h"
typedef struct s_map			t_map;

typedef struct s_player			t_player;
typedef struct s_game			t_game;
typedef struct s_texture		t_texture;
typedef struct s_render_frame	t_render_frame;
typedef struct s_wall_column	t_wall_column;
typedef struct s_ray			t_ray;

/* UTILS */
void							draw_pixel(t_game *game, int x, int y,
									int color);
t_texture						*get_texture(t_game *game, int texture_id);
int								get_texture_pixel(t_texture *texture, int tex_x,
									int tex_y);
int								rgb_to_int(char *rgb);

/* RENDERING */
void							init_texture(t_game *game, t_texture **texture,
									int *tex_x);
void							init_wall_column(t_wall_column *wall,
									t_texture *texture, t_render_frame *frame);
void							draw_wall_column(t_game *game, int x,
									t_render_frame *frame);
void							init_frame(t_render_frame *frame, t_ray *ray);
void							rendering_frame(t_game *game);

/* FLOOR AND CEILING */
void							render_floor_and_ceiling(t_game *game);

/* INITIALIZATION */
int								init_game_walls_paths_and_colors(t_game *game);
void							init_game_textures(t_game *game);
int								load_texture(t_game *game, t_texture *texture,
									char *path, char *texture_name);
int								load_all_textures(t_game *game);
void							init_player_data(t_game *game);
#endif
