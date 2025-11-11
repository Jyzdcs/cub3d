/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:57:33 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/11 14:20:04 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../include/controls.h"
# include "../include/map_parser.h"
# include "../include/rendering.h"
# include "../libs/libft/libft.h"
// # include "../libs/minilibx_opengl_20191021/mlx.h"
# include "../minilibx/mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>

# define TRUE 0
# define FALSE 1
# define SCREEN_WIDTH 920
# define SCREEN_HEIGHT 520
# define HITBOX_SIZE 0.2

typedef struct s_keys
{
	int			w_pressed;
	int			a_pressed;
	int			s_pressed;
	int			d_pressed;
	int			left_pressed;
	int			right_pressed;
	int			escape_pressed;
}				t_keys;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_wall_column
{
	int			tex_x;
	double		step;
	int			draw_start;
	int			draw_end;
	double		tex_pos;
	int			tex_y;
	int			color;
	int			y;
}				t_wall_column;

typedef struct s_render_frame
{
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_render_frame;

typedef struct s_player
{
	double		x;
	double		y;
	double		old_x;
	double		old_y;
	double		dir_x;
	double		dir_y;
	double		speed;
	double		rotation_speed;
	char		id;
}				t_player;

// FOV
typedef struct s_camera
{
	double		plane_x;
	double		plane_y;
}				t_camera;

typedef struct s_map
{
	char		**map;
	int			width;
	int			height;
	int			is_closed;
	char		*no_wall;
	char		*so_wall;
	char		*we_wall;
	char		*ea_wall;
	int			floor_color;
	int			ceiling_color;
}				t_map;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			side;
	int			texture_id;
	double		wall_x;
}				t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	void		*render_img;
	char		*render_addr;
	int			render_bits_per_pixel;
	int			render_line_length;
	int			render_endian;
	t_map		map;
	t_player	player;
	t_keys		keys;
	t_camera	camera;
	t_ray		ray;
	char		**file;
	t_texture	no_texture;
	t_texture	so_texture;
	t_texture	we_texture;
	t_texture	ea_texture;
}				t_game;

void			parsing(t_game *game, int argc, char **argv);

void			free_all(char **str);
void			exit_game(t_game *game, char *message);
int				ft_array_size(char **array);
void			exit_red_cross(t_game *game);

#endif
