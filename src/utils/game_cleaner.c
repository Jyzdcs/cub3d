/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:16:43 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/10 15:31:53 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	clean_textures(t_game *game)
{
	if (game->no_texture.img)
		mlx_destroy_image(game->mlx, game->no_texture.img);
	if (game->so_texture.img)
		mlx_destroy_image(game->mlx, game->so_texture.img);
	if (game->we_texture.img)
		mlx_destroy_image(game->mlx, game->we_texture.img);
	if (game->ea_texture.img)
		mlx_destroy_image(game->mlx, game->ea_texture.img);
	game->no_texture.img = NULL;
	game->no_texture.addr = NULL;
	game->so_texture.img = NULL;
	game->so_texture.addr = NULL;
	game->we_texture.img = NULL;
	game->we_texture.addr = NULL;
	game->ea_texture.img = NULL;
	game->ea_texture.addr = NULL;
}

void	free_map_wall(t_game *game)
{
	if (game->map.no_wall)
		free(game->map.no_wall);
	if (game->map.so_wall)
		free(game->map.so_wall);
	if (game->map.we_wall)
		free(game->map.we_wall);
	if (game->map.ea_wall)
		free(game->map.ea_wall);
}

void	exit_game(t_game *game, char *message)
{
	if (game->file)
		free_all(game->file);
	if (game->map.map)
		free_all(game->map.map);
	free_map_wall(game);
	if (game->mlx)
	{
		if (game->render_img)
			mlx_destroy_image(game->mlx, game->render_img);
		clean_textures(game);
		if (game->mlx_win)
			mlx_destroy_window(game->mlx, game->mlx_win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	ft_putstr_fd(message, 2);
	if (game)
		free(game);
	exit(1);
}
