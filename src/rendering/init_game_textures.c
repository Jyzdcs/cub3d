/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:15:38 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/24 15:18:58 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/rendering.h"

int init_game_walls_paths(t_game *game)
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
