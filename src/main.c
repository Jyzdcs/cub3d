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

void	init_game_data(t_game *game)
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

    // Initialiser les couleurs
    game->map.floor_color = 0x808080;
    game->map.ceiling_color = 0x404040;

    // Initialiser la map si elle n'existe pas
    if (!game->map.map)
    {
        game->map.map = malloc(sizeof(char*) * 6);
        game->map.map[0] = "111111";
        game->map.map[1] = "100001";
        game->map.map[2] = "100001";
        game->map.map[3] = "100001";
        game->map.map[4] = "100001";
        game->map.map[5] = "111111";
        game->map.map[6] = NULL;
        game->map.width = 6;
        game->map.height = 6;
    }
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

// int	main(int argc, char **argv)
// {
// 	t_game	*game;

// 	if (argc != 2)
// 		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);
// 	game = malloc(sizeof(t_game));
// 	game->map.is_closed = TRUE;
// 	if (!game)
// 		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);
// 	if (parsing(game, argc, argv) == FALSE)
// 	{
// 		free(game);
// 		return (1);
// 	}
// 	init_game_data(game);
// 	game->mlx = mlx_init();
// 	if (!game->mlx)
// 	{
// 		if (getenv("DOCKER") || getenv("WSL_DISTRO_NAME"))
// 			ft_putstr_fd("Error: MLX requires X11 server. Run with '-e DISPLAY=$DISPLAY'\n",
// 				2);
// 		else
// 			ft_putstr_fd("Error: MLX initialization failed\n", 2);
// 		return (1);
// 	}
// 	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
// 	if (!game->mlx_win)
// 		return (ft_putstr_fd("Error: creation of the window\n", 2), 1);
// 	init_render_image(game);
// 	init_xpm_data(game);
// 	rendering_frame(game);
// 	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);
// 	mlx_key_hook(game->mlx_win, handle_key_press, game);
// 	mlx_hook(game->mlx_win, 17, 0, close_window, game);
// 	mlx_loop(game->mlx);
// 	return (0);
// }

// Ajoutez ces fonctions dans main.c avant main():
int handle_key_press_simple(int keycode, t_game *game)
{
    printf("DEBUG: Key pressed: %d\n", keycode);

    if (keycode == XK_Escape)
    {
        printf("DEBUG: ESC pressed, exiting\n");
        mlx_destroy_window(game->mlx, game->mlx_win);
        exit(0);
    }
    else if (keycode == XK_w)
    {
        printf("DEBUG: W pressed - moving forward\n");
        // Mouvement vers l'avant
        game->player.x += game->player.dir_x * game->player.speed;
        game->player.y += game->player.dir_y * game->player.speed;
        printf("DEBUG: New position: x=%.2f, y=%.2f\n", game->player.x, game->player.y);
    }
    else if (keycode == XK_s)
    {
        printf("DEBUG: S pressed - moving backward\n");
        // Mouvement vers l'arrière
        game->player.x -= game->player.dir_x * game->player.speed;
        game->player.y -= game->player.dir_y * game->player.speed;
        printf("DEBUG: New position: x=%.2f, y=%.2f\n", game->player.x, game->player.y);
    }
    else if (keycode == XK_a)
    {
        printf("DEBUG: A pressed - moving left\n");
        // Mouvement vers la gauche (perpendiculaire)
        game->player.x -= game->player.dir_y * game->player.speed;
        game->player.y += game->player.dir_x * game->player.speed;
        printf("DEBUG: New position: x=%.2f, y=%.2f\n", game->player.x, game->player.y);
    }
    else if (keycode == XK_d)
    {
        printf("DEBUG: D pressed - moving right\n");
        // Mouvement vers la droite (perpendiculaire)
        game->player.x += game->player.dir_y * game->player.speed;
        game->player.y -= game->player.dir_x * game->player.speed;
        printf("DEBUG: New position: x=%.2f, y=%.2f\n", game->player.x, game->player.y);
    }
    else if (keycode == XK_Left)
    {
        printf("DEBUG: Left arrow pressed - rotating left\n");
        // Rotation vers la gauche
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(game->player.rotation_speed) - game->player.dir_y * sin(game->player.rotation_speed);
        game->player.dir_y = old_dir_x * sin(game->player.rotation_speed) + game->player.dir_y * cos(game->player.rotation_speed);
        printf("DEBUG: New direction: dir_x=%.2f, dir_y=%.2f\n", game->player.dir_x, game->player.dir_y);
    }
    else if (keycode == XK_Right)
    {
        printf("DEBUG: Right arrow pressed - rotating right\n");
        // Rotation vers la droite
        double old_dir_x = game->player.dir_x;
        game->player.dir_x = game->player.dir_x * cos(-game->player.rotation_speed) - game->player.dir_y * sin(-game->player.rotation_speed);
        game->player.dir_y = old_dir_x * sin(-game->player.rotation_speed) + game->player.dir_y * cos(-game->player.rotation_speed);
        printf("DEBUG: New direction: dir_x=%.2f, dir_y=%.2f\n", game->player.dir_x, game->player.dir_y);
    }

    // Redessiner la frame après chaque mouvement
    rendering_frame(game);
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);

    return (0);
}
int handle_key_release_simple(int keycode, t_game *game)
{
    if (keycode == XK_w)
        game->keys.w_pressed = 0;
    else if (keycode == XK_s)
        game->keys.s_pressed = 0;
    else if (keycode == XK_a)
        game->keys.a_pressed = 0;
    else if (keycode == XK_d)
        game->keys.d_pressed = 0;
    else if (keycode == XK_Left)
        game->keys.left_pressed = 0;
    else if (keycode == XK_Right)
        game->keys.right_pressed = 0;

    return (0);
}

