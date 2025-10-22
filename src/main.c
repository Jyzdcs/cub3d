/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:51:08 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/21 21:47:07 by kclaudan         ###   ########.fr       */
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

// Dans main(), avant parsing():
void	init_all_structures(t_game *game)
{
	// Initialiser t_player
	game->player.x = 1.5;
	game->player.y = 1.5;
	game->player.dir_x = 1.0;
	game->player.dir_y = 0.0;
	// ... autres champs

	// Initialiser t_camera
	game->camera.plane_x = 0.0;
	game->camera.plane_y = 0.66;

	// Initialiser t_keys
	game->keys.w_pressed = 0;
	// ... autres clés

	// Initialiser les textures à NULL
	game->no_texture.img = NULL;
	game->so_texture.img = NULL;
	game->we_texture.img = NULL;
	game->ea_texture.img = NULL;
}

void	init_render_image(t_game *game)
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

void	init_xpm_data(t_game *game)
{
	printf("DEBUG: no_wall = %p\n", game->map.no_wall);
	printf("DEBUG: no_wall content = %s\n",
		game->map.no_wall ? game->map.no_wall : "NULL");
	// Hardcode temporaire pour test MLX
	game->map.no_wall = "/home/kaa/Desktop/cub3d/maps/xpm/north.xpm";
	game->map.so_wall = "/home/kaa/Desktop/cub3d/maps/xpm/south.xpm";
	game->map.we_wall = "/home/kaa/Desktop/cub3d/maps/xpm/west.xpm";
	game->map.ea_wall = "/home/kaa/Desktop/cub3d/maps/xpm/east.xpm";
	printf("DEBUG: After hardcode - no_wall = %s\n", game->map.no_wall);
	game->no_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.no_wall,
			&game->no_texture.width, &game->no_texture.height);
	if (!game->no_texture.img)
	{
		ft_putstr_fd("Error: Failed to load NO texture\n", 2);
		return ;
	}
	game->no_texture.addr = mlx_get_data_addr(game->no_texture.img,
			&game->no_texture.bits_per_pixel, &game->no_texture.line_length,
			&game->no_texture.endian);
	game->so_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.so_wall,
			&game->so_texture.width, &game->so_texture.height);
	if (!game->so_texture.img)
	{
		ft_putstr_fd("Error: Failed to load SO texture\n", 2);
		return ;
	}
	game->so_texture.addr = mlx_get_data_addr(game->so_texture.img,
			&game->so_texture.bits_per_pixel, &game->so_texture.line_length,
			&game->so_texture.endian);
	game->we_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.we_wall,
			&game->we_texture.width, &game->we_texture.height);
	if (!game->we_texture.img)
	{
		ft_putstr_fd("Error: Failed to load WE texture\n", 2);
		return ;
	}
	game->we_texture.addr = mlx_get_data_addr(game->we_texture.img,
			&game->we_texture.bits_per_pixel, &game->we_texture.line_length,
			&game->we_texture.endian);
	game->ea_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.ea_wall,
			&game->ea_texture.width, &game->ea_texture.height);
	if (!game->ea_texture.img)
	{
		ft_putstr_fd("Error: Failed to load EA texture\n", 2);
		return ;
	}
	game->ea_texture.addr = mlx_get_data_addr(game->ea_texture.img,
			&game->ea_texture.bits_per_pixel, &game->ea_texture.line_length,
			&game->ea_texture.endian);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}

int	parsing(t_game *game, int argc, char **argv)
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

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);
	init_all_structures(game);
	if (parsing(game, argc, argv) == FALSE)
	{
		free(game);
		return (1);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		if (getenv("DOCKER") || getenv("WSL_DISTRO_NAME"))
			ft_putstr_fd("Error: MLX requires X11 server. Run with '-e DISPLAY=$DISPLAY'\n",
				2);
		else
			ft_putstr_fd("Error: MLX initialization failed\n", 2);
		return (1);
	}
	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	if (!game->mlx_win)
		return (ft_putstr_fd("Error: creation of the window\n", 2), 1);
	// Dans init_xpm_data(), remplacer par:
	init_render_image(game);
	game->map.no_wall = "/home/kaa/Desktop/cub3d/maps/xpm/north.xpm";
	game->map.so_wall = "/home/kaa/Desktop/cub3d/maps/xpm/south.xpm";
	game->map.we_wall = "/home/kaa/Desktop/cub3d/maps/xpm/west.xpm";
	game->map.ea_wall = "/home/kaa/Desktop/cub3d/maps/xpm/east.xpm";
	init_xpm_data(game);
	rendering_frame(game);
	mlx_key_hook(game->mlx_win, handle_key_press, game);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
	return (0);
}
