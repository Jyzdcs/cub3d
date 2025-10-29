/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:51:08 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/29 13:07:02 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/controls.h"
#include "../include/map_parser.h"
#include "../include/rendering.h"
#include "../libs/minilibx_opengl_20191021/mlx.h"

// int	main(int argc, char **argv)
// {
// 	t_game	*game;

// 	game = malloc(sizeof(t_game));
// 	if (!game)
// 		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);
// 	if (argc != 2)
// 	{
// 		free(game);
// 		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
// 	}
// 	if (file_handler(argv[1], game) == FALSE)
// 	{
// 		free(game);
// 		return (1);
// 	}
// 	free_all(game->file);
// 	free(game);
// 	return (0);
// }

void init_game_data(t_game *game)
{
	// Initialiser le joueur
	game->player.x = 1.5;
	game->player.y = 1.5;
	game->player.old_x = 0.0;
	game->player.old_y = 0.0;
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	game->player.speed = 0.1;
	game->player.rotation_speed = 0.1;

	// Initialiser la caméra
	game->camera.plane_x = 0.0;
	game->camera.plane_y = 0.66;

	// Initialiser les clés
	game->keys.w_pressed = 0;
	game->keys.a_pressed = 0;
	game->keys.s_pressed = 0;
	game->keys.d_pressed = 0;
	game->keys.left_pressed = 0;
	game->keys.right_pressed = 0;
	game->keys.escape_pressed = 0;
}

void init_render_image(t_game *game)
{
	game->render_img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->render_img)
	{
		ft_putstr_fd("Error: Failed to create render image\n", 2);
		return;
	}
	game->render_addr = mlx_get_data_addr(game->render_img,
																				&game->render_bits_per_pixel, &game->render_line_length, &game->render_endian);
}

void init_xpm_data(t_game *game)
{
	if (init_game_textures(game) == FALSE)
		exit_game(game, "Error: Failed to load textures\n");
}

int close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}

int parsing(t_game *game, int argc, char **argv)
{
	if (argc != 2)
	{
		free(game);
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), FALSE);
	}
	if (ft_check_extension(argv[1], ".cub", 4) == FALSE || file_handler(argv[1],
																																			game) == FALSE)
	{
		free(game);
		return (ft_putstr_fd("Error: extension or file handler failed\n", 2),
						FALSE);
	}
	if (game->file == NULL)
		return (ft_putstr_fd("Error: game->file is NULL\n", 2), FALSE);
	if (map_is_valid(game) == FALSE)
		return (ft_putstr_fd("Error: map is not valid\n", 2), FALSE);
	if (ft_textures_checker(game) == FALSE || ft_rgb_checker(game) == FALSE)
	{
		free_all(game->file);
		free(game);
		return (ft_putstr_fd("Error: textures checker failed\n", 2), FALSE);
	}
	free_all(game->file);
	ft_putstr_fd("Succes: map is valid\n", 1);
	return (TRUE);
}

int main(int argc, char **argv)
{
	t_game *game;

	if (argc != 2)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);
	game->map.is_closed = TRUE;
	if (parsing(game, argc, argv) == FALSE)
	{
		free(game);
		return (1);
	}
	init_game_data(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("MLX initialization failed\n");
		free(game);
		return (1);
	}
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game->mlx_win)
	{
		printf("MLX window creation failed\n");
		free(game);
		return (1);
	}

	init_render_image(game);
	init_xpm_data(game);

	// rendering_frame(game);
	// mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);

	mlx_hook(game->mlx_win, 2, 1L << 0, handle_key_press, game);	 // KeyPress
	mlx_hook(game->mlx_win, 3, 1L << 1, handle_key_release, game); // KeyRelease
	mlx_hook(game->mlx_win, 17, 0, close_window, game);						 // Close
	// mlx_loop_hook(game->mlx, process_keys, game);

	mlx_loop(game->mlx);

	return (0);
}