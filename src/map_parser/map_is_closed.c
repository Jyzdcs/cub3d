/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_is_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 11:54:43 by kclaudan          #+#    #+#             */
/*   Updated: 2025/11/09 11:54:58 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/map_parser.h"

void	flood_fill(t_map *map, char **map_copy, int x, int y)
{
	if (map->is_closed)
		return ;
	if (x < 0 || y < 0 || y >= map->height)
	{
		map->is_closed = FALSE;
		return ;
	}
	if (x >= ft_strlen(map_copy[y]))
	{
		map->is_closed = FALSE;
		return ;
	}
	if (map_copy[y][x] == '1' || map_copy[y][x] == 'F')
		return ;
	map_copy[y][x] = 'F';
	flood_fill(map, map_copy, x + 1, y);
	flood_fill(map, map_copy, x - 1, y);
	flood_fill(map, map_copy, x, y + 1);
	flood_fill(map, map_copy, x, y - 1);
}

int	map_is_closed(t_map *map, t_player *player)
{
	char	**map_copy;

	map_copy = create_map_copy(map);
	if (!map_copy)
		return (ft_putstr_fd("Error: Failed to create map copy\n", 2), FALSE);
	if (player->x < 0 || player->y < 0 || player->y >= map->height
		|| player->x >= (int)ft_strlen(map_copy[(int)player->y]))
	{
		map->is_closed = FALSE;
		free_map_copy(map_copy, map->height);
		return (ft_putstr_fd("Error: Player is out of bounds\n", 2), FALSE);
	}
	flood_fill(map, map_copy, (int)player->x, (int)player->y);
	free_map_copy(map_copy, map->height);
	if (map->is_closed)
		return (FALSE);
	return (TRUE);
}
