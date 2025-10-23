/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:15:38 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/23 17:40:07 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/rendering.h"

int init_game_textures(t_game *game)
{
	int i;
	int path_index;
	int j;

	i = 0;
	if (game->file == NULL)
		return (printf("Error: game->file is NULL\n"), FALSE);
	while (game->file[i])
	{
		j = 0;
		if (ft_is_line_empty(game->file[i]) == FALSE)
		{
			while (game->file[i][j] == ' ' || game->file[i][j] == '\t')
				j++;
			path_index = ft_find_path_to_textures(game->file[i]);
			if (ft_comp(&game->file[i][j], "NO") == TRUE)
				game->map.no_wall = &game->file[i][path_index];
			else if (ft_comp(&game->file[i][j], "SO") == TRUE)
				game->map.so_wall = &game->file[i][path_index];
			else if (ft_comp(&game->file[i][j], "WE") == TRUE)
				game->map.we_wall = &game->file[i][path_index];
			else if (ft_comp(&game->file[i][j], "EA") == TRUE)
				game->map.ea_wall = &game->file[i][path_index];
		}
		i++;
	}
	if (game->map.no_wall == NULL || game->map.so_wall == NULL || game->map.we_wall == NULL || game->map.ea_wall == NULL)
		return (printf("Error: Failed to load textures\n"), FALSE);
	return (TRUE);
}

// Hardcode temporaire pour test MLX
// game->map.no_wall = "/home/kaa/Desktop/cub3d/maps/xpm/north.xpm";
// game->map.so_wall = "/home/kaa/Desktop/cub3d/maps/xpm/south.xpm";
// game->map.we_wall = "/home/kaa/Desktop/cub3d/maps/xpm/west.xpm";
// game->map.ea_wall = "/home/kaa/Desktop/cub3d/maps/xpm/east.xpm";

// game->no_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.no_wall,
// 	&game->no_texture.width, &game->no_texture.height);
// if (!game->no_texture.img)
// {
// ft_putstr_fd("Error: Failed to load NO texture\n", 2);
// return ;
// }
// game->no_texture.addr = mlx_get_data_addr(game->no_texture.img,
// 	&game->no_texture.bits_per_pixel, &game->no_texture.line_length,
// 	&game->no_texture.endian);
// game->so_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.so_wall,
// 	&game->so_texture.width, &game->so_texture.height);
// if (!game->so_texture.img)
// {
// ft_putstr_fd("Error: Failed to load SO texture\n", 2);
// return ;
// }
// game->so_texture.addr = mlx_get_data_addr(game->so_texture.img,
// 	&game->so_texture.bits_per_pixel, &game->so_texture.line_length,
// 	&game->so_texture.endian);
// game->we_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.we_wall,
// 	&game->we_texture.width, &game->we_texture.height);
// if (!game->we_texture.img)
// {
// ft_putstr_fd("Error: Failed to load WE texture\n", 2);
// return ;
// }
// game->we_texture.addr = mlx_get_data_addr(game->we_texture.img,
// 	&game->we_texture.bits_per_pixel, &game->we_texture.line_length,
// 	&game->we_texture.endian);
// game->ea_texture.img = mlx_xpm_file_to_image(game->mlx, game->map.ea_wall,
// 	&game->ea_texture.width, &game->ea_texture.height);
// if (!game->ea_texture.img)
// {
// ft_putstr_fd("Error: Failed to load EA texture\n", 2);
// return ;
// }
// game->ea_texture.addr = mlx_get_data_addr(game->ea_texture.img,
// 	&game->ea_texture.bits_per_pixel, &game->ea_texture.line_length,
// 	&game->ea_texture.endian);