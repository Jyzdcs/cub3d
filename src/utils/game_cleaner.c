/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:16:43 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/02 19:28:43 by kclaudan         ###   ########.fr       */
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

void	exit_game(t_game *game, char *message)
{
	if (game->file)
		free_all(game->file);
	if (game->map.map)
		free_all(game->map.map);
	ft_putstr_fd(message, 2);
	if (game)
	{
		free(game);
		game = NULL;
	}
	exit(1);
}
