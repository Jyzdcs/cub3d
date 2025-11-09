/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_and_ceiling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:49:23 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/09 11:49:23 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/raycasting.h"
#include "../../include/rendering.h"

void	render_floor_and_ceiling(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (y < SCREEN_HEIGHT / 2)
				draw_pixel(game, x, y, game->map.ceiling_color);
			else
				draw_pixel(game, x, y, game->map.floor_color);
			x++;
		}
		y++;
	}
}
