/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:01:21 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/12 12:53:57 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../include/map_parser.h"
# include "../libs/libft/libft.h"

# define TRUE 0
# define FALSE 1

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
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_texture;

typedef struct s_player
{
	int x;
	int y;
	int old_x;
	int old_y;
	int width;
	int height;
	int movements;
	t_texture img;
} t_player;

typedef struct s_map
{
	void *mlx;
	void *mlx_win;
	char **map;
	int width;
	int height;
	int is_closed;
	t_texture no_wall;
	t_texture so_wall;
	t_texture we_wall;
	t_texture ea_wall;
	t_texture floor;
	t_texture ceiling;
} t_map;

typedef struct s_game
{
	t_map map;
	t_player player;
	char **file;
	t_keys		keys;
} t_game;

void free_all(char **str);

#endif
