/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:47:32 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/09 11:51:30 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/rendering.h"

int	init_game_rgb(t_game *game)
{
	int	i;
	int	rgb_index;
	int	j;

	i = 0;
	game->map.floor_color = -1;
	game->map.ceiling_color = -1;
	if (game->file == NULL)
		return (printf("Error: game->file is NULL\n"), FALSE);
	while (game->file[i])
	{
		j = 0;
		if (ft_is_line_empty(game->file[i]) == FALSE)
		{
			while (game->file[i][j] == ' ' || game->file[i][j] == '\t')
				j++;
			rgb_index = ft_index_of_first_rgb(game->file[i]);
			if (ft_comp(&game->file[i][j], "F") == TRUE)
				game->map.floor_color = rgb_to_int(&game->file[i][rgb_index]);
			else if (ft_comp(&game->file[i][j], "C") == TRUE)
				game->map.ceiling_color = rgb_to_int(&game->file[i][rgb_index]);
		}
		i++;
	}
	if (game->map.floor_color == -1 || game->map.ceiling_color == -1)
		return (printf("Error: Failed to load rgb colors\n"), FALSE);
	return (TRUE);
}
