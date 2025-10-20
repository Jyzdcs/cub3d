/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kclaudan <kclaudan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:20:29 by kclaudan          #+#    #+#             */
/*   Updated: 2025/10/20 18:32:34 by kclaudan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
#include "../../include/map_parser.h"

int	export_map(t_game *game)
{
	int	i;
	int	j;
	int	end;

	i = ft_start_index_of_the_map(game->file);
	end = ft_end_index_of_the_map(game->file, i);
	game->map.map = malloc(sizeof(char *) * (end - i + 1));
	if (i == -1)
		return (FALSE);
	j = 0;
	while (i <= end)
	{
		game->map.map[j] = ft_strdup(game->file[i]);
		j++;
		i++;
	}
	game->map.map[j] = NULL;
	return (TRUE);
}

int	find_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	find_map_max_width(char **map)
{
	int	i;
	int	max_width;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max_width)
			max_width = ft_strlen(map[i]);
		i++;
	}
	return (max_width);
}

void	init_player_pos(t_game *game, char **map)
{
	int	i;
	int	pos_x;

	i = 0;
	while (map[i])
	{
		pos_x = 0;
		while (map[i][pos_x] != 'N' && map[i][pos_x] != 'S'
			&& map[i][pos_x] != 'E' && map[i][pos_x] != 'W'
			&& map[i][pos_x] != '\0')
			pos_x++;
		if (map[i][pos_x] == '\0')
			i++;
		else
			break ;
	}
	game->player.x = pos_x;
	game->player.y = i;
}

void	init_map_basic_struct(t_game *game)
{
	game->map.height = find_map_height(game->map.map);
	game->map.width = find_map_max_width(game->map.map);
}

int	map_is_valid(t_game *game)
{
	if (export_map(game) == FALSE)
	{
		printf("Error: Export map failed\n");
		return (FALSE);
	}
	init_map_basic_struct(game);
	init_player_pos(game, game->map.map);
	if (map_have_one_player(game->map.map) == FALSE)
	{
		printf("Error: Map havent just one player\n");
		return (FALSE);
	}
	if (map_is_closed(game->map.map, &game->map, &game->player) == FALSE)
	{
		printf("Error: Map isnt closed\n");
		return (FALSE);
	}
	return (TRUE);
}