/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_textures_and_colors.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:15:38 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/10 15:24:44 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/rendering.h"

void	put_path_and_rgb_in_variable(t_game *game, int i, int j, int path_i)
{
	if (ft_comp(&game->file[i][j], "NO") == TRUE)
		game->map.no_wall = ft_strdup(&game->file[i][path_i]);
	else if (ft_comp(&game->file[i][j], "SO") == TRUE)
		game->map.so_wall = ft_strdup(&game->file[i][path_i]);
	else if (ft_comp(&game->file[i][j], "WE") == TRUE)
		game->map.we_wall = ft_strdup(&game->file[i][path_i]);
	else if (ft_comp(&game->file[i][j], "EA") == TRUE)
		game->map.ea_wall = ft_strdup(&game->file[i][path_i]);
	else if (ft_comp(&game->file[i][j], "F") == TRUE)
		game->map.floor_color = rgb_to_int(&game->file[i][path_i]);
	else if (ft_comp(&game->file[i][j], "C") == TRUE)
		game->map.ceiling_color = rgb_to_int(&game->file[i][path_i]);
}

int	init_game_walls_paths_and_colors(t_game *game)
{
	int	i;
	int	path_i;
	int	j;

	printf("Initializing game walls paths and colors\n");
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
			path_i = ft_find_path_to_textures(game->file[i]);
			put_path_and_rgb_in_variable(game, i, j, path_i);
		}
		i++;
	}
	if (game->map.no_wall == NULL || game->map.so_wall == NULL
		|| game->map.we_wall == NULL || game->map.ea_wall == NULL
		|| game->map.floor_color == -1 || game->map.ceiling_color == -1)
		return (printf("Error: Failed to put walls paths in the map\n"), FALSE);
	return (TRUE);
}

int	load_texture(t_game *game, t_texture *texture, char *path,
		char *texture_name)
{
	texture->img = NULL;
	texture->addr = NULL;
	texture->bits_per_pixel = 0;
	texture->line_length = 0;
	texture->endian = 0;
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (printf("Error: Failed to load %s", texture_name), FALSE);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	return (TRUE);
}

int	load_all_textures(t_game *game)
{
	printf("Loading all textures\n");
	if (load_texture(game, &game->no_texture, game->map.no_wall,
			"NO texture\n") == FALSE)
		return (FALSE);
	if (load_texture(game, &game->so_texture, game->map.so_wall,
			"SO texture\n") == FALSE)
		return (FALSE);
	if (load_texture(game, &game->we_texture, game->map.we_wall,
			"WE texture\n") == FALSE)
		return (FALSE);
	if (load_texture(game, &game->ea_texture, game->map.ea_wall,
			"EA texture\n") == FALSE)
		return (FALSE);
	return (TRUE);
}

void	init_game_textures(t_game *game)
{
	printf("Initializing game textures\n");
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	if (init_game_walls_paths_and_colors(game) == FALSE
		|| load_all_textures(game) == FALSE)
		exit_game(game, "Error: init game textures failed\n");
	printf("Success: game textures initialized\n");
}
