/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:51:08 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/10 15:27:03 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_game_data(t_game *game)
{
	init_player_data(game);
	game->keys.w_pressed = 0;
	game->keys.a_pressed = 0;
	game->keys.s_pressed = 0;
	game->keys.d_pressed = 0;
	game->keys.left_pressed = 0;
	game->keys.right_pressed = 0;
	game->keys.escape_pressed = 0;
}

void	init_render_image(t_game *game)
{
	game->render_img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->render_img)
	{
		ft_putstr_fd("Error: Failed to create render image\n", 2);
		return ;
	}
	game->render_addr = mlx_get_data_addr(game->render_img,
			&game->render_bits_per_pixel, &game->render_line_length,
			&game->render_endian);
}

void	parsing(t_game *game, int argc, char **argv)
{
	if (argc != 2)
		exit_game(game, "Error: wrong number of arguments\n");
	if (ft_check_extension(argv[1], ".cub", 4) == FALSE || file_handler(argv[1],
			game) == FALSE)
		exit_game(game, "Error: parsing failed\n");
	if (game->file == NULL)
		exit_game(game, "Error: game->file is NULL\n");
	if (map_is_valid(game) == FALSE)
		exit_game(game, "Error: parsing failed\n");
	if (ft_rgb_and_textures_checker(game) == FALSE)
		exit_game(game, "Error: parsing failed\n");
	ft_putstr_fd("Succes: map is valid\n", 1);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);
	parsing(game, argc, argv);
	init_game_data(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_game(game, "Error: MLX initialization failed\n");
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	if (!game->mlx_win)
		exit_game(game, "Error: MLX window creation failed\n");
	init_render_image(game);
	init_game_textures(game);
	rendering_frame(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);
	mlx_hook(game->mlx_win, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, handle_key_release, game);
	mlx_loop_hook(game->mlx, process_keys, game);
	mlx_loop(game->mlx);
	return (0);
}
