/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_and_textures_checker.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 14:20:16 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/10 14:32:51 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/map_parser.h"

int	ft_rgb_and_textures_checker(t_game *game)
{
	int	i;
	int	valid_path_counter;
	int	valid_rgb_counter;

	valid_path_counter = 0;
	valid_rgb_counter = 0;
	i = 0;
	while (game->file[i])
	{
		if (ft_is_identifier(game->file[i]) == 2
			&& ft_rgb_checker(game->file[i], &valid_rgb_counter) == FALSE)
			return (ft_putstr_fd("Error: invalid rgb\n", 2), FALSE);
		else if (ft_is_identifier(game->file[i]) == 1
			&& ft_textures_checker(game->file[i], &valid_path_counter) == FALSE)
			return (ft_putstr_fd("Error: invalid path or extension\n", 2),
				FALSE);
		i++;
	}
	if (valid_path_counter == 4 && valid_rgb_counter == 2)
		return (TRUE);
	return (printf("Error: invalid number of textures : %d and rgb: %d\n",
			valid_path_counter, valid_rgb_counter), FALSE);
}
