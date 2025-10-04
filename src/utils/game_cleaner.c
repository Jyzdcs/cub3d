/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_cleaner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:16:43 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/04 17:34:00 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void free_all(char **str)
{
	int i = 0;

	while (str[i])
		free(str[i++]);
}

void free_game(t_game *game)
{
	(void)game;
	return;
}