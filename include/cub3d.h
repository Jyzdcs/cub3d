/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cub3d.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: kclaudan <kclaudan@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/10/02 12:01:21 by kclaudan		  #+#	#+#			 */
/*   Updated: 2025/10/21 21:24:56 by kclaudan		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../include/map_parser.h"
#include "../include/rendering.h"
#include "../libs/libft/libft.h"
#include "../libs/minilibx_opengl_20191021/mlx.h"
// # include "../minilibx/mlx/mlx.h"
#include <errno.h>
#include <fcntl.h>

#define TRUE 0
#define FALSE 1
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define HITBOX_SIZE 0.2

typedef struct s_keys
{
	int w_pressed;
	int a_pressed;
	int s_pressed;
	int d_pressed;
	int left_pressed;
	int right_pressed;
	int escape_pressed;
} t_keys;

typedef struct s_texture
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_texture;

typedef struct s_wall_column
{
	int tex_x;
	double step;
	int draw_start;
	int draw_end;
	double tex_pos;
	int tex_y;
	int color;
	int y;
} t_wall_column;

typedef struct s_render_frame
{
	int line_height;
	int draw_start;
	int draw_end;
} t_render_frame;

typedef struct s_player
{
	double x;
	double y;
	double old_x;
	double old_y;
	double dir_x;
	double dir_y;
	double speed;
	double rotation_speed;
} t_player;

// FOV
typedef struct s_camera
{
	double plane_x;
	double plane_y;
} t_camera;

typedef struct s_map
{
	char **map;
	int width;
	int height;
	int is_closed;
	char *no_wall;
	char *so_wall;
	char *we_wall;
	char *ea_wall;
	int floor_color;
	int ceiling_color;
} t_map;

typedef struct s_ray
{
	double dir_x;					 // Direction du rayon X
	double dir_y;					 // Direction du rayon Y
	int map_x;						 // Position X sur la map
	int map_y;						 // Position Y sur la map
	int step_x;						 // -1 ou 1
	int step_y;						 // -1 ou 1
	double side_dist_x;		 // Distance du prochain cote X
	double side_dist_y;		 // Distance du prochain cote Y
	double delta_dist_x;	 // |1 / dir_x|
	double delta_dist_y;	 // |1 / dir_y|
	double perp_wall_dist; // Distance perpendiculaire au mur
	int side;							 // 0 = mur vertical(E/W), 1 = horizontal(N/S)
	int texture_id;				 // 0=NO, 1=SO, 2=WE, 3=EA
	double wall_x;				 // Point de collision du rayon sur le mur
} t_ray;

typedef struct s_game
{
	void *mlx;
	void *mlx_win;
	void *render_img;
	char *render_addr;
	int render_bits_per_pixel;
	int render_line_length;
	int render_endian;
	t_map map;
	t_player player;
	t_keys keys;
	t_camera camera;
	t_ray ray;
	char **file;
	t_texture no_texture;
	t_texture so_texture;
	t_texture we_texture;
	t_texture ea_texture;
} t_game;

int parsing(t_game *game, int argc, char **argv);

void free_all(char **str);
void exit_game(t_game *game, char *message);
int ft_array_size(char **array);

#endif
