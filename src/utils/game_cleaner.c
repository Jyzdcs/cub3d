/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:16:43 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/06 15:07:37 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "../include/cub3d.h"

void free_all(char **str)
{
	int i = 0;

	while (str[i])
		free(str[i++]);
}

void exit_game(t_game *game, char *message)
{
	if (game->file)
		free_all(game->file);
	ft_putstr_fd(message, 2);
#ifdef TESTING
	// Don't exit in test mode
	return;
#else
	exit(1);
#endif
}