int close_window_simple(t_game *game)
{
    printf("DEBUG: Window close requested\n");
    mlx_destroy_window(game->mlx, game->mlx_win);
    exit(0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
		return (ft_putstr_fd("Error: wrong number of arguments\n", 2), 1);

	printf("DEBUG: Starting program\n");

	game = malloc(sizeof(t_game));
	if (!game)
		return (ft_putstr_fd("Error: allocation memory on game\n", 2), 1);

	printf("DEBUG: Game allocated\n");

	game->map.is_closed = TRUE;

	printf("DEBUG: Before parsing\n");
	if (parsing(game, argc, argv) == FALSE)
	{
		printf("DEBUG: Parsing failed\n");
		free(game);
		return (1);
	}
	printf("DEBUG: Parsing succeeded\n");

	init_game_data(game);
	printf("DEBUG: Game data initialized\n");

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("DEBUG: MLX initialization failed\n");
		free(game);
		return (1);
	}
	printf("DEBUG: MLX initialized\n");

	game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!game->mlx_win)
	{
		printf("DEBUG: Window creation failed\n");
		free(game);
		return (1);
	}
	printf("DEBUG: Window created\n");

	init_render_image(game);
	printf("DEBUG: Render image initialized\n");

	// Hardcode textures
	game->map.no_wall = "/home/kaa/Desktop/cub3d/maps/xpm/north.xpm";
	game->map.so_wall = "/home/kaa/Desktop/cub3d/maps/xpm/south.xpm";
	game->map.we_wall = "/home/kaa/Desktop/cub3d/maps/xpm/west.xpm";
	game->map.ea_wall = "/home/kaa/Desktop/cub3d/maps/xpm/east.xpm";

	init_xpm_data(game);
	printf("DEBUG: XPM data initialized\n");

	rendering_frame(game);
	printf("DEBUG: Rendering frame completed\n");

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->render_img, 0, 0);
	printf("DEBUG: Image put to window\n");

	mlx_key_hook(game->mlx_win, handle_key_press_simple, game);
	printf("DEBUG: Key press hook set\n");

	mlx_hook(game->mlx_win, 2, 1L << 0, handle_key_release_simple, game); // Key release
	printf("DEBUG: Key release hook set\n");

	mlx_hook(game->mlx_win, 17, 0, close_window_simple, game);
	printf("DEBUG: Close hook set\n");

	mlx_loop(game->mlx);
	printf("DEBUG: MLX loop started (this should not print)\n");

	return (0);
}
