/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:01:21 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/02 18:26:26 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../libs/libft/libft.h"

#define TRUE 0
#define FALSE 1
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

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
	t_texture	no_wall;
	t_texture	so_wall;
	t_texture	we_wall;
	t_texture	ea_wall;
	int			floor_color;
	int			ceiling_color;
}				t_map;

typedef struct s_ray
{
	double		dir_x;					// Direction du rayon X
	double		dir_y;					// Direction du rayon Y
	int			map_x;					// Position X sur la map
	int			map_y;					// Position Y sur la map
	int			step_x;					// -1 ou 1
	int			step_y;					// -1 ou 1
	double		side_dist_x;			// Distance du prochain cote X
	double		side_dist_y;			// Distance du prochain cote Y
	double		delta_dist_x;			// |1 / dir_x|
	double		delta_dist_y;			// |1 / dir_y|
	double		perp_wall_dist;			// Distance perpendiculaire au mur
	int			side;					// 0 = mur vertical (E/W), 1 = mur horizontal (N/S)
	int			texture_id;				// 0=NO, 1=SO, 2=WE, 3=EA
	double		wall_x;					// Point de collision du rayon sur le mur
}					t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	t_map		map;
	t_player	player;
	t_camera	camera;
}				t_game;

#endif
