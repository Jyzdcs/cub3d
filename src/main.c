/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:51:08 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/13 14:52:15 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rendering.h"
#include "../minilibx/mlx/mlx.h"
#include "../include/map_parser.h"
#include "../include/controls.h"

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

void	init_xpm_data(t_game *game)
{
	// Hardcode temporaire pour test MLX
	game->map.no_wall = "../maps/xpm/north.xpm";
	game->map.so_wall = "../maps/xpm/south.xpm";
	game->map.we_wall = "../maps/xpm/west.xpm";
	game->map.ea_wall = "../maps/xpm/east.xpm";

	game->no_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.no_wall, &game->no_texture.width, &game->no_texture.height);
	game->no_texture.addr = mlx_get_data_addr(game->no_texture.img, &game->no_texture.bits_per_pixel, &game->no_texture.line_length, &game->no_texture.endian);
	game->so_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.so_wall, &game->so_texture.width, &game->so_texture.height);
	game->so_texture.addr = mlx_get_data_addr(game->so_texture.img, &game->so_texture.bits_per_pixel, &game->so_texture.line_length, &game->so_texture.endian);
	game->we_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.we_wall, &game->we_texture.width, &game->we_texture.height);
	game->we_texture.addr = mlx_get_data_addr(game->we_texture.img, &game->we_texture.bits_per_pixel, &game->we_texture.line_length, &game->we_texture.endian);
	game->ea_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.ea_wall, &game->ea_texture.width, &game->ea_texture.height);
	game->ea_texture.addr = mlx_get_data_addr(game->ea_texture.img, &game->ea_texture.bits_per_pixel, &game->ea_texture.line_length, &game->ea_texture.endian);
	if (!game->no_texture.img || !game->so_texture.img || !game->we_texture.img || !game->ea_texture.img)
		return (ft_putstr_fd("Error: initialization of the textures\n", 2), 1);
	if (!game->no_texture.addr || !game->so_texture.addr || !game->we_texture.addr || !game->ea_texture.addr)
		return (ft_putstr_fd("Error: initialization of the textures\n", 2), 1);
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	t_game	*game;
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);
	if (file_handler(argv[1], game) == FALSE)
		return (ft_putstr_fd("Error: file handler\n", 2), 1);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
			if (getenv("DOCKER") || getenv("WSL_DISTRO_NAME"))
				ft_putstr_fd("Error: MLX requires X11 server. Run with -e DISPLAY=$DISPLAY\n", 2);
			else
				ft_putstr_fd("Error: MLX initialization failed\n", 2);
			return (1);
		}
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game->mlx_win)
		return (ft_putstr_fd("Error: creation of the window\n", 2), 1);


	init_xpm_data(game);

	rendering_frame(game);


	mlx_key_hook(game->mlx_win, handle_key_press, game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
	return (0);
}
