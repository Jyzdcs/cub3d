/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:49:04 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/31 13:58:45 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/rendering.h"

static int is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void find_id_player(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (is_player_char(game->map.map[i][j]))
			{
				game->player.id = game->map.map[i][j];
				return;
			}
			j++;
		}
		i++;
	}
}

static void init_player_direction(t_game *game)
{
	if (game->player.id == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->camera.plane_x = 0.66;
		game->camera.plane_y = 0.0;
	}
	else if (game->player.id == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->camera.plane_x = -0.66;
		game->camera.plane_y = 0.0;
	}
	else if (game->player.id == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->camera.plane_x = 0.0;
		game->camera.plane_y = 0.66;
	}
	else if (game->player.id == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->camera.plane_x = 0.0;
		game->camera.plane_y = -0.66;
	}
}

void init_player_data(t_game *game)
{
	find_id_player(game);
	game->player.x += 0.5;
	game->player.y += 0.5;
	game->player.old_x = game->player.x;
	game->player.old_y = game->player.y;
	game->player.speed = 0.07;
	game->player.rotation_speed = 0.05;
	init_player_direction(game);
}
